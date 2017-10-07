// ContainerWatchView.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "ContainerWatchView.h"
#include "LAT2000Doc.h"
#include "AlarmSettingsDlg.h"


// CContainerWatchView
extern CMyDockablePaneData g_myDockablePaneData;
extern BOOL	g_bTMPControllerON;


IMPLEMENT_DYNCREATE(CContainerWatchView, CFormView)

CContainerWatchView::CContainerWatchView()
	: CFormView(CContainerWatchView::IDD)
{
	m_bFir = TRUE;

	m_font.CreateFont(16, 0, 0, 0, 500, FALSE, FALSE, 0,
		GB2312_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_MODERN,"宋体");
	CString strSection = "CContainerWatchView";
	CString strSetTemp;
	for (int i = 0; i < g_myDockablePaneData.m_strSetTMP.GetSize(); i ++)
    {
        strSetTemp.Format("strSetTemp%d", i + 1); 
        g_myDockablePaneData.m_strSetTMP[i] = AfxGetApp()->GetProfileStringA(strSection, strSetTemp, "20");
    }
}

CContainerWatchView::~CContainerWatchView()
{
}

void CContainerWatchView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IANALOGDISPLAYX_TMP1, m_cSample);
}

BEGIN_MESSAGE_MAP(CContainerWatchView, CFormView)
	ON_WM_CTLCOLOR()
	ON_MESSAGE(MSG_DOCKABLE_PANE_UPDATE_INFO, &CContainerWatchView::OnMsgDockablePaneUpdateInfo)
	ON_MESSAGE(MSG_DOCKABLE_PANE_UPDATE_TMP, &CContainerWatchView::OnMsgDockablePaneUpdateTmp)
	ON_BN_CLICKED(IDC_BUTTON_TMP_ON, &CContainerWatchView::OnBnClickedButtonTmpOn)
	ON_BN_CLICKED(IDC_BUTTON_TMP_OFF, &CContainerWatchView::OnBnClickedButtonTmpOff)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_TMP_ON2, &CContainerWatchView::OnBnClickedButtonTmpOn2)
	ON_BN_CLICKED(IDC_BUTTON_TMP_OFF3, &CContainerWatchView::OnBnClickedButtonTmpOff3)
	ON_BN_CLICKED(IDC_BUTTON_TMP_ON4, &CContainerWatchView::OnBnClickedButtonTmpOn4)
	ON_BN_CLICKED(IDC_BUTTON_TMP_OFF5, &CContainerWatchView::OnBnClickedButtonTmpOff5)
	ON_BN_CLICKED(IDC_BUTTON_TMP_ON3, &CContainerWatchView::OnBnClickedButtonTmpOn3)
	ON_BN_CLICKED(IDC_BUTTON_TMP_OFF4, &CContainerWatchView::OnBnClickedButtonTmpOff4)
END_MESSAGE_MAP()


// CContainerWatchView 诊断

#ifdef _DEBUG
void CContainerWatchView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CContainerWatchView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CContainerWatchView 消息处理程序


void CContainerWatchView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	InitControls();
	g_hDockablePaneDialog = m_hWnd;
	for (int i = 0; i < g_myDockablePaneData.m_strSetTMP.GetSize(); i++)
	{
		if(i % 4 == 0)
			m_cSetTMP[i].put_Value(g_myDockablePaneData.m_strSetTMP[i]);
	}
	
	m_bFir = FALSE;
	SetPos();
}

