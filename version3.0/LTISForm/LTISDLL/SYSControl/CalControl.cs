using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LTISDLL.LEDSYS.LTISDriver.Data;
using LTISDLL.FaultSystem;
using LTISDLL.LEDSYS.Data;
using LTISDLL.LEDSYS.LTISDriver;

namespace LTISDLL.SYSControl
{
    public class CalControl
    {
        private ControlSystem ledsystem;

        public CalControl(ControlSystem ledsystem)
        {
            this.ledsystem = ledsystem;
        }

        /// <summary>
        /// 是否正在校准
        /// </summary>
        private bool isbussy = false;

        /// <summary>
        /// 校准平均次数
        /// </summary>
        private int avrtime = 10;
               
        /// <summary>
        /// 单次采样
        /// </summary>
        public CalData GetCalOriginalData()
        {
            lock (this.ledsystem)
            {
                //检查是否开始了连续测试
                if (this.isbussy)
                {
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR,
                       "正在自动定标!");
                    return null;
                }

                //检查系统状态
                if (this.ledsystem.State != ControlState.Connect)
                {
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR,
                       "无法开始采集，当前设备:" + ControlStateString.ToString(this.ledsystem.State));
                    return null;
                }

                //检查暗电流是否已经扣除
                if (!this.ledsystem.TestControl.CheckDKData(this.ledsystem.TestConfig.LEDTestPar.itime))
                {
                    return null;
                }

                try
                {
                    //设置状态
                    this.ledsystem.State = ControlState.Calibrate;

                    //下发电参数，光参数
                    this.ledsystem.LedModel.LTISDev.SetElectricPar(this.ledsystem.TestConfig.LEDTestPar);

                    //采集原始定标数据
                    LEDData tdata = this.ledsystem.LedModel.LTISDev.GetLEDData(TRIGGER_MODE.SOFTWARE_SYNCHRONOUS);

                    //原始定标数据赋值
                    CalData ret = new CalData(tdata.lednum);

                    for (int i = 0; i < ret.lednum; i++)
                    {
                        ret.fPh[i] = tdata.ciedata[i].fPh;
                        ret.fLd[i] = tdata.ciedata[i].fLd;
                        ret.fLp[i] = tdata.ciedata[i].fLp;
                        ret.fx[i] = tdata.ciedata[i].fx;
                        ret.fy[i] = tdata.ciedata[i].fy;
                        ret.fVol[i] = tdata.eledata[i].fVol;
                        ret.fRa[i] = tdata.ciedata[i].fRa;
                        ret.fR9[i] = tdata.ciedata[i].fRi[8];
                    }

                    return ret;
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

        /// <summary>
        /// 获取定标系数
        /// </summary>
        /// <param name="stdData"></param>
        /// <returns></returns>
        public CalData GetCalibratePar(CalData stdData)
        {
            lock (this.ledsystem)
            {
                //检查是否开始了连续测试
                if (this.isbussy)
                {
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR,
                       "正在自动定标!");
                    return null;
                }

                //检查系统状态
                if (this.ledsystem.State != ControlState.Connect)
                {
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR,
                       "无法开始采集，当前设备:" + ControlStateString.ToString(this.ledsystem.State));
                    return null;
                }

                //检查暗电流是否已经扣除
                if (!this.ledsystem.TestControl.CheckDKData(this.ledsystem.TestConfig.LEDTestPar.itime))
                {
                    return null;
                }

                try
                {
                    //定标状态
                    this.ledsystem.State = ControlState.Calibrate;

                    //下发电参数，光参数
                    this.ledsystem.LedModel.LTISDev.SetElectricPar(this.ledsystem.TestConfig.LEDTestPar);

                    //采集LED数据
                    LEDData[] retarray = new LEDData[this.avrtime];
                    for (int i = 0; i < avrtime; i++)
                    {
                        //获取三晶LED结果，并且不进行修正
                        retarray[i] = this.ledsystem.LedModel.LTISDev.GetLEDData(TRIGGER_MODE.SOFTWARE_SYNCHRONOUS, false);
                    }

                    //平均值
                    CalData ret = new CalData(retarray[0].lednum);

                    //将测量结果取平均
                    foreach (LEDData tdata in retarray)
                    {
                        for (int i = 0; i < ret.lednum; i++)
                        {
                            ret.fPh[i] += tdata.ciedata[i].fPh / this.avrtime;
                            ret.fLd[i] += tdata.ciedata[i].fLd / this.avrtime;
                            ret.fLp[i] += tdata.ciedata[i].fLp / this.avrtime;
                            ret.fx[i] += tdata.ciedata[i].fx / this.avrtime;
                            ret.fy[i] += tdata.ciedata[i].fy / this.avrtime;
                            ret.fVol[i] += tdata.eledata[i].fVol / this.avrtime;
                            ret.fRa[i] += tdata.ciedata[i].fRa / this.avrtime;
                            ret.fR9[i] += tdata.ciedata[i].fRi[8] / this.avrtime;
                        }
                    }

                    //检查输入标准值的晶数和测量结果的晶数
                    if (stdData.lednum != ret.lednum)
                    {
                        FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, "输入的晶数和当前设置的不一致，请检查输入");
                        return null;
                    }

                    //取差值
                    for (int i = 0; i < ret.lednum; i++)
                    {
                        ret.fPh[i] = (float)Math.Round(ret.fPh[i] - stdData.fPh[i], 4);
                        ret.fLd[i] = (float)Math.Round(ret.fLd[i] - stdData.fLd[i], 4);
                        ret.fLp[i] = (float)Math.Round(ret.fLp[i] - stdData.fLp[i], 4);
                        ret.fx[i] = (float)Math.Round(ret.fx[i] - stdData.fx[i], 4);
                        ret.fy[i] = (float)Math.Round(ret.fy[i] - stdData.fy[i], 4);
                        ret.fVol[i] = (float)Math.Round(ret.fVol[i] - stdData.fVol[i], 4);
                        ret.fRa[i] = (float)Math.Round(ret.fRa[i] - stdData.fRa[i], 4);
                        ret.fR9[i] = (float)Math.Round(ret.fR9[i] - stdData.fR9[i], 4);
                    }

                    //返回定标系数
                    return ret;
                }
                catch (Exception ex)
                {
                    //校准失败
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, ex.Message);
                    return null;
                }
                finally
                {
                    this.ledsystem.State = ControlState.Connect;
                }

            }
        }

        /// <summary>
        /// 设置定标系数
        /// </summary>
        /// <param name="caldata"></param>
        public CalData CurrentCalPara
        {
            get { return this.ledsystem.LedModel.LTISDev.CalModifyData; }
            set { this.ledsystem.LedModel.LTISDev.CalModifyData = value; }
        }

        /// <summary>
        /// 当前修正系数对应的标准值
        /// </summary>
        public CalData StdCalData
        {
            get { return this.ledsystem.LedModel.LTISDev.CalStddata; }
            set
            {
                this.ledsystem.LedModel.LTISDev.CalStddata = value;
            }
        }
    }
}
