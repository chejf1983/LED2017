#include "StdAfx.h"
#include "AlarmSettingsData.h"
#include "LAT2000.h"

CAlarmSettingsData::CAlarmSettingsData(void)
{
	m_bStopTest = TRUE;
}

CAlarmSettingsData::~CAlarmSettingsData(void)
{
}

void CAlarmSettingsData::InitAlarmSettings()
{
    int i = 0;
    m_fCurrentH.SetSize(g_iGaugeNum);
    m_fCurrentL.SetSize(g_iGaugeNum);
    m_fPowerH.SetSize(g_iGaugeNum);
    m_fPowerL.SetSize(g_iGaugeNum);
    m_fVoltageH.SetSize(g_iGaugeNum);
    m_fVoltageL.SetSize(g_iGaugeNum);
    m_bRegionAlarm.SetSize(g_iGaugeNum);
    m_iRegionRingIndex.SetSize(g_iGaugeNum);
    for (i = 0; i < g_iGaugeNum; i ++)
    {
        m_fCurrentH[i]	= 0.00f;
        m_fCurrentL[i]	= 0.00f;

        m_fPowerH[i]	= 0.00f;
        m_fPowerL[i]	= 0.00f;

        m_fVoltageH[i]	= 0.00f;
        m_fVoltageL[i]	= 0.00f;

        m_bRegionAlarm[i]		= FALSE;
        m_iRegionRingIndex[i]	= -1;
    }

    m_fTMPH.SetSize(g_iTMPControlNum);
    m_fTMPL.SetSize(g_iTMPControlNum);
	m_fTMPOPEN.SetSize(g_iTMPControlNum);
    m_bTMPAlarm.SetSize(g_iTMPControlNum);
    m_iTMPRingIndex.SetSize(g_iTMPControlNum);
    for (i = 0; i < g_iTMPControlNum; i ++)
    {
        m_fTMPH[i] = 0.00f;
        m_fTMPL[i] = 0.00f;
		m_fTMPOPEN[i] = 0.00f;
        m_bTMPAlarm[i] = FALSE;
        m_iTMPRingIndex[i] = -1;
    }
}

BOOL CAlarmSettingsData::SaveFile(CString strPathName)
{
	CFile file;
	if (!file.Open(strPathName, CFile::modeWrite | CFile::modeCreate))
	{
		return FALSE;
	}

	CArchive ar(&file, CArchive::store);
	Serialize(ar);
	ar.Close();

	file.Close();
	return TRUE;
}


BOOL CAlarmSettingsData::LoadFile(CString strPathName)
{
	CFile file;
	if (!file.Open(strPathName, CFile::modeRead))
	{
		return FALSE;
	}

	CArchive ar(&file, CArchive::load);
	Serialize(ar);
	ar.Close();

	file.Close();
	return TRUE;
}


