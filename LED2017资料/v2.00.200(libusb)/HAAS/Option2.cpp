// Option2.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "Option2.h"
#include "Global_MySpec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COption2 property page
extern BOOL  g_bPhoEffSetAuto;
extern float g_fSpectB1,g_fSpectB2,g_fSpectY1,g_fSpectY2;

IMPLEMENT_DYNCREATE(COption2, CPropertyPage)

COption2::COption2() : CPropertyPage(COption2::IDD)
{
	//{{AFX_DATA_INIT(COption2)
	m_bInfo = FALSE;
	m_bHW = FALSE;
	m_bIp = FALSE;
	m_bLd = FALSE;
	m_bLp = FALSE;
	m_bNote = FALSE;
	m_bPH = FALSE;
	m_bPur = FALSE;
	m_bRa = FALSE;
	m_bRR = FALSE;
	m_bTc = FALSE;
	m_bUV = FALSE;
	m_bXY = FALSE;
	m_bIF = FALSE;
	m_bP = FALSE;
	m_bVF = FALSE;
	m_bLevel = FALSE;
	m_bWhite = FALSE;
	m_bZW   = FALSE;
	m_bRO = FALSE;
	m_bPhoEff = FALSE;
	m_bPhSP = FALSE;
	m_bPrintPh_ = FALSE;
	m_bdC = FALSE;
	m_bColorCorrectStr = FALSE;
	//}}AFX_DATA_INIT
}

COption2::~COption2()
{
}

void COption2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COption2)
	DDX_Control(pDX, IDC_CHECK_ZW, m_cZW);
	DDX_Check(pDX, IDC_CHECK_INFO, m_bInfo);
	DDX_Check(pDX, IDC_CHECK_HW, m_bHW);
	DDX_Check(pDX, IDC_CHECK_IP, m_bIp);
	DDX_Check(pDX, IDC_CHECK_LD, m_bLd);
	DDX_Check(pDX, IDC_CHECK_LP, m_bLp);
	DDX_Check(pDX, IDC_CHECK_NOTE, m_bNote);
	DDX_Check(pDX, IDC_CHECK_PH, m_bPH);
	DDX_Check(pDX, IDC_CHECK_PUR, m_bPur);
	DDX_Check(pDX, IDC_CHECK_RA, m_bRa);
	DDX_Check(pDX, IDC_CHECK_RR, m_bRR);
	DDX_Check(pDX, IDC_CHECK_TC, m_bTc);
	DDX_Check(pDX, IDC_CHECK_UV, m_bUV);
	DDX_Check(pDX, IDC_CHECK_XY, m_bXY);
	DDX_Check(pDX, IDC_CHECK_IF, m_bIF);
	DDX_Check(pDX, IDC_CHECK_P, m_bP);
	DDX_Check(pDX, IDC_CHECK_VF, m_bVF);
	DDX_Check(pDX, IDC_CHECK_LEVEL, m_bLevel);
	DDX_Check(pDX, IDC_CHECK_WHITE, m_bWhite);
	DDX_Check(pDX, IDC_CHECK_ZW, m_bZW);
	DDX_Check(pDX, IDC_CHECK_RO, m_bRO);
	DDX_Check(pDX, IDC_CHECK_PHO_EFF, m_bPhoEff);
	DDX_Check(pDX, IDC_CHECK_PH_S_P, m_bPhSP);
	DDX_Check(pDX, IDC_CHECK_PRINT_PH_, m_bPrintPh_);
	DDX_Check(pDX, IDC_CHECK_DC, m_bdC);
	DDX_Check(pDX, IDC_CHECK_COLOR_CORRECT_STR, m_bColorCorrectStr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COption2, CPropertyPage)
	//{{AFX_MSG_MAP(COption2)
	ON_BN_CLICKED(IDC_BUTTON_PHO, OnButtonPho)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COption2 message handlers

BOOL COption2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(g_SPEC.T_SPECT1==200)
	{
		m_cZW.ShowWindow(TRUE);
	}
	else
		m_cZW.ShowWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COption2::OnButtonPho() 
{
	// TODO: Add your control notification handler code here
}
