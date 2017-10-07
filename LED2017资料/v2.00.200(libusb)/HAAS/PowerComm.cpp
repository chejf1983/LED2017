// PowerComm.cpp: implementation of the CPowerComm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PowerComm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern BOOL g_bEnglish;

extern int	 g_iSetType2;
extern float g_fSetVol2;
extern float g_fSetCurr2;

CPowerComm::Comm_Type  CPowerComm::m_typeComm = CPowerComm::Comm_Type_RS;
int     CPowerComm::m_iCan2RS_Addr = 1;
//CCT_DebugerComm::TypeRS CPowerComm::m_typeRS = CCT_DebugerComm::TypeRS_8;
int CPowerComm::m_iCan2RS_TimeOut = 1000;

//extern CCT_DebugerComm g_CT_DebugerComm;

 BOOL g_bAdOrder;

int CPowerComm::m_iCurrStep = 0;

extern BOOL g_bDemo;

CPowerComm::CPowerComm()
{

}

CPowerComm::~CPowerComm()
{

}

CString  CPowerComm::PDC_GetVer()
{
	CString strVer;
	CString strTemp;
	
	strTemp = "Ver(USBCAN) 1.00 2008.10";
	strVer = strVer + strTemp+"\r\n";

	return strVer;
}

//
// Mode     = 9 Bists Mode
// Addr.    = 0x09
// Baudrate = 9600
//
BOOL CPowerComm::GetPower_PF4000(CString sPowerCom,float &fU, float &fI, float &fP, float &fPF)
{
/*	PF4000_DATA_TEST pf4te;
	int iCom=atoi(sPowerCom.Mid(3,1));

	BOOL bR;
	bR=ths_INS_PF4000_Test(iCom,0x09,9600,1,PF4000_DATA,pf4te,TRUE,NULL,FALSE);
	if(!bR)
		return FALSE;
	if(pf4te.iDataType==DATA_AA)
	{
		fU=pf4te.fUrms;
		fI=pf4te.fIrms;
		fP=pf4te.fP;
		fPF=pf4te.fLambda;
	}
	if(pf4te.iDataType==DATA_BB)
	{
		fU=pf4te.fU_t;
		fI=pf4te.fI_t;
		fP=pf4te.fP_t;
		fPF=pf4te.fLambda_t;
	}
	return bR;
	*/
	return TRUE;
}

void CPowerComm::PDC_GetPowerList(int &iN,CString sPowerTypeList[])
{
	iN=0;

	sPowerTypeList[iN]="PF110";
	iN++;

	sPowerTypeList[iN]="PF2010/S";
	iN++;

	sPowerTypeList[iN]="PF9805/02";
	iN++;
	
	sPowerTypeList[iN]="PF9805(NEW)";
	iN++;

	sPowerTypeList[iN]="PF9805(9BITS)"; //9bits huyubing
	iN++;

	sPowerTypeList[iN]="PF9810A";
	iN++;

	sPowerTypeList[iN]="PF9811/10";
	iN++;

	sPowerTypeList[iN]="PF9830/30A";
	iN++;

	sPowerTypeList[iN]="PF9832";
	iN++;

	sPowerTypeList[iN]="WY Series";
	iN++;

	sPowerTypeList[iN]="WY(9BITS)";
	iN++;

	sPowerTypeList[iN]="WY5010";
	iN++;

	sPowerTypeList[iN]="TPS-500B";
	iN++;

	sPowerTypeList[iN]="PF9822";
	iN++;

	sPowerTypeList[iN]="TYPE 8 BITS";
	iN++;

	sPowerTypeList[iN]="TYPE 9 BITS";
	iN++;

	sPowerTypeList[iN]="YF2401";
	iN++;

	sPowerTypeList[iN]="PF4000";
	iN++;

	sPowerTypeList[iN]="WT210";
	iN++;

	return;
}

BOOL CPowerComm::GetPower_TYPE8(CString sPowerCom,float &fU, float &fI, float &fP, float &fPF)
{
	HANDLE CommDev=NULL;
	BOOL bR;
	DWORD iRead=0;
	const DWORD iOutN=1;
	const DWORD iInN =21;
	BYTE Out[iOutN];
	BYTE In[iInN];
	Out[0]=0xEE;
	const BYTE RetByte=~Out[0];

	bR=Open(CommDev,sPowerCom,2400);
	if(!bR)
		return FALSE;
	bR=SetReadTime(CommDev,3000,1,3000);
	if(!bR)
	{
		Close(CommDev);
		return FALSE;
	}
	bR=Output(CommDev,Out,iOutN);
	if(!bR)
	{
		Close(CommDev);
		return FALSE;
	}
	bR=Input(CommDev,In,iInN);
	Close(CommDev);
	if(!bR)
		return FALSE;
	if(In[0]!=RetByte)
		return FALSE;
	BYTE bb[4];
	int i;

	for(i=0;i<4;i++)
		bb[i]=In[16+i+1];
	fP=(float)fabs(btof196(bb));

	for(i=0;i<4;i++)
		bb[i]=In[4*0+i+1];
	fU=(float)fabs(btof196(bb));

	for(i=0;i<4;i++)
		bb[i]=In[4*1+i+1];
	fI=(float)fabs(btof196(bb));

	for(i=0;i<4;i++)
		bb[i]=In[4*2+i+1];
	fPF=(float)fabs(btof196(bb));
	
	return TRUE;
}

BOOL CPowerComm::GetPower_TYPE9(CString sPowerCom,CString sPowerAd,float &fU, float &fI, float &fP, float &fPF)
{
	BYTE Out[1];
	BYTE In[21];
	HANDLE CommDev;
	BOOL bR;
	bR=Open(CommDev,sPowerCom,2400);
	if(!bR)
		return FALSE;
	bR=SetAd(CommDev,sPowerAd);
	if(!bR)
	{
		Close(CommDev);
		return FALSE;
	}
	SetReadTime(CommDev,5000,2,5000);

	Out[0]=0xEE;
	Output(CommDev,Out,1);
	bR=Input(CommDev,In,21);
	Close(CommDev);
	if(!bR)
		return FALSE;
	if(In[0]!=BYTE(~Out[0]))                //!!!!!!!
		return FALSE;
	BYTE bb[4];
	int i;
	for(i=0;i<4;i++)
		bb[i]=In[i+1];
	fU=btof196(bb);
	
	for(i=0;i<4;i++)
		bb[i]=In[i+4*1+1];
	fI=btof196(bb);

	for(i=0;i<4;i++)
		bb[i]=In[i+4*4+1];
	fP=btof196(bb);

	for(i=0;i<4;i++)
		bb[i]=In[i+4*2+1];
	fPF=btof196(bb);

	fU=(float)fabs(fU);
	fI=(float)fabs(fI);
	fP=(float)fabs(fP);
	fPF=(float)fabs(fPF);
	return TRUE;

}

float CPowerComm::ASCIItof2(unsigned char *bb, int n, CString &strTemp)
{
	char cTemp[30];
	for(int i=0;i<n;i++)
		cTemp[i]=bb[i];
	cTemp[i]='\0';
	strTemp=cTemp;
	return (float)atof(cTemp);
}

