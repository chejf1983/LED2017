// CalFluxList.h: interface for the CCalFluxList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALFLUXLIST_H__94A600A0_CE30_4BE7_9604_D85C33A7E7BB__INCLUDED_)
#define AFX_CALFLUXLIST_H__94A600A0_CE30_4BE7_9604_D85C33A7E7BB__INCLUDED_

#include "CalFluxData.h"
#include <afxtempl.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCalFluxList : public CObject  
{
public:
	CCalFluxList();
	virtual ~CCalFluxList();

	BOOL F_Load(CString strPathName);
	BOOL F_Save(CString strPathName);
	void Serialize(CArchive &ar);
	CTypedPtrArray<CObArray,CCalFluxData*> m_calData;

};

#endif // !defined(AFX_CALFLUXLIST_H__94A600A0_CE30_4BE7_9604_D85C33A7E7BB__INCLUDED_)
