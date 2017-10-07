// DlgSetOldLineTime.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DlgSetOldLineTime.h"
#include "afxdialogex.h"


// CDlgSetOldLineTime �Ի���

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


// CDlgSetOldLineTime ��Ϣ�������


void CDlgSetOldLineTime::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_fOldLineT_Times < 5)
	{
		AfxMessageBox("������������Ӧ����5��,�������趨!");
		return;
	}
	CDialogEx::OnOK();
}