BOOL CAlarmSettingsData::Serialize(CArchive & ar)
{
    int iVer = 0;
    int i = 0;
	if (ar.IsStoring())
	{
        iVer = 102;
        ar<<iVer;
		ar<<m_bStopTest;
        ar<<m_bScanerOverTimeAlarm;
        ar<<m_iScanerOverTimeRingIndex;
		ar << g_iGaugeNum;
        for (i = 0; i < g_iGaugeNum; i ++)
            ar<<m_fCurrentH[i];
        for (i = 0; i < g_iGaugeNum; i ++)
            ar<<m_fCurrentL[i];
        for (i = 0; i < g_iGaugeNum; i ++)
            ar<<m_fPowerH[i];
        for (i = 0; i < g_iGaugeNum; i ++)
            ar<<m_fPowerL[i];	
        for (i = 0; i < g_iTMPControlNum; i ++)
            ar<<m_fTMPH[i];
        for (i = 0; i < g_iTMPControlNum; i ++)
            ar<<m_fTMPL[i];
		for (i = 0; i < g_iTMPControlNum; i ++)
            ar<<m_fTMPOPEN[i];

        for (i = 0; i < g_iGaugeNum; i ++)
            ar<<m_fVoltageH[i];

        for (i = 0; i < g_iGaugeNum; i ++)
            ar<<m_fVoltageL[i];

		// Alarm ring index
		ar<<m_iLampTooHighRingIndex;
		ar<<m_iManualStopRingIndex;

        for (i = 0; i < g_iTMPControlNum; i ++)
            ar<<m_iTMPRingIndex[i];
        for (i = 0; i < g_iGaugeNum; i ++)
            ar<<m_iRegionRingIndex[i];


		ar<<m_bLampTooHighAlarm;
		ar<<m_bManualStopAlarm;

        for (i = 0; i < g_iTMPControlNum; i ++)
            ar<<m_bTMPAlarm[i];
        for (i = 0; i < g_iGaugeNum; i ++)
            ar<<m_bRegionAlarm[i];
	}
	else
	{
        ar >> iVer;
        if (iVer == 100 || iVer == 101 || iVer == 102)
        {
            ar >> m_bStopTest;  
            ar >> m_bScanerOverTimeAlarm;
            ar >> m_iScanerOverTimeRingIndex; 
        }
        else
        {
            m_bStopTest = iVer;
        }
		int iTempGaugeNum;
		if (iVer == 102)
		{
			ar >> iTempGaugeNum;
		}
		else
		{
			iTempGaugeNum = 6;
		}
		
		float fTemp;	
		if(iTempGaugeNum >= g_iGaugeNum)
		{
			m_fCurrentH.RemoveAll();
			for (i = 0; i < g_iGaugeNum; i ++)
			{
				ar>>fTemp;
				m_fCurrentH.Add(fTemp);
			}
			for (i = 0; i < iTempGaugeNum - g_iGaugeNum; i ++)
			{
				ar>>fTemp;
			}

			m_fCurrentL.RemoveAll();
			for (i = 0; i < g_iGaugeNum; i ++)
			{
				ar >> fTemp;
				m_fCurrentL.Add(fTemp);
			}
			for (i = 0; i < iTempGaugeNum - g_iGaugeNum; i ++)
			{
				ar>>fTemp;
			}

			m_fPowerH.RemoveAll();
			for (i = 0; i < g_iGaugeNum; i ++)
			{
				ar >> fTemp;
				m_fPowerH.Add(fTemp);
			}
			for (i = 0; i < iTempGaugeNum - g_iGaugeNum; i ++)
			{
				ar>>fTemp;
			}

			m_fPowerL.RemoveAll();
			for (i = 0; i < g_iGaugeNum; i ++)
			{
				ar >> fTemp;
				m_fPowerL.Add(fTemp);
			}
			for (i = 0; i < iTempGaugeNum - g_iGaugeNum; i ++)
			{
				ar>>fTemp;
			}
		}
		else
		{
			m_fCurrentH.RemoveAll();
			for (i = 0; i < g_iGaugeNum; i ++)
			{
				if(i < iTempGaugeNum)
				{
					ar>>fTemp;
					m_fCurrentH.Add(fTemp);
				}
			}
			for (i = 0; i < g_iGaugeNum - iTempGaugeNum; i ++)
			{
				m_fCurrentH.Add(fTemp);
			}

			m_fCurrentL.RemoveAll();
			for (i = 0; i < g_iGaugeNum; i ++)
			{
				if(i < iTempGaugeNum)
				{
					ar >> fTemp;
					m_fCurrentL.Add(fTemp);
				}
			}
			for (i = 0; i < g_iGaugeNum - iTempGaugeNum; i ++)
			{
				m_fCurrentL.Add(fTemp);
			}

			m_fPowerH.RemoveAll();
			for (i = 0; i < g_iGaugeNum; i ++)
			{
				if(i < iTempGaugeNum)
				{
					ar >> fTemp;
					m_fPowerH.Add(fTemp);
				}
			}
			for (i = 0; i < g_iGaugeNum - iTempGaugeNum; i ++)
			{
				m_fPowerH.Add(fTemp);
			}

			m_fPowerL.RemoveAll();
			for (i = 0; i < g_iGaugeNum; i ++)
			{
				if(i < iTempGaugeNum)
				{
					ar >> fTemp;
					m_fPowerL.Add(fTemp);
				}
			}
			for (i = 0; i < g_iGaugeNum - iTempGaugeNum; i ++)
			{
				m_fPowerL.Add(fTemp);
			}
		}

		m_fTMPH.RemoveAll();
		for (i = 0; i < g_iTMPControlNum; i ++)
        {
			ar >> fTemp;
			m_fTMPH.Add(fTemp);
		}

		m_fTMPL.RemoveAll();
        for (i = 0; i < g_iTMPControlNum; i ++)
        {
			ar>>fTemp;
			m_fTMPL.Add(fTemp);
		}

		m_fTMPOPEN.RemoveAll();
        for (i = 0; i < g_iTMPControlNum; i ++)
        {
			ar>>fTemp;
			m_fTMPOPEN.Add(fTemp);
		}

		if(iTempGaugeNum >= g_iGaugeNum)
		{
			m_fVoltageH.RemoveAll();
			for (i = 0; i < g_iGaugeNum; i ++)
			{
				ar>>fTemp;
				m_fVoltageH.Add(fTemp);
			}
			for (i = 0; i < iTempGaugeNum - g_iGaugeNum; i ++)
			{
				ar>>fTemp;
			}

			m_fVoltageL.RemoveAll();
			for (i = 0; i < g_iGaugeNum; i ++)
			{
				ar>>fTemp;
				m_fVoltageL.Add(fTemp);
			}
			for (i = 0; i < iTempGaugeNum - g_iGaugeNum; i ++)
			{
				ar>>fTemp;
			}
		}
		else
		{
			m_fVoltageH.RemoveAll();
			for (i = 0; i < g_iGaugeNum; i ++)
			{
				if(i < iTempGaugeNum)
				{
					ar>>fTemp;
					m_fVoltageH.Add(fTemp);
				}
			}
			for (i = 0; i < g_iGaugeNum - iTempGaugeNum; i ++)
			{
				m_fVoltageH.Add(fTemp);
			}

			m_fVoltageL.RemoveAll();
			for (i = 0; i < g_iGaugeNum; i ++)
			{
				if(i < iTempGaugeNum)
				{
					ar>>fTemp;
					m_fVoltageL.Add(fTemp);
				}
			}
			for (i = 0; i < g_iGaugeNum - iTempGaugeNum; i ++)
			{
				m_fVoltageL.Add(fTemp);
			}
		}

        // Alarm ring index
        ar>>m_iLampTooHighRingIndex;
        ar>>m_iManualStopRingIndex;

		m_iTMPRingIndex.RemoveAll();
		int iTemp;
        for (i = 0; i < g_iTMPControlNum; i ++)
        {
			ar>>iTemp;
			m_iTMPRingIndex.Add(iTemp);
		}

		if(iTempGaugeNum >= g_iGaugeNum)
		{
			m_iRegionRingIndex.RemoveAll();
	        for (i = 0; i < g_iGaugeNum; i ++)
		    {
				ar>>iTemp;
				m_iRegionRingIndex.Add(iTemp);
			}
			for (i = 0; i < iTempGaugeNum - g_iGaugeNum; i ++)
			{
				ar>>iTemp;
			}
		}
		else
		{
			m_iRegionRingIndex.RemoveAll();
	        for (i = 0; i < g_iGaugeNum; i ++)
		    {
				if(i < iTempGaugeNum)
				{
					ar>>iTemp;
					m_iRegionRingIndex.Add(iTemp);
				}
			}
			for (i = 0; i < g_iGaugeNum - iTempGaugeNum; i ++)
			{
				m_iRegionRingIndex.Add(iTemp);
			}
		}


        ar>>m_bLampTooHighAlarm;
        ar>>m_bManualStopAlarm;

		m_bTMPAlarm.RemoveAll();
		BOOL bTemp;
        for (i = 0; i < g_iTMPControlNum; i ++)
        {
			ar>>bTemp;
			m_bTMPAlarm.Add(bTemp);
		}

		if(iTempGaugeNum >= g_iGaugeNum)
		{
			m_bRegionAlarm.RemoveAll();
			for (i = 0; i < g_iGaugeNum; i ++)
			{
				ar>>bTemp;
				m_bRegionAlarm.Add(bTemp);
			}
			for (i = 0; i < iTempGaugeNum - g_iGaugeNum; i ++)
			{
				ar>>bTemp;
			}
		}
		else
		{
			m_bRegionAlarm.RemoveAll();
	        for (i = 0; i < g_iGaugeNum; i ++)
		    {
				if(i < iTempGaugeNum)
				{
					ar>>bTemp;
					m_bRegionAlarm.Add(bTemp);
				}
			}
			for (i = 0; i < g_iGaugeNum - iTempGaugeNum; i ++)
			{
				m_bRegionAlarm.Add(bTemp);
			}
		}

		
        
	}

	return TRUE;
}

