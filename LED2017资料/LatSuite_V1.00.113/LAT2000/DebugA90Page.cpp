// DebugA90Page.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DebugA90Page.h"
#include "afxdialogex.h"


// CDebugA90Page �Ի���

IMPLEMENT_DYNAMIC(CDebugA90Page, CPropertyPage)

CDebugA90Page::CDebugA90Page()
	: CPropertyPage(CDebugA90Page::IDD)
{

	m_iIntegralTimems = 50;
}

CDebugA90Page::~CDebugA90Page()
{
}

void CDebugA90Page::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INTEGRAL_TIME, m_iIntegralTimems);
	DDX_Control(pDX, IDC_STATIC_SSDCM, m_cSDCM);
}


BEGIN_MESSAGE_MAP(CDebugA90Page, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CDebugA90Page::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SAMPLE, &CDebugA90Page::OnBnClickedButtonSample)
END_MESSAGE_MAP()


// CDebugA90Page ��Ϣ�������


void CDebugA90Page::OnBnClickedButtonConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BeginWaitCursor();
	BOOL bR = g_Hass1200Meter.SetShutterOn();
	EndWaitCursor();
	if (bR)
	{
		AfxMessageBox("��ͨ�ɹ���");
	}
	else
	{
		AfxMessageBox("��ͨʧ�ܣ�");
	}
}


void CDebugA90Page::OnBnClickedButtonSample()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	BeginWaitCursor();
	g_Hass1200Meter.ShowTestDialog();
	//CNewTestColorData data;
	//float * fAD = new float[g_Hass1200Meter.GetCCDPixNum()];
	//g_Hass1200Meter.SetIntTime(m_iIntegralTimems * 1.0f);
	//BOOL bR = g_Hass1200Meter.TestOne(data, fAD);
	EndWaitCursor();
	/*if (bR)
	{
		CString strTemp;
		strTemp.Format("Flux:%.2f Tc:%.0f Ip:%.0f", data.m_fPh, data.m_fTc, data.m_fIp);
		AfxMessageBox(strTemp);
	}
	else
	{
		AfxMessageBox("����ʧ�ܣ�");
	}*/

	//delete [] fAD;
}


BOOL CDebugA90Page::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
// 	CRect rect;
// 	m_cSDCM.GetWindowRect(&rect);
// 	HDC dHdc;
// 	dHdc = ::GetDC(m_cSDCM);
// 	SDCM_DLL_DrawSDCM_OneGra(dHdc,rect,0.4f,0.4f,FALSE,FALSE);
// 	Invalidate(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
