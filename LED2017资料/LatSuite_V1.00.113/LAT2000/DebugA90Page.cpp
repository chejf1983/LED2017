// DebugA90Page.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DebugA90Page.h"
#include "afxdialogex.h"


// CDebugA90Page 对话框

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


// CDebugA90Page 消息处理程序


void CDebugA90Page::OnBnClickedButtonConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	BOOL bR = g_Hass1200Meter.SetShutterOn();
	EndWaitCursor();
	if (bR)
	{
		AfxMessageBox("试通成功！");
	}
	else
	{
		AfxMessageBox("试通失败！");
	}
}


void CDebugA90Page::OnBnClickedButtonSample()
{
	// TODO: 在此添加控件通知处理程序代码
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
		AfxMessageBox("测试失败！");
	}*/

	//delete [] fAD;
}


BOOL CDebugA90Page::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
// 	CRect rect;
// 	m_cSDCM.GetWindowRect(&rect);
// 	HDC dHdc;
// 	dHdc = ::GetDC(m_cSDCM);
// 	SDCM_DLL_DrawSDCM_OneGra(dHdc,rect,0.4f,0.4f,FALSE,FALSE);
// 	Invalidate(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
