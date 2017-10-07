// MusterData.h: interface for the CMusterData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUSTERDATA_H__A735D942_2F9C_11DC_B6B8_000D87C8DDE3__INCLUDED_)
#define AFX_MUSTERDATA_H__A735D942_2F9C_11DC_B6B8_000D87C8DDE3__INCLUDED_

#include "MusterType.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMusterData : public CObject  //保存的典型数据
{
public:
	BOOL OPEN(CString strPathName);
	BOOL SAVE(CString strPathName);
	void Serialize(CArchive &ar);
	CTypedPtrArray<CObArray,CMusterType*> m_listLamp;

	CMusterData();
	virtual ~CMusterData();

};

#endif // !defined(AFX_MUSTERDATA_H__A735D942_2F9C_11DC_B6B8_000D87C8DDE3__INCLUDED_)
