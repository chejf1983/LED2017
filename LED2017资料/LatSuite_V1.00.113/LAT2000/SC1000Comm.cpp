#include "StdAfx.h"
#include "SC1000Comm.h"

CSC1000Comm::CSC1000Comm()
{
	m_iBaudRate = 9600;
	m_ucDeviceAddress = 0x01;
	
	int i = 0;
	for(i = 0; i < 16; i++)
		m_bSaveOnFlag[i] = FALSE;

	for(i = 0; i < 8; i++)
		m_bSaveOutFlag[i] = FALSE;

	for(i = 0; i < 8; i++)
		m_bSaveOutFlag[i] = FALSE;
}

CSC1000Comm::~CSC1000Comm()
{
}


void CSC1000Comm::Initialize(CString strCOM, int iAddr, BOOL bEnglish)
{
	m_strCOM = strCOM;
	m_bEnglish = bEnglish;
}


BOOL CSC1000Comm::SetOnOff(BOOL bOn[])
{
	for(int i = 0; i < SC1000_LAMP_NUM; i++)
	{
		m_bSaveOnFlag[i] = bOn[i];
	}

	return Communicate(m_bSaveOnFlag, m_bSaveOutFlag, m_bSaveInputFlag, TRUE);
}


//
// 退出远程, 退出远程才能手动操作SC1000仪器面板上的按键
//
BOOL CSC1000Comm::ExitRemoteMode()
{
	return Communicate(m_bSaveOnFlag, m_bSaveOutFlag, m_bSaveInputFlag, FALSE);
}


// Set iCannel to -1 to turn off all channel
BOOL CSC1000Comm::SwitchChannel(int iChannel)
{
	int iFlag[SC1000_LAMP_NUM];
	for (int i = 0; i < SC1000_LAMP_NUM; i++)
	{
		iFlag[i] = i == iChannel;
	}

	return SetOnOff(iFlag);
}


BOOL CSC1000Comm::SetBuzzer(BOOL bOn)
{
	m_bSaveOutFlag[0] = bOn;

	return Communicate(m_bSaveOnFlag, m_bSaveOutFlag, m_bSaveInputFlag, TRUE);
}


BOOL CSC1000Comm::SwitchAllLamp(BOOL bON)
{
	BOOL bFlag[SC1000_LAMP_NUM];
	for (int i = 0; i < SC1000_LAMP_NUM; i++)
	{
		bFlag[i] = bON;
	}

	return SetOnOff(bFlag);
}


WORD CSC1000Comm::Pri_SC1000_TestState2WORD(BOOL bOnFlag[])
{
	int i;
	// high 8
	BYTE byte = 0x00;
	BYTE byteTemp;
	for(i = 0; i < 8; i++)
	{	
		byteTemp = 0x00;
		if(bOnFlag[i] == TRUE)
		{
			byteTemp = 0x01;
			byteTemp = byteTemp << i;
		}
		byte += byteTemp;
	}
	
	// low 8
	BYTE byte2 = 0x00;
	BYTE byteTemp2;
	for(i = 0; i < 8; i++)
	{	
		byteTemp2 = 0x00;
		if(bOnFlag[i + 8] == TRUE)
		{
			byteTemp2 = 0x01;
			byteTemp2 = byteTemp2 << i;
		}
		byte2 += byteTemp2;
	}
	
	return byte * 256  + byte2;
}

BYTE CSC1000Comm::Pri_SC1000_Output2BYTE(BOOL bOutputFlag[])
{
	int i;
	// high 8
	BYTE byte = 0x00;
	BYTE byteTemp;
	for(i = 0; i < 8; i++)
	{	
		byteTemp = 0x00;
		if(bOutputFlag[i] == TRUE)
		{
			byteTemp = 0x01;
			byteTemp = byteTemp << i;
		}
		byte += byteTemp;
	}
	return byte;
}

void CSC1000Comm::Pri_SC1000_BYTE2Input(BYTE byte, BOOL bInputFlag[])
{
	int i;
	for(i = 0; i < 8; i++)
	{	
		BYTE byteTemp = 0x01;
		byteTemp = byteTemp << i;
		if((byte & byteTemp) != 0x00)
			bInputFlag[i] = TRUE;
		else
			bInputFlag[i] = FALSE;
	}
}

BOOL CSC1000Comm::Communicate(BOOL bOn[], BOOL bOutputFlag[], BOOL bInputFlag[], BOOL bRemote)
{
	BYTE Out[100],In[100];
	BOOL bR;
	HANDLE comHandle;
	bR = m_ser.Open(comHandle,m_strCOM, 9600);
	if(!bR)
	{
		return FALSE;
	}
	m_ser.SetReadTime(comHandle,1500, 2, 1500);
	
	WORD dw1 = Pri_SC1000_TestState2WORD(bOn);
	
	Out[0] = 0x7B;
	Out[1] = 0x7B;
	Out[2] = m_ucDeviceAddress;
	Out[3] = (BYTE)(dw1 >> 8);
	Out[4] = (BYTE)(dw1 >> 0);
	Out[5] = 0xFF;  
	Out[6] = Pri_SC1000_Output2BYTE(bOutputFlag);   //
	Out[7] = bRemote ? 0x01 : 0x00;
	Out[8] = 0x7D;
	Out[9] = 0x7D;
	
	m_ser.Output(comHandle,Out, 10);
	bR = m_ser.Input(comHandle,In, 10);
	if(bR)
	{
		Pri_SC1000_BYTE2Input(In[5], bInputFlag);
		m_ser.Close(comHandle);	
		return TRUE;
	}
	else
	{
		m_ser.Close(comHandle);	
		return FALSE;
	}

	Sleep(200);
	m_ser.Close(comHandle);	
	return FALSE;
}