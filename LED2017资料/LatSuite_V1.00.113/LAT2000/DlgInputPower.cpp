// DlgInputPower.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DlgInputPower.h"
#include "afxdialogex.h"


// CDlgInputPower 对话框

IMPLEMENT_DYNAMIC(CDlgInputPower, CDialogEx)

CDlgInputPower::CDlgInputPower(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgInputPower::IDD, pParent)
{

	//  m_fInputVol = 0.0f;
	m_fInputCurr = 0.0f;
	m_fInputPF = 0.0f;
	m_fInputPower = 0.0f;
	m_fInputVol = 0.0f;
}

CDlgInputPower::~CDlgInputPower()
{
}

void CDlgInputPower::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT_INPUT_CURR, m_fInputVol);
	DDX_Text(pDX, IDC_EDIT_INPUT_CURR, m_fInputCurr);
	DDX_Text(pDX, IDC_EDIT_INPUT_PF, m_fInputPF);
	DDX_Text(pDX, IDC_EDIT_INPUT_POWER, m_fInputPower);
	DDX_Text(pDX, IDC_EDIT_INPUT_VOL, m_fInputVol);
}


BEGIN_MESSAGE_MAP(CDlgInputPower, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgInputPower::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgInputPower 消息处理程序


BOOL CDlgInputPower::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgInputPower::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL bR;
	bR = UpdateData(TRUE);
	if (!bR)
	{
		return;
	}
	CDialogEx::OnOK();
}