BOOL CPowerComm::GetPower_WY(CString strCom,float &fU, float &fI)
{
	HANDLE CommDev;
	BOOL bR;
	BYTE Out[1],In[40];      //
	bR=Open(CommDev,strCom,2400);
	if(!bR)
	{
		return FALSE;
	}
	SetReadTime(CommDev,5000,2,5000);
	Out[0]='G';
	Output(CommDev,Out,1);
	bR=Input(CommDev,In,1);
	if(!bR)
	{
		Close(CommDev);
		return FALSE;
	}
	if(In[0]!=BYTE(~Out[0]))
	{
		Close(CommDev);
		return FALSE;
	}
	bR=Input(CommDev,In,14);
	if(!bR)
	{
		Close(CommDev);
		return FALSE;
	}
	CString strVol,strCurr;

	int i;
	BYTE bb[10];
	
	for(i=0;i<6;i++)
		bb[i]=In[i];
	fU=ASCIItof2(bb,6,strVol);

	for(i=0;i<6;i++)
		bb[i]=In[7+i];
	fI=ASCIItof2(bb,6,strCurr);

	Close(CommDev);
	return TRUE;
}

BOOL CPowerComm::GetPower_WY9BITS(CString strCom,float &fU, float &fI,CString strAddr)
{
	HANDLE CommDev;
	BOOL bR;
	BYTE Out[1],In[40];      //
	bR=Open(CommDev,strCom,2400);
	if(!bR)
	{
		return FALSE;
	}
	bR=SetAd(CommDev,strAddr);
	if(!bR)
	{
		Close(CommDev);
		return FALSE;
	}
	SetReadTime(CommDev,5000,2,5000);
	Out[0]='G';
	Output(CommDev,Out,1);
	bR=Input(CommDev,In,1);
	if(!bR)
	{
		Close(CommDev);
		return FALSE;
	}
	if(In[0]!=BYTE(~Out[0]))
	{
		Close(CommDev);
		return FALSE;
	}
	bR=Input(CommDev,In,14);
	if(!bR)
	{
		Close(CommDev);
		return FALSE;
	}
	CString strVol,strCurr;

	int i;
	BYTE bb[10];
	
	for(i=0;i<6;i++)
		bb[i]=In[i];
	fU=ASCIItof2(bb,6,strVol);

	for(i=0;i<6;i++)
		bb[i]=In[7+i];
	fI=ASCIItof2(bb,6,strCurr);

	Close(CommDev);
	return TRUE;
}

BOOL CPowerComm::GetPower_PF9805_9BITS(CString sPowerCom,float &fU, float &fI, float &fP, float &fPF)
{
	BYTE In[21];
	HANDLE CommDev;
	BOOL bR;
	bR=Open(CommDev,sPowerCom,2400);
	if(!bR)
		return FALSE;
	bR=SetAd(CommDev,"05");
	if(!bR)
	{
		Close(CommDev);
		return FALSE;
	}
	SetReadTime(CommDev,5000,2,5000);

	bR=Input(CommDev,In,5*7+1);
	Close(CommDev);
	if(!bR)
		return FALSE;
	
	BYTE bb[10];

	int i;
	for(i=0;i<6;i++)
        bb[i]=In[i+7*0+0];
	fU=ASCIItof(bb,6);

	for(i=0;i<6;i++)
        bb[i]=In[i+7*1+0];
	fI=ASCIItof(bb,6);

	for(i=0;i<6;i++)
        bb[i]=In[i+7*4+0];
	fP=ASCIItof(bb,6);

	for(i=0;i<6;i++)
        bb[i]=In[i+7*2+0];
	fPF=ASCIItof(bb,6);

	if(In[6+7*4+0]=='k')
		fP=fP*1000;

	return TRUE;
}

