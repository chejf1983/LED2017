// NoneBorderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "NoneBorderDlg.h"
#include "afxdialogex.h"


// CNoneBorderDlg 对话框

IMPLEMENT_DYNAMIC(CNoneBorderDlg, CDialogEx)

CNoneBorderDlg::CNoneBorderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNoneBorderDlg::IDD, pParent)
{
	m_strInfo = _T("Info");
	m_font.CreateFont(-26, 0, 0, 0, 800, FALSE, FALSE, 0,
		GB2312_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_MODERN,"宋体");
}

CNoneBorderDlg::~CNoneBorderDlg()
{
}

void CNoneBorderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_INFO, m_strInfo);
	DDX_Check(pDX, IDC_CHECK_IGNORE, m_bIgnoreSame);
}


BEGIN_MESSAGE_MAP(CNoneBorderDlg, CDialogEx)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDOK, &CNoneBorderDlg::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CNoneBorderDlg 消息处理程序


BOOL CNoneBorderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetDlgItem(IDC_STATIC_INFO)->SetFont(&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


int CNoneBorderDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}


void CNoneBorderDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


HBRUSH CNoneBorderDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_INFO)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
