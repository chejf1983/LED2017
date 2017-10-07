// BWTEK_RS.cpp: implementation of the CBWTEK_RS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "BWTEK_RS.h"
#include "Global_MySpec.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBWTEK_RS::CBWTEK_RS()
{
	m_iBaudRate=115200;
	m_iIntTime=0;
	m_iAveN=0;
}

CBWTEK_RS::~CBWTEK_RS()
{

}

BOOL CBWTEK_RS::Init(CString strCom, int iBaudrate)
{
	if(g_bDemo)
	{
		return TRUE;
	}
	BOOL bR;
	if(1)
	{
		int B[3];
		B[0]=9600;
		B[1]=38400;
		B[2]=115200;
		for(int i=0;i<3;i++)
		{
			bR=BWSer.Open(m_CommDev,strCom,B[i]);
			if(bR)
			{
				bR=SetRaudRate(iBaudrate);
				BWSer.Close(m_CommDev);
				if(bR)
					break;
			}
		}
	}

	bR=BWSer.Open(m_CommDev,strCom,iBaudrate);
	if(!bR)
		return FALSE;

	BWSer.SetDCBParity(m_CommDev,NOPARITY);

	bR=SetDataMode(0);
	if(!bR)
		return FALSE;

	return TRUE;	
}

BOOL CBWTEK_RS::UnInit()
{
	if(g_bDemo)
		return TRUE;
	BWSer.Close(m_CommDev);
	return TRUE;
}

BOOL CBWTEK_RS::SetIntTime(int iIntTime)
{
	if(g_bDemo)
		return TRUE;
	if(m_iIntTime==iIntTime)
		return TRUE;
	BYTE Out[10];
	//Chr(73) + Str(inttime) + Chr(10) + Chr(13)
	Out[0]= 73;

	CString strTemp;
	strTemp.Format("%d",iIntTime);
	int iN;
	BYTE bb[10];
	BWSer.StrToByte(strTemp,bb,iN);
	for(int i=0;i<iN;i++)
		Out[1+i]=bb[i];

	Out[1+iN+0] = 10;
	Out[1+iN+1] = 13;
	BWSer.Output(m_CommDev,Out,1+iN+2);
	BYTE In[10];
	BWSer.SetReadTime(m_CommDev,1000,2,1000);
	BOOL bR=BWSer.Input(m_CommDev,In,10);
	if(!bR)
		return FALSE;
	m_iIntTime=iIntTime;
	return TRUE;
}

BOOL CBWTEK_RS::SetDataMode(int iMode)
{
	if(g_bDemo)
		return TRUE;
	BYTE Out[10];
	if(iMode==0)
		Out[0]=98;
	else
		Out[0]=97;
	Out[1] = 10;
	Out[2] = 13;

	BWSer.Output(m_CommDev,Out,1+2);
	BYTE In[10];
	BWSer.SetReadTime(m_CommDev,1000,2,1000);
	BOOL bR=BWSer.Input(m_CommDev,In,10);
	if(!bR)
		return FALSE;
	return TRUE;
}

BOOL CBWTEK_RS::SetRaudRate(int iRaudRate)
{
	if(g_bDemo)
		return TRUE;
	BYTE Out[10];
	//Chr(73) + Str(inttime) + Chr(10) + Chr(13)
	Out[0]= 75;

	int B=3;
	if(iRaudRate==115200)
		B=0;
	if(iRaudRate==38400)
		B=1;
	if(iRaudRate==19200)
		B=2;
	if(iRaudRate==9600)
		B=3;

	CString strTemp;
	strTemp.Format("%d",B);
	int iN;
	BYTE bb[10];
	BWSer.StrToByte(strTemp,bb,iN);
	for(int i=0;i<iN;i++)
		Out[1+i]=bb[i];

	Out[1+iN+0] = 10;
	Out[1+iN+1] = 13;
	BWSer.Output(m_CommDev,Out,1+iN+2);
	BWSer.Output(m_CommDev,Out,1+iN+2);
	BYTE In[14];
	BWSer.SetReadTime(m_CommDev,1000,2,1000);
	BOOL bR=BWSer.Input(m_CommDev,In,14);
	if(!bR)
		return FALSE;
	m_iBaudRate=iRaudRate;
	return TRUE;
}

BOOL CBWTEK_RS::Scan(int iIntTime,int iAveN,float fAD[])
{
	//Chr(83) + Chr(10) + Chr(13)
	if(g_bDemo)
		return TRUE;
	if(SetIntTime(iIntTime)==FALSE)
		return FALSE;
	if(SetAveNum(iAveN)==FALSE)
		return FALSE;
	BYTE Out[10];
	Out[0] = 83;
	Out[1] = 10;
	Out[2] = 13;
	BWSer.Output(m_CommDev,Out,1+2);
	BYTE In[10];
	BWSer.SetReadTime(m_CommDev,1000,2,1000);
	BOOL bR=BWSer.Input(m_CommDev,In,8);
	if(!bR||In[0]!=Out[0])
		return FALSE;
	BWSer.SetReadTime(m_CommDev,(iIntTime+100)*iAveN+1000,2,(iIntTime+100)*iAveN+1000);
	int iN=0;
	float data_old=0;
	int rec_wz=0;
	while(1)
	{
		bR=BWSer.Input(m_CommDev,In,1);
		if(!bR)
			return FALSE;
		if(In[0]==128)
		{
			data_old=0;
			bR=BWSer.Input(m_CommDev,In,2);
			if(!bR)
				return FALSE;
			fAD[iN]=(float)(In[0]*256+In[1]);
			data_old=fAD[iN];
			iN++;
		}
		else
		{
			if(In[0]<128)
				fAD[iN]=data_old+In[0];
			else
				fAD[iN]=data_old-(256-In[0]);
			data_old=fAD[iN];
			iN++;
		}
		if(iN==2048)
			break;
	}
	BWSer.Input(m_CommDev,In,2);
	return TRUE;
}

BOOL CBWTEK_RS::SetAveNum(int iAveN)
{
	if(g_bDemo)
		return TRUE;
	if(m_iAveN==iAveN)
		return TRUE;
	BYTE Out[10];
	//Chr(65) + Str(inttime) + Chr(10) + Chr(13)
	Out[0]= 65;

	CString strTemp;
	strTemp.Format("%d",iAveN);
	int iN;
	BYTE bb[10];
	BWSer.StrToByte(strTemp,bb,iN);
	for(int i=0;i<iN;i++)
		Out[1+i]=bb[i];

	Out[1+iN+0] = 10;
	Out[1+iN+1] = 13;
	BWSer.Output(m_CommDev,Out,1+iN+2);
	BWSer.Output(m_CommDev,Out,1+iN+2);
	BYTE In[14];
	BWSer.SetReadTime(m_CommDev,1000,2,1000);
	BOOL bR=BWSer.Input(m_CommDev,In,11);
	if(!bR)
		return FALSE;
	m_iAveN=iAveN;
	return TRUE;
}

BOOL CBWTEK_RS::Scan_N(int iIntTime, int iAveN, float fAD[])
{
	int iErr=0;
	BOOL bR;
Retry:
	bR=Scan(iIntTime,iAveN,fAD);
	if(!bR)
	{
		iErr++;
		if(iErr<3)
			goto Retry;
		return FALSE;
	}
	return TRUE;
}
