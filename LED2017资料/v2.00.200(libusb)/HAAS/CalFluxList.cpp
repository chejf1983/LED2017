// CalFluxList.cpp: implementation of the CCalFluxList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "CalFluxList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCalFluxList::CCalFluxList()
{

}

CCalFluxList::~CCalFluxList()
{

}

void CCalFluxList::Serialize(CArchive &ar)
{
	CString strVer;
	int i,iN;
	if (ar.IsStoring())
	{
		strVer="CalFe_A";
		ar<<strVer;
		iN=m_calData.GetSize();
		ar<<iN;
		for(i=0;i<iN;i++)
			m_calData.GetAt(i)->Serialize(ar);
	}
	else
	{
		ar>>strVer;
		if(strVer!="CalFe_A")
			return;
		m_calData.RemoveAll();
		ar>>iN;
		for(i=0;i<iN;i++)
		{
			CCalFluxData *temp=new CCalFluxData();
			temp->Serialize(ar);
			m_calData.Add(temp);
		}
	}
	
}

BOOL CCalFluxList::F_Save(CString strPathName)
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

BOOL CCalFluxList::F_Load(CString strPathName)
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
