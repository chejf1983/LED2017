#if !defined(AFX_SHOWLEVEL_H__2B80B454_7426_4615_9137_17C643064A78__INCLUDED_)
#define AFX_SHOWLEVEL_H__2B80B454_7426_4615_9137_17C643064A78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowLevel.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// ShowLevel dialog
#include "resFile\ReDrawListCtrl\ComboListCtrl.h"

class ShowLevel : public CDialog
{
// Construction
public:
	ShowLevel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ShowLevel)
	enum { IDD = IDD_showLevel };
	CEdit	m_temptest;
	CEdit	m_outboxnum;
	CEdit	m_outboxdetail;
	CEdit	m_tempcode;
	CEdit	m_codefromhardware;
	CEdit	m_boxfullnum;
	CListCtrl	m_feedingClowNum;
	CListCtrl	m_numInBox;
	CButton	m_stopclear;
	CButton	m_startclear;
	CComboListCtrl	m_binmaplist;
	CListCtrl	m_offsetlist;
	CComboListCtrl	m_levellist;
	//}}AFX_DATA

	bool InitBinMapList();
	bool SetBinMapList();
	bool updataBinMapList(int bin);

	bool initdlg();
	bool initoffsetlist();
	bool insertIteminit(CString text);

	bool InitExchangeParam();
	bool UpdataExchangeParam();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ShowLevel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ShowLevel)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnStartClear();
	afx_msg void OnStopClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWLEVEL_H__2B80B454_7426_4615_9137_17C643064A78__INCLUDED_)
