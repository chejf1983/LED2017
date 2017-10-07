// CSPEC_PRO.h: interface for the CCSPEC_PRO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSPEC_PRO_H__1E045AE1_E177_11D9_ABAD_00055D02EEF1__INCLUDED_)
#define AFX_CSPEC_PRO_H__1E045AE1_E177_11D9_ABAD_00055D02EEF1__INCLUDED_

#include "SpectData.h"

#include "Serial.h"

#include "SPEC_HAAS.h"
#include "FluxLampSelfCalData.h"

//加了可以
//#pragma comment(linker,"/opt:noref")

/////////////////////////////////////////////////
//光谱仪类型
#define     NH_GCS_V1_USB    "NH_GCS300_V100"

/////////////////////////////////////////////////
#define MY_TRIG_NORMAL         0  //正常模式
#define MY_TRIG_HARD_IN        1  //手动触发1
#define MY_TRIG_HARD_OUT       2  //手动触发2
#define MY_TRIG_HARD_OUT2      3  //手动触发3
/////////////////////////////////////////////////

#define WL_UV_SET   360.0f   //UV定标光谱分界波长
/////////////////////////////////////////////////

#define STA_A    0
#define STA_D65  1
/////////////////////////////////////////////////

#include "SelfCorrectData.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCSPEC_PRO  
{
public:
	//读取镜面反射系数
	BOOL  ReadJMFK(CString strPathName);
	BOOL  m_bMoveJM;
	float m_fJMFK;

	//处理光谱的奇异点
	BOOL HassDarkPro(float *pDark, int iCCDNum, float fAD_Range, int iContiNum, int &iErrorNum, float *pProDark);
	int m_iModBadP2;
	int m_iModBadP2_AD;
	int m_iModBadP2_Num;
	int m_iModBadP2_Time;

	float m_fReGeWL1; //重新计算光量子数波段范围
	float m_fReGeWL2;

	int m_iNum_KAC;
	float m_fWL_AC[1000];
	float m_fK_AC[1000];
	BOOL WD_ReadACData(CString strPathName);
	float m_wd_fMod;
	BOOL WD_GetCalData(CString strPathName);
	BOOL WD_SaveCalData(CString strPathName);
	BOOL MOD_SPEC_WL1(CString sPathName);

	int m_iSigType;
	int m_iSR2AngleType;

	int m_iSetPassword1;
	int m_iSetPassword2;

	BOOL m_bHaveLEDTMPCtrl;
	float m_fSetLEDTMP;
	CString m_strLEDTMPCom;

	CSelfCorrectData m_selfCorrectData;

	BOOL CorrectXY(CSpectData &spData);
	BOOL NEW_CorrectXY(CSpectData &spData);

	BOOL m_bUseColorCorrect;

	BOOL m_bUseListCalSele;
	int m_iTestListCalSele;

	BOOL CreateDirectoryMy(CString strPath);
	int m_iDateType;
	BOOL m_bNotUseColorDark;
	BOOL GetYFStaLamp(CString strPathName, int iEorFlux);
	float m_fStaVol,m_fStaCurr,m_fStaDis;

	int   m_iBadNum;
	int   m_iBadPoint[3648];
	int   m_iBadTime;
	BOOL  FILE_GetBadPoint(CString sPathName);

	void SPEC_CalcPhoEff(int iN,float fWL[], float fRelP[], float fPower, BOOL bAuto,
						float fSpectB1,float fSpectB2,float fSpectY1,float fSpectY2,
						float & fMol, float &fEff1, float &fEff2);
	int m_iCroWLType; //波长校正方法 0 三项拟合 1 分段差值
	//光源的谱线数据,WL.dat
	CArray<float,float> m_C2_fPix;
	CArray<float,float> m_C2_fStaWL;
	BOOL WL2_Load(CString strPathName);

	//
	BOOL ReadTrigSet(CString strPathName);
	/////////////////////////////////////////////////
	//定时测试
	BOOL m_bTimeTest;
	BOOL GetTimeTestData(CString strPathName);
	BOOL SaveTimeTestData(CString strPathName);
	CArray<int,int> m_arra_iTimeNum;
	/////////////////////////////////////////////////

	BOOL ReadData(CString strPathName);

	BOOL m_bCro;


	void ReadInitData();
	void SaveInitData();

	void ReadWaveData();
	void SaveWaveData();

	void  DoProAvg(double fData[], int iN, int iDoN);
	float CIE_DEuv(float x1,float y1,float x2,float y2,float x0,float y0);
	void  CIE_xLuv(float x,float y,float x0,float y0,float &xL,float &xu,float &xv,float &xSuv,float &xCuv,float &xHuv);
	float CIE_CalcW(float x,float y,float x0,float y0);
	float CIE_CalcYI(float x, float y);

	BOOL  ReadRouData(CString strPathName);
	int   m_iRrouNum;
	float m_fRrou_WL[10001];
	float m_fRrou_PL[10001];

	BOOL  ReadRouDark(CString strPathName);
	int   m_iRDarkNum;
	float m_fRDark_WL[10001];
	float m_fRDark_PL[10001];

	BOOL  GetTouData(CString strPathName);
	float m_f_Ttou_R;//透射率标准数据

	double m_fD65_WL[10001];
	double m_fD65_PL[10001];
	float  m_fA_Tc;
	int    m_iStaLampN;
	CString m_strLampName;

	BOOL GetStaLamp(CString strPathName);
	int  REF_TYPE;
	////////////////////////////////////////////////////////////////////
	int  m_iTestTRorTT;
	BOOL Get_TROrTT();
	//反射率定标数据
	CString m_strDateK_TR;
	float	m_fIntTime_TR;
	float   m_fSpect1_TR;
	float   m_fSpect2_TR;
	float   m_fK_TRAD[10001];    //cal k
	float   m_fK_TRou[10001];    //cal k

	BOOL TR_Save(CString strPathName);
	BOOL TR_Load(CString strPathName);

	CString m_strDateK_TR_Dark;
	float	m_fIntTime_TR_Dark;
	float   m_fSpect1_TR_Dark;
	float   m_fSpect2_TR_Dark;
	float   m_fK_TR_DarkAD[10001];    //cal k
	float   m_fK_TRou_Dark[10001];    //cal k

	BOOL TR_Dark_Save(CString strPathName);
	BOOL TR_Dark_Load(CString strPathName);

	//透射率定标数据
	CString m_strDateK_TT;
	float	m_fIntTime_TT;
	float   m_fSpect1_TT;
	float   m_fSpect2_TT;
	float   m_fK_TT[10001];    //cal k

	BOOL TT_Save(CString strPathName);
	BOOL TT_Load(CString strPathName);
	////////////////////////////////////////////////////////////////////
	//高低灵敏度数据互用
	float m_fSpkTime1;
	float m_fSpkTime2;
	float m_fRelN[10001];//高的数据
	float m_fRelR[10001];//低的数据
	BOOL Read_SP_K();
	double Lagrange_New(double x[], double y[], int n, float t);

	float   m_fIntTimeDark;//积分时间的暗电流
	// 亮度测试视场角度
	int     m_iViewL_Num;
	CString m_strViewL_Name[100];

	BOOL ViewL_Save(CString strPathName);
	BOOL ViewL_Load(CString strPathName);

	int    m_iSeleL;  // 亮度视场角选择

	////////////////////////////////////////////////////////////////
	int    m_iWLInter;       //色片波长分界点的个数
	float  m_fWLInter[10];   //波长分界点

	int    m_iHave_Color_K;		//快速测试的色片个数
	int    m_iWZ_Color_K[10];	//快速测试的色片位置
	int    m_iHave_Color_J;		//精确测试的色片个数
	int    m_iWZ_Color_J[10];	//精确测试的色片位置
	BOOL   WL_Inter_Get(CString strPathName);
	////////////////////////////////////////////////////////////////

	BOOL m_bPhoto;    //光度是否使用PHOTO-2000M

	//
	void ReMoveJF_Spec(float fInPL[],float fSpect1,float fInterval, int iInN);//去掉激发光谱
	///////////////荧光粉数据
	BOOL PHO_SaveCal(CString sPathName);
	BOOL PHO_OpenCal(CString sPathName);
	static CString sFormat(float fD, int iN);  //小数位数处理
	//拷贝文件
	BOOL CopyFile(const char *lpSrcFilename, const char *lpDestFilename, int nBuffersize = 50000);
	float MA_Ave(int iAveN,int iCurN,int iMaxN,float fData[]);  //平滑处理
	//////////////////////////////////////////////////////////////////
	HWND m_hWnd;
	int  m_iParType;    //典型测试的已定标数据个数
	BOOL m_bCal;        //是否定标界面
	BOOL m_bSingleWeak; //信号太弱
	BOOL m_bOverAD;     //信号溢出
	BOOL m_bAtt;        //是否使用衰减片
	int	 m_iAtt;        //强或者弱衰减片
	int  m_iLamp;       //光源类型选择  电光源 荧光粉
	int  m_iPE;			//荧光粉装置台

	//测试的波长范围
	float  m_fTestWL1;
	float  m_fTestWL2;

	BOOL   m_bTrig;
	int    m_iTrigMode;
	float  m_fPulseTime;//信号激发时间
	int    m_iPulseNum; //触发周期内信号个数

	BOOL Get_PL();
	void SPEC_Setting();
	BOOL FILE_GetTMPK(CString sPath);
	//////////////////////////////////////////////////////////////////
	////温度计算
	float m_fR1;
	float m_fR2;
	float m_fR3;
	int   m_iRAD1;
	int   m_iRAD2;
	int   m_iRAD3;

	BOOL m_bHaveCool;  //是否已经开制冷
	BOOL SPEC_Cool(BOOL bOn);
	BOOL SPEC_GetTMP(int iType,int iAveN,float &fTMP,int &iTMPAD);
	//////////////////////////////////////////////////////////////////
	/////光度定标
	BOOL FLUX_GetRangeK(CString sPathName);
	BOOL FLUX_SaveRangeK(CString sPathName);
	BOOL FLUX_GetCalK(CString sPathName);
	BOOL FLUX_SaveCalK(CString sPathName);
	BOOL GetDetectorK(CString sPath);
	BOOL GetPheK(CString sPath);
	BOOL GetPheK_High(CString sPath);

	CArray<float,float> m_arra_fDetctorK;
	CArray<float,float> m_arra_fDetctorWL;
	float  m_fDectorK;
	double m_fDecWL[2001];
	double m_fDecK[2001];

	CArray<float,float> m_arra_fPheWL;
	CArray<float,float> m_arra_fPheAD[100];
	CArray<float,float> m_arra_fPheK[100];

	CArray<float,float> m_arra_fPheAD_High;
	CArray<float,float> m_arra_fPheK_High;

	//////////////////////////////////////////////////////////////////
	int m_iBin;		  //采样模式选择 BIN 10  BIN FULL
	int m_iMode;	  //色度测量类型模式 快速 精确

	float m_fModeFluxK; //光通量修正系数
	float m_fModeSelfK; //自吸收修正系数

	BOOL SPEC_FluxAD(int iRange, float &fAD);    //固定量程 得到光通量AD值
	BOOL SPEC_FluxAuto(float &fAD,float &fFlux); //自动量程 计算得到光通量

	////////////////////////////////////////////////////////////////////////////////////
	//////高斯算法求波长校正系数
	static BOOL Gauss_EQU(double fk[], double fz[], int iN,double a[]);
	static BOOL Gauss2XF_Calc(double fx[], double fy[], int iN, int iMN, double a[]);
	static float MAX_F(float fD);  //进位

	float SPEC_Pix2WL(int iPix);
	////////////////////////////////////////
	////暗电流
	BOOL DARK_Save();
	BOOL DARK_Open();

	////////////////////////////////////////
	BOOL STAWL_Load(CString strPathName);

	BOOL Set_Save(CString strPathName);
	BOOL Set_Load(CString strPathName);

	////////////////////////////////////////
	////参数设置情况set.dat
	CString	m_strDriver;
	CString	m_strEprom;
	CString	m_strSoftVer;

	CString m_strSN;        //序列号
	int  m_iAutoLimitTime2; //自动积分上限
	int  m_iTestType;       //0:无  1:光通量  2:光照度
	float m_fDistance;      //光强测试距离
	float m_fIntK;          //光强修正系数

	float m_fIntTime1;      //积分时间的上下限
	float m_fIntTime2;

	int   m_iDark;

	float T_SPECT1;
	float T_SPECT2;
	float m_fOverK;
	float m_fWLK;
	int   m_Have_iBin;
	int   m_CCD_iMode;
	int   m_HAAS_iVer;  //HAAS-2000版本
	int   m_iBaudRate;
	////////////////////////////////////////////

	////////////////////////////////////////////
	////得到峰值半宽度
	int GetWL12peakPos(float fWL[],float fP[],int iN,float fWL1,float fWL2,float &fBW, float fHalf = 0.3f);

	CSPEC_HAAS  m_HAAS;

	////////////////////////////////////////////
	//蜂鸣器
	static void MyBeep(int iT);
	//仪器类型
	CString m_strSTCCom;   //如果对有些光谱仪要使用RS232
	CString m_strSTCType;  //仪器类型
	CString m_strSTC_ShowName;

	//采样
	BOOL SPEC_DoScan(float fIntTime,int iAveN, int nTriggerMode,float &fMax,BOOL bZero,int iType,BOOL bNote=TRUE);
	BOOL SPEC_UnInit();
	BOOL SPEC_Sample(float fIntTime, int iAveNum, int iTrigType,BOOL &bOverAD,BOOL bNote=TRUE);
	BOOL SPEC_Init();

	//计算数据
	void SPEC_GetSpectData(BOOL bK,CSpectData &spData,BOOL bDark=TRUE);
	//采样暗电流
	BOOL SPEC_GetDark(float fTime,int iAveN);
	//校正用
	BOOL SPEC_Correct();
	//自动积分时间
	BOOL SPEC_GetAutoTime(float &fIntTime,int iLimitTime,float fL1=0.6f,float fTimeB=0);
	//溢出
	BOOL SPEC_OVER(float fMax);
	//
	void Func2(double *x,double *y,double a[2][2],double b[2]);
	void Func3(double *x,double *y,double *z,double a[3][3],double b[3]);
	void Func4(double *x,double *y,double *m,double *n,double a[4][4],double b[4]);

	//波长数据
	double m_fLambdaPos[4096];
    int    m_iLambdaPos[4096];

	//波长校正文件
	BOOL WL_Save(CString strPathName);
	BOOL WL_Load(CString strPathName);
	BOOL WL_DataSave(CString strPathName);
	//光谱定标文件
	BOOL SP_Load(CString strPathName);
	BOOL SP_Save(CString strPathName);
	//紫外光谱定标文件
	BOOL SP_Load_UV(CString strPathName);
	BOOL SP_Save_UV(CString strPathName);

	//最大和极值
	float Max(float f[],int iN,int &iMax);
	void Maxmium(float fData[], int iN,int iMaxmium[], int &iHave, int iJu,float fMax);

	//采样来的数据
	int     m_nADW;
	int     m_iPixN;
	float   m_fIntTime;
	float   m_fIp;
	float   m_fAD[4096];      //AD value
	//暗电流
	float   m_fDarkAD[4096];

	CString m_strSerial;
	//波长校正数据
	double m_Icor,m_C1cor,m_C2cor,m_C3cor;//

	//测试波长间隔 0.1nm
	float   m_fInterval;
	//光谱定标数据
	CString m_SP_strDate;
	float   m_SP_fStaTc;
	float   m_SP_fIntTime; //定标时的积分时间
	float   m_SP_fSpect1;
	float   m_SP_fSpect2;
	float   m_SP_fK[10001];    //cal k

	//紫外光谱定标数据
	CString m_SP_strDate_UV;
	float   m_SP_fIntTime_UV; //定标时的积分时间
	float   m_SP_fSpect1_UV;
	float   m_SP_fSpect2_UV;
	float   m_SP_fK_UV[2001]; //cal k

	//光通量定标数据
	float  m_fZero[4];
	float  m_fRangeK[3];
	float  m_correctAD;
	float  m_correctK;

	float  m_CAL_fStaFlux[3];  //光通量定标值
	float  m_CAL_fIntTime[3];  //定标时积分时间(改为浮点数)
	float  m_CAL_fFluxK[3];    //光通量定标系数
	int    m_CAL_iRange[3];    //探头定标的档位

	float  m_CAL_fStaPho[3];   //光通量定标值 高 中 低
	float  m_CAL_fPhoTime[3];  //定标时积分时间(改为浮点数)
	float  m_CAL_fPhoK[3];     //光通量定标系数

	float m_FLT_K1[3][2048];
	float m_FLT_K2[3][2048];

	//光源的谱线数据,WL.dat
	CArray<CString,CString> m_arra_strSource;
	CArray<float,float>     m_arra_fStaWL;

	CFluxLampSelfCalData m_fluxLampSelfCalData;

	CCSPEC_PRO();
	virtual ~CCSPEC_PRO();
};

#endif // !defined(AFX_CSPEC_PRO_H__1E045AE1_E177_11D9_ABAD_00055D02EEF1__INCLUDED_)
