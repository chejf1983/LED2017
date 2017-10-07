// DlgDebugSaft.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DlgDebugSaft.h"
#include "afxdialogex.h"


// CDlgDebugSaft 对话框

IMPLEMENT_DYNAMIC(CDlgDebugSaft, CPropertyPage)

CDlgDebugSaft::CDlgDebugSaft()
	: CPropertyPage(CDlgDebugSaft::IDD)
	, m_strCOM(_T("COM1"))
{

}

CDlgDebugSaft::~CDlgDebugSaft()
{
}

void CDlgDebugSaft::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_COM, m_strCOM);
}


BEGIN_MESSAGE_MAP(CDlgDebugSaft, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_SETPARA, &CDlgDebugSaft::OnBnClickedButtonSetpara)
	ON_BN_CLICKED(IDC_BUTTON_START1, &CDlgDebugSaft::OnBnClickedButtonStart1)
	ON_BN_CLICKED(IDC_BUTTON_READPARA, &CDlgDebugSaft::OnBnClickedButtonReadpara)
	ON_BN_CLICKED(IDC_BUTTON_SETPARA2, &CDlgDebugSaft::OnBnClickedButtonSetpara2)
	ON_BN_CLICKED(IDC_BUTTON_START2, &CDlgDebugSaft::OnBnClickedButtonStart2)
	ON_BN_CLICKED(IDC_BUTTON_DICHARGE, &CDlgDebugSaft::OnBnClickedButtonDicharge)
END_MESSAGE_MAP()


// CDlgDebugSaft 消息处理程序


BOOL CDlgDebugSaft::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgDebugSaft::OnBnClickedButtonSetpara()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	g_SafetyTest_TongHui_TH2683AComm.Initialize(m_strCOM);
	CSafetyTest_TongHui_TH2683AComm::SetFunctionPara para;
	para.bClearZero = FALSE; 
	para.fTestOverVoltage_V = 150;  
	para.iTestMode = 0;     
	para.iTestSpeed = 1;   
	para.bCheckSwitch = 0;  
	para.fChargeTime_s = 20;  
	para.fWaitTime_s = 20;    
	para.fTestTime_s = 20;   
	para.fDischargeTime_s = 20;
	para.iTestAvgNum = 2;    
	para.iRange = 0;        
	para.bAutoRange = 0;   
	para.bDisplay = 1;   

	if (!g_SafetyTest_TongHui_TH2683AComm .SetTestFunctionPara(para))
	{
		AfxMessageBox("测试参数设置失败!");
	}
}


void CDlgDebugSaft::OnBnClickedButtonStart1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	g_SafetyTest_TongHui_TH2683AComm.Initialize(m_strCOM);
	if (!g_SafetyTest_TongHui_TH2683AComm.TH_SetTestStart_IR(TRUE))
	{
		AfxMessageBox("测试参数设置失败!");
	}
}


void CDlgDebugSaft::OnBnClickedButtonReadpara()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	g_SafetyTest_TongHui_TH2683AComm.Initialize(m_strCOM);
	float fIR, fLC, fTime;
	if (!g_SafetyTest_TongHui_TH2683AComm.TH_GetTestResult_IR(fIR, fLC, fTime))
	{
		AfxMessageBox("测试参数设置失败!");
		return ;
	}
	CString strNote;
	strNote.Format("IR:%g Ω, LC:%g A; TestTime:%.1f s", fIR, fLC, fTime);
	GetDlgItem(IDC_STATIC_RESULT)->SetWindowText(strNote);
}


void CDlgDebugSaft::OnBnClickedButtonSetpara2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgDebugSaft::OnBnClickedButtonStart2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgDebugSaft::OnBnClickedButtonDicharge()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	g_SafetyTest_TongHui_TH2683AComm.Initialize(m_strCOM);
	if (!g_SafetyTest_TongHui_TH2683AComm .SetTestDisCharge())
	{
		AfxMessageBox("测试参数设置失败!");
	}
}