HBRUSH CContainerWatchView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	switch(nCtlColor)
	{
	case CTLCOLOR_BTN:
	case CTLCOLOR_STATIC:
		pDC->SetBkMode(TRANSPARENT);
	case CTLCOLOR_DLG:
		CBrush * pBrush = NULL;
		switch(theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2003:
			pBrush = &g_brBackGreen;
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			pBrush = &g_brBackBlue;
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			pBrush = &g_brBackBlack;
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			pBrush = &g_brSilver;
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			pBrush = &g_brBackGreen;
			break;

		default:
			return hbr;
		}

		return static_cast<HBRUSH>(pBrush->GetSafeHandle());
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

afx_msg LRESULT CContainerWatchView::OnMsgDockablePaneUpdateInfo(WPARAM wParam, LPARAM lParam)
{
	int i;
	/*for (i = 0; i < g_myDockablePaneData.m_strTemperatureControllerText.GetSize(); i ++)
	{
		m_cTMPConName[i].SetWindowText(g_myDockablePaneData.m_strTemperatureControllerText.GetAt(i));
		if (g_myDockablePaneData.m_TemperatureController[i].m_bTMPReadSuccessful)
		{
			if(g_myDockablePaneData.m_TemperatureController[i].m_fTMP > 100)
			{
				m_cTMP.GetAt(i).put_ErrorActive(TRUE);
				m_cTMP.GetAt(i).put_ErrorText("----");
			}
			else
			{
				m_cTMP[i].put_ErrorActive(FALSE);
				m_cTMP[i].put_Value(g_myDockablePaneData.m_TemperatureController[i].m_fTMP);
			}
			if (g_myDockablePaneData.m_TemperatureController[i].m_bTMPAlarm)
			{
				m_cTMP[i].put_FontColor(RGB(255, 0, 0));
			}
			else
			{
				m_cTMP[i].put_FontColor(RGB(0, 255, 0));
			}
		}
	}*/

	for (i = 0; i < g_myDockablePaneData.m_strRegionText.GetSize(); i ++)
	{
	//	m_cRegionName[i].SetWindowText(g_myDockablePaneData.m_strRegionText.GetAt(i));
		if (g_myDockablePaneData.m_dataRegion[i].bReadSuccessful)
		{
			m_cU[i].put_ErrorActive(FALSE);
			m_cI[i].put_ErrorActive(FALSE);
			m_cP[i].put_ErrorActive(FALSE);
			m_cU[i].put_Value(g_myDockablePaneData.m_dataRegion[i].fVoltageV);
			m_cI[i].put_Value(g_myDockablePaneData.m_dataRegion[i].fCurrentA);
			m_cP[i].put_Value(g_myDockablePaneData.m_dataRegion[i].fPowerW);

			if (g_myDockablePaneData.m_dataRegion[i].bAlarmCurrent)
			{
				m_cI[i].put_FontColor(RGB(255, 0, 0));
			}
			else
			{
				m_cI[i].put_FontColor(RGB(0, 255, 0));
			}
			if (g_myDockablePaneData.m_dataRegion[i].bAlarmPower)
			{
				m_cP[i].put_FontColor(RGB(255, 0, 0));
			}
			else
			{
				m_cP[i].put_FontColor(RGB(0, 255, 0));
			}
			if (g_myDockablePaneData.m_dataRegion[i].bAlarmVoltage)
			{
				m_cU[i].put_FontColor(RGB(255, 0, 0));
			}
			else
			{
				m_cU[i].put_FontColor(RGB(0, 255, 0));
			}
		}
		else
		{
			m_cU[i].put_ErrorActive(TRUE);
			m_cI[i].put_ErrorActive(TRUE);
			m_cP[i].put_ErrorActive(TRUE);
		}
	}
	return 0;
}


afx_msg LRESULT CContainerWatchView::OnMsgDockablePaneUpdateTmp(WPARAM wParam, LPARAM lParam)
{
	int i;
	for (i = 0; i < g_myDockablePaneData.m_strTemperatureControllerText.GetSize(); i ++)
	{
	//	m_cTMPConName[i].SetWindowText(g_myDockablePaneData.m_strTemperatureControllerText.GetAt(i));
		if (g_myDockablePaneData.m_TemperatureController[i].m_bTMPReadSuccessful)
		{
			if(g_myDockablePaneData.m_TemperatureController[i].m_fTMP > 100)
			{
				m_cTMP.GetAt(i).put_ErrorActive(TRUE);
				m_cTMP.GetAt(i).put_ErrorText("----");
			}
			else
			{
				m_cTMP[i].put_ErrorActive(FALSE);
				m_cTMP[i].put_Value(g_myDockablePaneData.m_TemperatureController[i].m_fTMP);
			}
			if (g_myDockablePaneData.m_TemperatureController[i].m_bTMPAlarm)
			{
				m_cTMP[i].put_FontColor(RGB(255, 0, 0));
			}
			else
			{
				m_cTMP[i].put_FontColor(RGB(0, 255, 0));
			}
		}
	}

	/*for (i = 0; i < g_myDockablePaneData.m_strRegionText.GetSize(); i ++)
	{
		m_cRegionName[i].SetWindowText(g_myDockablePaneData.m_strRegionText.GetAt(i));
		if (g_myDockablePaneData.m_dataRegion[i].bReadSuccessful)
		{
			m_cU[i].put_ErrorActive(FALSE);
			m_cI[i].put_ErrorActive(FALSE);
			m_cP[i].put_ErrorActive(FALSE);
			m_cU[i].put_Value(g_myDockablePaneData.m_dataRegion[i].fVoltageV);
			m_cI[i].put_Value(g_myDockablePaneData.m_dataRegion[i].fCurrentA);
			m_cP[i].put_Value(g_myDockablePaneData.m_dataRegion[i].fPowerW);

			if (g_myDockablePaneData.m_dataRegion[i].bAlarmCurrent)
			{
				m_cI[i].put_FontColor(RGB(255, 0, 0));
			}
			else
			{
				m_cI[i].put_FontColor(RGB(0, 255, 0));
			}
			if (g_myDockablePaneData.m_dataRegion[i].bAlarmPower)
			{
				m_cP[i].put_FontColor(RGB(255, 0, 0));
			}
			else
			{
				m_cP[i].put_FontColor(RGB(0, 255, 0));
			}
			if (g_myDockablePaneData.m_dataRegion[i].bAlarmVoltage)
			{
				m_cU[i].put_FontColor(RGB(255, 0, 0));
			}
			else
			{
				m_cU[i].put_FontColor(RGB(0, 255, 0));
			}
		}
		else
		{
			m_cU[i].put_ErrorActive(TRUE);
			m_cI[i].put_ErrorActive(TRUE);
			m_cP[i].put_ErrorActive(TRUE);
		}
	}*/
	return 0;
}

static const FONTDESC _TitleFontHo = 
{
	sizeof(FONTDESC), OLESTR("MS Sans Serif"), FONTSIZE(18), FW_BOLD,ANSI_CHARSET,
	FALSE, FALSE, FALSE 
};

void CContainerWatchView::InitControls()
{
	// TmperatureControl 
	int i;
	//m_cTMPRange.SetSize(g_myDockablePaneData.m_strTemperatureControllerText.GetSize());
	m_cTMPConName.SetSize(g_myDockablePaneData.m_strTemperatureControllerText.GetSize());
	m_cTMP.SetSize(g_myDockablePaneData.m_strTemperatureControllerText.GetSize());
	m_cSetTMP.SetSize(g_myDockablePaneData.m_strTemperatureControllerText.GetSize());
	m_cStaticSetTMP.SetSize(g_myDockablePaneData.m_strTemperatureControllerText.GetSize());
	for (i = 0; i < m_cTMPConName.GetSize(); i ++)
	{
// 		m_cTMPRange.GetAt(i).Create("温控", WS_VISIBLE | WS_EX_TRANSPARENT | WS_CHILD | BS_GROUPBOX, CRect(0, 0, 0, 0), this, 40000+i);
// 		m_cTMPRange.GetAt(i).SetFont(GetFont());
// 		m_cTMPRange.GetAt(i).SetWindowPos(NULL,0, 0, 0, 0,SWP_SHOWWINDOW);

		m_cTMPConName.GetAt(i).Create(g_myDockablePaneData.m_strTemperatureControllerText.GetAt(i),
										WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE, CRect(0, 0, 0, 0), this, 40100 + i);
		m_cTMPConName.GetAt(i).SetFont(GetFont());
		m_cTMP.GetAt(i).Create("----", WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0), this, 40200 + i);
		m_cTMP.GetAt(i).put_Font((LPFONTDISP)m_cSample.get_Font());
		m_cTMP.GetAt(i).put_ErrorFont((LPFONTDISP)m_cSample.get_Font());
		m_cTMP.GetAt(i).put_ErrorActive(TRUE);
		m_cTMP.GetAt(i).put_ErrorText("----");
		m_cTMP.GetAt(i).put_BackGroundColor(RGB(0, 0, 0));
		m_cTMP.GetAt(i).put_ErrorBackGroundColor(RGB(0, 0, 0));
		m_cTMP.GetAt(i).put_ErrorFontColor(RGB(128, 128, 128));
		m_cTMP.GetAt(i).put_Alignment(CIanalogdisplayx_tmp1::iahCenter);
		m_cTMP.GetAt(i).SetWindowPos(NULL,0, 0, 0, 0,SWP_SHOWWINDOW);

		/*m_cStaticSetTMP.GetAt(i).Create("设定:", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE, CRect(0, 0, 0, 0), this, 40250 + i);
		m_cStaticSetTMP.GetAt(i).SetFont(GetFont());
		m_cSetTMP.GetAt(i).Create("----", WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0), this, 40300 + i);
		m_cSetTMP.GetAt(i).put_Font((LPFONTDISP)m_cSample.get_Font());
		m_cSetTMP.GetAt(i).put_Alignment(CIeditx_tmp1::taCenter);
		*/
	}

	// Region
	m_cRegionName.SetSize(g_myDockablePaneData.m_strRegionText.GetSize());
	m_cStaticU.SetSize(g_myDockablePaneData.m_strRegionText.GetSize());
	m_cStaticI.SetSize(g_myDockablePaneData.m_strRegionText.GetSize());
	m_cStaticP.SetSize(g_myDockablePaneData.m_strRegionText.GetSize());
	m_cU.SetSize(g_myDockablePaneData.m_strRegionText.GetSize());
	m_cI.SetSize(g_myDockablePaneData.m_strRegionText.GetSize());
	m_cP.SetSize(g_myDockablePaneData.m_strRegionText.GetSize());
	for (i = 0; i < m_cRegionName.GetSize(); i++)
	{
		m_cRegionName.GetAt(i).Create(g_myDockablePaneData.m_strRegionText.GetAt(i),
			WS_VISIBLE | WS_CHILD | BS_GROUPBOX, CRect(0, 0, 0, 0), this, 40400 + i);
		m_cRegionName.GetAt(i).SetFont(GetFont());
	}

	for (i = 0; i < m_cRegionName.GetSize(); i ++)
	{
		m_cStaticU.GetAt(i).Create("电压(V)", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_CENTER, CRect(0, 0, 0, 0), this, 40500 + i);
		m_cStaticU.GetAt(i).SetFont(GetFont());     
		m_cStaticI.GetAt(i).Create("电流(A)", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_CENTER, CRect(0, 0, 0, 0), this, 40600 + i);
		m_cStaticI.GetAt(i).SetFont(GetFont());     
		m_cStaticP.GetAt(i).Create("功率(W)", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_CENTER, CRect(0, 0, 0, 0), this, 40700 + i);
		m_cStaticP.GetAt(i).SetFont(GetFont());
		m_cU.GetAt(i).Create("----", WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0), this, 40800 + i);
		m_cU.GetAt(i).put_Font((LPFONTDISP)m_cSample.get_Font());
		m_cU.GetAt(i).put_ErrorFont((LPFONTDISP)m_cSample.get_Font());
		m_cU.GetAt(i).SetFont(&m_font);
		m_cU.GetAt(i).put_ErrorActive(TRUE);
		m_cU.GetAt(i).put_ErrorText("----");   
		m_cU.GetAt(i).put_BackGroundColor(RGB(0, 0, 0));
		m_cU.GetAt(i).put_ErrorBackGroundColor(RGB(0, 0, 0));
		m_cU.GetAt(i).put_ErrorFontColor(RGB(128, 128, 128));
		m_cU.GetAt(i).put_Alignment(CIanalogdisplayx_tmp1::iahCenter);
		m_cU.GetAt(i).SetWindowPos(NULL,0, 0, 0, 0,SWP_SHOWWINDOW);

		m_cI.GetAt(i).Create("----", WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0), this, 40900 + i);
		m_cI.GetAt(i).put_Font((LPFONTDISP)m_cSample.get_Font());
		m_cI.GetAt(i).put_ErrorFont((LPFONTDISP)m_cSample.get_Font());
		m_cI.GetAt(i).SetFont(&m_font);
		m_cI.GetAt(i).put_ErrorActive(TRUE);
		m_cI.GetAt(i).put_ErrorText("----");
		m_cI.GetAt(i).put_BackGroundColor(RGB(0, 0, 0));
		m_cI.GetAt(i).put_ErrorBackGroundColor(RGB(0, 0, 0));
		m_cI.GetAt(i).put_ErrorFontColor(RGB(128, 128, 128));
		m_cI.GetAt(i).put_Alignment(CIanalogdisplayx_tmp1::iahCenter);
		m_cI.GetAt(i).SetWindowPos(NULL,0, 0, 0, 0,SWP_SHOWWINDOW);

		m_cP.GetAt(i).Create("----", WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0), this, 41000 + i);
		m_cP.GetAt(i).put_Font((LPFONTDISP)m_cSample.get_Font());
		m_cP.GetAt(i).put_ErrorFont((LPFONTDISP)m_cSample.get_Font());
		m_cP.GetAt(i).SetFont(&m_font);
		m_cP.GetAt(i).put_ErrorActive(TRUE);
		m_cP.GetAt(i).put_ErrorText("----");
		m_cP.GetAt(i).put_BackGroundColor(RGB(0, 0, 0));
		m_cP.GetAt(i).put_ErrorBackGroundColor(RGB(0, 0, 0));
		m_cP.GetAt(i).put_ErrorFontColor(RGB(128, 128, 128));
		m_cP.GetAt(i).put_Alignment(CIanalogdisplayx_tmp1::iahCenter);
		m_cP.GetAt(i).SetWindowPos(NULL,0, 0, 0, 0,SWP_SHOWWINDOW);
	}
}

