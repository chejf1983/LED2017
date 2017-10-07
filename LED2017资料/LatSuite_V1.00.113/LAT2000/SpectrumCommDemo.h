// Only for generating demo data

#pragma once
#include "LedData.h"

class CSpectrumCommDemo
{
public:
	CSpectrumCommDemo(void);
	~CSpectrumCommDemo(void);

public:
	BOOL SetDemo(BOOL bDemo);
	BOOL Set(float fIntegralTimeMS);
	BOOL Sample(CLedData & data);

private:
	BOOL  m_bDemo;
};

