// CalFluxData.h: interface for the CCalFluxData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALFLUXDATA_H__16255191_19E2_47EA_BEC7_8A2594FFB9F4__INCLUDED_)
#define AFX_CALFLUXDATA_H__16255191_19E2_47EA_BEC7_8A2594FFB9F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCalFluxData : public CObject  
{
public:
	void Serialize(CArchive &ar);
	CString m_strDate;
	float	m_fCurr;
	CString m_strName;
	float   m_fFlux;
	float   m_fK;		 //����ϵ��
	float   m_fModeK;	 //���������ϵ��
	float   m_fSelfModeK;//������ϵ��

	CCalFluxData();
	virtual ~CCalFluxData();

};

#endif // !defined(AFX_CALFLUXDATA_H__16255191_19E2_47EA_BEC7_8A2594FFB9F4__INCLUDED_)
