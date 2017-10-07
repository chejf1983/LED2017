// DlgSaftSetup.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DlgSaftSetup.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"


// CDlgSaftSetup 对话框


IMPLEMENT_DYNAMIC(CDlgSaftSetup, CDialogEx)

CDlgSaftSetup::CDlgSaftSetup(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSaftSetup::IDD, pParent)
	, m_fSetVolNYY(0)
	, m_fSetTimeNYY(1)
	, m_fNYYLimit(0)
	, m_fSetTimeJYDZ(0)
	, m_fJYDZLimit(1)
	, m_fSetVolXLDL(220)
	, m_fSetTimeXLDL(1)
	, m_fXLDLLimit(0)
	, m_iTypeNYY(0)
	, m_strSetVolJYDZ(_T("100"))
{
	m_iDebugType = 0;
}

CDlgSaftSetup::~CDlgSaftSetup()
{
}

void CDlgSaftSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_VOL_NYY, m_fSetVolNYY);
	DDX_Text(pDX, IDC_EDIT_TIME_NYY, m_fSetTimeNYY);
	DDX_Text(pDX, IDC_EDIT_NYY_LIMIT, m_fNYYLimit);
	DDX_Text(pDX, IDC_EDIT_TIME_JYDZ, m_fSetTimeJYDZ);
	DDX_Text(pDX, IDC_EDIT_JYDZ_LIMIT, m_fJYDZLimit);
	DDX_Text(pDX, IDC_EDIT_VOL_XLDL, m_fSetVolXLDL);
	DDX_Text(pDX, IDC_EDIT_TIME_XLDL, m_fSetTimeXLDL);
	DDX_Text(pDX, IDC_EDIT_XLDL_LIMIT, m_fXLDLLimit);
	DDX_CBIndex(pDX, IDC_COMBO1, m_iTypeNYY);
	DDX_CBString(pDX, IDC_COMBO2, m_strSetVolJYDZ);
}


BEGIN_MESSAGE_MAP(CDlgSaftSetup, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgSaftSetup::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgSaftSetup::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgSaftSetup::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgSaftSetup::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgSaftSetup::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDlgSaftSetup::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDlgSaftSetup::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CDlgSaftSetup::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CDlgSaftSetup::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON17, &CDlgSaftSetup::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &CDlgSaftSetup::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, &CDlgSaftSetup::OnBnClickedButton19)
END_MESSAGE_MAP()


// CDlgSaftSetup 消息处理程序


BOOL CDlgSaftSetup::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetDlgItem(IDC_BUTTON1)->ShowWindow(m_iDebugType);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(m_iDebugType);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(m_iDebugType);
	GetDlgItem(IDC_BUTTON4)->ShowWindow(m_iDebugType);
	GetDlgItem(IDC_BUTTON5)->ShowWindow(m_iDebugType);
	GetDlgItem(IDC_BUTTON6)->ShowWindow(m_iDebugType);
	GetDlgItem(IDC_BUTTON7)->ShowWindow(m_iDebugType);
	GetDlgItem(IDC_BUTTON17)->ShowWindow(m_iDebugType);
	GetDlgItem(IDC_BUTTON18)->ShowWindow(m_iDebugType);
	GetDlgItem(IDC_BUTTON19)->ShowWindow(m_iDebugType);


	GetDlgItem(IDC_STATIC_XLDL1)->ShowWindow(g_pDoc->m_CommSettingsData.m_bHaveSaft_XLDL);
	GetDlgItem(IDC_STATIC_XLDL2)->ShowWindow(g_pDoc->m_CommSettingsData.m_bHaveSaft_XLDL);
	GetDlgItem(IDC_STATIC_XLDL3)->ShowWindow(g_pDoc->m_CommSettingsData.m_bHaveSaft_XLDL);
	GetDlgItem(IDC_STATIC_XLDL4)->ShowWindow(g_pDoc->m_CommSettingsData.m_bHaveSaft_XLDL);
	GetDlgItem(IDC_STATIC_XLDL5)->ShowWindow(g_pDoc->m_CommSettingsData.m_bHaveSaft_XLDL);
	GetDlgItem(IDC_EDIT_VOL_XLDL)->ShowWindow(g_pDoc->m_CommSettingsData.m_bHaveSaft_XLDL);
	GetDlgItem(IDC_EDIT_TIME_XLDL)->ShowWindow(g_pDoc->m_CommSettingsData.m_bHaveSaft_XLDL);
	GetDlgItem(IDC_EDIT_XLDL_LIMIT)->ShowWindow(g_pDoc->m_CommSettingsData.m_bHaveSaft_XLDL);
	GetDlgItem(IDC_BUTTON17)->ShowWindow(g_pDoc->m_CommSettingsData.m_bHaveSaft_XLDL);
	GetDlgItem(IDC_BUTTON18)->ShowWindow(g_pDoc->m_CommSettingsData.m_bHaveSaft_XLDL);
	GetDlgItem(IDC_BUTTON19)->ShowWindow(g_pDoc->m_CommSettingsData.m_bHaveSaft_XLDL);
	if(m_fSetVolJYDZ <= 0)
		m_fSetVolJYDZ = 100;
	m_strSetVolJYDZ.Format("%.0f",m_fSetVolJYDZ);
