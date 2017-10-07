// DlgMyLastSet.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DlgMyLastSet.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"


// CDlgMyLastSet 对话框

IMPLEMENT_DYNAMIC(CDlgMyLastSet, CDialogEx)

CDlgMyLastSet::CDlgMyLastSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMyLastSet::IDD, pParent)
	, m_fCurVolMyLast(220)
	, m_iCurTimeMyLast(1)
	, m_fCurFreqMyLast(50)
{

}

CDlgMyLastSet::~CDlgMyLastSet()
{
}

void CDlgMyLastSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_fCurVolMyLast);
	DDX_Text(pDX, IDC_EDIT17, m_iCurTimeMyLast);
	DDX_Control(pDX, IDC_LIST_LIMIT, m_cList);
	DDX_Text(pDX, IDC_EDIT_FREQ_MY, m_fCurFreqMyLast);
}


BEGIN_MESSAGE_MAP(CDlgMyLastSet, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgMyLastSet::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDCANCEL, &CDlgMyLastSet::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CDlgMyLastSet::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDOK, &CDlgMyLastSet::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_LIMIT, &CDlgMyLastSet::OnItemchangedListLimit)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgMyLastSet::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDlgMyLastSet 消息处理程序



void CDlgMyLastSet::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

void CDlgMyLastSet::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


BOOL CDlgMyLastSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_cList.SetExtendedStyle(m_cList.GetExtendedStyle()  | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	ReList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgMyLastSet::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL bR;
	bR = UpdateData(TRUE);
	if(!bR)
	{
		return;
	}
	BOOL bHaveAdd = FALSE;
	int iAddPos = -1;
	for (int i = 0; i < m_fVolMyLastList.GetSize(); i ++)
	{
		if(m_fVolMyLastList[i] == m_fCurVolMyLast && m_fFreqMyLastList[i] == m_fCurFreqMyLast)
		{
			bHaveAdd = TRUE;
			iAddPos = i;
			break;
		}
	}
	
	if(bHaveAdd)
	{
		int iR;
		iR = AfxMessageBox("已添加，是否修改?",MB_ICONINFORMATION | MB_YESNO);
		if(iR == IDYES)
		{
			m_fVolMyLastList[iAddPos]  = m_fCurVolMyLast;
			m_fFreqMyLastList[iAddPos]  = m_fCurFreqMyLast;
			m_iTimeMyLastList[iAddPos] = m_iCurTimeMyLast;
			ReList();
		}
	}
	else
	{
		m_fVolMyLastList.Add(m_fCurVolMyLast);
		m_fFreqMyLastList.Add(m_fCurFreqMyLast);
		m_iTimeMyLastList.Add(m_iCurTimeMyLast);

		ReList();
	}
}

void CDlgMyLastSet::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL bR;
	bR = UpdateData(TRUE);
	if(!bR)
	{
		return;
	}

	m_fVolMyLastList.RemoveAt(m_iCurSele);
	m_fFreqMyLastList.RemoveAt(m_iCurSele);
	m_iTimeMyLastList.RemoveAt(m_iCurSele);
	ReList();
}




void CDlgMyLastSet::OnItemchangedListLimit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_iCurSele = pNMLV->iItem;
	if (m_iCurSele >= 0 )
	{
		m_fCurVolMyLast = m_fVolMyLastList[m_iCurSele];
		m_fCurFreqMyLast = m_fFreqMyLastList[m_iCurSele];
		m_iCurTimeMyLast = m_iTimeMyLastList[m_iCurSele];
		UpdateData(FALSE);
	}
	*pResult = 0;
}

void CDlgMyLastSet::ReList()
{
	m_cList.DeleteAllItems();
    while(1)
    {
        if (m_cList.DeleteColumn(0) == FALSE)
        {
            break;
        }
    }
    CString strTemp;
    int iN = 0; 

    strTemp = _T("漫游老炼电压(V)");
    m_cList.InsertColumn(iN,strTemp);
    m_cList.SetColumnWidth(iN,130);
    iN ++;
	strTemp = _T("漫游老炼频率(Hz)");
	m_cList.InsertColumn(iN,strTemp);
	m_cList.SetColumnWidth(iN,130);
	iN ++;
    strTemp = _T("持续时间(s)");
    m_cList.InsertColumn(iN,strTemp);
    m_cList.SetColumnWidth(iN,100);
    iN ++;
    for (int i = 0; i < m_fVolMyLastList.GetSize(); i ++)
    {   
        iN = 0;  
        strTemp = "";
        m_cList.InsertItem(i,strTemp);

		strTemp.Format(_T("%.1f"), m_fVolMyLastList[i]);
        m_cList.SetItemText(i, iN, strTemp);
        iN ++;
		
		strTemp.Format(_T("%.1f"), m_fFreqMyLastList[i]);
		m_cList.SetItemText(i, iN, strTemp);
		iN ++;

		strTemp.Format(_T("%d"), m_iTimeMyLastList[i]);
        m_cList.SetItemText(i,iN,strTemp); 
    }

}


