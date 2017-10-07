// MySpec.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MySpec.h"

#include "MainFrm.h"
#include "MySpecDoc.h"
#include "MySpecView.h"
#include "Splash.h"
#include "label.h"
#include "SPEC_PRO.h"
#include "About_def.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySpecApp
extern CCSPEC_PRO g_SPEC;
extern HWND     g_FrameWnd;
extern int g_iSeleMode;
extern BOOL g_bTest;

BEGIN_MESSAGE_MAP(CMySpecApp, CWinApp)
	//{{AFX_MSG_MAP(CMySpecApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_CHINESE, OnChinese)
	ON_UPDATE_COMMAND_UI(ID_CHINESE, OnUpdateChinese)
	ON_COMMAND(ID_ENGLISH, OnEnglish)
	ON_UPDATE_COMMAND_UI(ID_ENGLISH, OnUpdateEnglish)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySpecApp construction
BOOL g_bEnglish;
CString g_strCurPath;
CString g_strDriverVer;

CMySpecApp::CMySpecApp()
{
	g_bEnglish=FALSE;

	char Path[256];
	GetModuleFileName(NULL,Path,250);   
	* ( strrchr( Path, '\\' ) + 1 ) = '\0';	
	g_strCurPath=Path;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMySpecApp object

CMySpecApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMySpecApp initialization

BOOL CMySpecApp::InitInstance()
{
	if(1)
	{
		CString strSection	= "Reg2";
		CString strFlag		= "Flag";
		int iFlag = AfxGetApp()->GetProfileInt(strSection, strFlag, 1234);
		if(iFlag == 1234)
		{
			SetCurrentDirectory(g_strCurPath + "Controls\\Iocomp\\");	
			DoEXE("RegIocomp.bat");
			
			AfxGetApp()->WriteProfileInt(strSection, strFlag, 0);
		}
	}
	/////////////////////////////////////////////
	HINSTANCE hocx=::LoadLibrary(_T("Controls\\NTGraph.ocx.ocx"));
	if(hocx!=NULL)
	{
		FARPROC lpfn=::GetProcAddress(hocx,_T("DllRegisterServer"));
		if(lpfn!=NULL)
			(*lpfn)();
		::FreeLibrary(hocx);
	}
	//////////////////////////////////////////////

	/////////////////////////////////////////////
	 hocx=::LoadLibrary(_T("Controls\\msflxgrd.ocx"));
	if(hocx!=NULL)
	{
		FARPROC lpfn=::GetProcAddress(hocx,_T("DllRegisterServer"));
		if(lpfn!=NULL)
			(*lpfn)();
		::FreeLibrary(hocx);
	}
	//////////////////////////////////////////////
	// CG: The following block was added by the Splash Screen component.
\
	{
\
		CCommandLineInfo cmdInfo;
\
		ParseCommandLine(cmdInfo);
\

\
		CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
\
	}
	AfxEnableControlContainer();
	AfxGetModuleState()->m_dwVersion = 0x0601;
	AfxOleInit();

	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings(9);  // Load standard INI file options (including MRU)

	// Register document templates
	//载入资源DLL
	GetLang(g_bEnglish);
	m_bHaveChange = g_bEnglish;

	WORD wLangPID = PRIMARYLANGID(::GetSystemDefaultLangID());
	if(wLangPID != LANG_CHINESE)
	{
		g_bEnglish = TRUE;
		SetLang(TRUE);
	}

	if(g_bEnglish)
	{
		m_hLangDLL =::LoadLibrary("SpectraNexus_En.dll");
		if( !m_hLangDLL)
		{
			AfxMessageBox(_T("Unable to load resource DLL!"));
			return FALSE;
		}
		AfxSetResourceHandle(m_hLangDLL);
	}

//	g_SPEC.SPEC_Init();

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMySpecDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CMySpecView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CStatic	m_cNote;
	CLabel	m_cEV;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_STATIC_NOTE, m_cNote);
	DDX_Control(pDX, IDC_EV, m_cEV);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CMySpecApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMySpecApp message handlers


BOOL CMySpecApp::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following lines were added by the Splash Screen component.
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;

	return CWinApp::PreTranslateMessage(pMsg);
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cEV.SetLink(TRUE)
		.SetTextColor(RGB(0,0,255))
		.SetFontUnderline(TRUE)
		.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));
	
	//读取仪器编号
	BOOL bR;
	CString sTemp;
	sTemp="";
	if(g_iSeleMode == 0 && !g_bTest)
	{
		sTemp = "";
		bR = g_SPEC.m_HAAS.ReadSN(sTemp);
		if(bR)
			sTemp = "SN:"+sTemp+" USB Driver:"+g_strDriverVer;
		else
			sTemp = "USB Driver:" + g_strDriverVer;
	}
	else
	{
		sTemp = "USB Driver:" + g_strDriverVer;
	}

	m_cNote.SetWindowText(sTemp);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMySpecApp::SetLang(BOOL bEnglish)
{
	FILE *fp;
    CString sTitle;
	sTitle="set.lang";
    if((fp=fopen(g_strCurPath+sTitle,"wt"))==0)
		return;
    else
	{
		fprintf(fp,"English:%d\n",bEnglish);
		fclose(fp);
		return;
	}
/*	FILE *fp;
	CString sTitle;
	sTitle="set.lang";
	if((fp=fopen(g_strCurPath+sTitle,"wt"))==0)
		return;
	else
	{
		fprintf(fp,"English:%d\n",bEnglish);
		fclose(fp);

		m_bHaveChange=bEnglish;
		if(g_bEnglish!=m_bHaveChange)
			::PostMessage(g_FrameWnd,WM_CLOSE,0,0);
		return;
	}*/
}

void CMySpecApp::GetLang(BOOL &bEnglish)
{
	FILE *fp;
    CString sTitle;
	sTitle="set.lang";
    if((fp=fopen(g_strCurPath+sTitle,"rt"))==0)
	{
		bEnglish=FALSE;
		return;
	}
    else
	{
		fscanf(fp,"English:%d\n",&bEnglish);
		bEnglish = abs(bEnglish);
		fclose(fp);
		return;
	}
}

int CMySpecApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_hLangDLL)
	{
		FreeLibrary(m_hLangDLL);
	}			
	return CWinApp::ExitInstance();
}

void CMySpecApp::OnChinese() 
{
	// TODO: Add your command handler code here
	SetLang(FALSE);
}

void CMySpecApp::OnUpdateChinese(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	BOOL bTemp;
	GetLang(bTemp);
	pCmdUI->SetCheck(!bTemp);
}

void CMySpecApp::OnEnglish() 
{
	// TODO: Add your command handler code here
	SetLang(TRUE);
}

void CMySpecApp::OnUpdateEnglish(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	BOOL bTemp;
	GetLang(bTemp);
	pCmdUI->SetCheck(bTemp);
}

BOOL CMySpecApp::DoEXE(CString strPathName)
{
	STARTUPINFO StartupInfo = {0};
	PROCESS_INFORMATION ProcessInfo;
	StartupInfo.cb = sizeof(STARTUPINFO);
	CString m_sExePath = strPathName;
	char a[256];
	int iN;
	iN = m_sExePath.GetLength();
	for(int i = 0; i < iN; i++)
		a[i] = m_sExePath.GetAt(i);
	
	a[i] = '\0';
	if(CreateProcess(NULL,a,NULL,NULL,FALSE,0,NULL,NULL,&StartupInfo,&ProcessInfo))
	{
		WaitForSingleObject(ProcessInfo.hProcess,INFINITE);
		return TRUE;
	}
	else
		return FALSE;
}
