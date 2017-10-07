// DebugScanerPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DebugScanerPage.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"

// CDebugScanerPage �Ի���

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

// CDebugScanerPage ��Ϣ�������

void CDebugScanerPage::OnCbnSelchangeComboCom()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);
    g_ScanerComm.Initialize(m_strCOM);
}

void CDebugScanerPage::OnBnClickedButtonStartScaner()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);
    m_bStopScaner = FALSE;
    m_cScaner.ResetContent();
    AfxBeginThread(ThreadScaner, this);
}

void CDebugScanerPage::OnBnClickedButtonStopScaner()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
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

			//���͸�������
        }
        else
        {
			if (SCAN_FAIL == iR)
			{
				AfxMessageBox("ɨ��ʧ��,���鴮���Ƿ���ȷ!");
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

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    GetDlgItem(IDC_BUTTON_START_SCANER)->EnableWindow(m_bStopScaner);
    GetDlgItem(IDC_BUTTON_STOP_SCANER)->EnableWindow(!m_bStopScaner);

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}

void CDebugScanerPage::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
