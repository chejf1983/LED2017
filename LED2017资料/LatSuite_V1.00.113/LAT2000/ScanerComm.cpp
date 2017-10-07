#include "StdAfx.h"
#include "ScanerComm.h"
#include "TestContainer.h"
#include "LAT2000Doc.h"

extern CLAT2000Doc * g_pDoc;

CScanerComm::CScanerComm(void)
{
    m_strCOM = "COM16";
    m_iBaudRate = 9600;
    m_bStop = FALSE;
}


CScanerComm::~CScanerComm(void)
{
}


void CScanerComm::Initialize(CString strCOM, int iBaudRate)
{
    m_strCOM = strCOM;
    m_iBaudRate = iBaudRate;
}


void CScanerComm::SetDemo(BOOL bDemo)
{
    m_bDemo = bDemo;
}

BOOL CScanerComm::TryTest()
{
	if (m_bDemo)
	{
		Sleep(100);
		return SCAN_OK;
	}
	HANDLE comHandle;
	BOOL bR;
	bR = m_ser.Open(comHandle, m_strCOM, m_iBaudRate);
	if (!bR)
	{
		return SCAN_FAIL;
	}
	m_ser.Close(comHandle);
	return SCAN_OK;
}

BOOL CScanerComm::ScanOneSN(CString &strSN)
{
    if (m_bDemo)
    {
        Sleep(100);
        return SCAN_OK;
    }
	HANDLE comHandle;
    BOOL bR;
    bR = m_ser.Open(comHandle, m_strCOM, m_iBaudRate);
    if (!bR)
    {
        return SCAN_FAIL;
    }
    BYTE byteIn[256];
    CString strTemp = "";
    m_ser.SetReadTime(comHandle, 100, 2, 100);
    m_bStop = FALSE;
    while(1)
    {
        if (m_bStop)
        {
            m_ser.Close(comHandle);
            return SCAN_CANCEL;
        }
        if (m_ser.Input(comHandle,byteIn, 1))
        {
            strTemp += byteIn[0];
        }
        if (0x0D == byteIn[0])    // end code
        {     
            break;
        }
    }
    strSN = strTemp;
    m_ser.Close(comHandle);
    return SCAN_OK;
}


BOOL CScanerComm::ScanSN(int iNum, int ReadTimems)
{
	g_pDoc->m_TestContainer.m_tempRowLEDSN.m_strLEDSN.RemoveAll();
    if (m_bDemo)
    {
        m_strLedSN.RemoveAll();
		//RowLEDSN rowLEDSN; 
		for (int i = 0; i < iNum; i ++)
        {
            CString strSN;
            strSN.Format("%d", i + 1);
            m_strLedSN.Add(strSN);
			Sleep(200);
			g_pDoc->m_TestContainer.m_tempRowLEDSN.AddLEDSN(g_ScanerComm.m_strLedSN.GetAt(i));
        }
        Sleep(5000);
        return SCAN_OK;
    }
	HANDLE comHandle;
    BOOL bR;
    bR = m_ser.Open(comHandle,m_strCOM, m_iBaudRate);
    if (!bR)
    {
        return SCAN_FAIL;
    }
    DWORD dwTime = (DWORD)::GetCurrentTime();
    BYTE byteIn[256];
    m_ser.SetReadTime(comHandle,100, 2, 100);
    m_strLedSN.RemoveAll();
    int iTime = (int)::GetCurrentTime();  
    CString strTemp = "";
    m_bStop = FALSE;
    while(1)
    {
        if (m_bStop)
        {
            m_ser.Close(comHandle);
            return SCAN_CANCEL;
        }
        if (m_ser.Input(comHandle,byteIn, 1))
        {
            strTemp += byteIn[0];
        }
        if (0x0D == byteIn[0])    // end code
        {     
            BOOL m_bNotRepeat = TRUE;
            for (int i = 0; i < m_strLedSN.GetSize(); i ++)
            {
                if (strTemp == m_strLedSN.GetAt(i))
                {
                    m_bNotRepeat = FALSE;
                    break;
                }
            }
            if (m_bNotRepeat)
            {
                m_strLedSN.Add(strTemp);
				g_pDoc->m_TestContainer.m_tempRowLEDSN.AddLEDSN(strTemp);
            }
            strTemp = "";
        }
        byteIn[0] = ' ';
        if (m_strLedSN.GetSize() == iNum)
        {
            break;
        }
        if ((int)::GetCurrentTime() - iTime > ReadTimems)
        {
            m_ser.Close(comHandle);
			if (m_strLedSN.GetSize() == 0)
			{
				return SCAN_FAIL;
			}
			else
			{
				return SCAN_OVERTIME;
			}
        }
    }
    
    m_ser.Close(comHandle);
    return SCAN_OK;
}


void CScanerComm::SetStop()
{
    m_bStop = TRUE;
}
