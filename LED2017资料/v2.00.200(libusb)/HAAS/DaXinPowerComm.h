// DaXinPowerComm.h: interface for the CDaXinPowerComm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DAXINPOWERCOMM_H__E78EC153_A1E9_4820_BD7F_7908BD422EAE__INCLUDED_)
#define AFX_DAXINPOWERCOMM_H__E78EC153_A1E9_4820_BD7F_7908BD422EAE__INCLUDED_

#include "Serial.h"

#define DX_ADDR_PRO 0x00 //设备地址
#define DX_ADDR_CMP 0xFB //计算机地址

#define DX_SET_VOLT			0x20
#define DX_SET_CURR			0x21
#define DX_SET_VOLT_MAX		0x22
#define DX_SET_CURR_MAX		0x23
#define DX_SET_OUTPUT		0x24


#define DX_READ_STAD		0x27 //读取状态
#define DX_READ_PARA		0x28 //读取输出参数

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDaXinPowerComm : public CObject  
{
public:
	CString m_strCOM;
	int m_iBaudRate;

	BOOL DX_Power_Init(int iCOM);
	BOOL DX_Power_SetPara(float fVol,float fCurr);
	BOOL DX_Power_Output(BOOL bOn);
	BOOL DX_Power_ReadPara(float &fVol,float &fCurr);

	Serial m_ser;

	CDaXinPowerComm();
	virtual ~CDaXinPowerComm();

};

#endif // !defined(AFX_DAXINPOWERCOMM_H__E78EC153_A1E9_4820_BD7F_7908BD422EAE__INCLUDED_)
