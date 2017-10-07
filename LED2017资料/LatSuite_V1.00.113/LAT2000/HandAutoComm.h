#pragma once
#include "Serial.h"

class CHandAutoComm
{
public:
	CHandAutoComm(void);
	~CHandAutoComm(void);

	void Initialize(CString strCOM);
    void SetDemo(BOOL bDemo);

	BOOL WriteToHandInpos(BOOL bInpos);
	BOOL ReadHandState(BOOL &bAllowMove);
	BOOL WriteToHandLamp(int iChannelOK[]);

private:

	Serial	m_ser;
	CString m_strCOM;
	int		m_iBaudRate;
    BOOL m_bDemo;
	BOOL m_bHaveReset;

	CRITICAL_SECTION m_critical;
};

