// DebugScanerPage.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DebugScanerPage.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"

// CDebugScanerPage 对话框

IMPLEMENT_DYNAMIC(CDebugScanerPage, CPropertyPage)

CDebugScanerPage::CDebugScanerPage()
	: CPropertyPage(CDebugScanerPage::IDD)
    , m_strCOM(_T(""))
{
    m_strCOM = g_pDoc->m_CommSettingsData.m_strScanerCOM;
    g_ScanerComm.Initialize(m_strCOM);
    m_bStopScaner = TRUE;
    m_iNum = 1;
}

CDebugScanerPage::~CDebugScanerPage()
{
}

void CDebugScanerPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_CBString(pDX, IDC_COMBO_COM, m_strCOM);
    DDX_Control(pDX, IDC_LIST_SCAN_TEXT, m_cScaner);
    DDX_Text(pDX, IDC_EDIT_NUM, m_iNum);
}

BEGIN_MESSAGE_MAP(CDebugScanerPage, CPropertyPage)
    ON_CBN_SELCHANGE(IDC_COMBO_COM, &CDebugScanerPage::OnCbnSelchangeComboCom)
    ON_BN_CLICKED(IDC_BUTTON_START_SCANER, &CDebugScanerPage::OnBnClickedButtonStartScaner)
    ON_BN_CLICKED(IDC_BUTTON_STOP_SCANER, &CDebugScanerPage::OnBnClickedButtonStopScaner)
	ON_BN_CLICKED(IDC_BUTTON1, &CDebugScanerPage::OnBnClickedButton1)
END_MESSAGE_MAP()

// CDebugScanerPage 消息处理程序

void CDebugScanerPage::OnCbnSelchangeComboCom()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    g_ScanerComm.Initialize(m_strCOM);
}

void CDebugScanerPage::OnBnClickedButtonStartScaner()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_bStopScaner = FALSE;
    m_cScaner.ResetContent();
    AfxBeginThread(ThreadScaner, this);
}

void CDebugScanerPage::OnBnClickedButtonStopScaner()
{
    // TODO: 在此添加控件通知处理程序代码
    m_bStopScaner = TRUE;
    g_ScanerComm.SetStop();
}

UINT CDebugScanerPage::ThreadScaner(LPVOID par)
{    
    CDebugScanerPage *pDlg = (CDebugScanerPage*)par;
    CString strSN;
    pDlg->GetDlgItem(IDC_BUTTON_START_SCANER)->EnableWindow(pDlg->m_bStopScaner);
    pDlg->GetDlgItem(IDC_BUTTON_STOP_SCANER)->EnableWindow(!pDlg->m_bStopScaner);
    int iScanerNum = 0;
    while(1)
    {
        if (pDlg->m_bStopScaner)
        {
            break;
        }
		int iR = g_ScanerComm.ScanOneSN(strSN);
        if (SCAN_OK == iR)
        {
            pDlg->m_cScaner.AddString(strSN);
            iScanerNum++;

			//发送给触摸屏
        }
        else
        {
			if (SCAN_FAIL == iR)
			{
				AfxMessageBox("扫码失败,请检查串口是否正确!");
				break;
			}
        }
        if (iScanerNum >= pDlg->m_iNum)
        {
            pDlg->m_bStopScaner = TRUE;
            break;
        }
    }
    pDlg->GetDlgItem(IDC_BUTTON_START_SCANER)->EnableWindow(pDlg->m_bStopScaner);
    pDlg->GetDlgItem(IDC_BUTTON_STOP_SCANER)->EnableWindow(!pDlg->m_bStopScaner);
    return 0;
}

BOOL CDebugScanerPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    // TODO:  在此添加额外的初始化
    GetDlgItem(IDC_BUTTON_START_SCANER)->EnableWindow(m_bStopScaner);
    GetDlgItem(IDC_BUTTON_STOP_SCANER)->EnableWindow(!m_bStopScaner);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CDebugScanerPage::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL bR;
	bR = UpdateData(TRUE);
	if (!bR)
	{
		return;
	}

	CString strTemp;
	m_cScaner.GetWindowTextA(strTemp);
	
	int iCOM = 1;
	m_strCOM.Trim();
	m_strCOM.MakeUpper();
	sscanf_s(m_strCOM.GetBuffer(), "COM%d", &iCOM);
	bR = g_TSrceenComm.SendShowData(0, strTemp);
	if (!bR)
	{
		AfxMessageBox("FAIL!");
	}
	else
	{
		AfxMessageBox("OK!");
	}
}
