// Debug3.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "Debug3.h"
#include "Global_MySpec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDebug3 property page

IMPLEMENT_DYNCREATE(CDebug3, CPropertyPage)

CDebug3::CDebug3() : CPropertyPage(CDebug3::IDD)
{
	//{{AFX_DATA_INIT(CDebug3)
	m_fC2 = 0.0;
	m_fC3 = 0.0;
	m_fC4 = 0.0;
	m_fC1 = 0.0;
	m_iBaud = 5;
	m_strDriver = _T("");
	m_strEprom = _T("");
	m_strSoftVer = _T("");
	m_strSN = _T("");
	//}}AFX_DATA_INIT
	CString strSection  = "NH_Debug_A";
	
	CString strDriver	= "Driver";
	CString strEprom    = "Eprom";
	CString strSoftVer  = "SoftVer";
	
	m_strDriver			= AfxGetApp()->GetProfileString(strSection,strDriver,"SpectraNexus USB DRIVER V1.00");
	m_strEprom			= AfxGetApp()->GetProfileString(strSection,strEprom,"SpectraNexus V1.00.iic");
	m_strSoftVer		= AfxGetApp()->GetProfileString(strSection,strSoftVer,"SpectraNexus_V1.00.100");
}

CDebug3::~CDebug3()
{
}

void CDebug3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDebug3)
	DDX_Control(pDX, IDC_COMBO_R_SN, m_cReadSN);
	DDX_Control(pDX, IDC_EDIT_SN, m_cWriteSN);
	DDX_Text(pDX, IDC_EDIT_C2, m_fC2);
	DDX_Text(pDX, IDC_EDIT_C3, m_fC3);
	DDX_Text(pDX, IDC_EDIT_C4, m_fC4);
	DDX_Text(pDX, IDC_EDIT_C1, m_fC1);
	DDX_CBIndex(pDX, IDC_COMBO_BUAD, m_iBaud);
	DDX_Text(pDX, IDC_EDIT_DRIVER, m_strDriver);
	DDX_Text(pDX, IDC_EDIT_EPROM, m_strEprom);
	DDX_Text(pDX, IDC_EDIT_SOFT_VER, m_strSoftVer);
	DDX_Text(pDX, IDC_EDIT_HAAS_SN, m_strSN);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDebug3, CPropertyPage)
	//{{AFX_MSG_MAP(CDebug3)
	ON_BN_CLICKED(IDC_BUTTON_S_ON, OnButtonSOn)
	ON_BN_CLICKED(IDC_BUTTON_S_OFF, OnButtonSOff)
	ON_BN_CLICKED(IDC_BUTTON_W_SN, OnButtonWSn)
	ON_BN_CLICKED(IDC_BUTTON_R_SN, OnButtonRSn)
	ON_BN_CLICKED(IDC_BUTTON_W_COR, OnButtonWCor)
	ON_BN_CLICKED(IDC_BUTTON_R_COR, OnButtonRCor)
	ON_BN_CLICKED(IDC_BUTTON_MOD_SN, OnButtonModSn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDebug3 message handlers

BOOL CDebug3::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString sTemp;
	sTemp="0910001";
	m_cWriteSN.SetWindowText(sTemp);

	m_strSN = g_SPEC.m_strSN;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDebug3::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	m_fC1   = g_SPEC.m_Icor;
	m_fC2   = g_SPEC.m_C1cor;
	m_fC3   = g_SPEC.m_C2cor;
	m_fC4   = g_SPEC.m_C3cor;

	UpdateData(FALSE);
	return CPropertyPage::OnSetActive();
}

void CDebug3::OnButtonSOn() 
{
	// TODO: Add your control notification handler code here
	BOOL bR = FALSE;
//	bR=g_SPEC.m_HAAS.SetCool(TRUE);
	if(!bR)
	{
		if(!g_bEnglish)
			AfxMessageBox("制冷开失败!  ",MB_ICONINFORMATION);
	}
	else
	{
		if(!g_bEnglish)
			AfxMessageBox("制冷已打开!  ",MB_ICONINFORMATION);
	}
}

void CDebug3::OnButtonSOff() 
{
	// TODO: Add your control notification handler code here
	BOOL bR = FALSE;
//	bR=g_SPEC.m_HAAS.SetCool(FALSE);
	if(!bR)
	{
		if(!g_bEnglish)
			AfxMessageBox("制冷关失败!  ",MB_ICONINFORMATION);
	}
	else
	{
		if(!g_bEnglish)
			AfxMessageBox("制冷已关闭!  ",MB_ICONINFORMATION);
	}
}

void CDebug3::OnButtonWSn() 
{
	// TODO: Add your control notification handler code here
	//修改仪器编号
	UpdateData(TRUE);
	CString sTemp;
	m_cWriteSN.GetWindowText(sTemp);
	BOOL bR;
	int iBaud;
	if(m_iBaud==0)
		iBaud=2400;
	else if(m_iBaud==1)
		iBaud=4800;
	else if(m_iBaud==2)
		iBaud=9600;
	else if(m_iBaud==3)
		iBaud=19200;
	else if(m_iBaud==4)
		iBaud=38400;
	else
		iBaud=115200;

	bR=g_SPEC.m_HAAS.SetSN(sTemp,iBaud);
	AfxMessageBox(sTemp);
	if(!bR)
	{
		if(!g_bEnglish)
			AfxMessageBox("序列号修改失败!  ",MB_ICONINFORMATION);
		else
			AfxMessageBox("FAIL");
	}
	else
	{
		g_SPEC.m_iBaudRate=iBaud;
		if(!g_bEnglish)
			AfxMessageBox("序列号修改成功!  ",MB_ICONINFORMATION);
		else
			AfxMessageBox("FAIL");
	}
}

void CDebug3::OnButtonRSn() 
{
	// TODO: Add your control notification handler code here
	//读取仪器编号
	BOOL bR;
	CString sTemp;
	bR=g_SPEC.m_HAAS.ReadSN(sTemp);

	m_cWriteSN.SetWindowText(sTemp);
	AfxMessageBox(sTemp);
	if(!bR)
	{
		if(!g_bEnglish)
			AfxMessageBox("序列号读取失败!  ",MB_ICONINFORMATION);
		else
			AfxMessageBox("FAIL");

	}
	else
	{
		m_cReadSN.InsertString(0,sTemp);
		if(!g_bEnglish)
			AfxMessageBox("序列号读取成功!  ",MB_ICONINFORMATION);
		else
			AfxMessageBox("FAIL");
	}
	UpdateData(FALSE);
}

void CDebug3::OnButtonWCor() 
{
	// TODO: Add your control notification handler code here

}

void CDebug3::OnButtonRCor() 
{
	// TODO: Add your control notification handler code here
	
}

void CDebug3::OnButtonModSn() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	g_SPEC.m_strSN		= m_strSN;
	g_SPEC.m_strSoftVer	= m_strSoftVer;
	g_SPEC.m_strEprom	= m_strEprom;
	g_SPEC.m_strDriver	= m_strDriver;

	CString strSection  = "Debug3_A";
	
	CString strDriver	= "Driver";
	CString strEprom    = "Eprom";
	CString strSoftVer  = "SoftVer";
	
	AfxGetApp()->WriteProfileString(strSection,strDriver,m_strDriver);
	AfxGetApp()->WriteProfileString(strSection,strEprom,m_strEprom);
	AfxGetApp()->WriteProfileString(strSection,strSoftVer,m_strSoftVer);
}