//	GetDlgItem(IDC_BUTTON5)->ShowWindow(g_pDoc->m_CommSettingsData.m_bHaveSaft_NYY || g_pDoc->m_CommSettingsData.m_bHaveSaft_JYDZ || g_pDoc->m_CommSettingsData.m_bHaveSaft_XLDL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgSaftSetup::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
}


void CDlgSaftSetup::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CDlgSaftSetup::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	BOOL bR = UpdateData(TRUE);
	if(!bR)
		return;
	if(g_pDoc->m_CommSettingsData.m_iTypeSaftNyy == 0)
	{
		bR = g_SafetyTest_TongHui_TH9310_20Comm.TH_Init_NYY(g_pDoc->m_CommSettingsData.m_strSaftNyyCOM);
		if(!bR)
		{
			AfxMessageBox("通讯失败!");
			return;
		}
		//Sleep(100);
		bR = g_SafetyTest_TongHui_TH9310_20Comm.TH_Setup_NYY(m_iTypeNYY,m_fSetVolNYY,m_fSetTimeNYY);
		if(!bR)
		{
			AfxMessageBox("通讯失败!");
			return;
		}
		//Sleep(100);
		bR = g_SafetyTest_TongHui_TH9310_20Comm.TH_SetTestStart_NYY(FALSE);

		bR = g_SafetyTest_TongHui_TH9310_20Comm.TH_SetTestStart_NYY(TRUE);
		if(!bR)
		{
			AfxMessageBox("通讯失败!");
			return;
		}
		//Sleep(100);
	}
	else
	{
		bR = g_SafetyTest_CS9912Comm.CS_Init_NYY(g_pDoc->m_CommSettingsData.m_strSaftNyyCOM);
		if(!bR)
		{
			AfxMessageBox("通讯失败!");
			return;
		}
		//Sleep(100);
		bR = g_SafetyTest_CS9912Comm.CS_Setup_NYY(m_iTypeNYY,m_fSetVolNYY,m_fSetTimeNYY,m_fNYYLimit);
		if(!bR)
		{
			AfxMessageBox("通讯失败!");
			return;
		}
		//Sleep(100);

		bR = g_SafetyTest_CS9912Comm.CS_Test_NYY(TRUE);
		if(!bR)
		{
			AfxMessageBox("通讯失败!");
			return;
		}
		//Sleep(100);
	}
	EndWaitCursor();
}


