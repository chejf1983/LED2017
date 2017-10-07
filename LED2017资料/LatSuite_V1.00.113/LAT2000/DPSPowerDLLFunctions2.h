#ifndef DPS_POWER_DLL_FUNCTIONS
#define DPS_POWER_DLL_FUNCTIONS

#include "DPSDefinition2.h"

#define DllExport __stdcall

// ������������
extern BOOL DllExport DPS_SetDeviceType2(DeviceType deviceType);

// ��ʼ����ָ��ͨ�Ŵ���
// This function should be called after the calling of SetDeviceType
extern BOOL DllExport DPS_InitializeComm(int iCOM);

// ͨ����������������������
extern BOOL DllExport DPS_SetDeviceTypeByName(char strTypeName[]);

// ���õ�ѹ��Ƶ�ʿ����������
// iRangU 0:0-150V		1:0-300V
extern BOOL DllExport DPS_FastRun(float fVoltageV, float fFrequenceHZ);

// ��ȡ��������
extern BOOL DllExport DPS_GetTypeName(int iIndex, char strName[]);

// ��ȡDLL֧�ֵ�������������
extern int DllExport DPS_GetTypeCount();

// ��ȡ��ǰ���õ���������
extern DeviceType DllExport DPS_GetDeviceType();

// ͨ���������ƻ�ȡ��������
extern BOOL DllExport DPS_FindDeviceType(char strTypeName[], DeviceType & deviceType);

// ������ʾģʽ��DLL�����������
extern void DllExport DPS_SetDemo(BOOL bOnOff);

// ����ͨ��ģʽ
extern BOOL DllExport DPS_InRemote();

// �˳�ͨ��ģʽ
extern BOOL DllExport DPS_OutRemote();

// �Ƿ������״̬
extern BOOL DllExport DPS_IsRunning();

// ���ò�����ͨ���ṹ��
extern BOOL DllExport DPS_SetParameter(Parameter & data);

// ���ò���
extern BOOL DllExport DPS_SetParameterEx(int iMemory, float fFrequency, float fFrequencyLow,
	float fFrequencyHigh, int iRangeU, float fVoltage, float fVoltageLow, float fVoltageHigh,
	BOOL bOvercurrentFoldBackEnable, BOOL  bVoltageAutoAdjustEnable, BOOL  bHarmonicEnable,
	BOOL  bExternalVoltageSamplingEnable, BOOL  bExternalCurrentSamplingEnable, float fExternalCurrentFactor);

// ���������״̬ʱ���ò���,ͨ���ṹ��
extern BOOL DllExport DPS_SetParameterRunning(float fVoltageV, float fFrequencyHZ, float fAlarmCurrentA, float fAlarmPowerW);

// �������
extern BOOL DllExport DPS_StartOutput(int iMemory);

// ֹͣ���
extern BOOL DllExport DPS_StopOutput(int iMemory);

// ��ȡ����,ͨ���ṹ��
extern BOOL DllExport DPS_GetParameter(Parameter & data, int iMemory);

// ��ȡ����
extern BOOL DllExport DPS_GetParameterEx(int iMemory, float &fFrequency, float &fFrequencyLow,
	float &fFrequencyHigh, int &iRangeU, float &fVoltage, float &fVoltageLow, float &fVoltageHigh,
	BOOL &bOvercurrentFoldBackEnable, BOOL  &bVoltageAutoAdjustEnable, BOOL  &bHarmonicEnable,
	BOOL &bExternalVoltageSamplingEnable, BOOL &bExternalCurrentSamplingEnable, float &fExternalCurrentFactor);

// ���������״̬ʱ��ȡʵʱ���ݣ�ͨ���ṹ��
extern BOOL DllExport DPS_GetRealTimeData(RealTimeData & data);

// ���������״̬ʱ��ȡʵʱ����
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

/// ���¶��꺯����֧��DPS1010_V100, DPS1020, DPS1020_V100
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