CAlarmSettingsData & CAlarmSettingsData::operator = (const CAlarmSettingsData &data)
{
    if (this == &data)
    {
        return *this;
    }
    int i;
    m_bStopTest = data.m_bStopTest;
    m_bScanerOverTimeAlarm = data.m_bScanerOverTimeAlarm;
    m_iScanerOverTimeRingIndex = data.m_iScanerOverTimeRingIndex;
    InitAlarmSettings();

	m_fCurrentH.RemoveAll();
	for (i = 0; i < g_iGaugeNum; i ++)
    {
		m_fCurrentH.Add(data.m_fCurrentH[i]);
	}

	m_fCurrentL.RemoveAll();
	for (i = 0; i < g_iGaugeNum; i ++)
    {
		m_fCurrentL.Add(data.m_fCurrentL[i]);
	}

	m_fPowerH.RemoveAll();
	for (i = 0; i < g_iGaugeNum; i ++)
	{
		m_fPowerH.Add(data.m_fPowerH[i]);
	}
    
	m_fPowerL.RemoveAll();
	for (i = 0; i < g_iGaugeNum; i ++)
	{
		m_fPowerL.Add(data.m_fPowerL[i]);
	}
    
	m_fTMPH.RemoveAll();
	for (i = 0; i < g_iTMPControlNum; i ++)
    {
		m_fTMPH.Add(data.m_fTMPH[i]);
	}
	
	m_fTMPL.RemoveAll();
    for (i = 0; i < g_iTMPControlNum; i ++)
	{
		m_fTMPL.Add(data.m_fTMPL[i]);
	}

	m_fTMPOPEN.RemoveAll();
    for (i = 0; i < g_iTMPControlNum; i ++)
	{
		m_fTMPOPEN.Add(data.m_fTMPOPEN[i]);
	}

	m_fVoltageH.RemoveAll();
    for (i = 0; i < g_iGaugeNum; i ++)
	{
		m_fVoltageH.Add(data.m_fVoltageH[i]);
	}
	m_fVoltageL.RemoveAll();
    for (i = 0; i < g_iGaugeNum; i ++)
		m_fVoltageL.Add(data.m_fVoltageL[i]);

    // Alarm ring index
    m_iLampTooHighRingIndex = data.m_iLampTooHighRingIndex;
    m_iManualStopRingIndex = data.m_iManualStopRingIndex;

	m_iTMPRingIndex.RemoveAll();
    for (i = 0; i < g_iTMPControlNum; i ++)
	{
		m_iTMPRingIndex.Add(data.m_iTMPRingIndex[i]);
	}
	m_iRegionRingIndex.RemoveAll();
    for (i = 0; i < g_iGaugeNum; i ++)
    {
		m_iRegionRingIndex.Add(data.m_iRegionRingIndex[i]);
	}


    m_bLampTooHighAlarm = data.m_bLampTooHighAlarm;
    m_bManualStopAlarm = data.m_bManualStopAlarm;
	
	m_bTMPAlarm.RemoveAll();
    for (i = 0; i < g_iTMPControlNum; i ++)
		m_bTMPAlarm.Add(data.m_bTMPAlarm[i]);
    
	m_bRegionAlarm.RemoveAll();
	for (i = 0; i < g_iGaugeNum; i ++)
		m_bRegionAlarm.Add(data.m_bRegionAlarm[i]);

    return *this;
}
