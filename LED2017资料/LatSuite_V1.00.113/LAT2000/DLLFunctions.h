#ifndef HAAS1200METER_DLL
#define HAAS1200METER_DLL

#include "Definition.h"

#define DLLCALL __stdcall

extern void DLLCALL HAAS1200_SetCIEXYReCalculate(float fx, float fy, float & fu_, float & fv_, float & fTc);

extern void DLLCALL HAAS1200_SetCIEU_V_ReCalculate(float fu_, float fv_, float &fx, float &fy, float &fTc);

extern BOOL DLLCALL HAAS1200_InitMeter(BOOL bDemo, BOOL bEnglish);

extern void DLLCALL HAAS1200_SetCalPath(char strPath[]);

extern BOOL DLLCALL HAAS1200_SetCommType(int iCommType);

extern BOOL DLLCALL HAAS1200_SetCom(char * strCom);

extern int DLLCALL HAAS1200_GetCCDPixNum();

extern BOOL DLLCALL HAAS1200_GetSerialNumber(char * strSN);

extern float DLLCALL HAAS1200_GetWL_Range1();

extern float DLLCALL HAAS1200_GetWL_Range2();

extern float DLLCALL HAAS1200_GetWL(int iPixel);

extern void DLLCALL HAAS1200_SetTestMode(int iTestMode);

extern BOOL DLLCALL HAAS1200_SetBinRange(int iBinRange);

extern void DLLCALL HAAS1200_SetTestAvgNum(int iAvgNum);

extern void DLLCALL HAAS1200_SetIntTime(float fIntTime);

extern BOOL DLLCALL HAAS1200_SetShutterOn();

extern BOOL DLLCALL HAAS1200_SetShutterOff();

extern BOOL DLLCALL HAAS1200_AutoIntegralTime(float & fIntegralTimems, float fMaxTimems = 60000, float fProperIp = 20000);

extern BOOL DLLCALL HAAS1200_SampleAD(float fAD[], BOOL bAutoGetDark = FALSE);

extern BOOL DLLCALL HAAS1200_CalcColorA(float fSetCalcInterval,  /* 0.1 or 0.2 0.5 1.0 */
								 float fIntTimeMs, float fOnLampTimeMs, 
								 float fDarkAD[], float fAD[], CNewTestColorData &data);

extern BOOL DLLCALL HAAS1200_TestOneA(CNewTestColorData &data, float fAD[]);

extern BOOL DLLCALL HAAS1200_CalcColorB(float fSetCalcInterval,  /* 0.1 or 0.2 0.5 1.0 */
			   float fIntTimeMs, float fOnLampTimeMs, 
			   float fDarkAD[], float fAD[], NewTestColorData &data);

extern BOOL DLLCALL HAAS1200_TestOneB(NewTestColorData &data, float fAD[]);

extern void DLLCALL HAAS1200_ShowSpectrumCalDlg();

extern void DLLCALL HAAS1200_ShowTestDialog();

extern BOOL DLLCALL HAAS1200_SetMultiShutter(int iShuterrIndex);

extern BOOL DLLCALL HASS1200_SetICommPoint(ICommRS232 * pIComm);

extern BOOL DLLCALL HASS1200_SetTestSigType(int iSigType);

#endif