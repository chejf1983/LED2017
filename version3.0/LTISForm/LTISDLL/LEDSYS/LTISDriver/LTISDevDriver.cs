using LTISDLL.LEDSYS.Data;
using LTISDLL.LEDSYS.LTISDriver.Data;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace LTISDLL.LEDSYS.LTISDriver
{
    #region 变量
    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct COLOR_PARA
    {
        public float fx;        //色坐标
        public float fy;
        public float fu;
        public float fv;

        public float fCCT;      //相关色温(K)
        public float dC;        //色差dC
        public float fLd;       //主波长(nm)
        public float fPur;      //色纯度(%)
        public float fLp;       //峰值波长(nm)
        public float fHW;       //半波宽(nm)
        public float fLav;      //平均波长(nm)
        public float fRa;       //显色性指数 Ra
        public float fRR;       //红色比
        public float fGR;       //绿色比
        public float fBR;       //蓝色比
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 15)]
        public float[] fRi;   //显色性指数 R1-R15

        public float fIp;      //峰值AD

        public float fPh;      //光度值
        public float fPhe;     //辐射度值
        public float fPlambda; //绝对光谱洗漱
        public float fSpect1;  //起始波长
        public float fSpect2;  //
        public float fInterval; //波长间隔

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5000)]
        public float[] fPL;   //光谱数据
    };

    public struct TestMode
    {
        public int LedMark;  //   单晶，双晶，三晶
        public int testMode; //   BIT0：光谱测试使能 BIT1：电测试使能
    };

    public struct ElectricData
    {
        public float NeType;   //极性 0 正向 1反向
        public float fVol;
        public float fIr;
    };

    public struct SElectricPar
    {
        public float NeVoltage;  //极性电压
        public float NeCurrent;  //极性电流
        public float NeDelay;    //测量延时
        public float NeTime;     //测量时间

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public float[] FVoltage; //LED正向电压
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public float[] FCurrent; //LED正向电流
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public float[] FDelay;   //LED正向延时
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public float[] FTime;    //LED正向测试时间

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public float[] RVoltage; //LED反向电压
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public float[] RCurrent; //LED反向电流
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public float[] RDelay;   //LED反向延时
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public float[] RTime;    //LED反向测试时间

    };

    public struct SpectralPar
    {
        public TRIGGER_MODE TriggerMode;
        public float fIntTime;
        public int iAveNum;
        public int iFilterBW;
    };
    #endregion

    public class LEDevDriver
    {
        #region 错误码
        public static int DLL_SUCCESS = 0;
        public static int FILE_OPEN_FAILED = 1; //文件打开失败
        public static int DEV_OPEN_FAILED = 2;  //设备连接失败
        public static int DEV_INIT_FAILED = 3; //设备初始化失败
        public static int DLL_INIT_FAILED = 4; //dll初始化失败
        public static int DEV_NOT_INIT = 5; //设备没有初始化
        public static int INVALID_PAR = 6;  //无效的参数

        public static int TIME_TOO_SMALL = 7; //设备没有初始化
        public static int TIME_TOO_BIG = 8;  //无效的参数
        public static int DLL_FAILED = -1; //通讯协议返回失败
        #endregion

        public static string dll = System.Environment.CurrentDirectory + "//SpectraArsenalEmission.dll";

        #region dll注册打印函数
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]//一定要加上这句，要不然C#中的回调函数只要被调用一次，程序就异常退出了！！！  
        public delegate void PrintF(string buffer);

        /// <summary>
        /// 添加DLL打印接口
        /// </summary>
        /// <param name="ptr"></param>
        [DllImport("SpectraArsenalEmission.dll", EntryPoint = "DLL_PRINT_SET")]
        public static extern void DLL_PRINT_SET(PrintF ptr);
        #endregion

        #region 初始化
        /// <summary>
        /// 搜索设备
        /// </summary>
        /// <returns>返回搜索到的个数</returns>
        [DllImport("SpectraArsenalEmission.dll", EntryPoint = "LED_LITS_SEARCH")]
        public static extern int LED_LITS_SEARCH();

        /// <summary>
        /// 断开连接设备
        /// </summary>
        /// <returns></returns>
        [DllImport("SpectraArsenalEmission.dll", EntryPoint = "LED_LITS_CLOSE")]
        public static extern void LED_LITS_CLOSE();

        /// <summary>
        /// 初始化设备
        /// </summary>
        /// <returns></returns>
        [DllImport("SpectraArsenalEmission.dll", EntryPoint = "LED_LITS_CONNECT")]
        public static extern int LED_LITS_CONNECT(int devnum);

        /// <summary>
        /// 获取设备信息
        /// </summary>
        /// <param name="serialnum">序列号</param>
        /// <param name="pixelnum">像素点</param>
        /// <returns></returns>
        [DllImport("SpectraArsenalEmission.dll", EntryPoint = "LED_LITS_GetDevInfo")]
        public static extern int LED_LITS_GetDevInfo(byte[] serialnum, ref int pixelnum);
        #endregion

        #region 单光谱仪控制
        /// <summary>
        /// 获取暗电流数据
        /// </summary>
        /// <param name="spar"></param>
        /// <param name="fAdValue"></param>
        /// <param name="ADlen"></param>
        /// <returns></returns>
        [DllImport("SpectraArsenalEmission.dll", EntryPoint = "LED_LITS_GetDarkData")]
        public static extern int LED_LITS_GetDarkData(SpectralPar spar, double[] fAdValue, int ADlen);

        /// <summary>
        /// 获取单CIE数据
        /// </summary>
        /// <param name="spar"></param>
        /// <param name="fDx"></param>
        /// <param name="fDy"></param>
        /// <param name="dPara"></param>
        /// <returns></returns>
        [DllImport("SpectraArsenalEmission.dll", EntryPoint = "LED_LITS_GetData")]
        public static extern int LED_LITS_GetData(SpectralPar spar, float[] dkdata, int dklen, float fDx, float fDy, ref COLOR_PARA dPara);

        /// <summary>
        /// 获取原始值
        /// </summary>
        /// <param name="spar">采集参数</param>
        /// <param name="dkdata"></param>
        /// <param name="dklen"></param>
        /// <param name="advalue"></param>
        /// <param name="len"></param>
        /// <returns></returns>
        [DllImport("SpectraArsenalEmission.dll", EntryPoint = "LED_LITS_GetOriginalData")]
        public static extern int LED_LITS_GetOriginalData(SpectralPar spar, float[] dkdata, int dklen, 
            double[] advalue, int len, ref double IP);

        /// <summary>
        /// 定标
        /// </summary>
        /// <param name="spar"></param>
        /// <param name="dkdata"></param>
        /// <param name="dklen"></param>
        /// <param name="iCalType">iCalType: 0使用色温法计算定标 1使用导入的绝对光谱定标</param>
        /// <param name="fCCT">色温，iCalType = 0时使用</param>
        /// <param name="fFlux">光通量，iCalType = 0时使用</param>
        /// <param name="iStaNum">数据个数，iCalType = 1时使用</param>
        /// <param name="fStaWL">波长值，iCalType = 1时使用</param>
        /// <param name="fStaPL">光度值，iCalType = 1时使用</param>
        /// <param name="ref fIp">最大值</param>
        /// <returns></returns>
        [DllImport("SpectraArsenalEmission.dll", EntryPoint = "LED_LITS_Calib")]
        public static extern int LED_LITS_Calib(SpectralPar spar, float[] dkdata, int dklen,
                                                int iCalType,   //定标类型
                                                float fCCT,     //
                                                float fFlux,    //
                                                int iStaNum,    //点个数
                                                float[] fStaWL, //波长
                                                float[] fStaPL, //光度值
                                                ref float fIp);
        #endregion

        #region LED三晶测试接口
        /// <summary>
        /// 设置三晶的积分时间
        /// </summary>
        /// <param name="time1"></param>
        /// <param name="time2"></param>
        /// <param name="time3"></param>
        /// <returns></returns>
        [DllImport("SpectraArsenalEmission.dll", EntryPoint = "LED_LITS_SetSPPar")]
        public static extern int LED_LITS_SetSPPar(float time1, float time2, float time3, int avr);

        /// <summary>
        /// 获取三晶的积分时间
        /// </summary>
        /// <param name="time1"></param>
        /// <param name="time2"></param>
        /// <param name="time3"></param>
        /// <returns></returns>
        [DllImport("SpectraArsenalEmission.dll", EntryPoint = "LED_LITS_GetSPPar")]
        public static extern int LED_LITS_GetSPPar(ref float time1, ref float time2, ref float time3);


        /// <summary>
        /// 设置LED类型
        /// </summary>
        /// <param name="epar"></param>
        /// <param name="ledmode"></param>
        /// <returns></returns>
        [DllImport("SpectraArsenalEmission.dll", EntryPoint = "LED_LITS_SetLEDType")]
        public static extern int LED_LITS_SetLEDType(int ledtype);

        /// <summary>
        /// 设置电参数测试条件
        /// </summary>
        /// <param name="epar"></param>
        /// <param name="ledmode"></param>
        /// <returns></returns>
        [DllImport("SpectraArsenalEmission.dll", EntryPoint = "LED_LITS_SetElectricPar")]
        public static extern int LED_LITS_SetElectricPar(SElectricPar epar, int ledmode);

        /// <summary>
        /// 获取电参数测试条件
        /// </summary>
        /// <param name="epar"></param>
        /// <param name="ledmode"></param>
        /// <returns></returns>
        [DllImport("SpectraArsenalEmission.dll", EntryPoint = "LED_LITS_GetElectricPar")]
        public static extern int LED_LITS_GetElectricPar(ref SElectricPar epar, ref int ledmode);

        /// <summary>
        /// 下发bin号
        /// </summary>
        /// <param name="bin"></param>
        /// <returns></returns>
        [DllImport("SpectraArsenalEmission.dll", EntryPoint = "LED_LITS_SetBin")]
        public static extern int LED_LITS_SetBin(int bin);

        /// <summary>
        /// 获取光电参数
        /// </summary>
        /// <param name="spar"></param>
        /// <param name="dkdata"></param>
        /// <param name="dklen"></param>
        /// <param name="fDx"></param>
        /// <param name="fDy"></param>
        /// <param name="dPara"></param>
        /// <param name="ePara"></param>
        /// <param name="ledmode"></param>
        /// <param name="timeout"></param>
        /// <returns></returns>
        [DllImport("SpectraArsenalEmission.dll", EntryPoint = "LED_LITS_GetLEDData")]
        public static extern int LED_LITS_GetLEDData(
            SpectralPar spar1, SpectralPar spar2, SpectralPar spar3,
            float[] dkdata1, float[] dkdata2, float[] dkdata3,
            int dklen, float[] fDx, float[] fDy,
            ref COLOR_PARA dPara1, ref COLOR_PARA dPara2, ref COLOR_PARA dPara3,
            ref ElectricData ePara1, ref ElectricData ePara2, ref ElectricData ePara3, int ledmode, int timeout);

        /// <summary>
        /// 获取三晶原始数据
        /// </summary>
        /// <param name="TriggerMode"></param>
        /// <param name="iFilterBW"></param>
        /// <param name="dkdata1"></param>
        /// <param name="dkdata2"></param>
        /// <param name="dkdata3"></param>
        /// <param name="dklen"></param>
        /// <param name="advalue1"></param>
        /// <param name="advalue2"></param>
        /// <param name="advalue3"></param>
        /// <param name="advaluelen"></param>
        /// <param name="ePara1"></param>
        /// <param name="ePara2"></param>
        /// <param name="ePara3"></param>
        /// <param name="ledmode"></param>
        /// <param name="timeout"></param>
        /// <returns></returns>
        [DllImport("SpectraArsenalEmission.dll", EntryPoint = "LED_LITS_GetLEDOriginalData")]
        public static extern int LED_LITS_GetLEDOriginalData(
            TRIGGER_MODE TriggerMode, int iFilterBW,
            float[] dkdata1, float[] dkdata2, float[] dkdata3, int dklen,
            double[] advalue1, double[] advalue2, double[] advalue3, int advaluelen, 
            ref ElectricData ePara1, ref ElectricData ePara2, ref ElectricData ePara3, int ledmode, int timeout);
        #endregion
    }
}
