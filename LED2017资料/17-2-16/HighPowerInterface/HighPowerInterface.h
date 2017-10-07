// HighPowerInterface.h : main header file for the HIGHPOWERINTERFACE application
//

#if !defined(AFX_HIGHPOWERINTERFACE_H__B49404FE_9755_481A_AD6A_DA89F554E524__INCLUDED_)
#define AFX_HIGHPOWERINTERFACE_H__B49404FE_9755_481A_AD6A_DA89F554E524__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHighPowerInterfaceApp:
// See HighPowerInterface.cpp for the implementation of this class
//

class CHighPowerInterfaceApp : public CWinApp
{
public:
	CHighPowerInterfaceApp();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHighPowerInterfaceApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHighPowerInterfaceApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HIGHPOWERINTERFACE_H__B49404FE_9755_481A_AD6A_DA89F554E524__INCLUDED_)
