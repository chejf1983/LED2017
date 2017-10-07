#ifndef DPS_POWER_DLL_FUNCTIONS
#define DPS_POWER_DLL_FUNCTIONS

#include "DPSDefinition2.h"

#define DllExport __stdcall

// 设置仪器类型
extern BOOL DllExport DPS_SetDeviceType2(DeviceType deviceType);

// 初始化，指定通信串口
// This function should be called after the calling of SetDeviceType
extern BOOL DllExport DPS_InitializeComm(int iCOM);

// 通过仪器名称设置仪器类型
extern BOOL DllExport DPS_SetDeviceTypeByName(char strTypeName[]);

// 设置电压和频率快速启动输出
// iRangU 0:0-150V		1:0-300V
extern BOOL DllExport DPS_FastRun(float fVoltageV, float fFrequenceHZ);

// 获取仪器名称
extern BOOL DllExport DPS_GetTypeName(int iIndex, char strName[]);

// 获取DLL支持的仪器类型总数
extern int DllExport DPS_GetTypeCount();

// 获取当前设置的仪器类型
extern DeviceType DllExport DPS_GetDeviceType();

// 通过仪器名称获取仪器类型
extern BOOL DllExport DPS_FindDeviceType(char strTypeName[], DeviceType & deviceType);

// 设置演示模式，DLL产生随机数据
extern void DllExport DPS_SetDemo(BOOL bOnOff);

// 进入通信模式
extern BOOL DllExport DPS_InRemote();

// 退出通信模式
extern BOOL DllExport DPS_OutRemote();

// 是否在输出状态
extern BOOL DllExport DPS_IsRunning();

// 设置参数，通过结构体
extern BOOL DllExport DPS_SetParameter(Parameter & data);

// 设置参数
extern BOOL DllExport DPS_SetParameterEx(int iMemory, float fFrequency, float fFrequencyLow,
	float fFrequencyHigh, int iRangeU, float fVoltage, float fVoltageLow, float fVoltageHigh,
	BOOL bOvercurrentFoldBackEnable, BOOL  bVoltageAutoAdjustEnable, BOOL  bHarmonicEnable,
	BOOL  bExternalVoltageSamplingEnable, BOOL  bExternalCurrentSamplingEnable, float fExternalCurrentFactor);

// 仪器在输出状态时设置参数,通过结构体
extern BOOL DllExport DPS_SetParameterRunning(float fVoltageV, float fFrequencyHZ, float fAlarmCurrentA, float fAlarmPowerW);

// 启动输出
extern BOOL DllExport DPS_StartOutput(int iMemory);

// 停止输出
extern BOOL DllExport DPS_StopOutput(int iMemory);

// 获取参数,通过结构体
extern BOOL DllExport DPS_GetParameter(Parameter & data, int iMemory);

// 获取参数
extern BOOL DllExport DPS_GetParameterEx(int iMemory, float &fFrequency, float &fFrequencyLow,
	float &fFrequencyHigh, int &iRangeU, float &fVoltage, float &fVoltageLow, float &fVoltageHigh,
	BOOL &bOvercurrentFoldBackEnable, BOOL  &bVoltageAutoAdjustEnable, BOOL  &bHarmonicEnable,
	BOOL &bExternalVoltageSamplingEnable, BOOL &bExternalCurrentSamplingEnable, float &fExternalCurrentFactor);

// 仪器在输出状态时获取实时数据，通过结构体
extern BOOL DllExport DPS_GetRealTimeData(RealTimeData & data);

// 仪器在输出状态时获取实时数据
extern BOOL DllExport DPS_GetRealTimeDataEx(BYTE &ucState, float &fVoltageV, float &fCurrentA, float &fPowerFactor,
	float &fPower, float &fFrequency, float &fVoltageWaveRatio, float &fCurrentWaveRatio, float &fVoltageWaveValue,
	float &fCurrentWaveValue, float &fVoltageHamonicLose, float &fCurrentHamonicLose);

extern LimitData DllExport DPS_GetLimitData();

extern void DllExport DPS_GetLimitDataEx(float &fCurrentRange1Low, float &fCurrentRange1Up,
		float &fCurrentRange2Low, float &fCurrentRange2Up,
		float &fVoltageRange1Low, float &fVoltageRange1Up,
		float &fVoltageRange2Low, float &fVoltageRange2Up,
		float &fPowerLow, float &fPowerUp,
		float &fFrequencyLow, float &fFrequencyUp,
		float &fExternalCurrentFactorLow, float &fExternalCurrentFactorUp,
		BOOL  &bOvercurrentFoldBackEnable,
		BOOL  &bExternalCurrentSamplingEnable,
		BOOL  &bVoltageAutoAdjustEnable,
		BOOL  &bHarmonicEnable,
		BOOL  &bExternalVoltageSamplingEnable);

/// 以下定标函数仅支持DPS1010_V100, DPS1020, DPS1020_V100
/// Function of DPS_SERIES_1010EX series
// Only for DPS_SERIES_1010EX
extern BOOL DllExport DPS_OuterScale(float fValue);						// 'X'

// Only for DPS_SERIES_1010EX
extern BOOL DllExport DPS_Scale(ScaleType nType, float fValue);			// 'U' | 'I' | 'X'

// Only for DPS_SERIES_1010EX
extern BOOL DllExport DPS_Range(ScaleType nType, int &nRange);			// 'C' | 'H'

// Only for DPS_SERIES_1010EX
extern BOOL DllExport DPS_ExitScaleI();									// 'F'

// Only for DPS_SERIES_1010EX
extern BOOL DllExport DPS_EnterScaleI();								// 'E'

// Only for DPS_SERIES_1010EX
extern BOOL DllExport DPS_ExitScaleU();									// 'B'

// Only for DPS_SERIES_1010EX
extern BOOL DllExport DPS_EnterScaleU();								// 'A'

#endif