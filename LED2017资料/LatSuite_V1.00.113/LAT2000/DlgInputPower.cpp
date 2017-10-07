// DlgInputPower.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DlgInputPower.h"
#include "afxdialogex.h"


// CDlgInputPower �Ի���

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


// CDlgInputPower ��Ϣ�������


BOOL CDlgInputPower::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgInputPower::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL bR;
	bR = UpdateData(TRUE);
	if (!bR)
	{
		return;
	}
	CDialogEx::OnOK();
}