int CPowerComm::PDC_GetPower(CString sCom,CString sType,int &iPowerType,float &fU1,float &fI1,float &fP1,float &fPf1,float &fU2,float &fI2,float &fP2,float &fPf2,CProgressCtrl &m_cProgress,BOOL bPro)
{
	if(sType=="PF4000")
	{
		iPowerType=1;
		BOOL bR;
		bR=GetPower_PF4000(sCom,fU1,fI1,fP1,fPf1);
		if(bR)
			return PD_COMM_OK;
		else
			return PD_COMM_FAIL;
	}
	else if(sType=="WY Series")
	{
		iPowerType=1;
		BOOL bR;
		bR=GetPower_WY(sCom,fU1,fI1);
		if(bR)
		{
			fP1=fU1*fI1;
			fPf1=1.0f;
			return PD_COMM_OK;
		}
		else
			return PD_COMM_FAIL;
	}
	else if(sType=="WY(9BITS)"||sType=="WY5010")
	{
		// 使用万能地址码100 ,0x64
		iPowerType=1;
		BOOL bR;
		bR=GetPower_WY9BITS("11",fU1,fI1,"100");
		if(bR)
		{
			fP1=fU1*fI1;
			fPf1=1.0f;
			return PD_COMM_OK;
		}
		else
			return PD_COMM_FAIL;
	}
	else if(sType=="TYPE 8 BITS")
	{
		iPowerType=1;
		BOOL bR;
		bR=GetPower_TYPE8(sCom,fU1,fI1,fP1,fPf1);
		if(bR)
			return PD_COMM_OK;
		else
			return PD_COMM_FAIL;
	}
	else if(sType=="TYPE 9 BITS"||sType=="PF9811/10")
	{
		iPowerType=1;
		BOOL bR;
		bR=GetPower_TYPE9(sCom,"09",fU1,fI1,fP1,fPf1);
		if(bR)
			return PD_COMM_OK;
		else
			return PD_COMM_FAIL;
	}
	else if(sType=="TPS-500B")
	{
		iPowerType=1;
		BOOL bR;
		float fFreq;
		//CAN通讯
		bR=TPS500B_Read("19",68,fU1,fFreq,fI1,fP1,fPf1);
		if(bR)
		{
			return PD_COMM_OK;
		}
		else
			return PD_COMM_FAIL;
	}
	else if(sType=="YF2401")
	{
		iPowerType=1;
		BOOL bR;
		float fUs;
		float fFreq;
		float fUIK;
		bR=YF2401_FlashData(sCom,fUs,fU1,fI1,fP1,fFreq,fPf1,fUIK);
		fI1=fI1/1000.0f;
		if(bR)
			return PD_COMM_OK;
		else
			return PD_COMM_FAIL;
	}
	else if(sType=="PF9805(9BITS)")
	{
		iPowerType=1;
		BOOL bR;
		bR=GetPower_PF9805_9BITS(sCom,fU1,fI1,fP1,fPf1);
		if(bR)
			return PD_COMM_OK;
		else
			return PD_COMM_FAIL;
	}
	else if(sType=="WT210")
	{
		iPowerType=1;
		BOOL bR;
		bR=GetPower_WT210(sCom,fU1,fI1,fP1,fPf1);
		if(bR)
			return PD_COMM_OK;
		else
			return PD_COMM_FAIL;
	}

    HANDLE CommDev=NULL;
    BOOL   bR;
    DWORD  iOut=1;
     DWORD  iIn;
    BYTE   RetByte;
    BYTE   Out[1];
    BYTE   In[3000];

	iPowerType=1;
    if(sType=="PF9811/10")
    {
        iIn     =4*(263)+102*4;
        Out[0]  =0x11;
        RetByte =~0x11;
    }
    else if(sType=="PF2010/S")
    {
        iIn     =4*(263);
        Out[0] =0xCA;
        RetByte =~0xCA;
    }
    else if(sType=="PF9805/02")
    {
        iIn     =4*(263);
        Out[0] =0x05;
        RetByte =~0x05;
    }
    else if(sType=="PF110")
    {
        iIn     =16;
        Out[0] =0x6E;
        RetByte =~0x6E;
    }
    else if(sType=="PF9830/30A")
    {
        iIn     =29*4;
        Out[0]  =0x1E;
        RetByte =~0x1E;
		
		iPowerType=2;
    }
    else if(sType=="PF9832")
    {
        iIn     =14*4;
        Out[0]  =0x20;
        RetByte =~0x20;
		
		iPowerType=2;
    }
/*    else if(sType=="WY5010")
    {
        iIn     =14;
        Out[0]  =0x78;
        RetByte =~0x78;		
    }
*/	else if(sType=="PF9810A")
	{
		iIn     =1+4*8+2*51*4+512*2;
        Out[0]  =0x1A;
        RetByte =~0x1A;
	}
	else if(sType=="PF9805(NEW)")
	{
		iIn     =1+5*7;
        Out[0]  =0x05;
        RetByte =~0x05;
	}
	else if(sType=="PF9822")
	{
		iIn     =1+45;
        Out[0]  =0x16;
        RetByte =~0x16;
	}
    else
		return PD_COMM_FAIL;
	if(bPro)
			m_cProgress.SetRange32(0,iIn);

	bR=Open(CommDev,sCom,2400);
    if(!bR)
		return PD_COMM_FAIL;

    SetReadTime(CommDev,5000,2,5000);
    bR=Output(CommDev,Out,1);
    if(!bR)
    {
        Close(CommDev);
		return PD_COMM_FAIL;
    }
    bR=Input(CommDev,In,1);
    if(!bR||In[0]!=RetByte)
    {
        Close(CommDev);
		return PD_COMM_FAIL;
    }
    SetReadTime(CommDev,500,2,500);
    for(int i=0;i<(int)iIn;i++)
    {
        BYTE M[1];
        bR=Input(CommDev,M,1);
        if(!bR)
        {
         	Close(CommDev);
			return PD_COMM_FAIL;
        }
        In[i]=M[0];
		if(bPro)
			m_cProgress.SetPos(i);
    }
    Close(CommDev);
    
    BYTE bb[10];
 
    if(sType=="PF9811/10"||sType=="PF2010/S"||sType=="PF9805/02")
    {
        for(i=0;i<4;i++)
         	bb[i]=In[i];
        fU1=btof196(bb);
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*1];
        fI1=btof196(bb);
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*2];
        fPf1=btof196(bb);
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*4];
        fP1=btof196(bb);
 
        fU2=0.0f;
        fI2=0.0f;
        fP2=0.0f;
        fPf2=0.0f;
    }
    else if(sType=="PF110")
    {
        for(i=0;i<4;i++)
         	bb[i]=In[i];
        fU1=btof196(bb);
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*1];
        fI1=btof196(bb);
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*2];
        fP1=btof196(bb);
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*3];
        fPf1=btof196(bb);
 
        fU2=0.0f;
        fI2=0.0f;
        fP2=0.0f;
        fPf2=0.0f;
    }
    else if(sType=="PF9830/30A")
    {
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*3+1];
        fU1=btof196(bb);
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*7+1];
        fI1=btof196(bb);
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*11+1];
        fP1=btof196(bb);
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*15+1];
        fPf1=btof196(bb);
 
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*1+1];
        fU2=btof196(bb);
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*5+1];
        fI2=btof196(bb);
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*9+1];
        fP2=btof196(bb);
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*13+1];
        fPf2=btof196(bb);
    }
    else if(sType=="PF9832")
    {
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*0];
        fU1=btof196(bb);
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*2];
        fI1=btof196(bb);
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*4];
        fP1=btof196(bb);
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*6];
        fPf1=btof196(bb);
 
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*1];
        fU2=btof196(bb);
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*3];
        fI2=btof196(bb);
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*5];
        fP2=btof196(bb);
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*7];
        fPf2=btof196(bb);
    }
	else if(sType=="WY5010")
	{
		CString sTemp;
		for(i=0;i<6;i++)
			bb[i]=In[i];
		sTemp=sStringTo(bb,6);
		fU1=(float)atof(sTemp);
		if(fU1<0)
			fU1=0;

		for(i=0;i<6;i++)
			bb[i]=In[7+i];
		sTemp=sStringTo(bb,6);
		fI1=(float)atof(sTemp);
		if(fI1<0)
			fI1=0;
		fP1=fU1*fI1;

		fPf1=1;
        fU2=0.0f;
        fI2=0.0f;
        fP2=0.0f;
        fPf2=0.0f;
	}
	else if(sType=="PF9810A")
	{
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*0+1];
        fU1=btof196(bb);
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*1+1];
        fI1=btof196(bb);
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*5+1];
        fP1=btof196(bb);
        for(i=0;i<4;i++)
         	bb[i]=In[i+4*3+1];
        fPf1=btof196(bb);

        fU2=0.0f;
        fI2=0.0f;
        fP2=0.0f;
        fPf2=0.0f;
	}
	else if(sType=="PF9805(NEW)")
	{
        for(i=0;i<6;i++)
         	bb[i]=In[i+7*0+0];
		fU1=ASCIItof(bb,6);

        for(i=0;i<6;i++)
         	bb[i]=In[i+7*1+0];
		fI1=ASCIItof(bb,6);

        for(i=0;i<6;i++)
         	bb[i]=In[i+7*4+0];
		fP1=ASCIItof(bb,6);

        for(i=0;i<6;i++)
         	bb[i]=In[i+7*2+0];
		fPf1=ASCIItof(bb,6);

		if(In[6+7*4+0]=='k')
			fP1=fP1*1000;

        fU2=0.0f;
        fI2=0.0f;
        fP2=0.0f;
        fPf2=0.0f;
	}
	else if(sType=="PF9822")
	{
        for(i=0;i<5;i++)
         	bb[i]=In[i+2];
		fU1=ASCIItof(bb,5);

        for(i=0;i<5;i++)
         	bb[i]=In[i+9+2];
		fI1=ASCIItof(bb,5)/1000.0f; //!!!!mA

        for(i=0;i<5;i++)
         	bb[i]=In[i+9+10+2];
		fP1=ASCIItof(bb,5);

        for(i=0;i<4;i++)
         	bb[i]=In[i+9+10+9+3];
		fPf1=ASCIItof(bb,4);

        fU2=0.0f;
        fI2=0.0f;
        fP2=0.0f;
        fPf2=0.0f;
	}
    else
		return PD_COMM_FAIL;

	if(bPro)
		m_cProgress.SetPos(0);
	return PD_COMM_OK;
}

