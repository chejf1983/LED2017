// NPPowerMeterComm.h: interface for the CDaXinPowerComm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPPOWERMETERCOMM_H__E78EC153_A1E9_4820_BD7F_7908BD422EAE__INCLUDED_)
#define AFX_NPPOWERMETERCOMM_H__E78EC153_A1E9_4820_BD7F_7908BD422EAE__INCLUDED_

#include "Serial.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNPPowerMeterComm : public CObject  
{
public:
	CString m_strCOM;
	int m_iBaudRate;

	BOOL NP_Power_Init(int iCOM);

	BOOL NP_Power_ReadData(float &fU,float &fI,float &fPower,float &fFreq,float &fPF);

	Serial m_ser;

	CNPPowerMeterComm();
	virtual ~CNPPowerMeterComm();

};

#endif // !defined(AFX_NPPOWERMETERCOMM_H__E78EC153_A1E9_4820_BD7F_7908BD422EAE__INCLUDED_)
