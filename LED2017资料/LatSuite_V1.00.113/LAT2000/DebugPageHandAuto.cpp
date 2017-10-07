// DebugPageHandAuto.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DebugPageHandAuto.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"

// CDebugPageHandAuto �Ի���

IMPLEMENT_DYNAMIC(CDebugPageHandAuto, CPropertyPage)

CDebugPageHandAuto::CDebugPageHandAuto()
	: CPropertyPage(CDebugPageHandAuto::IDD)
	, m_strCOM(_T("COM10"))
	, m_iChannel1(0)
	, m_iChannel10(0)
	, m_iChannel9(0)
	, m_iChannel8(0)
	, m_iChannel7(0)
	, m_iChannel6(0)
	, m_iChannel5(0)
	, m_iChannel4(0)
	, m_iChannel3(0)
	, m_iChannel2(0)
{

}

CDebugPageHandAuto::~CDebugPageHandAuto()
{
}

void CDebugPageHandAuto::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_COM, m_strCOM);
	DDX_CBIndex(pDX, IDC_COMBO1, m_iChannel1);
	DDX_CBIndex(pDX, IDC_COMBO31, m_iChannel10);
	DDX_CBIndex(pDX, IDC_COMBO10, m_iChannel9);
	DDX_CBIndex(pDX, IDC_COMBO30, m_iChannel8);
	DDX_CBIndex(pDX, IDC_COMBO9, m_iChannel7);
	DDX_CBIndex(pDX, IDC_COMBO8, m_iChannel6);
	DDX_CBIndex(pDX, IDC_COMBO29, m_iChannel5);
	DDX_CBIndex(pDX, IDC_COMBO7, m_iChannel4);
	DDX_CBIndex(pDX, IDC_COMBO3, m_iChannel3);
	DDX_CBIndex(pDX, IDC_COMBO2, m_iChannel2);
}


BEGIN_MESSAGE_MAP(CDebugPageHandAuto, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_BUZZER_OFF, &CDebugPageHandAuto::OnBnClickedButtonBuzzerOff)
	ON_BN_CLICKED(IDC_BUTTON_MOVE, &CDebugPageHandAuto::OnBnClickedButtonMove)
	ON_BN_CLICKED(IDC_BUTTON_GET_LINE_STATE, &CDebugPageHandAuto::OnBnClickedButtonGetLineState)
	ON_BN_CLICKED(IDC_BUTTON1, &CDebugPageHandAuto::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_LINESTOP, &CDebugPageHandAuto::OnBnClickedButtonLinestop)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CDebugPageHandAuto::OnBnClickedButtonSet)
END_MESSAGE_MAP()


// CDebugPageHandAuto ��Ϣ�������


BOOL CDebugPageHandAuto::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_strCOM = g_pDoc->m_CommSettingsData.m_strHandAutoCOM;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDebugPageHandAuto::OnBnClickedButtonBuzzerOff()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL bR;
	bR = UpdateData(TRUE);
	if (!bR)
	{
		return;
	}
	bR = g_HandAutoComm.WriteToHandInpos(TRUE);
	if (!bR)
	{
		AfxMessageBox("FAIL!");
	}
	else
	{
		AfxMessageBox("OK!");
	}
}


void CDebugPageHandAuto::OnBnClickedButtonMove()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL bR;
	bR = UpdateData(TRUE);
	if (!bR)
	{
		return;
	}
	bR = g_HandAutoComm.WriteToHandInpos(FALSE);
	if (!bR)
	{
		AfxMessageBox("FAIL!");
	}
	else
	{
		AfxMessageBox("OK!");
	}
}


void CDebugPageHandAuto::OnBnClickedButtonGetLineState()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL bR;
	bR = UpdateData(TRUE);
	if (!bR)
	{
		return;
	}
	BOOL bAllow = FALSE;
	bR = g_HandAutoComm.ReadHandState(bAllow);
	if (!bR)
	{
		AfxMessageBox("FAIL!");
		return;
	}

	CString strTemp;
	if (bAllow)
	{
		strTemp.Format("�����������!");
	}
	else
	{
		strTemp.Format("��ֹ��������!");
	}
	AfxMessageBox(strTemp);
}


void CDebugPageHandAuto::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
}


void CDebugPageHandAuto::OnBnClickedButtonLinestop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
}


void CDebugPageHandAuto::OnBnClickedButtonSet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL bR;
	bR = UpdateData(TRUE);
	if (!bR)
	{
		return;
	}
	int bCheck[10];
	bCheck[0] = m_iChannel1;
	bCheck[1] = m_iChannel2;
	bCheck[2] = m_iChannel3;
	bCheck[3] = m_iChannel4;
	bCheck[4] = m_iChannel5;
	bCheck[5] = m_iChannel6;
	bCheck[6] = m_iChannel7;
	bCheck[7] = m_iChannel8;
	bCheck[8] = m_iChannel9;
	bCheck[9] = m_iChannel10;
	g_HandAutoComm.Initialize(m_strCOM);
	bR = g_HandAutoComm.WriteToHandLamp(bCheck);
	if (!bR)
	{
		AfxMessageBox("FAIL!");
		return;
	}
}
