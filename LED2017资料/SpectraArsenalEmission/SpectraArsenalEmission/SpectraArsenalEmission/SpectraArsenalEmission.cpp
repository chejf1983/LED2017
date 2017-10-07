// SpectraArsenalEmission.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "SpectraArsenalEmission.h"

#include "ExGetColorParaDLL.h"
#include "SpectraArsenal.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CSpectraArsenalEmissionApp

BEGIN_MESSAGE_MAP(CSpectraArsenalEmissionApp, CWinApp)
END_MESSAGE_MAP()


// CSpectraArsenalEmissionApp 构造

CSpectraArsenalEmissionApp::CSpectraArsenalEmissionApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CSpectraArsenalEmissionApp 对象

CSpectraArsenalEmissionApp theApp;


// CSpectraArsenalEmissionApp 初始化

BOOL CSpectraArsenalEmissionApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
CString g_strCurPath;
float g_fCCor[4];

float g_fSPECT1 = 280.0f;
float g_fSPECT2 = 980.0f;

//double DarkSpect[2048];
//double DarkSpect_3LED[4][2048];
float g_fPixWL[2048];

float g_fIntTime = 0;
int	  g_iAveNum  = 0;
float g_fSP_fIntTime;
float g_fSP_fStaTc;
float g_fCAL_fStaFlux;
float g_fCAL_fFluxK;
float g_fSP_fK[10001];
float g_fSP_fSpect1;
float g_fSP_fSpect2;
float g_fSP_fInterval;

float NewInt_float(float *xa, float *ya, int n, float x)
{
	//牛顿插值

	int i, k;
	float u;
	k=1;
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
	u=(x-xa[k-1])/(xa[k]-xa[k-1]);
	return ya[k-1]+u*(ya[k]-ya[k-1]);
}

extern "C" __declspec(dllexport) int WINAPI JK_Emission_Close()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	SA_CloseSpectrometers();
	
	return SA_API_SUCCESS;
}

float g_fLamdaWL[1000];

extern "C" __declspec(dllexport) int WINAPI JK_Emission_Init()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	char Path[256];
	GetModuleFileName(NULL,Path,250);   
	* ( strrchr( Path, '\\' ) + 1 ) = '\0';	
	g_strCurPath=Path;

	BOOL bR;
	char sPass1[256];
	char sPass2[256];
	char sPath[256];
	CString strPass1;
	strPass1 = "NAHONG_TECH_NAHONG";
	CString strPass2;
	strPass2 = "GET_COLOR_PARA";
	int i;
	for (i = 0; i < strPass1.GetLength(); i++)
	{
		sPass1[i] = strPass1.GetAt(i);
	}
	sPass1[i] = 0x00;

	for (i = 0; i < strPass2.GetLength(); i++)
	{
		sPass2[i] = strPass2.GetAt(i);
	}
	sPass2[i] = 0x00;

	for (i = 0; i < g_strCurPath.GetLength(); i++)
	{
		sPath[i] = g_strCurPath.GetAt(i);
	}
	sPath[i] = 0x00;
	bR = NH_Init(sPass1,sPass2,sPath);
	if(!bR)
	{
		return SA_API_FAIL;
	}

	for (int i = 0; i < 401; i++)
	{
		g_fLamdaWL[i] = NH_GetV(380.0f + i);
	}

	double dCor[4];
	int iR;
	iR = SA_OpenSpectrometers();
	if(iR == SA_API_FAIL)
	{
		iR = SA_OpenSpectrometersForSerial();
		if(iR == SA_API_FAIL)
		{
			return SA_API_FAIL;
		}
	}
	
	iR = SA_GetWavelengthCalibrationCoefficients(0, dCor);
	if(iR == SA_API_FAIL)
	{
		return SA_API_FAIL;
	}

	for(i = 0; i < 4; i++)
	{
		g_fCCor[i] = (float)dCor[i];
	}

	int iPixNum = 0;
	iPixNum = SA_GetSpectrometerPixelsNumber(0);

	for(i = 0; i < iPixNum; i++)
	{
		g_fPixWL[i] = g_fCCor[0]
			+ g_fCCor[1] * i
			+ g_fCCor[2] * i * i
			+ g_fCCor[3] * i * i * i;
	}

	if(1)
	{
		int i,iN;
		//读取光谱定标数据
		FILE *fp;
		if(fopen_s(&fp, g_strCurPath + "Calibration\\Cal_standard.nh","rt"))
		{
			return SA_API_FAIL;
		}
		else
		{
			fscanf_s(fp,"%fK Time:%f\n",&g_fSP_fStaTc,&g_fSP_fIntTime);
			fscanf_s(fp,"%f %f %f\n",&g_fSP_fSpect1,&g_fSP_fSpect2,&g_fSP_fInterval);
			
			char a[256];
			fscanf_s(fp,"%s\n",a);
			CString SP_strDate=a;
			fscanf_s(fp,"%f  %f\n",&g_fCAL_fStaFlux, &g_fCAL_fFluxK);
			
			iN=(int)((g_fSP_fSpect2-g_fSP_fSpect1)/g_fSP_fInterval+1+0.5f);
			float fWL[10001];
			for(i=0;i<iN;i++)
			{
				float fAD;
				fscanf_s(fp,"%f %f %f\n",&fWL[i],&g_fSP_fK[i], &fAD);
			}
		}
		fclose(fp);
	}

	return SA_API_SUCCESS;
}

