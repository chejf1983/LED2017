using LTISDLL.LEDSYS.Data;
using LTISDLL.LEDSYS.LTISDriver.Data;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LTISDLL.LEDSYS;

namespace LTISDLL.SYSControl
{
    public delegate void IsAvailable(bool value);
    public class SPDevControl
    {
        private ControlSystem ledsystem;

        public SPDevControl(ControlSystem ledsystem)
        {
            this.ledsystem = ledsystem;
        }

        /// <summary>
        /// 系统是否连接
        /// </summary>
        public bool IsDevConnect { get { return ledsystem.State == ControlState.Connect; } }

        #region 采集控制
        private float lasttime; //上一次积分时间
        private float[] dkdata = null; //暗电流

        /// <summary>
        /// 采集CIE数据
        /// </summary>
        /// <param name="ftime"></param>
        /// <param name="avrnum"></param>
        /// <param name="ifilter"></param>
        /// <returns></returns>
        public CIEData CollectCIEData(float ftime, int avrnum, int ifilter)
        {
            lock (this.ledsystem)
            {
                //检查系统状态
                if (this.ledsystem.State != ControlState.Connect)
                {
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR,
                       "无法开始采集，当前设备:" + ControlStateString.ToString(this.ledsystem.State));
                }

                if (ftime != lasttime)
                {
                    dkdata = null;
                }

                SPCollectPar par = new SPCollectPar();
                par.fIntTime = ftime;
                par.iAveNum = avrnum;
                par.iFilterBW = ifilter;
                par.TriggerMode = TRIGGER_MODE.SOFTWARE_SYNCHRONOUS;
                try
                {
                    this.ledsystem.State = ControlState.Calibrate;
                    CIEData data = LEDPlatForm.Instance.LEDModels.LTISDev.GetCIEData(par, dkdata);
                    return data;
                }
                catch (Exception ex)
                {
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, "采集数据失败：" + ex.Message);
                    return null;
                }
                finally
                {
                    this.ledsystem.State = ControlState.Connect;
                }
            }
        }

        /// <summary>
        /// 获取AD值
        /// </summary>
        /// <param name="ftime"></param>
        /// <param name="avrnum"></param>
        /// <param name="ifilter"></param>
        /// <returns></returns>
        public float[] CollectADValue(float ftime, int avrnum, int ifilter)
        {
            lock (this.ledsystem)
            {
                //检查系统状态
                if (this.ledsystem.State != ControlState.Connect)
                {
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR,
                       "无法开始采集，当前设备:" + ControlStateString.ToString(this.ledsystem.State));
                }

                if (ftime != lasttime)
                {
                    dkdata = null;
                }

                SPCollectPar par = new SPCollectPar();
                par.fIntTime = ftime;
                par.iAveNum = avrnum;
                par.iFilterBW = ifilter;
                par.TriggerMode = TRIGGER_MODE.SOFTWARE_SYNCHRONOUS;
                //par.TriggerMode = TRIGGER_MODE.EXINT_HIGH_LEVEL;

                try
                {
                    if (dkdata == null)
                    {
                        throw new Exception("没有扣除暗电流");
                    }
                    this.ledsystem.State = ControlState.Calibrate;
                    float[] data = LEDPlatForm.Instance.LEDModels.LTISDev.GetADValue(par, dkdata);

                    return data;
                }
                catch (Exception ex)
                {
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, "采样失败：" + ex.Message);
                    return null;
                }
                finally
                {
                    this.ledsystem.State = ControlState.Connect;
                }
            }
        }

        /// <summary>
        /// 获取暗电流
        /// </summary>
        /// <param name="ftime"></param>
        /// <returns></returns>
        public float[] CollectDkData(float ftime, int avrnum, int ifilter)
        {
            //检查系统状态
            if (this.ledsystem.State != ControlState.Connect)
            {
                FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR,
                   "无法开始采集，当前设备:" + ControlStateString.ToString(this.ledsystem.State));
            }

            SPCollectPar par = new SPCollectPar();
            par.fIntTime = ftime;
            par.iAveNum = avrnum;
            par.iFilterBW = ifilter;
            par.TriggerMode = TRIGGER_MODE.SOFTWARE_SYNCHRONOUS;

            try
            {
                float[] data = LEDPlatForm.Instance.LEDModels.LTISDev.GetADValue(par, null);

                //保存暗电流
                this.lasttime = ftime;
                this.dkdata = data;

                return data;
            }
            catch (Exception ex)
            {
                FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, "获取暗电流失败：" + ex.Message);
                return null;
            }
        }
        #endregion

        #region 定标
        /// <summary>
        /// 定标
        /// </summary>
        /// <param name="ftime"></param>
        /// <param name="avrnum"></param>
        /// <param name="ifilter"></param>
        /// <param name="cct"></param>
        /// <param name="flux"></param>
        /// <returns></returns>
        public bool CCTCalibrate(float ftime, int avrnum, int ifilter, float cct, float flux)
        {
            lock (this.ledsystem)
            {
                //检查系统状态
                if (this.ledsystem.State != ControlState.Connect)
                {
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR,
                       "无法定标，当前设备:" + ControlStateString.ToString(this.ledsystem.State));
                    return false;
                }

                if (this.lasttime != ftime)
                {
                    this.dkdata = null;
                }

                SPCollectPar par = new SPCollectPar();
                par.fIntTime = ftime;
                par.iAveNum = avrnum;
                par.iFilterBW = ifilter;
                par.TriggerMode = TRIGGER_MODE.SOFTWARE_SYNCHRONOUS;

                try
                {
                    this.ledsystem.State = ControlState.Calibrate;
                    LEDPlatForm.Instance.LEDModels.LTISDev.CalibrateDevice(par, 0, cct, flux, 0, null, null, this.dkdata);
                    //return data;
                    return true;
                }
                catch (Exception ex)
                {
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, "定标失败：" + ex.Message);
                    return false;
                }
                finally
                {
                    this.ledsystem.State = ControlState.Config;
                }
            }
        }

        /// <summary>
        /// xy系数修正
        /// </summary>
        /// <param name="testx"></param>
        /// <param name="testy"></param>
        /// <param name="stdx"></param>
        /// <param name="stdy"></param>
        public void XYModify(float testx, float testy, float stdx, float stdy)
        {
            //标准-测试
            LEDPlatForm.Instance.LEDModels.LTISDev.fDx += stdx - testx;
            LEDPlatForm.Instance.LEDModels.LTISDev.fDy += stdy - testy;
        }

        public void ResetXY()
        {
            LEDPlatForm.Instance.LEDModels.LTISDev.fDx = 0;
            LEDPlatForm.Instance.LEDModels.LTISDev.fDy = 0;
        }
        #endregion
    }
}
