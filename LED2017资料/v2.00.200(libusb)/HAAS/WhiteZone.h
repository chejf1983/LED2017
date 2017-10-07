// WhiteZone.h: interface for the CWhiteZone class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WHITEZONE_H__D65FFDE3_550A_11DA_ABAD_00055D02EEF1__INCLUDED_)
#define AFX_WHITEZONE_H__D65FFDE3_550A_11DA_ABAD_00055D02EEF1__INCLUDED_

#include "ZOoneXY.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWhiteZone : public CObject  
{
public:
	CArray<float,float> m_arra_fx;
	CArray<float,float> m_arra_fy;

	BOOL  m_bMouse;
	CPoint m_xyPoint;

	float m_fX;
	float m_fY;
	CString IN_ZONE(float fx,float fy);
	BOOL XY_CheckPoyIN(CArray<float,float> &x,CArray<float,float> &y,float fx,float fy,int MAX_X);
	void Draw(CDC *pDC,CRect dRect ,int iSele,BOOL bPrint,int iType);
	void Serialize(CArchive &ar);
	BOOL WZ_Save(CString strPathName);
	BOOL WZ_Load(CString strPathName);
	//
	CTypedPtrArray<CObArray,CZOoneXY*>  m_arraXY;

	CWhiteZone();
	virtual ~CWhiteZone();

};

#endif // !defined(AFX_WHITEZONE_H__D65FFDE3_550A_11DA_ABAD_00055D02EEF1__INCLUDED_)
