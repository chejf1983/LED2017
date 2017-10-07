// StatisticParaChooseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "StatisticParaChooseDlg.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"


// CStatisticParaChooseDlg 对话框

IMPLEMENT_DYNAMIC(CStatisticParaChooseDlg, CDialogEx)

enum StatisticParaIndex;

CStatisticParaChooseDlg::CStatisticParaChooseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStatisticParaChooseDlg::IDD, pParent)
{
    m_iNotNum = 0;
    m_iYesNum = 0;
}

CStatisticParaChooseDlg::~CStatisticParaChooseDlg()
{
}

void CStatisticParaChooseDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_ADD, m_cAdd);
    DDX_Control(pDX, IDC_REMOVE, m_cRemove);
    DDX_Control(pDX, IDC_LIST_NOT, m_cListNot);
    DDX_Control(pDX, IDC_LIST_YES, m_cListYes);
}


BEGIN_MESSAGE_MAP(CStatisticParaChooseDlg, CDialogEx)
    ON_BN_CLICKED(IDC_ADD, &CStatisticParaChooseDlg::OnBnClickedAdd)
    ON_BN_CLICKED(IDC_REMOVE, &CStatisticParaChooseDlg::OnBnClickedRemove)
    ON_LBN_SELCHANGE(IDC_LIST_NOT, &CStatisticParaChooseDlg::OnLbnSelchangeListNot)
    ON_LBN_SELCHANGE(IDC_LIST_YES, &CStatisticParaChooseDlg::OnLbnSelchangeListYes)
	ON_BN_CLICKED(IDC_BUTTON_ALL, &CStatisticParaChooseDlg::OnBnClickedButtonAll)
	ON_BN_CLICKED(IDC_BUTTON_NOT, &CStatisticParaChooseDlg::OnBnClickedButtonNot)
END_MESSAGE_MAP()


// CStatisticParaChooseDlg 消息处理程序


BOOL CStatisticParaChooseDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    RelistNot();
    RelistYes();
    EnableButton();


    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}



void CStatisticParaChooseDlg::RelistNot()
{
    m_iNotNum = 0;
    m_cListNot.ResetContent();
    for (int i = 0; i < g_pDoc->m_StatisticLedDataContainer.GetCanStatisticParaNum(); i ++)
    {
        if (!g_pDoc->m_StatisticLedDataContainer.IsSelectedToStatistic(i))
        {
            m_cListNot.AddString(g_pDoc->m_StatisticLedDataContainer.GetStatisticParaName(StatisticParaIndex(i), 0));
            m_iNotSN[m_iNotNum] = i;
			m_bNotSNSel[m_iNotNum] = 0;
            m_iNotNum ++;
        }
    }
}


void CStatisticParaChooseDlg::RelistYes()
{  
    m_iYesNum = 0;
    m_cListYes.ResetContent();
    for (int i = 0; i < g_pDoc->m_StatisticLedDataContainer.GetCanStatisticParaNum(); i ++)
    {
        if (g_pDoc->m_StatisticLedDataContainer.IsSelectedToStatistic(i))
        {
            m_cListYes.AddString(g_pDoc->m_StatisticLedDataContainer.GetStatisticParaName(StatisticParaIndex(i), 0));
            m_iYesSN[m_iYesNum] = i; 
			m_bYesSNSel[m_iYesNum] = 0;
            m_iYesNum ++;
        }
    }
}

void CStatisticParaChooseDlg::OnBnClickedAdd()
{
    // TODO: 在此添加控件通知处理程序代码
    for (int i = 0; i < m_iNotNum; i ++)
    {
        if (m_bNotSNSel[i] != 0)
        {
            g_pDoc->m_StatisticLedDataContainer.SetbStatisticPara(m_iNotSN[i], TRUE);
        }
    }
    RelistNot();
    RelistYes();

    EnableButton();
}


void CStatisticParaChooseDlg::OnBnClickedRemove()
{

    // TODO: 在此添加控件通知处理程序代码
    for (int i = 0; i < m_iYesNum; i ++)
    {
        if (m_bYesSNSel[i] != 0)
        {
            g_pDoc->m_StatisticLedDataContainer.SetbStatisticPara(m_iYesSN[i], FALSE);
        }
    }
    RelistNot();
    RelistYes();

    EnableButton();
}


void CStatisticParaChooseDlg::OnLbnSelchangeListNot()
{
    // TODO: 在此添加控件通知处理程序代码
    for (int i = 0; i < m_iNotNum; i ++)
    {
        m_bNotSNSel[i] = m_cListNot.GetSel(i);
    }
}


void CStatisticParaChooseDlg::OnLbnSelchangeListYes()
{
    // TODO: 在此添加控件通知处理程序代码
    for (int i = 0; i < m_iYesNum; i ++)
    {
        m_bYesSNSel[i] = m_cListYes.GetSel(i);
    }
}


void CStatisticParaChooseDlg::EnableButton(void)
{
    m_cAdd.EnableWindow(m_cListNot.GetCount() != 0);
    m_cRemove.EnableWindow(m_cListYes.GetCount() != 0);
}


void CStatisticParaChooseDlg::OnBnClickedButtonAll()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < g_pDoc->m_StatisticLedDataContainer.GetCanStatisticParaNum(); i ++)
	{
		g_pDoc->m_StatisticLedDataContainer.SetbStatisticPara(i, TRUE);		
	}
	RelistNot();
	RelistYes();

	EnableButton();
}


void CStatisticParaChooseDlg::OnBnClickedButtonNot()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < g_pDoc->m_StatisticLedDataContainer.GetCanStatisticParaNum(); i ++)
	{
		g_pDoc->m_StatisticLedDataContainer.SetbStatisticPara(i, FALSE);		
	}
	RelistNot();
	RelistYes();

	EnableButton();
}
