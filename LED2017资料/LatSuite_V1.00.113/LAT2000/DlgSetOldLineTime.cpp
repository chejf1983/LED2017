// DlgSetOldLineTime.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DlgSetOldLineTime.h"
#include "afxdialogex.h"


// CDlgSetOldLineTime 对话框

IMPLEMENT_DYNAMIC(CDlgSetOldLineTime, CDialogEx)

CDlgSetOldLineTime::CDlgSetOldLineTime(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSetOldLineTime::IDD, pParent)
{

	m_fOldLineT_Times = 5.0f;
}

CDlgSetOldLineTime::~CDlgSetOldLineTime()
{
}

void CDlgSetOldLineTime::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_OLD_LINE_TIME, m_fOldLineT_Times);
}


BEGIN_MESSAGE_MAP(CDlgSetOldLineTime, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgSetOldLineTime::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgSetOldLineTime 消息处理程序


void CDlgSetOldLineTime::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_fOldLineT_Times < 5)
	{
		AfxMessageBox("老练节拍周期应大于5秒,请重新设定!");
		return;
	}
	CDialogEx::OnOK();
}
