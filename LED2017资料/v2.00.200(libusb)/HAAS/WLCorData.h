// WLCorData.h: interface for the CWLCorData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WLCORDATA_H__107335E1_9580_11DB_949D_00055D02EEF1__INCLUDED_)
#define AFX_WLCORDATA_H__107335E1_9580_11DB_949D_00055D02EEF1__INCLUDED_

#include <afxtempl.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWLCorData : public CObject  
{
public:
	void CalcCor(double fC[],int &iN,BOOL bShowErr=TRUE);
	void Sort();
	BOOL Save(CString strPathName,BOOL bShowErr=TRUE);
	BOOL Load(CString strPathName);
	void Add(float fStaWL,float fPix);
	int Delete(int iSele);
	//标准波长
	CArray<float,float> m_arra_fStaWL;
	//CCD像素点位置
	CArray<float,float> m_arra_fPix;
	//CCD像素个数一般为2048
	int  m_iPixN;

	CWLCorData();
	virtual ~CWLCorData();

};

#endif // !defined(AFX_WLCORDATA_H__107335E1_9580_11DB_949D_00055D02EEF1__INCLUDED_)
