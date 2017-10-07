#pragma once
#include "Serial.h"
enum
{
	SCAN_FAIL,
	SCAN_OK,
	SCAN_CANCEL,
	SCAN_OVERTIME,
};
class CScanerComm
{
public:
    CScanerComm(void);
    ~CScanerComm(void);
	void SetDemo(BOOL bDemo);
	void Initialize(CString strCOM, int iBaudRate = 9600);
	BOOL TryTest();
    BOOL ScanOneSN(CString &strSN);
    BOOL ScanSN(int iNum, int ReadTimems);
    void SetStop();
    CArray<CString, CString>m_strLedSN;
private:
    Serial	m_ser;
    CString m_strCOM;
    int		m_iBaudRate;
    BOOL m_bStop;
    BOOL m_bDemo;
};

