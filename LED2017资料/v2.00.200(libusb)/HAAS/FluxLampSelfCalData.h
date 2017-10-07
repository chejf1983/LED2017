// FluxLampSelfCalData.h: interface for the CFluxLampSelfCalData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLUXLAMPSELFCALDATA_H__8AEB551A_660B_4686_97FD_C5974C9B150A__INCLUDED_)
#define AFX_FLUXLAMPSELFCALDATA_H__8AEB551A_660B_4686_97FD_C5974C9B150A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFluxLampSelfCalData : public CObject  
{
public:
	CFluxLampSelfCalData();
	virtual ~CFluxLampSelfCalData();

public:
	BOOL Save(CString strPathName);
	BOOL Open(CString strPathName);

	void Serialize(CArchive &ar);
	CString m_strRemarks;
	float m_fStaFlux;
	float m_fTestFlux;
	float m_fCalK;
	CString m_strDate;
};

#endif // !defined(AFX_FLUXLAMPSELFCALDATA_H__8AEB551A_660B_4686_97FD_C5974C9B150A__INCLUDED_)
