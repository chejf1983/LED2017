// FluxLampSelfCalData.cpp: implementation of the CFluxLampSelfCalData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "FluxLampSelfCalData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFluxLampSelfCalData::CFluxLampSelfCalData()
{
	m_strRemarks = "";
	m_fStaFlux = 100;
	m_fTestFlux = 100;
	m_fCalK = 1;
	m_strDate = "";
}

CFluxLampSelfCalData::~CFluxLampSelfCalData()
{

}

void CFluxLampSelfCalData::Serialize(CArchive &ar)
{
	CString strVer;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		strVer ="FluxLampSelfCalData_A";
		ar<<strVer;

		ar<< m_strRemarks;
		ar<< m_fStaFlux;
		ar<< m_fTestFlux;
		ar<< m_fCalK;
		ar<< m_strDate;
	}
	else
	{
		// TODO: add loading code here
		ar>>strVer;
		if(strVer!="FluxLampSelfCalData_A")
			return;

		ar>> m_strRemarks;
		ar>> m_fStaFlux;
		ar>> m_fTestFlux;
		ar>> m_fCalK;
		ar>> m_strDate;
	}
}

BOOL CFluxLampSelfCalData::Open(CString strPathName)
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

BOOL CFluxLampSelfCalData::Save(CString strPathName)
{
	CFile sFile;
	if(!sFile.Open(strPathName,CFile::modeCreate|CFile::modeReadWrite))
		return FALSE;
	CArchive ar(&sFile,CArchive::store);
	Serialize(ar);
	ar.Close();
	sFile.Close();
	return TRUE;
}
