// PowerComm.h: interface for the CPowerComm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POWERCOMM_H__70B317D8_7B46_4ABE_8BA3_3530C7D53A31__INCLUDED_)
#define AFX_POWERCOMM_H__70B317D8_7B46_4ABE_8BA3_3530C7D53A31__INCLUDED_

#include "math.h"
#include "thsFun.h"     // for PF4000


#define PD_COMM_OK         0
#define PD_COMM_FAIL       1   //....


#define CM_TEST_EX_START2  0xB4    //触发测试 TRIG_OUT
#define CM_TEST_START      0xB5    //采样积分时间
#define CM_TEST_EX_START   0xB7    //触发测试 TRIG_IN

///////////////////////////////////////////////
//RS232/485通讯
#define HAAS_AD   0x36
#define HAAS_BAUD 115200
///////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define CM_TEST_TMP        0xB8    //温度

// 
// 由PowDLL V1.07修改,目的是为了增加USBCAN的兼容
//                           damin 2008.10
//
class CPowerComm    
{
public:
	static BOOL KTY_Out_On(CString strCom,float &fVol,float &fCurr);
	static BOOL KTY_Out_Off(CString strCom);
	static BOOL OutPut_Str(HANDLE &CommDev,CString strTemp,CString &strRe);
	static BOOL OutPut_ReadErr(HANDLE &CommDev,CString strTemp,CString &strRe);
	static BOOL OutPut_ReadData(HANDLE &CommDev,float &fVol,float &fCurr);
	static BOOL KTY_SetPara(CString strCom, int iTypeUI,float fVol,float fCurr);

	static BOOL TPS500B_Read(CString strCom,int m_iAddr,float &fVol, float &fFreq, float &fCurr, float &fPow, float &fPF);
	static BOOL TPS_SetPower(CString sPowerComm,int iSetType,float fSetVol,float fSetCurr,BOOL bShowError=FALSE);
	static BOOL TPS_Out_ON(CString sPowerComm,BOOL bShowError=FALSE);
	static BOOL TPS_Out_OFF(CString sPowerComm,BOOL bShowError=FALSE);

	static float ASCIItof(unsigned char *bb, int n, CString &strTemp);
	static void  StrToByte(CString strTemp, BYTE bb[], int &iN);

	static int   WY5010_SetPower(CString sPowerComm,int iSetType,float fSetVol,float fSetCurr,BOOL bShowError=FALSE);
	static BOOL  WY_Reset(CString strCom,BOOL bShowError=FALSE);

	static BOOL PH_GetCurData(CString strCom,CString strAddr,float &fMain, float &fRef);

	// PDC:    PowDLL_Comm
	static void      PDC_GetPowerList(int &iN,CString sPowerTypeList[]);
	static int       PDC_GetPower(CString sCom,CString sType,int &iPowerType,float &fU1,float &fI1,float &fP1,float &fPf1,float &fU2,float &fI2,float &fP2,float &fPf2,CProgressCtrl &m_cProgress,BOOL bPro);
	static CString   PDC_GetVer();

	CPowerComm();
	virtual ~CPowerComm();

private:
	static int m_iCurrStep;
	enum Comm_Type
	{
		Comm_Type_RS      = 0,
		Comm_Type_CAN2RS  = 1,
	};
	static Comm_Type               m_typeComm;
	static int                     m_iCan2RS_Addr;
//	static CCT_DebugerComm::TypeRS m_typeRS;
	static int                     m_iCan2RS_TimeOut;

	static BOOL    GetPower_WT210(CString sPowerCom,float &fU, float &fI, float &fP, float &fPF);
	static BOOL    GetPower_PF4000(CString sPowerCom,float &fU, float &fI, float &fP, float &fPF);
	static BOOL    GetPower_TYPE8(CString sPowerCom,float &fU, float &fI, float &fP, float &fPF);
	static BOOL    GetPower_TYPE9(CString sPowerCom,CString sPowerAd,float &fU, float &fI, float &fP, float &fPF);
	static float   ASCIItof2(unsigned char *bb, int n, CString &strTemp);
	static BOOL    GetPower_WY(CString strCom,float &fU, float &fI);
	static BOOL    GetPower_WY9BITS(CString strCom,float &fU, float &fI,CString strAddr);
	static BOOL    GetPower_PF9805_9BITS(CString sPowerCom,float &fU, float &fI, float &fP, float &fPF);
	static BOOL    Open(HANDLE &CommDev,CString sCom, int iBaudRate);
	static BOOL    Close(HANDLE &CommDev);
	static BOOL    SetReadTime(HANDLE &CommDev, int iReadIntervalTimeOut, int iReadTotalTimeoutMultiplier, int iReadTotalTimeoutConstant);
	static BOOL    Output(HANDLE &CommDev, BYTE *OutData, DWORD OutN);
	static BOOL    Input(HANDLE &CommDev, BYTE *InData, DWORD InN);
	static void    WordToByte(WORD Word, BYTE &hByte, BYTE &lByte);
	static float   btof196(BYTE *bb);
	static float   btof(BYTE *bb);
	static BOOL    SetDCBParity(HANDLE &CommDev,BYTE Parity);
	static BOOL    SetAd(HANDLE &CommDev, CString sAd);
	static CString sStringTo(BYTE *bb, int number);
	static float   ASCIItof(unsigned char *bb, int n);
	static BOOL    YF2401_FlashData(CString sCom,float &fUs,float &fUl,float &fIl,float &fPow,float &fFreq,float &fPF,float &fUIK);
	static float   ASCIItof_2(unsigned char *bb, int n, CString &strTemp);
};

#endif // !defined(AFX_POWERCOMM_H__70B317D8_7B46_4ABE_8BA3_3530C7D53A31__INCLUDED_)
