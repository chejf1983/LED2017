// AlarmSettingsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "AlarmSettingsDlg.h"
#include "afxdialogex.h"
#include "MyDockablePaneData.h"
#include "LAT2000Doc.h"

extern CMyDockablePaneData g_myDockablePaneData;
// CAlarmSettingsDlg 对话框

IMPLEMENT_DYNAMIC(CAlarmSettingsDlg, CDialogEx)

CAlarmSettingsDlg::CAlarmSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAlarmSettingsDlg::IDD, pParent)
{
	m_fCurCurrentH	= 0.0f;
	m_fCurCurrentL	= 0.0f;	
	m_fCurPowerH	= 0.0f;
	m_fCurPowerL	= 0.0f;

	m_fCurTMPH		= 0.0f;
	m_fCurTMPL		= 0.0f;
	m_fCurTMPOPEN	= 0.0f;
	m_fCurVoltageH = 0.0f;
	m_fCurVoltageL = 0.0f;

	m_iCurTMPRingIndex = 0;  
	m_iCurRegionRingIndex = 0;

	m_iLampTooHighRingIndex = 0;
	m_iManualStopRingIndex	= 0;
	m_bLowELorDisOnly		= FALSE;
	m_iListRegionIndex		= -1;
	m_iListTMPIndex			= -1;
	m_strRegionName			= _T("");
	m_strTMPControlName		= _T("");

	m_fCurrentH.SetSize(g_iGaugeNum);
	m_fCurrentL.SetSize(g_iGaugeNum);
	m_fPowerH.SetSize(g_iGaugeNum);
	m_fPowerL.SetSize(g_iGaugeNum);
	m_fVoltageH.SetSize(g_iGaugeNum);
	m_fVoltageL.SetSize(g_iGaugeNum);
	m_bRegion.SetSize(g_iGaugeNum);
	m_iRegionRingIndex.SetSize(g_iGaugeNum);


	m_fTMPH.SetSize(g_iTMPControlNum);
	m_fTMPL.SetSize(g_iTMPControlNum);
	m_fTMPOPEN.SetSize(g_iTMPControlNum);
	m_bTMP.SetSize(g_iTMPControlNum);
	m_iTMPRingIndex.SetSize(g_iTMPControlNum);
}

CAlarmSettingsDlg::~CAlarmSettingsDlg()
{
}

void CAlarmSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_STOP_TEST, m_bStopTest);
	DDX_Check(pDX, IDC_CHECK_REGION, m_bCurRegion);
	DDX_Text(pDX, IDC_EDIT_CURRENT_H, m_fCurCurrentH);
	DDX_Text(pDX, IDC_EDIT_CURRENT_L, m_fCurCurrentL);
	DDX_Text(pDX, IDC_EDIT_POWER_H, m_fCurPowerH);
	DDX_Text(pDX, IDC_EDIT_POWER_L, m_fCurPowerL);
	DDX_Text(pDX, IDC_EDIT_VOLTAGE_H, m_fCurVoltageH);
	DDX_Text(pDX, IDC_EDIT_VOLTAGE_L, m_fCurVoltageL);
	DDX_Control(pDX, IDC_COMBO_RING_REGION, m_cComboRegion);
	DDX_CBIndex(pDX, IDC_COMBO_RING_REGION, m_iCurRegionRingIndex);
	DDX_Control(pDX, IDC_CHECK_REGION, m_btCurRegionAlarm);
	DDX_Control(pDX, IDC_EDIT_CURRENT_H, m_cCurCurrentH);
	DDX_Control(pDX, IDC_EDIT_CURRENT_L, m_cCurCurrentL);
	DDX_Control(pDX, IDC_EDIT_POWER_H, m_cCurPowerH);
	DDX_Control(pDX, IDC_EDIT_POWER_L, m_cCurPowerL);
	DDX_Control(pDX, IDC_EDIT_VOLTAGE_H, m_cCurVoltageH);
	DDX_Control(pDX, IDC_EDIT_VOLTAGE_L, m_cCurVoltageL);
	DDX_Check(pDX, IDC_CHECK_TMP, m_bCurTMP);
	DDX_Text(pDX, IDC_EDIT_TMP_H, m_fCurTMPH);
	DDX_Text(pDX, IDC_EDIT_TMP_L, m_fCurTMPL);
	DDX_CBIndex(pDX, IDC_COMBO_RING_TMP, m_iCurTMPRingIndex);
	DDX_Control(pDX, IDC_COMBO_RING_TMP, m_cComboTMP);
	DDX_Control(pDX, IDC_CHECK_TMP, m_btCurTMPAlarm);
	DDX_Control(pDX, IDC_EDIT_TMP_H, m_cCurTMPH);
	DDX_Control(pDX, IDC_EDIT_TMP_L, m_cCurTMPL);
	DDX_Control(pDX, IDC_COMBO_RING_LAMP_TOO_HIGH, m_cComboLampTooHigh);
	DDX_Control(pDX, IDC_COMBO_RING_MANUAL_STOP, m_cComboManualStop);
	DDX_CBIndex(pDX, IDC_COMBO_RING_LAMP_TOO_HIGH, m_iLampTooHighRingIndex);
	DDX_CBIndex(pDX, IDC_COMBO_RING_MANUAL_STOP, m_iManualStopRingIndex);
	DDX_Check(pDX, IDC_CHECK_SCANER_OVERTIME, m_bScanerOverTimeAlarm);
	DDX_CBIndex(pDX, IDC_COMBO_RING_SCANER_OVERTIME, m_iScanerOverTimeRingIndex);
	DDX_Control(pDX, IDC_COMBO_RING_SCANER_OVERTIME, m_cScanerOverTime);
	DDX_Check(pDX, IDC_CHECK_LAMP_TOO_HIGH, m_bLampTooHigh);
	DDX_Check(pDX, IDC_CHECK_MANUAL_STOP, m_bManualStop);
	DDX_Control(pDX, IDC_LIST_REGION, m_cListRegion);
	DDX_Control(pDX, IDC_LIST_TMP, m_cListTMP);
	DDX_Text(pDX, IDC_EDIT_REGION_NAME, m_strRegionName);
	DDX_Text(pDX, IDC_EDIT_TMPCTRL_NAME, m_strTMPControlName);
	DDX_Control(pDX, IDC_EDIT_TMP_OPEN, m_cTmpOpen);
	DDX_Text(pDX, IDC_EDIT_TMP_OPEN, m_fCurTMPOPEN);
}


BEGIN_MESSAGE_MAP(CAlarmSettingsDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAlarmSettingsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_REGION, &CAlarmSettingsDlg::OnBnClickedCheckRegion)
	ON_BN_CLICKED(IDC_CHECK_TMP, &CAlarmSettingsDlg::OnBnClickedCheckTmp)
	ON_BN_CLICKED(IDC_CHECK_LAMP_TOO_HIGH, &CAlarmSettingsDlg::OnBnClickedCheckLampTooHigh)
	ON_BN_CLICKED(IDC_CHECK_MANUAL_STOP, &CAlarmSettingsDlg::OnBnClickedCheckManualStop)
    ON_BN_CLICKED(IDC_CHECK_SCANER_OVERTIME, &CAlarmSettingsDlg::OnBnClickedCheckScanerOvertime)
    ON_NOTIFY(NM_CLICK, IDC_LIST_REGION, &CAlarmSettingsDlg::OnNMClickListRegion)
    ON_NOTIFY(NM_CLICK, IDC_LIST_TMP, &CAlarmSettingsDlg::OnNMClickListTmp)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_BUTTON_CHANGE_REGION, &CAlarmSettingsDlg::OnBnClickedButtonChangeRegion)
    ON_BN_CLICKED(IDC_BUTTON_CHANGE_TMP, &CAlarmSettingsDlg::OnBnClickedButtonChangeTmp)
END_MESSAGE_MAP()


// CAlarmSettingsDlg 消息处理程序


void CAlarmSettingsDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


