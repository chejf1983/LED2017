// Serial.cpp: implementation of the Serial class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Serial.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Serial::Serial()
{
	m_ucPCAddress = 0xEE;
	m_ucDeviceAddress = 0x7F;
}

Serial::~Serial()
{
}

BOOL Serial::IsOpened()
{
	return TRUE;
}

BOOL Serial::Open(HANDLE &ComHandle,CString sCom, int iBaudRate)
{
	int iSN = atoi(sCom.Right(sCom.GetLength() - 3));
	sCom.Trim();
	if (sCom.GetLength() == 5)
	{
		sCom = "\\\\.\\" + sCom;
	}

	DCB dcb;
	ComHandle = CreateFile(sCom,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
	
	if(ComHandle == INVALID_HANDLE_VALUE) 
	{
		Sleep(100);
		return FALSE;
	}
	if(GetCommState(ComHandle, &dcb) == FALSE)
	{
	    return FALSE;
	}
	
 	dcb.BaudRate	= iBaudRate;
	dcb.Parity		= NOPARITY;//
	dcb.ByteSize	= 8;
	dcb.StopBits	= ONESTOPBIT;
	dcb.fRtsControl	= RTS_CONTROL_ENABLE;
	if(SetCommState(ComHandle,&dcb)==FALSE) 
	{
	    return FALSE;
	}
    SetupComm(ComHandle,4096*10,4096*10);

	// Set default read time
	SetReadTime(ComHandle, 1000, 1, 2000);

	return TRUE;
}

BOOL Serial::Close(HANDLE &ComHandle)
{
	CloseHandle(ComHandle);
	return TRUE;
}

BOOL Serial::SetReadTime(HANDLE &ComHandle, int iReadIntervalTimeOut, int iReadTotalTimeoutMultiplier, int iReadTotalTimeoutConstant)
{
	COMMTIMEOUTS tout;
	if(GetCommTimeouts(ComHandle, &tout)==FALSE)
	{
		return FALSE;
	}
	tout.ReadIntervalTimeout=iReadIntervalTimeOut;     
	tout.ReadTotalTimeoutMultiplier=iReadTotalTimeoutMultiplier; 
    tout.ReadTotalTimeoutConstant=iReadTotalTimeoutConstant; 
    //tout.WriteTotalTimeoutMultiplier; 
    //tout.WriteTotalTimeoutConstant; 
	if(SetCommTimeouts(ComHandle, &tout) == FALSE)
	{
		return FALSE;
	}
	Sleep(10);
	return TRUE;
}


BOOL Serial::Output(HANDLE &ComHandle,BYTE *OutData, DWORD OutN)
{
	DWORD N;	
	BOOL bR;
	bR = WriteFile(ComHandle, OutData, OutN, &N, NULL);
	if (!bR || N < OutN)
	{
		return FALSE;
	}

	//for(int i=0;i<(int)OutN;i++)
	//{
	//	BYTE Out[1];
	//	Out[0]=OutData[i];
	//	bR=WriteFile(CommDev,Out,1,&N,NULL);
	//	if(!bR||N<1)
	//	{
	//		return FALSE;
	//	}
	//	else
	//	{
	//	}
	//}

	return TRUE;
}


BOOL Serial::Input(HANDLE &ComHandle,BYTE *InData, DWORD InN)
{
	DWORD N;
	BOOL bR;

	bR=ReadFile(ComHandle, InData, InN, &N, NULL);
	if (!bR || N < InN)
	{
		return FALSE;
	}

	//for(int i=0;i<(int)InN;i++)
	//{
	//	BYTE In[1];		
	//	bR=ReadFile(CommDev,In,1,&N,NULL);
	//	if(!bR||N<1)
	//	{
	//		return FALSE;
	//	}
	//	else
	//	{
	//		InData[i]=In[0];
	//	}
	//}

	return TRUE;
}


void Serial::WordToByte(WORD Word, BYTE &hByte, BYTE &lByte)
{
	lByte=BYTE(Word);
	Word=Word>>8;
	hByte=BYTE(Word);
}


float Serial::btof196(BYTE *bb)
{
	char sig;
	union zho
	{unsigned char str[4];
	float flt;
	unsigned long zhon;
	}zho;

	/*float  *flt;
	unsigned long  *zhon;
	unsigned char str[4];*/
	unsigned char zhog;
	sig=bb[3];
	sig&=0x80;/*printf("%d\n",sig);*/
	if(bb[0]==0) 
		zho.str[3]=bb[0];
	else
		zho.str[3]=(bb[0]-1);
	zhog=zho.str[3];
	zho.str[2]=bb[3]&0x7f;
	zho.str[1]=bb[2];
	zho.str[0]=bb[1];
	/*zhon=&str[0];*/ /*printf("%ld\n",*zhon);*/
	zho.zhon=zho.zhon<<1;		/*printf("%ld\n",zho.zhon);*/
	zho.str[3]=zhog;
	zho.zhon=zho.zhon>>1;
	zho.str[3]|=sig;
	/*flt=&str[0];*/
	return(zho.flt);
}


float Serial::btof(BYTE *bb)
{
	float var;
	struct bytes
	{
		unsigned bt6:6;
		unsigned bt7:1;
		unsigned bt8:1;
	};
	union bytt
	{
		struct bytes bits;
		unsigned short chars;
	} bbt;

	bbt.chars=bb[0];
	//printf("%x   %x   %x\n",bitt[0],bitt[1],bitt[2]);
	var=(float)((1.0-2*bbt.bits.bt8)*(float)(bb[1]*256.0+bb[2])/pow(2.0,16.0));
	if(bbt.bits.bt7==1) 
	bbt.bits.bt6=~bbt.bits.bt6+1;
	var*=(float)(pow(2.0,(1.0-2*bbt.bits.bt7)*bbt.bits.bt6));
	//printf("var=%f\n",var);

	return(var);
}


BOOL Serial::SetDCBParity(HANDLE comHandle, BYTE Parity)
{
	DCB dcb;
	if(GetCommState(comHandle, &dcb)==FALSE)
	    return FALSE;
	dcb.Parity=Parity;//NOPARITY         
	                  //ODDPARITY
                      //EVENPARITY
                      //MARKPARITY
                      //SPACEPARITY 
	if(SetCommState(comHandle,&dcb)==FALSE) 
	    return FALSE;
	return TRUE;
}


BOOL Serial::SetAd(HANDLE &ComHandle, BYTE bAd,BOOL bRe)
{
	BOOL bR;
	SetReadTime(ComHandle,2500,2,2500);
	BYTE Out[1],In[1];
	Out[0] = bAd;
	SetDCBParity(ComHandle, MARKPARITY);
	Output(ComHandle,Out,1);
	if(bRe)
	{
		bR=Input(ComHandle,In,1);
		SetDCBParity(ComHandle, SPACEPARITY);
		if(!bR||(In[0]!=BYTE(~Out[0])))
		{
			return FALSE;
		}
		else
		{
			Sleep(10);
			return TRUE;
		}
	}
	else
	{
		Sleep(100);
		return TRUE;
	}
}


int Serial::bintoint(BYTE *bb)
{
	return(bb[0]+(bb[1]<<8));
}


float Serial::ASCIItof(unsigned char *bb, int n, CString &strTemp)
{
	char cTemp[30];
	int i;
	for(i=0;i<n;i++)
	{
		cTemp[i]=bb[i];
	}
	cTemp[i]='\0';
	strTemp=cTemp;
	
	return (float)atof(cTemp);
}


float Serial::Tof(BYTE *bb,BOOL bF)
{
	float f;
	unsigned char *pa;
	pa=(unsigned char*)&f;
	if(!bF)
	{
		*(pa+0)=bb[3];
		*(pa+1)=bb[2];
		*(pa+2)=bb[1];
		*(pa+3)=bb[0];
	}
	else
	{
		*(pa+0)=bb[0];
		*(pa+1)=bb[1];
		*(pa+2)=bb[2];
		*(pa+3)=bb[3];
	}
	
	return f;
}


void Serial::StrToByte(CString strTemp, BYTE bb[], int &iN)
{
	//12.3   ->31 32 2e 33
	iN=strTemp.GetLength();
	for(int i=0;i<iN;i++)
	{
		CString te;
		te=strTemp.Left(i+1);
		bb[i]=*te.Right(1);//@@@@@@@@@@
	}

}


BOOL Serial::DoReadData_0x7B7D(BYTE *pByte, int &iN)
{
	if (NULL == pByte || iN < 1)
	{
		return FALSE;
	}

	// the last byte of data can not be 0x7B or 0x7D
	if (0x7B == pByte[iN - 1] || 0x7D == pByte[iN - 1])
	{
		return FALSE;
	}

	BYTE *pNewByte = new BYTE [iN];
	int iNewByteNum = 0;

	for(int i = 0; i < iN; i++)		// 处理数据，将有效数据保存在pNewByte中
	{
		pNewByte[iNewByteNum++] = pByte[i];
		if(pByte[i] == 0x7B || pByte[i] == 0x7D)
		{
			i++;
		}
	}
	
	// copy data
	iN = iNewByteNum;
	for(int i = 0; i < iN; i++)
	{
		pByte[i] = pNewByte[i];
	}

	delete [] pNewByte;

	return TRUE;
}


BOOL Serial::DoWriteData_0x7B7D(BYTE * pOut, int nBytes, int iSize, int & iNewBytes)
{
	if (NULL == pOut || nBytes >= iSize)
	{
		return FALSE;
	}

	
	BYTE * pTemp = new BYTE[iSize];
	if (NULL == pTemp)
	{
		return FALSE;
	}

	int iTempIndex = 0;
	for (int i = 0; i < nBytes; i++)
	{
		pTemp[iTempIndex++] = pOut[i]; 
		if (pOut[i] == 0x7B || pOut[i] == 0x7D)
		{
			pTemp[iTempIndex++] = 0x80;
		}

		if (iTempIndex >= iSize)
		{
			delete [] pTemp;
			return FALSE;
		}
	}

	iNewBytes = iTempIndex;
	for (int i = 0; i < iNewBytes; i++)
	{
		pOut[i] = pTemp[i];
	}

	delete [] pTemp;
	return TRUE;
}


BOOL Serial::SendPackage(HANDLE &ComHandle,BYTE ucCommand, BYTE * pData, int nByte)
{
	if (NULL == pData)
	{
		return FALSE;
	}

	BYTE ucSend[2048];
	int iSendIndex = 0;
	BYTE ucLRC = 0;

	// 1. Package head
	ucSend[iSendIndex++] = 0x7B;
	ucSend[iSendIndex++] = 0x7B;

	// 2. Destination address
	ucSend[iSendIndex++] = m_ucDeviceAddress;
	
	// 3. Source address
	ucSend[iSendIndex++] = m_ucPCAddress;
	
	// 4. Command
	ucSend[iSendIndex++] = ucCommand;

	// 5. Data length in byte
	ucSend[iSendIndex++] = nByte / 256;
	ucSend[iSendIndex++] = nByte % 256;

	// 6. nByte data & calculate LRC
	for (int i = 2; i < iSendIndex; i++)
	{
		ucLRC += ucSend[i];
	}
	for (int i = 0; i < nByte; i++)
	{
		ucSend[iSendIndex++] = pData[i];
		ucLRC += pData[i];
	}

	int nNewByte = 0;
	iSendIndex -= nByte;
	BOOL bR = DoWriteData_0x7B7D(&ucSend[iSendIndex], nByte, 2048 - iSendIndex, nNewByte);
	if (!bR)
	{
		return FALSE;
	}
	iSendIndex += nNewByte;

	// 7. LRC
	ucSend[iSendIndex++] = ucLRC;

	// 8. Package tail
	ucSend[iSendIndex++] = 0x7D;
	ucSend[iSendIndex++] = 0x7D;

	bR = Output(ComHandle,ucSend, iSendIndex);

	return bR;
}


int Serial::ReceivePackage(HANDLE &ComHandle,BYTE ucCommand, BYTE * pData, int nSize, int & nReceived)
{
	BYTE ucReceive[2048];
	BOOL bR = FALSE;
	int  iReceiveIndex = 0;
	int  iThrow = 0;
	BOOL bThrow = FALSE;

	while(TRUE)
	{
		// Make sure not to exceed buffer
		if (iReceiveIndex >= 2048)
		{
			return -1;
		}

		bR = Input(ComHandle,&ucReceive[iReceiveIndex], 1);
		if (!bR)
		{
			// Haven't receive the tail of the package
			return -2;
		}
		
		// The index of data in a package is start at 7
		if (iReceiveIndex >= 6)
		{
			// Check the tail of the package
			// If received the real tail of a package, bThrow is obviously FALSE
			if (0x7D == ucReceive[iReceiveIndex - 1] && 0x7D == ucReceive[iReceiveIndex] && !bThrow)
			{
				iReceiveIndex++;
				break;
			}

			// Remove useless 0x80 : [0x7B|0x7D]0x80
			if ( 0x80 == ucReceive[iReceiveIndex] && (0x7B == ucReceive[iReceiveIndex - 1] || 0x7D == ucReceive[iReceiveIndex - 1]) )
			{
				iThrow++;
				iReceiveIndex--;
				bThrow = TRUE;
			}
			else
			{
				bThrow = FALSE;
			}
		}

		iReceiveIndex++;
	}

	if (iReceiveIndex < 10) // The minimize size of a intact package is 10 bytes 
	{
		return -3;
	}

	// Validate the head and the tail of the package
	if (ucReceive[0] != 0x7B || ucReceive[1] != 0x7B || 
		ucReceive[iReceiveIndex - 1] != 0x7D || ucReceive[iReceiveIndex - 2] != 0x7D)
	{
		return -4;
	}

	// Validate the command
	if (ucCommand != ucReceive[4])
	{
		return -5;
	}

	// The buffer is to small
	if (iReceiveIndex > nSize)
	{
		return -6;
	}

	// Validate the the length of data received
	nReceived = ucReceive[5] * 256 + ucReceive[6];
	if (nReceived + 10 != iReceiveIndex)
	{
		return -7;
	}

	for (int i = 0; i < iReceiveIndex; i++)
	{
		// Data of the package starts at the eighth byte
		pData[i] = ucReceive[7 + i];
	}

	return iThrow;
}