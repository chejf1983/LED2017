// AccreditData.cpp: implementation of the CAccreditData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AccreditData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAccreditData::CAccreditData()
{
	m_timeSetT1 = CTime::GetCurrentTime();
	m_timeSetT2 = CTime::GetCurrentTime();
}

CAccreditData::~CAccreditData()
{

}

void CAccreditData::ClearAllTime()
{
	m_time.RemoveAll();
}

void CAccreditData::Add(CTime time)
{
	m_time.Add(time);
}

BOOL CAccreditData::CanUse()
{
	int i;
	for(i = 0; i < m_time.GetSize(); i++)
	{
		if(m_time[i] < m_timeSetT1)
			return FALSE;

		if(m_time[i] > m_timeSetT2)
			return FALSE;
	}

	for(i = 0; i < m_time.GetSize() - 1; i++)
	{
		if(m_time[i] >= m_time[i + 1])
			return FALSE;
	}

	return TRUE;
}

void CAccreditData::SetTimeT12(CTime time1, CTime time2)
{
	m_timeSetT1 = time1;
	m_timeSetT2 = time2;
}

void CAccreditData::Serialize(CArchive &ar)
{
	int iVer;
	int iN;
	int i;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		iVer = 1;
		ar<< iVer;

		iN = m_time.GetSize();
		ar<< iN;

		ar<< m_timeSetT1;

		for(i = 0; i < iN; i++)
			ar<< m_time[i];

		ar<< m_timeSetT2;
	}
	else
	{
		ar>> iVer;
		if(iVer != 1)
			return;
		
		m_time.RemoveAll();
		ar>> iN;

		ar>> m_timeSetT1;
	
		for(i = 0; i < iN; i++)
		{
			CTime time;
			ar>> time;
			m_time.Add(time);
		}

		ar>> m_timeSetT2;
	}
}

BOOL CAccreditData::Open(CString strPathName)
{
	CFile oFile;
	if(!oFile.Open(strPathName,CFile::modeRead))
		return FALSE;
	
    CArchive ar(&oFile,CArchive::load);
	Serialize(ar);
	ar.Close();
	oFile.Close();
	return TRUE;
}

BOOL CAccreditData::Save(CString strPathName)
{
	CFile sFile;
	if(!sFile.Open(strPathName,CFile::modeCreate|CFile::modeReadWrite))
	{
		AfxMessageBox(strPathName);
		return FALSE;
	}
	CArchive ar(&sFile,CArchive::store);
	Serialize(ar);
	ar.Close();
	sFile.Close();
	return TRUE;
}

void CAccreditData::GetTimeT12(CTime &time1,CTime &time2)
{
	time1 = m_timeSetT1;
	time2 = m_timeSetT2;
	return;
}

void CAccreditData::Name2NewName(char szName[], char szNewName[])
{
	char szBuffer[256];
	int i;
	int iN = strlen(szName);
	for(i = 0; i < iN; i++)
	{
		sprintf(szBuffer, "%02d", szName[i] % 100);
		szNewName[2 * i + 0] = szBuffer[0];
		szNewName[2 * i + 1] = szBuffer[1];
	}

	szNewName[2 * iN] = 0x00;
	return;
}

int CAccreditData::GetTimeNum()
{
	return m_time.GetSize();
}

CString CAccreditData::GetTimeStr() const
{
	CString strTime;
	CString strTemp;
	for(int i = 0; i < m_time.GetSize(); i++)
	{
		strTemp = m_time[i].Format(_T("%Y-%m-%d %H:%M:%S"));
		strTime += strTemp + "\r\n";
	}

	return strTime;
}
