#if !defined(AFX_DEBUGLINE_H__04416398_8389_4C1C_8AE2_450BD6433713__INCLUDED_)
#define AFX_DEBUGLINE_H__04416398_8389_4C1C_8AE2_450BD6433713__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DebugLine.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDebugLine dialog

class CDebugLine : public CPropertyPage
{
	DECLARE_DYNCREATE(CDebugLine)

// Construction
public:
	CDebugLine();
	~CDebugLine();

// Dialog Data
	//{{AFX_DATA(CDebugLine)
	enum { IDD = IDD_DEBUG_LINE };
	CEdit	m_cData;
	int		m_iCroPix1;
	int		m_iCroPix2;
	int		m_iT1;
	int		m_iT2;
	int		m_iT3;
	int		m_iJsPix1;
	int		m_iJsPix2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDebugLine)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDebugLine)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEBUGLINE_H__04416398_8389_4C1C_8AE2_450BD6433713__INCLUDED_)
