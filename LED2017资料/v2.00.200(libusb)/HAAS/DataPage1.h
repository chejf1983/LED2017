#if !defined(AFX_DATAPAGE1_H__4088660D_E1CD_4914_B579_5369836DA129__INCLUDED_)
#define AFX_DATAPAGE1_H__4088660D_E1CD_4914_B579_5369836DA129__INCLUDED_

#include "DrawForMySpec.h"
#include "SpectData.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataPage1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataPage1 dialog

class CDataPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CDataPage1)

// Construction
public:
	CSpectData m_pSpData;
	void ReDraw();
	CDataPage1();
	~CDataPage1();

// Dialog Data
	//{{AFX_DATA(CDataPage1)
	enum { IDD = IDD_DATA_PAGE1 };
	CDrawForMySpec	m_cSDCM;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDataPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDataPage1)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void SetPos();
	BOOL m_bFir;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAPAGE1_H__4088660D_E1CD_4914_B579_5369836DA129__INCLUDED_)
