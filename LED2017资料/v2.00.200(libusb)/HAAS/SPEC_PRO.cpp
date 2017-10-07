// CSPEC_PRO.cpp: implementation of the CCSPEC_PRO class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "SPEC_PRO.h"
#include "ProcessData.h"
#include "math.h"

#include "Global_MySpec.h"
#include "sheetothers.h"
#include "mysheet.h"
#include "ExGetColorParaDLL.h"
#include "setup1.h"
#include "setup2.h"
#include "setup3.h"
#include "setup4.h"

#include "MainFrm.h"
//杂散光修正的函数
#include "MySpecView.h"

#include "SpectraArsenal.h"

#include "logfile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int g_iMax;
extern float g_fModSpect1;
extern BOOL g_bModeWL1;
//通讯模式选择

BOOL    g_bHaveTRZero;
BOOL    g_bStrong;

extern BOOL g_bOpenMulitCalSpectrum;

float   g_fSpect1;
float   g_fSpect2;

extern	int  g_iRange;	   //光度采样的档位
extern	int  g_iPerRange;  //光度采样的前一档位
extern  int  g_iSeleMode;
extern	BOOL g_bFunDebug;
extern  BOOL g_bUseHLK;

int		g_iOkTime;
int		g_iOkNum;
int		g_iFailTime;
int		g_iFailNum;

int g_iHaveTestNum; //已经测试了几次？
float g_fPerAD[3][2048]; //前面测试的3组AD值数据

extern int		g_iPerTime;
extern int		g_iSetType;
extern float	g_fSetVol;
extern float	g_fSetCurr;
extern int		g_iSetType2;
extern float	g_fSetVol2;
extern float	g_fSetCurr2;

extern g_bCorrectXY_mode1;
extern g_bCorrectXY_mode2;

CCSPEC_PRO::CCSPEC_PRO()
{
	g_iHaveTestNum = 0;
	m_iSigType			= 0;
	m_iSR2AngleType		= 0;

	m_iSetPassword1		= 2012;
	m_iSetPassword2		= 1015;

	m_bHaveLEDTMPCtrl	= FALSE;
	m_fSetLEDTMP		= 30.0f;
	m_strLEDTMPCom		= _T("COM5");

	m_bUseListCalSele   = FALSE;
	m_iTestListCalSele  = 0;

	m_iDateType = 1;
	g_bStrong			= FALSE;
	m_bHaveCool			= TRUE;
	m_iAutoLimitTime2	= 60000;
	g_bDemo				= FALSE;
	m_iTestType			= 1;
	m_iBin				= 1;

	g_bUseHLK		= FALSE;

	m_iTrigMode		= 0;
	m_fDectorK		= 1;
	m_fR1			= 1;
	m_fR2			= 1.2f;
	m_iRAD1			= 20000;
	m_iRAD2			= 40000;
	m_strSN			= "0612001";
	m_strSTCCom		= "COM1";
	m_iBaudRate		= 9600;

	g_iMax			= -1;
	m_nADW			= 65536;
	m_iPixN			= 2048;

	int i;
	for(i = 0; i < 10000; i++)
	{
		m_SP_fK[i]  = 1.0f;
	}

	for(i = 0; i < 4096; i++)
	{
		m_fDarkAD[i] = 0;
	}

	m_fOverK = 0.92f;
	m_fWLK   = 0.10f;

	T_SPECT1 = 380;
	T_SPECT2 = 780;
	m_iDark  = 0;

	m_fIntTime1 = 1;
	m_fIntTime2 = 60000;

	m_fInterval = 0.1f;
	m_iSeleL	= 0;

	m_iViewL_Num	    = 4;
	m_strViewL_Name[0]  = "0.1";
	m_strViewL_Name[1]  = "0.2";
	m_strViewL_Name[2]  = "1.0";
	m_strViewL_Name[3]  = "2.0";

	m_iTestTRorTT		= 0;
	m_fIntTime_TR		= 10;
	m_fSpect1_TR		= 380;
	m_fSpect2_TR		= 780;
	m_fIntTime_TR_Dark	= 10;
	m_fSpect1_TR_Dark	= 380;
	m_fSpect2_TR_Dark	= 780;
	m_fIntTime_TT		= 10;
	m_fSpect1_TT		= 380;
	m_fSpect2_TT		= 780;

	m_bNotUseColorDark  = FALSE;
	m_bUseColorCorrect  = FALSE;
}

CCSPEC_PRO::~CCSPEC_PRO()
{
}

void CCSPEC_PRO::SPEC_GetSpectData(BOOL bK,CSpectData &spData,BOOL bDark)
{
	//计算光谱数据或光电流数据
	int i;
	spData.m_bHaveData = TRUE;
	spData.m_fSpect1   = g_fSpect1;
	spData.m_fSpect2   = g_fSpect2;
	spData.m_fInterval = 0.1f;

	if(bK && g_bModeWL1)
	{
		if(g_fSpect1 <= T_SPECT1)
		{
			spData.m_fSpect1 = g_fModSpect1;
		}
	}

	double fData[10001];
	float  fRel[10001];
	m_fIp = (float)(m_fIp - m_fDarkAD[g_iMax]);
	//插值
	float fAD,fd;
	float fPixWL[4096];

	double fDataOld[2048];
	double fDataNew[2048];
	for(i = 0; i < m_iPixN; i++)
	{
		fPixWL[i]	= SPEC_Pix2WL(i);
		fAD			= m_fAD[i];
		fd			= m_fDarkAD[i];
		fData[i]	= (double)(fAD - fd);
		fDataOld[i] = fData[i];
		fDataNew[i] = fData[i];
	}

	int iNumPix = m_iPixN;
	SA_NonlinearCalibration(0,fDataOld,fDataNew,iNumPix);

	m_fIp = 0;
	for(i = 0; i < m_iPixN; i++)
	{
		fData[i] = fDataNew[i];
		m_fAD[i] = (float)(fData[i]);
		g_fPerAD[2][i] = m_fAD[i];
		if(fData[i]>m_fIp)
		{
			m_fIp = (float)(fData[i]);
		}
	}

	if (1)
	{
		if (g_iHaveTestNum > 2)
		{
			//利用前面三次测量的AD计算当前的AD
			//判断
			float fPosMax[3];
			int iPerMax[3];
			for (int m = 0; m < 3; m++)
			{
				iPerMax[m] = 0;
				for(i = 0; i < m_iPixN; i++)
				{
					if (fPosMax[m] < g_fPerAD[m][i])
					{
						fPosMax[m] = g_fPerAD[m][i];
						iPerMax[m] = i;
					}
				}
			}
			
			if (abs(iPerMax[0] - iPerMax[1]) < 10
				&& abs(iPerMax[0] - iPerMax[2]) < 10
				&& abs(iPerMax[2] - iPerMax[1]) < 10)
			{
				//峰值未变
				if (fabs(fPosMax[0] - fPosMax[1]) < 500
					&& fabs(fPosMax[0] - fPosMax[2]) < 500
					&& fabs(fPosMax[2] - fPosMax[1]) < 500)
				{
					//峰值AD变化小于500
					//当前数据的AD值=前面3组加当前组的平均值
					for(i = 0; i < m_iPixN; i++)
					{
						m_fAD[i] = (g_fPerAD[0][i] + g_fPerAD[1][i] + g_fPerAD[2][i])/3;
						fData[i] = m_fAD[i];
					}
				}
			}
		}
		
		for(i = 0; i < m_iPixN; i++)
		{
			//数组迁移
			g_fPerAD[0][i] = g_fPerAD[1][i];
			g_fPerAD[1][i] = g_fPerAD[2][i];
		}
		
		//保存
		FILE *fp;
		if((fp = fopen(g_strCurPath + "Per.ph","wt")) == 0)
		{
		}
		else
		{
			for(i = 0; i < m_iPixN; i++)
			{
				fprintf(fp,"%8.2f %8.2f %8.2f\r\n",g_fPerAD[0][i],g_fPerAD[1][i],g_fPerAD[2][i]);
			}
			fclose(fp);
		}

		g_iHaveTestNum++;
	}

	//取出测量波段内数据
	int iN = (int)((spData.m_fSpect2 - spData.m_fSpect1) / spData.m_fInterval + 1 + 0.5f);
	float fTemp;
	for(i = 0; i < iN; i++)
	{
		float fLamda = spData.m_fSpect1 + spData.m_fInterval * i;
		if(fLamda < T_SPECT1)
		{
			fTemp = 0;
		}
		else
		{
			fTemp = (float)g_doData.NewInt_double(m_fLambdaPos, fData, m_iPixN, fLamda);
		}

		//外插清零 如果外插的数据小于0直接清零
		if(fLamda<m_fLambdaPos[0] || fLamda > m_fLambdaPos[m_iPixN-1])
		{
			if(fLamda < m_fLambdaPos[0] && T_SPECT1 == 200.0f && T_SPECT2 == 1200.0f)
			{
				fTemp = (float)(fData[0]);
			}

			if(fTemp <= 0)
			{
				fTemp = 0;
			}
		}

		if(fLamda <= m_fLambdaPos[0])
			fTemp = (float)(fData[0]);
		if(fLamda >= m_fLambdaPos[m_iPixN - 1])
			fTemp = (float)(fData[m_iPixN - 1]);
		fRel[i] = fTemp;
	}

	float fMax = 1.000f;
	if(bK)  //相对光谱
	{
		float fLambda;
		float fK;//某点波长定标系数
		//实际测量的起始点  用可见定标系数计算
		int iBtest = (int)((spData.m_fSpect1 - m_SP_fSpect1) / spData.m_fInterval + 0.5f);

		if(iBtest <= 0)
		{
			if(spData.m_fSpect1 < T_SPECT1)
			{
				iBtest = iBtest - 1;
			}
		}

		if(T_SPECT1 < 300.0f)//紫外数据要用紫外定标系数
		{
			if(T_SPECT1 < 780.0f)//200-400用光辐射强度标准灯  分界点为360
			{
				int iUV_N = (int)((360 - m_SP_fSpect1) / spData.m_fInterval + 1 + 0.5f);
				// 紫外分界点系数 380
				float fUV_WL_SET_K = 1.0f;
				if(m_SP_fK_UV[iUV_N - 1] > 0)
				{
					fUV_WL_SET_K = (m_SP_fK[iUV_N - 1] / 1) / (m_SP_fK_UV[iUV_N - 1] / 1);
				}
				// 系数计算
				for(i = 0; i < iN; i++)//计算相对光谱
				{
					fLambda = spData.m_fSpect1+spData.m_fInterval*i;
					if(fLambda<360)
					{
						if(fLambda < T_SPECT1)
						{
							fK = 0;
						}
						else
						{
							fK = m_SP_fK_UV[i+iBtest]*fUV_WL_SET_K;
						}
					}
					else
					{
						fK = m_SP_fK[i + iBtest];
					}
					fRel[i]=fRel[i]*fK;
				}
			}
			else
			{
				int iUV_N = (int)((WL_UV_SET-m_SP_fSpect1)/spData.m_fInterval+1+0.5f);
				// 紫外分界点系数 380
				float fUV_WL_SET_K = 1.0f;
				if(m_SP_fK_UV[iUV_N-1]>0)
					fUV_WL_SET_K = (m_SP_fK[iUV_N-1]/1)/(m_SP_fK_UV[iUV_N-1]/1);
				// 系数计算
				for(i=0;i<iN;i++)//计算相对光谱
				{
					fLambda = spData.m_fSpect1+spData.m_fInterval*i;
					if(fLambda<WL_UV_SET)
						fK = m_SP_fK_UV[i+iBtest]*fUV_WL_SET_K;
					else
						fK = m_SP_fK[i+iBtest];
					fRel[i]=fRel[i]*fK;
				}
			}
		}
		else
		{
			// 系数计算
			for(i=0;i<iN;i++)//计算相对光谱
			{
				fLambda = spData.m_fSpect1+spData.m_fInterval*i;
				fK		= m_SP_fK[i+iBtest];
				fRel[i]	= fRel[i]*fK;
			}
		}

		fMax=fRel[0];

		for(i=0;i<iN;i++)
		{
			if(fRel[i]>fMax)
			{
				fMax=fRel[i];
			}
		}
		if(fMax<=0)
		{
			fMax=1;
		}
		for(i=0;i<iN;i++)
		{
			fRel[i]=fRel[i]/fMax;
			if(fRel[i]>1)
			{
				fRel[i]=1;
			}
		}

		//注意
		float fRel_N[401];
		int   iB= (int)((380.0f-spData.m_fSpect1)/spData.m_fInterval+0.5f);
		int   iE= (int)((780.0f-spData.m_fSpect1)/spData.m_fInterval+0.5f);
		int iCalInt = 1;
		int iCalNum = (int)(400.0f / iCalInt + 0.5f + 1);
		int   NN= (int)(iCalInt/spData.m_fInterval+0.5f);
		float f;
		for(i=0;i<iCalNum;i++)
		{
			if((iB+i*NN)<0)
			{
				fRel_N[i]=0;
			}
			else if((iB+i*NN)<=iE)
			{
				float fRelTemp = fRel[iB+i*NN];
				
				f=fRelTemp;//fRel[iB+i*NN];
				if(f>1)
					f=1;
				fRel_N[i]=f;
			}
			else
				fRel_N[i]=0;
		}
		//光度值
		if(spData.m_iTestType==0)
		{
		}
		else
		{
			float fPh=0;
			float fPh1=0;
			for(i=0;i<iCalNum;i++)
			{
				float fLamda = 380.0f + i * iCalInt;
				if (iCalInt == 5)
				{
					fPh = fPh + fRel_N[i] * fMax * NH_GetV(fLamda) * iCalInt;        //* fMax
				}
				else
				{
					fPh = fPh + fRel_N[i] * fMax * NH_GetV(fLamda) * iCalInt;        //* fMax
				}
			}

			fPh1=fPh*m_SP_fIntTime*m_CAL_fFluxK[0]/m_fIntTime;
			if(fPh1<=0)
				fPh1=0;
			spData.m_fPh=fPh1;


			float fPh_e=0;
			for(i=0;i<iN;i++)
				fPh_e=fPh_e+fRel[i]*fMax*spData.m_fInterval;  //* fMax
			fPh_e=fPh_e*m_CAL_fFluxK[0]*m_SP_fIntTime/m_fIntTime/683;
			if(fPh_e<=0)
				fPh_e=0;
			spData.m_fPh_e=fPh_e;
			spData.m_fPlambda=fMax*m_SP_fIntTime*m_CAL_fFluxK[0]/m_fIntTime/683*1000;
		}

		if(spData.m_fSpect2>=380.0f&&spData.m_fSpect1<=780.0f)
		{
			float fPL_N[4096];
			float fWL_N[4096];
			int   MM= (int)(iCalInt / spData.m_fInterval+0.5f);
			int iNum;
			iNum=(int)((spData.m_fSpect2-spData.m_fSpect1)/iCalInt + 0.5f + 1);
			for(i=0;i<iNum;i++)
			{
				fWL_N[i]=spData.m_fSpect1+i*iCalInt;
				float f=fRel[i*MM];
				if(f>1)
					f=1;
				fPL_N[i]=f;
			}

			g_doData.Process51(iNum,fWL_N, fPL_N, spData.m_x, spData.m_y, spData.m_u, spData.m_v,
				spData.m_fRedRatio, spData.m_fGreenRatio, spData.m_fBlueRatio, 
				spData.m_fMaxlambda, spData.m_fHalflambda, spData.m_fCCT,spData.m_fdc,
				spData.m_fRa,	    spData.m_fRi,        spData.m_fMainlambda, spData.m_fPurity);

			if(spData.m_fPurity>100)
				spData.m_fPurity=100;
			if(spData.m_fPurity<0)
				spData.m_fPurity=0;

			if(spData.m_fRa<=(-999))
				spData.m_fRa=-999;
			if(spData.m_fRa>=(999))
				spData.m_fRa=999;

			for(i=0;i<15;i++)
			{
				if(spData.m_fRi[i]<=(-999))
					spData.m_fRi[i]=-999;
				if(spData.m_fRi[i]>=(999))
					spData.m_fRi[i]=999;
			}
			if(spData.m_fRedRatio>100)
				spData.m_fRedRatio=100;
			if(spData.m_fRedRatio<0)
				spData.m_fRedRatio=0;
			
			//
			if((spData.m_x+spData.m_y)>1)
				spData.m_y=1-spData.m_x;
		}
	}
	//只有可见光LED，清红外数值
	if(m_bSingleWeak||spData.m_fSpect2<380.0f||spData.m_fSpect1>=780.0f)
		spData.m_bHaveColorPara=FALSE;
	else
		spData.m_bHaveColorPara=TRUE;

	//添加
	spData.m_fRelSpect.RemoveAll();
	for(i=0;i<iN;i++)
	{
		float fTemp;
		fTemp=fRel[i];
		if(fTemp<0)
		{
			fTemp=0;
		}
		spData.m_fRelSpect.Add(fTemp);
	}

	fMax=0.100f;
	int iMax=0;
	for(i=0;i<iN;i++)
	{
		if(spData.m_fRelSpect[i]>fMax)
		{
			iMax=i;
			fMax=spData.m_fRelSpect[i];
		}
	}
	spData.m_fMaxlambda	= iMax*spData.m_fInterval+spData.m_fSpect1;
	if(spData.m_fMaxlambda < T_SPECT2 - 10)
	{
		int iTempMax = iMax;
		//处理峰值波长问题 在峰值波长附件找点处理
		float fSum = 0;
		for(i = iMax - 200; i < iMax + 200; i++)
		{
			if(i >= 0 && i <= iN)
			{
				fSum = fSum + spData.m_fRelSpect[i];
			}
		}
		float fHalf = 0;
		for(i = iMax - 200; i < iMax + 200; i++)
		{
			if(i >= 0 && i <= iN)
			{
				fHalf = fHalf + spData.m_fRelSpect[i];
				if(fHalf >= fSum / 2)
				{
					iTempMax = i;
					break;
				}
			}
		}
		int iL = iMax;
		for(i = iMax - 200; i < iMax; i++)
		{
			if(spData.m_fRelSpect[i] / fMax >= 0.9f)
			{
				iL = i;
				break;
			}
		}

		int iR = iMax;
		for(i = iMax+200; i > iMax; i--)
		{
			if(spData.m_fRelSpect[i] / fMax >= 0.9f)
			{
				iR = i;
				break;
			}
		}
		iTempMax = (iL + iR) / 2;
		
		spData.m_fMaxlambda	= iTempMax * spData.m_fInterval+spData.m_fSpect1;

	}
//	NEW_CorrectXY(spData);

	spData.m_fIntTime	= m_fIntTime;
	spData.m_fIp		= m_fIp;
	spData.m_nADW		= m_nADW;

	spData.m_strSN = m_strSN;

	CTime tNow;
	tNow=CTime::GetCurrentTime();
	CString sNow;
	if(m_iDateType == 0)
		sNow=tNow.Format("%Y-%m-%d");
	else
		sNow=tNow.Format("%Y-%m-%d %H:%M:%S");
	spData.m_strDate=sNow;

	if(spData.m_fSpect1<300.0f)  //紫外参数计算
	{
		double fD1,fD2;
		int SP1,SP2;
		int B1,B2;
		float fTempInterval;

		fTempInterval=1.0f;

		// Calc UVC
		SP1=250;
		SP2=280;
		if(SP1>spData.m_fSpect2)
			SP1=(int)(spData.m_fSpect2);
		if(SP2>spData.m_fSpect2)
			SP2=(int)(spData.m_fSpect2);

		B1=(int)((SP1-spData.m_fSpect1)/fTempInterval+0.5f);
		B2=(int)((SP2-spData.m_fSpect1)/fTempInterval+0.5f);

		fD1=0;
		for(i=B1;i<=B2;i++)
		{
			float fSpect=spData.m_fSpect1+i*fTempInterval;
			float fSUV=g_doData.NewInt_float(g_doData.m_arra_fWAL,g_doData.m_arra_fSUV,g_doData.m_iSUV_N,fSpect);
			if(fSUV<0)
				fSUV=0;
			fD1=fD1+spData.m_fRelSpect[i*10]*fSUV*fTempInterval;
		}

		if(fD1<0)
			fD1=0;
		
		SP1=380;
		SP2=780;
		if(SP1>spData.m_fSpect2)
			SP1=(int)(spData.m_fSpect2);
		if(SP2>spData.m_fSpect2)
			SP2=(int)(spData.m_fSpect2);

		B1=(int)((SP1-spData.m_fSpect1)/fTempInterval+0.5f);
		B2=(int)((SP2-spData.m_fSpect1)/fTempInterval+0.5f);

		fD2=0;
		for(i=B1;i<=B2;i++)
		{
			float fSpect=spData.m_fSpect1+i*fTempInterval;
			fD2=fD2+683*spData.m_fRelSpect[i*10]* NH_GetV(fSpect) * fTempInterval;
		}
		if(fD2<0)
			fD2=0;

		fD2=1;
		if(fD2==0)
			spData.m_fKuv=0;
		else
			spData.m_fKuv=(float)(fD1/fD2)*spData.m_fPlambda;

		// Calc UVB
		SP1=280;
		SP2=315;
		if(SP1>spData.m_fSpect2)
			SP1=(int)(spData.m_fSpect2);
		if(SP2>spData.m_fSpect2)
			SP2=(int)(spData.m_fSpect2);

		B1=(int)((SP1-spData.m_fSpect1)/fTempInterval+0.5f);
		B2=(int)((SP2-spData.m_fSpect1)/fTempInterval+0.5f);

		fD1=0;
		for(i=B1;i<=B2;i++)
		{
			float fSpect=spData.m_fSpect1+i*fTempInterval;
			float fSUV=g_doData.NewInt_float(g_doData.m_arra_fWAL,g_doData.m_arra_fSUV,g_doData.m_iSUV_N,fSpect);
			if(fSUV<0)
				fSUV=0;
			fD1=fD1+spData.m_fRelSpect[i*10]*fSUV*fTempInterval;
		}

		if(fD1<0)
			fD1=0;

		SP1=380;
		SP2=780;
		if(SP1>spData.m_fSpect2)
			SP1=(int)(spData.m_fSpect2);
		if(SP2>spData.m_fSpect2)
			SP2=(int)(spData.m_fSpect2);

		B1=(int)((SP1-spData.m_fSpect1)/fTempInterval+0.5f);
		B2=(int)((SP2-spData.m_fSpect1)/fTempInterval+0.5f);

		fD2=0;
		for(i=B1;i<=B2;i++)
		{
			float fSpect=spData.m_fSpect1+i*fTempInterval;
		
			fD2=fD2+683*spData.m_fRelSpect[i*10]*NH_GetV(fSpect)*fTempInterval;
		}
		if(fD2<0)
			fD2=0;

		fD2=1;
		if(fD2==0)
			spData.m_fK1=0;
		else
			spData.m_fK1=(float)(fD1/fD2)*spData.m_fPlambda;

		// Calc K2
		SP1=315;
		SP2=400;
		if(SP1>spData.m_fSpect2)
			SP1=(int)(spData.m_fSpect2);
		if(SP2>spData.m_fSpect2)
			SP2=(int)(spData.m_fSpect2);

		B1=(int)((SP1-spData.m_fSpect1)/fTempInterval+0.5f);
		B2=(int)((SP2-spData.m_fSpect1)/fTempInterval+0.5f);

		fD1=0;
		for(i=B1;i<=B2;i++)
		{
			float fSpect=spData.m_fSpect1+i*fTempInterval;
			float fSUV=g_doData.NewInt_float(g_doData.m_arra_fWAL,g_doData.m_arra_fSUV,g_doData.m_iSUV_N,fSpect);
			if(fSUV<0)
				fSUV=0;
			fD1=fD1+spData.m_fRelSpect[i*10]*fSUV*fTempInterval;
		}

		if(fD1<0)
			fD1=0;

		SP1=380;
		SP2=780;
		if(SP1>spData.m_fSpect2)
			SP1=(int)(spData.m_fSpect2);
		if(SP2>spData.m_fSpect2)
			SP2=(int)(spData.m_fSpect2);

		B1=(int)((SP1-spData.m_fSpect1)/fTempInterval+0.5f);
		B2=(int)((SP2-spData.m_fSpect1)/fTempInterval+0.5f);

		fD2=0;
		for(i=B1;i<=B2;i++)
		{
			float fSpect=spData.m_fSpect1+i*fTempInterval;
			
			fD2=fD2+683*spData.m_fRelSpect[i*10]*NH_GetV(fSpect)*fTempInterval;
		}
		if(fD2<0)
			fD2=0;

		fD2=1;
		if(fD2==0)
			spData.m_fK2=0;
		else
			spData.m_fK2=(float)(fD1/fD2)*spData.m_fPlambda;
	}

	return;
}

