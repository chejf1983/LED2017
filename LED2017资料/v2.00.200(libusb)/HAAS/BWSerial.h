// BWSerial.h: interface for the BWSerial class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BWSerial_H__7F44D5D6_35A2_11D6_80F1_52544CBE8249__INCLUDED_)
#define AFX_BWSerial_H__7F44D5D6_35A2_11D6_80F1_52544CBE8249__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//专门用作BW仪器RS232通讯类
class BWSerial  
{
public:
	BOOL Clear(HANDLE &CommDev);
	void StrToByte(CString strTemp, BYTE bb[], int &iN);
	float ASCIItof(unsigned char *bb, int n,CString &strTemp);
	CString sStringTo(BYTE *bb, int number);
	BOOL SetDCBParity(HANDLE &CommDev,BYTE Parity);
	BOOL SetAd(HANDLE &CommDev, CString sAd);
	float btof(BYTE *bb);
	float btof196(BYTE *bb);
	void WordToByte(WORD Word, BYTE &hByte, BYTE &lByte);
	BOOL Input(HANDLE &CommDev,BYTE *InData, DWORD InN);
	BOOL Output(HANDLE &CommDev,BYTE *OutData, DWORD OutN);
	BOOL SetReadTime(HANDLE &CommDev,int iReadIntervalTimeOut, int iReadTotalTimeoutMultiplier, int iReadTotalTimeoutConstant);
	BOOL Close(HANDLE &CommDev);
	BOOL Open(HANDLE &CommDev,CString sCom, int iBaudRate);
	BWSerial();
	virtual ~BWSerial();

};

#endif // !defined(AFX_BWSerial_H__7F44D5D6_35A2_11D6_80F1_52544CBE8249__INCLUDED_)
