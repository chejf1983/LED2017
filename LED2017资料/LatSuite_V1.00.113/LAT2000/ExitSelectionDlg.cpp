// ExitSelectionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "ExitSelectionDlg.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"


// CExitSelectionDlg �Ի���

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


// CExitSelectionDlg ��Ϣ�������


BOOL CExitSelectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_CHECK_RESET_DPS)->EnableWindow(m_bDPSEnable);
	GetDlgItem(IDC_CHECK_RESET_TMP)->EnableWindow(m_bTMPControllerEnable);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CExitSelectionDlg::OnBnClickedSaveFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (0)//g_bhaveSaveFile == FALSE && g_pDoc->m_dataContainer.GetSize())
	{
        if (!g_pDoc->m_systemSettingsData.m_bAutoSave)
        {
            if (MessageBox("�����Ƿ񱣴浱ǰ�����ļ���","����",  MB_YESNO) == IDYES)
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