BOOL CCSPEC_PRO::SP_Save(CString strPathName)
{
	int i,iN;
	//光谱定标数据
	FILE *fp;
	if((fp=fopen(strPathName,"wt"))==NULL)
		return FALSE;
	else
	{
		fprintf(fp,"%.0fK Time:%.2f\n",m_SP_fStaTc,m_SP_fIntTime);
		fprintf(fp,"%.1f %.1f %.3f\n",m_SP_fSpect1,m_SP_fSpect2,m_fInterval);
		fprintf(fp,m_SP_strDate+"\n");
		fprintf(fp,"%.3f  %.9f\n",m_CAL_fStaFlux[0],m_CAL_fFluxK[0]);

		iN=(int)((m_SP_fSpect2-m_SP_fSpect1)/m_fInterval+1+0.5f);
		for(i=0;i<iN;i++)
		{
			fprintf(fp,"%.1f %.5e\n",m_SP_fSpect1+i*m_fInterval,m_SP_fK[i]);
		}
	}
	fclose(fp);
	return TRUE;
}

BOOL CCSPEC_PRO::SP_Load(CString strPathName)
{
	int i,iN,iN1;
	//光谱定标数据
	FILE *fp;
	if((fp=fopen(strPathName,"rt"))==NULL)
		return FALSE;
	else
	{
		fscanf(fp,"%fK Time:%f\n",&m_SP_fStaTc,&m_SP_fIntTime);
		fscanf(fp,"%f %f %f\n",&m_SP_fSpect1,&m_SP_fSpect2,&m_fInterval);
		
		char a[256];
		fscanf(fp,"%s\n",a);
		m_SP_strDate=a;
		fscanf(fp,"%f  %f\n",&m_CAL_fStaFlux[0],&m_CAL_fFluxK[0]);
		
		iN=(int)((m_SP_fSpect2-m_SP_fSpect1)/m_fInterval+1+0.5f);
		float fK[10001];
		float fWL[10001];
		for(i=0;i<iN;i++)
		{
			fscanf(fp,"%f %f\n",&fWL[i],&fK[i]);
		}
		
		//差值为0.1nm
		m_fInterval=0.1f;
		iN1=(int)((m_SP_fSpect2-m_SP_fSpect1)/m_fInterval+1+0.5f);
		float fLamda;
		for(i=0;i<iN1;i++)
		{
			fLamda=m_SP_fSpect1+0.1f*i;
			m_SP_fK[i]=(float)g_doData.NewInt_float(fWL,fK,iN,fLamda);
		}
	}
	fclose(fp);
	return TRUE;
}

void CCSPEC_PRO::Maxmium(float fData[], int iN, int iMaxmium[], int &iHave, int iJu, float fMax)
{
	int i;
	iHave=0;
	if(fMax>0)
	{
		for(i=iJu;i<iN-iJu;i++)
		{
			for(int j=1;j<(iJu+1);j++)
			{
				if((fData[i]<m_fWLK*fMax)||(fData[i]<fData[i-j])||(fData[i]<fData[i+j]))
					break;
			}
			if(j==iJu+1)
			{
				iHave++;
				iMaxmium[iHave-1]=i;
			}
		}
		if(iHave>100)
			iHave=100;
		for(int j=0;j<iHave;j++)
		{
			int iL=iMaxmium[j];
			float fHalfP=0.8f;
			for(i=iMaxmium[j];i>=50;i--)
			{
				if(fData[i]<=(fData[iMaxmium[j]]*fHalfP))
				{
					iL=i;
					break;
				}
			}
			int iR=iMaxmium[j];
			for(i=iMaxmium[j];i<=iMaxmium[j]+50;i++)
			{
				if(fData[i]<=(fData[iMaxmium[j]]*fHalfP))
				{
					iR=i;
					break;
				}
			}
			iMaxmium[j]=(iR+iL)/2;
		}
	}
}

BOOL CCSPEC_PRO::WL_Load(CString strPathName)
{
	// 波长校正数据
	FILE *fp;
	if((fp = fopen(strPathName,"rt"))==NULL)
		return FALSE;
	else
	{
		float f1,f2,f3,f4;
		char a[256];
		fscanf(fp,"%f  %f  %f  %f\n",&f1,&f2,&f3,&f4);
		fscanf(fp,"%s\n",a);
		m_strSerial=a;
// 		m_Icor  = f1;
// 		m_C1cor = f2;
// 		m_C2cor = f3;
// 		m_C3cor = f4;
	}
	fclose(fp);
	m_iCroWLType = 0;
	SPEC_Correct();
	return TRUE;
}

BOOL CCSPEC_PRO::WL_Save(CString strPathName)
{
	//波长校正数据
	static CString strAngle;
	strAngle = "";
	if(m_iSR2AngleType == 1)
		strAngle = "Angle_Pos1_";
	
	if(m_iSR2AngleType == 2)
		strAngle = "Angle_Pos2_";
	
	if(m_iSR2AngleType == 3)
		strAngle = "Angle_Pos3_";
	
	if(m_iSR2AngleType == 4)
		strAngle = "Angle_Pos4_";
	
	if(strAngle != "")
	{
		
		CString strNew = strAngle + "wavecor";
		strPathName.Replace("wavecor", strNew.GetBuffer(256));
		strNew.ReleaseBuffer();
	}

	SPEC_Correct();  //重新计算
	FILE *fp;
	if((fp=fopen(strPathName,"wt"))==NULL)
		return FALSE;
	else
	{
		fprintf(fp,"%e %e %e %e\n",m_Icor,m_C1cor,m_C2cor,m_C3cor);
		fprintf(fp,"%s\n",m_strSerial);

		fprintf(fp,"\n\n");
		fprintf(fp,"SN.:%s\n",m_strSN);
		fprintf(fp,"VER:%s\n",m_strSoftVer);
		fprintf(fp,"EPROM:%s\n",m_strEprom);
		fprintf(fp,"Driver:%s\n",m_strDriver);
	}
	fclose(fp);
	return TRUE;
}

float CCSPEC_PRO::Max(float f[], int iN, int &iMax)
{
	int i;
	float fMax;
	fMax=f[0];
	iMax=0;
	for(i=1;i<iN;i++)
	{
		if(f[i]>fMax)
		{
			fMax=f[i];
			iMax=i;
		}
	}
	return fMax;
}

void CCSPEC_PRO::Func2(double *x, double *y, double a[2][2], double b[2])
{
	double tempa[2][2],tempb[2];
	int   i,j;

	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
			tempa[i][j]=a[i][j];
		tempb[i]=b[i];
	}

	*x=(a[1][1]*b[0]-a[0][1]*b[1])/(a[0][0]*a[1][1]-a[0][1]*a[1][0]);
	*y=(a[0][0]*b[1]-a[1][0]*b[0])/(a[0][0]*a[1][1]-a[0][1]*a[1][0]);
}

void CCSPEC_PRO::Func3(double *x, double *y, double *z, double a[3][3], double b[3])
{
	double tempa[3][3],tempb[3];
	double aa[2][2],bb[2];
	int   i,j;

	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
			tempa[i][j]=a[i][j];
		tempb[i]=b[i];
	}
	for(i=0;i<2;i++)
	{
		for(j=0;j<3;j++)
		{
			tempa[0][j]=a[0][j];
			tempa[0][j]*=a[i+1][0];
			tempa[i+1][j]*=a[0][0];
		}
		tempb[0]=b[0];
		tempb[0]*=a[i+1][0];
		tempb[i+1]*=a[0][0];
		for(j=1;j<3;j++)
			aa[i][j-1]=tempa[i+1][j]-tempa[0][j];
		bb[i]=tempb[i+1]-tempb[0];
	}

	Func2(y,z,aa,bb);
	
	*x=(b[0]-a[0][1]*(*y)-a[0][2]*(*z))/a[0][0];
}

void CCSPEC_PRO::Func4(double *x, double *y, double *m, double *n, double a[4][4], double b[4])
{
	double tempa[4][4],tempb[4];
	double aa[3][3],bb[3];
	int   i,j;
		
	for(i=0;i<4;i++)		//保存形参
	{
		for(j=0;j<4;j++)
			tempa[i][j]=a[i][j];
		tempb[i]=b[i];
	}

	for(i=0;i<3;i++)
	{
		for(j=0;j<4;j++)
		{
			tempa[0][j]=a[0][j];
			tempa[0][j]*=a[i+1][0];
			tempa[i+1][j]*=a[0][0];
		}
		tempb[0]=b[0];
		tempb[0]*=a[i+1][0];
		tempb[i+1]*=a[0][0];
		
		for(j=1;j<4;j++)
			aa[i][j-1]=tempa[i+1][j]-tempa[0][j];
		bb[i]=tempb[i+1]-tempb[0];
	}

	Func3(y,m,n,aa,bb);
	*x=(b[0]-a[0][1]*(*y)-a[0][2]*(*m)-a[0][3]*(*n))/a[0][0];
}

BOOL CCSPEC_PRO::SPEC_Correct()
{
	int i;
	float fx[100];
	float fy[100];
	int iN;
	iN = m_C2_fStaWL.GetSize();
	for(i = 0;i<iN;i++)
	{
		fx[i] = m_C2_fPix[i];
		fy[i] = m_C2_fStaWL[i];
	}
	for(i=0;i<m_iPixN;i++)
	{
		float lamda;
		if(m_iCroWLType == 0)
		{
			lamda=(float)(m_Icor+m_C1cor*pow(i,1)+m_C2cor*pow(i,2)+m_C3cor*pow(i,3));
		}
		else
		{
			lamda = (float)(g_doData.NewInt_float(fx,fy,iN,i*1.0f));
		}
		m_fLambdaPos[i] = lamda;
		m_iLambdaPos[i] = i;
	}

	///////////////////////////////
	CString strPathName=g_strCurPath;
	strPathName=strPathName+"temp.wl";
	WL_DataSave(strPathName);
	//////////////////////////////

	if(m_fLambdaPos[0]>T_SPECT1||m_fLambdaPos[m_iPixN-1]<T_SPECT2)
		return FALSE;
	else
		return TRUE;
}

