#include "StdAfx.h"
#include "FujiTMPComm.h"
#include "LAT2000.h"
#include "EX_TmpDLL.h"


 

CFujiTMPComm::CFujiTMPComm(void)
{
	
}


CFujiTMPComm::~CFujiTMPComm(void)
{
}

void CFujiTMPComm::InitAddress(CArray<BYTE, BYTE> &ucAddress)
{
   m_ucAddress.RemoveAll();
   for (int i = 0; i < ucAddress.GetSize(); i ++)
   {
       m_ucAddress.Add(ucAddress[i]);
   }
}

void CFujiTMPComm::Initialize(CString strCOM, int iBaudrate /* = 9600 */)
{
	m_strCOM = strCOM;
	m_iBaudrate = iBaudrate;
	m_wxHighTMPRooomComm.SetCom(strCOM);
	m_wxHighTMPRooomComm.SetBaudrate(m_iBaudrate);	
	strCOM.Trim();
	strCOM.MakeUpper();
	int iCOM = 1;
	sscanf_s(strCOM.GetBuffer(), "COM%d", &iCOM);	
	TMP_InitCOM(iCOM,iBaudrate);
}

BOOL CFujiTMPComm::ReadTemperature(BYTE ucAddress, float & fTemperature, int &iAlam)
{
	CSingleLock(&m_criticalSection, TRUE);
	Sleep(200);
	/*int iAddress = ucAddress;
	return m_wxHighTMPRooomComm.GetPV(iAddress, fTemperature);*/
	return TMP_ReadData(ucAddress, fTemperature,iAlam);
}

BOOL CFujiTMPComm::SetTemperature(BYTE ucAddress, float fTemperature, float fTmpDown, float fTmpUp)
{
	CSingleLock(&m_criticalSection, TRUE);
	Sleep(200); 	/* ;
	/*int iAddress = ucAddress;
	if (!m_wxHighTMPRooomComm.SetSV(iAddress, fTemperature))
	{
		Sleep(200);
		return m_wxHighTMPRooomComm.SetSV(iAddress, fTemperature);
	}*/

	return TMP_WriteData(ucAddress,fTemperature,fTmpDown,fTmpUp);
	return TRUE;
}

BOOL CFujiTMPComm::Run(BYTE ucAddress)
{
	CSingleLock(&m_criticalSection, TRUE);
	Sleep(200);

	/*int iAddress = ucAddress;
	if (!m_wxHighTMPRooomComm.StandbyOff(iAddress))
	{
		Sleep(200);
		return m_wxHighTMPRooomComm.StandbyOff(iAddress);
	}*/
	TMP_SetState(ucAddress,0);

	return TRUE;
}


BOOL CFujiTMPComm::RunTwo()
{
	CSingleLock(&m_criticalSection, TRUE);
	Sleep(200);

	return Run(m_ucAddress[0]) && Run(m_ucAddress[1]);
}


BOOL CFujiTMPComm::Stop(BYTE ucAddress)
{
	CSingleLock(&m_criticalSection, TRUE);
	Sleep(200);

	TMP_SetState(ucAddress,1);
	return TRUE;
	
}


BOOL CFujiTMPComm::StopTwo()
{
	CSingleLock(&m_criticalSection, TRUE);
	Sleep(200);
	
	return Stop(m_ucAddress[0]) && Stop(m_ucAddress[1]);
}


BOOL CFujiTMPComm::SetSelfTruningMode(BYTE ucAddress)
{
    CSingleLock(&m_criticalSection, TRUE);
    Sleep(200);      

    int iAddress = ucAddress;
    return m_wxHighTMPRooomComm.SetSelfTruningMode(iAddress);
}


BOOL CFujiTMPComm::SetPIDTruning(BYTE ucAddress)
{
    CSingleLock(&m_criticalSection, TRUE);
    Sleep(200);      

    int iAddress = ucAddress;
    return m_wxHighTMPRooomComm.SetPIDTruning(iAddress);

}


BOOL CFujiTMPComm::GetPIDTruningState(BYTE ucAddress, int &iState)
{
    CSingleLock(&m_criticalSection, TRUE);
    Sleep(200);      

    int iAddress = ucAddress;
    return m_wxHighTMPRooomComm.GetPIDTruningState(iAddress, iState);
}


BOOL CFujiTMPComm::GetPID(BYTE ucAddress, float &fP, float &fI, float &fD)
{
    CSingleLock(&m_criticalSection, TRUE);
    Sleep(200);      

    int iAddress = ucAddress;
    return m_wxHighTMPRooomComm.GetPID(iAddress, fP, fI, fD);
}


BOOL CFujiTMPComm::SetInitPara(BYTE ucAddress)
{
    int iAddress = ucAddress;  
    Sleep(200);      
    if (!m_wxHighTMPRooomComm.SetP_n2Type(iAddress))
    {
        return FALSE;
    }

    Sleep(200);      
    if (!m_wxHighTMPRooomComm.SetP_dPType(iAddress))
    {
        return FALSE;
    }
    return TRUE;
}