BOOL CPowerComm::Open(HANDLE &CommDev,CString sCom, int iBaudRate)
{
	if(sCom.Left(3)=="COM")
		m_typeComm = Comm_Type_RS;
	else
		m_typeComm = Comm_Type_CAN2RS;

	if(m_typeComm==Comm_Type_RS)
	{
		DCB dcb;
		CommDev=CreateFile(sCom,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
		
		if(CommDev==INVALID_HANDLE_VALUE) 
			return FALSE;
		if(GetCommState(CommDev,&dcb)==FALSE)
			return FALSE;
		
		dcb.BaudRate = iBaudRate;
		dcb.Parity	 = NOPARITY;//
		dcb.ByteSize = 8;
		dcb.StopBits = ONESTOPBIT;
		dcb.fRtsControl=RTS_CONTROL_ENABLE;//RTS_CONTROL_DISABLE;
		if(SetCommState(CommDev,&dcb)==FALSE) 
			return FALSE;
		SetupComm(CommDev,4096*10,4096*10);
		return TRUE;
	}
/*
	if(m_typeComm==Comm_Type_CAN2RS)
	{
		m_iCan2RS_Addr = atoi(sCom);

		m_typeRS = CCT_DebugerComm::TypeRS_8;
		g_CT_DebugerComm.RS_ClearInput(m_iCan2RS_Addr);
		return TRUE;
	}
*/	return FALSE;
}

BOOL CPowerComm::Close(HANDLE &CommDev)
{
	if(m_typeComm==Comm_Type_RS)
		return CloseHandle(CommDev);
//	if(m_typeComm==Comm_Type_CAN2RS)
//		return TRUE;
	return FALSE;
}

BOOL CPowerComm::SetReadTime(HANDLE &CommDev, int iReadIntervalTimeOut, int iReadTotalTimeoutMultiplier, int iReadTotalTimeoutConstant)
{
	if(m_typeComm==Comm_Type_RS)
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
//	if(m_typeComm==Comm_Type_CAN2RS)
//	{
//		m_iCan2RS_TimeOut = iReadIntervalTimeOut;
//		return TRUE;
//	}
	return FALSE;
}

BOOL CPowerComm::Output(HANDLE &CommDev, BYTE *OutData, DWORD OutN)
{
	if(m_typeComm==Comm_Type_RS)
	{
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
//	if(m_typeComm==Comm_Type_CAN2RS)
//	{
//		return g_CT_DebugerComm.RS_Output(m_iCan2RS_Addr,OutData,OutN,m_typeRS);
//	}
	return FALSE;
}

BOOL CPowerComm::Input(HANDLE &CommDev, BYTE *InData, DWORD InN)
{
	DWORD N;
	BOOL bR;
	BYTE In[1];		
	if(m_typeComm==Comm_Type_RS)
	{
		for(int i=0;i<(int)InN;i++)
		{
			bR = ReadFile(CommDev,In,1,&N,NULL);
			if(!bR||N<1)
				return FALSE;
			else
				InData[i] = In[0];
		}
		return TRUE;
	}
/*	if(m_typeComm==Comm_Type_CAN2RS)
	{
		int iGetN;
		for(int i=0;i<(int)InN;i++)
		{
			bR = g_CT_DebugerComm.RS_Input(m_iCan2RS_Addr,In,1,iGetN,m_iCan2RS_TimeOut);
			if(!bR||iGetN<1)
				return FALSE;
			else
				InData[i] = In[0];
		}
		return TRUE;
	}
*/
	return FALSE;
}

void CPowerComm::WordToByte(WORD Word, BYTE &hByte, BYTE &lByte)
{
	lByte=BYTE(Word);
	Word=Word>>8;
	hByte=BYTE(Word);
}

float CPowerComm::btof196(BYTE *bb)
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

float CPowerComm::btof(BYTE *bb)
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

BOOL CPowerComm::SetDCBParity(HANDLE &CommDev,BYTE Parity)
{
	if(m_typeComm==Comm_Type_RS)
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
//	if(m_typeComm==Comm_Type_CAN2RS)
//	{
//		if(Parity==MARKPARITY)
//			m_typeRS = CCT_DebugerComm::TypeRS_9_Addr;
//		if(Parity==SPACEPARITY)
//			m_typeRS = CCT_DebugerComm::TypeRS_9_Data;
//		return TRUE;
//	}
	return FALSE;
}


BOOL CPowerComm::SetAd(HANDLE &CommDev, CString sAd)
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
//		Sleep(10);
		return TRUE;
	}
}

CString CPowerComm::sStringTo(BYTE *bb, int number)
{
	CString n,m;
	for(int i=0;i<number;i++)
	{
	  n.Format("%c",bb[i]);// ascii of hex->cstring of char
      m.Insert(i,n);
	}
	return m;
}

float CPowerComm::ASCIItof(unsigned char *bb, int n)
{
    char cTemp[30];
	for(int i=0;i<n;i++)
		cTemp[i]=bb[i];
	cTemp[i]='\0';
	return (float)atof(cTemp);
}

BOOL CPowerComm::YF2401_FlashData(CString sCom,float &fUs,float &fUl,float &fIl,float &fPow,float &fFreq,float &fPF,float &fUIK)
{
	//得到显示的数据

	HANDLE CommDev;
	BOOL bR;
	BYTE Out[1],In[100];      //
	bR=Open(CommDev,sCom,2400);
	if(!bR)
	{
		return FALSE;
	}
	SetReadTime(CommDev,5000,2,5000);
	Out[0]='G';
	Output(CommDev,Out,1);
	bR=Input(CommDev,In,1);
	if(!bR)
	{
		Close(CommDev);
		return FALSE;
	}
	if(In[0]!=BYTE(~Out[0]))
	{
		Close(CommDev);
		return FALSE;
	}
	bR=Input(CommDev,In,38);
	if(!bR)
	{
		Close(CommDev);
		return FALSE;
	}
	int i;
	BYTE bb[100];
	
	CString strTemp;

	int iCurN=0;

	for(i=0;i<7;i++)
	{
		bb[i]=In[iCurN];
		iCurN++;
	}
	fFreq=ASCIItof_2(bb,4,strTemp);

	for(i=0;i<4;i++)
	{
		bb[i]=In[iCurN];
		iCurN++;
	}
	fUs=ASCIItof_2(bb,3,strTemp);

	for(i=0;i<5;i++)
	{
		bb[i]=In[iCurN];
		iCurN++;
	}
	fUl=ASCIItof_2(bb,4,strTemp);

	for(i=0;i<7;i++)
	{
		bb[i]=In[iCurN];
		iCurN++;
	}
	fIl=ASCIItof_2(bb,5,strTemp);

	for(i=0;i<6;i++)
	{
		bb[i]=In[iCurN];
		iCurN++;
	}
	fPow=ASCIItof_2(bb,5,strTemp);

	for(i=0;i<4;i++)
	{
		bb[i]=In[iCurN];
		iCurN++;
	}
	fUIK=ASCIItof_2(bb,4,strTemp);

	for(i=0;i<5;i++)
	{
		bb[i]=In[iCurN];
		iCurN++;
	}
	fPF=ASCIItof_2(bb,5,strTemp);

	Close(CommDev);
	return TRUE;
}

float CPowerComm::ASCIItof_2(unsigned char *bb, int n, CString &strTemp)
{
    char cTemp[30];
	for(int i=0;i<n;i++)
		cTemp[i]=bb[i];
	cTemp[i]='\0';
	strTemp=cTemp;
	return (float)atof(cTemp);
}



BOOL CPowerComm::PH_GetCurData(CString strCom,CString strAddr, float &fMain, float &fRef)
{
	BYTE Out[1],In[9];
	HANDLE CommDev;
	BOOL bR;
	bR=Open(CommDev,strCom,2400);
	if(!bR)
		return FALSE;
	bR=SetAd(CommDev,strAddr);
	if(!bR)
	{
		Close(CommDev);
		return FALSE;
	}
	SetReadTime(CommDev,4000,2,4000);
	Out[0]=0x00;
	Output(CommDev,Out,1);
	bR = Input(CommDev,In,9);
	Close(CommDev);
	if(!bR)
		return FALSE;
	if(In[0]!=BYTE(~Out[0]))
		return FALSE;
	BYTE bb[4];
	int i;
	for(i=0;i<4;i++)
		bb[i]=In[i+1];
	fMain = btof196(bb);
	
	for(i=0;i<4;i++)
		bb[i]=In[i+4+1];
	fRef = btof196(bb);
		
	return TRUE;
}

