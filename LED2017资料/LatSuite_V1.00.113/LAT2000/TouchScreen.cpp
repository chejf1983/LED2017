#include "StdAfx.h"
#include "TouchScreen.h"


CTouchScreen::CTouchScreen(void)
{
}


CTouchScreen::~CTouchScreen(void)
{
}

void CTouchScreen::Initialize(CString strCOM, int iBaudRate)
{
	m_strCOM	= strCOM;
	m_iBaudRate = iBaudRate;
}


void CTouchScreen::SetDemo(BOOL bDemo)
{
	m_bDemo = bDemo;
}

BOOL CTouchScreen::SendData(CString sendData)
{
	if (m_bDemo)
	{
		Sleep(100);
		return TRUE;
	}
	HANDLE comHandle;
	BOOL bR;
	bR = m_ser.Open(comHandle, m_strCOM, m_iBaudRate);
	if (!bR)
	{
		return FALSE;
	}
	BYTE byteIn[256];
	CString strTemp = "";
	m_ser.SetReadTime(comHandle, 100, 2, 100);
	m_bStop = FALSE;
	
	if (m_ser.Input(comHandle,byteIn, 1))
	{
		strTemp += byteIn[0];
	}

	m_ser.Close(comHandle);
	return TRUE;
}
