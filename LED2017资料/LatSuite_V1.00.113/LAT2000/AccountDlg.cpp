// AccountDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "AccountDlg.h"
#include "afxdialogex.h"


// CAccountDlg �Ի���

IMPLEMENT_DYNAMIC(CAccountDlg, CDialogEx)

extern CString GetAdminExcutionPassword();
extern CString GetHighExcutionPassword();
CAccountDlg::CAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAccountDlg::IDD, pParent)
{

    m_iExecutionLevel = 0;
    m_strAdminExcutionPassword = _T("");
    m_strHighExcutionPassword = _T("");   
    CString str_m_iExecutionLevel = _T("m_iExecutionLevel");
    CString strSection = "CAccountDlg" ;

    m_iExecutionLevel = AfxGetApp()->GetProfileInt(strSection, str_m_iExecutionLevel, 0);

  
}

CAccountDlg::~CAccountDlg()
{
    CString str_m_iExecutionLevel = _T("m_iExecutionLevel");
    CString strSection = "CAccountDlg" ;

    AfxGetApp()->WriteProfileInt(strSection, str_m_iExecutionLevel, m_iExecutionLevel);
}

void CAccountDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Radio(pDX, IDC_LOW_EXECUTION_LEVEL, m_iExecutionLevel);
    DDX_Text(pDX, IDC_EDIT_ADMIN_EXECUTION_PASSWORD, m_strAdminExcutionPassword);
    DDX_Text(pDX, IDC_EDIT_HIGH_EXECUTION_PASSWORD, m_strHighExcutionPassword);
    DDX_Control(pDX, IDC_ILABELX1, m_iLabel);
}


BEGIN_MESSAGE_MAP(CAccountDlg, CDialogEx)
    ON_BN_CLICKED(IDOK, &CAccountDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDC_HIGH_EXECUTION_LEVEL, &CAccountDlg::OnBnClickedHighExecutionLevel)
    ON_BN_CLICKED(IDC_ADMIN_EXECUTION_LEVEL, &CAccountDlg::OnBnClickedAdminExecutionLevel)
END_MESSAGE_MAP()


// CAccountDlg ��Ϣ�������


void CAccountDlg::OnBnClickedOk()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);
    if (m_iExecutionLevel == HIGH_EXECUTION_LEVEL)
    {            
        if (m_strHighExcutionPassword != GetHighExcutionPassword()
            && m_strHighExcutionPassword != GetAdminExcutionPassword())
        {
            m_iLabel.put_Caption("�����������!");
            return;
        }

    }
    else if(m_iExecutionLevel == ADMIN_EXECUTION_LEVEL)
    {
        if (m_strAdminExcutionPassword != GetAdminExcutionPassword())
        {
            m_iLabel.put_Caption("�����������!");
            return;
        }    
    }
    CDialogEx::OnOK();
}


BOOL CAccountDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    m_iLabel.put_Caption("");

    UpdateData(FALSE);
    Enable();
    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}


void CAccountDlg::OnBnClickedHighExecutionLevel()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    Enable();
}


void CAccountDlg::OnBnClickedAdminExecutionLevel()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    Enable();

}


void CAccountDlg::Enable(void)
{
    UpdateData(TRUE);
    GetDlgItem(IDC_EDIT_ADMIN_EXECUTION_PASSWORD)
        ->EnableWindow(ADMIN_EXECUTION_LEVEL == m_iExecutionLevel);
    GetDlgItem(IDC_EDIT_HIGH_EXECUTION_PASSWORD)
        ->EnableWindow(HIGH_EXECUTION_LEVEL == m_iExecutionLevel);
}