// 新增，通讯横河WT210
BOOL CPowerComm::GetPower_WT210(CString sPowerCom,float &fU, float &fI, float &fP, float &fPF)
{
	BYTE In[200];
	BYTE Out[10];
	HANDLE CommDev;
	BOOL bR;
	bR=Open(CommDev,sPowerCom,9600);
	if(!bR)
		return FALSE;
	Out[0]='O';
	Out[1]='D';
	Out[2]=' ';
	Out[3]='\n';
	bR=Output(CommDev,Out,4);
	if(!bR)
	{
		Close(CommDev);
		return FALSE;
	}
	SetReadTime(CommDev,5000,2,5000);
	
	int iIn=0;
	while(1)
	{
		BYTE bb[1];
		bR=Input(CommDev,bb,1);
		In[iIn]=bb[0];
		if(iIn>3)
		{
			if(In[iIn-2]=='E'&&In[iIn-1]=='N'&&In[iIn]=='D')
				break;
		}
		iIn++;
		if(iIn>120)
			break;
	}
	Close(CommDev);
	if(!bR)
		return FALSE;
	
	BYTE bb[10];
	
	int i;
	int iB=0;
	while(1)
	{
		if(In[iB]=='V')
		{
			break;
		}
		else
			iB++;
	}
	for(i=0;i<10;i++)
        bb[i]=In[i+7+iB];
	fU=ASCIItof(bb,10);
	
	while(1)
	{
		if(In[iB]=='A')
		{
			break;
		}
		else
			iB++;
	}
	for(i=0;i<10;i++)
        bb[i]=In[i+iB+7];
	fI=ASCIItof(bb,10);
	
	while(1)
	{
		if(In[iB]=='W')
		{
			break;
		}
		else
			iB++;
	}
	for(i=0;i<10;i++)
        bb[i]=In[i+iB+7];
	fP=ASCIItof(bb,10);
	
	if(fU*fI!=0)
		fPF=fP/(fU*fI);
	else
		fPF=1;
	return TRUE;
}


BOOL CPowerComm::TPS_SetPower(CString sPowerComm, int iSetType, float fSetVol, float fSetCurr,BOOL bShowError)
{
	if(g_bDemo)
		return TRUE;

	HANDLE CommDev;
	CString strTemp;
	BOOL bR;
	BYTE Out[40],In[40];      //
	bR=Open(CommDev,sPowerComm,2400);
	if(!bR)
	{
		if(bShowError)
		{
			if(g_bEnglish)
				AfxMessageBox("TPS: Open Serial Port Fail!",MB_ICONSTOP);
			else
				AfxMessageBox("TPS电源控制: 打开串口失败!",MB_ICONSTOP);
		}
		return FALSE;
	}
	CString strAddr;
	strAddr.Format("%d",68);//TPS配CAN的地址码为0x19
	bR=SetAd(CommDev,strAddr);
	if(!bR)
	{
		if(bShowError)
		{
			if(g_bEnglish)
				AfxMessageBox("TPS: Comm Fail, Addr.!",MB_ICONSTOP);
			else
				AfxMessageBox("TPS电源控制: 通讯失败, 地址握手失败!",MB_ICONSTOP);
		}
		Close(CommDev);
		return FALSE;
	}
	SetReadTime(CommDev,5000,2,5000);
	int i,iTempN;
	BYTE bb[100];

	int iDataOutN =0;
	Out[iDataOutN]='S';
	iDataOutN++;

	Out[iDataOutN]=':';
	iDataOutN++;

	Out[iDataOutN]=0x30+iSetType;
	iDataOutN++;

	Out[iDataOutN]=':';
	iDataOutN++;

	strTemp.Format("%05.1f",fSetVol);
	StrToByte(strTemp,bb,iTempN);
	if(iTempN>=5)
		iTempN=5;
	for(i=0;i<iTempN;i++)
	{
		Out[iDataOutN]=bb[i];
		iDataOutN++;
	}

	Out[iDataOutN]=':';
	iDataOutN++;

	Out[iDataOutN]=0x30;
	iDataOutN++;

	Out[iDataOutN]=':';
	iDataOutN++;

	strTemp.Format("%05.2f",fSetCurr);
	StrToByte(strTemp,bb,iTempN);
	if(iTempN>=5)
		iTempN=5;
	for(i=0;i<iTempN;i++)
	{
		Out[iDataOutN]=bb[i];
		iDataOutN++;
	}
	
	Out[iDataOutN]='/';
	iDataOutN++;

	Sleep(80);
	Output(CommDev,Out,iDataOutN);
	bR=Input(CommDev,In,1);
	if(!bR)
	{
		if(bShowError)
		{
			if(g_bEnglish)
				AfxMessageBox("TPS: Can not read Data!",MB_ICONSTOP);
			else
				AfxMessageBox("TPS电源控制: 没有读取到反码!",MB_ICONSTOP);
		}
		Close(CommDev);
		return FALSE;
	}
	if(In[0]!=BYTE(~Out[0]))
	{
		if(bShowError)
		{
			if(g_bEnglish)
				AfxMessageBox("TPS: Setting Error or Outputing...!",MB_ICONSTOP);
			else
				AfxMessageBox("TPS电源控制: 设置失败,可能是设置参数有误,或正在输出!",MB_ICONSTOP);
		}
		Close(CommDev);
		return TRUE;
	}
	Close(CommDev);
	return TRUE;
}

