// HighPowerInterface.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "HighPowerInterface.h"
#include "HighPowerInterfaceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHighPowerInterfaceApp

BEGIN_MESSAGE_MAP(CHighPowerInterfaceApp, CWinApp)
	//{{AFX_MSG_MAP(CHighPowerInterfaceApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHighPowerInterfaceApp construction

CHighPowerInterfaceApp::CHighPowerInterfaceApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHighPowerInterfaceApp object

CHighPowerInterfaceApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHighPowerInterfaceApp initialization

BOOL CHighPowerInterfaceApp::InitInstance()
{
	HANDLE hMutex = CreateMutex(NULL, false, "分光软件");
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CWnd* cwnd = CWnd::FindWindow(NULL, "新圣芯分光分色软件");
		if(cwnd)
		{
			cwnd->ShowWindow(SW_SHOW);
			cwnd->SetForegroundWindow();
		}
		return false;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CHighPowerInterfaceDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