BOOL CCSPEC_PRO::SPEC_OVER(float fMax)
{
	int i=0;
	int j=0;
	if(1)
	{
		if(m_bOverAD)
			return TRUE;

		float fTemp;
		int iPix=m_iPixN;
		for(i=0;i<m_iPixN;i++)
		{
			fTemp=SPEC_Pix2WL(i);
			if(fTemp>=T_SPECT2)
			{
				iPix=i;
				break;
			}
		}

		for(i=0;i<iPix;i++)
		{
			if(m_fAD[i]>m_nADW*m_fOverK)
			{
				return TRUE;
			}
		}

		return FALSE;
	}

	if(m_HAAS_iVer<3)
	{
		if(fMax>=(m_nADW*m_fOverK))
			return TRUE;
		return FALSE;
		for(i=0;i<m_iPixN;i++)
		{
			if(m_fAD[i]>m_nADW*9/10)
			{
				BOOL bOver=TRUE;
				for(j=i;j<=i+20;j++)
				{
					if(j>=(m_iPixN-1))
					{
						bOver=FALSE;
						break;
					}
					if(fabs(m_fAD[j]-m_fAD[i])>=3)
					{
						bOver=FALSE;
						break;
					}
				}
				if(bOver)
					return TRUE;
			}
		}
		return FALSE;
	}
	else
	{
		if(m_bOverAD)
			return TRUE;
		else
			return FALSE;
	}
}

BOOL CCSPEC_PRO::SPEC_GetAutoTime(float &fIntTime, int iLimitTime,float fL1,float fTimeB)
{
	BOOL bR;
	// 得到最佳的积分时间
	if(g_bDemo)
	{
		fIntTime=10;
		return TRUE;
	}

	fL1=0.75f;

	fL1=0.7f;
	float fMax;
	int iTestN=0;
	fIntTime=100;
	if(fTimeB!=0)
		fIntTime=fTimeB;
	if(m_iBin!=0)
	{
		if(fIntTime < m_fIntTime1)
			fIntTime = m_fIntTime1;
	}
	if(fIntTime>2000)
		fIntTime=2000;
	int iTemp=m_iMode;  //保存测量模式
	m_iMode=0;          //自动积分使用快速模式
	if(g_iSeleMode == 1)
	{
		Sleep(500);
	}

	float fAdMax;
	fAdMax=65000;
	float fAdLimit = (float)(fAdMax*m_fOverK);  //溢出判断
	if(1 == iTemp)
	{
		fAdLimit=fAdLimit*0.9f;//
	}
	float fAdAuto  = (float)(fAdMax*fL1);       //自动积分
Try:
	CString strTemp;
	if(g_bEnglish)
		strTemp.Format("Auto Time...");
	else
		strTemp.Format("正在自动积分,请等待...");
	CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,255));
	bR=SPEC_DoScan(fIntTime,1,MY_TRIG_NORMAL,fMax,FALSE,TYPE_SCAN,FALSE);
	if(!bR)
	{
		m_iMode=iTemp;
		return FALSE;
	}
	if(g_iSeleMode==1)
		Sleep(500);

	iTestN++;
	float fTemp1,fTemp2;
	fTemp1=(float)(fMax-fAdLimit);
	fTemp2=(float)(fMax-fAdAuto);

	if(fTemp1>0)
	{
		if(fIntTime<m_fIntTime1&&m_iBin!=0)
		{
			if(!CMySpecView::m_bPC2Mode)
			{
				if(g_bEnglish)
					AfxMessageBox("Signal too strong!",MB_ICONINFORMATION);
				else
					AfxMessageBox("信号太强!",MB_ICONINFORMATION);
			}
			m_iMode=iTemp;
			return FALSE;
		}
		if(fIntTime<=5&&m_iBin==0)
		{
			g_bStrong=TRUE;
			if(!CMySpecView::m_bPC2Mode)
			{
				if(g_bEnglish)
					AfxMessageBox("Signal too strong!",MB_ICONINFORMATION);
				else
					AfxMessageBox("信号太强!",MB_ICONINFORMATION);
			}
			m_iMode=iTemp;
			return FALSE;
		}
		if(fIntTime<=100||fTimeB==0)
			fIntTime=0.8f*fIntTime;
		else
			fIntTime=0.5f*fIntTime;
		if(fIntTime>iLimitTime)
			fIntTime=iLimitTime*1.0f;
		goto Try;
	}
	else
	{
		if(fMax>fAdAuto)//fTemp2>(-3000)&&fMax>10000)
		{
			if(fIntTime>=1.0f)
				fIntTime=(float)((int)(fIntTime)*1.0f);
			m_iMode=iTemp;
			g_bStrong=FALSE;
			return TRUE;
		}
		else
		{
			if(fMax>m_iDark)
				fIntTime=(float)((int)(((m_nADW*(m_fOverK*0.90f)-m_iDark)*fIntTime)/(fMax-m_iDark)+0.5f));
			else
				fIntTime=fIntTime*2;
			if(fIntTime>=iLimitTime)
			{
				fIntTime = iLimitTime*1.0f;
				if(!CMySpecView::m_bPC2Mode)
				{
					if(g_bEnglish)
						AfxMessageBox("Signal is too weak!",MB_ICONINFORMATION);
					else
						AfxMessageBox("信号太弱!",MB_ICONINFORMATION);
				}
				else
				{
					m_iMode=iTemp;
					g_bStrong=FALSE;
					return TRUE;
				}

				m_iMode=iTemp;
				g_bStrong=FALSE;
				return FALSE;
			}
			if(fIntTime<=m_fIntTime1)
				fIntTime=m_fIntTime1*1.0f;

			if(iTestN>6)
			{
				if(fIntTime>=1.0f)
					fIntTime=(int)fIntTime*1.0f;
				m_iMode=iTemp;
				g_bStrong=FALSE;
				return TRUE;
			}
			goto Try;
		}
	}
}

BOOL CCSPEC_PRO::SPEC_GetDark(float fTime,int iAveN)
{
	int i;
	if(g_bDemo)
	{
		for(i=0;i<m_iPixN;i++)
		{
			m_fDarkAD[i] = 1000;
		}
		return TRUE;
	}
	float fTemp[4096];
	for(i=0;i<m_iPixN;i++)
		fTemp[i]=m_fAD[i];

//	BOOL bR;
	int iTemp=m_iMode;
	m_iMode=0;

	if(SPEC_Sample(fTime,iAveN,MY_TRIG_NORMAL,m_bOverAD,FALSE))
	{
		for(i=0;i<m_iPixN;i++)
			m_fDarkAD[i]=m_fAD[i];
	}
	else
		return FALSE;

	if(1)
	{
		//处理坏点
		float iTempPix[3648];
		float fTempAD[3648];
		
		BOOL bBad=FALSE;
		int i,j,iN=0;
		for(i=0;i<m_iPixN;i++)
		{
			bBad=FALSE;
			for(j=0;j<m_iBadNum;j++)
			{
				if(i==m_iBadPoint[j])
				{
					bBad=TRUE;
					break;
				}
			}
			if(!bBad)
			{
				iTempPix[iN]=(float)(i);
				fTempAD[iN]=(float)(m_fDarkAD[i]);
				iN++;
			}
		}
		for(i=0;i<m_iPixN;i++)
		{
			for(j=0;j<m_iBadNum;j++)
			{
				if(i==m_iBadPoint[j])
					m_fDarkAD[i]=(float)g_doData.NewInt_float(iTempPix,fTempAD,iN,i*1.0f);
			}
		}

		if(0)//m_iModBadP2 == 1)
		{
			if(m_iModBadP2 == 1 && fTime > m_iModBadP2_Time)
			{
				int iErrorNum;
				float m_fProAD[2048];
				HassDarkPro(m_fDarkAD, m_iPixN, m_iModBadP2_AD * 1.0f,m_iModBadP2_Num, iErrorNum, m_fProAD);
				if(iErrorNum > 0)
				{
					FILE *fp;
					if((fp=fopen(g_strCurPath+"ProAD.dat","wt"))==0)
					{
					}
					else
					{
						for(int i=0;i<m_iPixN;i++)
						{
							fprintf(fp,"%4d %10.3f %10.3f\n",i,m_fDarkAD[i], m_fProAD[i]);
						}
						fclose(fp);
					}

					CString sTemp;
					sTemp.Format("处理错误点数: %d",iErrorNum);
					AfxMessageBox(sTemp);
				}
				for(i=0;i<m_iPixN;i++)
				{
					m_fDarkAD[i] = m_fProAD[i];
				}
			}
		}
	}

	for(i=0;i<m_iPixN;i++)
	{
		m_fAD[i]=fTemp[i];
	}

	m_iMode=iTemp;
	Sleep(100);
	m_fIntTimeDark=fTime;
	DARK_Save();
	return TRUE;
}

BOOL CCSPEC_PRO::SPEC_Init()
{
	BOOL bR=FALSE;
	bR=m_HAAS.Init(m_iPixN,m_nADW);

	DARK_Open();
	return bR;
}

BOOL CCSPEC_PRO::SPEC_Sample(float fIntTime, int iAveNum, int iTrigType,BOOL &bOverAD,BOOL bNote)
{
	int i=0;
	BOOL bR=FALSE;
	bOverAD=FALSE;
	bR = SPEC_Init();
	if (!bR)
	{
		return FALSE;
	}
	bR= m_HAAS.Scan(fIntTime,iAveNum,m_fAD,bOverAD,bNote);

	return bR;
}

BOOL CCSPEC_PRO::SPEC_UnInit()
{
	if(g_bDemo)
		return TRUE;
	
	//Save Dark
	DARK_Save();

	return m_HAAS.UnInit();

	return TRUE;
}

BOOL CCSPEC_PRO::WL_DataSave(CString strPathName)
{
	FILE *fp;
	if((fp=fopen(strPathName,"wt"))==0)
	{
		return FALSE;
	}
	else
	{
		for(int i=0;i<m_iPixN;i++)
		{
			if(i==0)
				fprintf(fp,"%4d %8.3f %8.3f\n",i,m_fLambdaPos[i],0);
			else
				fprintf(fp,"%4d %8.3f %8.3f\n",i,m_fLambdaPos[i],m_fLambdaPos[i]-m_fLambdaPos[i-1]);
		}
		fclose(fp);
		return TRUE;
	}
}

BOOL CCSPEC_PRO::SPEC_DoScan(float fIntTime, int iAveN, int nTriggerMode, float &fMax, BOOL bZero, int iType,BOOL bNote)
{
	//采样数据
	if(g_bDemo)
	{
		ReadWaveData();

		Sleep((int)(fIntTime+0.5f)*iAveN);
		int i;
		fMax=0;
		int MM;
		srand(GetCurrentTime()*rand());
		MM=1400-(rand()*rand())%800;
		//MM=1200;
		float fK=0.0005f+0.0001f*rand()/RAND_MAX;
		//fK=0.0001f;
		if(nTriggerMode==MY_TRIG_HARD_IN)
		{
		}
		float M=2.0f+rand()*0.5f/RAND_MAX;
		//M=2.0f;
		for(i=0;i<m_iPixN;i++)
		{
			const float fP=1000;//+rand()*10.0f/RAND_MAX;
			float fD =fIntTime*fP*(float)(1/(1+fK*pow(fabs(i-MM),M)));
			//float fD =iIntTime*fP*(float)(1/(1+fK*pow(fabs(i-MM),1.4f)));
			//float fD =iIntTime*fP*(float)(1/(1+fK*fK*pow(fabs(i-MM),3.4f)));

			float fL1=fIntTime*fP*(float)(1/(1+1.005*pow((i-200),2)));
			float fL2=fIntTime*fP*(float)(1/(1+1.005*pow((i-400),2)));
			float fL3=fIntTime*fP*(float)(1/(1+1.005*pow((i-700),2)));
			float fL4=fIntTime*fP*(float)(1/(1+1.005*pow((i-900),2)));

			m_fAD[i]=(int)(fD+0.5f)*1.0f;
			if(iType==TYPE_CHECK)
				m_fAD[i]=fL1+fL2+fL3+fL4;
			if(1)//iType==TYPE_CAL)
			{
				m_fAD[i]=(float)(10000+fIntTime*1000*sin(i*3.1415926535*0.3f/(m_iPixN-1)));
				if(m_fAD[i]>65535)
					m_fAD[i]=65535;
			}
//			if(iType==TYPE_SCAN)
//				m_fAD[i]=fD;
			m_fAD[i] = 60000;
			if(m_fAD[i]>fMax)
				fMax=m_fAD[i];
		}
		m_fIntTime=fIntTime;
		m_fIp=fMax;
		return TRUE;
	}
	BOOL bR;
	//先读取波长数据
	ReadWaveData();

	if(bZero)
	{
		SPEC_GetDark(fIntTime,iAveN);
	}

	//启动采样数据
	bR = SPEC_Sample(fIntTime,iAveN,nTriggerMode,m_bOverAD,bNote);

	CString strTemp;
	strTemp="";
	CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,255));
	FILE *fp;
	if((fp=fopen(g_strCurPath+"data.dat","wt"))==NULL)
	{
	}
	else
	{
		for(int i=0;i<m_iPixN;i++)
			fprintf(fp,"%4d %.3f %.3f\n",i,m_fLambdaPos[i],m_fAD[i]);
	}
	fclose(fp);
	
	if(!bR)
	{
		return FALSE;
	}

	if(1)
	{
		//处理坏点
		float iTempPix[3648];
		float fTempAD[3648];
		
		BOOL bBad=FALSE;
		int i,j,iN=0;
		for(i=0;i<m_iPixN;i++)
		{
			bBad=FALSE;
			for(j=0;j<m_iBadNum;j++)
			{
				if(i==m_iBadPoint[j])
				{
					bBad=TRUE;
					break;
				}
			}
			if(!bBad)
			{
				iTempPix[iN]=(float)(i);
				fTempAD[iN]=(float)(m_fAD[i]);
				iN++;
			}
		}
		for(i=0;i<m_iPixN;i++)
		{
			for(j=0;j<m_iBadNum;j++)
			{
				if(i==m_iBadPoint[j])
					m_fAD[i]=(float)g_doData.NewInt_float(iTempPix,fTempAD,iN,i*1.0f);
			}
		}
	}
	//取出采样数据
	int i;
	int iMax=0;
	fMax=0;
	for(i=0;i<m_iPixN;i++)
	{
		m_fAD[i]=m_fAD[i]*1.0f;
		if(m_fAD[i]>fMax)
		{
			fMax=m_fAD[i];
			iMax=i;
		}
	}
	m_fIntTime=fIntTime;
//	if(g_iMax==-1)
		g_iMax=iMax;
	m_fIp=m_fAD[g_iMax];//fMax;
	if(m_fIp<=100)
		m_bSingleWeak=TRUE;
	else
		m_bSingleWeak=FALSE;

	return TRUE;
}

void CCSPEC_PRO::MyBeep(int iT)
{
	DWORD iT1=GetCurrentTime();
	while(1)
	{
		Beep(1000,500);
		if(GetCurrentTime()>(iT1+iT))
			break;
	}
}

int CCSPEC_PRO::GetWL12peakPos(float fWL[], float fP[], int iN, float fWL1, float fWL2,float &fBW, float fHalf)
{
	//得到两波段间的峰值
	int   iPos=0;
	float fMax=0;
	for(int i=0;i<iN;i++)
	{
		if(fWL[i]>=fWL1&&fWL[i]<=fWL2)
		{
			if(fP[i]>fMax)
			{
				fMax=fP[i];
				iPos=i;
			}
		}
	}
//	return iPos;
	//面积几何法
	int iMax=iPos;
	int iL=iMax;
	if(fHalf > 0.3f)
	{
		for(i = iMax; i >= 0; i--)
		{
			if(fP[i] <= (fMax * fHalf))
			{
				iL = i;
				break;
			}
		}
		int iR = iMax;
		for(i = iMax; i <= (iN-1); i++)
		{
			if(fP[i] <= (fMax * fHalf))
			{
				iR=i;
				break;
			}
		}
		float fSum1,fSum2;
		fSum1=0;
		for(i=iL;i<iR;i++)
		{
			fSum1=fP[i]+fSum1;
		}
		fSum2=0;
		for(i = iL; i < iR; i++)
		{
			fSum2=fP[i]+fSum2;
			if(fSum2>=(fSum1/2))
			{
				iPos=i;
				break;
			}
		}
		if(iPos<=0)
		{
			iPos=0;
		}

		if(iPos>=(iN-1))
		{
			iPos=iN-1;
		}

		fBW = (float)((iR - iL) * 0.1f);

		return iPos;
	}
	else
	{
		fHalf = 0.3f;
		if(g_bFunDebug)
			fHalf = 0.3f;
		else
			fHalf = 0.7f;
		for(i=iMax;i>=0;i--)
		{
			if(fP[i]<=(fMax*fHalf))
			{
				iL=i;
				break;
			}
		}
		int iR=iMax;
		for(i=iMax;i<=(iN-1);i++)
		{
			if(fP[i]<=(fMax*fHalf))
			{
				iR=i;
				break;
			}
		}
		float fSum1,fSum2;
		fSum1=0;
		for(i=iL;i<iR;i++)
		{
			fSum1=fP[i]+fSum1;
		}
		fSum2=0;
		for(i=iL;i<iR;i++)
		{
			fSum2=fP[i]+fSum2;
			if(fSum2>=(fSum1/2))
			{
				iPos=i;
				break;
			}
		}
		//	iPos=iPos-1;
		//	iPos=(iR+iL)/2;
		if(iPos<=0)
			iPos=0;
		if(iPos>=(iN-1))
			iPos=iN-1;
		return iPos;
	}
/*	//得到两波段间的峰值
	int   iPos=0;
	float fMax=0;
	for(int i=0;i<iN;i++)
	{
		if(fWL[i]>=fWL1&&fWL[i]<=fWL2)
		{
			if(fP[i]>fMax)
			{
				fMax=fP[i];
				iPos=i;
			}
		}
	}
//	return iPos;
	//面积几何法
	int iMax=iPos;
	int iL=iMax;
	if(fHalf > 0.3f)
	{
		for(i = iMax; i >= 0; i--)
		{
			if(fP[i] <= (fMax * fHalf))// && fWL[i] >= fWL1)
			{
				iL = i;
				break;
			}
		}
		int iR = iMax;
		for(i = iMax; i <= (iN-1); i++)
		{
			if(fP[i] <= (fMax * fHalf))// && fWL[i] <= fWL2)
			{
				iR=i;
				break;
			}
		}
		float fSum1,fSum2;
		fSum1=0;
		for(i=iL;i<iR;i++)
		{
			fSum1=fP[i]+fSum1;
		}
		fSum2=0;
		for(i = iL; i < iR; i++)
		{
			fSum2=fP[i]+fSum2;
			if(fSum2>=(fSum1/2))
			{
				iPos=i;
				break;
			}
		}
		if(iPos<=0)
		{
			iPos=0;
		}

		if(iPos>=(iN-1))
		{
			iPos=iN-1;
		}

		fBW = (float)((iR - iL) * 0.1f);

		return iPos;
	}
	else
	{
		fHalf = 0.3f;
		if(g_bFunDebug)
			fHalf = 0.3f;
		else
			fHalf = 0.7f;
		for(i=iMax;i>=0;i--)
		{
			if(fP[i]<=(fMax*fHalf))// && fWL[i] >= fWL1)
			{
				iL=i;
				break;
			}
		}
		int iR=iMax;
		for(i=iMax;i<=(iN-1);i++)
		{
			if(fP[i]<=(fMax*fHalf))// && fWL[i] <= fWL2)
			{
				iR=i;
				break;
			}
		}
		float fSum1,fSum2;
		fSum1=0;
		for(i=iL;i<iR;i++)
		{
			fSum1=fP[i]+fSum1;
		}
		fSum2=0;
		for(i=iL;i<iR;i++)
		{
			fSum2=fP[i]+fSum2;
			if(fSum2>=(fSum1/2))
			{
				iPos=i;
				break;
			}
		}
		//	iPos=iPos-1;
		//	iPos=(iR+iL)/2;
		if(iPos<=0)
			iPos=0;
		if(iPos>=(iN-1))
			iPos=iN-1;
		return iPos;
	}*/
}

