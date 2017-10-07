// SPEC_HAAS.cpp: implementation of the CSPEC_HAAS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "SPEC_HAAS.h"
#include "Global_MySpec.h"
#include "math.h"

#include "MainFrm.h"
#include "SpectraArsenal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int g_iPerColor;

extern BOOL g_bEnglish;
extern CString g_strDriverVer;
extern float g_fSpect1;
extern float g_fSpect2;
extern BOOL  g_bDemo;
extern CString g_strCurPath;

extern int g_iSeleMode;
BOOL g_bHaveOpen = FALSE;

CSPEC_HAAS::CSPEC_HAAS()
{
	m_iPixS[0]	= 0;
	m_iPixE[0]	= 250;
	m_iPixS[1]	= 250;
	m_iPixE[1]	= 500;
	m_iPixS[2]	= 500;
	m_iPixE[2]	= 750;
	m_iPixS[3]	= 750;
	m_iPixE[3]	= 1023;
	g_iPerColor	= -1;
	m_iPixN		= 2048;
}

CSPEC_HAAS::~CSPEC_HAAS()
{
}

BOOL CSPEC_HAAS::Init(int &iPixN, int &AD)
{
	if(!g_bHaveOpen)
	{
		m_iPixN	= 2048;//iPixN;
		
		int iR;
		iR = SA_OpenSpectrometers();
		if(iR >= 0)
		{
			//读取波长系数
			double dc[4];
			iR = SA_GetWavelengthCalibrationCoefficients(0,dc);
			if (iR == SA_API_SUCCESS)
			{
				g_SPEC.m_Icor  = dc[0];
				g_SPEC.m_C1cor = dc[1];
				g_SPEC.m_C2cor = dc[2];
				g_SPEC.m_C3cor = dc[3];//
				for (int i = 0; i < m_iPixN; i++)
				{
					g_SPEC.m_iLambdaPos[i] = i;
					g_SPEC.m_fLambdaPos[i] = dc[0]
						+ dc[1] * i
						+ dc[2] * i * i
						+ dc[3] * i * i * i;
				}
				
				g_bHaveOpen = TRUE;
				
				char *sSN;
				sSN = SA_GetSerialNumber(0);
				g_SPEC.m_strSN = sSN;
				return TRUE;
			}
		}
		else
		{
			SA_CloseSpectrometers();
			g_bHaveOpen = FALSE;
			return FALSE;
		}
	}
	else
	{
		return TRUE;
	}
	g_bHaveOpen = FALSE;
	
	return FALSE;
}

BOOL CSPEC_HAAS::HAAS_Scan(float fIntTime, float fAD[], BOOL &bOverAD)
{
	//只采样一次
	int i;
	int iR = 0;
	int iGetNum;
	double dGetAD[2048];
	iR = SA_GetSpectum(0, dGetAD, iGetNum);
	if(iR == SA_API_FAIL)
	{
		return FALSE;
	}
	m_iPixN = iGetNum;

	int iFilterBW = 1;
	double SpectumNew[2048];
	
	if (iFilterBW > 1)
	{
		for( i = 0 ;i<=iFilterBW;i++)
			SpectumNew[i] = dGetAD[i];
		
		for( i  = iGetNum - iFilterBW ;i<= iGetNum - 1;i++)
			SpectumNew[i] = dGetAD[i];
		
		for (i = iFilterBW+1 ;i<= iGetNum - iFilterBW;i++)
		{
			double tempSum = 0.0;
			for (int j = (i-iFilterBW) ; j<= (i+iFilterBW) ;j++)
				tempSum = tempSum + dGetAD[j];
			
			SpectumNew[i] = tempSum / (2 * iFilterBW + 1);
		}
		
		for (i = 0; i < iGetNum; i++)
		{
			dGetAD[i] = SpectumNew[i];
		}
	}

	for (i = 0; i < m_iPixN; i++)
	{
		fAD[i] = (float)(dGetAD[i]);
	}
	
	float fADTemp[2048];
	for (i = 0; i < m_iPixN; i++)
	{
		if (i == 0 || i == (m_iPixN - 1))
		{
			fADTemp[i] = fAD[i];
		}
		else
		{
			fADTemp[i] = (fAD[i - 1] + fAD[i] + fAD[i+1]) / 3;
		}
	}

	for (i = 0; i < m_iPixN; i++)
	{
		fAD[i] = fADTemp[i];
	}
// 	//此处将AD值做处理
// 	//第一步 取出2048/4个AD值
// 	float fADTemp[2048];
// 	float fPixN[2048];
// 	int iN = 0;
// 	for (i = 0; i < m_iPixN+1; i++)
// 	{
// 		float fSum = 0;
// 		if (i%4==0)
// 		{
// 			if ((i - 2) > 0 && (i + 2) < m_iPixN - 1)
// 			{
// 				fSum = fAD[i - 2] + fAD[i - 1] + fAD[i] + fAD[i+1] + fAD[i+2];
// 				fSum = fSum / 5;
// 			}
// 			if ((i + 2) >= m_iPixN - 1)
// 			{
// 				fSum = fAD[m_iPixN - 1];
// 			}
// 			if (i == 0)
// 			{
// 				fSum = fAD[0];
// 			}
// 			fADTemp[iN] = fSum;
// 			fPixN[iN] = i*1.0f;
// 			iN++;
// 		}
// 	}
// 	
// 	//将AD值差值成2048点
// 	for (i = 0; i < m_iPixN; i++)
// 	{
// 		fAD[i] = g_doData.NewInt_float(fPixN,fADTemp,iN,i*1.0f);
// 	}
	
	return TRUE;
}

