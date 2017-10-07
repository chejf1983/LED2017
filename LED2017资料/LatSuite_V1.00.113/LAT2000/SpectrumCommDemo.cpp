#include "stdafx.h"
#include "SpectrumCommDemo.h"
#include <stdlib.h>

CSpectrumCommDemo::CSpectrumCommDemo(void)
{
	m_bDemo = TRUE;
}


CSpectrumCommDemo::~CSpectrumCommDemo(void)
{
}

BOOL CSpectrumCommDemo::SetDemo(BOOL bDemo)
{
	m_bDemo = bDemo;

	return TRUE;
}

BOOL CSpectrumCommDemo::Set(float fIntegralTimeMS)
{
	if (m_bDemo)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CSpectrumCommDemo::Sample(CLedData & data)
{
	if (m_bDemo)
	{
		data.m_ColorData.m_fWL1 = 380;
		data.m_ColorData.m_fWL2 = 780;
		data.m_ColorData.m_fIntervalWL = 0.2f;

		int iRand;

		iRand = rand();
		data.m_ColorData.m_fPh = (float)(iRand % 10000);
	
		iRand = rand();
		data.m_ColorData.m_fPh_e = (float)(iRand % 10000);

		iRand = rand();
		data.m_ColorData.m_fHW = (float)(iRand % 3000);

		iRand = rand();
		data.m_ColorData.m_fLd = (float)(iRand % 1000);

		iRand = rand();
		data.m_ColorData.m_fLp = (float)(iRand % 1000);

		iRand = rand();
		data.m_ColorData.m_fPur = (float)(iRand % 100);

		iRand = rand();
		data.m_ColorData.m_fRa = (float)(iRand % 1000);

		iRand = rand();
		data.m_ColorData.m_fTc = (float)(iRand % 1000);

		iRand = rand();
		data.m_ColorData.m_fIp = (float)(iRand % 100);

		iRand = rand();
		data.m_ColorData.m_fCIEu_ = (float)(iRand / 33000.0);

		iRand = rand();
		data.m_ColorData.m_fCIEv_ = (float)(iRand / 33000.0);
	
		iRand = rand();
		data.m_ColorData.m_fRR = (float)(iRand % 255);

		iRand = rand();
		data.m_ColorData.m_fGR = (float)(iRand % 245);

		iRand = rand();
		data.m_ColorData.m_fBR = (float)(iRand % 225);

		srand(rand());
		data.m_ColorData.m_fCIEx = (float)(0.4 + rand() * 0.15f/ RAND_MAX);

		srand(rand());
		data.m_ColorData.m_fCIEy = (float)(0.3 + rand() * 0.15f/ RAND_MAX);

		float fWaveLengthStep = (float)(400.0 / 1024);
		data.m_fValue.RemoveAll();
		UINT uiCount = GetCurrentTime()%1000;
		data.m_ColorData.m_iPLLength = 2001;
		for (int i = 0; i < data.m_ColorData.m_iPLLength; i++)
		{
			data.m_ColorData.m_fPL[i] = i * 1.0f / data.m_ColorData.m_iPLLength;
		}

		data.m_ColorData.m_bHaveColorData = TRUE;

		return TRUE;
	}

	return FALSE;
}