#include "StdAfx.h"
#include "IndicatorComm.h"


CIndicatorComm::CIndicatorComm(void)
{
	m_strCOM = "COM1";
	m_iBaudrate = 9600;

	m_ser.m_ucPCAddress = 0xEE;
	m_ser.m_ucDeviceAddress = 0x9F;

	for (int i = 0; i < 32; i++)
	{
		m_state[i] = CHANNEL_OFF;
	}
}


CIndicatorComm::~CIndicatorComm(void)
{
}


void CIndicatorComm::Initialize(CString strCOM)
{
	m_strCOM = strCOM;
}


BOOL CIndicatorComm::IsConnected()
{
	return SetAllChannelState(m_state);
}


BOOL CIndicatorComm::SetAllChannelState(ChannelState iState[])
{
	ASSERT(NULL != iState);
	HANDLE comHandle;
	// 1
	m_state[0] = iState[0];
	m_state[1] = iState[1];
	m_state[2] = iState[2];
	m_state[3] = iState[3];

	// 2
	m_state[4] = iState[5];
	m_state[5] = iState[6];
	m_state[6] = iState[7];
	m_state[7] = iState[8];

	// 3
	m_state[8] = iState[4];
	m_state[9] = iState[10];
	m_state[10] = iState[11];
	m_state[11] = iState[12];

	// 4
	m_state[12] = iState[9];
	m_state[13] = iState[15];
	m_state[14] = iState[16];
	m_state[15] = iState[17];
	
	// 5
	m_state[16] = iState[13];
	m_state[17] = iState[14];
	m_state[18] = iState[20];
	m_state[19] = iState[21];

	// 6
	m_state[20] = iState[18];
	m_state[21] = iState[19];
	m_state[22] = iState[25];
	m_state[23] = iState[26];

	// 7
	m_state[24] = iState[22];
	m_state[25] = iState[23];
	m_state[26] = iState[24];
	m_state[27] = CHANNEL_OFF;	// Not use

	// 8
	m_state[28] = iState[27];
	m_state[29] = iState[28];
	m_state[30] = iState[29];
	m_state[31] = CHANNEL_OFF;	// Not use

	BYTE ucTemp, ucOut[8] = {0};
	
	for (int i = 0; i < 32; i++)
	{
		ucTemp = m_state[i];
		int iMove = (i % 4) * 2;
		if (iMove > 0)
		{
			ucTemp <<= iMove;
		}
		ucOut[i / 4] |= ucTemp;
	}

	BOOL bR = m_ser.Open(comHandle,m_strCOM, m_iBaudrate);
	if (!bR)
	{
		return FALSE;
	}
	m_ser.SetReadTime(comHandle,1000, 1, 2000);

	m_ser.SendPackage(comHandle,0xA5, ucOut, 8);

	BYTE ucIn[32];
	int nRecieve;
	bR = m_ser.ReceivePackage(comHandle,0xA5, ucIn, 32, nRecieve);
	m_ser.Close(comHandle);
	if (bR < 0)
	{
		return FALSE;
	}
	if (8 != nRecieve)
	{
		return TRUE;
	}
	
	return TRUE;
}