int CPowerComm::WY5010_SetPower(CString sPowerComm, int iSetType, float fSetVol, float fSetCurr,BOOL bShowError)
{
	//设定稳压稳流数据
	//retrun : 0:OK 1:Fail 2:Reset
	HANDLE CommDev;
	BOOL bR;
	BYTE Out[100],In[40];      //
	bR=Open(CommDev,sPowerComm,2400);
	if(!bR)
	{
		if(bShowError)
		{
			if(g_bEnglish)
				AfxMessageBox("WY: Can not open this serial port!",NULL,MB_ICONSTOP);
			else
				AfxMessageBox("WY电源控制: 打开串口失败!",NULL,MB_ICONSTOP);
		}
		return 1;
	}

	CString strAddr;
	strAddr="100";//WY配CAN的地址码为0x11
	bR=SetAd(CommDev,strAddr);
	if(!bR)
	{
		if(bShowError)
		{
			if(g_bEnglish)
				AfxMessageBox("WY: SetAd Error or Com port!",NULL,MB_ICONSTOP);
			else
				AfxMessageBox("WY电源控制: 地址握手不正确，请确认仪器地址码!",NULL,MB_ICONSTOP);
		}
		Close(CommDev);
		return 1;
	}

	SetReadTime(CommDev,5000,2,5000);
	if(iSetType==0)
		Out[0]='U';
	else
		Out[0]='I';
	Sleep(100);
	Output(CommDev,Out,1);
	bR=Input(CommDev,In,1);
	if(!bR)
	{
		if(bShowError)
		{
			if(g_bEnglish)
				AfxMessageBox("WY: Can not read byte!",NULL,MB_ICONSTOP);
			else
				AfxMessageBox("WY电源控制: 没有读取到反码!",NULL,MB_ICONSTOP);
		}
		Close(CommDev);
		return 1;
	}
	if(In[0]!=BYTE(~Out[0]))
	{
		if(bShowError)
		{
			if(g_bEnglish)
				AfxMessageBox("WY: Byte error!",NULL,MB_ICONSTOP);
			else
				AfxMessageBox("WY电源控制: 读取到反码不正确!",NULL,MB_ICONSTOP);
		}
		Close(CommDev);
		return 1;
	}
	int i,N,iTempN;
	BYTE bb[100];
	CString strTemp;

	Out[0]=':';
	N=1;

	strTemp.Format("%.4f",fSetVol);
	StrToByte(strTemp,bb,iTempN);
	if(iTempN>=6)
		iTempN=6;
	for(i=0;i<iTempN;i++)
		Out[N+i]=bb[i];
	N=N+iTempN;

	Out[N]=':';
	N++;

	strTemp.Format("%.4f",fSetCurr);
	StrToByte(strTemp,bb,iTempN);
	if(iTempN>=6)
		iTempN=6;
	for(i=0;i<iTempN;i++)
		Out[N+i]=bb[i];
	N=N+iTempN;

	Out[N]='/';
	N++;

	Output(CommDev,Out,N);

	SetReadTime(CommDev,100,2,100);
	float fVol,fCurr;
	CString strVol,strCurr;
	while(1)
	{
		bR=Input(CommDev,In,14);
		if(!bR&&In[0]==0x46)
		{
			Close(CommDev);
			if(bShowError)
			{
				if(g_bEnglish)
					AfxMessageBox("WY: Set Error,please set again!",NULL,MB_ICONSTOP);
				else
					AfxMessageBox("WY电源控制: 设定错误,请重新设定!",NULL,MB_ICONSTOP);
			}
			return 1;
		}
		if(bR)
		{
			for(i=0;i<6;i++)
				bb[i]=In[i];
			fVol=ASCIItof(bb,6,strVol);

			for(i=0;i<6;i++)
				bb[i]=In[7+i];
			fCurr=ASCIItof(bb,6,strCurr);

			Close(CommDev);
			return 0;
		}
	}
	Close(CommDev);
	return 2;
}

void CPowerComm::StrToByte(CString strTemp, BYTE bb[], int &iN)
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

float CPowerComm::ASCIItof(unsigned char *bb, int n, CString &strTemp)
{
	char cTemp[30];
	for(int i=0;i<n;i++)
		cTemp[i]=bb[i];
	cTemp[i]='\0';
	strTemp=cTemp;
	return (float)atof(cTemp);
}

BOOL CPowerComm::TPS_Out_OFF(CString sPowerComm,BOOL bShowError)
{
	if(g_bDemo)
		return TRUE;
	HANDLE CommDev;
	BOOL bR;
	BYTE Out[40],In[40];      //
	bR=Open(CommDev,sPowerComm,2400);
	if(!bR)
	{
		if(bShowError)
		{
			if(g_bEnglish)
				AfxMessageBox("TPS: Can not open serial port!",MB_ICONSTOP);
			else
				AfxMessageBox("TPS电源控制: 打开串口失败!",MB_ICONSTOP);
		}
		return FALSE;
	}
	CString strAddr;
	strAddr.Format("%d",68);
	bR=SetAd(CommDev,strAddr);
	if(!bR)
	{
		if(bShowError)
		{
			if(g_bEnglish)
				AfxMessageBox("TPS: Comm. Fail, Addr.!",MB_ICONSTOP);
			else
				AfxMessageBox("TPS电源控制: 通讯失败, 地址握手失败!",MB_ICONSTOP);
		}
		Close(CommDev);
		return FALSE;
	}
	SetReadTime(CommDev,5000,2,5000);
	Out[0]='F';
	Out[1]='/';
	Sleep(100);
	Output(CommDev,Out,2);
	bR=Input(CommDev,In,1);
	if(!bR)
	{
		if(bShowError)
		{
			if(g_bEnglish)
				AfxMessageBox("TPS: Can not read data!",MB_ICONSTOP);
			else
				AfxMessageBox("TPS电源控制: 没有读取到反码!",MB_ICONSTOP);
		}
		Close(CommDev);
		return FALSE;
	}
	if(In[0]!=BYTE(~Out[0]))
	{
		if(bShowError)
		{
			if(g_bEnglish)
				AfxMessageBox("TPS: Can not read data!",MB_ICONSTOP);
			else
				AfxMessageBox("TPS电源控制: 读取到反码不正确!",MB_ICONSTOP);
		}
		Close(CommDev);
		return FALSE;
	}
	Close(CommDev);
	return TRUE;
}

BOOL CPowerComm::TPS_Out_ON(CString sPowerComm,BOOL bShowError)
{
	if(g_bDemo)
		return TRUE;
	HANDLE CommDev;
	BOOL bR;
	BYTE Out[40],In[40];      //
	bR=Open(CommDev,sPowerComm,2400);
	if(!bR)
	{
		if(bShowError)
		{
			if(g_bEnglish)
				AfxMessageBox("TPS: Can not open serial port!",MB_ICONSTOP);
			else
				AfxMessageBox("TPS电源控制: 打开串口失败!",MB_ICONSTOP);
		}
		return FALSE;
	}
	CString strAddr;
	strAddr.Format("%d",68);
	bR=SetAd(CommDev,strAddr);
	if(!bR)
	{
		if(bShowError)
		{
			if(g_bEnglish)
				AfxMessageBox("TPS: Comm. Fail,Addr!",MB_ICONSTOP);
			else
				AfxMessageBox("TPS电源控制: 通讯失败, 地址握手失败!",MB_ICONSTOP);
		}
		Close(CommDev);
		return FALSE;
	}
	SetReadTime(CommDev,10000,2,10000);
	Out[0]='O';
	Out[1]='/';
	Sleep(100);
	Output(CommDev,Out,2);
	bR=Input(CommDev,In,1);
	if(!bR)
	{
		if(bShowError)
		{
			if(g_bEnglish)
				AfxMessageBox("TPS: Can not read data!",MB_ICONSTOP);
			else
				AfxMessageBox("TPS电源控制: 没有读取到反码!",MB_ICONSTOP);
		}
		Close(CommDev);
		return FALSE;
	}
	if(In[0]!=BYTE(~Out[0]))
	{
		if(bShowError)
		{
			if(g_bEnglish)
				AfxMessageBox("TPS: Read data error!",MB_ICONSTOP);
			else
				AfxMessageBox("TPS电源控制: 读取到反码不正确!",MB_ICONSTOP);
		}
		Close(CommDev);
		return FALSE;
	}
	Close(CommDev);
	return TRUE;
}

BOOL CPowerComm::WY_Reset(CString strCom,BOOL bShowError)
{
	//复位,可以是在设定调节过程中使用复位
	HANDLE CommDev;
	BOOL bR;
	BYTE Out[1];      //
	bR=Open(CommDev,strCom,2400);
	if(!bR)
	{
		if(bShowError)
		{
			if(g_bEnglish)
				AfxMessageBox("WY: Can not open this serial port!",NULL,MB_ICONSTOP);
			else
				AfxMessageBox("WY电源控制: 打开串口失败!",NULL,MB_ICONSTOP);
		}
		return 1;
	}

	CString strAddr;
	strAddr.Format("%d",100);//WY配CAN的地址码为0x11
	bR=SetAd(CommDev,strAddr);
	if(!bR)
	{
		if(bShowError)
		{
			if(g_bEnglish)
				AfxMessageBox("WY: SetAd Error or Com port!",NULL,MB_ICONSTOP);
			else
				AfxMessageBox("WY电源控制: 地址握手不正确，请确认仪器地址码!",NULL,MB_ICONSTOP);
		}
		Close(CommDev);
		return 1;
	}

	Out[0]='R';
	Output(CommDev,Out,1);
	Close(CommDev);
	Sleep(1000);
	return TRUE;
}

