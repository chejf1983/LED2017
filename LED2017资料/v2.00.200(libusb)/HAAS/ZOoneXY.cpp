// ZOoneXY.cpp: implementation of the CZOoneXY class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "ZOoneXY.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CZOoneXY::CZOoneXY()
{
	Init();
}

CZOoneXY::~CZOoneXY()
{

}

void CZOoneXY::Init()
{
	m_strName="NEW";
	m_fx.RemoveAll();
	m_fy.RemoveAll();
	return;
}

void CZOoneXY::Serialize(CArchive &ar)
{
	CString strVer;
	int i,iN;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		strVer="Zone A";
		ar<<strVer;

		ar<<m_strName;
		iN=m_fx.GetSize();
		ar<<iN;
		for(i=0;i<iN;i++)
		{
			ar<<m_fx[i];
			ar<<m_fy[i];
		}
	}
	else
	{
		ar>>strVer;
		if(strVer!="Zone A")
			return;
		ar>>m_strName;
		m_fx.RemoveAll();
		m_fy.RemoveAll();
		ar>>iN;
		for(i=0;i<iN;i++)
		{
			float f1,f2;
			ar>>f1;
			ar>>f2;
			m_fx.Add(f1);
			m_fy.Add(f2);
		}
	}
}

CZOoneXY& CZOoneXY::operator =(const CZOoneXY &xyData)
{
	Copy(xyData);
	return *this;
}

void CZOoneXY::Copy(const CZOoneXY &xyData)
{
	m_strName  = xyData.m_strName;
	
	m_fx.RemoveAll();
	m_fy.RemoveAll();

	int i,iN;
	iN=xyData.m_fx.GetSize();
	for(i=0;i<iN;i++)
	{
		m_fx.Add(xyData.m_fx[i]);
		m_fy.Add(xyData.m_fy[i]);
	}
}