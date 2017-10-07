// NoneBorderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "NoneBorderDlg.h"
#include "afxdialogex.h"


// CNoneBorderDlg �Ի���

IMPLEMENT_DYNAMIC(CNoneBorderDlg, CDialogEx)

CNoneBorderDlg::CNoneBorderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNoneBorderDlg::IDD, pParent)
{
	m_strInfo = _T("Info");
	m_font.CreateFont(-26, 0, 0, 0, 800, FALSE, FALSE, 0,
		GB2312_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_MODERN,"����");
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


// CNoneBorderDlg ��Ϣ�������


BOOL CNoneBorderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_STATIC_INFO)->SetFont(&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


int CNoneBorderDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}


void CNoneBorderDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


HBRUSH CNoneBorderDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_INFO)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
