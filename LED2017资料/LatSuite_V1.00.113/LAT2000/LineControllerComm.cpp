#include "StdAfx.h"
#include "LineControllerComm.h"

CLineControllerComm::CLineControllerComm(void)
{
	m_iBaudRate = 9600;
	m_iSendData[4] = 0;
	InitializeCriticalSection(&m_critical);
}


CLineControllerComm::~CLineControllerComm(void)
{
}


void CLineControllerComm::Initialize(CString strCOM)
{
	m_strCOM = strCOM;
}

void CLineControllerComm::SetDemo(BOOL bDemo)
{
    m_bDemo = bDemo;
}

BOOL CLineControllerComm::MoveLineOneStep()
{
    if (m_bDemo)
    {
        Sleep(500);
        return TRUE;
    }
	BOOL bR;
	bR = MoveLineOneStep_Sub();
	if (!bR)
	{
		Sleep(100);
		bR = MoveLineOneStep_Sub();
		if (!bR)
		{
			Sleep(200);
			bR = MoveLineOneStep_Sub();
		}	
	}
	return bR;
}

BOOL CLineControllerComm::MoveLineOneStep_Sub()
{
	EnterCriticalSection(&m_critical);
	Sleep(100);
	HANDLE comHandle;
	if (!m_ser.Open(comHandle,m_strCOM, m_iBaudRate))
	{
		LeaveCriticalSection(&m_critical);
		return FALSE;
	}
	m_ser.SetReadTime(comHandle,1000, 1, 1000);

	BYTE ucOut[256];
	BYTE ucIn[256];
	ucOut[0] = 0x7B;
	ucOut[1] = 0x7B;
	ucOut[2] = 0x00;
	ucOut[3] = 0x04;
	ucOut[4] = m_iSendData[4];

	ucOut[5] = 0x00;
	ucOut[6] = 0x01;
	ucOut[7] = 0x7D;
	ucOut[8] = 0x7D;

	m_ser.Output(comHandle,ucOut, 9);
	if (!m_ser.Input(comHandle,ucIn, 9))
	{
		LeaveCriticalSection(&m_critical);
		m_ser.Close(comHandle);
		return FALSE;
	}
	m_ser.Close(comHandle);
	Sleep(200);
	LeaveCriticalSection(&m_critical);	
	// delay 1000ms for read line state;if not delay 1000ms,read line state will be false
	return TRUE;
}

BOOL CLineControllerComm::ReadLineState(BOOL & bInposition, BOOL & bManualStopped, BOOL & bLampTooHigh)
{
    if (m_bDemo)
    {
        bInposition		= 2;
        bManualStopped	= 0;
        bLampTooHigh	= 0;
        return TRUE;
    }
	BOOL bR;
	bR = ReadLineState_Sub(bInposition, bManualStopped, bLampTooHigh);
	if (!bR)
	{
		Sleep(100);
		bR = ReadLineState_Sub(bInposition, bManualStopped, bLampTooHigh);
		if (!bR)
		{
			Sleep(200);
			bR = ReadLineState_Sub(bInposition, bManualStopped, bLampTooHigh);
		}	
	}
	return bR;
}

BOOL CLineControllerComm::ReadLineState_Sub(BOOL & bInposition, BOOL & bManualStopped, BOOL & bLampTooHigh)
{
	EnterCriticalSection(&m_critical);
	Sleep(200);
	HANDLE comHandle;
	if (!m_ser.Open(comHandle,m_strCOM, m_iBaudRate))
	{
		LeaveCriticalSection(&m_critical);
		return FALSE;
	}
	m_ser.SetReadTime(comHandle,1000, 1, 1000);

	BYTE ucOut[256];
	BYTE ucIn[256];
	ucOut[0] = 0x7B;
	ucOut[1] = 0x7B;
	ucOut[2] = 0x00;
	ucOut[3] = 0x20;
	ucOut[4] = m_iSendData[4];

	ucOut[5] = 0x00;
	ucOut[6] = 0x01;
	ucOut[7] = 0x7D;
	ucOut[8] = 0x7D;

	m_ser.Output(comHandle,ucOut, 9);
	if (!m_ser.Input(comHandle,ucIn, 9))
	{
		LeaveCriticalSection(&m_critical);
		m_ser.Close(comHandle);
		return FALSE;
	}

	bInposition = ucIn[2] & (1 << 1);
	bManualStopped = !(ucIn[2] & (1 << 2)) || !(ucIn[2] & (1 << 3));
	bLampTooHigh = ucIn[2] & (1 << 6);
	m_ser.Close(comHandle);
	Sleep(50);
	LeaveCriticalSection(&m_critical);
	return TRUE;
}

