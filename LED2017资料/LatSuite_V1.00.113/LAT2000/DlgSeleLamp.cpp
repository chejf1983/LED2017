// DlgSeleLamp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DlgSeleLamp.h"
#include "afxdialogex.h"


// CDlgSeleLamp �Ի���

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


// CDlgSeleLamp ��Ϣ�������


void CDlgSeleLamp::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CDlgSeleLamp::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
