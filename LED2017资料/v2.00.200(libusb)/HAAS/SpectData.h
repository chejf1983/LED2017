// SpectData.h: interface for the CSpectData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPECTDATA_H__22B91A82_DE70_11D9_ABAD_00055D02EEF1__INCLUDED_)
#define AFX_SPECTDATA_H__22B91A82_DE70_11D9_ABAD_00055D02EEF1__INCLUDED_

#include <afxtempl.h>
#include "ImageObject.h"
#include "WhiteZone.h"
#include "SelfCorrectData.h"

//光谱仪计算波长

//过小AD百分比
#define   T_L         0.3f    //AD1/AD

//测试数据类型
#define  TYPE_SCAN    0
#define  TYPE_CAL     1
#define  TYPE_CHECK   2

#define  PH_NONE     -1
#define  PH_F         0  //lm
#define  PH_I         1  //cd
#define  PH_L         2  //cd/m2
#define  PH_Fe        3  //W
#define  PH_Ie        4  //W/Sr
#define  PH_Le        5  //W/m2/Sr
#define  PH_E         6  //lx
#define  PH_Ee        7  //W/m2

#define  PARA_None   -1
#define  PARA_Ip      0
#define  PARA_PH      1
#define  PARA_x       2
#define  PARA_y       3
#define  PARA_u       4
#define  PARA_v       5
#define  PARA_Tc      6
#define  PARA_Ld      7
#define  PARA_Pur     8
#define  PARA_Lp      9
#define  PARA_HW      10
#define  PARA_RR      11
#define  PARA_Ra      12
#define  PARA_VF      13
#define  PARA_IF      14
#define  PARA_P       15
#define  PARA_VR      16
#define  PARA_IR      17
#define  PARA_EFF     18   //光效

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct tag_data_draw
{
	BOOL bShowCur;
	int  iDrawType;
	int  iCurSele;
	BOOL bMouse;
	CPoint pt;

	int iB;
	int iE;

	float fSetWL1;
	float fSetWL2;

	int   iChekStaN;          //check or correct
	float fCheckStaWL[100];

	int   iHave;
	int   iMaxmium[1000];
} DATA_DRAW;

class CSpectData : public CObject  
{
public:
	BOOL DoSpectrumSelfCorrect(CSelfCorrectData &data);
	static float m_fSetDoWL;
	static float m_fSetDoLimitAD;

	void DoADSpecForCal(float fLimitWL, float fSetAD);
	static BOOL m_bPrintPh_;

	BOOL CalcPh_(float &fPh_, float &fSP);
	static BOOL ReadV2(CString strPathName);
	void ProGetWL12(float fWL1, float fWL2);
	BOOL GetDW(float fPosWL,  float &fDW);
	float GetSDCM(int iSeleK);
	BOOL CalcPhoEff(float &fMol, float &fEff1, float &fEff2, int iPhType);
	float GetEe(int iB1,int iB2);
	void Demo();
	void DoPh_e(int iPhType);

	static CString DATA_Name(int iPara,int iPhType);
	static CString PH_Name(int iLamp,int iPhType,BOOL bAddCH=FALSE);
	static CString PH_Name(int iLamp,int iPhType,CString &strUnit,BOOL bAddCH=FALSE);
	///////////////
	//正向参数
	BOOL  m_bTestF;
	float m_fVF;  //V
	float m_fIF;  //A
	float m_fPow; //W
	float m_fPF;

	//光度
	int   m_iLamp;      //光源类型 电光源 荧光粉
	int   m_iTestType;  //类型 光通量 光照度等
	BOOL  m_bTestPH;
	float m_fDistance;  //测试距离 对光强与辐射强度有用
	float m_fPH;
	///////////////

	float m_fE_SP1,m_fE_SP2;
	float GetWL12_Ee(float fSP1, float fSP2, float fE);
	//
	//保存
	BOOL SP_Save(CString strPathName);
	//导出相对光谱数据Excel格式
	BOOL Export_CSV(CString strPathName,float fIntervalWL);

