// NPPowerMeterComm.cpp: implementation of the CNPPowerMeterComm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NPPowerMeterComm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNPPowerMeterComm::CNPPowerMeterComm()
{
	m_strCOM	= "COM5";
	m_iBaudRate = 9600;
}

CNPPowerMeterComm::~CNPPowerMeterComm()
{

}
BOOL CNPPowerMeterComm::NP_Power_Init(int iCOM)
{
	m_strCOM.Format("COM%d",iCOM);
	return TRUE;
}

BOOL CNPPowerMeterComm::NP_Power_ReadData(float &fU,float &fI,float &fPower,float &fFreq,float &fPF)
{
	BOOL bR;
	HANDLE comHandle;
	if (!m_ser.Open(comHandle, m_strCOM, m_iBaudRate))
	{
		return FALSE;
	}
	
	BYTE ucOut[100], ucIn[256];
	int iOut = 0;
	ucOut[iOut++] = 0x55; //֡ͷ
	ucOut[iOut++] = 0x00; //֡ͷ
	ucOut[iOut++] = 0x10;
	ucOut[iOut++] = 0x65;
	
	m_ser.Output(comHandle,ucOut,iOut);
	m_ser.SetReadTime(comHandle, 2000, 1, 2000);
	
	bR = m_ser.Input(comHandle,ucIn,24);
	if (!bR)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}
	fU = m_ser.Tof(&ucIn[3 + 4 * 0]);
	fI = m_ser.Tof(&ucIn[3 + 4 * 1]);
	fPower = m_ser.Tof(&ucIn[3 + 4 * 2]);
	fFreq = m_ser.Tof(&ucIn[3 + 4 * 3]);
	fPF = m_ser.Tof(&ucIn[3 + 4 * 4]);
	m_ser.Close(comHandle);
	return TRUE;

}
