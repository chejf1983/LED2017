// ExitSelectionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "ExitSelectionDlg.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"


// CExitSelectionDlg 对话框

IMPLEMENT_DYNAMIC(CExitSelectionDlg, CDialogEx)

CExitSelectionDlg::CExitSelectionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExitSelectionDlg::IDD, pParent)
{
	m_bResetDPS = TRUE;
	m_bResetTMPController = TRUE;
	m_bDPSEnable = TRUE;
	m_bTMPControllerEnable = TRUE;
	CString strSection = "ExitSelectionDlg";
	CString str_m_bSaveFile = "m_bSaveFile";
}

CExitSelectionDlg::~CExitSelectionDlg()
{
	CString strSection = "ExitSelectionDlg";
	CString str_m_bSaveFile = "m_bSaveFile";
}

void CExitSelectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_RESET_DPS, m_bResetDPS);
	DDX_Check(pDX, IDC_CHECK_RESET_TMP, m_bResetTMPController);
}


BEGIN_MESSAGE_MAP(CExitSelectionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SAVE_FILE, &CExitSelectionDlg::OnBnClickedSaveFile)
	ON_BN_CLICKED(IDOK, &CExitSelectionDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CExitSelectionDlg 消息处理程序


BOOL CExitSelectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetDlgItem(IDC_CHECK_RESET_DPS)->EnableWindow(m_bDPSEnable);
	GetDlgItem(IDC_CHECK_RESET_TMP)->EnableWindow(m_bTMPControllerEnable);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CExitSelectionDlg::OnBnClickedSaveFile()
{
	// TODO: 在此添加控件通知处理程序代码

	CFileDialog dlg(FALSE, "lat2000-everfine", "LAT-2000", 6UL, "nLAT2000 Files(*.lat2000-everfine)|*.lat2000-everfine|");
	if (IDOK == dlg.DoModal())
	{
		g_pDoc->m_dataContainer.GetTestSettingData() = g_pDoc->m_dataContainer.GetTestSettingData();		
		g_pDoc->m_dataContainer.SaveFile(dlg.GetPathName());
		g_bhaveSaveFile = TRUE;
	}
}




void CExitSelectionDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (0)//g_bhaveSaveFile == FALSE && g_pDoc->m_dataContainer.GetSize())
	{
        if (!g_pDoc->m_systemSettingsData.m_bAutoSave)
        {
            if (MessageBox("换灯是否保存当前测试文件？","提醒",  MB_YESNO) == IDYES)
            {
                CFileDialog dlg(FALSE, "lat2000-everfine", "LAT-2000", 6UL, "nLAT2000 Files(*.lat2000-everfine)|*.lat2000-everfine|");
                if (IDOK == dlg.DoModal())
                {          
                    g_pDoc->m_dataContainer.SaveFile(dlg.GetPathName());
                }
            }  	
        }
        else
        {
            CString strPathName;
            CTime tNow = CTime::GetCurrentTime();
            if (!g_pDoc->m_systemSettingsData.m_iPrefixInputMode)
            {
                strPathName = g_pDoc->m_systemSettingsData.m_strFilePath + "\\" + 
                    g_pDoc->m_systemSettingsData.m_strFileName + tNow.Format("%Y-%m-%d %H-%M-%S.lat2000-everfine");// 
            }
            else
            {
                strPathName = g_pDoc->m_systemSettingsData.m_strFilePath + "\\" + 
                    g_pDoc->m_dataContainer.GetTestSettingData().m_strLedModel + tNow.Format("%Y-%m-%d %H-%M-%S.lat2000-everfine");// %H-%M-%S
            }
            g_pDoc->m_dataContainer.SaveFile(strPathName);
        }   
	}
 
	
	CDialogEx::OnOK();
}