BOOL CSPEC_HAAS::Scan(float fIntTime, int iAveN, float fAD[],BOOL &bOverAD,BOOL bNote)
{
	//说明:iCCDMode   CCD类型是64还是128;
	//     iTestMode  测试类型是快速精确还是典型
	//     iBin       BIN3 BIN10 OR BIN FULL
	//     fIntTime   积分时间
	//     iTrigType  普通模式 或 触发模式
	float fTemp[5000];
	int i;
	for(i=0;i<m_iPixN;i++)
	{
		fAD[i]   = 0;
		fTemp[i] = 0;
	}
	int iR;
	CString strTemp;
	iR = SA_SetIntegrationTime(0, (int)(fIntTime * 1000));
	if(iR == SA_API_FAIL)
	{
		return FALSE;
	}

	iR = SA_SetAverageTimes(0,1);
	if(iR == SA_API_FAIL)
	{
		return FALSE;
	}

	if(1)
	{
		for(int j=0;j<iAveN;j++)
		{
			if(g_bEnglish)
			{
				if(iAveN>1)
					strTemp.Format("Testing %d...",j+1);
				else
					strTemp.Format("Testing ...");
			}
			else
			{
				if(iAveN>1)
					strTemp.Format("正在快速测试 %d[%.0fms]...",j+1,fIntTime);
				else
					strTemp.Format("正在快速测试 [%.0fms]...",fIntTime);
			}
			if(bNote)
				CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,255));

			BOOL bR=HAAS_Scan(fIntTime,fAD,bOverAD);
			if(!bR)
			{
				return FALSE;
			}

			for(i=0;i<m_iPixN;i++)
				fTemp[i]=fAD[i]+fTemp[i];
			Sleep(100);
		}
		for(i=0;i<m_iPixN;i++)
			fAD[i]=fTemp[i]/iAveN;
		CMainFrame::ShowNote("",TRUE,RGB(255,0,255));
		return TRUE;
	}

	CMainFrame::ShowNote("",TRUE,RGB(255,0,255));
	return TRUE;
}

BOOL CSPEC_HAAS::UnInit()
{
	return TRUE;
}

double CSPEC_HAAS::PRO_NewInt(double *xa, double *ya, int n, double x)
{
	/////////////////////////////////////////
	////牛顿插值
	int i, k;
	double u;

	if(xa[0]>xa[1]) //数组从大到小
	{
		for(i=1; i<=n-2; i++)
		{
			if( x >= xa[i] )
			{
				k=i;
				break;
			}
			else
				k=n-1;
		}
	}
	else  //从小到大
	{
		for(i=1; i<=n-2; i++)
		{
			if( x <= xa[i] )
			{
				k=i;
				break;
			}
			else
				k=n-1;
		}
	}
	u=(x-xa[k-1])/(xa[k]-xa[k-1]);
	return ya[k-1]+u*(ya[k]-ya[k-1]);
}