extern "C" __declspec(dllexport) int WINAPI JK_Emission_DarkStorage(float fIntTime, int iAveNum,int iFilterBW,float fDarkAD[])
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	int i, iR, iLength;
	int spectrometerIndex = 0;
	if (g_fIntTime != fIntTime)
	{
		iR = SA_SetIntegrationTime(0, (int)(fIntTime*1000));
		if(iR == SA_API_FAIL)
		{
			return SA_API_FAIL;
		}
		
		g_fIntTime = fIntTime;
	}
	
	if (g_iAveNum != iAveNum)
	{
		iR = SA_SetAverageTimes(0, iAveNum);
		if(iR == SA_API_FAIL)
		{
			return SA_API_FAIL;
		}
		
		g_iAveNum = iAveNum;
	}
	
	double Spectum[2048];
	double SpectumNew[2048];
	iR = SA_GetSpectum(spectrometerIndex, Spectum, iLength);
	if(iR == SA_API_FAIL)
	{
		return SA_API_FAIL;
	}
	
	if (iFilterBW > 1)
	{
		for( i = 0 ;i<=iFilterBW;i++)
			SpectumNew[i] = Spectum[i];

		for( i  = iLength - iFilterBW ;i<= iLength - 1;i++)
			SpectumNew[i] = Spectum[i];

		for (i = iFilterBW+1 ;i< iLength - iFilterBW;i++)
		{
			double tempSum = 0.0;
			for (int j = (i-iFilterBW) ; j<= (i+iFilterBW) ;j++)
				tempSum = tempSum + Spectum[j];

			SpectumNew[i] = tempSum / (2 * iFilterBW + 1);
		}

		for (i = 0; i < iLength; i++)
		{
			Spectum[i] = SpectumNew[i];
		}
	}
	
	for(i = 0; i < iLength; i++)
	{
		fDarkAD[i] = (float)(Spectum[i]);
	}
	return SA_API_SUCCESS;
}

extern "C" __declspec(dllexport) int WINAPI JK_Emission_GetData(TRIGGER_MODE TriggerMode,float fIntTime, int iAveNum,int iFilterBW, float fDx,float fDy, float fSetWL1,float fSetWL2,float fDarkAD[], COLOR_PARA &dPara)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//
// 	LONGLONG start,end;   
// 	LARGE_INTEGER largeint; 
// 	double TotTime, freq; 
// 
// 	QueryPerformanceFrequency(&largeint); 
// 	freq = (double)largeint.QuadPart;   
// 	QueryPerformanceCounter(&largeint);   
// 	start = largeint.QuadPart; 

	int i,iR;
	if (g_fIntTime != fIntTime)
	{
		iR = SA_SetIntegrationTime(0, (int)(fIntTime*1000));
		if(iR == SA_API_FAIL)
		{
			return SA_API_FAIL;
		}

		g_fIntTime = fIntTime;
	}

	if (g_iAveNum != iAveNum)
	{
		iR = SA_SetAverageTimes(0, iAveNum);
		if(iR == SA_API_FAIL)
		{
			return SA_API_FAIL;
		}

		g_iAveNum = iAveNum;
	}

	double Spectum[2048];
	double SpectumNew[2048];
	int iLength;
	if (TriggerMode == EXINT_RISING_EDGE
		|| TriggerMode == EXINT_FALLING_EDGE
		|| TriggerMode == EXINT_HIGH_LEVEL
		|| TriggerMode == EXINT_LOW_LEVEL)
	{
		iR =SA_GetSpectumHWTrigger( 0, Spectum, iLength, 10000, TriggerMode);
	}
	else
	{
		iR = SA_GetSpectum(0, Spectum, iLength);
	}

	if(iR == SA_API_FAIL)
	{
		return SA_API_FAIL;
	}

