#if !defined(AFX_PAGECURRVST2_H__E52747F8_365D_4802_8982_D6BAFCA75241__INCLUDED_)
#define AFX_PAGECURRVST2_H__E52747F8_365D_4802_8982_D6BAFCA75241__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageCurrVsT2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageCurrVsT2 dialog

class CPageCurrVsT2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageCurrVsT2)

// Construction
public:
	CPageCurrVsT2();
	~CPageCurrVsT2();

// Dialog Data
	//{{AFX_DATA(CPageCurrVsT2)
	enum { IDD = IDD_PAGE_CURR_VS_T2 };
	CListCtrl	m_cList;
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageCurrVsT2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageCurrVsT2)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bFir;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGECURRVST2_H__E52747F8_365D_4802_8982_D6BAFCA75241__INCLUDED_)
