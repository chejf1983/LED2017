// MySpec.h : main header file for the MYSPEC application
//

#if !defined(AFX_MYSPEC_H__799E0384_8CF0_11DB_949D_00055D02EEF1__INCLUDED_)
#define AFX_MYSPEC_H__799E0384_8CF0_11DB_949D_00055D02EEF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMySpecApp:
// See MySpec.cpp for the implementation of this class
//

class CMySpecApp : public CWinApp
{
public:
	BOOL DoEXE(CString strPathName);
	BOOL m_bHaveChange;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CMySpecApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySpecApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMySpecApp)
	afx_msg void OnAppAbout();
	afx_msg void OnChinese();
	afx_msg void OnUpdateChinese(CCmdUI* pCmdUI);
	afx_msg void OnEnglish();
	afx_msg void OnUpdateEnglish(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HINSTANCE m_hLangDLL;
	void SetLang(BOOL bEnglish);
	void GetLang(BOOL &bEnglish);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSPEC_H__799E0384_8CF0_11DB_949D_00055D02EEF1__INCLUDED_)