BOOL CAlarmSettingsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	
	// Insert ring data
    LOW_EXECUTION_LEVEL ==  g_iExecutionLevel || TRUE == g_bDisplayLimitOnly ?
        m_bLowELorDisOnly = TRUE : m_bLowELorDisOnly = FALSE; 
	m_cComboLampTooHigh.AddString("Default");
	m_cComboManualStop.AddString("Default");
	m_cComboTMP.AddString("Default");
	m_cComboRegion.AddString("Default");
    m_cScanerOverTime.AddString("Default");

	if (NULL != g_pDoc)
	{
		for (int i = 0; i < g_pDoc->m_AlarmRingData.GetRingCount(); i++)
		{
			m_cComboLampTooHigh.AddString(g_pDoc->m_AlarmRingData.GetRingInfoString(i));
			m_cComboManualStop.AddString(g_pDoc->m_AlarmRingData.GetRingInfoString(i));
			m_cComboTMP.AddString(g_pDoc->m_AlarmRingData.GetRingInfoString(i));
			m_cComboRegion.AddString(g_pDoc->m_AlarmRingData.GetRingInfoString(i));
            m_cScanerOverTime.AddString(g_pDoc->m_AlarmRingData.GetRingInfoString(i));
		}
	}
	UpdateData(FALSE);
	SetEnable();
	EnaleControls_bDisor_LowExecu();
    if (!g_pDoc->m_CommSettingsData.m_bHaveScaner)
    {
        GetDlgItem(IDC_STATIC_SCANER)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHECK_SCANER_OVERTIME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_RING_SCANER_OVERTIME)->ShowWindow(SW_HIDE);
    }      

    m_cListTMP.ModifyStyle(0,LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS|LVS_NOSORTHEADER);
    LOW_EXECUTION_LEVEL ==  g_iExecutionLevel || TRUE == g_bDisplayLimitOnly?
        m_cListTMP.SetExtendedStyle(m_cListTMP.GetExtendedStyle()  | 
        LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES| LVS_EX_HEADERDRAGDROP)
        :
    m_cListTMP.SetExtendedStyle(m_cListTMP.GetExtendedStyle()  | 
        LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES| LVS_EX_HEADERDRAGDROP|LVS_EX_CHECKBOXES);

    m_cListTMP.SetBkColor(RGB(232, 255, 255));
    m_cListTMP.SetTextColor(RGB(128, 0, 64));
    m_cListTMP.SetTextBkColor(RGB(232, 255, 255));

    m_cListRegion.ModifyStyle(0,LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS|LVS_NOSORTHEADER);
    m_bLowELorDisOnly?
        m_cListRegion.SetExtendedStyle(m_cListRegion.GetExtendedStyle()  | 
        LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES| LVS_EX_HEADERDRAGDROP)
        :
    m_cListRegion.SetExtendedStyle(m_cListRegion.GetExtendedStyle()  | 
        LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES| LVS_EX_HEADERDRAGDROP|LVS_EX_CHECKBOXES);

    m_cListRegion.SetBkColor(RGB(232, 255, 255));
    m_cListRegion.SetTextColor(RGB(128, 0, 64));
    m_cListRegion.SetTextBkColor(RGB(232, 255, 255));

    ListRegionLimit();
    ListTMPLimit();
    m_cListTMP.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
    m_cListTMP.EnsureVisible(0, FALSE);	
    m_cListRegion.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
    m_cListRegion.EnsureVisible(0, FALSE);	
    m_iListRegionIndex = 0;
    m_iListTMPIndex = 0;
    SetTimer(1, 20, NULL);
    SetTimer(2, 20, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CAlarmSettingsDlg::SetEnable()
{
	GetDlgItem(IDC_EDIT_VOLTAGE_L)->EnableWindow(m_bCurRegion);
	GetDlgItem(IDC_EDIT_VOLTAGE_H)->EnableWindow(m_bCurRegion);
	GetDlgItem(IDC_EDIT_CURRENT_L)->EnableWindow(m_bCurRegion);
	GetDlgItem(IDC_EDIT_CURRENT_H)->EnableWindow(m_bCurRegion);
	GetDlgItem(IDC_EDIT_POWER_L)->EnableWindow(m_bCurRegion);
	GetDlgItem(IDC_EDIT_POWER_H)->EnableWindow(m_bCurRegion);
	GetDlgItem(IDC_COMBO_RING_REGION)->EnableWindow(m_bCurRegion);

	GetDlgItem(IDC_EDIT_TMP_L)->EnableWindow(m_bCurTMP);
	GetDlgItem(IDC_EDIT_TMP_H)->EnableWindow(m_bCurTMP);
	GetDlgItem(IDC_EDIT_TMP_OPEN)->EnableWindow(m_bCurTMP);
	GetDlgItem(IDC_COMBO_RING_TMP)->EnableWindow(m_bCurTMP);

	GetDlgItem(IDC_COMBO_RING_LAMP_TOO_HIGH)->EnableWindow(m_bLampTooHigh);
	GetDlgItem(IDC_COMBO_RING_MANUAL_STOP)->EnableWindow(m_bManualStop);
    GetDlgItem(IDC_COMBO_RING_SCANER_OVERTIME)->EnableWindow(m_bScanerOverTimeAlarm);
}


void CAlarmSettingsDlg::OnBnClickedCheckRegion()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SetEnable();
}

