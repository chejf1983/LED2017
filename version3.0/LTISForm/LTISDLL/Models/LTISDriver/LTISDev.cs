﻿using LTISDLL.LEDSYS.Data;
using LTISDLL.LEDSYS.LTISDriver;
using LTISDLL.LEDSYS.LTISDriver.Data;
using LTISDLL.LOGSYS;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace LTISDLL.LEDSYS.LTISDriver
{
    public class LTISDev
    {
        public LTISDev()
        {
            ///注册DLL打印
            //LEDevDriver.DLL_PRINT_SET(delegate(string buffer)
            //{
            //    SysLog.Instance.PrintLog("[DLL]" + buffer);
            //});
        }

        #region 连接与断开
        public static void ResetDev(int index){
            LEDevDriver.LED_LITS_ResetModel_I(index);
        }
        /// <summary>
        /// 连接光谱仪
        /// </summary>
        /// <returns></returns>
        public bool Connect()
        {
            lock (this)
            {
                //已经连接，不用重复连接
                if (!this.connect)
                {
                    if (LEDevDriver.LED_LITS_SEARCH() > 0)
                    {
                        //初始化设备
                        int ret = LEDevDriver.LED_LITS_CONNECT(0);
                        if (LEDevDriver.DLL_SUCCESS != ret)
                        {
                            SysLog.Instance.PrintLog("连接设备失败！" + ret);
                            return false;
                        }

                        //初始化设备参数
                        if (!this.InitDevpar())
                        {
                            return false;
                        }
                        this.connect = true;
                    }
                    else
                    {
                        SysLog.Instance.PrintLog("没有找到设备！");
                    }
                }

                return this.connect;
            }
        }

        /// <summary>
        /// 断开光谱仪
        /// </summary>
        public void DisConnect()
        {
            lock (this)
            {
                if (this.connect)
                {
                    LEDevDriver.LED_LITS_ResetModel();
                    LEDevDriver.LED_LITS_CLOSE();
                    this.connect = false;
                }
            }
        }

        //重置软件模式
        public void Reset()
        {
            LEDevDriver.LED_LITS_ResetModel();
        }
        #endregion

        #region 设备参数
        /// <summary>
        /// 连接状态
        /// </summary>
        private bool connect = false;
        public bool IsConnect { get { return connect; } }

        /// <summary>
        /// 设备序列号
        /// </summary>
        private string serialNum = "";
        public string SerialNum { get { return serialNum; } }

        /// <summary>
        /// 像素点
        /// </summary>
        private int pixlenum = 0;

        //初始化设备参数
        private bool InitDevpar()
        {
            int ret;

            serialNum = "";
            //获取序列号，像素点个数
            byte[] serialnum = new byte[50];
            ret = LEDevDriver.LED_LITS_GetDevInfo(serialnum, ref this.pixlenum);
            if (LEDevDriver.DLL_SUCCESS != ret)
            {
                SysLog.Instance.PrintLog("无法获取设备信息！" + ret);
                return false;
            }
            serialNum = System.Text.Encoding.Default.GetString(serialnum);
            serialNum = serialNum.Replace('\0', ' ');
            serialNum = serialNum.Trim();

            //获取电参数
            int mode = 1;
            SElectricPar epar = new SElectricPar();
            ret = LEDevDriver.LED_LITS_GetElectricPar(ref epar, ref mode);
            if (LEDevDriver.DLL_SUCCESS != ret)
            {
                SysLog.Instance.PrintLog("无法获取电参数信息！" + ret);
                //return false;
            }
            else
            {

                this.elcpar.emode = (LEDMODE)mode;
                this.elcpar.NeVoltage = epar.NeVoltage;
                this.elcpar.NeCurrent = epar.NeCurrent;
                this.elcpar.NeDelay = epar.NeDelay;
                this.elcpar.NeTime = epar.NeTime;

                for (int i = 0; i < 3; i++)
                {
                    this.elcpar.itime[i] = epar.FTime[i];
                    this.elcpar.FVoltage[i] = epar.FVoltage[i];
                    this.elcpar.FCurrent[i] = epar.FCurrent[i];
                    this.elcpar.FDelay[i] = epar.FDelay[i];
                    this.elcpar.FTime[i] = epar.FTime[i];

                    this.elcpar.RVoltage[i] = epar.RVoltage[i];
                    this.elcpar.RCurrent[i] = epar.RCurrent[i];
                    this.elcpar.RDelay[i] = epar.RDelay[i];
                    this.elcpar.RTime[i] = epar.RTime[i];
                }
            }


            ret = LEDevDriver.LED_LITS_GetSPPar(ref this.elcpar.itime[0], ref this.elcpar.itime[1], ref this.elcpar.itime[2]);
            if (LEDevDriver.DLL_SUCCESS != ret)
            {
                SysLog.Instance.PrintLog("无法获取积分时间！" + ret);
                //return false;
            }
            return true;
        }
        #endregion

        #region 光谱仪操作接口
        private CIEData ConvertToCieData(COLOR_PARA colorpar)
        {
            //填值
            CIEData data = new CIEData();
            data.fx = colorpar.fx;
            data.fy = colorpar.fy;
            data.fu = colorpar.fu;
            data.fv = colorpar.fv;
            data.fCCT = colorpar.fCCT;
            data.fdC = colorpar.dC;
            data.fLd = colorpar.fLd;
            data.fPur = colorpar.fPur;
            data.fLp = colorpar.fLp;
            data.fHW = colorpar.fHW;
            data.fLav = colorpar.fLav;
            data.fRa = colorpar.fRa;
            data.fRR = colorpar.fRR;
            data.fGR = colorpar.fGR;
            data.fBR = colorpar.fBR;
            data.fRi = colorpar.fRi;
            data.fIp = colorpar.fIp;
            data.fPh = colorpar.fPh;
            data.fPhe = colorpar.fPhe;
            data.fPlambda = colorpar.fPlambda;
            data.fSpect1 = colorpar.fSpect1;
            data.fSpect2 = colorpar.fSpect2;
            data.fInterval = colorpar.fInterval;
            float intv = colorpar.fInterval == 0 ? 1 : colorpar.fInterval;
            data.fPL = new float[(int)((colorpar.fSpect2 - colorpar.fSpect1) / intv)];
            if (colorpar.fPL != null)
                Array.Copy(colorpar.fPL, data.fPL, data.fPL.Length);
            return data;
        }

        /// <summary>
        /// 采集CIE光谱数据
        /// </summary>
        /// <param name="collectpar"></param>
        /// <returns></returns>
        public CIEData GetCIEData(SPCollectPar collectpar, float[] dkdata)
        {
            lock (this)
            {
                //检查设备连接
                if (!this.connect)
                {
                    throw new Exception("设备未连接");
                }

                //获取暗电流
                if (dkdata == null)
                {
                    throw new Exception("暗电流没有扣除");
                }

                //调用库函数
                SpectralPar par = new SpectralPar();
                par.TriggerMode = collectpar.TriggerMode;
                par.fIntTime = collectpar.fIntTime;
                par.iAveNum = collectpar.iAveNum;
                par.iFilterBW = collectpar.iFilterBW;
                COLOR_PARA colorpar = new LTISDriver.COLOR_PARA();
                int ret = LEDevDriver.LED_LITS_GetData(par, dkdata, dkdata.Length,
                            fDx,
                            fDy,
                            ref colorpar);

                ///检查结果
                if (LEDevDriver.DLL_SUCCESS != ret)
                {
                    throw new Exception("通信失败:" + ret);
                }

                //将结果复制到CIEDATA
                CIEData data = ConvertToCieData(colorpar);

                //返回
                return data;
            }
        }

        /// <summary>
        /// 获取AD值
        /// </summary>
        /// <param name="collectpar"></param>
        /// <returns></returns>
        public float[] GetADValue(SPCollectPar collectpar, float[] dkdata)
        {
            lock (this)
            {
                //检查设备连接
                if (!this.connect)
                {
                    throw new Exception("设备未连接");
                }
                
                //转换输入参数
                SpectralPar par = new SpectralPar();
                par.TriggerMode = collectpar.TriggerMode;
                par.fIntTime = collectpar.fIntTime;
                par.iAveNum = collectpar.iAveNum;
                par.iFilterBW = collectpar.iFilterBW;

                //申请double的buffer
                double[] advalue = new double[this.pixlenum];
                double IP = 0;


                int ret = 0;
                if (dkdata == null)
                {
                    ret = LEDevDriver.LED_LITS_GetDarkData(par, advalue, this.pixlenum);
                }
                else
                {
                    ret = LEDevDriver.LED_LITS_GetOriginalData(par, dkdata, dkdata.Length, advalue, this.pixlenum, ref IP);
                }

                ///检查结果
                if (LEDevDriver.DLL_SUCCESS != ret)
                {
                    throw new Exception("通信失败:" + ret);
                }

                //转换成float数组
                float[] fadvalue = new float[this.pixlenum];
                for (int i = 0; i < fadvalue.Length; i++)
                {
                    fadvalue[i] = (float)(advalue[i]);
                }
                return fadvalue;
            }
        }

        /// <summary>
        /// 光谱仪定标
        /// </summary>
        /// <param name="collectpar"></param>
        /// <param name="iCalType"></param>
        /// <param name="fCCT"></param>
        /// <param name="fFlux"></param>
        /// <param name="iStaNum"></param>
        /// <param name="fStaWL"></param>
        /// <param name="fStaPL"></param>
        /// <param name="fIp"></param>
        public void CalibrateDevice(SPCollectPar collectpar,
                                                int iCalType,
                                                float fCCT,
                                                float fFlux,
                                                int iStaNum,    //点个数
                                                float[] fStaWL, //波长
                                                float[] fStaPL, float[] dkdata) //光度值))
        {
            lock (this)
            {
                //检查设备连接
                if (!this.connect)
                {
                    throw new Exception("设备未连接");
                }

                //检查暗电流是否扣除
                if (dkdata == null)
                {
                    throw new Exception("暗电流没有扣除");
                }

                //转换输入参数
                SpectralPar par = new SpectralPar();
                par.TriggerMode = collectpar.TriggerMode;
                par.fIntTime = collectpar.fIntTime;
                par.iAveNum = collectpar.iAveNum;
                par.iFilterBW = collectpar.iFilterBW;

                float ip = 0;
                int ret = LEDevDriver.LED_LITS_Calib(par, dkdata, dkdata.Length, iCalType,
                    fCCT, fFlux, iStaNum, fStaWL, fStaPL, ref ip);

                ///检查结果
                if (LEDevDriver.DLL_SUCCESS != ret)
                {
                    if (ret == LEDevDriver.TIME_TOO_SMALL)
                    {
                        throw new Exception("积分时间太短,ip = " + ip);
                    }
                    else if (ret == LEDevDriver.TIME_TOO_BIG)
                    {
                        throw new Exception("积分时间太长,ip = " + ip);
                    }
                    else
                        throw new Exception("" + ret);
                }
            }
        }
        #endregion

        #region 光谱仪，电参数板控制接口
        private LEDCollectPar elcpar = new LEDCollectPar();
        /// <summary>
        /// 光电参数
        /// </summary>
        public LEDCollectPar LEDTestPar { get { return elcpar; } }

        private int timeout = 2500;

        /// <summary>
        /// 设置光电参数
        /// </summary>
        /// <param name="ntestpar"></param>
        /// <param name="ledpars"></param>
        /// <param name="lednum"></param>
        /// <returns></returns>
        public void SetElectricPar(LEDCollectPar ntestpar, LEDType type)
        {
            //赋值电参数
            SElectricPar elcpar = new SElectricPar();

            elcpar.rgb_num = ntestpar.cl_num;
            elcpar.NeVoltage = ntestpar.NeVoltage;
            elcpar.NeCurrent = ntestpar.NeCurrent;
            elcpar.NeDelay = ntestpar.NeDelay;
            elcpar.NeTime = ntestpar.NeTime;

            elcpar.FVoltage = new float[3];
            elcpar.FCurrent = new float[3];
            elcpar.FDelay = new float[3];
            elcpar.FTime = new float[3];

            elcpar.RVoltage = new float[3];
            elcpar.RCurrent = new float[3];
            elcpar.RDelay = new float[3];
            elcpar.RTime = new float[3];
            for (int i = 0; i < 3; i++)
            {
                elcpar.FVoltage[i] = ntestpar.FVoltage[i];
                elcpar.FCurrent[i] = ntestpar.FCurrent[i];
                elcpar.FDelay[i] = ntestpar.FDelay[i];
                elcpar.FTime[i] = ntestpar.FTime[i];

                elcpar.RVoltage[i] = ntestpar.RVoltage[i];
                elcpar.RCurrent[i] = ntestpar.RCurrent[i];
                elcpar.RDelay[i] = ntestpar.RDelay[i];
                elcpar.RTime[i] = ntestpar.RTime[i];
            }

            //下发电参数
            if (LEDevDriver.DLL_SUCCESS != LEDevDriver.LED_LITS_SetElectricPar(elcpar, (int)ntestpar.emode))
            {
                throw new Exception("设置电参数失败！");
            }

            System.Threading.Thread.Sleep(20);

            //下发光参数
            if (LEDevDriver.DLL_SUCCESS != LEDevDriver.LED_LITS_SetSPPar(ntestpar.itime[0], ntestpar.itime[1], ntestpar.itime[2], 1))
            {

                throw new Exception("设置积分时间失败！");
            }

            System.Threading.Thread.Sleep(20);

            //下发LED类型
            if (LEDevDriver.DLL_SUCCESS != LEDevDriver.LED_LITS_SetLEDType((int)type))
            {
                throw new Exception("设置类型失败！");
            }

            //更新本地缓存
            this.elcpar = ntestpar;
        }

        /// <summary>
        /// 下发bin号
        /// </summary>
        /// <param name="bin"></param>
        public void SetBin(int bin)
        {
            lock (this)
            {
                //检查设备连接
                if (!this.connect)
                {
                    throw new Exception("设备未连接");
                }

                if (LEDevDriver.DLL_SUCCESS !=
                        LEDevDriver.LED_LITS_SetBin(bin))
                {

                    throw new Exception("下发bin号失败");
                }
            }
        }

        /// <summary>
        /// 获取原始三晶数据
        /// </summary>
        /// <returns></returns>
        public ADValueList GetOriginalThreeLEDData()
        {
            lock (this)
            {
                //检查设备连接
                if (!this.connect)
                {
                    throw new Exception("设备未连接");
                }

                ADValueList ret = new ADValueList(elcpar.cl_num, this.pixlenum);

                ElectricData[] edatas = new ElectricData[3];
                for (int i = 0; i < 3; i++)
                {
                    //检查暗电流是否扣除
                    if (i < (int)this.LEDTestPar.cl_num && !LEDPlatForm.Instance.LEDModels.DKStore.IsDKDataAvailable(LEDTestPar.itime[i]))
                    {
                        throw new Exception("暗电流没有扣除");
                    }
                    edatas[i] = new ElectricData();
                }

                float[] dkdata1 = LEDPlatForm.Instance.LEDModels.DKStore.GetDKData(LEDTestPar.itime[0]);
                float[] dkdata2 = LEDPlatForm.Instance.LEDModels.DKStore.GetDKData(LEDTestPar.itime[1]);
                float[] dkdata3 = LEDPlatForm.Instance.LEDModels.DKStore.GetDKData(LEDTestPar.itime[2]);

                //采集三晶数据
                if (LEDevDriver.DLL_SUCCESS != LEDevDriver.LED_LITS_GetLEDOriginalData(
                    TRIGGER_MODE.SOFTWARE_SYNCHRONOUS, 1,
                    dkdata1, dkdata2, dkdata3, dkdata1.Length,
                    ret.advalue1, ret.advalue2, ret.advalue3, ret.advalue1.Length,
                    ref edatas[0], ref edatas[1], ref edatas[2],
                    (int)elcpar.cl_num, timeout))
                {
                    throw new Exception("采集数据失败");
                }

                //转换数据结构
                for (int i = 0; i < (int)elcpar.cl_num; i++)
                {
                    ret.edatas[i].NeType = edatas[i].NeType;
                    ret.edatas[i].fVol = edatas[i].fVol;
                    ret.edatas[i].fIr = Math.Abs(edatas[i].fIr) * 1000; //从mA转uA

                    //计算光效
                    ret.edatas[i].fGx = 0;
                }

                return ret;
            }
        }

        /// <summary>
        /// 采集LED和电参数
        /// </summary>
        /// <param name="TriggerMode"></param>
        /// <param name="needCal"></param>
        /// <returns></returns>
        public LEDData GetLEDData(TRIGGER_MODE TriggerMode, CalData calmodify)
        {
            lock (this)
            {
                //检查设备连接
                if (!this.connect)
                {
                    throw new Exception("设备未连接");
                }

                SpectralPar[] spar = new SpectralPar[3];
                float[] dx = new float[3];
                float[] dy = new float[3];
                COLOR_PARA[] ciedatas = new COLOR_PARA[3];
                ElectricData[] edatas = new ElectricData[3];

                float[] dkdata1 = LEDPlatForm.Instance.LEDModels.DKStore.GetDKData(LEDTestPar.itime[0]);
                float[] dkdata2 = LEDPlatForm.Instance.LEDModels.DKStore.GetDKData(LEDTestPar.itime[1]);
                float[] dkdata3 = LEDPlatForm.Instance.LEDModels.DKStore.GetDKData(LEDTestPar.itime[2]);

                for (int i = 0; i < 3; i++)
                {
                    //检查暗电流是否扣除
                    if (i < (int)this.LEDTestPar.cl_num && !LEDPlatForm.Instance.LEDModels.DKStore.IsDKDataAvailable(LEDTestPar.itime[i]))
                    {
                        throw new Exception("暗电流没有扣除");
                    }

                    spar[i].TriggerMode = TriggerMode;
                    spar[i].fIntTime = LEDTestPar.itime[i];
                    spar[i].iAveNum = 1;
                    spar[i].iFilterBW = 1;

                    dx[i] = fDx;
                    dy[i] = fDy;

                    ciedatas[i] = new COLOR_PARA();
                    edatas[i] = new ElectricData();
                }

                //采集三晶数据
                if (LEDevDriver.DLL_SUCCESS != LEDevDriver.LED_LITS_GetLEDData(
                    spar[0], spar[1], spar[2],
                    dkdata1, dkdata2, dkdata3, dkdata1.Length,
                    dx, dy,
                    ref ciedatas[0], ref ciedatas[1], ref ciedatas[2],
                    ref edatas[0], ref edatas[1], ref edatas[2],
                    (int)elcpar.cl_num, timeout))
                {
                    throw new Exception("采集数据失败");
                }


                //转换数据
                LEDData leddata = new LEDData(elcpar.cl_num);
                for (int i = 0; i < (int)elcpar.cl_num; i++)
                {
                    leddata.ciedata[i] = ConvertToCieData(ciedatas[i]);
                    /*
                    leddata.ciedata[i].fRi = new float[15];
                    for (int m = 0; m < leddata.ciedata[i].fRi.Length; m++ )
                    {
                        leddata.ciedata[i].fRi[m] = 0;
                    }*/

                    EleData edata = new EleData();
                    edata.NeType = edatas[i].NeType;
                    edata.fVol = edatas[i].fVol;
                    edata.fIr = Math.Abs(edatas[i].fIr) * 1000; //从mA转uA

                    //计算光效
                    float w = edata.fVol * edata.fIr;
                    if (w >= -float.Epsilon && w <= float.Epsilon)
                    {
                        edata.fGx = 0;
                    }
                    else
                    {
                        edata.fGx = leddata.ciedata[i].fPh / (w);
                    }

                    leddata.eledata[i] = edata;
                }

                if (calmodify != null)
                {
                    //选取结果和修正系数中，晶数小的值，进行遍历
                    int clnum = (int)leddata.rgb_num < (int)calmodify.lednum ? (int)leddata.rgb_num : (int)calmodify.lednum;
                    //修正结果
                    for (int i = 0; i < clnum; i++)
                    {
                        leddata.ciedata[i].fPh *= calmodify.fPh[i];
                        leddata.ciedata[i].fLd += calmodify.fLd[i];
                        leddata.ciedata[i].fLp += calmodify.fLp[i];
                        leddata.ciedata[i].fx += calmodify.fx[i];
                        leddata.ciedata[i].fy += calmodify.fy[i];
                        leddata.eledata[i].fVol += calmodify.fVol[i];
                        leddata.ciedata[i].fRa += calmodify.fRa[i];
                        leddata.ciedata[i].fRi[8] += calmodify.fR9[i];
                    }
                }

                return leddata;
            }
        }
        #endregion

        #region 校准
        //光谱仪x,y校准系数
        public float fDx { get { return Properties.Settings.Default.fdx; } set { Properties.Settings.Default.fdx = value; Properties.Settings.Default.Save(); } }
        public float fDy { get { return Properties.Settings.Default.fdy; } set { Properties.Settings.Default.fdy = value; Properties.Settings.Default.Save(); } }
        #endregion

        #region 电参数测试
        public EleData GetLecTestData(ElcTestPar elctest_par)
        {
            lock (this)
            {
                //检查设备连接
                if (!this.connect)
                {
                    throw new Exception("设备未连接");
                }

                ElectricData ret = new ElectricData();
                SEleTestPar par = new SEleTestPar();
                par.rgb_index = elctest_par.rgb_index;
                par.fCurrent = elctest_par.Current;
                par.fVol = elctest_par.Volt;
                par.fdelay = elctest_par.delay;
                par.ftime = elctest_par.time;
                par.test_mode = (int)elctest_par.tmode;
                //采集三晶数据
                int DLL_RET = LEDevDriver.LED_LITS_TestElcBord(par, ref ret);
                if (LEDevDriver.DLL_SUCCESS != DLL_RET)
                {
                    throw new Exception("采集数据失败:" + DLL_RET);
                }

                EleData eret = new EleData();
                eret.fIr = ret.fIr;
                eret.fVol = ret.fVol;
                eret.NeType = ret.NeType;
                return eret;
            }
        }
        #endregion
    }
}