BOOL CCSPEC_PRO::Set_Load(CString strPathName)
{
	FILE *fp;
	if((fp=fopen(strPathName,"rt"))==0)
		return FALSE;
	else
	{
		fscanf(fp,"Set\n");
		fscanf(fp,"OverPerAD:%f\n",&m_fOverK);
		fscanf(fp,"WL Range :%f-%f\n",&T_SPECT1,&T_SPECT2);
		if(g_fSpect1<T_SPECT1)
			g_fSpect1=T_SPECT1;
		if(g_fSpect2>T_SPECT2)
			g_fSpect2=T_SPECT2;
		fscanf(fp,"IntTime  :%f-%f\n",&m_fIntTime1,&m_fIntTime2);

		fclose(fp);
		return TRUE;
	}
}

BOOL CCSPEC_PRO::Set_Save(CString strPathName)
{
	FILE *fp;
	if((fp=fopen(strPathName,"wt"))==0)
		return FALSE;
	else
	{
		fprintf(fp,"Set\n");
		fprintf(fp,"OverPerAD:%.2f\n",m_fOverK);
		fprintf(fp,"WL Range :%.0f-%.0f\n",T_SPECT1,T_SPECT2);
		if(m_fIntTime1<1)
			fprintf(fp,"IntTime  :%.2f-%.0f\n",m_fIntTime1,m_fIntTime2);
		else
			fprintf(fp,"IntTime  :%.0f-%.0f\n",m_fIntTime1,m_fIntTime2);
		fclose(fp);
		return TRUE;
	}
}

BOOL CCSPEC_PRO::DARK_Open()
{
	FILE *fp;
	if((fp=fopen(g_strCurPath+"dark.dat","rt"))==0)
		return FALSE;
	else
	{
		int iTemp;
		for(int i=0;i<m_iPixN;i++)
			fscanf(fp,"%d %f\n",&iTemp,&m_fDarkAD[i]);
		fclose(fp);
		return TRUE;
	}
}

BOOL CCSPEC_PRO::DARK_Save()
{
	FILE *fp;
	if((fp=fopen(g_strCurPath+"dark.dat","wt"))==0)
		return FALSE;
	else
	{
		for(int i=0;i<m_iPixN;i++)
			fprintf(fp,"%4d %10.3f\n",i,m_fDarkAD[i]);
		fclose(fp);
		return TRUE;
	}
}

float CCSPEC_PRO::SPEC_Pix2WL(int iPix)
{
	if(m_iCroWLType == 0)
	{
		return (float)(m_Icor+m_C1cor*pow(iPix,1)+m_C2cor*pow(iPix,2)+m_C3cor*pow(iPix,3));
	}
	else
	{
		int i;
		float fx[100];
		float fy[100];
		int iN;
		iN = m_C2_fStaWL.GetSize();
		for(i = 0;i<iN;i++)
		{
			fx[i] = m_C2_fPix[i];
			fy[i] = m_C2_fStaWL[i];
		}

		float flambda;
		flambda = (float)(g_doData.NewInt_float(fx,fy,iN,iPix*1.0f));
		return flambda;
	}
}

float CCSPEC_PRO::MAX_F(float fD)
{
	//如是  1.2  -> 1.5
	//      2.0  -> 2.0
	//      0.21 -> 0.25
	if(fD==0)
		return 1.0f;

	BOOL bF=FALSE;
	if(fD<0)
		bF=TRUE;
	CString strTemp;
	strTemp.Format("%.0e",fabsf(fD));
	float fD2=(float)atof(strTemp);
	if(fD2<fabsf(fD))
	{
		strTemp.Insert(1,'5');
		strTemp.Insert(1,'.');
		fD2=(float)atof(strTemp);
	}
	if(bF)
		fD2=fD2*-1;
	return fD2;
}

BOOL CCSPEC_PRO::STAWL_Load(CString strPathName)
{
	//标准的谱线
	FILE *fp;
	if((fp=fopen(strPathName,"r++"))==NULL)
		return FALSE;
	else
	{
		m_arra_strSource.RemoveAll();
		m_arra_fStaWL.RemoveAll();
		int iN;
		fscanf(fp,"SOURCE:%d\n\n",&iN);

		float fTemp;

		for(int i = 0; i < iN; i++)
		{
			CString strSource;
			char aC[256],aE[256];
			fscanf(fp,"%s %s\n",aC,aE);
			if(g_bEnglish)
			{
				strSource = aE;
			}
			else
			{
				strSource = aC;
			}

			int N;
			fscanf(fp,"%d", &N);
	
			for(int j = 0; j < N; j++)
			{
				fscanf(fp,"%f", &fTemp);
				m_arra_strSource.Add(strSource);
				m_arra_fStaWL.Add(fTemp);
			}
		}
		fclose(fp);
		return TRUE;
	}
}

BOOL CCSPEC_PRO::Gauss2XF_Calc(double fx[], double fy[], int iN, int iMN, double a[])
{
	//代数多项式的Gauss最小二乘法,曲线拟合
	// IN:  fx[],fy[] 拟合数据 iN个数
	//      iMN  拟合多项式的次数
	// OUT: a[]  多项式各次系数  a0 a1 a2 ...共 (iMN+1)个

	if(iN<iMN)
		return FALSE;
	if(iMN<1)
		return FALSE;

	int NN=iMN+1;
	int i,j,t;
	double *K=new double[NN*NN];//系数     ==
	double *z=new double[NN];
	//1.求出法方程的系数
	for(i=0;i<NN;i++)          //行
	{
		//K
		for(j=i;j<NN;j++)      //列
		{
			K[i*NN+j]=0;
			for(t=0;t<iN;t++)
			{
				K[i*NN+j]=K[i*NN+j]+pow(fx[t],i+j);
			}

			if(i!=j)
			{
				K[j*NN + i] = K[i * NN + j];
			}
		}
		//z
		z[i]=0;
		for(t=0;t<iN;t++)
			z[i]=z[i]+pow(fx[t],i)*fy[t];
	}

	//2.解线性方程组  高斯消元()法
	if(Gauss_EQU(K,z,NN,a)==FALSE)
	{
		delete K;
		delete z;
		return FALSE;
	}
	delete K;
	delete z;
	return TRUE;
}

BOOL CCSPEC_PRO::Gauss_EQU(double fk[], double fz[], int iN, double a[])
{
	//高斯消去法解线性方程组
	//IN:  fK[] iN*iN 个行-列
	//     fz   iN行
	//OUT: a[]  iN个解
	int i,j,t;
	double fTemp1,fTemp2,fTemp;
	double K;
	//1.消元
	for(i=0;i<iN-1;i++)              //行
	{
		fTemp1=fk[i*iN+i];           //i行i列

		//如果是0找出不是0的换行
		if(fTemp1==0.0)
		{
			//找出不是0的i列的某一行iSele
			int iSele=-1;
			for(j=i+1;j<iN;j++)
			{
				if(fk[j*iN+i]!=0.0)
				{
					iSele=j;
					break;
				}
			}
			if(iSele==-1)        //找不到
				return FALSE;

			//交换
			for(j=0;j<iN;j++)
			{
				fTemp=fk[i*iN+j];
				fk[i*iN+j]=fk[iSele*iN+j];
				fk[iSele*iN+j]=fTemp;
			}
			fTemp	 = fz[i];
			fz[i]	 = fz[iSele];
			fz[iSele]= fTemp;
			fTemp1	 = fk[i*iN+i];   //i行i列
		}

		//计算三角矩形，及Z
		for(j=i+1;j<iN;j++)          //行
		{
			fTemp2=fk[j*iN+i];       //j行i列
			K=-fTemp2/fTemp1;
			for(t=i;t<iN;t++)        //列变化
				fk[j*iN+t]=fk[j*iN+t]+fk[i*iN+t]*K;
			fz[j]=fz[j]+fz[i]*K;
		}
	}
	//2.回代
	for(i=iN-1;i>=0;i--)     //行
	{
		a[i]=fz[i];
		for(j=i+1;j<iN;j++)    //列
			a[i]=a[i]-fk[i*iN+j]*a[j];
		a[i]=a[i]/fk[i*iN+i];
	}
	return TRUE;
}

BOOL CCSPEC_PRO::SPEC_FluxAD(int iRange, float &fAD)
{
	////////////////////////////////////
	// 得到光通量值 固定量程
	BOOL bR = TRUE;

	return bR;
}

BOOL CCSPEC_PRO::FLUX_GetRangeK(CString sPathName)
{
	///读取光度档位系数
	FILE *fp;
	if((fp=fopen(sPathName,"rt"))==0)
	{
		m_fModeSelfK	= 1.0f;
		m_fModeFluxK	= 1.0f;
		m_correctAD		= 15000;
		m_correctK		= 0;

		m_fZero[0]		= 0;
		m_fZero[1]		= 0;
		m_fZero[2]		= 0;
		m_fZero[3]		= 0;

		m_fRangeK[0]	= 10;
		m_fRangeK[1]	= 10;
		m_fRangeK[2]	= 10;
	
		if(g_bEnglish)
		{
			AfxMessageBox("Open the file fail!",MB_ICONINFORMATION);
		}
		else
		{
			AfxMessageBox("文件读取失败!",MB_ICONINFORMATION);
		}
		return FALSE;
	}
	else
	{
		fscanf(fp,"Zero1:%f\n",&m_fZero[0]);
		fscanf(fp,"Zero2:%f\n",&m_fZero[1]);
		fscanf(fp,"Zero3:%f\n",&m_fZero[2]);
		fscanf(fp,"Zero4:%f\n",&m_fZero[3]);

		fscanf(fp,"K12:%f\n",&m_fRangeK[0]);
		fscanf(fp,"K23:%f\n",&m_fRangeK[1]);
		fscanf(fp,"K34:%f\n",&m_fRangeK[2]);

		fscanf(fp,"\ncorrect:AD=%f  k=%f\n",&m_correctAD,&m_correctK);

		fclose(fp);
		return TRUE;
	}
	return TRUE;
}

BOOL CCSPEC_PRO::FLUX_SaveRangeK(CString sPathName)
{
	////保存FLUXK.dat
	FILE *fp;
	CString sTemp = g_strCurPath;
	if((fp = fopen(sTemp + "Cal\\FluxK.dat", "wt")) == 0)
	{
		if(g_bEnglish)
		{
			AfxMessageBox("Fail!", MB_ICONINFORMATION);
		}
		else
		{
			AfxMessageBox("保存失败!", MB_ICONINFORMATION);
		}
		return FALSE;
	}
	else
	{
		fprintf(fp,"Zero1:%10.6f\n", m_fZero[0]);
		fprintf(fp,"Zero2:%10.6f\n", m_fZero[1]);
		fprintf(fp,"Zero3:%10.6f\n", m_fZero[2]);
		fprintf(fp,"Zero4:%10.6f\n", m_fZero[3]);
		
		fprintf(fp,"K12:%10.6f\n", m_fRangeK[0]);
		fprintf(fp,"K23:%10.6f\n", m_fRangeK[1]);
		fprintf(fp,"K34:%10.6f\n", m_fRangeK[2]);
		
		fprintf(fp,"\ncorrect:AD=%f  k=%f\n", g_SPEC.m_correctAD, g_SPEC.m_correctK);
		
		fprintf(fp,"\n\n");
		fprintf(fp,"SN.:%s\n",m_strSN);
		fprintf(fp,"VER:%s\n",m_strSoftVer);
		fprintf(fp,"EPROM:%s\n",m_strEprom);
		fprintf(fp,"Driver:%s\n",m_strDriver);

		fclose(fp);

		if(g_bEnglish)
		{
			AfxMessageBox("Succeed!",MB_ICONINFORMATION);
		}
		else
		{
			AfxMessageBox("保存成功!",MB_ICONINFORMATION);
		}
		return TRUE;
	}
}

BOOL CCSPEC_PRO::FLUX_GetCalK(CString sPathName)
{
	//读取光通量定标数据文件
	FILE *fp;
	if((fp=fopen(sPathName,"rt"))==0)
	{

		if(g_bEnglish)
			AfxMessageBox("Open the file 'Flux.cal' fail!\r\n" + sPathName,MB_ICONINFORMATION);
		else
			AfxMessageBox("未找到定标文件Flux.cal,\n请在测试前先定标\r\n" + sPathName,NULL,MB_ICONINFORMATION);

//		m_CAL_fStaFlux[0]=100.0f;
//		m_CAL_fIntTime[0]=100.0f;
//		m_CAL_fFluxK[0]=1;
//		m_CAL_iRange[0]=0;

		m_CAL_fStaFlux[1]=100.0f;
		m_CAL_fIntTime[1]=100.0f;
		m_CAL_fFluxK[1]=1;
		m_CAL_iRange[1]=0;

		m_CAL_fStaFlux[2]=100.0f;
		m_CAL_fIntTime[2]=100.0f;
		m_CAL_fFluxK[2]=1;
		m_CAL_iRange[2]=0;

		return FALSE;
	}
	else
	{
		fscanf(fp,"Flux:\n");
		float f1;
		fscanf(fp,"StaFlux:%f\n",&f1);//m_CAL_fStaFlux[0]);
		fscanf(fp,"IntTime:%f\n",&f1);//m_CAL_fIntTime[0]);
		fscanf(fp,"FluxK  :%f\n\n",&f1);//m_CAL_fFluxK[0]);

		fscanf(fp,"StaFlux:%f\n",&m_CAL_fStaFlux[1]);
		fscanf(fp,"FluxK  :%f\n",&m_CAL_fFluxK[1]);
		fscanf(fp,"Range  :%d\n\n",&m_CAL_iRange[1]);

		fscanf(fp,"LX:\n");
		fscanf(fp,"StaFlux:%f\n",&m_CAL_fStaFlux[2]);
		fscanf(fp,"FluxK  :%f\n",&m_CAL_fFluxK[2]);
		fscanf(fp,"Range  :%d\n\n",&m_CAL_iRange[2]);
		fclose(fp);
	}
	return TRUE;
}

BOOL CCSPEC_PRO::FLUX_SaveCalK(CString sPathName)
{
	//保存光通量定标文件
	FILE *fp;
	if((fp=fopen(sPathName,"wt"))==NULL)
	{
		if(g_bEnglish)
			AfxMessageBox("Can't creat file.",NULL,MB_ICONSTOP);
		else
			AfxMessageBox("不能创建文件.",NULL,MB_ICONSTOP);
		return FALSE;
	}
	else
	{
		fprintf(fp,"Flux:\n");
		fprintf(fp,"StaFlux:%.3f\n",m_CAL_fStaFlux[0]);
		fprintf(fp,"IntTime:%.3f\n",m_CAL_fIntTime[0]);
		fprintf(fp,"FluxK  :%.9f\n\n",m_CAL_fFluxK[0]);

		fprintf(fp,"StaFlux:%.3f\n",m_CAL_fStaFlux[1]);
		fprintf(fp,"FluxK  :%.8f\n",m_CAL_fFluxK[1]);
		fprintf(fp,"Range  :%d\n\n",m_CAL_iRange[1]);

		fprintf(fp,"LX:\n");
		fprintf(fp,"StaFlux:%.3f\n",m_CAL_fStaFlux[2]);
		fprintf(fp,"FluxK  :%.8f\n",m_CAL_fFluxK[2]);
		fprintf(fp,"Range  :%d\n",m_CAL_iRange[2]);

		CTime tNow;
		tNow=CTime::GetCurrentTime();
		CString sNow=tNow.Format("%Y-%m-%d %I:%M");
		fprintf(fp,sNow);

		fprintf(fp,"\n\n");
		fprintf(fp,"SN.:%s\n",m_strSN);
		fprintf(fp,"VER:%s\n",m_strSoftVer);
		fprintf(fp,"EPROM:%s\n",m_strEprom);
		fprintf(fp,"Driver:%s\n",m_strDriver);
	}
	fclose(fp);
	return TRUE;
}