BOOL CLineControllerComm::SetShowLED(int iType)
{
	//iType2=ºì 1=ÂÌ 0=»Æ
	EnterCriticalSection(&m_critical);
	Sleep(200);
	HANDLE comHandle;
	if (!m_ser.Open(comHandle,m_strCOM, m_iBaudRate))
	{
		LeaveCriticalSection(&m_critical);
		return FALSE;
	}
	m_ser.SetReadTime(comHandle,1000, 1, 1000);

	BYTE ucOut[256];
	BYTE ucIn[256];
	ucOut[0] = 0x7B;
	ucOut[1] = 0x7B;
	ucOut[2] = 0x00;
	ucOut[3] = 0x02;
	if (iType == 0)
	{
		ucOut[4] = 4;
	}
	if (iType == 1)
	{
		ucOut[4] = 2;
	}
	if (iType == 2)
	{
		ucOut[4] = 1;
	}
	//m_iSendData[4] = ucOut[4];
	ucOut[5] = 0x00;
	ucOut[6] = 0x01;
	ucOut[7] = 0x7D;
	ucOut[8] = 0x7D;

	m_ser.Output(comHandle,ucOut, 9);
	if (!m_ser.Input(comHandle,ucIn, 9))
	{
		LeaveCriticalSection(&m_critical);
		m_ser.Close(comHandle);
		return FALSE;
	}
	m_ser.Close(comHandle);
	Sleep(500);
	LeaveCriticalSection(&m_critical);
	return TRUE;
}

BOOL CLineControllerComm::SetLinePause()
{
	return TRUE;
    if (m_bDemo)
    {
        Sleep(500);
        return TRUE;
    }
    BOOL bR;
	bR = SetLinePause_Sub();
	if (!bR)
	{
		Sleep(100);
		bR = SetLinePause_Sub();
		if (!bR)
		{
			Sleep(200);
			bR = SetLinePause_Sub();
		}	
	}
	return bR;
}

BOOL CLineControllerComm::SetLinePause_Sub()
{
	EnterCriticalSection(&m_critical);
	Sleep(200);
	HANDLE comHandle;
	if (!m_ser.Open(comHandle,m_strCOM, m_iBaudRate))
	{
		LeaveCriticalSection(&m_critical);
		return FALSE;
	}
	m_ser.SetReadTime(comHandle,1000, 1, 1000);

	BYTE ucOut[256];
	BYTE ucIn[256];
	ucOut[0] = 0x7B;
	ucOut[1] = 0x7B;
	ucOut[2] = 0x00;
	ucOut[3] = 0x01;
	ucOut[4] = 0x00;

	ucOut[5] = 0x00;
	ucOut[6] = 0x01;
	ucOut[7] = 0x7D;
	ucOut[8] = 0x7D;

	m_ser.Output(comHandle,ucOut, 9);
	if (!m_ser.Input(comHandle,ucIn, 9))
	{
		LeaveCriticalSection(&m_critical);
		m_ser.Close(comHandle);
		return FALSE;
	}
	m_ser.Close(comHandle);
	Sleep(100);
	LeaveCriticalSection(&m_critical);
	return TRUE;
}

