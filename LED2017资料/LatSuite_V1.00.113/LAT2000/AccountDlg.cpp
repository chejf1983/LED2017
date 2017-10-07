// AccountDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "AccountDlg.h"
#include "afxdialogex.h"


// CAccountDlg 对话框

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


// CAccountDlg 消息处理程序


void CAccountDlg::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    if (m_iExecutionLevel == HIGH_EXECUTION_LEVEL)
    {            
        if (m_strHighExcutionPassword != GetHighExcutionPassword()
            && m_strHighExcutionPassword != GetAdminExcutionPassword())
        {
            m_iLabel.put_Caption("输入密码错误!");
            return;
        }

    }
    else if(m_iExecutionLevel == ADMIN_EXECUTION_LEVEL)
    {
        if (m_strAdminExcutionPassword != GetAdminExcutionPassword())
        {
            m_iLabel.put_Caption("输入密码错误!");
            return;
        }    
    }
    CDialogEx::OnOK();
}


BOOL CAccountDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    m_iLabel.put_Caption("");

    UpdateData(FALSE);
    Enable();
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}


void CAccountDlg::OnBnClickedHighExecutionLevel()
{
    // TODO: 在此添加控件通知处理程序代码
    Enable();
}


void CAccountDlg::OnBnClickedAdminExecutionLevel()
{
    // TODO: 在此添加控件通知处理程序代码
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
