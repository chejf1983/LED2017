#include "StdAfx.h"
#include "AlarmRingData.h"


CAlarmRingData::CAlarmRingData(void)
{
	m_defaultRing.iRingNumber = 1;
	m_defaultRing.iRingONTimems = 1000;
	m_defaultRing.iRingOFFTimems = 0;
	m_defaultRing.strRingName = "Default";
}


CAlarmRingData::~CAlarmRingData(void)
{
}


int CAlarmRingData::GetRingCount()
{
	return m_ringData.GetCount();
}


void CAlarmRingData::RemoveAll()
{
	m_ringData.RemoveAll();
}


void CAlarmRingData::AddRing(RingData data)
{
	m_ringData.Add(data);
}


int CAlarmRingData::FindRing(CString strName)
{
	for (int i = 0; i < m_ringData.GetSize(); i++)
	{
		if (m_ringData[i].strRingName == strName)
		{
			return i;
		}
	}

	return -1;
}


BOOL CAlarmRingData::GetRingDataA(CString strName, RingData * pData)
{
	for (int i = 0; i < m_ringData.GetCount(); i++)
	{
		if (strName == m_ringData[i].strRingName)
		{
			pData = &m_ringData[i];
			return TRUE;
		}
	}

	return FALSE;
}


RingData & CAlarmRingData::GetRingData(int iIndex)
{
	if (iIndex >= 0 && iIndex < m_ringData.GetSize())
	{
		return m_ringData[iIndex];
	}
		
	return m_defaultRing;
}


BOOL CAlarmRingData::DeleteRingData(CString strName)
{
	for (int i = 0; i < m_ringData.GetCount(); i++)
	{
		if (strName == m_ringData[i].strRingName)
		{
			m_ringData.RemoveAt(i);
			return TRUE;
		}
	}

	return FALSE;
}


CString CAlarmRingData::GetRingInfoString(int iIndex)
{
	if (iIndex >= 0 && iIndex < m_ringData.GetSize())
	{
		CString strInfo;
		strInfo.Format("%d. %s (每隔%dms响%dms,共%d次)", 
			iIndex + 1,
			m_ringData[iIndex].strRingName,
			m_ringData[iIndex].iRingOFFTimems,
			m_ringData[iIndex].iRingONTimems,
			m_ringData[iIndex].iRingNumber);
		return strInfo;
	}

	return "";
}


CString CAlarmRingData::GetRingInfoString(CString strRingName)
{
	for (int i = 0; i < m_ringData.GetSize(); i++)
	{
		if (m_ringData[i].strRingName == strRingName)
		{
			CString strInfo;
			strInfo.Format("%d. %s (每隔%dms响%dms,共%d次)", 
				i + 1,
				m_ringData[i].strRingName,
				m_ringData[i].iRingOFFTimems,
				m_ringData[i].iRingONTimems,
				m_ringData[i].iRingNumber);
			return strInfo;
		}
	}

	return "";
}


BOOL CAlarmRingData::LoadFile(CString strPathName)
{
	CFile file;
	if (!file.Open(strPathName, CFile::modeRead))
	{
		return FALSE;
	}

	CArchive ar(&file, CArchive::load);
	Serialize(ar);

	return TRUE;
}


BOOL CAlarmRingData::SaveFile(CString strPathName)
{
	CFile file;
	if (!file.Open(strPathName, CFile::modeWrite | CFile::modeCreate))
	{
		return FALSE;
	}

	CArchive ar(&file, CArchive::store);
	Serialize(ar);

	return TRUE;
}


void CAlarmRingData::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{
		CString strEdition = "Alarm Ring Data V1.00";
		ar<<strEdition;

		int iSize = m_ringData.GetSize();
		ar<<iSize;
		for (int i = 0; i < iSize; i++)
		{
			ar<<m_ringData[i].strRingName;
			ar<<m_ringData[i].iRingNumber;
			ar<<m_ringData[i].iRingOFFTimems;
			ar<<m_ringData[i].iRingONTimems;
		}
	}
	else
	{
		CString strEdition;
		ar>>strEdition;
		if ("Alarm Ring Data V1.00" != strEdition)
		{
			AfxMessageBox("Alarm Ring Data Format Error!");
			return;
		}
		int iSize = 0;
		ar>>iSize;
		RingData data;
		m_ringData.RemoveAll();
		for (int i = 0; i < iSize; i++)
		{
			ar>>data.strRingName;
			ar>>data.iRingNumber;
			ar>>data.iRingOFFTimems;
			ar>>data.iRingONTimems;
			m_ringData.Add(data);
		}
	}
}