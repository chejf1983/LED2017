#pragma once
#include "Serial.h"

#define		LRA_CHANNEL_NUM		10

class CLRAComm
{
public:
	CLRAComm(void);
	~CLRAComm(void);

	void SetAddress(BYTE ucPCAddress = 0xEE, BYTE ucDeviceAddress = 0xBF);
	void Initialize(CString strCOM, int iBaudRate = 9600);
	BOOL SetChannel(BOOL bChannel[]);
	BOOL SwitchAllChannel(BOOL bOn);
	BOOL SwitchOneChannel(int iChannel, BOOL bOn);

private:
	Serial	m_ser;
	CString m_strCOM;
	int		m_iBaudRate;
};