BOOL CLineControllerComm::MoveLineContinuous()
{
    if (m_bDemo)
    {
        Sleep(500);
        return TRUE;
    }
	BOOL bR;
	bR = MoveLineContinuous_Sub();
	if (!bR)
	{
		bR = MoveLineContinuous_Sub();
		if (!bR)
		{
			bR = MoveLineContinuous_Sub();
		}	
	}
	return bR;
}

BOOL CLineControllerComm::MoveLineContinuous_Sub()
{
	if (TryEnterCriticalSection(&m_critical))
	{
		HANDLE comHandle;
		if (!m_ser.Open(comHandle,m_strCOM, m_iBaudRate))
		{
			LeaveCriticalSection(&m_critical);
			return FALSE;
		}
		m_ser.SetReadTime(comHandle,1000, 1, 1000);

		BYTE ucOut[256];
		BYTE ucIn[256];
		ucOut[0] = 0x7B;
		ucOut[1] = 0x7B;
		ucOut[2] = 0x00;
		ucOut[3] = 0x02;
		ucOut[4] = 0x00;

		ucOut[5] = 0x00;
		ucOut[6] = 0x01;
		ucOut[7] = 0x7D;
		ucOut[8] = 0x7D;

		m_ser.Output(comHandle,ucOut, 9);
		if (!m_ser.Input(comHandle,ucIn, 9))
		{
			LeaveCriticalSection(&m_critical);
			m_ser.Close(comHandle);
			return FALSE;
		}
		m_ser.Close(comHandle);
		Sleep(100);
		LeaveCriticalSection(&m_critical);
		return TRUE;
	}
	return TRUE;	
}

BOOL CLineControllerComm::SetOldTime(float fOnTimeSec, float fOffTimeSec)
{
    if (m_bDemo)
    {
        Sleep(10);
        return TRUE;
    }
	BOOL bR;
	bR = SetOldTime_Sub(fOnTimeSec, fOffTimeSec);
	if (!bR)
	{
		Sleep(100);
		bR = SetOldTime_Sub(fOnTimeSec, fOffTimeSec);
		if (!bR)
		{
			Sleep(200);
			bR = SetOldTime_Sub(fOnTimeSec, fOffTimeSec);
		}	
	}

	return bR;
}

BOOL CLineControllerComm::SetOldTime_Sub(float fOnTimeSec, float fOffTimeSec)
{
	float fBurnTotalSeconds;

	fBurnTotalSeconds = fOffTimeSec + fOnTimeSec;

	fOffTimeSec = fBurnTotalSeconds;
	EnterCriticalSection(&m_critical);
	Sleep(200);
	HANDLE comHandle;
	if (!m_ser.Open(comHandle,m_strCOM, m_iBaudRate))
	{
		LeaveCriticalSection(&m_critical);
		return FALSE;
	}
	m_ser.SetReadTime(comHandle,1000, 1, 1000);

	int iON = (int)(fOffTimeSec * 10);
	// ON time
	BYTE ucOut[256];
	BYTE ucIn[256];
	ucOut[0] = 0x7B;
	ucOut[1] = 0x7B;
	ucOut[2] = 0x00;
	ucOut[3] = 0x08;
	ucOut[4] = iON / 256;

	ucOut[5] = iON % 256;
	ucOut[6] = 0x01;
	ucOut[7] = 0x7D;
	ucOut[8] = 0x7D;

	m_ser.Output(comHandle,ucOut, 9);
	if (!m_ser.Input(comHandle,ucIn, 9))
	{
		LeaveCriticalSection(&m_critical);
		m_ser.Close(comHandle);
		return FALSE;
	}
	
	Sleep(200);
	// OFF time
	int iOFF = (int)(fOnTimeSec * 10);
	ucOut[0] = 0x7B;
	ucOut[1] = 0x7B;
	ucOut[2] = 0x00;
	ucOut[3] = 0x10;
	ucOut[4] = iOFF / 256;

	ucOut[5] = iOFF % 256;
	ucOut[6] = 0x01;
	ucOut[7] = 0x7D;
	ucOut[8] = 0x7D;

	m_ser.Output(comHandle,ucOut, 9);
	if (!m_ser.Input(comHandle,ucIn, 9))
	{
		LeaveCriticalSection(&m_critical);
		m_ser.Close(comHandle);
		return FALSE;
	}

	m_ser.Close(comHandle);
	Sleep(100);
	LeaveCriticalSection(&m_critical);
	return TRUE;
}


