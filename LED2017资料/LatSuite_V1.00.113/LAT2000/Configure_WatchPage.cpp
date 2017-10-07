// Configure_WatchPage.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "Configure_WatchPage.h"
#include "afxdialogex.h"
#include "MyDockablePaneData.h"
extern CMyDockablePaneData g_myDockablePaneData;

// CConfigure_WatchPage 对话框

IMPLEMENT_DYNAMIC(CConfigure_WatchPage, CPropertyPage)

CConfigure_WatchPage::CConfigure_WatchPage()
	: CPropertyPage(CConfigure_WatchPage::IDD)
{
    m_ucGaugeAddress.SetSize(g_iGaugeNum);
    m_ucTemperatureAddress.SetSize(g_iTMPControlNum);
    m_strTMPControlName = _T("");
    m_strGaugeName = _T("");     
}

CConfigure_WatchPage::~CConfigure_WatchPage()
{
}

void CConfigure_WatchPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK_GAUGE, m_bGauge);
    DDX_Check(pDX, IDC_CHECK_TEMPERATURE_CONTROLLER, m_bTemperatureController);
    DDX_CBString(pDX, IDC_COMBO_GAUGE_COM, m_strGaugeCOM);
    DDX_CBString(pDX, IDC_COMBO_TEMPERATURE_CONTROLLER_COM, m_strTemperatureContrllerCOM);
    DDX_Text(pDX, IDC_EDIT_GAUGE_ADDRESS, m_ucCurSelGaugeAddress);
    DDX_Text(pDX, IDC_EDIT_TEMPERATURE_CONTROLLER_ADDRESS, m_ucCurSelTemperatureContrllerAddress);
    DDX_Control(pDX, IDC_LIST_TEMPERATURE_CONTROLLER, m_cListTMP);
    DDX_Control(pDX, IDC_LIST_GAUGE, m_cListGauge);
	DDX_Text(pDX, IDC_EDIT_TEMPERATURE_NAME, m_strTMPControlName);
    DDX_Text(pDX, IDC_EDIT_GAUGE_NAME, m_strGaugeName);
}


BEGIN_MESSAGE_MAP(CConfigure_WatchPage, CPropertyPage)
    ON_BN_CLICKED(IDC_BUTTON_TEMPERATURE_CONTROLLER, &CConfigure_WatchPage::OnBnClickedButtonTemperatureController)
    ON_BN_CLICKED(IDC_BUTTONIT_GAUGE, &CConfigure_WatchPage::OnBnClickedButtonitGauge)
    ON_BN_CLICKED(IDC_MODIFY_TEMPERATURE_CONTROLLER_ADDRESS, &CConfigure_WatchPage::OnBnClickedModifyTemperatureControllerAddress)
    ON_BN_CLICKED(IDC_MODIFY_GAUGE_ADDRESS, &CConfigure_WatchPage::OnBnClickedModifyGaugeAddress)
    ON_NOTIFY(NM_CLICK, IDC_LIST_TEMPERATURE_CONTROLLER, &CConfigure_WatchPage::OnNMClickListTemperatureController)
    ON_NOTIFY(NM_CLICK, IDC_LIST_GAUGE, &CConfigure_WatchPage::OnNMClickListGauge)
END_MESSAGE_MAP()


// CConfigure_WatchPage 消息处理程序


void CConfigure_WatchPage::OnBnClickedButtonTemperatureController()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);

    g_FujiTMPComm.Initialize(m_strTemperatureContrllerCOM);
    float fT;
	int nAlarm;
    if (g_FujiTMPComm.ReadTemperature(m_ucCurSelTemperatureContrllerAddress, fT, nAlarm))
    {
        AfxMessageBox("试通成功！");
    }
    else
    {
        AfxMessageBox("试通失败！");
    }
}


void CConfigure_WatchPage::OnBnClickedButtonitGauge()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);

    g_GaugeComm.Initialize(m_strGaugeCOM);
    float f1, f2, f3;
    if (g_GaugeComm.Read3(m_ucCurSelGaugeAddress, f1, f2, f3))
    {
        AfxMessageBox("试通成功！");
    }
    else
    {
        AfxMessageBox("试通失败！");
    }
}


void CConfigure_WatchPage::OnBnClickedModifyTemperatureControllerAddress()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_ucTemperatureAddress[m_iSelTMPControl] = m_ucCurSelTemperatureContrllerAddress;
    ListTMPAdress();
}


void CConfigure_WatchPage::OnBnClickedModifyGaugeAddress()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_ucGaugeAddress[m_iSelGauge] = m_ucCurSelGaugeAddress;
    ListGaugeAdress();

}