BOOL CPowerComm::TPS500B_Read(CString strCom, int m_iAddr, float &fVol, float &fFreq, float &fCurr, float &fPow, float &fPF)
{
	// int m_iAddr = 68;
	BOOL m_bShowError = FALSE;
	// CString strCom = "COM1";
	HANDLE CommDev;
	BOOL bR;
	BYTE Out[40],In[80];      //
	bR=Open(CommDev,strCom,2400);
	if(!bR)
	{
		if(m_bShowError)
		{
			if(0)
				AfxMessageBox("TPS: Open Serial Port!",MB_ICONSTOP);
			else
				AfxMessageBox("TPS电源控制: 打开串口失败!",MB_ICONSTOP);
		}
		return FALSE;
	}
	CString strAddr;
	strAddr.Format("%d",m_iAddr);
	bR=SetAd(CommDev,strAddr);
	if(!bR)
	{
		if(m_bShowError)
		{
			if(0)
				AfxMessageBox("TPS: Comm. Fail,Addr.!",MB_ICONSTOP);
			else
				AfxMessageBox("TPS电源控制: 通讯失败, 地址握手失败!",MB_ICONSTOP);
		}
		Close(CommDev);
		return FALSE;
	}
	SetReadTime(CommDev,5000,2,5000);
	Out[0]='G';
	Out[1]='/';
	Output(CommDev,Out,2);
	bR=Input(CommDev,In,1+2+5+3+5+3+5+3+5+3+5+1);
	if(!bR)
	{
		if(m_bShowError)
		{
			if(0)
				AfxMessageBox("TPS: Can not Read Data!",MB_ICONSTOP);
			else
				AfxMessageBox("TPS电源控制: 没有读取到反码!",MB_ICONSTOP);
		}
		Close(CommDev);
		return FALSE;
	}
	if(In[0]!=BYTE(~Out[0]))
	{
		if(m_bShowError)
		{
			if(0)
				AfxMessageBox("TPS: Read data Error!",MB_ICONSTOP);
			else
				AfxMessageBox("TPS电源控制: 读取到反码不正确!",MB_ICONSTOP);
		}
		Close(CommDev);
		return FALSE;
	}
	
	CString strTemp;
	fVol	= ASCIItof2(&In[3],5,strTemp);
	fFreq	= ASCIItof2(&In[11],5,strTemp);
	fCurr	= ASCIItof2(&In[19],5,strTemp);
	fPow	= ASCIItof2(&In[27],5,strTemp);
	fPF		= ASCIItof2(&In[35],5,strTemp);
	
	Close(CommDev);
	return TRUE;
}

BOOL CPowerComm::KTY_SetPara(CString strCom,int iTypeUI, float fVol, float fCurr)
{
	HANDLE CommDev;
	BOOL bR;
//	BYTE Out[100],In[100];      //
	bR=Open(CommDev,strCom,9600);
	if(!bR)
	{
		if(g_bEnglish)
			AfxMessageBox("Open Serial Port!",MB_ICONSTOP);
		else
			AfxMessageBox("打开串口失败!",MB_ICONSTOP);
		return FALSE;
	}

	SetReadTime(CommDev,2000,2,2000);

	CString strTemp,strRe;
	CString sTemp;
	//发复位信号
	strTemp="*RST\r\n";
	OutPut_Str(CommDev,strTemp,strRe);

	if(iTypeUI==0)
	{
		//	*RST 稳压
		//	:SOUR:FUNC CURR
		//	:SOUR:CURR:MODE FIXED
		//	:SOUR:CURR:RANG MIN
		//	:SOUR:CURR:LEV 0
		//	:SENS:VOLT:PROT 25
		//	:SENS:FUNC "VOLT"
		//	:SENS:VOLT:RANG 20
		//	:FORM:ELEM VOLT
		/////////////////////////////////////////////
		strTemp=":SOUR:FUNC VOLT\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		strTemp=":SOUR:VOLT:MODE FIXED\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		strTemp=":SOUR:VOLT:RANG:AUTO ON\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		sTemp.Format("%.0f\r\n",fVol);
		strTemp=":SOUR:VOLT:LEV "+sTemp;
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		strTemp=":SOUR:FUNC VOLT\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		sTemp.Format("%e\r\n",fCurr/1000);
		strTemp=":SENS:CURR:PROT "+sTemp;
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		strTemp=":SENS:FUNC 'CURR'\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		strTemp=":SENS:CURR:RANG:AUTO ON\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		strTemp=":FORM:ELEM CURR\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
	}
	else
	{
		strTemp=":SOUR:FUNC CURR\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		strTemp=":SOUR:CURR:MODE FIXED\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		strTemp=":SOUR:CURR:RANG:AUTO ON\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		sTemp.Format("%e\r\n",fCurr/1000.0f);
		strTemp=":SOUR:CURR:LEV "+sTemp;
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		strTemp=":SENS:FUNC 'VOLT'\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		strTemp=":SENS:VOLT:RANG:AUTO ON\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		sTemp.Format("%e\r\n",fVol);
		strTemp=":SENS:VOLT:PROT "+sTemp;
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		strTemp=":FORM:ELEM VOLT\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);

/*		strTemp="*RST\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);

		strTemp=":SENS:FUNC:CONC OFF\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);

		strTemp=":SOUR:FUNC CURR\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);

		strTemp=":SENS:FUNC 'VOLT:DC'\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);

		strTemp=":SENS:VOLT:PROT 10\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);

		strTemp=":SOUR:CURR:START 1E-3\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);

		strTemp=":SOUR:CURR:STOP 10E-3\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);

		strTemp=":SOUR:CURR:STEP 1E-3\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);

		strTemp=":SOUR:CURR:MODE SWE\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);

		strTemp=":SOUR:SWE:RANG AUTO\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);

		strTemp=":SOUR:SWE:SPAC LIN\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);

		strTemp=":TRIG:COUN 10\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);

		strTemp=":SOUR:DEL 1\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);

		strTemp=":OUTP ON\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		strTemp=":READ?\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
*/
/*		strTemp="*RST\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		strTemp=":SENS:FUNC:CONC OFF\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);

		strTemp=":SOUR:FUNC CURR\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);

		strTemp=":SENS:FUNC 'VOLT:DC'\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);

		strTemp=":SENS:VOLT:PROT 10\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);

		strTemp=":SOUR:CURR:MODE LIST\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);

		strTemp=":SOUR:LIST:CURR 0,1E-3,0\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);

		strTemp=":TRIG:COUN 3\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		strTemp=":SOUR:DEL 0.1\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
			
		strTemp=":OUTP ON\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
			
		strTemp=":READ?\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe); */
/*			
		strTemp=":SOURce:CURRent:MODE LIST\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
//		strTemp=":SOURce:VOLTage:MODE LIST\r\n";
//		bR=OutPut_Str(CommDev,strTemp,strRe);
			
		strTemp=":SOURce:LIST:CURRent 10E-3,20E-3,5E-3\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
			
		strTemp=":SOURce:LIST:CURRent:APPend 10E-3,20E-3,5E-3\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
			
		strTemp=":SOURce:LIST:CURRent:POINts 3\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
			
//		strTemp=":SOURce:LIST:VOLTage 0,10,0\r\n";
//		bR=OutPut_Str(CommDev,strTemp,strRe);
			
//		strTemp=":SOURce:LIST:VOLTage:APPend 0,10,0\r\n";
//		bR=OutPut_Str(CommDev,strTemp,strRe);

//		strTemp=":SOURce:LIST:VOLTage:POINts?\r\n";
//		bR=OutPut_Str(CommDev,strTemp,strRe);
			
		strTemp=":SOURce:SWEep:RANGing AUTO\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
			
			
/*		strTemp=":SOUR:FUNC CURR\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		strTemp=":SOUR:CURR:MODE FIXED\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		strTemp=":SOUR:CURR:RANG:AUTO ON\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		sTemp.Format("%e\r\n",fCurr/1000);
		strTemp=":SOUR:CURR:LEV "+sTemp;
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		strTemp=":SENS:FUNC 'VOLT'\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		strTemp=":SENS:VOLT:RANG:AUTO ON\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
		
		sTemp.Format("%e\r\n",fVol);
		strTemp=":SENS:VOLT:PROT "+sTemp;
		bR=OutPut_Str(CommDev,strTemp,strRe);

		strTemp=":FORM:ELEM VOLT\r\n";
		bR=OutPut_Str(CommDev,strTemp,strRe);
*/	}

	Close(CommDev);
	return TRUE;
}

