#include "StdAfx.h"
#include "GaugeComm.h"
#include "DPSPowerComm.h"
#include "DPSDefinition.h"
#include "math.h"

extern BOOL g_bDemo;

CGaugeComm::CGaugeComm(void)
{
	m_strCOM = "COM1";
	m_iBaudrate = 9600;
}


CGaugeComm::~CGaugeComm(void)
{
}


void CGaugeComm::Initialize(CString strCOM /* =  */, int iBaudrate /* = 9600 */)
{
	m_strCOM = strCOM;
	m_iBaudrate = iBaudrate;
}


BOOL CGaugeComm::Read3(int iGaugeIndex, float & fVoltageV, float & fCurrentA, float & fPowerW)
{
	CSingleLock(&m_criticalSection, TRUE);
	Sleep(200);
	if (g_bDemo)
	{
		fVoltageV	= 220.0f + 10.0f * rand() / RAND_MAX;
		fCurrentA	= 1.0f + 0.2f * rand() / RAND_MAX;
		fPowerW		= fVoltageV * fCurrentA;
		return TRUE;
	}
	BOOL bR = Read(iGaugeIndex, fVoltageV, fCurrentA, fPowerW);
	if (!bR)
	{
		Sleep(200);
		bR = Read(iGaugeIndex, fVoltageV, fCurrentA, fPowerW);
		if (!bR)
		{
			Sleep(200);
			bR = Read(iGaugeIndex, fVoltageV, fCurrentA, fPowerW);

			return bR;
		}
	}

	return TRUE;
}


BOOL CGaugeComm::Read(int iAddress, float & fVoltageV, float & fCurrentA, float & fPowerW)
{
    if (1)
    {
        HANDLE comHandle;
        BOOL bR = m_ser.Open(comHandle,m_strCOM, m_iBaudrate);
        if (!bR)
        {
            return FALSE;
        }

        m_ser.SetReadTime(comHandle,1000, 10, 1000);
        Sleep(10);

        BYTE ucOut[32];
        BYTE ucIn[32];

        ucOut[0] = iAddress;	// Address

        // Voltage
        ucOut[1] = 0x03;	// Read
        ucOut[2] = 0x00;	// H
        ucOut[3] = 0x0B;	// L
        ucOut[4] = 0x00;	// H
        ucOut[5] = 0x02;	// L
        int iCrc = GetCRC(ucOut, 6);
        ucOut[6] = (BYTE)(iCrc % 256);
        ucOut[7] = (BYTE)(iCrc / 256);

        bR = m_ser.Output(comHandle,ucOut, 8);
        bR = m_ser.Input(comHandle,ucIn, 9);
        if (!bR)
        {
            m_ser.Close(comHandle);
            return FALSE;
        }

        fVoltageV = *(float *)&ucIn[3];

        // Current
        ucOut[1] = 0x03;	// Read
        ucOut[2] = 0x00;	// H
        ucOut[3] = 0x0C;	// L
        ucOut[4] = 0x00;	// H
        ucOut[5] = 0x02;	// L
        iCrc = GetCRC(ucOut, 6);
        ucOut[6] = (BYTE)(iCrc % 256);
        ucOut[7] = (BYTE)(iCrc / 256);

        bR = m_ser.Output(comHandle,ucOut, 8);
        bR = m_ser.Input(comHandle,ucIn, 9);
        if (!bR)
        {
            m_ser.Close(comHandle);
            return FALSE;
        }

        fCurrentA = *(float *)&ucIn[3];

        // Power
        ucOut[1] = 0x03;	// Read
        ucOut[2] = 0x00;	// H
        ucOut[3] = 0x0E;	// L
        ucOut[4] = 0x00;	// H
        ucOut[5] = 0x02;	// L
        iCrc = GetCRC(ucOut, 6);
        ucOut[6] = (BYTE)(iCrc % 256);
        ucOut[7] = (BYTE)(iCrc / 256);

        bR = m_ser.Output(comHandle,ucOut, 8);
        bR = m_ser.Input(comHandle,ucIn, 9);
        if (!bR)
        {
            m_ser.Close(comHandle);
            return FALSE;
        }

        fPowerW = *(float *)&ucIn[3];

        m_ser.Close(comHandle);
    }
	return TRUE;
}


UINT CGaugeComm::GetCRC(BYTE * pBuf, BYTE num)
{
	UINT i, j;
	UINT wCrc = 0xFFFF;
	for (i = 0; i < num; i++)
	{
		wCrc ^= (UINT)(pBuf[i]);
		for (j = 0; j < 8; j++)
		{
			if (wCrc & 1)
			{
				wCrc >>= 1;
				wCrc ^= 0xA001;
			}
			else
			{
				wCrc >>= 1;
			}
		}
	}

	return wCrc;
}