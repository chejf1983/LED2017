//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLGLEVEL_H__09AF6F01_3FDF_11DA_B322_000D87C8DDE3__INCLUDED_)
#define AFX_DLGLEVEL_H__09AF6F01_3FDF_11DA_B322_000D87C8DDE3__INCLUDED_

#include "LevelLimit.h"
#include "FullList.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLevel.h : header file
//

#define   ED_NONE    0
#define   ED_MOD     1

/////////////////////////////////////////////////////////////////////////////
// CDlgLevel dialog

class CDlgLevel : public CDialog
{
// Construction
public:
	CString m_strPathName;
	void GetData(int iN,float fTemp,CString &sTemp);
	void SetPos();
	void ListData();
	void SetList();
	void ReShow();
	CLevelLimit m_levelLimit;

	int m_iType;
	int m_iX,m_iY;
	int m_iSele12;

	CDlgLevel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLevel)
	enum { IDD = IDD_DIALOG_SET_LEVEL };
	CStatic	m_cS1;
	CButton	m_cOK;
	CEdit	m_cD;
	CMSFlexGrid	m_Grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLevel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLevel)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonMod();
	afx_msg void OnButtonDel();
	afx_msg void OnOpen();
	afx_msg void OnSave();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditD();
	afx_msg void OnDblClickMsflexgrid1();
	afx_msg void OnButtonSave();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLEVEL_H__09AF6F01_3FDF_11DA_B322_000D87C8DDE3__INCLUDED_)