void CContainerWatchView::SetPos()
{
	CRect clRect;
	GetClientRect(clRect);
	if (1)
	{
		//温度监视排布
		CRect tmpNameRect1;
		CRect tmpNameRect2;
		CRect tmpNameRect3;
		CRect tmpNameRect4;
		CRect dStaticRect;
		CRect dTmpRect;
		CRect dSetRect;
		CRect dSetEditRect;
		CRect tmpRect;
		GetDlgItem(IDC_STATIC_TMP_NAME)->GetClientRect(tmpNameRect1);
		GetDlgItem(IDC_STATIC_TMP_NAME2)->GetClientRect(tmpNameRect2);
		GetDlgItem(IDC_STATIC_TMP_NAME3)->GetClientRect(tmpNameRect3);
		GetDlgItem(IDC_STATIC_TMP_NAME4)->GetClientRect(tmpNameRect4);
		GetDlgItem(IDC_STATIC_TMP1)->GetClientRect(dStaticRect);
		GetDlgItem(IDC_IANALOGDISPLAYX_TMP1)->GetClientRect(dTmpRect);
 		GetDlgItem(IDC_STATIC_SET_TMP)->GetClientRect(dSetRect);
		GetDlgItem(IDC_IEDITX_TMP1)->GetClientRect(dSetEditRect);
		for (int i = 0; i < m_cTMPConName.GetSize(); i ++)
		{
			if (i < 4)
			{
				tmpRect.top		= tmpNameRect1.top - 5 + (i + 1) * tmpNameRect1.Height() / 5;
				tmpRect.bottom	= tmpRect.top + dStaticRect.Height();
				tmpRect.left	= tmpNameRect1.left + 20;
				tmpRect.right	= tmpRect.left + dStaticRect.Width();
				m_cTMPConName.GetAt(i).MoveWindow(tmpRect);

				tmpRect.top		= tmpNameRect1.top - 10 + (i + 1) * tmpNameRect1.Height() / 5;
				tmpRect.bottom	= tmpRect.top + dTmpRect.Height();
				tmpRect.left	= tmpRect.right + 10;
				tmpRect.right	= tmpRect.left + dTmpRect.Width();
				m_cTMP.GetAt(i).MoveWindow(tmpRect);

				if (i == 0)
				{
					tmpRect.top		= tmpNameRect1.top - 5 + (i + 1) * tmpNameRect1.Height() / 5;
					tmpRect.bottom	= tmpRect.top + dSetRect.Height();
					tmpRect.left	= tmpRect.right + 10;
					tmpRect.right	= tmpRect.left + dSetRect.Width();
					m_cStaticSetTMP.GetAt(i).MoveWindow(tmpRect);

					tmpRect.top		= tmpNameRect1.top - 10 + (i + 1) * tmpNameRect1.Height() / 5;
					tmpRect.bottom	= tmpRect.top + dSetEditRect.Height();
					tmpRect.left	= tmpRect.right + 10;
					tmpRect.right	= tmpRect.left + dSetEditRect.Width();
					m_cSetTMP.GetAt(i).MoveWindow(tmpRect);
				}
			}
			else if (i < 8)
			{
				tmpRect.top		= tmpNameRect2.top - 5 + (i - 4 + 1) * tmpNameRect2.Height() / 5;
				tmpRect.bottom	= tmpRect.top + dStaticRect.Height();
				tmpRect.left	= tmpNameRect1.right + 30;
				tmpRect.right	= tmpRect.left + dStaticRect.Width();
				m_cTMPConName.GetAt(i).MoveWindow(tmpRect);

				tmpRect.top		= tmpNameRect2.top - 10 + (i - 4 + 1) * tmpNameRect2.Height() / 5;
				tmpRect.bottom	= tmpRect.top + dTmpRect.Height();
				tmpRect.left	= tmpRect.right + 10;
				tmpRect.right	= tmpRect.left + dTmpRect.Width();
				m_cTMP.GetAt(i).MoveWindow(tmpRect);

				if (i == 4)
				{
					tmpRect.top		= tmpNameRect2.top - 5 + (i - 4 + 1) * tmpNameRect2.Height() / 5;
					tmpRect.bottom	= tmpRect.top + dSetRect.Height();
					tmpRect.left	= tmpRect.right + 10;
					tmpRect.right	= tmpRect.left + dSetRect.Width();
					m_cStaticSetTMP.GetAt(i).MoveWindow(tmpRect);

					tmpRect.top		= tmpNameRect2.top - 10 + (i - 4 + 1) * tmpNameRect2.Height() / 5;
					tmpRect.bottom	= tmpRect.top + dSetEditRect.Height();
					tmpRect.left	= tmpRect.right + 10;
					tmpRect.right	= tmpRect.left + dSetEditRect.Width();
					m_cSetTMP.GetAt(i).MoveWindow(tmpRect);
				}
			}
			else if (i < 12)
			{
				tmpRect.top		= tmpNameRect1.bottom + 30 - 5 + (i - 8 + 1) * tmpNameRect1.Height() / 5;
				tmpRect.bottom	= tmpRect.top + dStaticRect.Height();
				tmpRect.left	= tmpNameRect1.left + 20;
				tmpRect.right	= tmpRect.left + dStaticRect.Width();
				m_cTMPConName.GetAt(i).MoveWindow(tmpRect);

				tmpRect.top		= tmpNameRect1.bottom + 30 - 10 + (i - 8 + 1) * tmpNameRect1.Height() / 5;
				tmpRect.bottom	= tmpRect.top + dTmpRect.Height();
				tmpRect.left	= tmpRect.right + 10;
				tmpRect.right	= tmpRect.left + dTmpRect.Width();
				m_cTMP.GetAt(i).MoveWindow(tmpRect);

				if (i == 8)
				{
					tmpRect.top		= tmpNameRect1.bottom + 30 - 5 + (i - 8 + 1) * tmpNameRect1.Height() / 5;
					tmpRect.bottom	= tmpRect.top + dSetRect.Height();
					tmpRect.left	= tmpRect.right + 10;
					tmpRect.right	= tmpRect.left + dSetRect.Width();
					m_cStaticSetTMP.GetAt(i).MoveWindow(tmpRect);

					tmpRect.top		= tmpNameRect1.bottom + 30 - 10 + (i - 8 + 1) * tmpNameRect1.Height() / 5;
					tmpRect.bottom	= tmpRect.top + dSetEditRect.Height();
					tmpRect.left	= tmpRect.right + 10;
					tmpRect.right	= tmpRect.left + dSetEditRect.Width();
					m_cSetTMP.GetAt(i).MoveWindow(tmpRect);
				}
			}
			else
			{
				tmpRect.top		= tmpNameRect1.bottom + 30 - 5 + (i - 12 + 1) * tmpNameRect1.Height() / 5;
				tmpRect.bottom	= tmpRect.top + dStaticRect.Height();
				tmpRect.left	= tmpNameRect1.right + 30;
				tmpRect.right	= tmpRect.left + dStaticRect.Width();
				m_cTMPConName.GetAt(i).MoveWindow(tmpRect);

				tmpRect.top		= tmpNameRect1.bottom + 30 - 10 + (i - 12 + 1) * tmpNameRect1.Height() / 5;
				tmpRect.bottom	= tmpRect.top + dTmpRect.Height();
				tmpRect.left	= tmpRect.right + 10;
				tmpRect.right	= tmpRect.left + dTmpRect.Width();
				m_cTMP.GetAt(i).MoveWindow(tmpRect);

				if (i == 12)
				{
					tmpRect.top		= tmpNameRect1.bottom + 30 - 5 + (i - 12 + 1) * tmpNameRect1.Height() / 5;
					tmpRect.bottom	= tmpRect.top + dSetRect.Height();
					tmpRect.left	= tmpRect.right + 10;
					tmpRect.right	= tmpRect.left + dSetRect.Width();
					m_cStaticSetTMP.GetAt(i).MoveWindow(tmpRect);

					tmpRect.top		= tmpNameRect1.bottom + 30 - 10 + (i - 12 + 1) * tmpNameRect1.Height() / 5;
					tmpRect.bottom	= tmpRect.top + dSetEditRect.Height();
					tmpRect.left	= tmpRect.right + 10;
					tmpRect.right	= tmpRect.left + dSetEditRect.Width();
					m_cSetTMP.GetAt(i).MoveWindow(tmpRect);
				}
			}
		}
// 	}
// 
// 	if (1)
// 	{
		//表头监控排布
		CRect regionRect;
		CRect dRectU;
		CRect dRectI;
		CRect dRectP;
		CRect dRectStaticU;
		CRect dRectStaticI;
		CRect dRectStaticP;
		GetDlgItem(IDC_STATIC_REGION1)->GetClientRect(regionRect);
		GetDlgItem(IDC_STATIC_VOL)->GetClientRect(dRectStaticU);
		GetDlgItem(IDC_STATIC_CUR)->GetClientRect(dRectStaticI);
		GetDlgItem(IDC_STATIC_POW)->GetClientRect(dRectStaticP);
		GetDlgItem(IDC_IANALOGDISPLAYX_U1)->GetClientRect(dRectU);
		GetDlgItem(IDC_IANALOGDISPLAYX_I1)->GetClientRect(dRectI);
		GetDlgItem(IDC_IANALOGDISPLAYX_P1)->GetClientRect(dRectP);
		int iW1 = regionRect.Width();
		int iH1 = regionRect.Height();
		int iW2 = dRectStaticU.Width();
		int iH2 = dRectStaticU.Height();
		int iW3 = dRectU.Width();
		int iH3 = dRectU.Height();

		for (int i = 0; i < m_cRegionName.GetSize(); i++)
		{
			if (i < 6)
			{
				if (i!=0)
				{
					regionRect.top	= regionRect.bottom + 10;
				}
				else
				{
					regionRect.top	= tmpNameRect1.top + 10;
				}
				
				regionRect.left		= tmpNameRect1.left + tmpNameRect1.Width() * 2 + 20;
				regionRect.right	= regionRect.left + iW1;
				regionRect.bottom	= regionRect.top + iH1;
				m_cRegionName[i].MoveWindow(regionRect);

				dRectStaticU.top	= regionRect.top + 20;
				dRectStaticU.left	= regionRect.left + 5;
				dRectStaticU.right	= dRectStaticU.left + iW2;
				dRectStaticU.bottom	= dRectStaticU.top + iH2;
				m_cStaticU[i].MoveWindow(dRectStaticU);
				
				dRectStaticI.top	= dRectStaticU.top;
				dRectStaticI.left	= dRectStaticU.right + 10;
				dRectStaticI.right	= dRectStaticI.left + iW2;
				dRectStaticI.bottom	= dRectStaticI.top + iH2;
				m_cStaticI[i].MoveWindow(dRectStaticI);

				dRectStaticP.top	= dRectStaticU.top;
				dRectStaticP.left	= dRectStaticI.right + 20;
				dRectStaticP.right	= dRectStaticP.left + iW2;
				dRectStaticP.bottom	= dRectStaticP.top + iH2;
				m_cStaticP[i].MoveWindow(dRectStaticP);
				
				dRectU.top		= dRectStaticU.bottom + 5; 
				dRectU.left		= dRectStaticU.left + 5;
				dRectU.right	= dRectU.left + iW3;
				dRectU.bottom	= dRectU.top + iH3;
				m_cU[i].MoveWindow(dRectU);

				dRectI.top		= dRectU.top; 
				dRectI.left		= dRectU.right + 10;
				dRectI.right	= dRectI.left + iW3;
				dRectI.bottom	= dRectU.bottom;
				m_cI[i].MoveWindow(dRectI);

				dRectP.top		= dRectU.top; 
				dRectP.left		= dRectI.right + 10;
				dRectP.right	= dRectP.left + iW3;
				dRectP.bottom	= dRectU.bottom;
				m_cP[i].MoveWindow(dRectP);
			}
			else
			{
				if (i!=6)
				{
					regionRect.top	= regionRect.bottom + 10;
				}
				else
				{
					regionRect.top	= tmpNameRect1.top + 10;
				}

				regionRect.left		= tmpNameRect1.left + tmpNameRect1.Width() * 3 + 30;
				regionRect.right	= regionRect.left + iW1;
				regionRect.bottom	= regionRect.top + iH1;
				m_cRegionName[i].MoveWindow(regionRect);

				dRectStaticU.top	= regionRect.top + 20;
				dRectStaticU.left	= regionRect.left + 5;
				dRectStaticU.right	= dRectStaticU.left + iW2;
				dRectStaticU.bottom	= dRectStaticU.top + iH2;
				m_cStaticU[i].MoveWindow(dRectStaticU);

				dRectStaticI.top	= dRectStaticU.top;
				dRectStaticI.left	= dRectStaticU.right + 10;
				dRectStaticI.right	= dRectStaticI.left + iW2;
				dRectStaticI.bottom	= dRectStaticI.top + iH2;
				m_cStaticI[i].MoveWindow(dRectStaticI);

				dRectStaticP.top	= dRectStaticU.top;
				dRectStaticP.left	= dRectStaticI.right + 20;
				dRectStaticP.right	= dRectStaticP.left + iW2;
				dRectStaticP.bottom	= dRectStaticP.top + iH2;
				m_cStaticP[i].MoveWindow(dRectStaticP);

				dRectU.top		= dRectStaticU.bottom + 5; 
				dRectU.left		= dRectStaticU.left + 5;
				dRectU.right	= dRectU.left + iW3;
				dRectU.bottom	= dRectU.top + iH3;
				m_cU[i].MoveWindow(dRectU);

				dRectI.top		= dRectU.top; 
				dRectI.left		= dRectU.right + 10;
				dRectI.right	= dRectI.left + iW3;
				dRectI.bottom	= dRectU.bottom;
				m_cI[i].MoveWindow(dRectI);

				dRectP.top		= dRectU.top; 
				dRectP.left		= dRectI.right + 10;
				dRectP.right	= dRectP.left + iW3;
				dRectP.bottom	= dRectU.bottom;
				m_cP[i].MoveWindow(dRectP);
			}
		}
	}
}

