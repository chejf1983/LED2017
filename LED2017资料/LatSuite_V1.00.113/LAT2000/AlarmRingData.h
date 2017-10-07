#pragma once

struct RingData
{
	CString strRingName;
	int iRingNumber;
	int iRingONTimems;
	int iRingOFFTimems;
	RingData()
	{
		strRingName = "Unnamed";
		iRingNumber = 1;
		iRingONTimems = 1000;
		iRingOFFTimems = 1000;
	}
};

class CAlarmRingData
{
public:
	CAlarmRingData(void);
	~CAlarmRingData(void);

	int GetRingCount();
	void RemoveAll();
	void AddRing(RingData data);
	int  FindRing(CString strName);
	BOOL GetRingDataA(CString strName, RingData * pData);
	RingData & GetRingData(int iIndex);
	BOOL DeleteRingData(CString strName);
	CString GetRingInfoString(CString strRingName);
	CString GetRingInfoString(int iIndex);

	void Serialize(CArchive & ar);
	BOOL LoadFile(CString strPathName);
	BOOL SaveFile(CString strPathName);

public:
	//int m_iLampTooHighRingIndex;
	//int m_iManualStopRingIndex;

	//int m_iTMP1RingIndex;
	//int m_iTMP2RingIndex;

	//int m_iRegion1RingIndex;
	//int m_iRegion2RingIndex;
	//int m_iRegion3RingIndex;
	//int m_iRegion4RingIndex;
	//int m_iRegion5RingIndex;
	//int m_iRegion6RingIndex;
	//
	//BOOL	m_bLampTooHighRingAlarm;
	//BOOL	m_bManualStopRingAlarm;
	//BOOL	m_bTMP1RingAlarm;
	//BOOL	m_bTMP2RingAlarm;
	//BOOL	m_bRegion1RingAlarm;
	//BOOL	m_bRegion2RingAlarm;
	//BOOL	m_bRegion3RingAlarm;
	//BOOL	m_bRegion4RingAlarm;
	//BOOL	m_bRegion5RingAlarm;
	//BOOL	m_bRegion6RingAlarm;

	
private:
	CArray<RingData, RingData> m_ringData;
	RingData m_defaultRing;
};