void CAlarmSettingsDlg::OnBnClickedCheckTmp()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SetEnable();
}

void CAlarmSettingsDlg::OnBnClickedCheckLampTooHigh()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SetEnable();
}

void CAlarmSettingsDlg::OnBnClickedCheckManualStop()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SetEnable();
}

void CAlarmSettingsDlg::EnaleControls_bDisor_LowExecu()
{
	if (LOW_EXECUTION_LEVEL ==  g_iExecutionLevel || TRUE == g_bDisplayLimitOnly)
	{
		GetDlgItem(IDC_CHECK_STOP_TEST)->EnableWindow(FALSE);

		GetDlgItem(IDC_CHECK_REGION)->EnableWindow(FALSE);
		CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_VOLTAGE_L);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_VOLTAGE_H);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_CURRENT_L);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_CURRENT_H);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_POWER_L);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_POWER_H);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_COMBO_RING_REGION)->EnableWindow(FALSE);

		GetDlgItem(IDC_CHECK_TMP)->EnableWindow(FALSE);
		pEdit = (CEdit*)GetDlgItem(IDC_CHECK_TMP);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TMP_L);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TMP_H);
		pEdit->SetReadOnly(TRUE);

		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TMP_OPEN);
		pEdit->SetReadOnly(TRUE);

		GetDlgItem(IDC_COMBO_RING_TMP)->EnableWindow(FALSE);

		GetDlgItem(IDC_CHECK_LAMP_TOO_HIGH)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_RING_LAMP_TOO_HIGH)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_MANUAL_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_RING_MANUAL_STOP)->EnableWindow(FALSE);

		GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON_CHANGE_REGION)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON_CHANGE_TMP)->ShowWindow(SW_HIDE);
	}
}

void CAlarmSettingsDlg::OnBnClickedCheckScanerOvertime()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    GetDlgItem(IDC_COMBO_RING_SCANER_OVERTIME)->EnableWindow(m_bScanerOverTimeAlarm);
}

void CAlarmSettingsDlg::OnNMClickListRegion(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    SetTimer(1, 20, NULL);
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    m_iListRegionIndex = pNMListView->iItem;
    *pResult = 0;
}

void CAlarmSettingsDlg::OnNMClickListTmp(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    SetTimer(2, 20, NULL);
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    m_iListTMPIndex = pNMListView->iItem;
    *pResult = 0;
}


void CAlarmSettingsDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    if (1 == nIDEvent)
    {
        for (int i = 0; i < g_myDockablePaneData.m_dataRegion.GetSize(); i ++)
        {
            if (!m_bLowELorDisOnly)
            {   
                m_bRegion[i] = m_cListRegion.GetCheck(i);
            }
        }
        if (m_iListRegionIndex >= 0 && m_iListRegionIndex <= g_myDockablePaneData.m_dataRegion.GetSize() - 1)
        {
            SetRegionLimittoView();
            m_cListRegion.SetItemState(m_iListRegionIndex, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
            m_cListRegion.EnsureVisible(m_iListRegionIndex, FALSE);	
        }
        KillTimer(1);
    }

    if (2 == nIDEvent)
    {
        for (int i = 0; i < g_myDockablePaneData.m_TemperatureController.GetSize(); i ++)
        {
            if (!m_bLowELorDisOnly)
            {
                m_bTMP[i] = m_cListTMP.GetCheck(i);
            }
        }
        if (m_iListTMPIndex >= 0 && m_iListTMPIndex <= g_myDockablePaneData.m_TemperatureController.GetSize() - 1)
        {
            SetTMPLimittoView();
            m_cListTMP.SetItemState(m_iListTMPIndex, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
            m_cListTMP.EnsureVisible(m_iListTMPIndex, FALSE);	
        }
        KillTimer(2);
    }

    CDialogEx::OnTimer(nIDEvent);
}


void  CAlarmSettingsDlg::SetRegionLimittoView()
{
    m_bCurRegion			= m_bRegion[m_iListRegionIndex];
	m_iCurRegionRingIndex	= m_iRegionRingIndex[m_iListRegionIndex];
    m_fCurCurrentH			= m_fCurrentH[m_iListRegionIndex];
    m_fCurCurrentL			= m_fCurrentL[m_iListRegionIndex];
    m_fCurPowerH			= m_fPowerH[m_iListRegionIndex];
    m_fCurPowerL			= m_fPowerL[m_iListRegionIndex];
    m_fCurVoltageH			= m_fVoltageH[m_iListRegionIndex];
    m_fCurVoltageL			= m_fVoltageL[m_iListRegionIndex];
    m_strRegionName			= g_myDockablePaneData.m_strRegionText[m_iListRegionIndex];
    UpdateData(FALSE);      
    if(m_bLowELorDisOnly)
    {
        m_btCurRegionAlarm.SetCheck(m_bCurRegion);
        m_btCurRegionAlarm.EnableWindow(FALSE);
        m_cComboRegion.EnableWindow(FALSE);
        m_cCurCurrentH.SetReadOnly(TRUE);
        m_cCurCurrentL.SetReadOnly(TRUE);
        m_cCurPowerH.SetReadOnly(TRUE);
        m_cCurPowerL.SetReadOnly(TRUE);
        m_cCurVoltageH.SetReadOnly(TRUE);
        m_cCurVoltageL.SetReadOnly(TRUE);  
    }
    else
    {
       SetEnable();
    }
}

void  CAlarmSettingsDlg::SetTMPLimittoView()
{

    // TMP
    m_bCurTMP			= m_bTMP[m_iListTMPIndex];
    m_iCurTMPRingIndex	= m_iTMPRingIndex[m_iListTMPIndex];
    m_fCurTMPH			= m_fTMPH[m_iListTMPIndex];
	m_fCurTMPL			= m_fTMPL[m_iListTMPIndex];
	m_fCurTMPOPEN		= m_fTMPOPEN[m_iListTMPIndex];
    m_strTMPControlName = g_myDockablePaneData.m_strTemperatureControllerText[m_iListTMPIndex];
    UpdateData(FALSE);  
     if(m_bLowELorDisOnly)
    {
        m_btCurTMPAlarm.SetCheck(m_bCurTMP);
        m_btCurTMPAlarm.EnableWindow(FALSE);
        m_cComboTMP.EnableWindow(FALSE);
        m_cCurTMPH.SetReadOnly(TRUE);
        m_cCurTMPL.SetReadOnly(TRUE);
		m_cCurTMPOPEN.SetReadOnly(TRUE);
    }
    else
    {  
        SetEnable();
    }
}

void  CAlarmSettingsDlg::ListRegionLimit()
{
    m_cListRegion.DeleteAllItems();
    while(1)
    {
        if (m_cListRegion.DeleteColumn(0) == FALSE)
        {
            break;
        }
    }
    CString strTemp;
    int iN = 0; 

    strTemp = _T("是否报警");
    m_cListRegion.InsertColumn(iN,strTemp);
    m_cListRegion.SetColumnWidth(iN,75);
    iN ++;
    strTemp = _T("区域名称");
    m_cListRegion.InsertColumn(iN,strTemp);
    m_cListRegion.SetColumnWidth(iN,130);
    iN ++;
    strTemp = _T("电压限值(V)");
    m_cListRegion.InsertColumn(iN,strTemp);
    m_cListRegion.SetColumnWidth(iN,90);
    iN ++;
    strTemp = _T("电流限值(A)");
    m_cListRegion.InsertColumn(iN,strTemp);
    m_cListRegion.SetColumnWidth(iN,90); 

    iN ++;
    strTemp = _T("功率限值(W)");
    m_cListRegion.InsertColumn(iN,strTemp);
    m_cListRegion.SetColumnWidth(iN,90); 

    iN ++;
    strTemp = _T("提示音");
    m_cListRegion.InsertColumn(iN,strTemp);
    m_cListRegion.SetColumnWidth(iN,90); 
    for (int i = 0; i < g_myDockablePaneData.m_dataRegion.GetSize(); i ++)
    {   
        iN = 0;  
        strTemp = "";
        m_cListRegion.InsertItem(i,strTemp);
        if (!m_bLowELorDisOnly)
        {
            if (m_bRegion[i])
            {
                m_cListRegion.SetCheck(i);
            }
        }
        else
        {
            if (m_bRegion[i])
            {
                strTemp.Format(_T("%s"), _T("是"));
                m_cListRegion.SetItemText(i,iN,strTemp); 
            }
            else
            {
                strTemp.Format(_T("%s"), _T("否"));
                m_cListRegion.SetItemText(i,iN,strTemp);
            }
        }
        iN ++;
        m_cListRegion.SetItemText(i, iN, g_myDockablePaneData.m_strRegionText[i]);
        iN ++;
        strTemp.Format(_T("%g - %g"), m_fVoltageL[i], m_fVoltageH[i]);
        m_cListRegion.SetItemText(i,iN,strTemp); 
        iN ++;
        strTemp.Format(_T("%g - %g"), m_fCurrentL[i], m_fCurrentH[i]);
        m_cListRegion.SetItemText(i,iN,strTemp); 
        iN ++;
        strTemp.Format(_T("%g - %g"), m_fPowerL[i], m_fPowerH[i]);
        m_cListRegion.SetItemText(i,iN,strTemp); 
        iN ++;
        if (m_iRegionRingIndex[i] == 0)
        {
            m_cListRegion.SetItemText(i,iN,"Default"); 
        }
        else
        {
            m_cListRegion.SetItemText(i,iN,g_pDoc->m_AlarmRingData.GetRingInfoString(m_iRegionRingIndex[i] - 1)); 
        }
    }
}

void  CAlarmSettingsDlg::ListTMPLimit()
{
    m_cListTMP.DeleteAllItems();
    while(1)
    {
        if (m_cListTMP.DeleteColumn(0) == FALSE)
        {
            break;
        }
    }
    CString strTemp;
    int iN = 0; 
    strTemp = _T("是否报警");
    m_cListTMP.InsertColumn(iN,strTemp);
    m_cListTMP.SetColumnWidth(iN,75);
    iN ++;
    strTemp = _T("温控名称");
    m_cListTMP.InsertColumn(iN,strTemp);
    m_cListTMP.SetColumnWidth(iN,130);
    iN ++;
    strTemp = _T("温度(℃)");
    m_cListTMP.InsertColumn(iN,strTemp);
    m_cListTMP.SetColumnWidth(iN,90);
    iN ++;

	strTemp = _T("风机开启温度(℃)");
    m_cListTMP.InsertColumn(iN,strTemp);
    m_cListTMP.SetColumnWidth(iN,110);
	iN ++;

    strTemp = _T("提示音");
    m_cListTMP.InsertColumn(iN,strTemp);
    m_cListTMP.SetColumnWidth(iN,90); 
    for (int i = 0; i < g_myDockablePaneData.m_TemperatureController.GetSize(); i ++)
    {   
        iN = 0;  
        strTemp = "";
        m_cListTMP.InsertItem(i,strTemp);
        if (!m_bLowELorDisOnly)
        {
            if (m_bTMP[i])
            {
                m_cListTMP.SetCheck(i);
            }
        }
        else
        {
            if (m_bTMP[i])
            {
                strTemp.Format(_T("%s"), _T("是"));
                m_cListTMP.SetItemText(i,iN,strTemp); 
            }
            else
            {
                strTemp.Format(_T("%s"), _T("否"));
                m_cListTMP.SetItemText(i,iN,strTemp);
            }
        }
        iN ++;
        m_cListTMP.SetItemText(i, iN, g_myDockablePaneData.m_strTemperatureControllerText[i]);
        iN ++;
        strTemp.Format(_T("%g - %g"), m_fTMPL[i], m_fTMPH[i]);
        m_cListTMP.SetItemText(i,iN,strTemp); 
        iN ++;

		strTemp.Format(_T("%g"), m_fTMPOPEN[i]);
        m_cListTMP.SetItemText(i,iN,strTemp); 
        iN ++;
        if (m_iTMPRingIndex[i] == 0)
        {
            m_cListTMP.SetItemText(i,iN,"Default"); 
        }
        else
        {
            m_cListTMP.SetItemText(i,iN,g_pDoc->m_AlarmRingData.GetRingInfoString(m_iTMPRingIndex[i] - 1)); 
        }

    }
}

void CAlarmSettingsDlg::OnBnClickedButtonChangeRegion()
{
    // TODO: 在此添加控件通知处理程序代码   
    UpdateData(TRUE);
    if (m_iListRegionIndex == -1 || m_iListRegionIndex > g_iGaugeNum - 1)
    {
        return;
    }
    m_bRegion[m_iListRegionIndex]			= m_bCurRegion;
    m_iRegionRingIndex[m_iListRegionIndex]	= m_iCurRegionRingIndex;
    m_fCurrentH[m_iListRegionIndex]			= m_fCurCurrentH;
    m_fCurrentL[m_iListRegionIndex]			= m_fCurCurrentL;
    m_fPowerH[m_iListRegionIndex]			= m_fCurPowerH;
    m_fPowerL[m_iListRegionIndex]			= m_fCurPowerL;
    m_fVoltageH[m_iListRegionIndex]			= m_fCurVoltageH;
    m_fVoltageL[m_iListRegionIndex]			= m_fCurVoltageL;
    ListRegionLimit();
}

void CAlarmSettingsDlg::OnBnClickedButtonChangeTmp()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    if (m_iListTMPIndex == -1 || m_iListTMPIndex > g_iTMPControlNum - 1)
    {
        return;
    }
    m_bTMP[m_iListTMPIndex]				= m_bCurTMP;
    m_iTMPRingIndex[m_iListTMPIndex]	= m_iCurTMPRingIndex;
    m_fTMPH[m_iListTMPIndex]			= m_fCurTMPH;
    m_fTMPL[m_iListTMPIndex]			= m_fCurTMPL;
	m_fTMPOPEN[m_iListTMPIndex]			= m_fCurTMPOPEN;  
	g_myDockablePaneData.m_TemperatureController[m_iListTMPIndex].m_fTMPDown = m_fCurTMPL;
	g_myDockablePaneData.m_TemperatureController[m_iListTMPIndex].m_fTMPUp = m_fCurTMPH;
	g_myDockablePaneData.m_TemperatureController[m_iListTMPIndex].m_fTMPOpen = m_fCurTMPOPEN;
	ListTMPLimit();
}
