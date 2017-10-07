#if !defined(AFX_PAGECURRVSL2_H__C17D69AE_A5B7_480E_94A7_D24E524848B8__INCLUDED_)
#define AFX_PAGECURRVSL2_H__C17D69AE_A5B7_480E_94A7_D24E524848B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageCurrVsL2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageCurrVsL2 dialog

class CPageCurrVsL2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageCurrVsL2)

// Construction
public:
	CPageCurrVsL2();
	~CPageCurrVsL2();

// Dialog Data
	//{{AFX_DATA(CPageCurrVsL2)
	enum { IDD = IDD_PAGE_CURR_VS_L_2 };
	CListCtrl	m_cList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageCurrVsL2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageCurrVsL2)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bFir;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGECURRVSL2_H__C17D69AE_A5B7_480E_94A7_D24E524848B8__INCLUDED_)
