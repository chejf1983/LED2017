// DlgControlShow.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DlgControlShow.h"
#include "afxdialogex.h"


// CDlgControlShow 对话框

IMPLEMENT_DYNAMIC(CDlgControlShow, CDialogEx)

CDlgControlShow::CDlgControlShow(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgControlShow::IDD, pParent)
	, m_iSeleControl(0)
{

}

CDlgControlShow::~CDlgControlShow()
{
}

void CDlgControlShow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_iSeleControl);
}


BEGIN_MESSAGE_MAP(CDlgControlShow, CDialogEx)
END_MESSAGE_MAP()


// CDlgControlShow 消息处理程序