void CDlgSaftSetup::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	BOOL bR = UpdateData(TRUE);
	if(!bR)
		return;
	float fIR,fLC;
	BOOL bOK;
	if(g_pDoc->m_CommSettingsData.m_iTypeSaftNyy == 0)
	{
		bR = g_SafetyTest_TongHui_TH9310_20Comm.TH_GetTestResult_NYY(fLC);
		if(!bR)
		{
			AfxMessageBox("通讯失败!");
			return;
		}
		CString strTemp;
		strTemp.Format("I: %.3fmA",fLC);
		if(1)
		{
			bR = g_SafetyTest_TongHui_TH9310_20Comm.TH_SetTestStart_NYY(FALSE); //必须停止才能再次测试
			if(!bR)
			{
				AfxMessageBox("通讯失败!");
				return;
			}
			AfxMessageBox("测试完成!" + strTemp);
		}
		else
		{
			AfxMessageBox("测试中..." + strTemp);
		}
	}
	else
	{
		bR = g_SafetyTest_CS9912Comm.CS_GetData_NYY(m_iTypeNYY,bOK,fIR);
		if(!bR)
		{
			AfxMessageBox("通讯失败!");
			return;
		}
		CString strTemp;
		strTemp.Format("I: %.3fmA",fIR);
		if(bOK)
		{
			bR = g_SafetyTest_CS9912Comm.CS_Test_NYY(FALSE); //必须停止才能再次测试
			if(!bR)
			{
				AfxMessageBox("通讯失败!");
				return;
			}
			AfxMessageBox("测试完成!" + strTemp);
		}
		else
		{
			AfxMessageBox("测试中..." + strTemp);
		}
	}
	EndWaitCursor();
}


void CDlgSaftSetup::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	BOOL bR = UpdateData(TRUE);
	if(!bR)
		return;
	if (g_pDoc->m_CommSettingsData.m_iTypeSaftJydz == 0)
		bR = g_SafetyTest_TongHui_TH9310_20Comm.TH_SetTestStart_NYY(FALSE); //必须停止才能再次测试
	else
		bR = g_SafetyTest_CS9912Comm.CS_Test_NYY(FALSE); //必须停止才能再次测试
	if(!bR)
	{
		AfxMessageBox("通讯失败!");
		return;
	}
	EndWaitCursor();
}


void CDlgSaftSetup::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//Sleep(100);
	BeginWaitCursor();
	BOOL bR;
	if (g_pDoc->m_CommSettingsData.m_iTypeSaftJydz == 0)
	{
		//TH2683A
		bR = g_SafetyTest_TongHui_TH2683AComm.TH_SetTestStart_IR(TRUE);
	}
	else
	{
		bR = g_SafetyTest_CS2676Comm.CS_Test_IR(TRUE);
	}
	if(!bR)
	{
		AfxMessageBox("通讯失败!");
		return;
	}
	//Sleep(100);
	EndWaitCursor();
}


void CDlgSaftSetup::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	//读取绝缘电阻
	BeginWaitCursor();
	BOOL bR;
	float fIR,fLC,fTime;
	if (g_pDoc->m_CommSettingsData.m_iTypeSaftJydz == 0)
	{
		int iT1,iT2;
		iT1 = GetCurrentTime();
		int iErr = 0;
		while(1)
		{
			Sleep(100);
			iT2 = GetCurrentTime();
			if(iT2 - iT1 > m_fSetTimeJYDZ*1000 + 1000)
			{
				bR = g_SafetyTest_TongHui_TH2683AComm.TH_GetTestResult_IR(fIR,fLC,fTime);
				if(bR || iErr > 3)
					break;
				else
					iErr++;
			}
		}
		if(!bR)
		{
			AfxMessageBox("通讯失败!");
			return;
		}
		fIR = fIR / 1000 / 1000; //转化为M
	}
	else
	{
		bR = g_SafetyTest_CS2676Comm.CS_GetData_IR(fIR);
		if(!bR)
		{
			AfxMessageBox("通讯失败!");
			return;
		}
	}

	CString strTemp;
	strTemp.Format("%.1fMΩ",fIR);
	AfxMessageBox("测试完成!" + strTemp);
	
	EndWaitCursor();
}


void CDlgSaftSetup::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	BOOL bR;
	
	if (g_pDoc->m_CommSettingsData.m_iTypeSaftJydz == 0)
		bR = g_SafetyTest_TongHui_TH2683AComm.SetTestDisCharge();
	else
		bR = g_SafetyTest_CS2676Comm.CS_Test_IR(FALSE);
	if(!bR)
	{
		AfxMessageBox("通讯失败!");
		return;
	}
	EndWaitCursor();
}


