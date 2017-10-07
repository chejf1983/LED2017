using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LTISDLL.LEDSYS.Data;
using LTISDLL.LEDSYS.LTISDriver.Data;
using System.Threading;
using LTISDLL.FaultSystem;

namespace LTISDLL.SYSControl
{
    public delegate bool ReQuestDkDataCollect();
    public delegate void UpdateControl();
    public class LEDTest
    {
        private ControlSystem ledsystem;

        public LEDTest(ControlSystem ledsystem)
        {
            this.ledsystem = ledsystem;
            this.ledsystem.StateChangeEvent += new ChangeState(ledsystem_StateChangeEvent);
        }

        private void ledsystem_StateChangeEvent(ControlState laststate, ControlState newstate)
        {
            //配置过后，清空数据表,重新记录
            if (laststate == ControlState.Config && newstate == ControlState.Connect)
            {
                this.DataTable.CleanTable();
            }
        }

        //数据报表接口
        public LTISDLL.LEDSYS.DataReport.DataSaver DataTable { get { return this.ledsystem.LedModel.DataTable; } }

        #region 采集数据
        //记时器
        private System.Diagnostics.Stopwatch sw = new System.Diagnostics.Stopwatch();

        #region 暗电流检查
        //暗电流扣除请求
        public event ReQuestDkDataCollect RequestDKModify;
        public event ReQuestDkDataCollect NeedClearDK;

        /// <summary>
        /// 提示用户进行暗电流扣除
        /// </summary>
        /// <param name="ftime"></param>
        /// <returns></returns>
        public bool CheckDKData(float[] ftime)
        {
            if (this.ledsystem.LedModel.LTISDev.NeedReStoreDkData)
            {
                //如果没有保存，发送扣暗电流请求
                if (NeedClearDK != null)
                {
                    if (this.NeedClearDK())
                    {
                        this.ledsystem.LedModel.LTISDev.ClearAllDkData();
                    }
                    this.ledsystem.LedModel.LTISDev.NeedReStoreDkData = false;
                }
            }

            foreach (float time in ftime)
            {
                //检查积分时间对应的暗电流是否有保存
                if (!this.ledsystem.LedModel.LTISDev.IsDKDataAvailable(time))
                {
                    //如果没有保存，发送扣暗电流请求
                    if (RequestDKModify != null)
                    {
                        //如果暗电流请求成功,自动扣除暗电流
                        this.RequestDKModify();
                    }

                    return false; ;
                }
            }

            return true;
        }
        #endregion

        /// <summary>
        /// 检测测试条件
        /// </summary>
        /// <returns></returns>
        private bool LockSystemState()
        {
            //检查系统状态
            if (this.ledsystem.State != ControlState.Connect)
            {
                FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR,
                   "无法开始采集，当前设备:" + ControlStateString.ToString(this.ledsystem.State));
                return false;
            }

            //检查暗电流是否已经扣除
            if (!CheckDKData(this.ledsystem.TestConfig.LEDTestPar.itime))
            {
                this.ledsystem.State = ControlState.Connect;
                return false;
            }

            //检查分bin过滤条件
            if (!this.ledsystem.LedModel.filterPolicy.IsFilterReady)
            {
                FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR,
                    "没有设置分bin策略,无法进行测试");
                this.ledsystem.State = ControlState.Connect;
                return false;
            }

