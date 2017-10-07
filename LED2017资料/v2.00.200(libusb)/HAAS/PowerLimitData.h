// PowerLimitData.h: interface for the CPowerLimitData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POWERLIMITDATA_H__3321E1E6_ED8E_4BB7_9B08_71C999F87AE0__INCLUDED_)
#define AFX_POWERLIMITDATA_H__3321E1E6_ED8E_4BB7_9B08_71C999F87AE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPowerLimitData  
{
public:
	void Init();
	void Serialize(CArchive& ar);
	void Copy(const CPowerLimitData &Data);
	CPowerLimitData& operator = (const CPowerLimitData &Data);
	
	BOOL Save(CString strPathName);
	BOOL Load(CString strPathName);
	
	CString m_strModel;
	BOOL	m_bCurr_In;
	BOOL	m_bPow_Out;
	BOOL	m_bPF_Out;
	BOOL	m_bVol_Out;
	float	m_fCurrIn1;
	float	m_fCurrIn2;
	float	m_fPowIn1;
	float	m_fPowIn2;
	float	m_fPFIn1;
	float	m_fPFIn2;
	float	m_fVolIn1;
	float	m_fVolIn2;
	CPowerLimitData();
	virtual ~CPowerLimitData();

};

#endif // !defined(AFX_POWERLIMITDATA_H__3321E1E6_ED8E_4BB7_9B08_71C999F87AE0__INCLUDED_)