BOOL CSPEC_HAAS::PRO_ModAD(int iN, float fAD[])
{
	int i,iMax=0;
	float fMax=fAD[0];
	for(i=0;i<iN;i++)
	{
		if(fAD[i]>fMax)
		{
			fMax=fAD[i];
			iMax=i;
		}
	}
	int iL=iMax;
	float fHalfP=0.8f;
	for(i=iMax;i>=50;i--)
	{
		if(fAD[i]<=(fAD[iMax]*fHalfP))
		{
			iL=i;
			break;
		}
	}
	int iR=iMax;
	for(i=iMax;i<=iMax+50;i++)
	{
		if(fAD[i]<=(fAD[iMax]*fHalfP))
		{
			iR=i;
			break;
		}
	}
	iMax=(iR+iL)/2;
	for(i=0;i<iN;i++)
	{
		if(i==0)
			fAD[i]=(2*fAD[i+1]+fAD[i+2]);
		else if(i==(iN-1))
			fAD[i]=(2*fAD[i-2]+fAD[i-1]);
		else
			fAD[i]=(fAD[i-1]+fAD[i+1])/2;
	}
	return TRUE;
}

BOOL CSPEC_HAAS::SetSN(CString strSN,int iBaudRate)
{
	////设置序列号
	BOOL bR = TRUE;
//	bR=HAAS_SN_Write(strSN,iBaudRate);
	return bR;
}

BOOL CSPEC_HAAS::ReadSN(CString &strSN)
{
	////读取序列号
	BOOL bR = TRUE; 
	BYTE buf[256];
	
	for(int i = 0; i < 256; i++)
	{
		buf[i] = 0x00;
	}

//	bR=HAAS_SN_Read(buf);
	if(!bR)
	{
		return FALSE;
	}

	CString sTemp;
	CString sStr;
	strSN = "";
	int iNum = 7;
	iNum = 7;

	for(i = 0; i < iNum; i++)
	{
		sStr.Format("%c",buf[i]);
		strSN=strSN+sStr;
	}
	return bR;
}

BOOL CSPEC_HAAS::ReadEppData()
{
//	if(g_iSeleMode == 1)
//		return FALSE;
	////读取仪器中定标系数
	BOOL bR = TRUE; 
	BYTE buf[256];
	
	for(int i = 0; i < 256; i++)
	{
		buf[i] = 0x00;
	}
	
	int iHaveNum = 13 * 4 + 2;
	int iAddrS = 0;
//	bR=HAAS_Read_EPP(buf,iHaveNum,iAddrS);
	if(!bR)
	{
		return FALSE;
	}

	if(buf[0]!=0x7B || buf[1]!=0x7B)
	{
		//未写过数据
		return FALSE;
	}
	int iN = 0;
	int iB = 2;
	g_SPEC.m_fZero[0] = Tof(&buf[iB + iN * 4]);
	iN++;
	g_SPEC.m_fZero[1] = Tof(&buf[iB + iN * 4]);
	iN++;
	g_SPEC.m_fZero[2] = Tof(&buf[iB + iN * 4]);
	iN++;
	g_SPEC.m_fZero[3] = Tof(&buf[iB + iN * 4]);
	iN++;
	g_SPEC.m_fRangeK[0] = Tof(&buf[iB + iN * 4]);
	iN++;
	g_SPEC.m_fRangeK[1] = Tof(&buf[iB + iN * 4]);
	iN++;
	g_SPEC.m_fRangeK[2] = Tof(&buf[iB + iN * 4]);
	iN++;
	g_SPEC.m_fR1 = Tof(&buf[iB + iN * 4]);
	iN++;
	g_SPEC.m_fR2 = Tof(&buf[iB + iN * 4]);
	iN++;
	g_SPEC.m_fR3 = Tof(&buf[iB + iN * 4]);
	iN++;
	g_SPEC.m_iRAD1 = (int)(Tof(&buf[iB + iN * 4]));
	iN++;
	g_SPEC.m_iRAD2 = (int)(Tof(&buf[iB + iN * 4]));
	iN++;
	g_SPEC.m_iRAD3 = (int)(Tof(&buf[iB + iN * 4]));
	iN++;

	return TRUE;
}

