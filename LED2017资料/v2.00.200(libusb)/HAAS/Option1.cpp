// Option1.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "Option1.h"
#include "Global_MySpec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COption1 property page

IMPLEMENT_DYNCREATE(COption1, CPropertyPage)

COption1::COption1() : CPropertyPage(COption1::IDD)
{
	//{{AFX_DATA_INIT(COption1)
	m_strIntervalWL = _T("0.2 nm");
	m_bPrintLogo    = FALSE;
	m_iPrintLogoPos = 0;
	m_iReportType   = 0;
	m_bPrintPage    = FALSE;
	m_iShowCIE      = 0;
	m_strPrTitle = _T("");
	m_iPrintG = 0;
	m_strAddr = _T("杭州市南环路");
	m_strCompany = _T("NAHON");
	m_iNType = 0;
	m_strChecker = _T("");
	m_bPrintChecker = FALSE;
	m_strNewT = _T("");
	//}}AFX_DATA_INIT
}

COption1::~COption1()
{
}

void COption1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COption1)
	DDX_Control(pDX, IDC_COMBO_POS, m_cPrintLogoPos);
	DDX_Control(pDX, IDC_STATIC_LOGO, m_cLogo);
	DDX_CBString(pDX, IDC_COMBO_INTERVAL_WL, m_strIntervalWL);
	DDX_Check(pDX, IDC_CHECK_PRINT_LOGO, m_bPrintLogo);
	DDX_CBIndex(pDX, IDC_COMBO_POS, m_iPrintLogoPos);
	DDX_Radio(pDX, IDC_RADIO_REPORT1, m_iReportType);
	DDX_Check(pDX, IDC_CHECK_PRINT_PAGE, m_bPrintPage);
	DDX_Radio(pDX, IDC_RADIO_SHOW1, m_iShowCIE);
	DDX_Text(pDX, IDC_EDIT_PRINT_TITLE, m_strPrTitle);
	DDX_Radio(pDX, IDC_RADIO_PRINT_G1, m_iPrintG);
	DDX_Text(pDX, IDC_EDIT_PRINT_ADDR, m_strAddr);
	DDX_Text(pDX, IDC_EDIT_PRINT_COMPANY, m_strCompany);
	DDX_Radio(pDX, IDC_RADIO_N_TYPE1, m_iNType);
	DDX_Text(pDX, IDC_EDIT_CHECKER, m_strChecker);
	DDX_Check(pDX, IDC_CHECK_PRINT_CHECKER, m_bPrintChecker);
	DDX_Text(pDX, IDC_EDIT_NEW_T, m_strNewT);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COption1, CPropertyPage)
	//{{AFX_MSG_MAP(COption1)
	ON_BN_CLICKED(IDC_CHECK_PRINT_LOGO, OnCheckPrintLogo)
	ON_BN_CLICKED(IDC_STATIC_LOGO, OnStaticLogo)
	ON_CBN_EDITCHANGE(IDC_COMBO_INTERVAL_WL, OnEditchangeComboIntervalWl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COption1 message handlers

void COption1::OnCheckPrintLogo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_cLogo.EnableWindow(m_bPrintLogo);
	m_cPrintLogoPos.EnableWindow(m_bPrintLogo);	
}

BOOL COption1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_cLogo.SetLink(TRUE)
		.SetTextColor(RGB(0,0,255))
		.SetFontUnderline(TRUE)
		.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));
	
	UpdateData(FALSE);
	OnCheckPrintLogo();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COption1::OnStaticLogo() 
{
	// TODO: Add your control notification handler code here
	CString strTemp;
	if(g_bEnglish)
		strTemp=g_strCurPath+"logo1.bmp";
	else
		strTemp=g_strCurPath+"logo.bmp";

	MSPAINT(strTemp);
}

void COption1::MSPAINT(CString strPathName)
{
	CString sStr;
	char a[256];
	GetSystemDirectory(a,256);
	CString sSystemPath=a;
	sSystemPath=sSystemPath.Left(2);

	//Windows 98
	sStr=sSystemPath;
	sStr=sStr+"\\Program Files\\Accessories\\MSPAINT.EXE "+strPathName;
	if(::WinExec(sStr,SW_SHOWDEFAULT)>=31)
	{
	}

	//Windows 20000
	sStr=sSystemPath;
	sStr=sStr+"\\WinNT\\System32\\MSPAINT.EXE "+strPathName;
	if(::WinExec(sStr,SW_SHOWDEFAULT)>=31)
	{
	}

	//Windows XP
	sStr=sSystemPath;
	sStr=sStr+"\\Windows\\System32\\MSPAINT.EXE "+strPathName;
	if(::WinExec(sStr,SW_SHOWDEFAULT)>=31)
	{
	}
}

void COption1::OnEditchangeComboIntervalWl() 
{
	// TODO: Add your control notification handler code here
	
}