BOOL CLineControllerComm::ClearAllState()
{
    if (m_bDemo)
    {
        Sleep(10);
        return TRUE;
    }
	BOOL bR;
	bR = ClearAllState_Sub();
	if (!bR)
	{
		Sleep(100);
		bR = ClearAllState_Sub();
		if (!bR)
		{
			Sleep(200);
			bR = ClearAllState_Sub();
		}	
	}

	return bR;
}


BOOL CLineControllerComm::ClearAllState_Sub()
{
	EnterCriticalSection(&m_critical);
	HANDLE comHandle;
	if (!m_ser.Open(comHandle,m_strCOM, m_iBaudRate))
	{
		LeaveCriticalSection(&m_critical);
		return FALSE;
	}
	m_ser.SetReadTime(comHandle,1000, 1, 1000);

	BYTE ucOut[256];
	BYTE ucIn[256];
	ucOut[0] = 0x7B;
	ucOut[1] = 0x7B;
	ucOut[2] = 0x00;
	ucOut[3] = 0x40;
	ucOut[4] = m_iSendData[4];

	ucOut[5] = 0x00;
	ucOut[6] = 0x01;
	ucOut[7] = 0x7D;
	ucOut[8] = 0x7D;

	m_ser.Output(comHandle,ucOut, 9);
	if (!m_ser.Input(comHandle,ucIn, 9))
	{
		LeaveCriticalSection(&m_critical);
		m_ser.Close(comHandle);
		return FALSE;
	}
	m_ser.Close(comHandle);
	Sleep(100);
	LeaveCriticalSection(&m_critical);
	return TRUE;
}


BOOL CLineControllerComm::SetBuzzer(BOOL bBuzzer)
{
	if (m_bDemo)
	{
		Sleep(10);
		return TRUE;
	}
	BOOL bR;
	bR = SetBuzzer_Sub(bBuzzer);
	if (!bR)
	{
		Sleep(100);
		bR = SetBuzzer_Sub(bBuzzer);
		if (!bR)
		{
			Sleep(200);
			bR = SetBuzzer_Sub(bBuzzer);
		}	
	}

	return bR;
}


BOOL CLineControllerComm::SetBuzzer_Sub(BOOL bBuzzer)
{
	EnterCriticalSection(&m_critical);
	Sleep(100);
	HANDLE comHandle;
	if (!m_ser.Open(comHandle,m_strCOM, m_iBaudRate))
	{
		LeaveCriticalSection(&m_critical);
		return FALSE;
	}
	m_ser.SetReadTime(comHandle,1000, 1, 1000);

	// ON time
	BYTE ucOut[256];
	BYTE ucIn[256];
	ucOut[0] = 0x7B;
	ucOut[1] = 0x7B;
	ucOut[2] = 0x00;
	ucOut[3] = 0x80;
	ucOut[4] = bBuzzer;

	ucOut[5] = 0x00;
	ucOut[6] = 0x01;
	ucOut[7] = 0x7D;
	ucOut[8] = 0x7D;

	m_ser.Output(comHandle,ucOut, 9);
	if (!m_ser.Input(comHandle,ucIn, 9))
	{
		m_ser.Close(comHandle);
		LeaveCriticalSection(&m_critical);
		return FALSE;
	}
	m_ser.Close(comHandle);
	Sleep(100);
	LeaveCriticalSection(&m_critical);
	return TRUE;
}

