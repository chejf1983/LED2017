#if !defined(AFX_DATAPAGE4_H__CFA1DEE3_B97F_4B61_AC00_AD855E6FD662__INCLUDED_)
#define AFX_DATAPAGE4_H__CFA1DEE3_B97F_4B61_AC00_AD855E6FD662__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataPage4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataPage4 dialog

class CDataPage4 : public CPropertyPage
{
	DECLARE_DYNCREATE(CDataPage4)

// Construction
public:
	BOOL m_bHaveData;
	float m_fu;
	float m_fv;
	float m_fCCT;

	CDataPage4();
	~CDataPage4();

// Dialog Data
	//{{AFX_DATA(CDataPage4)
	enum { IDD = IDD_DATA_PAGE4 };
	CStatic	m_cCIE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDataPage4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDataPage4)
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

#endif // !defined(AFX_DATAPAGE4_H__CFA1DEE3_B97F_4B61_AC00_AD855E6FD662__INCLUDED_)
