#pragma once
#include "Serial.h"

// #define g_iColomnNum	9
// #define g_iRowNum			3

enum ChannelState
{
	CHANNEL_OFF		= 0,
	CHANNEL_GREEN	= 1,   // LED_Q
	CHANNEL_RED		= 2,  // LED_UNON or LED_UQ
};

class CIndicatorComm
{
public:
	CIndicatorComm(void);
	~CIndicatorComm(void);

public:
	void Initialize(CString strCOM);

	BOOL SetAllChannelState(ChannelState iState[]);

	BOOL IsConnected();

private:
	CString m_strCOM;
	int m_iBaudrate;

	Serial m_ser;
	ChannelState m_state[32];
};