BOOL CConfigure_WatchPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    // TODO:  在此添加额外的初始化
    m_cListTMP.ModifyStyle(0,LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS|LVS_NOSORTHEADER);
    m_cListTMP.SetExtendedStyle(m_cListTMP.GetExtendedStyle()  | 
        LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES| LVS_EX_HEADERDRAGDROP);
    m_cListTMP.SetBkColor(RGB(232, 255, 255));
    m_cListTMP.SetTextColor(RGB(128, 0, 64));
    m_cListTMP.SetTextBkColor(RGB(232, 255, 255));

    m_cListGauge.ModifyStyle(0,LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS|LVS_NOSORTHEADER);
    m_cListGauge.SetExtendedStyle(m_cListGauge.GetExtendedStyle()  | 
        LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES| LVS_EX_HEADERDRAGDROP);
    m_cListGauge.SetBkColor(RGB(232, 255, 255));
    m_cListGauge.SetTextColor(RGB(128, 0, 64));
    m_cListGauge.SetTextBkColor(RGB(232, 255, 255));
    ListTMPAdress();
    ListGaugeAdress();
    m_cListTMP.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
    m_cListTMP.EnsureVisible(0, FALSE);	
    m_cListGauge.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
    m_cListGauge.EnsureVisible(0, FALSE);	
    m_iSelTMPControl = 0;
    m_iSelGauge = 0;
    m_strTMPControlName = g_myDockablePaneData.m_strTemperatureControllerText[m_iSelTMPControl];
    m_strGaugeName = g_myDockablePaneData.m_strRegionText[m_iSelGauge];   
    m_ucCurSelTemperatureContrllerAddress = m_ucTemperatureAddress[m_iSelTMPControl];
    m_ucCurSelGaugeAddress = m_ucGaugeAddress[m_iSelGauge];
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void  CConfigure_WatchPage::ListTMPAdress()
{
    m_cListTMP.DeleteAllItems();
    while(1)
    {
        if (m_cListTMP.DeleteColumn(0) == FALSE)
        {
            break;
        }
    }
    int iN = 0;
    CString strTemp;
    strTemp = _T("温控名称");
    m_cListTMP.InsertColumn(iN,strTemp);
    m_cListTMP.SetColumnWidth(iN,130);
    iN ++;
    strTemp = _T("地址");
    m_cListTMP.InsertColumn(iN,strTemp);
    m_cListTMP.SetColumnWidth(iN,90); 
    for (int i = 0; i < g_myDockablePaneData.m_TemperatureController.GetSize(); i ++)
    {   
        iN = 0;  
        m_cListTMP.InsertItem(i,strTemp);
        m_cListTMP.SetItemText(i, iN, g_myDockablePaneData.m_strTemperatureControllerText[i]);
        iN ++;
        strTemp.Format(_T("0x%x"), m_ucTemperatureAddress[i]);
        m_cListTMP.SetItemText(i, iN, strTemp);
    }
}

void  CConfigure_WatchPage::ListGaugeAdress()
{
    m_cListGauge.DeleteAllItems();
    while(1)
    {
        if (m_cListGauge.DeleteColumn(0) == FALSE)
        {
            break;
        }
    }
    int iN = 0;
    CString strTemp;
    strTemp = _T("表头区域名称");
    m_cListGauge.InsertColumn(iN,strTemp);
    m_cListGauge.SetColumnWidth(iN,130);
    iN ++;
    strTemp = _T("地址");
    m_cListGauge.InsertColumn(iN,strTemp);
    m_cListGauge.SetColumnWidth(iN,90); 
    for (int i = 0; i < g_myDockablePaneData.m_dataRegion.GetSize(); i ++)
    {   
        iN = 0;  
        m_cListGauge.InsertItem(i,strTemp);
        m_cListGauge.SetItemText(i, iN, g_myDockablePaneData.m_strRegionText[i]);
        iN ++;
        strTemp.Format(_T("0x%x"), m_ucGaugeAddress[i]);
        m_cListGauge.SetItemText(i, iN, strTemp);
    }
}


void CConfigure_WatchPage::OnNMClickListTemperatureController(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    m_iSelTMPControl = pNMListView->iItem;
    m_strTMPControlName = g_myDockablePaneData.m_strTemperatureControllerText[m_iSelTMPControl];
    m_ucCurSelTemperatureContrllerAddress = m_ucTemperatureAddress[m_iSelTMPControl];
    UpdateData(FALSE);
    *pResult = 0;
}


void CConfigure_WatchPage::OnNMClickListGauge(NMHDR *pNMHDR, LRESULT *pResult)
{
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;   
    m_iSelGauge = pNMListView->iItem;
    m_strGaugeName = g_myDockablePaneData.m_strRegionText[m_iSelGauge];
    m_ucCurSelGaugeAddress = m_ucGaugeAddress[m_iSelGauge];
    UpdateData(FALSE);
    *pResult = 0;
}
