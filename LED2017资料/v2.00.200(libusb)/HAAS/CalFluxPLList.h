// CalFluxPLList.h: interface for the CCalFluxPLList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALFLUXPLLIST_H__94A600A0_CE30_4BE7_9604_D85C33A7E7BB__INCLUDED_)
#define AFX_CALFLUXPLLIST_H__94A600A0_CE30_4BE7_9604_D85C33A7E7BB__INCLUDED_

#include "CalFluxPLData.h"
#include <afxtempl.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCalFluxPLList : public CObject  
{
public:
	CCalFluxPLList();
	virtual ~CCalFluxPLList();

	BOOL F_Load(CString strPathName);
	BOOL F_Save(CString strPathName);
	void Serialize(CArchive &ar);
	CTypedPtrArray<CObArray,CCalFluxPLData*> m_calData;

};

#endif // !defined(AFX_CALFLUXPLLIST_H__94A600A0_CE30_4BE7_9604_D85C33A7E7BB__INCLUDED_)
