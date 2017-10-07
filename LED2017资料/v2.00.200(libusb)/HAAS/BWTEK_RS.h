// BWTEK_RS.h: interface for the CBWTEK_RS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BWTEK_RS_H__67070961_00FA_11DB_949C_00055D02EEF1__INCLUDED_)
#define AFX_BWTEK_RS_H__67070961_00FA_11DB_949C_00055D02EEF1__INCLUDED_

#include "BWSerial.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBWTEK_RS  
{
public:
	BOOL Scan_N(int iIntTime,int iAveN,float fAD[]);
	int m_iBaudRate;
	int m_iIntTime;
	int m_iAveN;
	BOOL SetAveNum(int iAveN);
	BOOL Scan(int iIntTime,int iAveN,float fAD[]);
	BOOL SetRaudRate(int iRaudRate);
	BOOL SetDataMode(int iMode);
	BOOL SetIntTime(int iIntTime);
	BOOL UnInit();
	BOOL Init(CString strCom,int iBaudrate);
	BWSerial BWSer;
	HANDLE m_CommDev;
	CBWTEK_RS();
	virtual ~CBWTEK_RS();

};

#endif // !defined(AFX_BWTEK_RS_H__67070961_00FA_11DB_949C_00055D02EEF1__INCLUDED_)
