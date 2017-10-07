// SelfCorrectData.cpp: implementation of the CSelfCorrectData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "SelfCorrectData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSelfCorrectData::CSelfCorrectData()
{
	m_iType = 0;
	
	m_iSaveTestNum = 0;
	
	m_iSaveRefNum = 0;
}

CSelfCorrectData::~CSelfCorrectData()
{

}

void CSelfCorrectData::Serialize(CArchive &ar)
{
	int i;
	CString strVer;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		strVer ="CSelfCorrectData_A";
		ar<<strVer;
		
		ar<< m_iType;
		
		ar<<m_iSaveTestNum;
		for(i = 0; i < m_iSaveTestNum; i++)
		{
			ar<<m_fSave_TestWL[i];
			ar<<m_fSave_TestPL[i];
		}

		ar<<m_iSaveRefNum;
		for(i = 0; i < m_iSaveRefNum; i++)
		{
			ar<<m_fSave_RefWL[i];
			ar<<m_fSave_RefPL[i];
		}
	}
	else
	{
		// TODO: add loading code here
		ar>>strVer;
		if(strVer!="CSelfCorrectData_A")
			return;

		ar>> m_iType;
		
		ar>>m_iSaveTestNum;
		for(i = 0; i < m_iSaveTestNum; i++)
		{
			ar>>m_fSave_TestWL[i];
			ar>>m_fSave_TestPL[i];
		}
		
		ar>>m_iSaveRefNum;
		for(i = 0; i < m_iSaveRefNum; i++)
		{
			ar>>m_fSave_RefWL[i];
			ar>>m_fSave_RefPL[i];
		}
	}
}

BOOL CSelfCorrectData::Open(CString strPathName)
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

BOOL CSelfCorrectData::Save(CString strPathName)
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