BOOL CCSPEC_PRO::SPEC_FluxAuto(float &fAD, float &fFlux)
{
	BOOL bR;
	int iType=m_iTestType;
	if(iType>2)
		iType=2;
	float fFlux1;
	if(m_bPhoto)
	{
		bR=SPEC_FluxAD(g_iRange,fFlux);    //当前档位
		if(!bR)
			return FALSE;
		fFlux1=(float)(m_CAL_fFluxK[iType]*fFlux);
		fAD=fFlux;
		fFlux=fFlux1;
	}
	else
	{
		////////////////////////////////////
		////得到光通量值 自动量程切换
		while(1)
		{
			bR=SPEC_FluxAD(g_iRange,fFlux);    //当前档位
			if(!bR)
				return FALSE;

			if(fFlux>AD_FLUX_MAX)  //溢出
				g_iRange++;
			else if(fFlux<AD_FLUX_MIN)  //太小
				g_iRange--;
			else
			{
				break;
			}

			if(g_iRange < 0)
			{
				g_iRange = 0;
				break;
			}
			if(g_iRange > 3)
			{
				g_iRange = 3;
				break;
			}
		}

		fAD=fFlux;

		fFlux=fFlux-m_fZero[g_iRange];
		if(fFlux<=0)
		{
			fFlux1=0;
		}
		else
		{
			if(g_iRange==0)
				fFlux=(float)(fFlux/m_fRangeK[0]);
			else if(g_iRange==1)
				fFlux=(float)(fFlux);
			else if(g_iRange==2)
				fFlux=(float)(fFlux*m_fRangeK[1]);
			else
				fFlux=(float)(fFlux*m_fRangeK[1]*m_fRangeK[2]);
			if(m_fModeFluxK<=0)
				m_fModeFluxK=1;

			if(m_fModeSelfK<=0)
				m_fModeSelfK=1;

			fFlux1=(float)(m_CAL_fFluxK[iType]*fFlux*m_fModeFluxK*m_fModeSelfK);
		}
		fFlux=fFlux1;
	}
	return TRUE;
}

BOOL CCSPEC_PRO::SPEC_GetTMP(int iType,int iAveN,float &fTMP,int &iTMPAD)
{
		return TRUE;
}

BOOL CCSPEC_PRO::SPEC_Cool(BOOL bOn)
{
	if(g_bDemo)
	{
		m_bHaveCool = bOn;
		return TRUE;
	}

	return TRUE;
}

BOOL CCSPEC_PRO::WD_ReadACData(CString strPathName)
{
	FILE *fp;
	if((fp=fopen(strPathName+"\\Cal\\LampC.dat","rt"))==0)
	{
		if(g_bEnglish)
			AfxMessageBox("'LampC.dat' can't open!");
		else
			AfxMessageBox("LampC.dat 文件读取失败!",MB_ICONINFORMATION);

		m_iNum_KAC = 0;
		return FALSE;
	}
	else
	{
		m_iNum_KAC = 0;
		while (1)
		{
			float f1,f2,f3;
			fscanf(fp,"%f	%f	%f\n",&f1,&f2,&f3);
			if(f1 < 0 || m_iNum_KAC >= 1000)
			{
				break;
			}
			m_fWL_AC[m_iNum_KAC] = f1;
			if(f2!=0 && f3!=0)
			{
				m_fK_AC[m_iNum_KAC] = f2 / f3;
			}
			else
			{
				m_fK_AC[m_iNum_KAC] = 0;
			}

			m_iNum_KAC++;
			
		}
		fclose(fp);
	}
	return TRUE;
}


BOOL CCSPEC_PRO::WD_GetCalData(CString strPathName)
{
	FILE *fp;
	if((fp=fopen(strPathName+"Cal\\wd_cal.dat","rt"))==0)
	{
		if(g_bEnglish)
			AfxMessageBox("'wd_cal.dat' can't open!");
		else
			AfxMessageBox("wd_cal.dat 文件读取失败!",MB_ICONINFORMATION);
		return FALSE;
	}
	else
	{
		fscanf(fp,"wd_cal:%f\n",&m_wd_fMod);
		fclose(fp);
	}
	return TRUE;
}

BOOL CCSPEC_PRO::WD_SaveCalData(CString strPathName)
{
	FILE *fp;
	if((fp=fopen(strPathName+"Cal\\wd_cal.dat","wt"))==0)
	{
		if(g_bEnglish)
			AfxMessageBox("'wd_cal.dat' can't save!");
		else
			AfxMessageBox("wd_cal.dat 文件保存失败!",MB_ICONINFORMATION);
		return FALSE;
	}
	else
	{
		fprintf(fp,"wd_cal:%f\n",m_wd_fMod);
		fclose(fp);
	}
	return TRUE;
}

BOOL CCSPEC_PRO::FILE_GetTMPK(CString sPath)
{
	FILE *fp;
	if((fp=fopen(sPath+"Cal\\TMP.dat","rt"))==0)
	{
		if(g_bEnglish)
			AfxMessageBox("'TMP.dat' can't open!");
		else
			AfxMessageBox("TMP.dat 文件读取失败!",MB_ICONINFORMATION);
		return FALSE;
	}
	else
	{
		fscanf(fp,"R1:%f AD1:%d\n",&m_fR1,&m_iRAD1);
		fscanf(fp,"R2:%f AD2:%d\n",&m_fR2,&m_iRAD2);
		fscanf(fp,"R3:%f AD3:%d\n",&m_fR3,&m_iRAD3);

		fclose(fp);
	}
	return TRUE;
}

void CCSPEC_PRO::SPEC_Setting()
{
	CString strT;
	if(g_bEnglish)
		strT="System Setup";
	else
		strT="系统设置";
	CMySheet sheet(strT);

	CSetup1 dPage1;
//	CSetup2 dPage2;
	CSetup3 dPage3;
	CSetup4 dPage4;

	dPage1.m_bHavePower = g_bHavePower;
	dPage1.m_bManuP     = g_bManuP;
	dPage1.m_strPowType = g_strPowType;
	dPage1.m_strPowCom  = g_strPowCom;

	dPage1.m_iSouType	= g_iSouType;
	dPage1.m_strSouComm	= g_strSouComm;
	dPage1.m_bAuto		= g_bAutoLamp;
	dPage1.m_iPerTime	= g_iPerTime;

	dPage1.m_fSetCurr	= g_fSetCurr;
	dPage1.m_fSetVol	= g_fSetVol;
	

// 	dPage2.m_strSTCType = m_strSTC_ShowName;
// 	dPage2.m_strSTCCom  = m_strSTCCom;
// 	dPage2.m_bDemo      = g_bDemo;

	dPage3.m_iTestListCalSele = g_SPEC.m_iTestListCalSele;

	dPage3.m_iAutoTime2 = m_iAutoLimitTime2;
	dPage3.m_iTestType  = m_iTestType;
	dPage3.m_iBin       = m_iBin;
	dPage3.m_iLED       = m_iParType;
	dPage3.m_iMode      = m_iMode;
	dPage3.m_iLamp      = m_iLamp;
	dPage3.m_iPEType    = m_iPE;
	dPage3.m_bPhoto     = m_bPhoto;//注意
	///////////////////////////////////////////////
	dPage3.m_bTrig      = m_bTrig;
	dPage3.m_iTrigMode  = m_iTrigMode;
	if(m_fPulseTime<=0)
		m_fPulseTime=1;
	dPage3.m_fPulseTime = m_fPulseTime;
	if(m_iPulseNum<0)
		m_iPulseNum=1;
	dPage3.m_iPulseNum  = m_iPulseNum;
	///////////////////////////////////////////////
	dPage3.m_fDistance  = m_fDistance;
	dPage3.m_fIntK      = m_fIntK;
	dPage3.m_iSeleL     = m_iSeleL;

	dPage3.m_bAtt = m_bAtt;
	dPage3.m_iAtt = m_iAtt;

	dPage3.m_fWL1		= g_fSpect1;
	dPage3.m_fWL2		= g_fSpect2;
	dPage3.m_bUseListCalSele = g_SPEC.m_bUseListCalSele;
	dPage3.m_iSigType= g_SPEC.m_iSigType;

//	dPage2.m_iDateType = m_iDateType;

	GetTimeTestData(g_strCurPath+"MutiTime.dat");
	dPage4.m_bCheckTimeTest = m_bTimeTest;

	sheet.AddPage(&dPage3);
	sheet.AddPage(&dPage4);
//	sheet.AddPage(&dPage2);
	sheet.AddPage(&dPage1);

	if(sheet.DoModal()==IDCANCEL)
		return;
//	BOOL bCh_STC=(m_strSTCCom!=dPage2.m_strSTCCom);

	g_bHavePower	= dPage1.m_bHavePower;
	g_bManuP		= dPage1.m_bManuP;
	g_strPowType	= dPage1.m_strPowType;
	g_strPowCom		= dPage1.m_strPowCom;	

	g_iSouType		= dPage1.m_iSouType;
	g_strSouComm	= dPage1.m_strSouComm;
	g_bAutoLamp		= dPage1.m_bAuto;
	g_iPerTime		= dPage1.m_iPerTime;

//	g_iSetType		= dPage1.m_iSetType;
	g_fSetCurr		= dPage1.m_fSetCurr;
	g_fSetVol		= dPage1.m_fSetVol;

// 	g_iSetType2		= dPage1.m_iSetType2;
// 	g_fSetCurr2		= dPage1.m_fSetCurr2;
// 	g_fSetVol2		= dPage1.m_fSetVol2;

// 	m_strSTC_ShowName	= dPage2.m_strSTCType;
// 	m_strSTCCom		= dPage2.m_strSTCCom;
// 	g_bDemo			= dPage2.m_bDemo;
// 	m_iDateType		= dPage2.m_iDateType;

	m_iAutoLimitTime2 = dPage3.m_iAutoTime2;
	m_iTestType       = dPage3.m_iTestType;
	m_iBin            = dPage3.m_iBin;
	m_iParType        = dPage3.m_iLED;
	m_iMode           = dPage3.m_iMode;
	m_iLamp           = dPage3.m_iLamp;
	m_iPE             = dPage3.m_iPEType;

//	T_SPECT1=g_fSpect1;
//	T_SPECT2=g_fSpect2;

	m_bPhoto          = dPage3.m_bPhoto;
	m_bTrig           = dPage3.m_bTrig;
	m_iTrigMode       = dPage3.m_iTrigMode;
	m_fPulseTime	  = dPage3.m_fPulseTime;
	m_iPulseNum		  = dPage3.m_iPulseNum;
	m_fDistance       = dPage3.m_fDistance;
	m_fIntK           = dPage3.m_fIntK;
	m_iSeleL          = dPage3.m_iSeleL;

	m_bAtt = dPage3.m_bAtt;
	m_iAtt = dPage3.m_iAtt;

	g_SPEC.m_iTestListCalSele = dPage3.m_iTestListCalSele;
	g_SPEC.m_bUseListCalSele = dPage3.m_bUseListCalSele;

	if(g_SPEC.m_bUseListCalSele == FALSE)
		g_SPEC.m_iTestListCalSele = 0;

	if(dPage3.m_fWL1>dPage3.m_fWL2)
	{
		g_fSpect2		  = dPage3.m_fWL1;
		g_fSpect1		  = dPage3.m_fWL2;
	}
	else
	{
		g_fSpect1		  = dPage3.m_fWL1;
		g_fSpect2		  = dPage3.m_fWL2;
	}
	if(g_fSpect1<T_SPECT1)
		g_fSpect1=T_SPECT1;
	if(g_fSpect2>T_SPECT2)
		g_fSpect2=T_SPECT2;

	g_SPEC.m_iSigType = dPage3.m_iSigType;

	m_bTimeTest = dPage4.m_bCheckTimeTest;

//	BOOL bR;

	SaveInitData();
	//先读取波长数据
	ReadWaveData();

	SaveTimeTestData(g_strCurPath+"MutiTime.dat");

//	CCmdTarget::EndWaitCursor();
}

BOOL CCSPEC_PRO::Get_PL()
{
	BOOL bR;
	
	/////////////////////////////////////////////
	//读取光谱定标文件
	CString sTemp;
	sTemp="spectrumcal.cal";    //低
	
	// 亮度测试有视场角
	CString strL;
	strL="";
	if(m_iTestType==0)
	{
	}
	if(m_iTestType==1)
	{
	}
	if(m_iTestType==2)
	{
		strL="LX_";
	}
	if(m_iTestType==3)
	{
		strL="I_";
	}
	
	sTemp = strL + sTemp;
	
	sTemp = g_strCurPath+"Cal\\Li_"+sTemp;
	
	
	CString strPosName;
	if(g_bOpenMulitCalSpectrum)
	{
		if(m_iTestListCalSele > 0)
		{
			strPosName.Format("CAL_%03d", m_iTestListCalSele);
			sTemp.Replace(g_strCurPath + "Cal", g_strCurPath + "Cal\\" + strPosName);
		}
	}
	
	bR=SP_Load(sTemp);
	if(!bR)
	{
		if(g_bEnglish)
		{
			AfxMessageBox("Can not find the cal file!\n"+sTemp,NULL,MB_ICONINFORMATION);
		}
		else
		{
			AfxMessageBox("未找到光谱定标文件!\n"+sTemp,NULL,MB_ICONINFORMATION);
		}
	}
	
	return bR;
}

float CCSPEC_PRO::MA_Ave(int iAveN,int iCurN,int iMaxN, float fData[])
{
	float fTemp=0;
	int i;
	int iTemp;
	iTemp=(int)(iCurN-iAveN/2);
	if(iTemp<=0)
	{
		iTemp=0;
	}
	if(iTemp>=iMaxN)
		iTemp=(int)(iCurN-iAveN/2-1);
	for(i=0;i<iAveN;i++)
		fTemp=fTemp+fData[iCurN-i-iTemp];

	fTemp=fTemp/iAveN;
	return fTemp;
}

BOOL CCSPEC_PRO::CopyFile(const char *lpSrcFilename, const char *lpDestFilename, int nBuffersize)
{
	CFile Out, In;
	int nFilesize;
	char *lpBuffer;

	// Attempt to open the input file.
	if( !In.Open( lpSrcFilename, CFile::modeRead ) ){
	//*	AfxMessageBox( "Could not open the input file." );
		return( FALSE );
		}

	DeleteFile(lpDestFilename);

	// Attempt to create the output file.
	if( !Out.Open( lpDestFilename,
		CFile::modeWrite | CFile::modeCreate ) ){
	//*	AfxMessageBox( "Could not open the output file." );
		return( FALSE );
		}

	// Create the copy buffer.
	lpBuffer = new char [nBuffersize];
	if( lpBuffer == NULL ){
	//*	AfxMessageBox( "Could not allocate the copy buffer." );
		return( FALSE );
		}

	// Get the input file status so that
	// we can set the output file's status
	// to the same. This will preserve
	// things such as time and date.
	CFileStatus rStatus;
	In.GetStatus( lpSrcFilename, rStatus );

	// Get file file size so that we know
	// when we're done copying.
	nFilesize = In.GetLength();

	while( nFilesize > 0 ){

		// Start off by assuming
		// we'll read in enough bytes
		// to fill the buffer.
		int nSize = nBuffersize;

		// If the number of bytes remaining
		// isn't enough to fill the
		// buffer, adjust the size.
		if( nSize > nFilesize )
			nSize = nFilesize;

		// Read in the bytes and make
		// sure we catch any exceptions
		// that are thrown.
		try{
			In.Read( lpBuffer, nSize );
			}
		catch( CFileException *e ){

			// Format a message from
			// the system.
			char *lpMsgBuf;
			if( FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM,
				NULL, e->m_lOsError,
				MAKELANGID( LANG_NEUTRAL,
					SUBLANG_DEFAULT ),
				(LPSTR) &lpMsgBuf, 0, NULL ) > 0 ){
				AfxMessageBox( lpMsgBuf );
				LocalFree( lpMsgBuf );
				}

			// Free the exception and
			// return.
			e->Delete();
			return( FALSE );
			}

		// Write out the bytes and make
		// sure we catch any exceptions
		// that are thrown.
		try{
			Out.Write( lpBuffer, nSize );
			}

		catch( CFileException *e ){

			// Format a message from
			// the system.
			char *lpMsgBuf;
			if( FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM,
				NULL, e->m_lOsError,
				MAKELANGID( LANG_NEUTRAL,
					SUBLANG_DEFAULT ),
				(LPSTR) &lpMsgBuf, 0, NULL ) > 0 ){
				AfxMessageBox( lpMsgBuf );
				LocalFree( lpMsgBuf );
				}

			// Free the exception and
			// return.
			e->Delete();
			return( FALSE );
			}

		nFilesize -= nSize;

		}

	// Close the output file so that the
	// SetStatus() function won't fail.
	Out.Close();
	CFile::SetStatus( lpDestFilename, rStatus );

	// Delete the buffer.
	delete [] lpBuffer;

	return( TRUE );
}

