// WarningYesNODlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "WarningYesNODlg.h"
#include "afxdialogex.h"


// CWarningYesNODlg �Ի���

IMPLEMENT_DYNAMIC(CWarningYesNODlg, CDialogEx)

CWarningYesNODlg::CWarningYesNODlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWarningYesNODlg::IDD, pParent)
{
	m_font.CreateFont(-26, 0, 0, 0, 800, FALSE, FALSE, 0,
		GB2312_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_MODERN,"����");
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


// CWarningYesNODlg ��Ϣ�������


BOOL CWarningYesNODlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_STATIC_INFO)->SetFont(&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

HBRUSH CWarningYesNODlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_INFO)
	{
		pDC->SetTextColor(RGB(0, 0, 255));
		pDC->SetBkMode(TRANSPARENT);
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


