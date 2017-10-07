// GCSDemo.h : main header file for the GCSDEMO application
//

#if !defined(AFX_GCSDEMO_H__A397BCBA_E9EE_4CBA_8BDE_54B9A907A088__INCLUDED_)
#define AFX_GCSDEMO_H__A397BCBA_E9EE_4CBA_8BDE_54B9A907A088__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGCSDemoApp:
// See GCSDemo.cpp for the implementation of this class
//

class CGCSDemoApp : public CWinApp
{
public:
	CGCSDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGCSDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGCSDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GCSDEMO_H__A397BCBA_E9EE_4CBA_8BDE_54B9A907A088__INCLUDED_)
