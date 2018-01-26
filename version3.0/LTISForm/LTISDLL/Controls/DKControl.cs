using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LTISDLL.LEDSYS.LTISDriver.Data;
using LTISDLL.LEDSYS.Data;

namespace LTISDLL.SYSControl
{
    public delegate bool ReQuestDkDataCollect();
    public class DKControl
    {
        private ControlSystem ledsystem;

        public DKControl(ControlSystem controlSystem)
        {
            // TODO: Complete member initialization
            this.ledsystem = controlSystem;
        }


        /// <summary>
        /// 是否需要重新校准暗电流
        /// </summary>
        public bool NeedReStoreDkData = true;
        public event ReQuestDkDataCollect NeedClearDK;


        //开始扣除暗电流提示
        public event ReQuestDkDataCollect RequestDKModify;
        //暗电流扣除完毕提示
        public event ReQuestDkDataCollect DKFinished;
        
        /// <summary>
        /// 提示用户进行暗电流扣除
        /// </summary>
        /// <param name="ftime"></param>
        /// <returns></returns>
        public bool CheckDKData(float[] ftime, int num)
        {
            float[] time = new float[(int)num];

            for (int i = 0; i < ftime.Length; i++)
            {
                if (i < (int)num)
                {
                    time[i] = ftime[i];
                }
            }

            return this.CheckDKData(time);
        }

        /// <summary>
        /// 提示用户进行暗电流扣除
        /// </summary>
        /// <param name="ftime"></param>
        /// <returns></returns>
        public bool CheckDKData(float[] ftime)
        {
            //开机后，第一次请求用户检查是否需要重新校准所有暗电流
            if (this.NeedReStoreDkData)
            {
                if (NeedClearDK != null)
                {
                    if (this.NeedClearDK())
                    {
                        //如果需要重新效暗电流，清除所有旧记录
                        LEDPlatForm.Instance.LEDModels.DKStore.ClearAllDkData();
                    }
                    NeedReStoreDkData = false;
                }
            }

            //检查所有积分时间
            foreach (float time in ftime)
            {
                //如果有一个积分时间没有保存暗电流，就提示开始扣除暗电流
                if (!LEDPlatForm.Instance.LEDModels.DKStore.IsDKDataAvailable(time))
                {
                    //发送扣暗电流请求
                    if (RequestDKModify != null)
                    {
                        //如果暗电流请求成功,自动扣除暗电流
                        this.RequestDKModify();

                        if (this.DKModify(ftime) && this.DKFinished != null)
                        {
                        //提示暗电流扣除完毕
                            this.DKFinished();
                        }
                    }

                    return false; ;
                }
            }

            return true;
        }

        /// <summary>
        /// 扣除暗电流
        /// </summary>
        /// <param name="collectpar"></param>
        /// <returns></returns>
        private bool DKModify(float[] ftime)
        {
            lock (this)
            {
                //检查系统状态
                if (this.ledsystem.State != ControlState.Connect)
                {
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR,
                       "无法开始采集，当前设备:" + ControlStateString.ToString(this.ledsystem.State));
                    return false;
                }

                SPCollectPar collectpar = new SPCollectPar();
                collectpar.iAveNum = 10;
                collectpar.iFilterBW = 1;
                collectpar.TriggerMode = TRIGGER_MODE.SOFTWARE_SYNCHRONOUS;
                foreach (float time in ftime)
                {
                    collectpar.fIntTime = time;

                    try
                    {
                        float[] fadvalue = LEDPlatForm.Instance.LEDModels.LTISDev.GetADValue(collectpar, null);
                        //添加到暗电流库
                        LEDPlatForm.Instance.LEDModels.DKStore.SaveDKDat(time, fadvalue);
                    }
                    catch (Exception ex)
                    {
                        FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR,
                            "暗电流采集失败:" + ex.Message);
                        return false;
                    }
                }
                //返回暗电流
                return true;
            }
        }

        /// <summary>
        /// 清除暗电流
        /// </summary>
        public void ClearALLDK()
        {
            //如果需要重新效暗电流，清除所有旧记录
            LEDPlatForm.Instance.LEDModels.DKStore.ClearAllDkData();
        }
    }
}
