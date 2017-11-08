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
    //public delegate void UpdateControl();
    public class LEDTest
    {
        private ControlSystem ledsystem;

        public LEDTest(ControlSystem ledsystem)
        {
            this.ledsystem = ledsystem;
        }

        #region 采集数据
        private bool needsetbin = true;
        public bool NeedSetBin { get { return this.needsetbin; } set { this.needsetbin = value; } }
        //记时器
        private System.Diagnostics.Stopwatch sw = new System.Diagnostics.Stopwatch();

        /// <summary>
        /// 测试准备
        /// </summary>
        /// <returns></returns>
        private bool PreparTest()
        {
            //设置测试参数
            if (!this.ledsystem.TestConfig.SetTestPar())
            {
                return false;
            }

            //检查暗电流是否已经扣除
            if (!this.ledsystem.DKControl.CheckDKData(
                this.ledsystem.TestConfig.ConfigPar.LEDTestPar.itime, 
                this.ledsystem.TestConfig.ConfigPar.LEDTestPar.lednum))
            {
                this.ledsystem.State = ControlState.Connect;
                return false;
            }

            //设置状态
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
                //检查分bin过滤条件
                if (!LEDPlatForm.Instance.LEDModels.filterPolicy.IsFilterReady)
                {
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR,
                        "没有设置分bin策略,无法进行测试");
                    this.ledsystem.State = ControlState.Connect;
                    return;
                }

                //测试准备
                if (this.PreparTest())
                {
                    //单次采集也启动新进程
                    ThreadPool.QueueUserWorkItem(new WaitCallback(delegate
                    {
                        try
                        {
                            //统计单次采集时间
                            sw.Reset();
                            sw.Start();
                            ///从设备采集数据
                            LEDData data = LEDPlatForm.Instance.LEDModels.LTISDev.GetLEDData(
                                this.ledsystem.TestConfig.ConfigPar.TestMode,
                                this.ledsystem.CalControl.CalParameter);

                            //分bin
                            LEDPlatForm.Instance.LEDModels.filterPolicy.FilterData(data);

                            if(needsetbin)
                            //下发bin数据
                            LEDPlatForm.Instance.LEDModels.LTISDev.SetBin(data.report.binnum);

                            //停止采集
                            sw.Stop();

                            //记录时间
                            data.timeconsume = sw.Elapsed.TotalMilliseconds;

                            //保存数据
                            LEDPlatForm.Instance.LEDModels.DataTable.AddNewRecord(data);
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
                //检查分bin过滤条件
                if (!LEDPlatForm.Instance.LEDModels.filterPolicy.IsFilterReady)
                {
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR,
                        "没有设置分bin策略,无法进行测试");
                    this.ledsystem.State = ControlState.Connect;
                    return false;
                }

                //检查测试条件
                if (this.PreparTest())
                {
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
                                LEDData leddata = LEDPlatForm.Instance.LEDModels.LTISDev.GetLEDData(
                                    this.ledsystem.TestConfig.ConfigPar.TestMode,
                                    this.ledsystem.CalControl.CalParameter);

                                //分bin
                                LEDPlatForm.Instance.LEDModels.filterPolicy.FilterData(leddata);
                                
                                if (needsetbin)
                                //下发bin数据
                                LEDPlatForm.Instance.LEDModels.LTISDev.SetBin(leddata.report.binnum);

                                //统计结束
                                sw.Stop();

                                //更新统计时间
                                leddata.timeconsume = sw.Elapsed.TotalMilliseconds;

                                //保存数据
                                LEDPlatForm.Instance.LEDModels.DataTable.AddNewRecord(leddata);

                                ///采样间隔至少1ms
                                Thread.Sleep((int)this.ledsystem.TestConfig.ConfigPar.TimeLag);
                            }
                            catch (Exception ex)
                            {
                                //超时异常不处理，继续采集，直到手动停止
                                Console.Write(ex.Message);
                                sw.Stop();
                            }
                        }
                        //如果循环结束，重置状态
                        this.ledsystem.State = ControlState.Connect;
                        ///出现异常，停止采集
                        this.isSustainedStart = false;

                    }));
                }
                
                return isSustainedStart;
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

        #region 空测试
        public LEDData CollectDataOnly()
        {
            lock (this.ledsystem)
            {
                if (this.PreparTest())
                {
                    try
                    {
                        return LEDPlatForm.Instance.LEDModels.LTISDev.GetLEDData(TRIGGER_MODE.SOFTWARE_SYNCHRONOUS,
                             this.ledsystem.CalControl.CalParameter);
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

                return null;
            }
        }
        #endregion

        #endregion
    }
}
