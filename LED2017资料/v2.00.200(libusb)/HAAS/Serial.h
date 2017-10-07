// Serial.h: interface for the Serial class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERIAL_H__7F44D5D6_35A2_11D6_80F1_52544CBE8249__INCLUDED_)
#define AFX_SERIAL_H__7F44D5D6_35A2_11D6_80F1_52544CBE8249__INCLUDED_

#define WM_RS_SET_RANGE    WM_USER+2000
#define WM_RS_SET_POS      WM_USER+2001

#define WM_SHOW_STATUS    (WM_USER+0x2224)//

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Serial  
{
public:
	float Tof(BYTE *bb,BOOL bF = TRUE);
	WORD CRC16(BYTE *paucMsg, int size);
	void SetStatus(CString strTemp);
	CString m_strStatus;
	HWND m_hWnd;

	void StrToByte(CString strTemp, BYTE bb[], int &iN);
	float ASCIItof(unsigned char *bb, int n, CString &strTemp);
	//通讯进度条
	CProgressCtrl *m_pProComm;
	//转化函数
	int bintoint(BYTE *bb);
	float btof(BYTE *bb);
	float btof196(BYTE *bb);
	void  WordToByte(WORD Word, BYTE &hByte, BYTE &lByte);
	//通讯函数
	BOOL SetAd(HANDLE &CommDev,CString sAd);                //地址通讯
	BOOL SetDCBParity(HANDLE &CommDev,BYTE Parity);         //第九位控制
	BOOL Input(HANDLE &CommDev,BYTE *InData, DWORD InN);    //接收数据
	BOOL Output(HANDLE &CommDev,BYTE *OutData, DWORD OutN); //发送数据
	BOOL SetReadTime(HANDLE &CommDev,int iReadIntervalTimeOut, int iReadTotalTimeoutMultiplier, int iReadTotalTimeoutConstant);   //超时设置
	BOOL Close(HANDLE &CommDev);                            //关串行口
	BOOL Open(HANDLE &CommDev,CString sCom, int iBaudRate); //打开串口
	Serial();
	virtual ~Serial();

};

#endif // !defined(AFX_SERIAL_H__7F44D5D6_35A2_11D6_80F1_52544CBE8249__INCLUDED_)
