// CalFluxData.h: interface for the CCalFluxPLData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALFLUXPLDATA_H__16255191_19E2_47EA_BEC7_8A2594FFB9F4__INCLUDED_)
#define AFX_CALFLUXPLDATA_H__16255191_19E2_47EA_BEC7_8A2594FFB9F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCalFluxPLData : public CObject  
{
public:
	void Serialize(CArchive &ar);

	CString m_strDate;
	CString m_strName;
	float   m_fFlux;
	float   m_fK;		 //定标系数

	CCalFluxPLData();
	virtual ~CCalFluxPLData();

};

#endif // !defined(AFX_CALFLUXPLDATA_H__16255191_19E2_47EA_BEC7_8A2594FFB9F4__INCLUDED_)