void CContainerWatchView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (!m_bFir)
	{
		SetPos();
	}
}

void CContainerWatchView::OnBnClickedButtonTmpOn()
{
	// TODO: 在此添加控件通知处理程序代码
	//温控一区
	UpdateData(TRUE);
	BeginWaitCursor();
	float fSetTMP;
	float fSetTMPUp;
	float fSetTMPDown;
	float fSetOpen;
	for (int i = 0; i < g_myDockablePaneData.m_strSetTMP.GetSize(); i++)
	{
		if(1)//i % 4 == 0)
		{
			fSetTMP = (float)atof(m_cSetTMP[i].get_Value());
			g_myDockablePaneData.m_strSetTMP[i] = m_cSetTMP[i].get_Value();
			fSetTMPDown = g_myDockablePaneData.m_TemperatureController[i].m_fTMPDown;
			fSetTMPUp = g_myDockablePaneData.m_TemperatureController[i].m_fTMPUp;
			fSetOpen = g_myDockablePaneData.m_TemperatureController[i].m_fTMPOpen;
		}

		if ( fSetTMP < 0 || fSetTMP > 50 )
		{
			AfxMessageBox("温度应该在0 ~ 50度之间！");
			return;
		}

		if (!g_FujiTMPComm.SetTemperature(g_FujiTMPComm.m_ucAddress[i], fSetTMP, fSetTMPDown, fSetOpen) )
		{
			Sleep(100);
			if (!g_FujiTMPComm.SetTemperature(g_FujiTMPComm.m_ucAddress[i], fSetTMP, fSetTMPDown, fSetOpen) )
			{
				Sleep(100);
				if (!g_FujiTMPComm.SetTemperature(g_FujiTMPComm.m_ucAddress[i], fSetTMP, fSetTMPDown, fSetOpen) )
				{
					AfxMessageBox("设置失败！");
					return;
				}
			}
		}
	}

	EndWaitCursor();

	BeginWaitCursor();
	// 
	g_bTMPControllerON = TRUE;
	GetDlgItem(IDC_BUTTON_TMP_ON)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TMP_OFF)->EnableWindow(TRUE);
	AfxMessageBox("启动成功！");
	EndWaitCursor();
}

