// CalFluxPLList.cpp: implementation of the CCalFluxPLList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "CalFluxPLList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCalFluxPLList::CCalFluxPLList()
{

}

CCalFluxPLList::~CCalFluxPLList()
{

}

void CCalFluxPLList::Serialize(CArchive &ar)
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
			CCalFluxPLData *temp=new CCalFluxPLData();
			temp->Serialize(ar);
			m_calData.Add(temp);
		}
	}
	
}

BOOL CCalFluxPLList::F_Save(CString strPathName)
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

BOOL CCalFluxPLList::F_Load(CString strPathName)
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
