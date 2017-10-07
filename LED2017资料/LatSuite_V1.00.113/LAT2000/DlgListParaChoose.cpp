// DlgListParaChoose.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DlgListParaChoose.h"
#include "afxdialogex.h"


// CDlgListParaChoose 对话框

IMPLEMENT_DYNAMIC(CDlgListParaChoose, CDialogEx)

CDlgListParaChoose::CDlgListParaChoose(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgListParaChoose::IDD, pParent)
{

}

CDlgListParaChoose::~CDlgListParaChoose()
{
}

void CDlgListParaChoose::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_ADD, m_cAdd);
    DDX_Control(pDX, IDC_REMOVE, m_cRemove);
    DDX_Control(pDX, IDC_LIST_NOT, m_cListNot);
    DDX_Control(pDX, IDC_LIST_YES, m_cListYes);
}


BEGIN_MESSAGE_MAP(CDlgListParaChoose, CDialogEx)
    ON_BN_CLICKED(IDC_ADD, &CDlgListParaChoose::OnBnClickedAdd)
    ON_BN_CLICKED(IDC_REMOVE, &CDlgListParaChoose::OnBnClickedRemove)
    ON_LBN_SELCHANGE(IDC_LIST_NOT, &CDlgListParaChoose::OnLbnSelchangeListNot)
    ON_LBN_SELCHANGE(IDC_LIST_YES, &CDlgListParaChoose::OnLbnSelchangeListYes)
    ON_BN_CLICKED(IDC_BUTTON_ALL, &CDlgListParaChoose::OnBnClickedButtonAll)
    ON_BN_CLICKED(IDC_BUTTON_NOT, &CDlgListParaChoose::OnBnClickedButtonNot)
END_MESSAGE_MAP()


// CDlgListParaChoose 消息处理程序


BOOL CDlgListParaChoose::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    RelistNot();
    RelistYes();
    EnableButton();
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}


void CDlgListParaChoose::EnableButton(void)
{
    m_cAdd.EnableWindow(m_cListNot.GetCount() != 0);
    m_cRemove.EnableWindow(m_cListYes.GetCount() != 0);
}


void CDlgListParaChoose::RelistNot()
{
    m_iNotNum = 0;
    m_cListNot.ResetContent();
    for (int i = 0; i < PARA_NUM; i ++)
    {
        if (!g_bListPara[i])
        {
            m_cListNot.AddString(g_strListParaName[i]);
            m_iNotSN[m_iNotNum]		= i;
            m_bNotSNSel[m_iNotNum]	= 0;
            m_iNotNum++;
        }
    }
}


void CDlgListParaChoose::RelistYes()
{
    m_iYesNum = 0;
    m_cListYes.ResetContent();
    for (int i = 0; i < PARA_NUM; i ++)
    {
        if (g_bListPara[i])
        {
            m_cListYes.AddString(g_strListParaName[i]);
            m_iYesSN[m_iYesNum]		= i; 
            m_bYesSNSel[m_iYesNum]	= 0;
            m_iYesNum ++;
        }
    }
}


void CDlgListParaChoose::OnBnClickedAdd()
{
    // TODO: 在此添加控件通知处理程序代码
    for (int i = 0; i < m_iNotNum; i ++)
    {
        if (m_bNotSNSel[i] != 0)
        {
            g_bListPara[m_iNotSN[i]] =  TRUE;
        }
    }
    RelistNot();
    RelistYes();

    EnableButton();
}


void CDlgListParaChoose::OnBnClickedRemove()
{

    // TODO: 在此添加控件通知处理程序代码
    for (int i = 0; i < m_iYesNum; i ++)
    {
        if (m_bYesSNSel[i] != 0)
        {
            g_bListPara[m_iYesSN[i]] = FALSE;
        }
    }
    RelistNot();
    RelistYes();

    EnableButton();
}


void CDlgListParaChoose::OnLbnSelchangeListNot()
{
    // TODO: 在此添加控件通知处理程序代码
    for (int i = 0; i < m_iNotNum; i ++)
    {
        m_bNotSNSel[i] = m_cListNot.GetSel(i);
    }
}


void CDlgListParaChoose::OnLbnSelchangeListYes()
{
    // TODO: 在此添加控件通知处理程序代码
    for (int i = 0; i < m_iYesNum; i ++)
    {
        m_bYesSNSel[i] = m_cListYes.GetSel(i);
    }
}


void CDlgListParaChoose::OnBnClickedButtonAll()
{
    // TODO: 在此添加控件通知处理程序代码
    for (int i = 0; i < PARA_NUM; i ++)
    {
       g_bListPara[i] = TRUE;		
    }
    RelistNot();
    RelistYes();

    EnableButton();
}


void CDlgListParaChoose::OnBnClickedButtonNot()
{
    // TODO: 在此添加控件通知处理程序代码
    for (int i = 0; i < PARA_NUM; i ++)
    {
        g_bListPara[i] = FALSE;		
    }
    RelistNot();
    RelistYes();

    EnableButton();
}



