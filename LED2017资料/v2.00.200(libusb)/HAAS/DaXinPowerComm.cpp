// DaXinPowerComm.cpp: implementation of the CDaXinPowerComm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DaXinPowerComm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDaXinPowerComm::CDaXinPowerComm()
{
	m_strCOM	= "COM5";
	m_iBaudRate = 38400;
}

CDaXinPowerComm::~CDaXinPowerComm()
{

}

BOOL CDaXinPowerComm::DX_Power_Init(int iCOM)
{
	m_strCOM.Format("COM%d",iCOM);

	BOOL bR;
	HANDLE comHandle;
	if (!m_ser.Open(comHandle, m_strCOM, m_iBaudRate))
	{
		return FALSE;
	}
	BOOL bRemote = TRUE;
	BYTE ucOut[100], ucIn[256];
	int iOut = 0;
	ucOut[iOut++] = 0xA5; //帧头
	ucOut[iOut++] = 0x5A; //帧头
	ucOut[iOut++] = DX_ADDR_PRO;
	ucOut[iOut++] = DX_ADDR_CMP;
	ucOut[iOut++] = 0x26;
	ucOut[iOut++] = 0x80;
	ucOut[iOut++] = 0x01;
	if (bRemote)
		ucOut[iOut++] = 0x01;
	else
		ucOut[iOut++] = 0x00;
	
	WORD wCRC;
	BYTE bCheckCRC[10];
	for (int i = 0; i < (iOut - 2); i++)
	{
		bCheckCRC[i] = ucOut[2 + i];
	}
	wCRC = m_ser.CRC16(bCheckCRC,iOut - 2);
	
	ucOut[iOut++] = (BYTE)(wCRC/256);
	ucOut[iOut++] = (BYTE)(wCRC%256);
	
	m_ser.Output(comHandle,ucOut,iOut);
	m_ser.SetReadTime(comHandle, 2000, 1, 2000);
	
	bR = m_ser.Input(comHandle,ucIn,10);
	if (!bR || ucIn[7]!=0x00)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}
	
	m_ser.Close(comHandle);
	return TRUE;
}

BOOL CDaXinPowerComm::DX_Power_SetPara(float fVol, float fCurr)
{
	//电流单位为mA
	BOOL bR;
	HANDLE comHandle;
	if (!m_ser.Open(comHandle, m_strCOM, m_iBaudRate))
	{
		return FALSE;
	}
	
	BYTE ucOut[100], ucIn[256];
	int iOut = 0;
	ucOut[iOut++] = 0xA5; //帧头
	ucOut[iOut++] = 0x5A; //帧头
	ucOut[iOut++] = DX_ADDR_PRO;
	ucOut[iOut++] = DX_ADDR_CMP;

	ucOut[iOut++] = DX_SET_VOLT;
	ucOut[iOut++] = 0x80;
	int iVol = (int)(fVol * 100); //转化为10mV
	ucOut[iOut++] = 0x02; //电压最大为3000（30V）
	ucOut[iOut++] = (BYTE)(iVol / 256);
	ucOut[iOut++] = (BYTE)(iVol % 256);

	WORD wCRC;
	BYTE bCheckCRC[10];
	for (int i = 0; i < (iOut - 2); i++)
	{
		bCheckCRC[i] = ucOut[2 + i];
	}
	wCRC = m_ser.CRC16(bCheckCRC,iOut - 2);

	ucOut[iOut++] = (BYTE)(wCRC/256);
	ucOut[iOut++] = (BYTE)(wCRC%256);

	m_ser.Output(comHandle,ucOut,iOut);
	m_ser.SetReadTime(comHandle, 2000, 1, 2000);

	bR = m_ser.Input(comHandle,ucIn,10);
	if (!bR || ucIn[7]!=0x00)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}
	//下面设置电流值
	iOut = 0;
	ucOut[iOut++] = 0xA5; //帧头
	ucOut[iOut++] = 0x5A; //帧头
	ucOut[iOut++] = DX_ADDR_PRO;
	ucOut[iOut++] = DX_ADDR_CMP;
	
	ucOut[iOut++] = DX_SET_CURR;
	ucOut[iOut++] = 0x80;
	int iCurr = (int)(fCurr);
	ucOut[iOut++] = 0x02; //最大为3000（3A）
	ucOut[iOut++] = (BYTE)(iCurr / 256);
	ucOut[iOut++] = (BYTE)(iCurr % 256);
	
	wCRC = m_ser.CRC16(&ucOut[2], iOut - 2);
	ucOut[iOut++] = (BYTE)(wCRC/256);
	ucOut[iOut++] = (BYTE)(wCRC%256);
	
	m_ser.Output(comHandle,ucOut,iOut);
	m_ser.SetReadTime(comHandle, 2000, 1, 2000);
	
	bR = m_ser.Input(comHandle,ucIn,10);
	if (!bR || ucIn[7]!=0x00)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}

	m_ser.Close(comHandle);
	return TRUE;
}

