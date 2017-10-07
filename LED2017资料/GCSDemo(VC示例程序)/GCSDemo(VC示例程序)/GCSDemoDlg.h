// GCSDemoDlg.h : header file
//
//{{AFX_INCLUDES()
#include "ntgraph.h"
//}}AFX_INCLUDES

#if !defined(AFX_GCSDEMODLG_H__A456B495_2D74_49F2_9427_CF06A2E53FAD__INCLUDED_)
#define AFX_GCSDEMODLG_H__A456B495_2D74_49F2_9427_CF06A2E53FAD__INCLUDED_

#include "SpectraArsenalEmissionAPI.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGCSDemoDlg dialog

class CGCSDemoDlg : public CDialog
{
// Construction
public:
	BOOL m_bStop;
	BOOL m_bGetData;
	void ReDraw(COLOR_PARA &dPara);
	CGCSDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGCSDemoDlg)
	enum { IDD = IDD_GCSDEMO_DIALOG };
	CButton	m_cTestL;
	CButton	m_cStop;
	CEdit	m_cData;
	float	m_fIntTime;
	int		m_iAveNum;
	float	m_fCCT;
	float	m_fFlux;
	int		m_iFilterBW;
	CNTGraph	m_cSpectrum;
	BOOL	m_bUseTrig;
	int		m_iTrigMode;
	int		m_iPerIntTime;
	int		m_iMaxIntTime;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGCSDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGCSDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonInit();
	afx_msg void OnButtonInitDark();
	afx_msg void OnButtonInitTest();
	afx_msg void OnButtonCalc();
	afx_msg void OnButtonInit2();
	afx_msg void OnButtonAuto();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	static UINT ThreadGetAsynData(LPVOID pPar);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GCSDEMODLG_H__A456B495_2D74_49F2_9427_CF06A2E53FAD__INCLUDED_)
