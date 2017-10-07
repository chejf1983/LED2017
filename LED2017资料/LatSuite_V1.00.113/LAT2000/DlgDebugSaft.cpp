// DlgDebugSaft.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DlgDebugSaft.h"
#include "afxdialogex.h"


// CDlgDebugSaft �Ի���

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


// CDlgDebugSaft ��Ϣ�������


BOOL CDlgDebugSaft::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgDebugSaft::OnBnClickedButtonSetpara()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		AfxMessageBox("���Բ�������ʧ��!");
	}
}


void CDlgDebugSaft::OnBnClickedButtonStart1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	g_SafetyTest_TongHui_TH2683AComm.Initialize(m_strCOM);
	if (!g_SafetyTest_TongHui_TH2683AComm.TH_SetTestStart_IR(TRUE))
	{
		AfxMessageBox("���Բ�������ʧ��!");
	}
}


void CDlgDebugSaft::OnBnClickedButtonReadpara()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	g_SafetyTest_TongHui_TH2683AComm.Initialize(m_strCOM);
	float fIR, fLC, fTime;
	if (!g_SafetyTest_TongHui_TH2683AComm.TH_GetTestResult_IR(fIR, fLC, fTime))
	{
		AfxMessageBox("���Բ�������ʧ��!");
		return ;
	}
	CString strNote;
	strNote.Format("IR:%g ��, LC:%g A; TestTime:%.1f s", fIR, fLC, fTime);
	GetDlgItem(IDC_STATIC_RESULT)->SetWindowText(strNote);
}


void CDlgDebugSaft::OnBnClickedButtonSetpara2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgDebugSaft::OnBnClickedButtonStart2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgDebugSaft::OnBnClickedButtonDicharge()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	g_SafetyTest_TongHui_TH2683AComm.Initialize(m_strCOM);
	if (!g_SafetyTest_TongHui_TH2683AComm .SetTestDisCharge())
	{
		AfxMessageBox("���Բ�������ʧ��!");
	}
}
