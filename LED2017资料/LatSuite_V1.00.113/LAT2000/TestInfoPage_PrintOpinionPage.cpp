// DlgPrintOpinion.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "afxdialogex.h"
#include "TestInfoPage_PrintOpinionPage.h"

// CTestInfoPage_PrintOpinionPage 对话框


IMPLEMENT_DYNAMIC(CTestInfoPage_PrintOpinionPage, CPropertyPage)



extern CString g_strCurrentPath;
CTestInfoPage_PrintOpinionPage::CTestInfoPage_PrintOpinionPage()
    : CPropertyPage(CTestInfoPage_PrintOpinionPage::IDD)

{

    m_iPageHeadLogoPos = 0;
    m_strPrintCap = _T("");
    m_strPageHeadCap = _T("");
    m_strPageHeadCapInfo = _T("");
    m_strPrintSubCap = _T("");
}

CTestInfoPage_PrintOpinionPage::~CTestInfoPage_PrintOpinionPage()
{
}

void CTestInfoPage_PrintOpinionPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK_PRINT_LOGO, m_bPrintPageHeadLogo);
    DDX_CBIndex(pDX, IDC_COMBO_POS, m_iPageHeadLogoPos);
    DDX_Text(pDX, IDC_EDIT_PRINT_T, m_strPrintCap);
    DDX_Control(pDX, IDC_STATIC_LOGO, m_cModify_Logo);
    DDX_Control(pDX, IDC_COMBO_POS, m_ccomPos);
    DDX_Text(pDX, IDC_EDIT_PAGE_HEAD_CAP, m_strPageHeadCap);
    DDX_Text(pDX, IDC_EDIT_PAGE_HEAD_INFO, m_strPageHeadCapInfo);
    DDX_Text(pDX, IDC_EDIT_PRINT_T2, m_strPrintSubCap);
    DDX_Check(pDX, IDC_CHECK_PRINT_SUBCAP, m_bPrintSubCap);
}


BEGIN_MESSAGE_MAP(CTestInfoPage_PrintOpinionPage, CPropertyPage)
    ON_BN_CLICKED(IDC_STATIC_LOGO, &CTestInfoPage_PrintOpinionPage::OnStaticLogo)
    ON_BN_CLICKED(IDC_CHECK_PRINT_LOGO, &CTestInfoPage_PrintOpinionPage::OnBnClickedCheckPrintLogo)
    ON_BN_CLICKED(IDC_CHECK_PRINT_SUBCAP, &CTestInfoPage_PrintOpinionPage::OnBnClickedCheckPrintSubcap)
END_MESSAGE_MAP()


// CTestInfoPage_PrintOpinionPage 消息处理程序


void CTestInfoPage_PrintOpinionPage::OnStaticLogo()
{
    // TODO: 在此添加控件通知处理程序代码
    CString strTemp;
    strTemp = g_strCurrentPath + _T("logo.bmp");   
    MSPAINT(strTemp);	
}



BOOL CTestInfoPage_PrintOpinionPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    // TODO:  在此添加额外的初始化
    m_cModify_Logo.SetLink(TRUE)
        .SetTextColor(RGB(0, 0, 255))
        .SetFontUnderline(TRUE)
        .SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND_CUR));
    CFont *Font = GetFont();
    m_cModify_Logo.SetFont(Font);
    m_cModify_Logo.SetFontSize(16);
    m_ccomPos.EnableWindow(m_bPrintPageHeadLogo);
    GetDlgItem(IDC_EDIT_PAGE_HEAD_CAP)->EnableWindow(m_bPrintSubCap);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}


void CTestInfoPage_PrintOpinionPage::OnBnClickedCheckPrintLogo()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_ccomPos.EnableWindow(m_bPrintPageHeadLogo);
}







void CTestInfoPage_PrintOpinionPage::MSPAINT(CString strPathName)
{
    CString sStr;
    char a[256];
    GetSystemDirectory(a,256);
    CString sSystemPath=a;
    sSystemPath=sSystemPath.Left(2);

    //Windows 98
    sStr=sSystemPath;
    sStr=sStr+"\\Program Files\\Accessories\\MSPAINT.EXE "+strPathName;
    if(::WinExec(sStr,SW_SHOWDEFAULT)>=31)
    {
    }

    //Windows 20000
    sStr=sSystemPath;
    sStr=sStr+"\\WinNT\\System32\\MSPAINT.EXE "+strPathName;
    if(::WinExec(sStr,SW_SHOWDEFAULT)>=31)
    {
    }

    //Windows XP
    sStr=sSystemPath;
    sStr=sStr+"\\Windows\\System32\\MSPAINT.EXE "+ "\"" + strPathName + "\" -L -S";
    if(::WinExec(sStr,SW_SHOWDEFAULT)>=31)
    {
    }
}


void CTestInfoPage_PrintOpinionPage::OnBnClickedCheckPrintSubcap()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    GetDlgItem(IDC_EDIT_PRINT_T2)->EnableWindow(m_bPrintSubCap);
}


