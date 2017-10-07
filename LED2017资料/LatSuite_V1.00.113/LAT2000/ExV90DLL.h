////ExV90DLL.h
//��Ȩ���� 2007-2011 ����Զ�������Ϣ�ɷ����޹�˾(EVERFINE)

// #include "ExHaasDLL.h"

#ifndef _EXV90DLL_H_
#define _EXV90DLL_H_

enum HaasMode{
	H12_Bin03     =  0x03,    // Bin 03ģʽ
	H12_Bin10     =  0x01,    // Bin 10ģʽ
	H12_Bin64     =  0x00,    // Bin 10ģʽ
	H12_BinFull   =  0x02,    // Bin Fullģʽ
};

enum CCDMode{
	H12_Line64    =  0x00,    // CCD  64ģʽ
	H12_Line128   =  0x01,    // CCD 128ģʽ
};

enum HaasTypeTMP{
	H12_TMP_CCD_IN  = 0x01,   // CCD�ڲ��¶�
	H12_TMP_CCD_OUT = 0x02,   // CCD�ⲿ�¶�(����)
	H12_TMP_EN      = 0x03,   // �����¶�
	H12_TMP_HEAT    = 0x04,   // ɢ�����¶�
};

enum HaasColor{
	H12_H_COLOR_OFF  = 0,
	H12_H_COLOR_ON   = 1,
	H12_H_COLOR_A1   = 2,
	H12_H_COLOR_A2   = 3,
	H12_H_COLOR_B    = 4, // ��ɫ BLUE
	H12_H_COLOR_G    = 5, // ��ɫ GREEN
	H12_H_COLOR_O    = 6, // ��ɫ ORANGE
	H12_H_COLOR_R    = 7, // ��ɫ RED
};

extern BOOL __stdcall V90_GetType(int &iAD_W,int &iCCD_N, BOOL bEnglish);
extern BOOL __stdcall V90_TestTMP(HaasTypeTMP typeTMP,int iAvgN,float &fTMP,int &iTMP);
extern BOOL __stdcall V90_SN_Read(BYTE buf[]);
extern BOOL __stdcall V90_SN_Write(CString strN,int iBaudRate);
extern BOOL __stdcall V90_SetCool(BOOL bOn);
extern BOOL __stdcall V90_Sample(int iTrig,CCDMode lineMode,HaasMode haasMode,float fIntTime,float fData[],  float fZero[], BOOL &bOverAD);
extern BOOL __stdcall V90_SeleColor(HaasColor color, BOOL bReset);
extern BOOL __stdcall V90_SamplePH(int iPhRange,float &fPhAd,BOOL bCal);
extern BOOL __stdcall V90_GetDriverVer(CString &strVer);
extern BOOL __stdcall V90_GetCommMode(BOOL bUSB,CString strHassCom);
extern BOOL __stdcall V90_SetCommBaud(int iBuadRate);
extern BOOL __stdcall V90_GetLastPhAD(float &fPhAd);

extern BOOL  __stdcall V90_SetType(int iBeginAddN, int iUserNum);
extern BOOL  __stdcall V90_GetYaAD(float fYaAD[], int &iN);

#endif
