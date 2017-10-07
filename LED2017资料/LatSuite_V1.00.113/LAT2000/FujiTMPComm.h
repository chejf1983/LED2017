#pragma once
#include "Comm.h"

#define TMP_CONTROLLER_NUMBER	2

class CFujiTMPComm
{
public:
	CFujiTMPComm(void);
	~CFujiTMPComm(void);

public:
	CArray<BYTE, BYTE> m_ucAddress;
    void InitAddress(CArray<BYTE, BYTE> &ucAddress);
public:
	void Initialize(CString strCOM, int iBaudrate = 9600);

	BOOL ReadTemperature(BYTE ucAddress, float & fTemperature, int &iAlam);
	
	BOOL SetTemperature(BYTE ucAddress, float fTemperature, float fTmpDown, float fTmpUp);

	BOOL Run(BYTE ucAddress);
	
	BOOL RunTwo();

	BOOL Stop(BYTE ucAddress);
	
	BOOL StopTwo();

    BOOL SetSelfTruningMode(BYTE ucAddress);

    BOOL SetPIDTruning(BYTE ucAddress);

    BOOL GetPIDTruningState(BYTE ucAddress, int &iState); 

    BOOL GetPID(BYTE ucAddress, float &fP, float &fI, float &fD);

    BOOL SetInitPara(BYTE ucAddress);
private:
	CComm m_wxHighTMPRooomComm;
	CString m_strCOM;
	int		m_iBaudrate;
	CCriticalSection m_criticalSection;
	BYTE ucAddress;
};

