// BWSerial.cpp: implementation of the BWSerial class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BWSerial.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BWSerial::BWSerial()
{

}

BWSerial::~BWSerial()
{

}

BOOL BWSerial::Open(HANDLE &CommDev,CString sCom, int iBaudRate)
{
	DCB dcb;
	CommDev=CreateFile(sCom,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
	
	if(CommDev==INVALID_HANDLE_VALUE) 
		return FALSE;
	if(GetCommState(CommDev,&dcb)==FALSE)
	    return FALSE;

 	dcb.BaudRate=iBaudRate;
	dcb.Parity=NOPARITY;
	dcb.ByteSize=8;
	dcb.StopBits=ONESTOPBIT;
	
	if(SetCommState(CommDev,&dcb)==FALSE) 
	    return FALSE;
    
	return TRUE;
}

BOOL BWSerial::Close(HANDLE &CommDev)
{
	return CloseHandle(CommDev);
}

BOOL BWSerial::SetReadTime(HANDLE &CommDev, int iReadIntervalTimeOut, int iReadTotalTimeoutMultiplier, int iReadTotalTimeoutConstant)
{
	COMMTIMEOUTS tout;
	if(GetCommTimeouts(CommDev,&tout)==FALSE)
		return FALSE;
	tout.ReadIntervalTimeout=iReadIntervalTimeOut;     
	tout.ReadTotalTimeoutMultiplier=iReadTotalTimeoutMultiplier; 
    tout.ReadTotalTimeoutConstant=iReadTotalTimeoutConstant; 
    //tout.WriteTotalTimeoutMultiplier; 
    //tout.WriteTotalTimeoutConstant; 
	if(SetCommTimeouts(CommDev,&tout)==FALSE)
		return FALSE;
	return TRUE;
}

BOOL BWSerial::Output(HANDLE &CommDev, BYTE *OutData, DWORD OutN)
{
	Clear(CommDev);
	DWORD N;	
	BOOL bR;
	for(int i=0;i<(int)OutN;i++)
	{
		BYTE Out[1];
		Out[0]=OutData[i];
		bR=WriteFile(CommDev,Out,1,&N,NULL);
		if(!bR||N<1)
			return FALSE;
	}
	return TRUE;
}

BOOL BWSerial::Input(HANDLE &CommDev, BYTE *InData, DWORD InN)
{
	DWORD N;
	BOOL bR;
	for(int i=0;i<(int)InN;i++)
	{
		BYTE In[1];		
		bR=ReadFile(CommDev,In,1,&N,NULL);
		if(!bR||N<1)
		{
			return FALSE;
		}
		else
		{
			InData[i]=In[0];
		}
	}
	return TRUE;
}

void BWSerial::WordToByte(WORD Word, BYTE &hByte, BYTE &lByte)
{
	lByte=BYTE(Word);
	Word=Word>>8;
	hByte=BYTE(Word);
}

float BWSerial::btof196(BYTE *bb)
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

float BWSerial::btof(BYTE *bb)
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
	if(bb[0]==0) zho.str[3]=bb[0];
	else  zho.str[3]=(bb[0]-1);
	zhog=zho.str[3];
	zho.str[2]=bb[3]&0x7f;
	zho.str[1]=bb[2];
	zho.str[0]=bb[1];
	/*zhon=&str[0];*/ /*printf("%ld\n",*zhon);*/
	zho.zhon=zho.zhon<<1;/*printf("%ld\n",zho.zhon);*/
	zho.str[3]=zhog;
	zho.zhon=zho.zhon>>1;
	zho.str[3]|=sig;
	/*flt=&str[0];*/
	return(zho.flt);
}

BOOL BWSerial::SetAd(HANDLE &CommDev, CString sAd)
{
	BOOL bR;
	SetReadTime(CommDev,2500,2,2500);
	BYTE Out[1],In[1];
	Out[0]=BYTE((int)atof(sAd));
	SetDCBParity(CommDev,MARKPARITY);
	Output(CommDev,Out,1);
	bR=Input(CommDev,In,1);
	SetDCBParity(CommDev,SPACEPARITY);
	if(!bR||(In[0]!=BYTE(~Out[0])))
		return FALSE;
	else
	{
		Sleep(10);
		return TRUE;
	}
}

BOOL BWSerial::SetDCBParity(HANDLE &CommDev, BYTE Parity)
{
	DCB dcb;
	if(GetCommState(CommDev,&dcb)==FALSE)
	    return FALSE;
	dcb.Parity=Parity;//NOPARITY         
	                  //ODDPARITY
                      //EVENPARITY
                      //MARKPARITY
                      //SPACEPARITY 
	if(SetCommState(CommDev,&dcb)==FALSE) 
	    return FALSE;
	return TRUE;
}

CString BWSerial::sStringTo(BYTE *bb, int number)
{
	CString n,m;
	for(int i=0;i<number;i++)
	{
	  n.Format("%c",bb[i]);// ascii of hex->cstring of char
      m.Insert(i,n);
	}
	return m;
}

float BWSerial::ASCIItof(unsigned char *bb, int n, CString &strTemp)
{
    char cTemp[30];
	for(int i=0;i<n;i++)
		cTemp[i]=bb[i];
	cTemp[i]='\0';
	strTemp=cTemp;
	return (float)atof(cTemp);
}

void BWSerial::StrToByte(CString strTemp, BYTE bb[], int &iN)
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

BOOL BWSerial::Clear(HANDLE &CommDev)
{
	PurgeComm(CommDev,PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
	return TRUE;
}
