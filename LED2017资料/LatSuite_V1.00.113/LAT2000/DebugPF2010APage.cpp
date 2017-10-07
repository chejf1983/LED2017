// DebugPowerMeterPage.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DebugPF2010APage.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"


// CDebugPF2010APage 对话框

IMPLEMENT_DYNAMIC(CDebugPF2010APage, CPropertyPage)

CDebugPF2010APage::CDebugPF2010APage()
	: CPropertyPage(CDebugPF2010APage::IDD)
{
	m_fPower = 0.0f;
	m_fCurrent = 0.0f;
	m_fPowerFactor = 0.0f;
	m_fVoltage = 0.0f;

	CString strSection = "Debug_PF2010A";
	m_strCOM = AfxGetApp()->GetProfileString(strSection, "m_strCOM", "COM1");
	m_strTypeName = AfxGetApp()->GetProfileString(strSection, "m_strTypeName", "");
	m_iRangeCF = 0;
	m_iRangeI = 0;
	m_iRangeU = 0;
}

CDebugPF2010APage::~CDebugPF2010APage()
{
	CString strSection = "Debug_PF2010A";
	AfxGetApp()->WriteProfileString(strSection, "m_strCOM", m_strCOM);
	AfxGetApp()->WriteProfileString(strSection, "m_strTypeName", m_strTypeName);
}

void CDebugPF2010APage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_CBString(pDX, IDC_COMBO_COM, m_strCOM);
    DDX_CBString(pDX, IDC_COMBO_TYPE, m_strTypeName);
    DDX_Control(pDX, IDC_COMBO_TYPE, m_cTypeList);
    DDX_Text(pDX, IDC_EDIT_POWER, m_fPower);
    DDX_Text(pDX, IDC_EDIT_CURRENT, m_fCurrent);
    DDX_Text(pDX, IDC_EDIT_POWER_FACTOR, m_fPowerFactor);
    DDX_Text(pDX, IDC_EDIT_VOLTAGE, m_fVoltage);
    DDX_CBIndex(pDX, IDC_COMBO_CF, m_iRangeCF);
    DDX_CBIndex(pDX, IDC_COMBO_RANGE_I, m_iRangeI);
    DDX_CBIndex(pDX, IDC_COMBO_RANGE_U, m_iRangeU);
    DDX_Control(pDX, IDC_COMBO_RANGE_I, m_cRangeI);
    DDX_Control(pDX, IDC_COMBO_RANGE_U, m_cRangeV);
}


BEGIN_MESSAGE_MAP(CDebugPF2010APage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CDebugPF2010APage::OnBnClickedButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CDebugPF2010APage::OnBnClickedButtonSet)
    ON_CBN_SELCHANGE(IDC_COMBO_CF, &CDebugPF2010APage::OnCbnSelchangeComboCf)
END_MESSAGE_MAP()


// CDebugPF2010APage 消息处理程序


void CDebugPF2010APage::OnBnClickedButtonRead()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	g_PowerMeterComm.Initialize(m_strCOM, g_pDoc->m_CommSettingsData.m_iPFType, m_iRangeCF);

	BeginWaitCursor();
	BOOL bR = g_PowerMeterComm.Read(m_fVoltage, m_fCurrent, m_fPower, m_fPowerFactor);
	EndWaitCursor();
	UpdateData(FALSE);
	if (bR)
	{
		AfxMessageBox("读取成功！");
	}
	else
	{
		AfxMessageBox("读取失败！");
	}
}


BOOL CDebugPF2010APage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	int iCount = g_PowerMeterComm.GetTypeCount();
	CString strTemp;
	for (int i = 0; i < iCount; i++)
	{
		strTemp = g_PowerMeterComm.GetTypeName(i);
		m_cTypeList.InsertString(i, strTemp);
	}

	int iIndex = m_cTypeList.FindString(0, "TYPE 8 BITS");
	iIndex = iIndex < 0 ? 0 : iIndex;
	m_cTypeList.SetCurSel(iIndex);

    g_PowerMeterComm.Initialize(m_strCOM, g_pDoc->m_CommSettingsData.m_iPFType, m_iRangeCF);
    m_cRangeI.ResetContent();
    m_cRangeV.ResetContent();
    for (int i = 0; i < g_PowerMeterComm.GetVolRangeNum(); i ++)
    {
        strTemp.Format("%g", g_PowerMeterComm.GetVolRange(i));
        m_cRangeV.AddString(strTemp);
    }

    for (int i = 0; i < g_PowerMeterComm.GetCurRangeNum(); i ++)
    {
        strTemp.Format("%g", g_PowerMeterComm.GetCurRange(i));
        m_cRangeI.AddString(strTemp);
	}
	m_strCOM = g_pDoc->m_CommSettingsData.m_strCOMPF2010A;
    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDebugPF2010APage::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	BeginWaitCursor();
	BOOL bR = g_PowerMeterComm.SetRange(m_iRangeU, m_iRangeI, m_iRangeCF);
	EndWaitCursor();

	if (bR)
	{
		AfxMessageBox("设置成功！");
	}
	else
	{
		AfxMessageBox("设置失败！");
	}
}


void CDebugPF2010APage::OnCbnSelchangeComboCf()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    CString strTemp;
    g_PowerMeterComm.Initialize(m_strCOM ,g_pDoc->m_CommSettingsData.m_iPFType, 
        m_iRangeCF);
    m_cRangeI.ResetContent();
    m_cRangeV.ResetContent();
    for (int i = 0; i < g_PowerMeterComm.GetVolRangeNum(); i ++)
    {
        strTemp.Format("%g", g_PowerMeterComm.GetVolRange(i));
        m_cRangeV.AddString(strTemp);
    }

    for (int i = 0; i < g_PowerMeterComm.GetCurRangeNum(); i ++)
    {
        strTemp.Format("%g", g_PowerMeterComm.GetCurRange(i));
        m_cRangeI.AddString(strTemp);
    }
    m_cRangeV.SetCurSel(0);
    m_cRangeI.SetCurSel(0);
}