BOOL CDaXinPowerComm::DX_Power_Output(BOOL bOn)
{
	BOOL bR;
	HANDLE comHandle;
	if (!m_ser.Open(comHandle, m_strCOM, m_iBaudRate))
	{
		return FALSE;
	}
	
	BYTE ucOut[100], ucIn[256];
	int iOut = 0;
	ucOut[iOut++] = 0xA5; //帧头
	ucOut[iOut++] = 0x5A; //帧头
	ucOut[iOut++] = DX_ADDR_PRO;
	ucOut[iOut++] = DX_ADDR_CMP;
	ucOut[iOut++] = DX_SET_OUTPUT;
	ucOut[iOut++] = 0x80;
	ucOut[iOut++] = 0x01;
	if (bOn)
		ucOut[iOut++] = 0x01;
	else
		ucOut[iOut++] = 0x00;

	WORD wCRC;
	BYTE bCheckCRC[10];
	for (int i = 0; i < (iOut - 2); i++)
	{
		bCheckCRC[i] = ucOut[2 + i];
	}
	wCRC = m_ser.CRC16(bCheckCRC,iOut - 2);
	
	ucOut[iOut++] = (BYTE)(wCRC/256);
	ucOut[iOut++] = (BYTE)(wCRC%256);
	
	m_ser.Output(comHandle,ucOut,iOut);
	m_ser.SetReadTime(comHandle, 2000, 1, 2000);
	
	bR = m_ser.Input(comHandle,ucIn,10);
	if (!bR || ucIn[7]!=0x00)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}

	m_ser.Close(comHandle);
	return TRUE;
}

BOOL CDaXinPowerComm::DX_Power_ReadPara(float &fVol, float &fCurr)
{
	BOOL bR;
	HANDLE comHandle;
	if (!m_ser.Open(comHandle, m_strCOM, m_iBaudRate))
	{
		return FALSE;
	}
	
	BYTE ucOut[100], ucIn[256];
	int iOut = 0;
	ucOut[iOut++] = 0xA5; //帧头
	ucOut[iOut++] = 0x5A; //帧头
	ucOut[iOut++] = DX_ADDR_PRO;
	ucOut[iOut++] = DX_ADDR_CMP;
	
	ucOut[iOut++] = DX_READ_PARA;
	ucOut[iOut++] = 0x80;
	ucOut[iOut++] = 0x00; //电压最大为3000（30V）
	
	WORD wCRC;
	BYTE bCheckCRC[10];
	for (int i = 0; i < (iOut - 2); i++)
	{
		bCheckCRC[i] = ucOut[2 + i];
	}
	wCRC = m_ser.CRC16(bCheckCRC,iOut - 2);
	ucOut[iOut++] = (BYTE)(wCRC/256);
	ucOut[iOut++] = (BYTE)(wCRC%256);
	
	m_ser.Output(comHandle,ucOut,iOut);
	m_ser.SetReadTime(comHandle, 2000, 1, 2000);
	
	bR = m_ser.Input(comHandle,ucIn,14);
	if (!bR)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}
	fVol = (float)((ucIn[8] * 256 + ucIn[9])) /100.0f;
	fCurr = (float)(ucIn[10] * 256 + ucIn[11]);
	m_ser.Close(comHandle);
	return TRUE;
}
