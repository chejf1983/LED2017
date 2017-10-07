// Configure_AssistantPage.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "Configure_AssistantPage.h"
#include "afxdialogex.h"


// CConfigure_AssistantPage 对话框

IMPLEMENT_DYNAMIC(CConfigure_AssistantPage, CPropertyPage)

CConfigure_AssistantPage::CConfigure_AssistantPage()
	: CPropertyPage(CConfigure_AssistantPage::IDD)
	, m_iDis1(184)
	, m_iSpeed1(3000)
	, m_iDis2(208)
	, m_iSpeed2(8000)
	, m_iDis3(210)
	, m_iSpeed3(7000)
	, m_iDis4(2240)
	, m_iSpeed4(7000)
	, m_iDis5(172)
	, m_iSpeed5(10000)
	, m_iXMove(40)
	, m_iZMove(10)
	, m_strTouscnComm(_T("COM1"))
{

}

CConfigure_AssistantPage::~CConfigure_AssistantPage()
{
}

void CConfigure_AssistantPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_SCANER, m_bHaveScaner);
	DDX_Check(pDX, IDC_CHECK_MANIPULATOR, m_bHaveHandAuto);
	DDX_Text(pDX, IDC_EDIT_MANIPULATOR_RANGE, m_strHandAutoRange1);
	DDX_Text(pDX, IDC_EDIT_MANIPULATOR_RANGE2, m_strHandAutoRange2);
	DDX_Text(pDX, IDC_COMBO_MANIPULATOR_COM, m_strHandAutoCOM);
	DDX_CBString(pDX, IDC_COMBO_SCANER_COM, m_strScanerCOM);
	DDX_Text(pDX, IDC_EDIT_DIS1, m_iDis1);
	DDX_Text(pDX, IDC_EDIT_SPEED1, m_iSpeed1);
	DDX_Text(pDX, IDC_EDIT_DIS2, m_iDis2);
	DDX_Text(pDX, IDC_EDIT_SPEED2, m_iSpeed2);
	DDX_Text(pDX, IDC_EDIT_DIS3, m_iDis3);
	DDX_Text(pDX, IDC_EDIT_SPEED3, m_iSpeed3);
	DDX_Text(pDX, IDC_EDIT_DIS4, m_iDis4);
	DDX_Text(pDX, IDC_EDIT_SPEED4, m_iSpeed4);
	DDX_Text(pDX, IDC_EDIT_DIS5, m_iDis5);
	DDX_Text(pDX, IDC_EDIT_SPEED5, m_iSpeed5);
	DDV_MinMaxInt(pDX, m_iDis1, 0, 2600);
	DDV_MinMaxInt(pDX, m_iDis2, 0, 250);
	DDV_MinMaxInt(pDX, m_iDis3, 0, 250);
	DDV_MinMaxInt(pDX, m_iSpeed1, 0, 4000);
	DDV_MinMaxInt(pDX, m_iSpeed2, 0, 14000);
	DDV_MinMaxInt(pDX, m_iSpeed3, 0, 10000);
	DDV_MinMaxInt(pDX, m_iSpeed4, 0, 9000);
	DDV_MinMaxInt(pDX, m_iSpeed5, 0, 14000);
	DDV_MinMaxInt(pDX, m_iDis5, 0, 250);
	DDV_MinMaxInt(pDX, m_iDis4, 0, 26000);
	DDX_Text(pDX, IDC_EDIT_X_MOVE, m_iXMove);
	DDX_Text(pDX, IDC_EDIT_Z_MOVE, m_iZMove);
	DDX_CBString(pDX, IDC_COMBO_TOUSCN_COM, m_strTouscnComm);
}


BEGIN_MESSAGE_MAP(CConfigure_AssistantPage, CPropertyPage)
    ON_BN_CLICKED(IDC_BUTTON_SCANER, &CConfigure_AssistantPage::OnBnClickedButtonScaner)
    ON_BN_CLICKED(IDC_BUTTON_MANIPULATOR, &CConfigure_AssistantPage::OnBnClickedButtonManipulator)

    ON_BN_CLICKED(IDC_CHECK_SCANER, &CConfigure_AssistantPage::OnBnClickedCheckScaner)
    ON_BN_CLICKED(IDC_CHECK_MANIPULATOR, &CConfigure_AssistantPage::OnBnClickedCheckManipulator)
	ON_BN_CLICKED(IDC_BUTTON1, &CConfigure_AssistantPage::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CConfigure_AssistantPage::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CConfigure_AssistantPage::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CConfigure_AssistantPage::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CConfigure_AssistantPage::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_SCANER2, &CConfigure_AssistantPage::OnBnClickedButtonScaner2)

END_MESSAGE_MAP()


// CConfigure_AssistantPage 消息处理程序



BOOL CConfigure_AssistantPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    // TODO:  在此添加额外的初始化
    GetDlgItem(IDC_EDIT_MANIPULATOR_RANGE)->EnableWindow(m_bHaveHandAuto);
	GetDlgItem(IDC_EDIT_MANIPULATOR_RANGE2)->EnableWindow(m_bHaveHandAuto);
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CConfigure_AssistantPage::OnBnClickedButtonScaner()
{
    UpdateData(TRUE);
	g_ScanerComm.Initialize(m_strScanerCOM);
	if (SCAN_OK == g_ScanerComm.TryTest())
	{
		AfxMessageBox("试通成功!");
	}
	else
	{
		AfxMessageBox("试通失败!");		
	}
}

void CConfigure_AssistantPage::OnBnClickedButtonManipulator()
{
	
}

void CConfigure_AssistantPage::OnBnClickedCheckScaner()
{
    UpdateData(TRUE);
}

void CConfigure_AssistantPage::OnBnClickedCheckManipulator()
{
    UpdateData(TRUE);
    GetDlgItem(IDC_EDIT_MANIPULATOR_RANGE)->EnableWindow(m_bHaveHandAuto);
	GetDlgItem(IDC_EDIT_MANIPULATOR_RANGE2)->EnableWindow(m_bHaveHandAuto);
}

void CConfigure_AssistantPage::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	
}

void CConfigure_AssistantPage::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

}

void CConfigure_AssistantPage::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	
}

void CConfigure_AssistantPage::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	
}

void CConfigure_AssistantPage::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	
}

void CConfigure_AssistantPage::OnBnClickedButtonScaner2()
{
	// TODO: 在此添加控件通知处理程序代码
	
}

