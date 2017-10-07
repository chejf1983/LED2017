#if !defined(AFX_WYDLG_H__CE44A841_9A8A_11D8_A0D0_00055D02EEF1__INCLUDED_)
#define AFX_WYDLG_H__CE44A841_9A8A_11D8_A0D0_00055D02EEF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WYDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWYDlg dialog

class CWYDlg : public CDialog
{
// Construction
public:
	CString m_strAddr;
	BOOL m_bCancel;
	BOOL CheckLimit();
	int WY_SetPower(CString strCom,int iTypeWY,CString strAddr, int iSeleUI, float fSetVol, float fSetCurr, float &fVol, float &fCurr, CString &strVol, CString &strCurr);
	BOOL WY_Reset(CString strCom,int iTypeWY,CString strAddr);
	BOOL WY_GetPower(CString strCom,int iTypeWY,CString strAddr,float &fVol,float &fCurr,CString &strVol,CString &strCurr);
	BOOL GetRangeFile();
	CString m_strCurPath;
	//电压、电流量程范围
	float m_fVolR1;
	float m_fVolR2;
	float m_fCurrR1;
	float m_fCurrR2;
	CWYDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWYDlg)
	enum { IDD = IDD_WY_DIALOG };
	CStatic	m_cRange;
	CString	m_strCom;
	CString	m_strCurr;
	float	m_fSetCurr;
	float	m_fSetVol;
	CString	m_strVol;
	int		m_iSeleUI;
	int		m_iTypeWY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWYDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWYDlg)
	afx_msg void OnButtonGet();
	afx_msg void OnButtonSet();
	afx_msg void OnButtonReset();
	virtual void OnCancel();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WYDLG_H__CE44A841_9A8A_11D8_A0D0_00055D02EEF1__INCLUDED_)
