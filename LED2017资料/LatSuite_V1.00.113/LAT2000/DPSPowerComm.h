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
	BOOL InitializeComm(int iCOM);	// 初始化，指定通信串口

	void SetDemo(BOOL bOnOff);		// 设置演示模式,产生随机数据

	BOOL SetDeviceType(DeviceType deviceType);	// 设置通信仪器类型
	
	BOOL SetDeviceTypeByName(char strName[]);	// 通过通信仪器名称设置仪器类型

	BOOL InRemote();		// 进入通信模式

	BOOL OutRemote();		// 退出通信模式

	BOOL FastRun(float fVoltage, float fFrequence);		// 设置电压和频率快速启动输出,同时会进入通信模式

	BOOL SetParameter(Parameter & data);	// 设置参数

	BOOL SetParameterRunning(float fVoltageV, float fFrequencyHZ, float fAlarmCurrentA, float fAlarmPowerW);		// 设置参数

	BOOL StartOutput(int iMemory = 0);		// 启动输出

	BOOL StopOutput(int iMemory = 0);		// 停止输出

	BOOL GetParameter(Parameter & data, int iMemory = 0);	// 获取参数

	BOOL GetRealTimeData(RealTimeData & data);		// 获取时实数据

	int  GetTypeCount();		// 获取DLL支持的DLL类型总数

	BOOL GetTypeName(int iIndex, char strName[]);	// 获取仪器名称

	LimitData GetLimitData();		// 获取当前仪器的参数限值

	DeviceType GetDeviceType();		// 获取当前仪器类型

	BOOL IsRunning();


public:
	/// 以下函数仅在DPS_SERIES_1010EX系列仪器定标时使用
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

