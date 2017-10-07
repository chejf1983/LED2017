// CalFluxPLData.cpp: implementation of the CCalFluxPLData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "CalFluxPLData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCalFluxPLData::CCalFluxPLData()
{

}

CCalFluxPLData::~CCalFluxPLData()
{

}

void CCalFluxPLData::Serialize(CArchive &ar)
{
	CString strVer;
	if (ar.IsStoring())
	{
		strVer="PL_CAL_A";
		ar<<strVer;

		ar<<m_strDate;

		ar<<m_strName;
		ar<<m_fFlux;
		ar<<m_fK;
	}
	else
	{
		ar>>strVer;
		if(strVer!="PL_CAL_A")
			return;
		ar>>m_strDate;

		ar>>m_strName;
		ar>>m_fFlux;
		ar>>m_fK;
	}
}
