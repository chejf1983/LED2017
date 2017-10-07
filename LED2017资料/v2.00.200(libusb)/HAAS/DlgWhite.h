//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLGWHITE_H__D65FFDE1_550A_11DA_ABAD_00055D02EEF1__INCLUDED_)
#define AFX_DLGWHITE_H__D65FFDE1_550A_11DA_ABAD_00055D02EEF1__INCLUDED_

#include "DrawForMySpec.h"
#include "WhiteZone.h"
#include "Label.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWhite.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWhite dialog

class CDlgWhite : public CDialog
{
// Construction
public:
	CString m_strPathName;

	void ReDraw();
	int  m_iX;
	int  m_iY;
	int  m_iSele12;
	int  m_iSeleName;
	int  m_iSeleXY;
	void ReGridXY();
	void ReGridName();
	CWhiteZone m_xyZone;

	CDlgWhite(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWhite)
	enum { IDD = IDD_WHITE };
	CLabel	m_cEV;
	CEdit	m_cName;
	CEdit	m_cD;
	CDrawForMySpec	m_cDraw;
	CMSFlexGrid	m_cGridName;
	CMSFlexGrid	m_cGridLevel;
	float	m_fX;
	float	m_fY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWhite)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWhite)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnWSave();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDel();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickMsflexgrid1();
	afx_msg void OnButtonAdd2();
	afx_msg void OnButtonDel2();
	afx_msg void OnClickMsflexgrid2();
	afx_msg void OnChangeEditName();
	afx_msg void OnChangeEditD();
	afx_msg void OnButtonCheck();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnWOpen();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWHITE_H__D65FFDE1_550A_11DA_ABAD_00055D02EEF1__INCLUDED_)
