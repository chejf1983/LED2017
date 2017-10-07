#if !defined(AFX_DLGEXPORTLAMP_H__89BF8A48_6C7A_4D88_A485_AA38FA3D65A4__INCLUDED_)
#define AFX_DLGEXPORTLAMP_H__89BF8A48_6C7A_4D88_A485_AA38FA3D65A4__INCLUDED_

#include "SpectData.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgExportLamp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgExportLamp dialog

class CDlgExportLamp : public CDialog
{
// Construction
public:
	CSpectData m_spData;
	CDlgExportLamp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgExportLamp)
	enum { IDD = IDD_DIALOG_EXPORT_LAMP };
	CString	m_strCurr;
	float	m_fPH;
	CString	m_strModel;
	CString	m_strSN;
	CString	m_strUnit;
	CString	m_strVol;
	int		m_iInterval;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgExportLamp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgExportLamp)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEXPORTLAMP_H__89BF8A48_6C7A_4D88_A485_AA38FA3D65A4__INCLUDED_)
