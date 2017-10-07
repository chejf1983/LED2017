// Setup1.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "Setup1.h"
#include "PowerComm.h"
#include "DaXinPowerComm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetup1 property page
extern BOOL g_bEnglish;
extern CDaXinPowerComm g_cPower;

IMPLEMENT_DYNCREATE(CSetup1, CPropertyPage)

CSetup1::CSetup1() : CPropertyPage(CSetup1::IDD)
{
	//{{AFX_DATA_INIT(CSetup1)
	m_bHavePower	= FALSE;
	m_strPowCom		= _T("COM1");
	m_strPowType	= _T("PM9805");
	m_bManuP		= FALSE;
	m_iSouType		= -1;
	m_strSouComm	= _T("COM2");
	m_bAuto			= FALSE;
	m_iPerTime		= 0;
	m_fSetVol		= 0.0f;
	m_fSetCurr		= 0.0f;
	//}}AFX_DATA_INIT
}

CSetup1::~CSetup1()
{
}

void CSetup1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetup1)
	DDX_Control(pDX, IDC_EDIT_PER_TIME, m_cPerTime);
	DDX_Control(pDX, IDC_EDIT_CURR, m_cSetCurr);
	DDX_Control(pDX, IDC_EDIT_VOL, m_cSetVol);
	DDX_Control(pDX, IDC_COMBO_SOU_COM, m_cSouComm);
	DDX_Control(pDX, IDC_COMBO_SOU, m_cSouType);
	DDX_Control(pDX, IDC_CHECK1_MANU, m_cManuP);
	DDX_Control(pDX, IDC_COMBO_POW_TYPE, m_cPowType);
	DDX_Control(pDX, IDC_COMBO_POW_COM, m_cPowCom);
	DDX_Check(pDX, IDC_CHECK_HAVE_POWER, m_bHavePower);
	DDX_CBString(pDX, IDC_COMBO_POW_COM, m_strPowCom);
	DDX_CBString(pDX, IDC_COMBO_POW_TYPE, m_strPowType);
	DDX_Check(pDX, IDC_CHECK1_MANU, m_bManuP);
	DDX_CBIndex(pDX, IDC_COMBO_SOU, m_iSouType);
	DDX_CBString(pDX, IDC_COMBO_SOU_COM, m_strSouComm);
	DDX_Check(pDX, IDC_CHECK_AUTO, m_bAuto);
	DDX_Text(pDX, IDC_EDIT_PER_TIME, m_iPerTime);
	DDX_Text(pDX, IDC_EDIT_VOL, m_fSetVol);
	DDX_Text(pDX, IDC_EDIT_CURR, m_fSetCurr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetup1, CPropertyPage)
	//{{AFX_MSG_MAP(CSetup1)
	ON_BN_CLICKED(IDC_CHECK_HAVE_POWER, OnCheckHavePower)
	ON_BN_CLICKED(IDC_BUTTON_LAMP_OFF, OnButtonLampOff)
	ON_BN_CLICKED(IDC_CHECK_AUTO, OnCheckAuto)
	ON_CBN_SELCHANGE(IDC_COMBO_SOU, OnSelchangeComboSou)
	ON_BN_CLICKED(IDC_BUTTON_ON, OnButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_ON2, OnButtonOn2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetup1 message handlers

void CSetup1::OnCheckHavePower() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
//	m_cS1.EnableWindow(m_bHavePower);
//	m_cS2.EnableWindow(m_bHavePower);
//	m_cS3.EnableWindow(m_bHavePower);
	m_cPowType.EnableWindow(m_bHavePower);
	m_cPowCom.EnableWindow(m_bHavePower);
	m_cManuP.EnableWindow(m_bHavePower);
}

BOOL CSetup1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
//	m_cS1.EnableWindow(m_bHavePower);
//	m_cS2.EnableWindow(m_bHavePower);
//	m_cS3.EnableWindow(m_bHavePower);


	UpdateData(FALSE);

	OnCheckHavePower();

	UpdateData(TRUE);
	ShowState();
	SetLimit();
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetup1::OnButtonLampOff() 
{
	// TODO: Add your control notification handler code here
	BOOL bR=TRUE;
	int iCOM;
	sscanf(m_strSouComm,"COM%d", &iCOM);
	bR = g_cPower.DX_Power_Init(iCOM);
	if (!bR)
	{
		AfxMessageBox("FAIL !");
		return;
	}
	bR = g_cPower.DX_Power_Output(FALSE);
	if(bR)
		MessageBox("OK");
	else
	{
		AfxMessageBox("FAIL !");
		return;
	}
}

void CSetup1::OnCheckAuto() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ShowState();
	UpdateData(FALSE);
}

void CSetup1::ShowState()
{
	if(m_bAuto)
	{
		m_cPerTime.EnableWindow(TRUE);
		m_cSetCurr.EnableWindow(TRUE);
		m_cSetVol.EnableWindow(TRUE);
	}
	else
	{
		m_cPerTime.EnableWindow(FALSE);
		m_cSetCurr.EnableWindow(FALSE);
		m_cSetVol.EnableWindow(FALSE);
	}
}

void CSetup1::OnSelchangeComboSou() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ShowState();
	SetLimit();
	UpdateData(FALSE);
}

void CSetup1::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	BOOL bR;
	bR=SetLimit();
	if(!bR)
		return;
	CCmdTarget::BeginWaitCursor();
	int iCOM;
	sscanf(m_strSouComm,"COM%d", &iCOM);
	bR = g_cPower.DX_Power_Init(iCOM);
	if (!bR)
	{
		AfxMessageBox("FAIL !");
		return;
	}
	bR = g_cPower.DX_Power_SetPara(m_fSetVol,m_fSetCurr*1000);
	CCmdTarget::EndWaitCursor();
	bR = g_cPower.DX_Power_Init(iCOM);
	if (!bR)
	{
		AfxMessageBox("FAIL !");
		return;
	}
	else
	{
		if(g_bEnglish)
			AfxMessageBox("Communication OK!");
		else
			AfxMessageBox("通讯成功!");
		return;
	}
}

void CSetup1::OnButtonOn2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	BOOL bR;
	CCmdTarget::BeginWaitCursor();
	int iCOM;
	sscanf(m_strSouComm,"COM%d", &iCOM);
	bR = g_cPower.DX_Power_Init(iCOM);
	if (!bR)
	{
		AfxMessageBox("FAIL !");
		return;
	}
	bR = g_cPower.DX_Power_Output(TRUE);
	if (!bR)
	{
		AfxMessageBox("FAIL !");
	}
	CCmdTarget::EndWaitCursor();
}

BOOL CSetup1::SetLimit()
{
	m_cSetCurr.ShowWindow(TRUE);
	m_cSetVol.ShowWindow(TRUE);
	if(1)
	{
		if(m_fSetVol<0||m_fSetVol>30)
		{
			m_fSetVol=3;
			if(g_bEnglish)
				AfxMessageBox("Voltage set error!0-30V!");
			else
				AfxMessageBox("电压设置错误!0-30V!");
			return FALSE;
		}

		if(m_fSetCurr<0||m_fSetCurr>3)
		{
			m_fSetVol=0.02f;
			if(g_bEnglish)
				AfxMessageBox("Current set error!0-3A!");
			else
				AfxMessageBox("电流设置错误!0-3A!");
			return FALSE;
		}
	}
	return TRUE;
}
