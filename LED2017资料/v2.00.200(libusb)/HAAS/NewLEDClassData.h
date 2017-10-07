// NewLEDClassData.h: interface for the CNewLEDClassData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEWLEDCLASSDATA_H__365D1336_8B6E_47AB_B0AF_E9CCC0BC3FA1__INCLUDED_)
#define AFX_NEWLEDCLASSDATA_H__365D1336_8B6E_47AB_B0AF_E9CCC0BC3FA1__INCLUDED_

#include "LimitData.h"  // for data Type

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNewLEDClassData : public CObject  
{
public:
	int GetClassParaNum();
	CNewLEDClassData& operator =(const CNewLEDClassData &xyData);
	void Copy(const CNewLEDClassData &xyData);
	void Serialize(CArchive &ar);

	CNewLEDClassData();
	CNewLEDClassData(const CNewLEDClassData &xyData);
	virtual ~CNewLEDClassData();

	CString m_strName;
	CArray<float,float> m_fLimit1;
	CArray<float,float> m_fLimit2;
	COLORREF m_color;
};

#endif // !defined(AFX_NEWLEDCLASSDATA_H__365D1336_8B6E_47AB_B0AF_E9CCC0BC3FA1__INCLUDED_)
