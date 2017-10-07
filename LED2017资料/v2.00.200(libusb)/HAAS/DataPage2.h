#if !defined(AFX_DATAPAGE2_H__709EDEF2_B31E_4068_A200_FD8692AAB6FB__INCLUDED_)
#define AFX_DATAPAGE2_H__709EDEF2_B31E_4068_A200_FD8692AAB6FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataPage2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataPage2 dialog

class CDataPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CDataPage2)

// Construction
public:
	BOOL m_bHaveData;
	float m_fx;
	float m_fy;
	float m_fCCT;

	CDataPage2();
	~CDataPage2();

// Dialog Data
	//{{AFX_DATA(CDataPage2)
	enum { IDD = IDD_DATA_PAGE2 };
	CStatic	m_cCIE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDataPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDataPage2)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bFir;
	void SetPos();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAPAGE2_H__709EDEF2_B31E_4068_A200_FD8692AAB6FB__INCLUDED_)