CString CCSPEC_PRO::sFormat(float fD, int iN)
{
	if(fD==0)
		return "0";

	// 格式化
	CString strTemp,temp;
	if(fD<1)
		strTemp.Format("%.6f",fD);
	else
		strTemp.Format("%.4f",fD);

	// 小数点位置
	int iPointPos = -1;

	// 长度
	int iL;
	iL = strTemp.GetLength();

	// 找到最后一位 iE
	int iE = 0;
	for(int i=0;i<iL;i++)
	{
		temp = strTemp.GetAt(i);

		if(temp==".")
			iPointPos = i;

		// 对于第1个零、+, - ,都不计数，
		else if((temp != "0"&& temp != "-" && temp != "+")||(iE > 0))
			iE++;
		// 最后一位找到
		if(iE >= iN)
			break;
	}

	// 格式化转化
	if(iPointPos != -1)
		temp.Format("%%.%df",i-iPointPos);
	else
		temp.Format("%%.%df",0);
	strTemp.Format(temp,fD);

	return strTemp;
}

BOOL CCSPEC_PRO::PHO_SaveCal(CString sPathName)
{
	//保存光通量定标文件
	FILE *fp;
	if((fp=fopen(sPathName,"wt"))==NULL)
	{
		if(g_bEnglish)
			AfxMessageBox("Can't save file.",NULL,MB_ICONSTOP);
		else
			AfxMessageBox("不能保存文件.",NULL,MB_ICONSTOP);
		return FALSE;
	}
	else
	{
		fprintf(fp,"Phose:\n");
		fprintf(fp,"StaPho :%.3f\n",m_CAL_fStaPho[0]);
		fprintf(fp,"PhoTime:%.3f\n",m_CAL_fPhoTime[0]);
		fprintf(fp,"PhoseK :%.9f\n\n",m_CAL_fPhoK[0]);

		fprintf(fp,"StaPho :%.3f\n",m_CAL_fStaPho[1]);
		fprintf(fp,"PhoTime:%.3f\n",m_CAL_fPhoTime[1]);
		fprintf(fp,"PhoseK :%.9f\n\n",m_CAL_fPhoK[1]);

		fprintf(fp,"StaPho :%.3f\n",m_CAL_fStaPho[2]);
		fprintf(fp,"PhoTime:%.3f\n",m_CAL_fPhoTime[2]);
		fprintf(fp,"PhoseK :%.9f\n\n",m_CAL_fPhoK[2]);

		CTime tNow;
		tNow=CTime::GetCurrentTime();
		CString sNow=tNow.Format("%Y-%m-%d %I:%M");
		fprintf(fp,sNow);

		fprintf(fp,"\n\n");
		fprintf(fp,"SN.:%s\n",m_strSN);
		fprintf(fp,"VER:%s\n",m_strSoftVer);
		fprintf(fp,"EPROM:%s\n",m_strEprom);
		fprintf(fp,"Driver:%s\n",m_strDriver);
	}
	fclose(fp);
//	if(g_bEnglish)
//		AfxMessageBox("Save the data succeed!");
//	else
//		AfxMessageBox("数据保存成功!");
	return TRUE;
}

BOOL CCSPEC_PRO::PHO_OpenCal(CString sPathName)
{
	//读取光通量定标文件
	FILE *fp;
	if((fp=fopen(sPathName,"rt"))==NULL)
	{
		if(g_bEnglish)
			AfxMessageBox("Can't creat file.",NULL,MB_ICONSTOP);
		else
			AfxMessageBox("未找到相对亮度定标文件.",NULL,MB_ICONSTOP);
		return FALSE;
	}
	else
	{
		fscanf(fp,"Phose:\n");
		fscanf(fp,"StaPho :%f\n",&m_CAL_fStaPho[0]);
		fscanf(fp,"PhoTime:%f\n",&m_CAL_fPhoTime[0]);
		fscanf(fp,"PhoseK :%f\n\n",&m_CAL_fPhoK[0]);

		fscanf(fp,"StaPho :%f\n",&m_CAL_fStaPho[1]);
		fscanf(fp,"PhoTime:%f\n",&m_CAL_fPhoTime[1]);
		fscanf(fp,"PhoseK :%f\n\n",&m_CAL_fPhoK[1]);

		fscanf(fp,"StaPho :%f\n",&m_CAL_fStaPho[2]);
		fscanf(fp,"PhoTime:%f\n",&m_CAL_fPhoTime[2]);
		fscanf(fp,"PhoseK :%f\n\n",&m_CAL_fPhoK[2]);
	}
	fclose(fp);
	return TRUE;
}

void CCSPEC_PRO::ReMoveJF_Spec(float fInPL[], float fSpect1, float fInInterval, int iInN)
{
	float fWL[10001];
	float fPL[10001];
	int   iN = iInN;
	int   i;
	int   iMax = 0;

	//pe-5去掉460位置谱线
	float m_fJFWL = 460.0f;

	for(i = 0 ; i < iN ; i++)
	{
		fWL[i] = fSpect1 + fInInterval * i;
		fPL[i] = fInPL[i];
	}
	//找到激发光谱的位置
	for(i = 1;i < iN ; i++)
	{
		if(fWL[i - 1] < m_fJFWL && fWL[i] >= m_fJFWL)
		{
			iMax = i;
		}
	}

	//起始波长大于460 不去除
	if(fSpect1 > m_fJFWL)
	{
		return;
	}
	//找到460附近的 50nm 最小值
	float fMin	 = fPL[iMax];
	float fMinWL = fSpect1 + iMax * fInInterval;
	int   iMin	 = iMax + 20;
	for(i = iMax; i < (iMax + 500); i++)
	{
		if(fPL[i] <= fMin)
		{
			fMin	= fPL[i];
			fMinWL	= fSpect1 + i * fInInterval;
			iMin	= i;
		}
	}
	
	float fW1 = fSpect1 + fInInterval * iMin;
	float fW2 = fSpect1 + fInInterval * (iMin + 1);
	float fP1 = fPL[iMin];
	float fP2 = fPL[iMin + 1];
	
	double fx[1000];
	double fy[1000];
	for(i = iMin; i < iMin + 500; i++)
	{
		fx[i - iMin] = (double)(fSpect1 + i * fInInterval);
		fy[i - iMin] = (double)(fPL[i]);
	}
	fx[0] = 460;
	fy[0] = 0;
	
	for(i = 0; i < iMin; i++)
	{
		float fWL = fSpect1 + i * fInInterval;
		fPL[i] = (float)(Lagrange_New(fx,fy, 500, fSpect1 + i * fInInterval));
		
		if(fPL[i] < 0)
		{
			fPL[i] = 0;
		}
	}
	
	//去除补充数据不正确的数值
	int		iTempMin	= 0;
	float	fTempMinRel = fPL[0];
	
	for(i = 0; i < iMin; i++)
	{
		if(fTempMinRel > fPL[i])
		{
			fTempMinRel = fPL[i];
			iTempMin	= i;
		}
	}
	
	for(i = 0; i < iTempMin; i++)
	{
		fPL[i] = 0;
	}
	
	//都插值成原来间隔nm数据
	for(i = 0; i < iN; i++)
	{
		fWL[i] = fSpect1 + i * fInInterval;
	}
	
	for(i = 0; i < iInN; i++)
	{
		fInPL[i] = g_doData.NewInt_float(fWL, fPL, iN, fSpect1 + fInInterval * i);
		if(fInPL[i] <= 0)
		{
			fInPL[i] = 0;
		}
	}
	
	//归一数据 (!!! 不能去归一的：胡余兵!!!!)
	if(0)
	{
		float fMax = 0;
		for(i = 0; i < iInN; i++)
		{
			if(fInPL[i] > fMax)
			{
				fMax = fInPL[i];
			}
		}
		if(fMax <= 0)
		{
			fMax = 1.0f;
		}
		
		for(i = 0; i < iInN; i++)
		{
			fInPL[i] = fInPL[i] / fMax;
		}
	}
/*
	float fMin	= fPL[iMax];
	float fMinWL= fWL[iMax];
	int   iMin	= iMax;
	for(i = iMax ; i < (iMax+500) ; i++)
	{
		if(i >= (iN-1))
		{
			break;
		}

		if(fPL[i] < fMin)
		{
			fMin	= fPL[i];
			fMinWL	= fWL[i];
			iMin	= i;
		}
	}

	float fW1 = fMinWL;
	float fW2 = fWL[iMin+1];
	float fP1 = fMin;
	float fP2 = fPL[iMin+1];
	for(i=0;i<iMin;i++)
	{
		float fL = fWL[i];
		fPL[i]   = fP1 + (fL-fW1)*(fP2-fP1)/(fW2-fW1);
		if(fPL[i] < 0)
		{
			fPL[i] = 0;
		}
	}

	for(i=0;i<iN;i++)
	{
		fInPL[i] = fPL[i];
	}

	return;*/
}

BOOL CCSPEC_PRO::GetDetectorK(CString sPath)
{
	FILE *fp;
	if((fp=fopen(sPath+"Cal\\DetctorK.dat","rt"))==0)
	{
		return FALSE;
	}
	else
	{
		m_arra_fDetctorK.RemoveAll();
		m_arra_fDetctorWL.RemoveAll();
		while(1)
		{
			float f1,f2;
			fscanf(fp,"%f %f\n",&f1,&f2);
			if(f1==-1&&f2==-1)
				break;
			m_arra_fDetctorK.Add(f2);
			m_arra_fDetctorWL.Add(f1);
		}

		int iN;
		iN=m_arra_fDetctorK.GetSize();
		for(int i=0;i<iN;i++)
		{
			m_fDecWL[i]=m_arra_fDetctorWL.GetAt(i);
			m_fDecK[i]=m_arra_fDetctorK.GetAt(i);
		}

		fclose(fp);
	}
	return TRUE;
}

BOOL CCSPEC_PRO::GetPheK(CString sPath)
{
	FILE *fp;
	if((fp=fopen(sPath+"Cal\\ModePhe.dat","rt"))==0)
	{
		return FALSE;
	}
	else
	{
		int i = 0;
		for (i = 0; i < 100; i++)
		{
			m_arra_fPheWL.RemoveAll();
			m_arra_fPheK[i].RemoveAll();
			m_arra_fPheAD[i].RemoveAll();
		}
		int iNumPhe;
		fscanf(fp,"ModeNum:%d\n",&iNumPhe);
		for (i = 0 ; i < iNumPhe; i++)
		{
			float fModeWL;
			int iNumWL;
			fscanf(fp,"WL:%f\n KNum:%d\n",&fModeWL,&iNumWL);
			m_arra_fPheWL.Add(fModeWL);

			for (int j = 0; j < iNumWL; j++)
			{
				float f1,f2;
				fscanf(fp,"%f %f\n",&f1,&f2);
				m_arra_fPheAD[i].Add(f1);
				m_arra_fPheK[i].Add(f2);
			}
		}
		fclose(fp);
	}
	return TRUE;
}

BOOL CCSPEC_PRO::GetPheK_High(CString sPath)
{
	FILE *fp;
	if((fp=fopen(sPath+"Cal\\ModePhe_high.dat","rt"))==0)
	{
		return FALSE;
	}
	else
	{
		m_arra_fPheK_High.RemoveAll();
		m_arra_fPheAD_High.RemoveAll();
		while(1)
		{
			float f1,f2;
			fscanf(fp,"%f %f\n",&f1,&f2);
			if(f1==-1&&f2==-1)
				break;
			m_arra_fPheK_High.Add(f2);
			m_arra_fPheAD_High.Add(f1);
		}
		
		fclose(fp);
	}
	return TRUE;
}

BOOL CCSPEC_PRO::WL_Inter_Get(CString strPathName)
{
	//读取光通量定标文件
	FILE *fp;
	if((fp=fopen(strPathName,"rt"))==NULL)
	{
		return FALSE;
	}
	else
	{
		int i;
		fscanf(fp,"Color:%d\n",&m_iWLInter);
		if(T_SPECT1==200)
		{
			m_iWLInter++;
			m_fWLInter[0]=360;
		}
		for(i=0;i<m_iWLInter;i++)
		{
			if(T_SPECT1==200)
				fscanf(fp,"%f\n",&m_fWLInter[i+1]);
			else
				fscanf(fp,"%f\n",&m_fWLInter[i]);
		}
		if(T_SPECT2>780)
		{
			m_iWLInter++;
			m_fWLInter[3]=780;
		}

		int iTemp;
		//读取快速色片位置
		fscanf(fp,"Mode Color1:%d\n",&m_iHave_Color_K);
		for(i=0;i<m_iHave_Color_K;i++)
		{
			fscanf(fp,"%d %d\n",&iTemp,&m_iWZ_Color_K[i]);
		}

		float fWLS[10];
		float fWLE[10];
		//读取精确色片位置
		fscanf(fp,"Mode Color2:%d\n",&m_iHave_Color_J);
		for(i=0;i<m_iHave_Color_J;i++)
		{
			fscanf(fp,"%d %d %f %f\n",&iTemp,&m_iWZ_Color_J[i],&fWLS[i],&fWLE[i]);
		}

		for(i=0;i<m_iHave_Color_J;i++)
		{
			int iSele=0;
			for(int j=0;j<m_iPixN;j++)
			{
				if(SPEC_Pix2WL(j)>=fWLE[i])
				{
					iSele=j;
					break;
				}
			}
			if(i==0)
			{
				m_HAAS.m_iPixS[i]=0;
				m_HAAS.m_iPixE[i]=iSele;
			}
			else
			{
				m_HAAS.m_iPixS[i]=m_HAAS.m_iPixE[i-1]+1; //+1
				m_HAAS.m_iPixE[i]=iSele;
			}
		}
		m_HAAS.m_iPixE[i-1]=m_HAAS.m_iPixN-1;
	}

	fclose(fp);
	return TRUE;
}

//
// 读取视场角信息
//
BOOL CCSPEC_PRO::ViewL_Load(CString strPathName)
{
	FILE *fp;
	if((fp=fopen(strPathName,"rt"))==NULL)
		return FALSE;
	else
	{
		char szBuffer[256];

		fscanf(fp,"Num:%d\n",&m_iViewL_Num);
		for(int i=0;i<m_iViewL_Num;i++)
		{
			fscanf(fp,"%s\n",&szBuffer);
			m_strViewL_Name[i] = szBuffer;
		}
	}
	fclose(fp);
	return TRUE;
}

BOOL CCSPEC_PRO::ViewL_Save(CString strPathName)
{
	FILE *fp;
	if((fp=fopen(strPathName,"wt"))==NULL)
		return FALSE;
	else
	{
		fprintf(fp,"Num:%d\n",m_iViewL_Num);
		for(int i=0;i<m_iViewL_Num;i++)
			fprintf(fp,"%s\n",m_strViewL_Name[i]);

		fprintf(fp,"\n\n注意:每行的名称中间不能有空格,不要出现汉字,取中英文通用的名称!\n",m_strViewL_Name[i]);
	}
	fclose(fp);
	return TRUE;
}

//胡余兵 ( 2008-10-30 09:36:38 ) 
//
// 不等间隔
//
double CCSPEC_PRO::Lagrange_New(double x[], double y[], int n, float t)
{
	int i,j,k,m;
	double z,s,xi,xj;
	z=0.0;
	if(n<1)
	{
		return(z);
	}
	
	if(n==1)
	{
		z=y[0];
		return(z);
	}
	if(n==2)
	{
		z=(y[1]*(t-x[0])-y[0]*(t-x[1]))/(x[1]-x[0]);
		return(z);
	}
	if(t>x[0])
	{
		for(i=0;i<n;i++)
		{
			if(x[i]>=t)
				break;
		}
	}
	else
		i=0;

	k=(i-2)<0?0:i-2;
	m=(i+1)>n-1?n-1:i+1;
	for(i=k;i<=m;i++)
	{
		s=1.0;
		xi=x[i];
		for(j=k;j<=m;j++)
		{
			if(j!=i)
			{
				xj=x[j];
				s*=(t-xj)/(xi-xj);
			}
		}
		z+=s*y[i];
	}
	
	return(z);
}

BOOL CCSPEC_PRO::Read_SP_K()
{
	//光谱定标数据
	FILE *fp;
	CString strPathName=g_strCurPath+"CAL\\Att_K.dat";
	if((fp=fopen(strPathName,"rt"))==NULL)
		return FALSE;
	else
	{
		int iN;
		fscanf(fp,"%d %f %f\n",&iN,&m_fSpkTime1,&m_fSpkTime2);

		for(int i=0;i<iN;i++)
			fscanf(fp,"%f %f\n",&m_fRelN[i],&m_fRelR[i]);
	}
	fclose(fp);

	return TRUE;
}

BOOL CCSPEC_PRO::GetStaLamp(CString strPathName)
{
	FILE *fp;
	if((fp=fopen(strPathName,"rt"))==NULL)
	{
		return FALSE;
	}
	else
	{
		unsigned char a[256];
		fscanf(fp,"NAME:%s\n",a);
		m_strLampName=a;
		if(a[0]=='A')
		{
			REF_TYPE=STA_A;
			fscanf(fp,"TC:%fK\n",&m_fA_Tc);
			fclose(fp);
			return TRUE;
		}
		else
		{
			REF_TYPE=STA_D65;
		}
		fscanf(fp,"NUM:%d\n",&m_iStaLampN);
		for(int i=0;i<m_iStaLampN;i++)
		{
			float f1,f2;
			fscanf(fp,"%f %f\n",&f1,&f2);
			m_fD65_WL[i]=f1;
			m_fD65_PL[i]=f2;
		}
		fclose(fp);
		return TRUE;
	}
}