// 	QueryPerformanceCounter(&largeint);   
// 	end = largeint.QuadPart; 
// 	TotTime = (double)(end - start) / freq; 
// 	TotTime = TotTime * 1000;
// 
// 	double TotTime1;
// 	QueryPerformanceFrequency(&largeint); 
// 	freq = (double)largeint.QuadPart;   
// 	QueryPerformanceCounter(&largeint);   
// 	start = largeint.QuadPart; 
	
	if (iFilterBW > 1)
	{
		for( i = 0 ;i<=iFilterBW;i++)
			SpectumNew[i] = Spectum[i];

		for( i  = iLength - iFilterBW ;i<= iLength - 1;i++)
			SpectumNew[i] = Spectum[i];

		for (i = iFilterBW+1 ;i< iLength - iFilterBW;i++)
		{
			double tempSum = 0.0;
			for (int j = (i-iFilterBW) ; j<= (i+iFilterBW) ;j++)
				tempSum = tempSum + Spectum[j];

			SpectumNew[i] = tempSum / (2 * iFilterBW + 1);
		}

		for (i = 0; i < iLength; i++)
		{
			Spectum[i] = SpectumNew[i];
		}
	}

	float fAD[2048];
	float fRel[10001];
	dPara.fIp = 0;
	for(i = 0; i < iLength; i++)
	{
		if (dPara.fIp < Spectum[i])
		{
			dPara.fIp = (float)(Spectum[i]);
		}
		Spectum[i] = Spectum[i] - fDarkAD[i];
	}

	SA_NonlinearCalibration(0, Spectum, SpectumNew, iLength);

	for(i = 0; i < iLength; i++)
	{
		fAD[i] = (float)(SpectumNew[i]);
	}

	float fSpect1 = g_fSPECT1;
	float fSpect2 = g_fSPECT2;
	dPara.fSpect1 = fSpect1;
	dPara.fSpect2 = fSpect2;
	float fInterval = 0.1f;
	dPara.fInterval = fInterval;
	int iN = (int)((fSpect2 - fSpect1) / fInterval + 1 +0.5f);
	float fLastAD	= 0;
	float fTempAD;
	float fTempL;

	int iPerStart = 1;
	for(i = 0; i < iN; i++)
	{
		fTempL  = fSpect1 + i * fInterval;
		//外插处理第一个点的数据
		if (fTempL < g_fPixWL[0])
		{
			fTempAD = fAD[0];
		}
		else if (fTempL <= g_fPixWL[iLength - 1])
		{
			//外插处理成最后一点的AD值
			//fTempAD = NewInt_float(g_fPixWL, fAD, iLength, fTempL);
			if (1)
			{
				int m, k;
				float u;
				k=1;
				for(m = iPerStart; m <= iLength-2; m++)
				{
					if( fTempL <= g_fPixWL[m] )
					{
						k=m;
						break;
					}
					else
						k=iLength-1;
				}
				iPerStart = k;
				if ((g_fPixWL[k]-g_fPixWL[k-1]) != 0)
				{
					u=(fTempL-g_fPixWL[k-1])/(g_fPixWL[k]-g_fPixWL[k-1]);
				}
				else
				{
					u = 0;
				}
				fTempAD = fAD[k-1]+u*(fAD[k]-fAD[k-1]);
			}
			fLastAD = fTempAD;
		}
		else
		{
			fTempAD = fLastAD;
		}
	
		fRel[i] = fTempAD * g_fSP_fK[i];
	}

	int iT3 = GetCurrentTime();
	if(1)
	{
		//归一成相对光谱
		float fMax=fRel[0];

		for(i = 0; i < iN; i++)
		{
			if(fRel[i] > fMax)
			{
				fMax = fRel[i];
			}
		}
		if(fMax <= 0)
		{
			fMax=1;
		}
		for(i=0;i<iN;i++)
		{
			fRel[i] = fRel[i] / fMax;
			dPara.fPL[i]  = fRel[i];
		}

		//注意 取出1nm数据计算
		float fRel_N[401];
		int   iB= (int)((380.0f - fSpect1)/ fInterval + 0.5f);
		int   iE= (int)((780.0f - fSpect1)/ fInterval + 0.5f);
		int   NN= (int)(1.0f / fInterval + 0.5f);
		float f;
		for(i = 0; i < 401; i++)
		{
			if((iB+i*NN)<0)
			{
				fRel_N[i]=0;
			}
			else if((iB+i*NN)<=iE)
			{
				f=fRel[iB+i*NN];
				if(f>1)
				{
					f=1;
				}
				fRel_N[i]=f;
			}
			else
			{
				fRel_N[i]=0;
			}
		}

		//光度值
		dPara.fPh = 0;
		for(i = 0; i < 401; i++)
		{
			//float fLamda = 380 + i * 1.0f;
			dPara.fPh = dPara.fPh + fRel_N[i] * fMax * g_fLamdaWL[i];//NH_GetV(fLamda);        //* fMax
		}

		float fPh1 = dPara.fPh;
		dPara.fPh = dPara.fPh * g_fSP_fIntTime * g_fCAL_fFluxK / fIntTime;
		if(dPara.fPh<=0)
			dPara.fPh=0;

		for(i=0;i<iN;i++)
			dPara.fPhe = dPara.fPhe + fRel[i]*fMax* fInterval;

		dPara.fPhe = dPara.fPhe * g_fCAL_fFluxK * g_fSP_fIntTime / fIntTime / 683;
		if(dPara.fPhe<=0)
			dPara.fPhe=0;

		dPara.fPlambda=fMax* g_fSP_fIntTime * g_fCAL_fFluxK / fIntTime / 683 * 1000;

		float fPL_N[4096];
		float fWL_N[4096];
		int   MM= (int)(1.0f/fInterval+0.5f);
		int iNum;
		iNum=(int)((fSpect2-fSpect1)+1);
		for(i=0;i<iNum;i++)
		{
			fWL_N[i]=fSpect1+i;
			float f=fRel[i*MM];
			if(f>1)
				f=1;
			fPL_N[i]=f;
		}

// 		QueryPerformanceCounter(&largeint);   
// 		end = largeint.QuadPart; 
// 		TotTime2 = (double)(end - start) / freq; 
// 		TotTime2 = TotTime2 * 1000;
// 
// 		double TotTime3;
// 		QueryPerformanceFrequency(&largeint); 
// 		freq = (double)largeint.QuadPart;   
// 		QueryPerformanceCounter(&largeint);   
// 		start = largeint.QuadPart; 

		//按新算法计算色参数
		NH_GetColorPara(fWL_N, fPL_N, iNum, dPara,FALSE,0.3f,0.3f);
	
// 		QueryPerformanceCounter(&largeint);   
// 		end = largeint.QuadPart; 
// 		TotTime3 = (double)(end - start) / freq; 
// 		TotTime3 = TotTime3 * 1000;
// 
// 		double TotTime5;
// 		QueryPerformanceFrequency(&largeint); 
// 		freq = (double)largeint.QuadPart;   
// 		QueryPerformanceCounter(&largeint);   
// 		start = largeint.QuadPart; 

		if (fDx!=0 || fDy!=0)
		{
			//计算偏置后的色度参数
			float fxx,fyy;
			fxx = dPara.fx+fDx;
			fyy = dPara.fy+fDy;
			float fLD;
			fLD = dPara.fLd;
			NH_GetColorPara(fWL_N, fPL_N, iNum, dPara,TRUE,fxx,fyy);
			if (fabs(fLD - dPara.fLd) > 3)
			{
			//	dPara.fLd = fLD;
			}
			dPara.fx = fxx;
			dPara.fy = fyy;
		}
	
		if(1)
		{
			//是否需要重新计算峰值波长
			int iB,iE;
			iB = (int)((fSetWL1 - fSpect1) / fInterval + 1 +0.5f);
			iE = (int)((fSetWL2 - fSpect1) / fInterval + 1 +0.5f);
			if (iB < 0)
			{
				iB = 0;
			}
			if (iE > iN)
			{
				iE = iN;
			}
			if (iB >= iE)
			{
				iB = 0;
				iE = iN;
			}
			//处理峰值波长
			fMax=0.01f;
			int iMax=iB;

			for(i=0;i<iN;i++)
			{
				if(dPara.fPL[i] < 0)
				{
					dPara.fPL[i] = 0;
				}
			}

			for(i=iB;i<iE;i++)
			{
				if(dPara.fPL[i] > fMax)
				{
					iMax = i;
					fMax = dPara.fPL[i];
				}
			}
			dPara.fLp	= iMax * fInterval + fSpect1;
			if (fMax <= 0)
			{
				fMax = 1;
			}
			int iTempMax = iMax;
			//处理峰值波长问题 在峰值波长附件找点处理
			int iL = iMax;
			BOOL bLeft = FALSE;	//是否有左值
			for(i = iMax; i > iB; i--)
			{
				if(dPara.fPL[i] / fMax <= 0.9f)
				{
					iL = i;
					bLeft = TRUE;
					break;
				}
			}
			
			int iR = iMax;
			BOOL bRight = FALSE;	//是否有右值
			for(i = iMax; i < iE; i++)
			{
				if(dPara.fPL[i] / fMax <= 0.9f)
				{
					iR = i;
					bRight = TRUE;
					break;
				}
			}
			if (bLeft && bRight)
			{
				iTempMax = (iL + iR) / 2;
				
				dPara.fLp	= iTempMax * fInterval + fSpect1;
			}
		}
	}

	return SA_API_SUCCESS;
}