void CDlgMyLastSet::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	BOOL bR;
	//漫游
	int i;
	int iCOM;
	sscanf_s(g_pDoc->m_CommSettingsData.m_strMyLastCOM.GetBuffer(), "COM%d", &iCOM);
	g_DPSComm_MyLast.SetDeviceType((DeviceType)g_pDoc->m_CommSettingsData.m_iMyLastPowerType);
	g_DPSComm_MyLast.InitializeComm(iCOM);
	g_DPSComm_MyLast.InRemote();
	g_DPSComm_MyLast.StopOutput();
	Sleep(100);

	if(m_fVolMyLastList.GetSize() > 0)
	{
		Parameter data;
		data.fFrequenceLow = 45;
		data.fFrequenceUpper = 60;
		data.fExternalCurrentFactor = 0;
		data.fVoltageLow = 10;
		data.fVoltageUpper = 300;
		data.bOvercurrentFoldBackEnable = FALSE;
		data.bHarmonicEnable = FALSE;
		data.bExternalVoltageSamplingEnable = FALSE;
		data.bExternalCurrentSamplingEnable = FALSE;
		data.bVoltageAutoAdjustEnable = TRUE;
		data.iMemory = 0;

		data.fVoltage		= m_fVolMyLastList[0];
		data.fFrequence		= m_fFreqMyLastList[0];
		data.fAlarmCurrent	= g_DPSComm_MyLast.GetLimitData().LimitCurrentRange2.fUpper;
		data.fAlarmPower	= g_DPSComm_MyLast.GetLimitData().LimitPower.fUpper;
		data.iRangeU		= 1;
		g_DPSComm_MyLast.SetParameter(data);
	//	g_DPSComm_MyLast.FastRun(data.fVoltage,data.fFrequence);
		Sleep(100);
	}

	if (!g_DPSComm_MyLast.IsRunning())
	{
//		bR = g_DPSComm_MyLast.StopOutput();
		bR = g_DPSComm_MyLast.StartOutput();
		Sleep(100);
	}
	int iTolTIme = GetCurrentTime();
	if (1)
	{
		for (i = 0; i < m_fVolMyLastList.GetSize(); i++)
		{
			CString strTemp;
			strTemp.Format("%ds %.1f %.1f %.1f %.1f",m_iTimeMyLastList[i],
					m_fVolMyLastList[i], 
					m_fFreqMyLastList[i],g_DPSComm_MyLast.GetLimitData().LimitCurrentRange2.fUpper, 
					g_DPSComm_MyLast.GetLimitData().LimitPower.fUpper);
			int iT1 = GetCurrentTime();
			int iT2 = GetCurrentTime();
			bR = g_DPSComm_MyLast.SetParameterRunning(m_fVolMyLastList[i], 
														m_fFreqMyLastList[i],
														g_DPSComm_MyLast.GetLimitData().LimitCurrentRange2.fUpper, 
														g_DPSComm_MyLast.GetLimitData().LimitPower.fUpper);
			if (!bR)
			{
				AfxMessageBox("漫游失败2!");
				return;
			}
			

			while(1)
			{
				Sleep(10);
						
				iT2 = GetCurrentTime();
				if((iT2 - iT1) > (m_iTimeMyLastList[i] * 1000))
				{
					break;
				}
			} // while, end wait
		}
	}
	iTolTIme = GetCurrentTime() - iTolTIme;

	g_DPSComm_MyLast.StopOutput();
	EndWaitCursor();
	CString strTemp;
	strTemp.Format("%dms",iTolTIme);
	AfxMessageBox("漫游成功!" + strTemp);
}
