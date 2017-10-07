#if !defined(AFX_DATAPAGE3_H__5A0716AF_7CCC_4602_804E_7635C3D8B133__INCLUDED_)
#define AFX_DATAPAGE3_H__5A0716AF_7CCC_4602_804E_7635C3D8B133__INCLUDED_

#include "DrawForMySpec.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataPage3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataPage3 dialog

class CDataPage3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CDataPage3)

// Construction
public:
	CSpectData *m_pSpData;
	void ReDraw();

	CDataPage3();
	~CDataPage3();

// Dialog Data
	//{{AFX_DATA(CDataPage3)
	enum { IDD = IDD_DATA_PAGE3 };
	CDrawForMySpec	m_cDraw;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDataPage3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDataPage3)
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

#endif // !defined(AFX_DATAPAGE3_H__5A0716AF_7CCC_4602_804E_7635C3D8B133__INCLUDED_)