extern "C" __declspec(dllexport) int WINAPI JK_Emission_CalcDxy(COLOR_PARA &dPara,float fDx,float fDy)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (fDx!=0 || fDy!=0)
	{
		float fPL_N[4096];
		float fWL_N[4096];
		int   MM= (int)(1.0f/dPara.fInterval+0.5f);
		int iNum;
		iNum=(int)((dPara.fSpect2-dPara.fSpect1)+1);
		for(int i=0;i<iNum;i++)
		{
			fWL_N[i]=dPara.fSpect1+i;
			float f=dPara.fPL[i*MM];
			if(f>1)
				f=1;
			fPL_N[i]=f;
		}

		//计算偏置后的色度参数
		float fxx,fyy;
		fxx = dPara.fx+fDx;
		fyy = dPara.fy+fDy;
		float fLD;
		fLD = dPara.fLd;
		NH_GetColorPara(fWL_N, fPL_N, iNum, dPara,TRUE,fxx,fyy);
		if (fabs(fLD - dPara.fLd) > 3)
		{
		//	dPara.fLd = fLD;
		}
		dPara.fx = fxx;
		dPara.fy = fyy;
	}
	return SA_API_SUCCESS;
}

extern "C" __declspec(dllexport) int WINAPI JK_Emission_Calib(float fIntTime, int iAveNum,int iFilterBW, int iCalType, float fCCT, float fFlux,int iStaNum,float fStaWL[],float fStaPL[],float fDarkAD[],float &fIp)
{
	//iCalType: 0使用色温法计算定标
	//			1使用导入的绝对光谱定标
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int i,iR;

	iR = SA_SetIntegrationTime(0, (int)(fIntTime*1000));
	if(iR == SA_API_FAIL)
	{
		return SA_API_FAIL;
	}

	iR = SA_SetAverageTimes(0, iAveNum);
	if(iR == SA_API_FAIL)
	{
		return SA_API_FAIL;
	}

	double Spectum[2048];
	double SpectumNew[2048];
	int iLength;
	iR = SA_GetSpectum(0, Spectum, iLength);
	if(iR == SA_API_FAIL)
	{
		return SA_API_FAIL;
	}

	if (iFilterBW > 1)
	{
		for( i = 0 ;i<=iFilterBW;i++)
			SpectumNew[i] = Spectum[i];

		for( i  = iLength - iFilterBW ;i<= iLength - 1;i++)
			SpectumNew[i] = Spectum[i];

		for (i = iFilterBW+1 ;i< iLength - iFilterBW;i++)
		{
			double tempSum = 0.0;
			for (int j = (i-iFilterBW) ; j<= (i+iFilterBW) ;j++)
				tempSum = tempSum + Spectum[j];

			SpectumNew[i] = tempSum / (2 * iFilterBW + 1);
		}

		for (i = 0; i < iLength; i++)
		{
			Spectum[i] = SpectumNew[i];
		}
	}

	float fPixWL[2048];
	float fAD[2048];
	float fMax = 0;
	fIp = 0;
	for(i = 0; i < iLength; i++)
	{
		if (fIp < Spectum[i])
		{
			fIp = (float)(Spectum[i]);
		}
		Spectum[i] = Spectum[i] - fDarkAD[i];
		if(Spectum[i] > fMax)
			fMax = (float)(Spectum[i]);
	}

	if(fMax < 20000)
	{
		AfxMessageBox("请增大积分时间!");
		return SA_API_FAIL;
	}

	if(fMax > 60000)
	{
		AfxMessageBox("请减小积分时间!");
		return SA_API_FAIL;
	}
	SA_NonlinearCalibration(0, Spectum, SpectumNew, iLength);
	for(i = 0; i < iLength; i++)
	{
		fPixWL[i] = g_fCCor[0]
		+ g_fCCor[1] * i
			+ g_fCCor[2] * i * i
			+ g_fCCor[3] * i * i * i;
		fAD[i] = (float)(SpectumNew[i]);
	}
	float fPL[10001];
	float fSpect1 = 280.0f;
	float fSpect2 = 980.0f;
	float fInterval = 0.1f;
	int iNum = (int)((fSpect2 - fSpect1) / fInterval + 1 +0.5f);
	float fLastAD = 0;
	for(i = 0; i < iNum; i++)
	{
		fPL[i] = NewInt_float(fPixWL,fAD,iLength,fSpect1 + i * fInterval);
		float fTempL  = fSpect1 + i * fInterval;
		float fTempAD;
		//外插处理第一个点的数据
		if (fTempL < fPixWL[0])
		{
			fTempAD = fAD[0];
		}
		//外插处理成最后一点的AD值
		else if (fTempL <= fPixWL[iLength - 1])
		{
			fTempAD = NewInt_float(fPixWL, fAD, iLength, fTempL);
			fLastAD = fTempAD;
		}
		else
		{
			fTempAD = fLastAD;
		}
		fPL[i] = fTempAD;
	}

	if(iCalType == 0)
	{
		//色温法计算定标洗漱
		float c1 = (float)(3.741844E19*9.58378/8.071367);
		float c2 = (float)(1.438833E7/fCCT);

		g_fSP_fSpect1		= fSpect1;
		g_fSP_fSpect2		= fSpect2;
		g_fSP_fInterval		= fInterval;
		g_fSP_fStaTc		= fCCT;
		g_fSP_fIntTime		= fIntTime;
		g_fCAL_fStaFlux		= fFlux;

		CTime tNow;
		tNow = CTime::GetCurrentTime();
		CString sNow = tNow.Format("%Y-%m-%d,%H:%M");
		CString SP_strDate = sNow;
		int i;
		for(i=0;i<iNum;i++)
		{
			float lamda = fSpect1 + i * fInterval;
			float fRel;
			double fTemp;
			fRel = fPL[i];
			if(fRel <= 0)
			{
				fTemp = 0;
			}
			else
			{
				fTemp = (double)((c1/pow(lamda,5)/(exp(c2/lamda)-1))/fRel);
			}

			g_fSP_fK[i]=(float)(fTemp);
		}

		//根据光通量积分公式计算定标数据
		double d = 0;
		for(i = 0; i < 401; i++)
		{
			float lamda=380+i*1.0f;
			d = d + (c1/pow(lamda,5)/(exp(c2/lamda)-1)) * NH_GetV(lamda); 
		}

		// 光强到照度计算
		float fTempPh;
		fTempPh= fFlux;

		if(d>0)
			g_fCAL_fFluxK = (float)(fFlux/d);
		else
			g_fCAL_fFluxK = 1.0f;
		g_fCAL_fStaFlux = fTempPh;

		CString sTemp;
		sTemp="Cal_standard.nh";   //低

		/* AAA.新建目录 */
		CString strPathName = g_strCurPath +  "Calibration\\";
		CreateDirectory(strPathName,NULL);
		SHChangeNotify(SHCNE_MKDIR,SHCNF_PATH,strPathName,0);

		//光谱定标数据保存
		FILE *fp;
		if(fopen_s(&fp, g_strCurPath + "Calibration\\" + sTemp,"wt"))
		{
			return SA_API_FAIL;
		}
		else
		{
			fprintf_s(fp,"%.0fK Time:%.2f\n",g_fSP_fStaTc,g_fSP_fIntTime);
			fprintf_s(fp,"%.1f %.1f %.3f\n",g_fSP_fSpect1,g_fSP_fSpect2,g_fSP_fInterval);
			fprintf_s(fp,SP_strDate+"\n");
			fprintf_s(fp,"%.3f  %.9f\n",g_fCAL_fStaFlux, g_fCAL_fFluxK);

			for(i = 0; i < iNum; i++)
			{
				fprintf_s(fp,"%.1f %.5e %.1f \n", g_fSP_fSpect1 + i * g_fSP_fInterval, g_fSP_fK[i], fPL[i]);
			}
		}
		fclose(fp);
	}
	else
	{
		//使用导入的绝对光谱数据计算
		g_fSP_fSpect1		= fSpect1;
		g_fSP_fSpect2		= fSpect2;
		g_fSP_fInterval		= fInterval;
		g_fSP_fStaTc		= fCCT;
		g_fSP_fIntTime		= fIntTime;
		g_fCAL_fStaFlux		= fFlux;

		CTime tNow;
		tNow = CTime::GetCurrentTime();
		CString sNow = tNow.Format("%Y-%m-%d,%H:%M");
		CString SP_strDate = sNow;
		int i;
		for(i=0;i<iNum;i++)
		{
			float lamda = fSpect1 + i * fInterval;
			float fRel;
			double fTemp;
			fRel = fPL[i];
			float fStd;
			fStd = NewInt_float(fStaWL,fStaPL,iStaNum,fSpect1 + i * fInterval);
			if(fRel <= 0)
			{
				fTemp = 0;
			}
			else
			{
				fTemp = (double)(fStd/fRel);
			}

			g_fSP_fK[i]=(float)(fTemp);
		}

		//根据光通量积分公式计算定标数据
		double d = 0;
		for(i = 0; i < 401; i++)
		{
			float lamda=380+i*1.0f;
			float fStd;
			fStd = NewInt_float(fStaWL,fStaPL,iStaNum,lamda);
			d = d + fStd * NH_GetV(lamda); 
		}

		// 光强到照度计算
		float fTempPh;
		fTempPh= fFlux;

		if(d>0)
			g_fCAL_fFluxK = (float)(fFlux/d);
		else
			g_fCAL_fFluxK = 1.0f;
		g_fCAL_fStaFlux = fTempPh;

		CString sTemp;
		sTemp="Cal_standard.nh";   //低

		/* AAA.新建目录 */
		CString strPathName = g_strCurPath +  "Calibration\\";
		CreateDirectory(strPathName,NULL);
		SHChangeNotify(SHCNE_MKDIR,SHCNF_PATH,strPathName,0);

		//光谱定标数据保存
		FILE *fp;
		if(fopen_s(&fp, g_strCurPath + "Calibration\\" + sTemp,"wt"))
		{
			return SA_API_FAIL;
		}
		else
		{
			fprintf_s(fp,"%.0fK Time:%.2f\n",g_fSP_fStaTc,g_fSP_fIntTime);
			fprintf_s(fp,"%.1f %.1f %.3f\n",g_fSP_fSpect1,g_fSP_fSpect2,g_fSP_fInterval);
			fprintf_s(fp,SP_strDate+"\n");
			fprintf_s(fp,"%.3f  %.9f\n",g_fCAL_fStaFlux, g_fCAL_fFluxK);

			for(i = 0; i < iNum; i++)
			{
				fprintf_s(fp,"%.1f %.5e %.1f \n", g_fSP_fSpect1 + i * g_fSP_fInterval, g_fSP_fK[i], fPL[i]);
			}
		}
		fclose(fp);
	}

	return SA_API_SUCCESS;
}