            this.ledsystem.State = ControlState.LEDCollect;
            return true;
        }

        #region 单次采集
        /// <summary>
        /// 单次采样
        /// </summary>
        public void GetLEDData()
        {
            lock (this.ledsystem)
            {
                //检查测试条件
                if (!this.LockSystemState())
                {
                    return;
                }

                try
                {
                    //下发电参数，光参数
                    this.ledsystem.LedModel.LTISDev.SetElectricPar(this.ledsystem.TestConfig.LEDTestPar);
                }
                catch (Exception ex)
                {
                    this.ledsystem.State = ControlState.Connect;
                    //采集失败
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, ex.Message);
                    return;
                }

                //单次采集也启动新进程
                ThreadPool.QueueUserWorkItem(new WaitCallback(delegate
                {
                    try
                    {
                        //统计单次采集时间
                        sw.Reset();
                        sw.Start();
                        ///从设备采集数据
                        LEDData data = this.ledsystem.LedModel.LTISDev.GetLEDData(this.ledsystem.TestConfig.TestMode);

                        //分bin
                        this.ledsystem.LedModel.filterPolicy.FilterData(data);

                        //下发bin数据
                        this.ledsystem.LedModel.LTISDev.SetBin(data.report.binnum);

                        //停止采集
                        sw.Stop();

                        //记录时间
                        data.timeconsume = sw.Elapsed.TotalMilliseconds;

                        //保存数据
                        this.ledsystem.LedModel.DataTable.AddNewRecord(data);
                    }
                    catch (Exception ex)
                    {
                        sw.Stop();
                        ///通过控制器上报异常
                        FaultCenter.Instance.SendFault(FaultLevel.ERROR,
                            "采集数据失败:" + ex.Message);
                        ///跳出循环
                    }
                    finally
                    {
                        this.ledsystem.State = ControlState.Connect;
                    }

                }));

            }
        }
        #endregion

        #region 连续采集
        /// <summary>
        /// 连续采集是否开始
        /// </summary>
        private bool isSustainedStart = false;
        public bool IsSustainedCollectStart
        {
            get
            {
                return this.isSustainedStart;
            }
        }

        /// <summary>
        /// 开始连续采集
        /// </summary>
        public bool StartSustainedCollect(int time)
        {
            //锁住控制系统
            lock (this.ledsystem)
            {
                //检查测试条件
                if (!this.LockSystemState())
                {
                    //检查失败返回false
                    return false;
                }

                try
                {
                    //下发电参数，光参数
                    this.ledsystem.LedModel.LTISDev.SetElectricPar(this.ledsystem.TestConfig.LEDTestPar);
                }
                catch (Exception ex)
                {
                    //报错
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, ex.Message);
                    //重置状态为connect
                    this.ledsystem.State = ControlState.Connect;
                    //返回失败
                    return false;
                }

                //设置连续采集标志
                this.isSustainedStart = true;
                ///启动新线程
                ThreadPool.QueueUserWorkItem(new WaitCallback(delegate
                {
                    while (this.isSustainedStart)
                    {
                        //统计单次采集时间
                        sw.Reset();
                        sw.Start();
                        try
                        {
                            ///从设备采集数据
                            LEDData leddata = this.ledsystem.LedModel.LTISDev.GetLEDData(this.ledsystem.TestConfig.TestMode);

                            //分bin
                            this.ledsystem.LedModel.filterPolicy.FilterData(leddata);

                            //下发bin数据
                            this.ledsystem.LedModel.LTISDev.SetBin(leddata.report.binnum);

                            //统计结束
                            sw.Stop();

                            //更新统计时间
                            leddata.timeconsume = sw.Elapsed.TotalMilliseconds;

                            //保存数据
                            this.ledsystem.LedModel.DataTable.AddNewRecord(leddata);

                            ///采样间隔至少1ms
                            Thread.Sleep(1);
                        }
                        catch (Exception ex)
                        {
                            sw.Stop();
                            //超时异常不处理，继续采集，直到手动停止
                        }
                    }
                    //如果循环结束，重置状态
                    this.ledsystem.State = ControlState.Connect;
                    ///出现异常，停止采集
                    this.isSustainedStart = false;

                }));
                return true;
            }
        }

        /// <summary>
        /// 停止连续采集
        /// </summary>
        public void StopSustainedCollect()
        {
            lock (this)
            {
                //停止循环即可
                if (this.isSustainedStart)
                {
                    this.isSustainedStart = false;
                }
            }
        }
        #endregion

        #region 暗电流修正
        /// <summary>
        /// 暗电流校准
        /// </summary>
        public void DarkDataModify()
        {
            lock (this.ledsystem)
            {
                //检查系统状态
                if (this.ledsystem.State != ControlState.Connect)
                {
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR,
                       "无法开始采集，当前设备:" + ControlStateString.ToString(this.ledsystem.State));
                    return;
                }

                //扣除暗电流
                foreach (float ttt in this.ledsystem.TestConfig.LEDTestPar.itime)
                {
                    SPCollectPar par = new SPCollectPar();
                    par.fIntTime = ttt;
                    par.iAveNum = 10;
                    par.iFilterBW = 1;
                    par.TriggerMode = TRIGGER_MODE.SOFTWARE_SYNCHRONOUS;
                    try
                    {
                        this.ledsystem.LedModel.LTISDev.StoreDKData(par);
                    }
                    catch (Exception ex)
                    {
                        FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, "获取暗电流失败：" + ex.Message);
                        break;
                    }
                }
            }
        }
        #endregion

        #region 预测试
        public LEDData PreCollectOrignalData()
        {
            lock (this.ledsystem)
            {
                if (!this.LockSystemState())
                {
                    return null;
                }

                try
                {
                    //下发电参数，光参数
                    this.ledsystem.LedModel.LTISDev.SetElectricPar(this.ledsystem.TestConfig.LEDTestPar);
                    return this.ledsystem.LedModel.LTISDev.GetLEDData(TRIGGER_MODE.SOFTWARE_SYNCHRONOUS);
                    //return this.ledsystem.LedModel.LTISDev.GetOriginalThreeLEDData();
                }
                catch (Exception ex)
                {
                    //采集失败
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, ex.Message);
                    return null;
                }
                finally
                {
                    this.ledsystem.State = ControlState.Connect;
                }

            }
        }
        #endregion

        #endregion
    }
}
