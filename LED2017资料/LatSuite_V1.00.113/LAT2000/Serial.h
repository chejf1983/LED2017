

#if !defined(AFX_SERIAL_H__)
#define AFX_SERIAL_H__

#if _MSC_VER > 1000
#pragma once
#endif 

/************************************************************************************************
	֡��ʽΪ��֡ͷ��0x7b 0x7b�� + Ŀ�ĵ�ַ��1 byte��+ Դ��ַ��1 byte�� + ���1 byte��
	+ ���ȣ�2 byte�� + ���ݣ�n byte�� + LRC��1byte��  + ֡β��0x7d 0x7d����

����:
	 PC��ַĬ��Ϊ0xee���豸��ַĬ��Ϊ0x7f��
	 LRC�����ۼ�У�飬������֡ͷ��֡β��
	 ���������������0x7b ��0x7d�������Ҫ��0x7b��0x7d�����Ч����,0x80,0x80�����ݳ��Ⱥ�LRC��û��Ӱ�졣
*************************************************************************************************/

class Serial  
{
public:
	Serial();
	virtual ~Serial();

public:
	BOOL IsOpened();
	// Convert function
	static float Tof(BYTE *bb,BOOL bF=FALSE);
	int bintoint(BYTE *bb);
	float btof(BYTE *bb);
	float btof196(BYTE *bb);
	void  WordToByte(WORD Word, BYTE &hByte, BYTE &lByte);
	void StrToByte(CString strTemp, BYTE bb[], int &iN);
	float ASCIItof(unsigned char *bb, int n, CString &strTemp);
	
	// Communication functions
	BOOL SetAd(HANDLE &ComHandle, BYTE bAd,BOOL bRe = TRUE);    //��ַͨѶ
	BOOL SetDCBParity(HANDLE comHandle, BYTE Parity);			//�ھ�λ����
	BOOL Input(HANDLE &ComHandle, BYTE *InData, DWORD InN);		//��������
	BOOL Output(HANDLE &ComHandle, BYTE *OutData, DWORD OutN);	//��������
	BOOL SetReadTime(HANDLE &ComHandle, int iReadIntervalTimeOut, int iReadTotalTimeoutMultiplier, int iReadTotalTimeoutConstant);   //��ʱ����
	BOOL Open(HANDLE &ComHandle, CString sCom, int iBaudRate);	//�򿪴���
	BOOL Close(HANDLE &ComHandle);								//�ش��п�
	
	// Send a package, ucCommand is the command of the package,
	// pData is the data of the package, nByte is the size of data
	BOOL SendPackage(HANDLE &ComHandle, BYTE ucCommand, BYTE * pData, int nByte);

	// Receive a package, ucCommand is the command of the package to receive,
	// pData is the buffer to receive data, nSize is the size of pData
	// nReceived is the byte count of valid data received
	// the return value is the number of no use 0x80 in data, none negative if successful
	int  ReceivePackage(HANDLE &ComHandle, BYTE ucCommand, BYTE * pData, int nSize, int & nReceived);

public:
	BYTE m_ucPCAddress;
	BYTE m_ucDeviceAddress;

private:
	// pByte is the data part of a package
	BOOL DoReadData_0x7B7D(BYTE *pByte, int &iN);

	// pOut is the data part of a package, nBytes is the size of data
	// iSize is the buffer size of pOut, iNewBytes is the size of data after precessing
	BOOL DoWriteData_0x7B7D(BYTE * pOut, int nBytes, int iSize, int & iNewBytes);


	CMutex m_mutex;
};


#endif 