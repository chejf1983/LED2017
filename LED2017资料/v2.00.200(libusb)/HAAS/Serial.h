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
	//ͨѶ������
	CProgressCtrl *m_pProComm;
	//ת������
	int bintoint(BYTE *bb);
	float btof(BYTE *bb);
	float btof196(BYTE *bb);
	void  WordToByte(WORD Word, BYTE &hByte, BYTE &lByte);
	//ͨѶ����
	BOOL SetAd(HANDLE &CommDev,CString sAd);                //��ַͨѶ
	BOOL SetDCBParity(HANDLE &CommDev,BYTE Parity);         //�ھ�λ����
	BOOL Input(HANDLE &CommDev,BYTE *InData, DWORD InN);    //��������
	BOOL Output(HANDLE &CommDev,BYTE *OutData, DWORD OutN); //��������
	BOOL SetReadTime(HANDLE &CommDev,int iReadIntervalTimeOut, int iReadTotalTimeoutMultiplier, int iReadTotalTimeoutConstant);   //��ʱ����
	BOOL Close(HANDLE &CommDev);                            //�ش��п�
	BOOL Open(HANDLE &CommDev,CString sCom, int iBaudRate); //�򿪴���
	Serial();
	virtual ~Serial();

};

#endif // !defined(AFX_SERIAL_H__7F44D5D6_35A2_11D6_80F1_52544CBE8249__INCLUDED_)
