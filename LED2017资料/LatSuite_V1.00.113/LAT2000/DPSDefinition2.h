#ifndef DPS_DEFINITION
#define DPS_DEFINITION

#pragma once


#define URANGE_150V 0
#define URANGE_300V 1

// Classify all DPS devices into three general type
enum DPSSeries2{
	DPS_SERIES_1030	= 1,		// DPS1030, DPS1060
	DPS_SERIES_1010 = 2,		// DPS1005, DPS1005_V100, DPS1010
	DPS_SERIES_1010EX = 3,		// DPS1010_V100, DPS1020, DPS1020_V100
	
	// There is little difference between DPS_SERIES_1010 and DPS_SERIES_GK
	// 1. the address of device:DPS_SERIES_1010(0x1B) DPS_SERIES_GK(0x2B)
	// 2. SetParameterRunning function:DPS_SERIES_GK don't return the radix complement of command 'T'
	DPS_SERIES_GK = 4,			// GK10005, GK10010, GK10030, GK10060
};

enum DeviceType2{
	DPS_1005 = 1,
	DPS_1005_V100 = 2,
	DPS_1010 = 3,
	GK_10005 = 4,
	GK_10010 = 5,
	GK_10030 = 6,
	GK_10060 = 7,

	DPS_1010_V100 = 11,
	DPS_1020 = 12,
	DPS_1020_V100 = 13,

	DPS_1030V200_65 = 21,
	DPS_1030V200_450 = 22,
	DPS_1060V200_65 = 23,
	DPS_1060V200_450 = 24,
};

enum ScaleType2{
	ST_U = 0,
	ST_I = 1,
	ST_X = 2
};

struct LimitFloat2
{
	float fLower;
	float fUpper;
};

struct LimitData2
{
	LimitFloat2 LimitCurrentRange1;	// 0 - 150V
	LimitFloat2 LimitCurrentRange2;	// 0 - 300V
	LimitFloat2 LimitVoltageRange1;	// 0 - 150V
	LimitFloat2 LimitVoltageRange2;	// 0 - 300V
	LimitFloat2 LimitPower;
	LimitFloat2 LimitFrequency;
	LimitFloat2 LimitExternalCurrentFactor;
	
	// DPS1010M and DPS1030
	BOOL  bOvercurrentFoldBackEnable;
	BOOL  bExternalCurrentSamplingEnable;	// current external sample
	BOOL  bVoltageAutoAdjustEnable;			// voltage automatic regulation
	// DPS1030 only
	BOOL  bHarmonicEnable;					// harmonic analysis
	BOOL  bExternalVoltageSamplingEnable;	// voltage external sample
};

#define MEMORY1_2	 0
#define	MEMORY2_2	 1
#define	MEMORY3_2	 2
struct Parameter2
{
	// General
	int   iMemory;		// 0 - 2

	float fFrequence;
	float fFrequenceLow;
	float fFrequenceUpper;

	float fVoltage;
	float fVoltageLow;
	float fVoltageUpper;

	float fAlarmCurrent;
	float fAlarmPower;

	int   iRangeU;	

	// DPS1010M and DPS1030
	BOOL  bOvercurrentFoldBackEnable;
	BOOL  bExternalCurrentSamplingEnable;	// current external sample
	float fExternalCurrentFactor;			// external current factor
	BOOL  bVoltageAutoAdjustEnable;			// voltage automatic regulation

	// DPS1030 only
	BOOL  bHarmonicEnable;					// harmonic analysis
	BOOL  bExternalVoltageSamplingEnable;	// voltage external sample
};


struct RealTimeData2
{
	BYTE  ucState;	// Not used with DPS1030

	float fVoltageValue;
	float fCurrentValue;
	float fPowerFator;
	float fPower;

	// Only used by DPS1030
	float fFrequence;
	float fVoltageWaveRatio;
	float fCurrentWaveRatio;
	float fVolatgeWaveValue;
	float fCurrentWaveValue;
	float fVoltageHamonicLose;
	float fCurrentHamonicLose;
};


#endif // DPS_DEFINITION