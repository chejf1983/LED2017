#pragma once
#include "Serial.h"

class CTouchScreen
{
public:
	CTouchScreen(void);
	~CTouchScreen(void);
	void SetDemo(BOOL bDemo);
	void Initialize(CString strCOM, int iBaudRate = 9600);
	BOOL SendData(CString sendData);
private:
	Serial	m_ser;
	CString m_strCOM;
	int		m_iBaudRate;
	BOOL m_bStop;
	BOOL m_bDemo;
};

