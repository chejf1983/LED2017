#pragma once
#include "Serial.h"

class CGaugeComm
{
public:
	CGaugeComm(void);
	~CGaugeComm(void);

public:
	void Initialize(CString strCOM, int iBaudrate = 9600);
	BOOL Read(int iGaugeIndex, float & fVoltageV, float & fCurrentA, float & fPowerW);
	BOOL Read3(int iGaugeIndex, float & fVoltageV, float & fCurrentA, float & fPowerW);

private:
	UINT GetCRC(BYTE * pBuf, BYTE num);
	CCriticalSection m_criticalSection;
	
	CString m_strCOM;
	int m_iBaudrate;
	Serial m_ser;
};

