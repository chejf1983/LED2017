#pragma once
#include "LAT2000.h"
class CAlarmSettingsData
{
public:
	CAlarmSettingsData(void);
	~CAlarmSettingsData(void);

	BOOL Serialize(CArchive & ar);
	BOOL SaveFile(CString strPathName);
	BOOL LoadFile(CString strPathName);
    CAlarmSettingsData &operator = (const CAlarmSettingsData &data);
    void InitAlarmSettings();
public:
	BOOL m_bStopTest;
	
    CArray<float, float>m_fCurrentH;
    CArray<float, float>m_fCurrentL;

    CArray<float, float>m_fPowerH;
    CArray<float, float>m_fPowerL;

    CArray<float, float>m_fVoltageH;
    CArray<float, float>m_fVoltageL;
    CArray<BOOL, BOOL>m_bRegionAlarm;
    CArray<int, int>m_iRegionRingIndex;

    CArray<float, float>m_fTMPH;
    CArray<float, float>m_fTMPL;
	CArray<float, float>m_fTMPOPEN;
    CArray<BOOL, BOOL>m_bTMPAlarm;
    CArray<int, int>m_iTMPRingIndex;

	// Alarm ring index
	int m_iLampTooHighRingIndex;
	int m_iManualStopRingIndex;


    int m_iScanerOverTimeRingIndex;
	
	BOOL m_bLampTooHighAlarm;
	BOOL m_bManualStopAlarm;


    BOOL m_bScanerOverTimeAlarm;
};

