// MusterType.cpp: implementation of the CMusterType class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "MusterType.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMusterType::CMusterType()
{
	Init();
}

CMusterType::~CMusterType()
{

}

void CMusterType::Init()
{
	m_strName="NEW";
	m_fRefS.RemoveAll();
	m_fRefQ.RemoveAll();
	return;
}

void CMusterType::Serialize(CArchive &ar)
{
	CString strVer;
	int i,iN;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		strVer="Muster Type";
		ar<<strVer;

		ar<<m_strName;
		iN=m_fRefS.GetSize();
		ar<<iN;
		for(i=0;i<iN;i++)
		{
			ar<<m_fRefS[i];
			ar<<m_fRefQ[i];
		}
	}
	else
	{
		ar>>strVer;
		if(strVer!="Muster Type")
			return;
		ar>>m_strName;
		m_fRefS.RemoveAll();
		m_fRefQ.RemoveAll();
		ar>>iN;
		for(i=0;i<iN;i++)
		{
			float f1,f2;
			ar>>f1;
			ar>>f2;
			m_fRefS.Add(f1);
			m_fRefQ.Add(f2);
		}
	}
}

CMusterType& CMusterType::operator =(const CMusterType &MtData)
{
	Copy(MtData);
	return *this;
}

void CMusterType::Copy(const CMusterType &MtData)
{
	m_strName  = MtData.m_strName;
	
	m_fRefS.RemoveAll();
	m_fRefQ.RemoveAll();

	int i,iN;
	iN=MtData.m_fRefS.GetSize();
	for(i=0;i<iN;i++)
	{
		m_fRefS.Add(MtData.m_fRefS[i]);
		m_fRefQ.Add(MtData.m_fRefQ[i]);
	}
}