extern "C" __declspec(dllexport) int WINAPI JK_ScanStartAsyncSoftTrigger()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//启动软件异步触发模式
	return SA_ScanStartAsyncSoftTrigger(0);
	return SA_API_SUCCESS;
}

extern "C" __declspec(dllexport) int WINAPI JK_GetSpectumAsyncSoftTrigger(int &pState, float fIntTime, int iAveNum,int iFilterBW, float fDx,float fDy, float fSetWL1,float fSetWL2, float fDarkAD[],COLOR_PARA &dPara)
{
	//读取软件异步触发数据状态 和 结果
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//
	int i,iR;
	if (g_fIntTime != fIntTime)
	{
		iR = SA_SetIntegrationTime(0, (int)(fIntTime*1000));
		if(iR == SA_API_FAIL)
		{
			return SA_API_FAIL;
		}

		g_fIntTime = fIntTime;
	}

	if (g_iAveNum != iAveNum)
	{
		iR = SA_SetAverageTimes(0, iAveNum);
		if(iR == SA_API_FAIL)
		{
			return SA_API_FAIL;
		}

		g_iAveNum = iAveNum;
	}

	double Spectum[2048];
	double SpectumNew[2048];
	int iLength;
	iR = SA_GetSpectumAsyncSoftTrigger(0, pState, Spectum, iLength);
	if(iR == SA_API_FAIL)
	{
		return SA_API_FAIL;
	}

	if (pState != 2)
	{
		//处于等待数据状态中
		return SA_API_FAIL;
	}
	
	if (iFilterBW > 1)
	{
		for( i = 0 ;i<=iFilterBW;i++)
			SpectumNew[i] = Spectum[i];

		for( i  = iLength - iFilterBW ;i<= iLength - 1;i++)
			SpectumNew[i] = Spectum[i];

		for (i = iFilterBW+1 ;i< iLength - iFilterBW;i++)
		{
			double tempSum = 0.0;
			for (int j = (i-iFilterBW) ; j<= (i+iFilterBW) ;j++)
				tempSum = tempSum + Spectum[j];

			SpectumNew[i] = tempSum / (2 * iFilterBW + 1);
		}

		for (i = 0; i < iLength; i++)
		{
			Spectum[i] = SpectumNew[i];
		}
	}

	float fAD[2048];
	float fRel[10001];
	dPara.fIp = 0;
	for(i = 0; i < iLength; i++)
	{
		if (dPara.fIp < Spectum[i])
		{
			dPara.fIp = (float)(Spectum[i]);
		}
		Spectum[i] = Spectum[i] - fDarkAD[i];
	}

	SA_NonlinearCalibration(0, Spectum, SpectumNew, iLength);
	int iT1 = GetCurrentTime();

	for(i = 0; i < iLength; i++)
	{
		fAD[i] = (float)(SpectumNew[i]);
	}

	float fSpect1	= 280.0f;
	float fSpect2	= 980.0f;
	dPara.fSpect1 = fSpect1;
	dPara.fSpect2 = fSpect2;
	float fInterval = 0.1f;
	dPara.fInterval = fInterval;
	int iN = (int)((fSpect2 - fSpect1) / fInterval + 1 +0.5f);
	float fLastAD	= 0;
	float fTempAD;
	float fTempL;

	int iPerStart = 1;
	for(i = 0; i < iN; i++)
	{
		fTempL  = fSpect1 + i * fInterval;
		//外插处理第一个点的数据
		if (fTempL < g_fPixWL[0])
		{
			fTempAD = fAD[0];
		}
		else if (fTempL <= g_fPixWL[iLength - 1])
		{
			//外插处理成最后一点的AD值
			fTempAD = NewInt_float(g_fPixWL, fAD, iLength, fTempL);
			
			fLastAD = fTempAD;
		}
		else
		{
			fTempAD = fLastAD;
		}
	
		fRel[i] = fTempAD * g_fSP_fK[i];
	}

	int iT3 = GetCurrentTime();
	if(1)
	{
		//归一成相对光谱
		float fMax=fRel[0];

		for(i = 0; i < iN; i++)
		{
			if(fRel[i] > fMax)
			{
				fMax = fRel[i];
			}
		}
		if(fMax <= 0)
		{
			fMax=1;
		}
		for(i=0;i<iN;i++)
		{
			fRel[i] = fRel[i] / fMax;
			dPara.fPL[i]  = fRel[i];
		}

		//注意 取出1nm数据计算
		float fRel_N[401];
		int   iB= (int)((380.0f - fSpect1)/ fInterval + 0.5f);
		int   iE= (int)((780.0f - fSpect1)/ fInterval + 0.5f);
		int   NN= (int)(1.0f / fInterval + 0.5f);
		float f;
		for(i = 0; i < 401; i++)
		{
			if((iB+i*NN)<0)
			{
				fRel_N[i]=0;
			}
			else if((iB+i*NN)<=iE)
			{
				f=fRel[iB+i*NN];
				if(f>1)
				{
					f=1;
				}
				fRel_N[i]=f;
			}
			else
			{
				fRel_N[i]=0;
			}
		}

		//光度值
		dPara.fPh = 0;
		for(i = 0; i < 401; i++)
		{
			float fLamda = 380 + i * 1.0f;
			dPara.fPh = dPara.fPh + fRel_N[i] * fMax * NH_GetV(fLamda);        //* fMax
		}

		float fPh1 = dPara.fPh;
		dPara.fPh = dPara.fPh * g_fSP_fIntTime * g_fCAL_fFluxK / fIntTime;
		if(dPara.fPh<=0)
			dPara.fPh=0;

		for(i=0;i<iN;i++)
			dPara.fPhe = dPara.fPhe + fRel[i]*fMax* fInterval;

		dPara.fPhe = dPara.fPhe * g_fCAL_fFluxK * g_fSP_fIntTime / fIntTime / 683;
		if(dPara.fPhe<=0)
			dPara.fPhe=0;

		dPara.fPlambda=fMax* g_fSP_fIntTime * g_fCAL_fFluxK / fIntTime / 683 * 1000;

		float fPL_N[4096];
		float fWL_N[4096];
		int   MM= (int)(1.0f/fInterval+0.5f);
		int iNum;
		iNum=(int)((fSpect2-fSpect1)+1);
		for(i=0;i<iNum;i++)
		{
			fWL_N[i]=fSpect1+i;
			float f=fRel[i*MM];
			if(f>1)
				f=1;
			fPL_N[i]=f;
		}

		//按新算法计算色参数
		NH_GetColorPara(fWL_N, fPL_N, iNum, dPara,FALSE,0.3f,0.3f);
		if (fDx!=0 || fDy!=0)
		{
			//计算偏置后的色度参数
			float fxx,fyy;
			fxx = dPara.fx+fDx;
			fyy = dPara.fy+fDy;
			float fLD;
			fLD = dPara.fLd;
			NH_GetColorPara(fWL_N, fPL_N, iNum, dPara,TRUE,fxx,fyy);
			if (fabs(fLD - dPara.fLd) > 3)
			{
			//	dPara.fLd = fLD;
			}
			dPara.fx = fxx;
			dPara.fy = fyy;
		}
	
		//处理峰值波长
		fMax=0.100f;
		int iMax=0;
		for(i=0;i<iN;i++)
		{
			if(dPara.fPL[i] > fMax)
			{
				iMax = i;
				fMax = dPara.fPL[i];
			}
		}
		dPara.fLp	= iMax*fInterval + fSpect1;
	
		if(1)
		{
			//是否需要重新计算峰值波长
			int iB,iE;
			iB = (int)((fSetWL1 - fSpect1) / fInterval + 1 +0.5f);
			iE = (int)((fSetWL2 - fSpect1) / fInterval + 1 +0.5f);
			if (iB < 0)
			{
				iB = 0;
			}
			if (iE > iN)
			{
				iE = iN;
			}
			if (iB >= iE)
			{
				iB = 0;
				iE = iN;
			}
			//处理峰值波长
			fMax=0.000f;
			int iMax=iB;

			for(i=0;i<iN;i++)
			{
				if(dPara.fPL[i] < 0)
				{
					dPara.fPL[i] = 0;
				}
			}

			for(i=iB;i<iE;i++)
			{
				if(dPara.fPL[i] > fMax)
				{
					iMax = i;
					fMax = dPara.fPL[i];
				}
			}
			dPara.fLp	= iMax * fInterval + fSpect1;

			int iTempMax = iMax;
			//处理峰值波长问题 在峰值波长附件找点处理
			int iL = iMax;
			if (fMax <= 0)
			{
				fMax = 1;
			}
			BOOL bLeft = FALSE;	//是否有左值
			for(i = iMax; i > iB; i--)
			{
				if(dPara.fPL[i] / fMax <= 0.9f)
				{
					iL = i;
					bLeft = TRUE;
					break;
				}
			}

			int iR = iMax;
			BOOL bRight = FALSE;	//是否有右值
			for(i = iMax; i < iE; i++)
			{
				if(dPara.fPL[i] / fMax <= 0.9f)
				{
					iR = i;
					bRight = TRUE;
					break;
				}
			}
			if (bLeft && bRight)
			{
				iTempMax = (iL + iR) / 2;

				dPara.fLp	= iTempMax * fInterval + fSpect1;
			}
		}
	}
	return SA_API_SUCCESS;
}

