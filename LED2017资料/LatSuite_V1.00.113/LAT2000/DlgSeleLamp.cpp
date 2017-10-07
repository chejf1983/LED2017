// DlgSeleLamp.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DlgSeleLamp.h"
#include "afxdialogex.h"


// CDlgSeleLamp 对话框

IMPLEMENT_DYNAMIC(CDlgSeleLamp, CDialogEx)

CDlgSeleLamp::CDlgSeleLamp(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSeleLamp::IDD, pParent)
{

	m_iSeleTestLamp = 0;
}

CDlgSeleLamp::~CDlgSeleLamp()
{
}

void CDlgSeleLamp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_iSeleTestLamp);
}


BEGIN_MESSAGE_MAP(CDlgSeleLamp, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgSeleLamp::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgSeleLamp::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgSeleLamp 消息处理程序


void CDlgSeleLamp::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CDlgSeleLamp::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
