#if !defined(AFX_OPTION2_H__9C14DC22_90FD_11DB_949D_00055D02EEF1__INCLUDED_)
#define AFX_OPTION2_H__9C14DC22_90FD_11DB_949D_00055D02EEF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Option2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COption2 dialog

class COption2 : public CPropertyPage
{
	DECLARE_DYNCREATE(COption2)

// Construction
public:
	COption2();
	~COption2();

// Dialog Data
	//{{AFX_DATA(COption2)
	enum { IDD = IDD_OPTION2 };
	CButton	m_cZW;
	BOOL	m_bInfo;
	BOOL	m_bHW;
	BOOL	m_bIp;
	BOOL	m_bLd;
	BOOL	m_bLp;
	BOOL	m_bNote;
	BOOL	m_bPH;
	BOOL	m_bPur;
	BOOL	m_bRa;
	BOOL	m_bRR;
	BOOL	m_bTc;
	BOOL	m_bUV;
	BOOL	m_bXY;
	BOOL	m_bIF;
	BOOL	m_bP;
	BOOL	m_bVF;
	BOOL	m_bLevel;
	BOOL	m_bWhite;
	BOOL	m_bZW;
	BOOL	m_bRO;
	BOOL	m_bPhoEff;
	BOOL	m_bPhSP;
	BOOL	m_bPrintPh_;
	BOOL	m_bdC;
	BOOL	m_bColorCorrectStr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COption2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COption2)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonPho();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTION2_H__9C14DC22_90FD_11DB_949D_00055D02EEF1__INCLUDED_)
