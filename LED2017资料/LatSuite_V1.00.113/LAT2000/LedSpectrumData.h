#pragma once
#include "NewTestColorData.h"

class CLedSpectrumData
{
public:
	CLedSpectrumData(void);
	~CLedSpectrumData(void);
	
//	CArray<float,float> m_fWaveLength;
	CArray<float,float> m_fValue;

	CNewTestColorData	m_colorData;
};

