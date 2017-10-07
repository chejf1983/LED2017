#if !defined(AFX_DLGSELFKEDIT_H__946CFD6A_AE40_4E3D_8E94_A7AEE3E05D5C__INCLUDED_)
#define AFX_DLGSELFKEDIT_H__946CFD6A_AE40_4E3D_8E94_A7AEE3E05D5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSelfKEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSelfKEdit dialog

class CDlgSelfKEdit : public CDialog
{
// Construction
public:
	void Serialize(CArchive &ar);
	BOOL Load();
	BOOL Save();
	void ReLIst();
	CDlgSelfKEdit(CWnd* pParent = NULL);   // standard constructor

	int m_iSele;
	CArray<float, float> m_fListK;
	CArray<CString, CString> m_strListName;

// Dialog Data
	//{{AFX_DATA(CDlgSelfKEdit)
	enum { IDD = IDD_SELF_K_EDIT };
	CComboBox	m_cSele;
	float	m_fK;
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSelfKEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSelfKEdit)
	afx_msg void OnButtonMod();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeComboSele();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSELFKEDIT_H__946CFD6A_AE40_4E3D_8E94_A7AEE3E05D5C__INCLUDED_)