BOOL CSPEC_HAAS::SaveEppData()
{
//	if(g_iSeleMode == 1)
//		return FALSE;
	BOOL bR = TRUE; 
	BYTE buf[256];

	int iOut = 0;
	buf[iOut] = 0x7B;
	iOut++;
	buf[iOut] = 0x7B;
	iOut++;

	BYTE *pa;
	pa=(BYTE*)&g_SPEC.m_fZero[0];
	buf[iOut]=pa[3];
	iOut++;
	buf[iOut]=pa[2];
	iOut++;
	buf[iOut]=pa[1];
	iOut++;
	buf[iOut]=pa[0];
	iOut++;

	pa=(BYTE*)&g_SPEC.m_fZero[1];
	buf[iOut]=pa[3];
	iOut++;
	buf[iOut]=pa[2];
	iOut++;
	buf[iOut]=pa[1];
	iOut++;
	buf[iOut]=pa[0];
	iOut++;

	pa=(BYTE*)&g_SPEC.m_fZero[2];
	buf[iOut]=pa[3];
	iOut++;
	buf[iOut]=pa[2];
	iOut++;
	buf[iOut]=pa[1];
	iOut++;
	buf[iOut]=pa[0];
	iOut++;

	pa=(BYTE*)&g_SPEC.m_fZero[3];
	buf[iOut]=pa[3];
	iOut++;
	buf[iOut]=pa[2];
	iOut++;
	buf[iOut]=pa[1];
	iOut++;
	buf[iOut]=pa[0];
	iOut++;

	pa=(BYTE*)&g_SPEC.m_fRangeK[0];
	buf[iOut]=pa[3];
	iOut++;
	buf[iOut]=pa[2];
	iOut++;
	buf[iOut]=pa[1];
	iOut++;
	buf[iOut]=pa[0];
	iOut++;

	pa=(BYTE*)&g_SPEC.m_fRangeK[1];
	buf[iOut]=pa[3];
	iOut++;
	buf[iOut]=pa[2];
	iOut++;
	buf[iOut]=pa[1];
	iOut++;
	buf[iOut]=pa[0];
	iOut++;
	pa=(BYTE*)&g_SPEC.m_fRangeK[2];
	buf[iOut]=pa[3];
	iOut++;
	buf[iOut]=pa[2];
	iOut++;
	buf[iOut]=pa[1];
	iOut++;
	buf[iOut]=pa[0];
	iOut++;
	pa=(BYTE*)&g_SPEC.m_fR1;
	buf[iOut]=pa[3];
	iOut++;
	buf[iOut]=pa[2];
	iOut++;
	buf[iOut]=pa[1];
	iOut++;
	buf[iOut]=pa[0];
	iOut++;
	pa=(BYTE*)&g_SPEC.m_fR2;
	buf[iOut]=pa[3];
	iOut++;
	buf[iOut]=pa[2];
	iOut++;
	buf[iOut]=pa[1];
	iOut++;
	buf[iOut]=pa[0];
	iOut++;
	pa=(BYTE*)&g_SPEC.m_fR3;
	buf[iOut]=pa[3];
	iOut++;
	buf[iOut]=pa[2];
	iOut++;
	buf[iOut]=pa[1];
	iOut++;
	buf[iOut]=pa[0];
	iOut++;
	float f1;
	f1 = g_SPEC.m_iRAD1 * 1.0f;
	pa=(BYTE*)&f1;
	buf[iOut]=pa[3];
	iOut++;
	buf[iOut]=pa[2];
	iOut++;
	buf[iOut]=pa[1];
	iOut++;
	buf[iOut]=pa[0];
	iOut++;
	float f2;
	f2 = g_SPEC.m_iRAD2 * 1.0f;
	pa=(BYTE*)&f2;
	buf[iOut]=pa[3];
	iOut++;
	buf[iOut]=pa[2];
	iOut++;
	buf[iOut]=pa[1];
	iOut++;
	buf[iOut]=pa[0];
	iOut++;
	float f3;
	f3 = g_SPEC.m_iRAD3 * 1.0f;
	pa=(BYTE*)&f3;
	buf[iOut]=pa[3];
	iOut++;
	buf[iOut]=pa[2];
	iOut++;
	buf[iOut]=pa[1];
	iOut++;
	buf[iOut]=pa[0];
	iOut++;

	int iHaveNum = iOut;
	int iAddrS = 0;
//	bR=HAAS_Write_EPP(buf,iHaveNum,iAddrS);
	if(!bR)
	{
		return FALSE;
	}
	return TRUE;
}


float CSPEC_HAAS::Tof(BYTE *bb)
{
	float f;
	unsigned char *pa;
	pa=(unsigned char*)&f;
	*(pa+0)=bb[3];
	*(pa+1)=bb[2];
	*(pa+2)=bb[1];
	*(pa+3)=bb[0];
	return f;
}

BOOL CSPEC_HAAS::LoadWaveToGCS(double dc[])
{
	int iR;
	iR = SA_SetWavelengthCalibrationCoefficients(0,dc);
	if (iR != SA_API_SUCCESS)
	{
		return FALSE;
	}
	return TRUE;
}