BOOL CPowerComm::OutPut_Str(HANDLE &CommDev,CString strTemp,CString &strRe)
{
	BYTE Out[1000];
	int iLength=strTemp.GetLength();
	int iN=0;
	for(int i = 0; i < iLength; i++)
	{
		Out[iN] = strTemp.GetAt(i);
		iN++;
	}
	Output(CommDev,Out,iN);
	return TRUE;
}

BOOL CPowerComm::OutPut_ReadErr(HANDLE &CommDev,CString strTemp,CString &strRe)
{
	BYTE In[1000];
	strTemp=":SYST:ERR?\r\n";
	OutPut_Str(CommDev,strTemp,strRe);

	SetReadTime(CommDev,2000,2,2000);
	BOOL bR;
	int iIn = 0;
	while(1)
	{
		BYTE bb[1];
		bR = Input(CommDev,bb,1);
		if(!bR)
		{
			return FALSE;
		}
		
		In[iIn] = bb[0];
		iIn++;
		if(In[iIn-2] == '\r' && In[iIn-1] == '\n')
		{
			break;
		}
	}

	if(In[0]!='0')
	{
		CString sTemp;
		strRe = "";
		for(int i = 0 ; i < (iIn-2) ; i++)
		{
			sTemp.Format("%c",In[i]);
			strRe = strRe + sTemp;
		}
		Sleep(100);
		return FALSE;
	}

	Sleep(100);
	return TRUE;
}

BOOL CPowerComm::OutPut_ReadData(HANDLE &CommDev,float &fVol,float &fCurr)
{
	BYTE In[1000];
	CString strTemp = ":MEAS?\r\n";
	CString strRe;
	OutPut_Str(CommDev,strTemp,strRe);
	
	SetReadTime(CommDev,2000,2,2000);
	BOOL bR;
	int iIn = 0;

	while(1)
	{
		BYTE bb[1];
		bR=Input(CommDev,bb,1);
		if(!bR)
		{
			return FALSE;
		}

		In[iIn]=bb[0];
		iIn++;
		if(In[iIn-1] == 0x0D)
			break;
	}

	CString sTemp;
	strRe="";
	for(int i=0;i<iIn-1;i++)
	{
		sTemp.Format("%c",In[i]);
		strRe = strRe+sTemp;
	}

	if(g_iSetType2 == 0)//电压源
	{
		fVol  = g_fSetVol2;
		fCurr = (float)atof(strRe);
	}
	else//电流源
	{
		fCurr = g_fSetCurr2/1000;
		fVol  = (float)atof(strRe);
	}

	return TRUE;
}

BOOL CPowerComm::KTY_Out_On(CString strCom,float &fVol,float &fCurr)
{
	HANDLE CommDev;
	BOOL bR;
	//	BYTE Out[100],In[100];      // 
	bR = Open(CommDev,strCom,9600);
	if(!bR)
	{
		if(g_bEnglish)
		{
			AfxMessageBox("Open Serial Port!",MB_ICONSTOP);
		}
		else
		{
			AfxMessageBox("打开串口失败!",MB_ICONSTOP);
		}

		return FALSE;
	}
	
	SetReadTime(CommDev,5000,2,5000);
	
	CString strTemp,strRe;

	strTemp = ":TRIG:COUN 1\r\n";
	OutPut_Str(CommDev,strTemp,strRe);

	strTemp=":TRIG:OUTP SENS\r\n";
	OutPut_Str(CommDev,strTemp,strRe);
	//开灯后延时3ms发触发信号
	strTemp="TRIG:DELay 0.003\r\n";
	OutPut_Str(CommDev,strTemp,strRe);

	strTemp=":OUTP ON\r\n";
	OutPut_Str(CommDev,strTemp,strRe);

	bR=OutPut_ReadErr(CommDev,strTemp,strRe);
	if(!bR)
	{
		Close(CommDev);
		return FALSE;
	}

	OutPut_ReadData(CommDev,fVol,fCurr);

/*
	strTemp=":TRIG:COUN 1\r\n";
	OutPut_Str(CommDev,strTemp,strRe);
	
	strTemp=":TRIG:OUTP SENS\r\n";
	OutPut_Str(CommDev,strTemp,strRe);
	
	strTemp="TRIG:WIDth 0.0010\r\n";
	OutPut_Str(CommDev,strTemp,strRe);
	
	strTemp="TRIG:DELay 1\r\n";
	OutPut_Str(CommDev,strTemp,strRe);
	
	strTemp=":OUTP ON\r\n";
	OutPut_Str(CommDev,strTemp,strRe);

	strTemp=":SOUR:PULS:WIDT 0.002\r\n";
	OutPut_Str(CommDev,strTemp,strRe);
	strTemp=":SOUR:PULS:DEL 0.003\r\n";
	OutPut_Str(CommDev,strTemp,strRe);
	strTemp=":TRIG:COUN 1\r\n";
	OutPut_Str(CommDev,strTemp,strRe);
	
	OutPut_ReadData(CommDev,fVol,fCurr);
*/
	Close(CommDev);
	return TRUE;
}

BOOL CPowerComm::KTY_Out_Off(CString strCom)
{
	HANDLE CommDev;
	BOOL bR;
	//	BYTE Out[100],In[100];      //
	bR=Open(CommDev,strCom,9600);
	if(!bR)
	{
		if(g_bEnglish)
		{
			AfxMessageBox("Open Serial Port!",MB_ICONSTOP);
		}
		else
		{
			AfxMessageBox("打开串口失败!",MB_ICONSTOP);
		}
		return FALSE;
	}
	
	SetReadTime(CommDev,1000,2,1000);
	
	CString strTemp,strRe;
	//发复位信号
	strTemp = ":OUTP OFF\r\n";
	OutPut_Str(CommDev,strTemp,strRe);
	
	Close(CommDev);
	return TRUE;
}
