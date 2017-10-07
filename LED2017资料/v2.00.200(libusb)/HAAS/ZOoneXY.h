// ZOoneXY.h: interface for the CZOoneXY class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZOONEXY_H__D65FFDE4_550A_11DA_ABAD_00055D02EEF1__INCLUDED_)
#define AFX_ZOONEXY_H__D65FFDE4_550A_11DA_ABAD_00055D02EEF1__INCLUDED_

#include "afxtempl.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CZOoneXY : public CObject  
{
public:
	CZOoneXY& operator =(const CZOoneXY &xyData);
	void Copy(const CZOoneXY &xyData);
	void Serialize(CArchive &ar);
	void Init();
	CString m_strName;
	CArray<float,float> m_fx;
	CArray<float,float> m_fy;
	CZOoneXY();
	virtual ~CZOoneXY();

};

#endif // !defined(AFX_ZOONEXY_H__D65FFDE4_550A_11DA_ABAD_00055D02EEF1__INCLUDED_)
