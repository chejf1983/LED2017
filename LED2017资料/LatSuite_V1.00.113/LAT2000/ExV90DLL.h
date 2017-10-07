////ExV90DLL.h
//版权所有 2007-2011 杭州远方光电信息股份有限公司(EVERFINE)

// #include "ExHaasDLL.h"

#ifndef _EXV90DLL_H_
#define _EXV90DLL_H_

enum HaasMode{
	H12_Bin03     =  0x03,    // Bin 03模式
	H12_Bin10     =  0x01,    // Bin 10模式
	H12_Bin64     =  0x00,    // Bin 10模式
	H12_BinFull   =  0x02,    // Bin Full模式
};

enum CCDMode{
	H12_Line64    =  0x00,    // CCD  64模式
	H12_Line128   =  0x01,    // CCD 128模式
};

enum HaasTypeTMP{
	H12_TMP_CCD_IN  = 0x01,   // CCD内部温度
	H12_TMP_CCD_OUT = 0x02,   // CCD外部温度(电流)
	H12_TMP_EN      = 0x03,   // 环境温度
	H12_TMP_HEAT    = 0x04,   // 散热器温度
};

enum HaasColor{
	H12_H_COLOR_OFF  = 0,
	H12_H_COLOR_ON   = 1,
	H12_H_COLOR_A1   = 2,
	H12_H_COLOR_A2   = 3,
	H12_H_COLOR_B    = 4, // 蓝色 BLUE
	H12_H_COLOR_G    = 5, // 绿色 GREEN
	H12_H_COLOR_O    = 6, // 橙色 ORANGE
	H12_H_COLOR_R    = 7, // 红色 RED
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
