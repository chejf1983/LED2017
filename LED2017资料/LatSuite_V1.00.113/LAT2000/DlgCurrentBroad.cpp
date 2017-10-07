// DlgCurrentBroad.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DlgCurrentBroad.h"
#include "afxdialogex.h"


// CDlgCurrentBroad �Ի���

IMPLEMENT_DYNAMIC(CDlgCurrentBroad, CDialogEx)

CDlgCurrentBroad::CDlgCurrentBroad(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCurrentBroad::IDD, pParent)
	, m_iTestStartLEDID(1)
	, m_iCurrentBroadID(1)
	, m_iTolBroadNum(0)
{

}

CDlgCurrentBroad::~CDlgCurrentBroad()
{
}

void CDlgCurrentBroad::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CURLEDID, m_iTestStartLEDID);
	DDX_Text(pDX, IDC_EDIT_CURRENT_BOARD_INDEX, m_iCurrentBroadID);
	DDX_Text(pDX, IDC_EDIT2, m_iTolBroadNum);
}


BEGIN_MESSAGE_MAP(CDlgCurrentBroad, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgCurrentBroad::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgCurrentBroad ��Ϣ�������


void CDlgCurrentBroad::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
