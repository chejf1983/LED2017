// Setup2.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "Setup2.h"
#include "SPEC_PRO.h"
#include "Global_MySpec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetup2 property page
extern float g_fSpect1;
extern float g_fSpect2;

IMPLEMENT_DYNCREATE(CSetup2, CPropertyPage)

CSetup2::CSetup2() : CPropertyPage(CSetup2::IDD)
{
	//{{AFX_DATA_INIT(CSetup2)
	m_bDemo		= FALSE;
	m_strSTCCom = _T("");
	m_strSTCType= _T("");
	m_iDateType = 0;
	//}}AFX_DATA_INIT
}

CSetup2::~CSetup2()
{
}

void CSetup2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetup2)
	DDX_Control(pDX, IDC_MODE, m_cMode);
	DDX_Control(pDX, IDC_WL_RANGE, m_cWL12);
	DDX_Control(pDX, IDC_STC_S2, m_cS2);
	DDX_Control(pDX, IDC_STC_S1, m_cS1);
	DDX_Control(pDX, IDC_COMBO_STC_TYPE, m_cSTCType);
	DDX_Control(pDX, IDC_COMBO_STC_COM, m_cSTCCom);
	DDX_Check(pDX, IDC_CHECK_DEMO, m_bDemo);
	DDX_CBString(pDX, IDC_COMBO_STC_COM, m_strSTCCom);
	DDX_CBString(pDX, IDC_COMBO_STC_TYPE, m_strSTCType);
	DDX_Radio(pDX, IDC_RADIO_T_TYPE1, m_iDateType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetup2, CPropertyPage)
	//{{AFX_MSG_MAP(CSetup2)
	ON_CBN_SELCHANGE(IDC_COMBO_STC_TYPE, OnSelchangeComboStcType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetup2 message handlers

void CSetup2::OnSelchangeComboStcType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

BOOL CSetup2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cSTCType.ResetContent();

	m_cSTCType.AddString(g_SPEC.m_strSTC_ShowName);

	UpdateData(FALSE);
	OnSelchangeComboStcType();
	CString strTemp;
	strTemp.Format("%.0f - %.0f nm",g_SPEC.T_SPECT1,g_SPEC.T_SPECT2);
	m_cWL12.SetWindowText(strTemp);
	m_cWL12.SetTextColor(RGB(0,0,255));
	m_cWL12.SetFontUnderline(TRUE);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
