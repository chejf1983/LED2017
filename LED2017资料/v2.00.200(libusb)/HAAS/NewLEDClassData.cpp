// NewLEDClassData.cpp: implementation of the CNewLEDClassData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "NewLEDClassData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNewLEDClassData::CNewLEDClassData()
{
	m_color = RGB(0, 0, 255);
	m_strName = "New";

	m_fLimit1.RemoveAll();
	m_fLimit2.RemoveAll();
}

CNewLEDClassData::CNewLEDClassData(const CNewLEDClassData &xyData)
{
	Copy(xyData);
}

CNewLEDClassData::~CNewLEDClassData()
{

}

CNewLEDClassData& CNewLEDClassData::operator =(const CNewLEDClassData &xyData)
{
	if(this == &xyData)
		return *this;

	Copy(xyData);

	return *this;
}

void CNewLEDClassData::Copy(const CNewLEDClassData &xyData)
{
	m_strName = xyData.m_strName;

	m_color = xyData.m_color;
	m_fLimit1.Copy(xyData.m_fLimit1);
	m_fLimit2.Copy(xyData.m_fLimit2);
}

void CNewLEDClassData::Serialize(CArchive &ar)
{
	CString strVer;
	int iN,i;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		strVer="NewLED_B";
		ar<<strVer;
		
		ar<<m_strName;

		iN = m_fLimit1.GetSize();
		ar<<iN;
		for(i = 0; i < iN; i++)
		{
			ar<<m_fLimit1[i];
			ar<<m_fLimit2[i];
		}

		ar<<m_color;
	}
	else
	{
		ar>>strVer;
		if(strVer!="NewLED_A" && strVer!="NewLED_B")
			return;
		ar>>m_strName;
		
		ar>>iN;
		m_fLimit1.RemoveAll();
		m_fLimit2.RemoveAll();

		for(i = 0; i < iN; i++)
		{
			float f1,f2;
			ar>>f1;
			ar>>f2;

			m_fLimit1.Add(f1);
			m_fLimit2.Add(f2);
		}

		if(strVer == "NewLED_A")
		{

		}
		else
			ar>>m_color;
	}
}

//
// 分类参数个数
//
int CNewLEDClassData::GetClassParaNum()
{
	return m_fLimit1.GetSize();
}