	void WR_Info();
	void RD_Info();
	void Init();
	CSpectData& operator =(const CSpectData &spData);
	void Copy(const CSpectData &spData);
	/////////////////////////////////////////////////////////
	//色容差
	void ColorErr(CDC *pControlDC, BOOL bHave,CRect mRect, float x, float y, int iSeleK,int iSDCM1,int iSDCM2);
	//CIE图
	void DrawCIE(CDC *pDC,CRect mRect);
	void DrawCIE_UV(CDC *pDC,CRect mRect);
	//画数据
	void DrawData(CDC *pDC ,CRect mRect);
	//光谱曲线
	void DrawSpect(CDC *pDC,CRect mRect,DATA_DRAW &drawData,CString strNote,BOOL bPrint,BOOL bShow, int iPhType);
	void DrawSpectBW(CDC *pDC,CRect mRect,DATA_DRAW &drawData,CString strNote,BOOL bPrint,BOOL bShow);
	//反射率透射率曲线
	//打印报告
	void printFoot(CDC *pDC,  CRect printRect,int iCur,int iMax);
	void printHead(CDC *pDC, CRect printRect,int iCur,int iMax,BOOL bPrintLogo,int iPrintLogoPos,BOOL bPrintPage);
	void printReport(CDC *pDC, CRect printRect,int iTypeP,int iSeleK,int iSDCM1,int iSDCM2,int iPhType,CWhiteZone &xyZone,CString strLevel,CString strWhite);
	void printReport_2(CDC *pDC, CRect printRect,int iTypeP,int iSeleK,int iSDCM1,int iSDCM2,int iPhType,CWhiteZone &xyZone,CString strLevel,CString strWhite,BOOL bPrintLogo,int iPrintLogoPos);

	void printCIE(CDC *pDC, CRect mRect, float x, float y, float fTc);
	void printCIE_UV(CDC *pDC, CRect mRect, float u, float v, float fTc);
	void printColorErr(CDC *pControlDC, CRect mRect, float x, float y,int iSeleK,int iSDCM1,int iSDCM2);
	/////////////////////////////////////////////////////////
	//找最大值
	float Max(CArray<float,float> &f,int& iMax);
	//保存
	void Serialize(CArchive& ar);

	//是否有光谱数据
	BOOL  m_bHaveData;
	int   m_iCoolState;  //制冷状态

	//要注意这个新增加的变量，
	BOOL  m_bHaveColorPara;  //对于红外光谱，没有色，只有谱(有Lp,HW,Ph_e)

	////注意：保存的是测量的类型
	CString m_strName;
	float m_fPulseTime;

	CString m_strSN; //测试仪器编号

	int   m_iDataType;                //数据类型
	float m_fIntTime;                 //积分时间
	float m_fInterval;                //间隔波长
	float m_fSpect1,m_fSpect2;        //波长范围
	CArray<float,float> m_fRelSpect;  //相对光谱

	int   m_nADW;       //满AD
	float m_fIp;        //最大AD

	float m_x,m_y;
	float m_u,m_v;
	float m_fCCT;
	float m_fdc;
	float m_fRedRatio;
	float m_fGreenRatio;
	float m_fBlueRatio;
	float m_fMainlambda;
    float m_fMaxlambda;
	float m_fPurity;
	float m_fHalflambda;
	float m_fRa;
	float m_fRi[15];

	//使用光谱法测试的光度与辐射度参数
	float m_fPh;
	float m_fPh_e;
	float m_fPlambda;
	CString m_strAngleView; // 亮度视场角

	float m_fKuv;
	float m_fK1;
	float m_fK2;

	float m_fEnTMP;

	//测试信息
	CString	m_strModel;
	CString	m_strNumber;
	CString	m_strFactory;
	CString	m_strT;
	CString	m_strH;
	CString	m_strTester;
	CString	m_strDate;
	CString	m_strRemark;

	CString	m_strSampleName;
	CString	m_strSampleStandard;
	CString	m_strSampleState;

	CString m_strFilter;

	CString m_strCompany;
	CString m_strAddr;


	CString m_strColorCorrectStr;

	CSpectData();
	virtual ~CSpectData();

protected:

	static int   m_iv2Num;
	static float m_fv2WL[421];
	static float m_fv2VL[421];
};

#endif // !defined(AFX_SPECTDATA_H__22B91A82_DE70_11D9_ABAD_00055D02EEF1__INCLUDED_)
