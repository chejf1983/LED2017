// WarningYesNODlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "WarningYesNODlg.h"
#include "afxdialogex.h"


// CWarningYesNODlg 对话框

IMPLEMENT_DYNAMIC(CWarningYesNODlg, CDialogEx)

CWarningYesNODlg::CWarningYesNODlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWarningYesNODlg::IDD, pParent)
{
	m_font.CreateFont(-26, 0, 0, 0, 800, FALSE, FALSE, 0,
		GB2312_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_MODERN,"宋体");
}

CWarningYesNODlg::~CWarningYesNODlg()
{
}

void CWarningYesNODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_INFO, m_strInfo);
}


BEGIN_MESSAGE_MAP(CWarningYesNODlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CWarningYesNODlg 消息处理程序


BOOL CWarningYesNODlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetDlgItem(IDC_STATIC_INFO)->SetFont(&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

HBRUSH CWarningYesNODlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_INFO)
	{
		pDC->SetTextColor(RGB(0, 0, 255));
		pDC->SetBkMode(TRANSPARENT);
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


