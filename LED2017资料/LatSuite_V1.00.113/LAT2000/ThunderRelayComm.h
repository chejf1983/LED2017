#pragma once
#include "Serial.h"

#define		THUNDER_CHANNEL_NUM		10

class CThunderRelayComm
{
public:
	CThunderRelayComm(void);
	~CThunderRelayComm(void);

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

