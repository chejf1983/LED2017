// Copyright (C) EVERFINE
// All rights reserved.
//
// This is the definition of DPS Power communication class.
// C++ programer can easyly control DPS Power by calling functions 
// of a intance of this class.

#pragma once
#include "DPSDefinition.h"


/// C++ class
class CBaseComm;
class CDPSPowerComm
{
public:
	CDPSPowerComm();
	~CDPSPowerComm(void);

public:
	BOOL InitializeComm(int iCOM);	// ��ʼ����ָ��ͨ�Ŵ���

	void SetDemo(BOOL bOnOff);		// ������ʾģʽ,�����������

	BOOL SetDeviceType(DeviceType deviceType);	// ����ͨ����������
	
	BOOL SetDeviceTypeByName(char strName[]);	// ͨ��ͨ����������������������

	BOOL InRemote();		// ����ͨ��ģʽ

	BOOL OutRemote();		// �˳�ͨ��ģʽ

	BOOL FastRun(float fVoltage, float fFrequence);		// ���õ�ѹ��Ƶ�ʿ����������,ͬʱ�����ͨ��ģʽ

	BOOL SetParameter(Parameter & data);	// ���ò���

	BOOL SetParameterRunning(float fVoltageV, float fFrequencyHZ, float fAlarmCurrentA, float fAlarmPowerW);		// ���ò���

	BOOL StartOutput(int iMemory = 0);		// �������

	BOOL StopOutput(int iMemory = 0);		// ֹͣ���

	BOOL GetParameter(Parameter & data, int iMemory = 0);	// ��ȡ����

	BOOL GetRealTimeData(RealTimeData & data);		// ��ȡʱʵ����

	int  GetTypeCount();		// ��ȡDLL֧�ֵ�DLL��������

	BOOL GetTypeName(int iIndex, char strName[]);	// ��ȡ��������

	LimitData GetLimitData();		// ��ȡ��ǰ�����Ĳ�����ֵ

	DeviceType GetDeviceType();		// ��ȡ��ǰ��������

	BOOL IsRunning();


public:
	/// ���º�������DPS_SERIES_1010EXϵ����������ʱʹ��
	/// Function of DPS_SERIES_1010EX
	// Only for DPS_SERIES_1010EX
	BOOL OuterScale(float fValue);					// 'X'

	// Only for DPS_SERIES_1010EX
	BOOL Scale(ScaleType nType, float fValue);		// 'U' | 'I' | 'X'

	// Only for DPS_SERIES_1010EX
	BOOL Range(ScaleType nType, int &nRange);		// 'C' | 'H'

	// Only for DPS_SERIES_1010EX
	BOOL ExitScaleI();								// 'F'

	// Only for DPS_SERIES_1010EX
	BOOL EnterScaleI();								// 'E'

	// Only for DPS_SERIES_1010EX
	BOOL ExitScaleU();								// 'B'

	// Only for DPS_SERIES_1010EX
	BOOL EnterScaleU();								// 'A'
	
	void InitLimitData(LimitData & data);

	void InitParameter(Parameter & data);

private:
	BOOL m_bRunning;

	DeviceType m_deviceType;	// There may be little difference between each type of device
	DPSSeries  m_seriesType;
	CBaseComm *m_pDPSComm;
	LimitData  m_limitData;
	Parameter  m_preParameter;	// The latest parameter set by SetParameter function
};

