// Setup5.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "Setup5.h"
#include "TC100LEDTMP_Factory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetup5 property page

IMPLEMENT_DYNCREATE(CSetup5, CPropertyPage)

CSetup5::CSetup5() : CPropertyPage(CSetup5::IDD)
{
	//{{AFX_DATA_INIT(CSetup5)
	m_bHaveUseLEDTMP = FALSE;
	m_fSetTMP = 25.0f;
	m_strLEDTMPCom = _T("COM5");
	m_iType = 0;
	//}}AFX_DATA_INIT
}

CSetup5::~CSetup5()
{
}

void CSetup5::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetup5)
	DDX_Control(pDX, IDC_EDIT_CURR_TMP, m_cCurrTMP);
	DDX_Check(pDX, IDC_CHECK_USE_LED_TMP, m_bHaveUseLEDTMP);
	DDX_Text(pDX, IDC_EDIT_SET_TMP, m_fSetTMP);
	DDX_CBString(pDX, IDC_COMBO_LED_TMP_COM, m_strLEDTMPCom);
	DDX_CBIndex(pDX, IDC_COMBO_TYPE, m_iType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetup5, CPropertyPage)
	//{{AFX_MSG_MAP(CSetup5)
	ON_BN_CLICKED(IDC_CHECK_USE_LED_TMP, OnCheckUseLedTmp)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_READ_TMP, OnButtonReadTmp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetup5 message handlers

void CSetup5::OnCheckUseLedTmp() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	EnableShow();
}

BOOL CSetup5::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	EnableShow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetup5::EnableShow()
{
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(m_bHaveUseLEDTMP);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(m_bHaveUseLEDTMP);
	GetDlgItem(IDC_BUTTON_READ_TMP)->EnableWindow(m_bHaveUseLEDTMP);

}

void CSetup5::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE) == FALSE)
		return;

	CTC100LEDTMP_Factory::m_iType = m_iType;
	CString strCom = m_strLEDTMPCom;
	strCom.Replace("COM", "");
	int iCom = atoi(strCom);	
	CTC100LEDTMP_Factory::GetInstance()->SetCom(iCom);

	BOOL bR;
	BeginWaitCursor();
	bR = CTC100LEDTMP_Factory::GetInstance()->SetTMP(m_fSetTMP);
	if(bR == FALSE)
		bR = CTC100LEDTMP_Factory::GetInstance()->SetTMP(m_fSetTMP);
	if(bR == FALSE)
	{
		if(g_bEnglish)
			AfxMessageBox("Comm. Fail!");
		else
			AfxMessageBox("通讯失败!");
		return;
	}

	bR = CTC100LEDTMP_Factory::GetInstance()->SetCtrl(TRUE);
	if(bR == FALSE)
		bR = CTC100LEDTMP_Factory::GetInstance()->SetCtrl(TRUE);
	if(bR == FALSE)
		bR = CTC100LEDTMP_Factory::GetInstance()->SetCtrl(TRUE);
	EndWaitCursor();

	if(bR == FALSE)
	{
		if(g_bEnglish)
			AfxMessageBox("Comm. Fail!");
		else
			AfxMessageBox("通讯失败!");
		return;
	}
}

void CSetup5::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE) == FALSE)
		return;

	CTC100LEDTMP_Factory::m_iType = m_iType;
	CString strCom = m_strLEDTMPCom;
	strCom.Replace("COM", "");
	int iCom = atoi(strCom);	
	CTC100LEDTMP_Factory::GetInstance()->SetCom(iCom);
	
	BOOL bR;
	BeginWaitCursor();
	bR = CTC100LEDTMP_Factory::GetInstance()->SetCtrl(FALSE);
	if(bR == FALSE)
		bR = CTC100LEDTMP_Factory::GetInstance()->SetCtrl(FALSE);
	if(bR == FALSE)
		bR = CTC100LEDTMP_Factory::GetInstance()->SetCtrl(FALSE);
	EndWaitCursor();

	if(bR == FALSE)
	{
		if(g_bEnglish)
			AfxMessageBox("Comm. Fail!");
		else
			AfxMessageBox("通讯失败!");
		return;
	}
}

void CSetup5::OnButtonReadTmp() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE) == FALSE)
		return;
	
	CTC100LEDTMP_Factory::m_iType = m_iType;
	CString strCom = m_strLEDTMPCom;
	strCom.Replace("COM", "");
	int iCom = atoi(strCom);	
	CTC100LEDTMP_Factory::GetInstance()->SetCom(iCom);
	
	float fTMP = 0;
	float fTMP_En = 0;
	BOOL bR;
	BeginWaitCursor();
	bR = CTC100LEDTMP_Factory::GetInstance()->ReadTMP(fTMP, fTMP_En);
	if(bR == FALSE)
		bR = CTC100LEDTMP_Factory::GetInstance()->ReadTMP(fTMP, fTMP_En);
	if(bR == FALSE)
		bR = CTC100LEDTMP_Factory::GetInstance()->ReadTMP(fTMP, fTMP_En);
	EndWaitCursor();

	if(bR == FALSE)
	{
		if(g_bEnglish)
			AfxMessageBox("Comm. Fail!");
		else
			AfxMessageBox("通讯失败!");
		return;
	}

	CString strTemp;
	strTemp.Format(_T("%.2f"), fTMP);
	m_cCurrTMP.SetWindowText(strTemp);
}