void CContainerWatchView::OnBnClickedButtonTmpOff()
{
	// TODO: 在此添加控件通知处理程序代码
	//温控一区
 	BeginWaitCursor();
	for (int i = 0; i < g_myDockablePaneData.m_strSetTMP.GetSize(); i ++)
	{
		if (!g_FujiTMPComm.SetTemperature(g_FujiTMPComm.m_ucAddress[i], 0, 0 ,0))
		{
			Sleep(100);
			if (!g_FujiTMPComm.SetTemperature(g_FujiTMPComm.m_ucAddress[i], 0 ,0 ,0))
			{
				Sleep(100);
				if (!g_FujiTMPComm.SetTemperature(g_FujiTMPComm.m_ucAddress[i], 0, 0 ,0))
				{
					AfxMessageBox("设置失败！");
					return ;
				}
			}
		}
	}
	EndWaitCursor();

	g_bTMPControllerON = FALSE;
	GetDlgItem(IDC_BUTTON_TMP_ON)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TMP_OFF)->EnableWindow(FALSE);
	AfxMessageBox("停止成功！");
}

void CContainerWatchView::OnBnClickedButtonTmpOn2()
{
	// TODO: 在此添加控件通知处理程序代码
	//温控二区
}


void CContainerWatchView::OnBnClickedButtonTmpOff3()
{
	// TODO: 在此添加控件通知处理程序代码
	//温控二区
}


void CContainerWatchView::OnBnClickedButtonTmpOn4()
{
	// TODO: 在此添加控件通知处理程序代码
	//温控三区
}


void CContainerWatchView::OnBnClickedButtonTmpOff5()
{
	// TODO: 在此添加控件通知处理程序代码
	//温控三区
}


void CContainerWatchView::OnBnClickedButtonTmpOn3()
{
	// TODO: 在此添加控件通知处理程序代码
	//温控四区
}


void CContainerWatchView::OnBnClickedButtonTmpOff4()
{
	// TODO: 在此添加控件通知处理程序代码
	//温控四区
}