void CDlgSaftSetup::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	//绝缘电阻设置
	BeginWaitCursor();
	BOOL bR = UpdateData(TRUE);
	if(!bR)
		return;
	if (g_pDoc->m_CommSettingsData.m_iTypeSaftJydz == 0)
	{
		g_SafetyTest_TongHui_TH2683AComm.Initialize(g_pDoc->m_CommSettingsData.m_strSaftJydzCOM);
		bR = TRUE;
	}
	else
		bR = g_SafetyTest_CS2676Comm.CS_Init_IR(g_pDoc->m_CommSettingsData.m_strSaftJydzCOM);
	if(!bR)
	{
		AfxMessageBox("通讯失败!");
		return;
	}
	m_fSetVolJYDZ = (float)atof(m_strSetVolJYDZ);
	//Sleep(100);
	if (g_pDoc->m_CommSettingsData.m_iTypeSaftJydz == 0)
		bR = g_SafetyTest_TongHui_TH2683AComm.TH_Setup_IR(m_fSetVolJYDZ, m_fSetTimeJYDZ);
	else
		bR = g_SafetyTest_CS2676Comm.CS_Setup_IR(m_fSetVolJYDZ ,m_fSetTimeJYDZ);
	if(!bR)
	{
		AfxMessageBox("通讯失败!");
		return;
	}
	EndWaitCursor();
}


void CDlgSaftSetup::OnBnClickedButton17()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	BOOL bR = UpdateData(TRUE);
	if(!bR)
		return;
	if(g_pDoc->m_CommSettingsData.m_iTypeSaftXLDL == 0)
	{
		bR = g_SafetyTest_CS5505Comm.CS_Init_XL(g_pDoc->m_CommSettingsData.m_strSaftXLDLCOM);
		if(!bR)
		{
			AfxMessageBox("通讯失败!");
			return;
		}
		//Sleep(100);
		bR = g_SafetyTest_CS5505Comm.CS_Setup_XL(m_fSetVolXLDL,m_fSetTimeXLDL);
		if(!bR)
		{
			AfxMessageBox("通讯失败!");
			return;
		}
		//Sleep(100);

		bR = g_SafetyTest_CS5505Comm.CS_Test_XL(TRUE);
		if(!bR)
		{
			AfxMessageBox("通讯失败!");
			return;
		}
		//Sleep(100);
	}
	EndWaitCursor();
}


void CDlgSaftSetup::OnBnClickedButton18()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	BOOL bR = UpdateData(TRUE);
	if(!bR)
		return;
	float fLC;
	BOOL bOK;
	if(g_pDoc->m_CommSettingsData.m_iTypeSaftXLDL == 0)
	{
		bR = g_SafetyTest_CS5505Comm.CS_GetData_XL(fLC,bOK);
		if(!bR)
		{
			AfxMessageBox("通讯失败!");
			return;
		}
		CString strTemp;
		strTemp.Format("LC: %.3fmA",fLC);
		if(bOK)
		{
			bR = g_SafetyTest_CS5505Comm.CS_Test_XL(FALSE); //必须停止才能再次测试
			if(!bR)
			{
				AfxMessageBox("通讯失败!");
				return;
			}
			AfxMessageBox("测试完成!" + strTemp);
		}
		else
		{
			AfxMessageBox("测试中..." + strTemp);
		}
	}
	EndWaitCursor();
}


void CDlgSaftSetup::OnBnClickedButton19()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	BOOL bR = UpdateData(TRUE);
	if(!bR)
		return;
	if (g_pDoc->m_CommSettingsData.m_iTypeSaftXLDL == 0)
		bR = g_SafetyTest_CS5505Comm.CS_Test_XL(FALSE); //必须停止才能再次测试
	if(!bR)
	{
		AfxMessageBox("通讯失败!");
		return;
	}
	EndWaitCursor();
}