BOOL CCSPEC_PRO::GetTouData(CString strPathName)
{
	FILE *fp;
	if((fp=fopen(strPathName,"rt"))==NULL)
	{
		m_f_Ttou_R=1;
		return FALSE;
	}
	else
	{
		fscanf(fp,"Tou:%f\n",&m_f_Ttou_R);
		if(m_f_Ttou_R>1)
			m_f_Ttou_R=1;
		if(m_f_Ttou_R<0)
			m_f_Ttou_R=1;
		fclose(fp);
		return TRUE;
	}
}

BOOL CCSPEC_PRO::ReadRouData(CString strPathName)
{
	FILE *fp;
	if((fp=fopen(strPathName,"rt"))==NULL)
	{
		return FALSE;
	}
	else
	{
		fscanf(fp,"NUM:%d\n",&m_iRrouNum);
		for(int i=0;i<m_iRrouNum;i++)
		{
			fscanf(fp,"%f %f\n",&m_fRrou_WL[i],&m_fRrou_PL[i]);
		}
		fclose(fp);
		return TRUE;
	}
}

BOOL CCSPEC_PRO::ReadRouDark(CString strPathName)
{
	FILE *fp;
	if((fp=fopen(strPathName,"rt"))==NULL)
	{
		return FALSE;
	}
	else
	{
		fscanf(fp,"NUM:%d\n",&m_iRDarkNum);
		for(int i=0;i<m_iRDarkNum;i++)
		{
			fscanf(fp,"%f %f\n",&m_fRDark_WL[i],&m_fRDark_PL[i]);
		}
		fclose(fp);
		return TRUE;
	}
}

BOOL CCSPEC_PRO::SP_Save_UV(CString strPathName)
{
	//光谱定标数据
	FILE *fp;
	if((fp=fopen(strPathName,"wt"))==NULL)
		return FALSE;
	else
	{
		fprintf(fp,"Time:%.2f\n",m_SP_fIntTime_UV);
		fprintf(fp,"%.1f %.1f %.3f\n",m_SP_fSpect1_UV,m_SP_fSpect2_UV,m_fInterval);
		fprintf(fp,m_SP_strDate_UV+"\n");

		int iN=(int)((m_SP_fSpect2_UV-m_SP_fSpect1_UV)/m_fInterval+1+0.5f);
		for(int i=0;i<iN;i++)
		{
			fprintf(fp,"%.1f %.5e\n",m_SP_fSpect1_UV+i*m_fInterval,m_SP_fK_UV[i]);
		}
	}
	fclose(fp);
	return TRUE;
}

BOOL CCSPEC_PRO::SP_Load_UV(CString strPathName)
{
	//光谱定标数据
	FILE *fp;
	if((fp=fopen(strPathName,"rt"))==NULL)
		return FALSE;
	else
	{
		fscanf(fp,"Time:%f\n",&m_SP_fIntTime_UV);
		fscanf(fp,"%f %f %f\n",&m_SP_fSpect1_UV,&m_SP_fSpect2_UV,&m_fInterval);

		char a[256];
		fscanf(fp,"%s\n",a);
		m_SP_strDate_UV=a;

		int iN=(int)((m_SP_fSpect2_UV-m_SP_fSpect1_UV)/m_fInterval+1+0.5f);
//		float fKUV[2001];
		float fWL[10001];
		for(int i=0;i<iN;i++)
		{
			fscanf(fp,"%f %f\n",&fWL[i],&m_SP_fK_UV[i]);
		}
/*
		//差值为0.1nm
		m_fInterval=0.1f;
		int iN1=(int)((m_SP_fSpect2_UV-m_SP_fSpect1_UV)/m_fInterval+1+0.5f);
		float fLamda;
		for(i=0;i<iN1;i++)
		{
			fLamda=m_SP_fSpect1_UV+0.1f*i;
			m_SP_fK_UV[i]=(float)g_doData.NewInt_float(fWL,fKUV,iN,fLamda);
		}
*/	}
	fclose(fp);
	return TRUE;
}

float CCSPEC_PRO::CIE_CalcYI(float x, float y)
{
// 计算黄色度
//
	if(y<=0)
		return 0.0f;
	
	float z=1-x-y;
	return 100*(1.28f*x-1.06f*z)/y;
}

float CCSPEC_PRO::CIE_CalcW(float x, float y, float x0, float y0)
{
// 计算白度
// x ,y   样品色坐标
// x0,y0  完全漫射体在CIE1931的色品坐标
// 其实只对D65照射下的白度才有效
	float Y=100*y/y0;   // 要修改,完全漫射体y0是100,对应y是Y
	return Y+800*(x0-x)+1700*(y0-y);
}

void CCSPEC_PRO::CIE_xLuv(float x, float y, float x0, float y0, float &xL, float &xu, float &xv, float &xSuv, float &xCuv, float &xHuv)
{
// 计算L*,u*,v* (为计算色差)
// xLuv  明度
// xSuv  饱和度
// xCuv  彩度
// xHuv  色调
	float z,z0;
	z  = 1 - x - y;
	z0 = 1 -x0 - y0;
	
	float u_, v_;
	float u0_, v0_;
	
	u_   = 4 * x / (x + 15 * y + 3 * z);
	v_   = 9 * y / (x + 15 * y + 3 * z);
	
	u0_  = 4 * x0 / (x0 + 15 * y0 + 3 * z0);
	v0_  = 9 * y0 / (x0 + 15 * y0 + 3 * z0);
	
	xL = (float)(116 * (pow((y / y0), 1 / 3.0f)) - 16);
	xu = 13 * xL * (u_ - u0_);
	xv = 13 * xL * (v_ - v0_);
	
	double d;
	d = pow((u_ - u0_), 2) + pow((v_ - v0_), 2);
	d = pow(d, 0.5);
	
	xSuv= (float)(13 * d);
	
	d	= pow(xu, 2) + pow(xv, 2);
	d	= pow(d, 0.5);
	xCuv= (float)(d);
	d	= atan2(v_ - v0_, u_ - u0_);
	xHuv= (float)(d * 180 / 3.1415926535);
	if(xHuv < 0)
	{
		xHuv = 360 + xHuv;
	}
	
	return;
}

float CCSPEC_PRO::CIE_DEuv(float x1, float y1, float x2, float y2, float x0, float y0)
{
	float xL1,xu1,xv1;
	float xL2,xu2,xv2;
	float xSuv,xCuv,xHuv;
	
	CIE_xLuv(x1,y1,x0,y0,xL1,xu1,xv1,xSuv,xCuv,xHuv);
	CIE_xLuv(x2,y2,x0,y0,xL2,xu2,xv2,xSuv,xCuv,xHuv);
	
	double dE;
	dE = pow(xL1 - xL2, 2) + pow(xu1 - xu2, 2) + pow(xv1 - xv2, 2);
	dE = pow(dE,0.5);
	return (float)dE;
}

void CCSPEC_PRO::DoProAvg(double fData[], int iN, int iDoN)
{
	if(iDoN <= 1)
	{
		return;
	}

	int i,j;
	float *pData = new float[iN];
	int iTempN;

	// 1.滑动平均处理
	for(i = 0; i < iN; i++)
	{
		iTempN		= 0;
		pData[i]	= 0;
		for(j = i - iDoN; j <= i + iDoN; j++)
		{
			if(j >= 0 && j < iN)
			{
				pData[i] += (float)(fData[j]);
				iTempN++;
			}
		}
		pData[i] /= iTempN;
	}

	// 送出数据
	for(i = 0; i < iN; i++)
	{
		fData[i] = pData[i];
	}

	delete [] pData;
}


void CCSPEC_PRO::ReadInitData()
{
	//读取初始化设置的数据
	CString strTemp;
	CString strSection	= "MySpec SETUP";

	CString strTestType	= "TestType";
	CString strAutoLimit= "AutoLimit";
	CString strBIN		= "BIN";
	CString strPAR		= "PAR";
	CString strMODE		= "MODE";
	CString strDemo		= "DEMO";
	CString strbAtt		= "BATT";
	CString striAtt		= "IATT";
	CString strLamp		= "LAMP";
	CString strPE		= "PE";
	CString strbTrig	= "bTrig";
	CString strTrigMode	= "TrigMode";
	CString strDistance	= "Distance";
	CString strIntK		= "INT K";
	CString strWL1		= "WL1";
	CString strWL2		= "WL2";

	m_iTestType			= AfxGetApp()->GetProfileInt(strSection,strTestType,1);
	m_iAutoLimitTime2	= AfxGetApp()->GetProfileInt(strSection,strAutoLimit,5000);
	m_iBin				= AfxGetApp()->GetProfileInt(strSection,strBIN,0);
	m_iParType			= AfxGetApp()->GetProfileInt(strSection,strPAR,0);
	m_iMode				= AfxGetApp()->GetProfileInt(strSection,strMODE,0);
	g_bDemo				= AfxGetApp()->GetProfileInt(strSection,strDemo,FALSE);
	m_bAtt				= AfxGetApp()->GetProfileInt(strSection,strbAtt,FALSE);
	m_iAtt				= AfxGetApp()->GetProfileInt(strSection,striAtt,0);
	m_iLamp				= AfxGetApp()->GetProfileInt(strSection,strLamp,0);
	m_iPE				= AfxGetApp()->GetProfileInt(strSection,strPE,0);
	m_bTrig				= AfxGetApp()->GetProfileInt(strSection,strbTrig,0);
	m_iTrigMode			= AfxGetApp()->GetProfileInt(strSection,strTrigMode,0);
	strTemp				= AfxGetApp()->GetProfileString(strSection,strDistance,"0.1");
	m_fDistance			= (float)atof(strTemp);
	strTemp				= AfxGetApp()->GetProfileString(strSection,strIntK,"1.0");
	m_fIntK				= (float)atof(strTemp);
	strTemp				= AfxGetApp()->GetProfileString(strSection,strWL1,"380");
	g_fSpect1			= (float)atof(strTemp);
	strTemp				= AfxGetApp()->GetProfileString(strSection,strWL2,"780");
	g_fSpect2			= (float)atof(strTemp);

	if(g_fSpect1 < T_SPECT1)
	{
		g_fSpect1 = T_SPECT1;
	}

	if(g_fSpect2 > T_SPECT2)
	{
		g_fSpect2 = T_SPECT2;
	}

			strSection	= "Trig Setup";
	CString strPulseTime= "PulseTime";
	CString strPulseNum	= "PulseNum";

	strTemp		= AfxGetApp()->GetProfileString(strSection,strPulseTime, "10");
	m_fPulseTime= (float)atof(strTemp);
	m_iPulseNum	= AfxGetApp()->GetProfileInt(strSection,strPulseNum,1);
	m_bTrig		= FALSE;
}

void CCSPEC_PRO::SaveInitData()
{
	//记录设置数据
	CString strSection   = "MySpec SETUP";

	CString strTestType  = "TestType";
	CString strAutoLimit = "AutoLimit";
	CString strBIN       = "BIN";
	CString strPAR       = "PAR";
	CString strMODE      = "MODE";
	CString strDemo      = "DEMO";
	CString strbAtt      = "BATT";
	CString striAtt      = "IATT";
	CString strLamp      = "LAMP";
	CString strPE        = "PE";
	CString strbTrig     = "bTrig";
	CString strTrigMode  = "TrigMode";
	CString strDistance  = "Distance";
	CString strIntK      = "INT K";
	CString strWL1       = "WL1";
	CString strWL2       = "WL2";

	AfxGetApp()->WriteProfileInt(strSection,strTestType,m_iTestType);
	AfxGetApp()->WriteProfileInt(strSection,strAutoLimit,m_iAutoLimitTime2);
	AfxGetApp()->WriteProfileInt(strSection,strBIN,m_iBin);
	AfxGetApp()->WriteProfileInt(strSection,strPAR,m_iParType);
	AfxGetApp()->WriteProfileInt(strSection,strMODE,m_iMode);
	AfxGetApp()->WriteProfileInt(strSection,strDemo,g_bDemo);
	AfxGetApp()->WriteProfileInt(strSection,strbAtt,m_bAtt);
	AfxGetApp()->WriteProfileInt(strSection,striAtt,m_iAtt);
	AfxGetApp()->WriteProfileInt(strSection,strLamp,m_iLamp);
	AfxGetApp()->WriteProfileInt(strSection,strPE,m_iPE);
	AfxGetApp()->WriteProfileInt(strSection,strbTrig,m_bTrig);
	AfxGetApp()->WriteProfileInt(strSection,strTrigMode,m_iTrigMode);
	CString strTemp;
	strTemp.Format("%f",m_fDistance);
	AfxGetApp()->WriteProfileString(strSection,strDistance,strTemp);
	strTemp.Format("%f",m_fIntK);
	AfxGetApp()->WriteProfileString(strSection,strIntK,strTemp);
	strTemp.Format("%f",g_fSpect1);
	AfxGetApp()->WriteProfileString(strSection,strWL1,strTemp);
	strTemp.Format("%f",g_fSpect2);
	AfxGetApp()->WriteProfileString(strSection,strWL2,strTemp);

		strSection		= "Trig Setup";
	CString strPulseTime= "PulseTime";
	CString strPulseNum	= "PulseNum";
	strTemp.Format("%f",m_fPulseTime);
	AfxGetApp()->WriteProfileString(strSection,strPulseTime,strTemp);
	AfxGetApp()->WriteProfileInt(strSection,strPulseNum,m_iPulseNum);
}

void CCSPEC_PRO::ReadWaveData()
{
	return;
	//读取波长文件
	BOOL bR;
	if(1)
	{
		if(m_iMode==0)
		{
			if(m_iBin==0)
				bR=WL2_Load(g_strCurPath+"Cal\\C2_wavecor_0.dat");
			if(m_iBin==1)
				bR=WL2_Load(g_strCurPath+"Cal\\C2_wavecor_1.dat");
			if(m_iBin==2)
				bR=WL2_Load(g_strCurPath+"Cal\\C2_wavecor_2.dat");
			if(m_iBin==3)
				bR=WL2_Load(g_strCurPath+"Cal\\C2_wavecor_3.dat");
		}
		else
		{
			if(m_iBin==0)
				bR=WL2_Load(g_strCurPath+"Cal\\C2_wavecor_4.dat");
			if(m_iBin==1)
				bR=WL2_Load(g_strCurPath+"Cal\\C2_wavecor_5.dat");
			if(m_iBin==2)
				bR=WL2_Load(g_strCurPath+"Cal\\C2_wavecor_6.dat");
			if(m_iBin==3)
				bR=WL2_Load(g_strCurPath+"Cal\\C2_wavecor_7.dat");
		}

/*		CString strTemp;
		strTemp.Format("%d %d", m_iMode, m_iBin);
		AfxMessageBox(strTemp);*/

		if(bR)
		{
			WL_Inter_Get(g_strCurPath+"CAL\\Color.dat");
			return;
		}
	}

	if(m_iMode==0)
	{
		if(m_iBin==0)
			bR=WL_Load(g_strCurPath+"Cal\\wavecor_0.dat");
		if(m_iBin==1)
			bR=WL_Load(g_strCurPath+"Cal\\wavecor_1.dat");
		if(m_iBin==2)
			bR=WL_Load(g_strCurPath+"Cal\\wavecor_2.dat");
		if(m_iBin==3)
			bR=WL_Load(g_strCurPath+"Cal\\wavecor_3.dat");
	}
	else
	{
		if(m_iBin==0)
			bR=WL_Load(g_strCurPath+"Cal\\wavecor_4.dat");
		if(m_iBin==1)
			bR=WL_Load(g_strCurPath+"Cal\\wavecor_5.dat");
		if(m_iBin==2)
			bR=WL_Load(g_strCurPath+"Cal\\wavecor_6.dat");
		if(m_iBin==3)
			bR=WL_Load(g_strCurPath+"Cal\\wavecor_7.dat");
	}
	if(!bR)
	{
		bR=WL_Load(g_strCurPath+"Cal\\wavecor.dat");
		if(!bR)
		{
			if(g_bEnglish)
				AfxMessageBox("Can not find wavecor.dat!",NULL,MB_ICONINFORMATION);
			else
				AfxMessageBox("未找到定标文件 wavecor.dat!",NULL,MB_ICONINFORMATION);
		}
	}
	WL_Inter_Get(g_strCurPath+"CAL\\Color.dat");
	return;
}

void CCSPEC_PRO::SaveWaveData()
{
	//保存波长数据
	if(m_iMode==0)
	{
		if(m_iBin==0)
			WL_Save(g_strCurPath+"Cal\\wavecor_0.dat");
		if(m_iBin==1)
			WL_Save(g_strCurPath+"Cal\\wavecor_1.dat");
		if(m_iBin==2)
			WL_Save(g_strCurPath+"Cal\\wavecor_2.dat");
		if(m_iBin==3)
			WL_Save(g_strCurPath+"Cal\\wavecor_3.dat");
	}
	else
	{
		if(m_iBin==0)
			WL_Save(g_strCurPath+"Cal\\wavecor_4.dat");
		if(m_iBin==1)
			WL_Save(g_strCurPath+"Cal\\wavecor_5.dat");
		if(m_iBin==2)
			WL_Save(g_strCurPath+"Cal\\wavecor_6.dat");
		if(m_iBin==3)
			WL_Save(g_strCurPath+"Cal\\wavecor_7.dat");
	}
	WL_Save(g_strCurPath+"Cal\\wavecor.dat");
}

BOOL CCSPEC_PRO::GetTimeTestData(CString strPathName)
{
	FILE *fp;
	if((fp=fopen(strPathName,"rt"))==0)
	{
		m_bTimeTest=FALSE;
		return FALSE;
	}
	else
	{
		fscanf(fp,"TimeTest:%d\n",&m_bTimeTest);
		int iNum=0;
		fscanf(fp,"NUM:%d\n",&iNum);
		m_arra_iTimeNum.RemoveAll();
		for(int i=0;i<iNum;i++)
		{
			int iTemp;
			fscanf(fp,"%d\n",&iTemp);
			m_arra_iTimeNum.Add(iTemp);
		}
		fclose(fp);
	}

	return TRUE;
}

