// DebugWYPage.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DebugWYPage.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"


// CDebugWYPage 对话框

IMPLEMENT_DYNAMIC(CDebugWYPage, CPropertyPage)

CDebugWYPage::CDebugWYPage()
	: CPropertyPage(CDebugWYPage::IDD)
	, m_fCurr(0)
{

	m_fVoltage = 0.0f;
	m_fCurrent = 0.0f;

	CString strSection = "WYDebugPage";
	m_strCOM = AfxGetApp()->GetProfileStringA(strSection, "m_strCOM", "COM1");
	m_fProtectCurrent = 0.0f;
	m_fVoltageSet = 0.0f;
}

CDebugWYPage::~CDebugWYPage()
{
	CString strSection = "WYDebugPage";
	AfxGetApp()->WriteProfileStringA(strSection, "m_strCOM", m_strCOM);
}

void CDebugWYPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_COM, m_strCOM);
	DDX_Text(pDX, IDC_EDIT_VOLTAGE_READ, m_fVoltage);
	DDX_Text(pDX, IDC_EDIT_CURRENT_READ, m_fCurrent);
	DDX_Text(pDX, IDC_EDIT_PRPTECT_CURRENT, m_fProtectCurrent);
	DDX_Text(pDX, IDC_EDIT_VOLTAGE_SET, m_fVoltageSet);
	DDX_Text(pDX, IDC_EDIT_CURRENT_SET, m_fCurr);
}


BEGIN_MESSAGE_MAP(CDebugWYPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CDebugWYPage::OnBnClickedButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT, &CDebugWYPage::OnBnClickedButtonOutput)
    ON_BN_CLICKED(IDC_OUTPUT_HLS_200, &CDebugWYPage::OnBnClickedOutputHls200)
    ON_BN_CLICKED(IDC_RESET_HLS_200, &CDebugWYPage::OnBnClickedResetHls200)
    ON_BN_CLICKED(IDC_BUTTON_READ_STATE, &CDebugWYPage::OnBnClickedButtonReadState)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CDebugWYPage::OnBnClickedButtonSet)
END_MESSAGE_MAP()


// CDebugWYPage 消息处理程序


void CDebugWYPage::OnBnClickedButtonRead()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	BeginWaitCursor();
	int iCom = 1;
	sscanf_s(m_strCOM, "COM%d", &iCom);
	g_WYComm.Initialize(iCom, 1);
    
	BOOL bR = g_WYComm.GetPower(m_fVoltage, m_fCurrent, TRUE);
	EndWaitCursor();
}


void CDebugWYPage::OnBnClickedButtonOutput()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	BeginWaitCursor();
	int iCom = 1;
	sscanf_s(m_strCOM, "COM%d", &iCom);
	g_WYComm.Initialize(iCom, 1);
	float f1, f2;
	BOOL bR = g_WYComm.SetPower(sele_u, m_fVoltageSet, m_fProtectCurrent, f1, f2, TRUE);
	EndWaitCursor();
}


BOOL CDebugWYPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_strCOM = g_pDoc->m_CommSettingsData.m_strStandardSupplyCOM;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDebugWYPage::OnBnClickedOutputHls200()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);

    BeginWaitCursor();
    int iCom = 1;
    sscanf_s(m_strCOM, "COM%d", &iCom);
    g_HLS_200.SetCom(iCom);

    BOOL bR = g_HLS_200.OpenOutput();
    if (!bR)
    {
        AfxMessageBox("输出失败!");
    }
    EndWaitCursor();
}


void CDebugWYPage::OnBnClickedResetHls200()
{
    // TODO: 在此添加控件通知处理程序代码
    BeginWaitCursor();
    int iCom = 1;
    sscanf_s(m_strCOM, "COM%d", &iCom);
    g_HLS_200.SetCom(iCom);

    BOOL bR = g_HLS_200.CloseOutput();
    if (!bR)
    {
        AfxMessageBox("复位失败!");
    }
    EndWaitCursor();
}


void CDebugWYPage::OnBnClickedButtonReadState()
{
    // TODO: 在此添加控件通知处理程序代码
    BeginWaitCursor();
    int iCom = 1;
    sscanf_s(m_strCOM, "COM%d", &iCom);
    g_HLS_200.SetCom(iCom);
    BOOL Output,Load,Warning;
    BOOL bR = g_HLS_200.GetState(Output,Load,Warning);
    if (!bR)
    {
        AfxMessageBox("读取状态失败!");
    }
    else
    {
        CString strTemp;
        strTemp.Format("输出状态:%d, 负载状态: %d, 短路状态: %d", Output,Load,Warning);
        AfxMessageBox(strTemp);
    }
    EndWaitCursor();
}


void CDebugWYPage::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	BeginWaitCursor();
	int iCom = 1;
	sscanf_s(m_strCOM, "COM%d", &iCom);
	g_HLS_200.SetCom(iCom);
	BOOL bR = g_HLS_200.SetCurr(m_fCurr*10);
	if (!bR)
	{
		AfxMessageBox("失败!");
	}
	else
	{
		AfxMessageBox("OK!");
	}
	EndWaitCursor();
}
