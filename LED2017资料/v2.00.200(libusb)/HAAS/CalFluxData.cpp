// CalFluxData.cpp: implementation of the CCalFluxData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "CalFluxData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCalFluxData::CCalFluxData()
{

}

CCalFluxData::~CCalFluxData()
{

}

void CCalFluxData::Serialize(CArchive &ar)
{
	CString strVer;
	if (ar.IsStoring())
	{
		strVer="CAL_B";
		ar<<strVer;
		ar<<m_strDate;
		ar<<m_fCurr;
		ar<<m_strName;
		ar<<m_fFlux;
		ar<<m_fK;
		ar<<m_fModeK;
		ar<<m_fSelfModeK;
	}
	else
	{
		ar>>strVer;
		if(strVer!="CAL_A"&&strVer!="CAL_B")
			return;
		ar>>m_strDate;
		ar>>m_fCurr;
		ar>>m_strName;
		ar>>m_fFlux;
		ar>>m_fK;
		if(strVer!="CAL_A")
		{
			ar>>m_fModeK;
			ar>>m_fSelfModeK;
		}
		else
		{
			m_fModeK=1.0f;
			m_fSelfModeK=1.0f;
		}
	}
}
