

#if !defined(AFX_SERIAL_H__)
#define AFX_SERIAL_H__

#if _MSC_VER > 1000
#pragma once
#endif 

/************************************************************************************************
	帧格式为：帧头（0x7b 0x7b） + 目的地址（1 byte）+ 源地址（1 byte） + 命令（1 byte）
	+ 长度（2 byte） + 数据（n byte） + LRC（1byte）  + 帧尾（0x7d 0x7d）；

其中:
	 PC地址默认为0xee，设备地址默认为0x7f；
	 LRC采用累加校验，不包括帧头和帧尾；
	 如果遇到数据中有0x7b 或0x7d的情况，要在0x7b或0x7d后加无效数据,0x80,0x80对数据长度和LRC都没有影响。
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
	BOOL SetAd(HANDLE &ComHandle, BYTE bAd,BOOL bRe = TRUE);    //地址通讯
	BOOL SetDCBParity(HANDLE comHandle, BYTE Parity);			//第九位控制
	BOOL Input(HANDLE &ComHandle, BYTE *InData, DWORD InN);		//接收数据
	BOOL Output(HANDLE &ComHandle, BYTE *OutData, DWORD OutN);	//发送数据
	BOOL SetReadTime(HANDLE &ComHandle, int iReadIntervalTimeOut, int iReadTotalTimeoutMultiplier, int iReadTotalTimeoutConstant);   //超时设置
	BOOL Open(HANDLE &ComHandle, CString sCom, int iBaudRate);	//打开串口
	BOOL Close(HANDLE &ComHandle);								//关串行口
	
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