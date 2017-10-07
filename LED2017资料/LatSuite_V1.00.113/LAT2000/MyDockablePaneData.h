#pragma once

struct ElectricalData
{
	float fVoltageV;
	float fCurrentA;
	float fPowerW;

	BOOL bReadSuccessful;
	BOOL bAlarmVoltage;
	BOOL bAlarmCurrent;
	BOOL bAlarmPower;

	ElectricalData()
	{
		fVoltageV	= 0;
		fCurrentA	= 0;
		fPowerW		= 0;

		bReadSuccessful = FALSE;
		bAlarmCurrent	= FALSE;
		bAlarmPower		= FALSE;
		bAlarmVoltage	= FALSE;
	}
};

struct TemperatureData
{
    float m_fTMP,m_fTMPUp,m_fTMPDown,m_fTMPOpen;
    BOOL  m_bTMPReadSuccessful;
    BOOL  m_bTMPAlarm;
	int m_nAlarm;
    TemperatureData()
    {
        m_fTMP					= 0.0f;
        m_bTMPReadSuccessful	= FALSE;
        m_bTMPAlarm				= FALSE;
		m_fTMPUp				= 43.0f;
		m_fTMPDown				= 0.0f;
		m_fTMPOpen				= 40.0f;
    }
};

class CMyDockablePaneData
{
public:
	CMyDockablePaneData(void);
	~CMyDockablePaneData(void);

public:
    CArray<CString, CString> m_strSetTMP;
    CArray<CString, CString> m_strTemperatureControllerText;
    CArray<TemperatureData, TemperatureData&>m_TemperatureController;

    CArray<CString, CString>m_strRegionText;
    CArray<ElectricalData, ElectricalData&>m_dataRegion;
    //for AgeOutPutPower
    CArray<CString, CString> m_strOutPutVoltage;
    CArray<CString, CString> m_strOutPutFrequezy;
};