BOOL CCSPEC_PRO::SaveTimeTestData(CString strPathName)
{
	FILE *fp;
	if((fp=fopen(strPathName,"wt"))==0)
	{
		return FALSE;
	}
	else
	{
		fprintf(fp,"TimeTest:%d\n",m_bTimeTest);

		int iNum=m_arra_iTimeNum.GetSize();
		fprintf(fp,"NUM:%d\n",iNum);

		for(int i=0;i<iNum;i++)
		{
			int iTemp=m_arra_iTimeNum[i];
			fprintf(fp,"%d\n",iTemp);
		}
		fclose(fp);
	}

	return TRUE;
}

BOOL CCSPEC_PRO::ReadTrigSet(CString strPathName)
{
	FILE *fp;
	if((fp=fopen(strPathName,"rt"))==0)
	{
		return FALSE;
	}
	else
	{
		fscanf(fp,"OkTime:%d\n",&g_iOkTime);
		fscanf(fp,"OkNum:%d\n",&g_iOkNum);
		fscanf(fp,"FailTime:%d\n",&g_iFailTime);
		fscanf(fp,"FailNum:%d\n",&g_iFailNum);
		fclose(fp);
	}
	return TRUE;
}

BOOL CCSPEC_PRO::WL2_Load(CString strPathName)
{
	FILE *fp;
	if((fp=fopen(strPathName,"rt"))==NULL)
		return FALSE;
	else
	{
		char a[256];
		fscanf(fp,"%s\n",a);
		CString strTemp=a;
		if(strTemp!="WLCOR")
		{
			fclose(fp);	
			return FALSE;
		}
		
		fscanf(fp,"PixN=%d\n",&m_iPixN);
		
		m_C2_fStaWL.RemoveAll();
		m_C2_fPix.RemoveAll();
		while(1)
		{
			float fWL;
			float fPix;
			fscanf(fp,"%f %f\n",&fWL,&fPix);
			if(fWL>0&&fPix>0)
			{
				m_C2_fStaWL.Add(fWL);
				m_C2_fPix.Add(fPix);
			}
			else
			{
				break;
			}
		}
	}
    fclose(fp);	
	m_iCroWLType = 1;
	SPEC_Correct();
	return TRUE;
}

void CCSPEC_PRO::SPEC_CalcPhoEff(int iN, float fWL[], float fRelP[], float fPower, BOOL bAuto, 
								 float fSpectB1, float fSpectB2, float fSpectY1, float fSpectY2,
								 float &fMol,float &fEff1, float &fEff2)
{
	//  bAuto 自动找寻波段 在波段设置基础上
	//  fWL:波长 iN:点数 fRelP绝对光谱(W/nm) fPower:灯功率
	//	给出具有绝对单位而不是归一化的光谱图（客户要求）；
	//	光量子数:各波长的光谱功率（单位：W）乘以与波长成正比的函数，380nm处为3.17，780处为6.51，光量子数的单位为umol/s;
	//  对光谱图中荧光粉的发光功率进行积分，对光谱图中蓝光的发光功率进行积分，两者相比得到荧光粉转换效率（根据客户要求）；
    //  对光谱图中荧光粉的发光功率进行积分，除以LED电功率。
	fMol  = 0; //光量子数  单位为umol/s
	fEff1 = 0; //转换效率
	fEff2 = 0; //转换光效 lm/W

	int i;
	float fInterval = fWL[1] - fWL[0];

	if(bAuto)
	{
		//有点理想化 先找480前的最大值 再找480后的最大值 然后找中间的最小值
		float fWLFJ = 480.0f;
		float fMax1 = fRelP[0];
		int iMax1   = 0;
		for(i = 0; i < iN; i++)
		{
			if(fWL[i] < fWLFJ)
			{
				if(fMax1 < fRelP[i])
				{
					iMax1 = i;
					fMax1 = fRelP[i];
				}
			}
		}

		float fMax2 = fRelP[0];
		int iMax2   = 0;
		for(i = 0; i < iN; i++)
		{
			if(fWL[i] > fWLFJ)
			{
				if(fMax2 < fRelP[i])
				{
					iMax2 = i;
					fMax2 = fRelP[i];
				}
			}
		}
		float fMin = fRelP[iMax1];
		int iMin = iMax1;
		for(i = iMax1; i < iMax2; i++)
		{

			if(fMin > fRelP[i])
			{
				fMin = fRelP[i];
				iMin = i;
			}
		}
		
		fSpectB1 = 0;
		fSpectB2 = iMin * fInterval + fWL[0];
		fSpectY1 = fSpectB2;
		fSpectY2 = fWL[iN - 1];
	}

	int iB1 = (int)((fSpectB1 - fWL[0]) / fInterval + 0.5f);
	if(iB1 <= 0)
	{
		iB1 = 0;
	}
	if(iB1 >= iN)
	{
		iB1 = iN - 1;
	}

	int iB2 = (int)((fSpectB2 - fWL[0]) / fInterval + 0.5f);
	if(iB2 <= 0)
	{
		iB2 = 0;
	}
	if(iB2 >= iN)
	{
		iB2 = iN - 1;
	}

	int iY1 = (int)((fSpectY1 - fWL[0]) / fInterval + 0.5f);
	if(iY1 <= 0)
	{
		iY1 = 0;
	}
	if(iY1 >= iN)
	{
		iY1 = iN - 1;
	}

	int iY2 = (int)((fSpectY2 - fWL[0]) / fInterval + 0.5f);
	if(iY2 <= 0)
	{
		iY2 = 0;
	}
	if(iY2 >= iN)
	{
		iY2 = iN - 1;
	}

	//计算光量子数
	fMol = 0;
	int iB = (int)((g_SPEC.m_fReGeWL1 - fWL[0]) / fInterval + 0.5f);
	int iE = (int)((g_SPEC.m_fReGeWL2 - fWL[0]) / fInterval + 0.5f);
	if(iB < 0)
		iB = 0;
	if(iE > iN - 1)
	{
		iE = iN - 1;
	}
	for(i = iB; i <= iE; i++)
	{
		float fK = (float)((6.51 - 3.17)/(780-380) * (fWL[i] - 380) + 3.17);
		fMol = fMol + fRelP[i] * fInterval * fK;
	}

	//计算效率
	float fBP = 0; //蓝光功率
	for(i = iB1; i <= iB2; i++)
	{
		fBP = fBP + fRelP[i] * fInterval;
	}

	float fYP = 0; //荧光粉发光功率  黄光部分
	for(i = iY1; i <= iY2; i++)
	{
		fYP = fYP + fRelP[i] * fInterval;
	}

	if(fBP > 0)
	{
		fEff1 = fYP / fBP; //黄光/蓝光
	}
	else
	{
		fEff1 = 0;
	}

	if(fPower > 0)
	{
		fEff2 = fYP / fPower; //黄光/电功率
	}
	else
	{
		fEff2 = 0;
	}
	return;
}

BOOL CCSPEC_PRO::FILE_GetBadPoint(CString sPathName)
{
	FILE *fp;
	if((fp=fopen(sPathName,"rt"))==0)
	{
		m_iBadNum=0;
		return FALSE;
	}
	else
	{
		fscanf(fp,"NUM:%d\n",&m_iBadNum);
		for(int i=0;i<m_iBadNum;i++)
			fscanf(fp,"%d\n",&m_iBadPoint[i]);
		
		fscanf(fp,"TIME:%d\n",&m_iBadTime);
		fclose(fp);
	}
	return FALSE;
}

BOOL CCSPEC_PRO::GetYFStaLamp(CString strPathName, int iEorFlux)
{
	FILE *fp;
	if((fp=fopen(strPathName,"rt"))==NULL)
	{
		return FALSE;
	}
	else
	{
		REF_TYPE = STA_D65;
		char a[256];
		char b[256];
		fscanf(fp,"Model:%s SN:%s\n",a,b);
		//		CString sType   = a;
		//		CString sNumber = b;
		fscanf(fp,"Voltage:%fV Current:%fA\n",&m_fStaVol,&m_fStaCurr);

		float fK = 1.0f;

		CString strType = "";
		if(iEorFlux == 0)
		{
			strType ="uW/cm2/nm";
			fK = 0.01f;
		}
		if(iEorFlux == 1)
		{
			strType ="W/nm";
			fK = 1.0f;
		}

		char szBuffer[256];

		fscanf(fp,"Distance:%fm  Uint:%s\n",&m_fStaDis, szBuffer);

		CString strTempType = szBuffer;


		float fTemp1,fTemp2;
		m_iStaLampN=0;
		while(1)
		{
			fscanf(fp,"%f %f\n",&fTemp1,&fTemp2);
			if(fTemp1<=0&&fTemp2<=0)
				break;
			m_fD65_WL[m_iStaLampN] = fTemp1;
			m_fD65_PL[m_iStaLampN] = fTemp2 * fK;
			m_iStaLampN++;
			if(m_iStaLampN>10000)
				break;
		}
		fclose(fp);

		if(strTempType != strType)
		{
			if(g_bEnglish)
				AfxMessageBox("Lamp Files unit error, unit must :" + strType + "\n\n"+strPathName);
			else
				AfxMessageBox("Lamp标准灯单位有误, 单位应为:" + strType + "\n\n"+strPathName);
			return FALSE;
		}

		return TRUE;
	}
}

BOOL CCSPEC_PRO::CreateDirectoryMy(CString strPath)
{
	CreateDirectory(strPath,NULL);
	SHChangeNotify(SHCNE_MKDIR,SHCNF_PATH,strPath,0);
	return TRUE;
}

BOOL CCSPEC_PRO::CorrectXY(CSpectData &spData)
{
	return FALSE;
}

BOOL CCSPEC_PRO::NEW_CorrectXY(CSpectData &spData)
{
	return FALSE;
}

BOOL CCSPEC_PRO::MOD_SPEC_WL1(CString sPathName)
{
	FILE *fp;
	if((fp=fopen(sPathName+"\\Cal\\modWL1.dat","rt"))==0)
	{
		g_bModeWL1 = FALSE;
		return FALSE;
	}
	else
	{
		char a[256];
		fscanf(fp,"MOD:%s\n",&a);
		CString strTemp;
		strTemp = a;
		if(strTemp == "ON")
		{
			g_bModeWL1 = TRUE;
		}
		else
		{
			g_bModeWL1 = FALSE;
		}
		float f1,f2;
		fscanf(fp,"WL1:%f %f\n",&f1,&f2);
		if(f1 == T_SPECT1)
		{
			g_fModSpect1 = f2;
		}	
		fclose(fp);
	}
	return TRUE;
}

BOOL CCSPEC_PRO::HassDarkPro(float *pDark, int iCCDNum, float fAD_Range, int iContiNum, int &iErrorNum, float *pProDark)
{
	iErrorNum = 0;
	float *pDark_DecPre = new float[iCCDNum];
	float *pDark_DecAft = new float[iCCDNum];
	int *pDarkPos_DecPre = new int[iCCDNum];
	int *pDarkPos_DecAft = new int[iCCDNum];
	int *pDarkPos_NeedInter = new int[iCCDNum];
	int *pStartArray_NeedInter = new int[iCCDNum];
	int *pEndArray_NeedInter = new int[iCCDNum];
	int iNeedInterNum = 0;
	int i,j;

	for (i = 0; i < iCCDNum; i++)
	{
		pDark_DecPre[i] = (i > 0) ? (pDark[i] - pDark[i - 1]) : (pDark[i + 1] - pDark[i]);
		pDark_DecAft[i] = (i < iCCDNum - 1)? (pDark[i] - pDark[i + 1]) : (pDark[i] - pDark[i - 1]);
		pDarkPos_DecPre[i] = 1;
		pDarkPos_DecAft[i] = 1;
		pDarkPos_NeedInter[i] = 1;
	}

	for (i = 0; i < iCCDNum; i ++)
	{
		pProDark[i] = pDark[i];
		if (i > 0)
		{
			if (pDark_DecPre[i] >= fAD_Range && pDark_DecPre[i - 1] < fAD_Range)
			{
				pDarkPos_DecPre[i] = 0;
			}
		}
		if (i < iCCDNum - 1)
		{
			if (pDark_DecAft[i] >= fAD_Range && pDark_DecAft[i + 1] < fAD_Range)
			{
				pDarkPos_DecAft[i] = 0;
			}
		}
	}

	for (i = 0; i < iCCDNum; i ++)
	{
		if (pDarkPos_DecPre[i] == 1)
		{
			continue;
		}
		for (int j = i; j < iCCDNum; j ++)
		{
			if (pDarkPos_DecAft[j] == 1)
			{
				continue;
			}
			if (j - i + 1 <= iContiNum)
			{
				pStartArray_NeedInter[iNeedInterNum] = i;
				pEndArray_NeedInter[iNeedInterNum] = j;
				for (int k = i; k <= j; k++)
				{
					iErrorNum ++;
					pDarkPos_NeedInter[k] = 0;
				}
				iNeedInterNum ++;
			}
			break;
		}
	}

	for ( i = 0; i < iNeedInterNum; i++)
	{
		for ( j = pStartArray_NeedInter[i]; j <= pEndArray_NeedInter[i]; j ++)
		{
			if (pStartArray_NeedInter[i] == 0)
			{
				pProDark[j] =  pDark[pEndArray_NeedInter[i] + 1] 
				+ (pDark[pEndArray_NeedInter[i] + 2] - pDark[pEndArray_NeedInter[i] + 1]) 
					* (j - pEndArray_NeedInter[i] - 1 );
			}
			else  
			{
				if (pEndArray_NeedInter[j] == iCCDNum - 1)
				{
					pProDark[j] =  pDark[pStartArray_NeedInter[i] - 1] 
					+ (pDark[pStartArray_NeedInter[i] - 1] - pDark[pStartArray_NeedInter[i] - 2]) 
						* (j - pStartArray_NeedInter[i] + 1 );
				}
				else
				{
					pProDark[j] = pDark[pStartArray_NeedInter[i] - 1] + 
						(pDark[pEndArray_NeedInter[i] + 1] - pDark[pStartArray_NeedInter[i] - 1])
						/ (pEndArray_NeedInter[i] - pStartArray_NeedInter[i] + 2) * (j -  pStartArray_NeedInter[i] + 1);
				}  
			}

		}
	}
	
	for (i = 0; i < iNeedInterNum; i++)
	{
		for (j = pStartArray_NeedInter[i]; j <= pEndArray_NeedInter[i]; j ++)
		{
			pDarkPos_NeedInter[j] = 0;
			if (pStartArray_NeedInter[i] == 0)
			{
				pProDark[j] =  pDark[pEndArray_NeedInter[i] + 1] 
					+ (pDark[pEndArray_NeedInter[i] + 2] - pDark[pEndArray_NeedInter[i] + 1]) 
					* (j - pEndArray_NeedInter[i] - 1 );
			}
			else
			{
				if (pEndArray_NeedInter[j] == iCCDNum - 1)
				{
					pProDark[j] =  pDark[pStartArray_NeedInter[i] - 1]
						+ (pDark[pStartArray_NeedInter[i] - 1] - pDark[pStartArray_NeedInter[i] - 2])
						* (j - pStartArray_NeedInter[i] + 1 );
				}
				else
				{
					pProDark[j] = pDark[pStartArray_NeedInter[i] - 1] + 
						(pDark[pEndArray_NeedInter[i] + 1] - pDark[pStartArray_NeedInter[i] - 1])
						/ (pEndArray_NeedInter[i] - pStartArray_NeedInter[i] + 2) * (j -  pStartArray_NeedInter[i] + 1);
				}  
			}

		}
	}
/*
	FILE *fp;
	if (_wfopen_s(&fp, g_strPath + L"ProDark.info",L"wt"))
	{

	}
	else
	{
		CString strTemp;
		strTemp.Format(L"总处理波峰: %d",iNeedInterNum);
		fprintf_s(fp,"%s",CString2Char(strTemp));
		fprintf_s(fp,"\n");
		fprintf_s(fp,"%16s",CString2Char(L"点名称"));
		fprintf_s(fp,"%16s",CString2Char(L"原始暗电流"));
		fprintf_s(fp,"%16s",CString2Char(L"处理暗电流"));
		fprintf_s(fp,"%16s",CString2Char(L"处理位置")); 
		fwprintf_s(fp,L"\n");
		for (int i = 0; i < iCCDNum; i++)
		{
			fwprintf_s(fp,L"%16d",i);
			fwprintf_s(fp,L"%16.1f",pDark[i]);
			fwprintf_s(fp,L"%16.1f",pProDark[i]);
			fwprintf_s(fp,L"%16d",pDarkPos_NeedInter[i]);
			fwprintf_s(fp,L"\n");

		}

		fclose(fp);
	}*/

	delete []pDark_DecPre;
	delete []pDark_DecAft;
	delete []pDarkPos_DecPre;
	delete []pDarkPos_DecAft;
	delete []pDarkPos_NeedInter;
	delete []pStartArray_NeedInter;
	delete []pEndArray_NeedInter;
	return TRUE;
}


BOOL CCSPEC_PRO::ReadJMFK(CString strPathName)
{
	FILE *fp;
	if((fp=fopen(strPathName,"rt"))==NULL)
	{
		m_bMoveJM = FALSE;
		m_fJMFK = 1;
		return FALSE;
	}
	else
	{
		fscanf(fp,"JMFK:%f\n", &m_fJMFK);

		fclose(fp);
		return TRUE;
	}
}
