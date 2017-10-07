// MusterData.cpp: implementation of the CMusterData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "MusterData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMusterData::CMusterData()
{

}

CMusterData::~CMusterData()
{

}


void CMusterData::Serialize(CArchive &ar)
{
	CString strVer;
	int iN,i;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		strVer="Muster Dara";
		ar<<strVer;
		iN=m_listLamp.GetSize();
		ar<<iN;
		for(i=0;i<iN;i++)
			m_listLamp[i]->Serialize(ar);
	}
	else
	{
		ar>>strVer;
		if(strVer!="Muster Dara")
			return;
		m_listLamp.RemoveAll();
		ar>>iN;
		for(i=0;i<iN;i++)
		{
			CMusterType *temp=new CMusterType();
			temp->Serialize(ar);
			m_listLamp.Add(temp);
		}
	}
}

BOOL CMusterData::SAVE(CString strPathName)
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

BOOL CMusterData::OPEN(CString strPathName)
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
