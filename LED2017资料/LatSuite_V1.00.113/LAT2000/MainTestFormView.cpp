// LED850FormView.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "MainTestFormView.h"
#include "MainFrm.h"
#include "NoneBorderDlg.h"




extern CString g_strLimitDataPath;
extern CEvent g_EventOlding;

HACCEL g_hAccel = NULL;
// CMainTestFormView

IMPLEMENT_DYNCREATE(CMainTestFormView, CFormView)
CMainTestFormView *g_pMainTestFormView;

CMainTestFormView::CMainTestFormView()
	: CFormView(CMainTestFormView::IDD)
{
	m_ucItemShowFlag = SHOW_FLUX | SHOW_TC | SHOW_XY;

	m_iCheckLEDCount = 0;

	m_eAlarmType = AT_NOME;
	m_bIsAlarming = FALSE;
	m_bStopAlarming = FALSE;
	m_bMessageIsShowing = FALSE;
}

CMainTestFormView::~CMainTestFormView()
{
}

void CMainTestFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMainTestFormView, CFormView)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR()
	ON_WM_CONTEXTMENU()
	ON_WM_INITMENUPOPUP()
	ON_UPDATE_COMMAND_UI(ID_POP_FLUX, &CMainTestFormView::OnUpdatePopFlux)
	ON_COMMAND(ID_POP_FLUX, &CMainTestFormView::OnPopFlux)
	ON_UPDATE_COMMAND_UI(ID_POP_TC, &CMainTestFormView::OnUpdatePopTc)
	ON_COMMAND(ID_POP_TC, &CMainTestFormView::OnPopTc)
	ON_UPDATE_COMMAND_UI(ID_POP_XY, &CMainTestFormView::OnUpdatePopXy)
	ON_COMMAND(ID_POP_XY, &CMainTestFormView::OnPopXy)
	ON_UPDATE_COMMAND_UI(ID_POP_UV, &CMainTestFormView::OnUpdatePopUv)
	ON_COMMAND(ID_POP_UV, &CMainTestFormView::OnPopUv)
	ON_UPDATE_COMMAND_UI(ID_POP_LD, &CMainTestFormView::OnUpdatePopLd)
	ON_COMMAND(ID_POP_LD, &CMainTestFormView::OnPopLd)
	ON_UPDATE_COMMAND_UI(ID_POP_DISPERSION, &CMainTestFormView::OnUpdatePopDispersion)
	ON_COMMAND(ID_POP_DISPERSION, &CMainTestFormView::OnPopDispersion)
	//ON_COMMAND(ID_STOP_BUZZER, &CMainTestFormView::OnMenuStopBuzzer)
	//ON_UPDATE_COMMAND_UI(ID_STOP_BUZZER, &CMainTestFormView::OnUpdateMenuStopBuzzer)
	ON_BN_CLICKED(IDC_BUTTON_TEST_FAIL, &CMainTestFormView::OnBnClickedButtonTestFail)
	ON_BN_CLICKED(IDC_BUTTON_BAD, &CMainTestFormView::OnBnClickedButtonBad)
	ON_BN_CLICKED(IDC_BUTTON_NONE, &CMainTestFormView::OnBnClickedButtonNone)
	ON_BN_CLICKED(IDC_BUTTON_REVERSE, &CMainTestFormView::OnBnClickedButtonReverse)
	ON_BN_CLICKED(IDC_BUTTON_GOOD, &CMainTestFormView::OnBnClickedButtonGood)
	ON_CBN_KILLFOCUS(IDC_COMBO_FILE, &CMainTestFormView::OnKillfocusComboFile)
	ON_MESSAGE(MSG_TEST_STARTED, &CMainTestFormView::OnMsgStartTest)
	ON_MESSAGE(MSG_LED_RELIST, &CMainTestFormView::OnMsgReListLED)
	ON_MESSAGE(MSG_TEST_ENDED, &CMainTestFormView::OnMsgTestEnded)
	ON_MESSAGE(MSG_SHOW_NONE_BRODER_MESSAGE, &CMainTestFormView::OnMsgShowMessage)
	ON_UPDATE_COMMAND_UI(ID_MENU_PRINT, &CMainTestFormView::OnUpdateMenuPrint)
	ON_COMMAND(ID_MENU_PRINT, &CMainTestFormView::OnMenuPrint)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_RESET_STATISTICS, &CMainTestFormView::OnResetStatistics)
END_MESSAGE_MAP()


// CMainTestFormView 诊断

#ifdef _DEBUG
void CMainTestFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMainTestFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMainTestFormView 消息处理程序


void CMainTestFormView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CFormView::OnPaint()
	
	// Draw scale
	CLAT2000Doc * pDoc = (CLAT2000Doc *)GetDocument();
	if (NULL == pDoc)
	{
		return;
	}

	dc.SetBkMode(TRANSPARENT);
	CSize size1 = dc.GetOutputTextExtent("1");
	CRect rectClient;
	GetClientRect(&rectClient);
	CRect rectX = rectClient, rectY = rectClient;
	rectX.left += 25;
	rectX.bottom = rectX.top + 25;
	rectY.top += 25;
	rectY.bottom -= rectClient.Height() / 3;
	rectY.right = rectY.left + 25;

	int iX = rectX.Width() / pDoc->m_TestContainer.GetLEDColumnSize();
	int iY = rectY.Height() / pDoc->m_TestContainer.GetLEDRowSize();
	for (int i = 0; i < pDoc->m_TestContainer.GetLEDColumnSize(); i++)
	{
		dc.SetTextAlign(TA_CENTER);
		CString strTemp;
		strTemp.Format("%d", i + 1);
		dc.TextOut(rectX.left + i * iX + iX / 2, 0, strTemp);
	}
	for (int i = 0; i < pDoc->m_TestContainer.GetLEDRowSize(); i++)
	{
		if (0 == i)
		{
			dc.SetTextColor(RGB(0, 0, 255));
		}
		else
		{
			dc.SetTextColor(RGB(0, 0, 0));
		}
		dc.SetTextAlign(TA_LEFT);
		CString strTemp;
		strTemp.Format("%d", i + 1);
		dc.TextOut(0, rectY.top + i * iY + iY / 2 - size1.cy / 2, strTemp);
	}

}
BEGIN_EVENTSINK_MAP(CMainTestFormView, CFormView)
END_EVENTSINK_MAP()


int CMainTestFormView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect rect(10, 10, 10, 10);
	m_cColorDemo.Create(NULL, SS_BLACKFRAME, rect, this, ID_COLORDEMO);

	// Create a child static control that centers its text horizontally.
	m_cOtherInfo.Create(_T("Test Information"), WS_CHILD | SS_CENTER,
		CRect(10,10,150,50), this);

	//::PostMessage(m_hWnd, WM_SIZE, 0, 0);
    CLAT2000Doc *pDoc = (CLAT2000Doc*)GetDocument();
    pDoc->m_pShowOldTime = new CDlgShowOldingTime;
    pDoc->m_pShowOldTime->Create(IDD_DIALOG_SHOW_OLDING_STATE, NULL);
    pDoc->m_pShowOldTime->ShowWindow(SW_HIDE);  
	return 0;
}


void CMainTestFormView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	ShowLEDIndicator();
	
	// rect1 | rect2
	CRect rect;
	GetClientRect(&rect);
	rect.top = rect.bottom - rect.Height() / 3;
	rect.DeflateRect(5, 5);
	CRect rect1 = rect, rect2 = rect;
	rect2.top = rect1.top;
	rect2.left = rect2.right - rect2.Width() * 3 / 10;
	rect1.right = rect2.left;
    rect2.DeflateRect(CSize(5, 5));
	GetDlgItem(ID_COLORDEMO)->MoveWindow(&rect2);
	GetDlgItem(ID_COLORDEMO)->ShowWindow(SW_SHOW);

	// rect31  rect32
	// rect33  rect34
	//CRect rect31 = rect3, rect32 = rect3, rect33 = rect3, rect34 = rect3;
	//rect31.right = rect31.left + rect31.Width() / 2;
	//rect31.bottom = rect31.top + rect31.Height() / 2;
	//rect32.left = rect31.right;
	//rect32.bottom = rect31.bottom;
	//rect33.right = rect31.right;
	//rect33.top = rect31.bottom;
	//rect34.left = rect31.right;
	//rect34.top = rect31.bottom;
	//rect31.DeflateRect(CSize(5, 5));
	//rect32.DeflateRect(CSize(5, 5));
	//rect33.DeflateRect(CSize(5, 5));
	//rect34.DeflateRect(CSize(5, 5));
	//if (IsWindow(GetDlgItem(IDC_BUTTON_SYSTEM_ON)->GetSafeHwnd()))
	//{
	//	GetDlgItem(IDC_BUTTON_SYSTEM_ON)->MoveWindow(&rect31);
	//	GetDlgItem(IDC_BUTTON_SYSTEM_OFF)->MoveWindow(&rect33);
	//	GetDlgItem(IDC_BUTTON_TMP_ON)->MoveWindow(&rect32);
	//	GetDlgItem(IDC_BUTTON_TMP_OFF)->MoveWindow(&rect34);
	//}

	//       rect1T
	// ------------------
	// rect1BL   rect1BR
	//rect1.right -= rect1.Width() / 8;
	//rect1.top += rect1.Height() / 4;
	//CRect rect1T = rect1, rect1BL = rect1, rect1BR = rect1;
	//rect1T.bottom = rect1T.top + rect1T.Height() / 2;
	//rect1BL.top = rect1T.bottom;
	//rect1BL.right = rect1BL.left + rect1BL.Width() / 2;
	//rect1BR.top = rect1T.bottom;
	//rect1BR.left = rect1BL.right;
	//rect1T.DeflateRect(CSize(2, 2));
	//rect1BL.DeflateRect(CSize(2, 2));
	//rect1BR.DeflateRect(CSize(2, 2));

    rect1.DeflateRect(CSize(5, 5));
    m_cOtherInfo.MoveWindow(&rect1);
    m_cOtherInfo.ShowWindow(SW_SHOW);

    CLAT2000Doc *pDoc = (CLAT2000Doc*)GetDocument();

    if (NULL != pDoc->m_pShowOldTime)
    {
        pDoc->m_pShowOldTime->SetWindowPos(&wndTopMost, 300, 350, 0, 0,  SWP_NOSIZE);
    }

}


void CMainTestFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	if (NULL == g_pDoc)
	{
		return;
	}
    g_pMainTestFormView = this;
	m_cOtherInfo.SetLineState(Free);
	g_pDoc->m_hWndTestFormView = m_hWnd;
	m_cOtherInfo.SetBurnInInfo(g_pDoc->m_dataContainer.GetTestSettingData().m_iBurnInONSeconds, g_pDoc->m_dataContainer.GetTestSettingData().m_iBurnInOFFSeconds);

	g_hAccel = LoadAccelerators(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));

	Invalidate(TRUE);

	InitLEDIndicator();

	g_pDoc->GetCurrentData();
	ShowLEDIndicator();
	UpdateLEDIndicator();
	//if (pDoc->GetTestedLEDNumber() > 0)
	//{
	//	int iIndex = m_cComboFileList.FindString(0, "Temp.dat");
	//	if (iIndex >= 0)
	//	{
	//		m_cComboFileList.SetCurSel(iIndex);
	//	}
	//}

	SetActiveWindow();

	AfxBeginThread(ThreadGetLineState, this);
	AfxBeginThread(ThreadAlarmPlayRing, this);
    g_EventOlding.SetEvent();
}


LRESULT CMainTestFormView::OnMsgStartTest(UINT wParam, LONG lParam)
{
	m_iRowIndex = 0;
	m_iColumnIndex = 0;
	
	// Test start, begin update indicator
	SetTimer(1, 200, NULL);

	return 0;
}


LRESULT CMainTestFormView::OnMsgReListLED(UINT wParam, LONG lParam)
{
	CLAT2000Doc * pDoc = (CLAT2000Doc *)GetDocument();

	Invalidate(TRUE);

	ShowLEDIndicator();

	return 0;
}


void CMainTestFormView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// Update the picture

	if (1 == nIDEvent)
	{
		UpdateLEDIndicator();

		if (!g_pDoc->IsRunning())
		{
			KillTimer(nIDEvent);
		}
	}

	//((CMainFrame *)AfxGetMainWnd())->GetStatusBar().EnablePaneProgressBar(3, lTotal, TRUE);
	//((CMainFrame *)AfxGetMainWnd())->GetStatusBar().SetPaneProgress(3, (UINT)iTestNumber);
}


void CMainTestFormView::ListLimitFile()
{
	//CLAT2000Doc * pDoc = (CLAT2000Doc *)GetDocument();
	//if (NULL == pDoc)
	//{
	//	return;
	//}

	//if (IsWindow(m_cComboFileList.GetSafeHwnd()))
	//{
	//	WIN32_FIND_DATA findFileData;
	//	m_cComboFileList.ResetContent();
	//	HANDLE hFind = FindFirstFile(g_strLimitDataPath + "*.dat", &findFileData);
	//	if (INVALID_HANDLE_VALUE == hFind)
	//	{
	//		return;
	//	}

	//	BOOL bFind = TRUE;
	//	while(bFind)
	//	{
	//		m_cComboFileList.InsertString(0, findFileData.cFileName);
	//		bFind = FindNextFile(hFind, &findFileData);
	//	}

	//	int iIndex = m_cComboFileList.FindString(0, pDoc->m_strLimitDataFileName);
	//	m_cComboFileList.SetCurSel(iIndex);
	//	m_cComboFileList.RedrawWindow();
	//}
}

void CMainTestFormView::InitLEDIndicator()
{
	CLAT2000Doc * pDoc = (CLAT2000Doc *)GetDocument();
	if (NULL == pDoc)
	{
		return;
	}

	m_LEDIndicator.RemoveAll();
	int iCount = pDoc->m_TestContainer.GetLEDColumnSize() * pDoc->m_TestContainer.GetLEDRowSize();
	m_LEDIndicator.SetSize(iCount);
	for (int i = 0; i < pDoc->m_TestContainer.GetLEDRowSize(); i++)
	{
		for (int j = 0; j < pDoc->m_TestContainer.GetLEDColumnSize(); j++)
		{
			int iIndex = pDoc->m_TestContainer.GetIndex(i, j);
			m_LEDIndicator[iIndex].Create("", SS_BLACKFRAME | SS_NOTIFY, CRect(0, 0, 10, 10), this, iIndex + 50000);
		}
	}
}

void CMainTestFormView::ShowLEDIndicator()
{
	CLAT2000Doc * pDoc = (CLAT2000Doc *)GetDocument();
	if (NULL == pDoc || 0 == m_LEDIndicator.GetSize())
	{
		return;
	}
	if ( !IsWindow(m_LEDIndicator[0].GetSafeHwnd()) )
	{
		return;
	}

	for (int iRow = 0; iRow < pDoc->m_TestContainer.GetLEDRowSize(); iRow++)
	{
		for (int iCol = 0; iCol < pDoc->m_TestContainer.GetLEDColumnSize(); iCol++)
		{
			int iLEDIndex = pDoc->m_TestContainer.GetIndex(iRow, iCol);
			CRect rect;
			GetItemRect(iCol, iRow, rect);
			m_LEDIndicator[iLEDIndex].MoveWindow(&rect);
			m_LEDIndicator[iLEDIndex].ShowWindow(SW_SHOW);

			// The latest tested LED's data may not be ready
			LEDState & state = pDoc->m_TestContainer.GetLEDState(iRow, iCol);
            if (state.IsSuccessful())
            {
                CString strTemp;
                strTemp.Format("%-3d - LED(%2d,%2d)\n\n", iLEDIndex + 1, iRow + 1, iCol + 1);
                if (pDoc->m_TestContainer.GetLEDData(iRow, iCol).IsLEDON())
                {
					int iTypeFail= 0;
                    if ( pDoc->m_dataContainer.GetTestSettingData().IsQulified(pDoc->m_TestContainer.GetLEDData(iRow, iCol),iTypeFail) )
                    {
                        m_LEDIndicator[iLEDIndex].SetColor(g_ColorGood);                 
                    }
                    else
                    {
                        m_LEDIndicator[iLEDIndex].SetColor(g_ColorBad);                 
                    }
                    strTemp += pDoc->m_TestContainer.GetInfoString(iRow, iCol, TRUE);
                }
                else
                {
                    m_LEDIndicator[iLEDIndex].SetColor(g_ColorBad_Codi);  
                    strTemp += pDoc->m_TestContainer.GetInfoString(iRow, iCol, FALSE);
                }
                m_LEDIndicator[iLEDIndex].SetTooltip(strTemp);  
            }
            else if (state.IsTested())
            {
                m_LEDIndicator[iLEDIndex].SetColor(g_ColorInvalid);

                CString strTemp;
                strTemp.Format("%-3d - LED(%2d,%2d)\n\nTest Fail", iLEDIndex + 1, iRow + 1, iCol + 1);
                m_LEDIndicator[iLEDIndex].SetTooltip(strTemp);
            }
            else
            {
                // Not test
                m_LEDIndicator[iLEDIndex].SetColor(g_ColorNotTest);

                CString strTemp;
                strTemp.Format("%-3d - LED(%2d,%2d)\n\nNot Test", iLEDIndex + 1, iRow + 1, iCol + 1);
                m_LEDIndicator[iLEDIndex].SetTooltip(strTemp);
            }
		}
	}
}


void CMainTestFormView::UpdateLEDIndicator()
{
	CLAT2000Doc * pDoc = (CLAT2000Doc *)GetDocument();
	if (0 == m_LEDIndicator.GetSize())
	{
		return;
	}
	
	if ( !IsWindow(m_LEDIndicator[0].GetSafeHwnd()) )
	{
		return;
	}

	for (int iRow = 0; iRow < pDoc->m_TestContainer.GetLEDRowSize(); iRow++)
	{
		for (int iCol = 0; iCol < pDoc->m_TestContainer.GetLEDColumnSize(); iCol++)
		{
			if (pDoc->m_TestContainer.IsLEDUpdated(iRow, iCol))
			{
				continue;
			}

			int iLEDIndex = pDoc->m_TestContainer.GetIndex(iRow, iCol);

			LEDState & state = pDoc->m_TestContainer.GetLEDState(iRow, iCol);
			if (state.IsSuccessful())
			{
                CString strTemp;
                strTemp.Format("%-3d - LED(%2d,%2d)\n\n", iLEDIndex + 1, iRow + 1, iCol + 1);
                if (pDoc->m_TestContainer.GetLEDData(iRow, iCol).IsLEDON())
                {
					int iTypeFail = 0;
                    if ( pDoc->m_dataContainer.GetTestSettingData().IsQulified(pDoc->m_TestContainer.GetLEDData(iRow, iCol),iTypeFail) )
                    {
                        m_LEDIndicator[iLEDIndex].SetColor(g_ColorGood);                 
                    }
                    else
                    {
                        m_LEDIndicator[iLEDIndex].SetColor(g_ColorBad);                 
                    }
                    strTemp += pDoc->m_TestContainer.GetInfoString(iRow, iCol, TRUE);
                }
                else
                {
                    m_LEDIndicator[iLEDIndex].SetColor(g_ColorBad_Codi);   
                    strTemp += pDoc->m_TestContainer.GetInfoString(iRow, iCol, FALSE);
                }

                m_LEDIndicator[iLEDIndex].SetTooltip(strTemp);
			}
			else if (state.IsTested())
			{
				m_LEDIndicator[iLEDIndex].SetColor(g_ColorInvalid);

				CString strTemp;
				if (pDoc->m_TestContainer.GetLEDState(iRow, iCol).ElectricalTestState == Failed)
				{
					strTemp.Format("%-3d - LED(%2d,%2d)\n\nElectrical Test Fail", iLEDIndex + 1, iRow + 1, iCol + 1);
				}
				else if (pDoc->m_TestContainer.GetLEDState(iRow, iCol).SpectrumTestState == Failed)
				{
					strTemp.Format("%-3d - LED(%2d,%2d)\n\nSpectrum Test Fail", iLEDIndex + 1, iRow + 1, iCol + 1);
				}
				m_LEDIndicator[iLEDIndex].SetTooltip(strTemp);
			}
			else
			{
				// Not test
				m_LEDIndicator[iLEDIndex].SetColor(g_ColorNotTest);

				CString strTemp;
				strTemp.Format("%-3d - LED(%2d,%2d)\n\nNot Test", iLEDIndex + 1, iRow + 1, iCol + 1);
				m_LEDIndicator[iLEDIndex].SetTooltip(strTemp);
			}
			
			pDoc->m_TestContainer.SetLEDUpdated(iRow, iCol, TRUE);
		} // for
	} // for

}


BOOL CMainTestFormView::GetItemRect(int iColumn, int iItem, CRect & rect)
{
	CLAT2000Doc * pDoc = (CLAT2000Doc *)GetDocument();
	if (NULL == pDoc)
	{
		return FALSE;
	}
	
	CRect clientRect;
	GetClientRect(&clientRect);
	clientRect.top += 25;
	clientRect.bottom -= clientRect.Height() / 3;
	clientRect.left += 25;

	rect.left = clientRect.left + iColumn * (clientRect.Width() / pDoc->m_TestContainer.GetLEDColumnSize());
	rect.top = clientRect.top + iItem * (clientRect.Height() / pDoc->m_TestContainer.GetLEDRowSize());
	rect.right = rect.left + clientRect.Width() / pDoc->m_TestContainer.GetLEDColumnSize();
	rect.bottom = rect.top + clientRect.Height() / pDoc->m_TestContainer.GetLEDRowSize();

	rect.DeflateRect(CSize(1, 1));

	//if (pDoc->GetLEDTotalNumber() == 1)
	//{
	//	rect.DeflateRect(rect.Width()/4, rect.Height()/4);
	//}

	if (rect.Width() < rect.Height())
	{
		int iDeflate = (rect.Height() - rect.Width()) / 2;
		rect.top += iDeflate;
		rect.bottom -= iDeflate;
	}
	else
	{
		int iDeflate = (rect.Width() - rect.Height()) / 2;
		rect.left += iDeflate;
		rect.right -= iDeflate;
	}
	
	return TRUE;
}


void CMainTestFormView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (NULL != g_pDoc)
	{
		ShowLEDIndicator();
		UpdateLEDIndicator();
	}
}


void CMainTestFormView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
	//CMenu menu;
	//menu.LoadMenu(IDR_MENU_ITEM_SHOW);
	//CMenu* pPopup = menu.GetSubMenu(0);
	//ASSERT(pPopup != NULL);
	//pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}


void CMainTestFormView::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CFormView::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	// TODO: 在此处添加消息处理程序代码
	CCmdUI cmdUI;
	int nCount = pPopupMenu->GetMenuItemCount();
	cmdUI.m_nIndexMax = nCount;
	cmdUI.m_pMenu = pPopupMenu;

	for (int i = 0; i < nCount; i++)
	{
		UINT nID = pPopupMenu->GetMenuItemID(i);
		if (0 != nID)
		{
			cmdUI.m_nID = nID;
			cmdUI.m_nIndex = i;
			cmdUI.DoUpdate(this, TRUE);
		}
	}
}


void CMainTestFormView::OnUpdatePopFlux(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_ucItemShowFlag & SHOW_FLUX);
}


void CMainTestFormView::OnPopFlux()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ucItemShowFlag & SHOW_FLUX)
	{
		m_ucItemShowFlag -= SHOW_FLUX;
	}
	else
	{
		m_ucItemShowFlag |= SHOW_FLUX;
	}

	Invalidate(FALSE);
}


void CMainTestFormView::OnUpdatePopTc(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_ucItemShowFlag & SHOW_TC);
}


void CMainTestFormView::OnPopTc()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ucItemShowFlag & SHOW_TC)
	{
		m_ucItemShowFlag -= SHOW_TC;
	}
	else
	{
		m_ucItemShowFlag |= SHOW_TC;
	}

	Invalidate(FALSE);
}


void CMainTestFormView::OnUpdatePopXy(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_ucItemShowFlag & SHOW_XY);
}


void CMainTestFormView::OnPopXy()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ucItemShowFlag & SHOW_XY)
	{
		m_ucItemShowFlag -= SHOW_XY;
	}
	else
	{
		m_ucItemShowFlag |= SHOW_XY;
	}

	Invalidate(FALSE);
}


void CMainTestFormView::OnUpdatePopUv(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_ucItemShowFlag & SHOW_UV);
}


void CMainTestFormView::OnPopUv()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ucItemShowFlag & SHOW_UV)
	{
		m_ucItemShowFlag -= SHOW_UV;
	}
	else
	{
		m_ucItemShowFlag |= SHOW_UV;
	}

	Invalidate(FALSE);
}


void CMainTestFormView::OnUpdatePopLd(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_ucItemShowFlag & SHOW_LD);
}


void CMainTestFormView::OnPopLd()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ucItemShowFlag & SHOW_LD)
	{
		m_ucItemShowFlag -= SHOW_LD;
	}
	else
	{
		m_ucItemShowFlag |= SHOW_LD;
	}

	Invalidate(FALSE);
}


void CMainTestFormView::OnUpdatePopDispersion(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_ucItemShowFlag & SHOW_DISPERSION);
}


void CMainTestFormView::OnPopDispersion()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ucItemShowFlag & SHOW_DISPERSION)
	{
		m_ucItemShowFlag -= SHOW_DISPERSION;
	}
	else
	{
		m_ucItemShowFlag |= SHOW_DISPERSION;
	}

	Invalidate(FALSE);
}


int CMainTestFormView::GetCheck()
{
	CLAT2000Doc * pDoc = (CLAT2000Doc *)GetDocument();
	if (NULL == pDoc)
	{
		return 0;
	}

	int iCount = 0;
	//for (int i = 0; i < pDoc->m_TestContainer.GetLEDRowCount(); i++)
	//{
	//	for (int j = 0; j < pDoc->m_TestContainer.GetLEDColumnSize(); j++)
	//	{
	//		int iIndex = i * pDoc->m_TestContainer.GetLEDColumnSize() + j;
	//		pDoc->m_pChecked[iIndex] = m_pLED[iIndex].GetCheck();
	//		if (pDoc->m_pChecked[iIndex])
	//		{
	//			iCount++;
	//		}
	//	}
	//}

	return iCount;
}


void CMainTestFormView::OnBnClickedButtonTestFail()
{
	// TODO: 在此添加控件通知处理程序代码
	CLAT2000Doc * pDoc = (CLAT2000Doc *)GetDocument();
	if (NULL == pDoc)
	{
		return;
	}

	//////////////////////////
	//BOOL bR = g_LED850Comm.SetTestParameter(pDoc->m_dataContainer.GetTestSettingData().m_fTestCurrent,
	//	1, pDoc->m_dataContainer.GetTestSettingData().m_fWarmUpTime, pDoc->m_dataContainer.GetTestSettingData().m_fOnTime);
	//if (!bR)
	//{
	//	AfxMessageBox("参数设置失败，触发未启动！");
	//	return;
	//}
	//CLedData data;
	//bR = g_LED850Comm.LEDTouchOff(TRUE, 0, 0, data);
	//return;
	//g_LED850Comm.SwitchLED(TRUE, 1, 1);
	//return;

	//for (int i = 0; i < pDoc->m_TestContainer.GetLEDRowCount(); i++)
	//{
	//	for (int j = 0; j < pDoc->m_TestData[i].GetSize(); j++)
	//	{
	//		int iIndex = i * pDoc->m_TestContainer.GetLEDColumnSize() + j;
	//		if (pDoc->m_TestData[i].GetAt(j).IsValid())
	//		{
	//			pDoc->m_pChecked[iIndex] = FALSE;
	//		}
	//		else
	//		{
	//			pDoc->m_pChecked[iIndex] = TRUE;
	//		}

	//		m_pLED[iIndex].SetCheck(pDoc->m_pChecked[iIndex]);
	//	}
	//}
}


void CMainTestFormView::OnBnClickedButtonBad()
{
	// TODO: 在此添加控件通知处理程序代码
	CLAT2000Doc * pDoc = (CLAT2000Doc *)GetDocument();
	if (NULL == pDoc)
	{
		return;
	}
	
	//for (int i = 0; i < pDoc->m_TestContainer.GetLEDRowCount(); i++)
	//{
	//	for (int j = 0; j < pDoc->m_TestData[i].GetSize(); j++)
	//	{
	//		int iIndex = i * pDoc->m_TestContainer.GetLEDColumnSize() + j;
	//		pDoc->m_pChecked[iIndex] = FALSE;
	//		if (pDoc->m_TestData[i].GetAt(j).IsValid())
	//		{
	//			if ( !pDoc->m_dataContainer.GetTestSettingData().IsQulified(pDoc->m_TestData[i].GetAt(j)) )
	//			{
	//				pDoc->m_pChecked[iIndex] = TRUE;
	//			}
	//		}

	//		m_pLED[iIndex].SetCheck(pDoc->m_pChecked[iIndex]);
	//	}
	//}
}


void CMainTestFormView::OnBnClickedButtonNone()
{
	// TODO: 在此添加控件通知处理程序代码
	CLAT2000Doc * pDoc = (CLAT2000Doc *)GetDocument();
	if (NULL == pDoc)
	{
		return;
	}
	
	//for (int i = 0; i < pDoc->m_TestContainer.GetLEDRowCount(); i++)
	//{
	//	for (int j = 0; j < pDoc->m_TestData[i].GetSize(); j++)
	//	{
	//		int iIndex = i * pDoc->m_TestContainer.GetLEDColumnSize() + j;
	//		pDoc->m_pChecked[iIndex] = FALSE;
	//		m_pLED[iIndex].SetCheck(pDoc->m_pChecked[iIndex]);
	//	}
	//}
}


void CMainTestFormView::OnBnClickedButtonReverse()
{
	// TODO: 在此添加控件通知处理程序代码
	CLAT2000Doc * pDoc = (CLAT2000Doc *)GetDocument();
	if (NULL == pDoc)
	{
		return;
	}
	
	//for (int i = 0; i < pDoc->m_TestContainer.GetLEDRowCount(); i++)
	//{
	//	for (int j = 0; j < pDoc->m_TestData[i].GetSize(); j++)
	//	{
	//		int iIndex = i * pDoc->m_TestContainer.GetLEDColumnSize() + j;
	//		pDoc->m_pChecked[iIndex] = !pDoc->m_pChecked[iIndex];
	//		m_pLED[iIndex].SetCheck(pDoc->m_pChecked[iIndex]);
	//	}
	//}
}


void CMainTestFormView::OnBnClickedButtonGood()
{
	// TODO: 在此添加控件通知处理程序代码
	CLAT2000Doc * pDoc = (CLAT2000Doc *)GetDocument();
	if (NULL == pDoc)
	{
		return;
	}
	
	//for (int i = 0; i < pDoc->m_TestContainer.GetLEDRowCount(); i++)
	//{
	//	for (int j = 0; j < pDoc->m_TestData[i].GetSize(); j++)
	//	{
	//		int iIndex = i * pDoc->m_TestContainer.GetLEDColumnSize() + j;
	//		pDoc->m_pChecked[iIndex] = FALSE;
	//		if (pDoc->m_TestData[i].GetAt(j).IsValid())
	//		{
	//			if ( pDoc->m_dataContainer.GetTestSettingData().IsQulified(pDoc->m_TestData[i].GetAt(j)) )
	//			{
	//				pDoc->m_pChecked[iIndex] = TRUE;
	//			}
	//		}

	//		m_pLED[iIndex].SetCheck(pDoc->m_pChecked[iIndex]);
	//	}
	//}
}


HBRUSH CMainTestFormView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CMainTestFormView::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	CFormView::PreSubclassWindow();
}

void CMainTestFormView::OnKillfocusComboFile()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
}

void CMainTestFormView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CFormView::OnLButtonDown(nFlags, point);
}

BOOL CMainTestFormView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	//CLAT2000Doc * pDoc = (CLAT2000Doc *)GetDocument();
	//if (NULL != pDoc)
	//{
	//	if (pDoc->IsRunning() && pMsg->message == WM_LBUTTONDOWN)
	//	{
	//		AfxMessageBox("测试正在进行，请稍候再进行选择！");
	//		pMsg->message = WM_NULL;
	//		return FALSE;
	//	}
	//}

	if (TranslateAccelerator(AfxGetMainWnd()->GetSafeHwnd(), g_hAccel, pMsg))
	{
		return TRUE;
	}

	return CFormView::PreTranslateMessage(pMsg);
}

afx_msg LRESULT CMainTestFormView::OnMsgTestEnded(WPARAM wParam, LPARAM lParam)
{
	CLAT2000Doc * pDoc = (CLAT2000Doc *)GetDocument();

	KillTimer(1);
	ShowLEDIndicator();

	return 0;
}

afx_msg LRESULT CMainTestFormView::OnMsgShowMessage(WPARAM wParam, LPARAM lParam)
{
	if (m_bMessageIsShowing)
	{
		return 1;
	}
	m_bMessageIsShowing = TRUE;

	if (NULL != g_pDoc)
	{
		if (AT_NOME != wParam && !m_bIsAlarming)
		{
			m_eAlarmType = (AlarmType)wParam;
			m_PlayOneRing.SetEvent();
		}
		CNoneBorderDlg dlg;
		dlg.m_strInfo = g_pDoc->m_strNoneBorderMsg;
		if (AT_LAMP_TOO_HIGH == wParam)
        {
			if (g_pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_bLampTooHighAlarm)
			{
				dlg.DoModal();
				if (dlg.m_bIgnoreSame)
				{
					g_pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_bLampTooHighAlarm = FALSE;
				}
				goto ShowMessageEnd;
			}
        }
        if (AT_MANUAL_STOP == wParam)
        {
			if (g_pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_bManualStopAlarm)
			{
				dlg.DoModal();
				if (dlg.m_bIgnoreSame)
				{
					g_pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_bManualStopAlarm = FALSE;
				}
				goto ShowMessageEnd;
			}
        }
        for (int i = 0; i < g_iTMPControlNum; i ++)
        {
            if (AT_TMP1 + i== wParam)
            {
                if (g_pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_bTMPAlarm[i])
                {
                    dlg.DoModal();
                    if (dlg.m_bIgnoreSame)
                    {
                        g_pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_bTMPAlarm[i] = FALSE;
                    }
					goto ShowMessageEnd;
                }
            }
               
        }
		

        for (int i = 0; i < g_iGaugeNum; i ++)
        {
             if (AT_REGION1 + i == wParam)
             {
                 if (g_pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_bRegionAlarm[i])
                 {
                     dlg.DoModal();
                     if (dlg.m_bIgnoreSame)
                     {
                         g_pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_bRegionAlarm[i] = FALSE;
                     }
					 goto ShowMessageEnd;
                 }
             }
        }
        if (AT_SCANEROVERTIME == wParam)
        {
            if (g_pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_bScanerOverTimeAlarm)
            {
                dlg.DoModal();
                if (dlg.m_bIgnoreSame)
                {
                    g_pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_bScanerOverTimeAlarm = FALSE;
                }
				goto ShowMessageEnd;
            }
        }
			dlg.DoModal();
	}
ShowMessageEnd:
	g_LineControllerComm.SetShowLED(0);
    m_bMessageIsShowing = FALSE;
    return 0;
}


afx_msg LRESULT CMainTestFormView::OnMsgLimitFileRelist(WPARAM wParam, LPARAM lParam)
{
	ListLimitFile();
	return 0;
}


UINT CMainTestFormView::ThreadAlarmPlayRing(LPVOID pPar)
{
	CMainTestFormView * pView = (CMainTestFormView *)pPar;
	int iRingIndex = -1, iWaitTimemsec = 0;
	while(pView->m_PlayOneRing.Lock())
	{
		pView->m_bIsAlarming = TRUE;
		if (NULL == g_pDoc)
		{
			Sleep(1000);
			goto NEXT;
		}
        iRingIndex = -1;	
		if (pView->m_eAlarmType == AT_LAMP_TOO_HIGH)
		{
            if (!g_pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_bLampTooHighAlarm)
            {
                goto NEXT;
            }
            iRingIndex = g_pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_iLampTooHighRingIndex;
		}

        if (pView->m_eAlarmType == AT_MANUAL_STOP)
        {
			if (!g_pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_bManualStopAlarm)
			{
				goto NEXT;
			}
			iRingIndex = g_pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_iManualStopRingIndex;
        }
        if (pView->m_eAlarmType == AT_NOME)
        {
            iRingIndex = -2;
            goto NEXT;
            break;
        }
		for (int i = 0; i < g_iGaugeNum; i ++)
		{
            if (AT_REGION1 + i == pView->m_eAlarmType)
            {
                if (!g_pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_bRegionAlarm[i])
                {
                    goto NEXT;
                }
                iRingIndex = g_pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_iRegionRingIndex[i];
            }
		}
        for (int i = 0; i < g_iTMPControlNum; i ++)
        {
            if (AT_TMP1 + i == pView->m_eAlarmType)
            {
                if (!g_pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_bTMPAlarm[i])
                {
                    goto NEXT;
                }
                iRingIndex = g_pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_iTMPRingIndex[i];
            }
        }
		
        if (AT_SCANEROVERTIME == pView->m_eAlarmType)
        {
            if (!g_pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_bScanerOverTimeAlarm)
            {
                goto NEXT;
            }
            iRingIndex = g_pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_iScanerOverTimeRingIndex;
        }
            

		RingData & data = g_pDoc->m_AlarmRingData.GetRingData(iRingIndex);
		for (int i = 0; i < data.iRingNumber; i++)
		{
			g_pDoc->m_CommSettingsData.m_iTestChannelControlerType == 1  ? 
				g_SC1000Comm.SetBuzzer(TRUE) : g_LineControllerComm.SetBuzzer(TRUE);
			
			iWaitTimemsec = 0;
			while(iWaitTimemsec < data.iRingONTimems)
			{
				Sleep(100);
				iWaitTimemsec += 100;
				if (pView->m_bStopAlarming)
				{
					g_pDoc->m_CommSettingsData.m_iTestChannelControlerType == 1  ? 
					g_SC1000Comm.SetBuzzer(FALSE) : g_LineControllerComm.SetBuzzer(FALSE);
					goto NEXT;
				}
			}

			g_pDoc->m_CommSettingsData.m_iTestChannelControlerType == 1  ? 
				g_SC1000Comm.SetBuzzer(FALSE) : g_LineControllerComm.SetBuzzer(FALSE);
			while(iWaitTimemsec < data.iRingOFFTimems)
			{
				Sleep(100);
				iWaitTimemsec += 100;
				if (pView->m_bStopAlarming)
				{
					goto NEXT;
				}
			}// While
		}// For

NEXT:
		pView->m_bIsAlarming = FALSE;
	}

	return 0;
}


UINT CMainTestFormView::ThreadGetLineState(LPVOID pPar)
{
	CMainTestFormView * pView = (CMainTestFormView *)pPar;
    CLAT2000Doc *pDoc = (CLAT2000Doc*)pView->GetDocument(); 

	BOOL bIsMoving = FALSE;
	BOOL bInPosition = FALSE, bManualStop = FALSE, bLampTooHigh = FALSE;
	while(1)
	{
		if (NULL == g_pDoc)
		{
			Sleep(1000);
			continue;
		}

        g_EventOlding.Lock();    
        
		// Line
		if (g_pDoc->IsRunning())
		{
			if (WaitTime == g_pDoc->m_lineState)
			{
				pView->m_cOtherInfo.SetWaitRemainSeconds(g_pDoc->m_iWaitRemainSeconds);
				pView->m_cOtherInfo.SetLineState(WaitTime);
				bIsMoving = FALSE;
			}
			else
			{
				pView->m_cOtherInfo.SetLineState(g_pDoc->m_lineState);
			}
		}
		else
		{
			if (g_LineControllerComm.ReadLineState(bInPosition, bManualStop, bLampTooHigh))
			{
				if (NULL == pView || !IsWindow(pView->GetSafeHwnd()))
				{
					return 0;
				}	
			
				if (Free == g_pDoc->m_lineState)
				{
					pView->m_cOtherInfo.SetLineState(Free);
				}
				if (bLampTooHigh)
				{
					g_LineControllerComm.SetShowLED(2);
					g_LineControllerComm.SetLinePause();
					pView->m_cOtherInfo.SetLineState(LampTooHigh);
				}
				else if (bManualStop)
				{
					g_LineControllerComm.SetShowLED(2);
					g_LineControllerComm.SetLinePause();
					pView->m_cOtherInfo.SetLineState(ManulStopped);
				}
				else if (bInPosition)
				{
					if (pDoc->m_bSetStop || pView->m_bMessageIsShowing)
					{
						g_LineControllerComm.SetShowLED(0);
					}
					pView->m_cOtherInfo.SetLineState(Free);
				}
			}
			else
			{
				if (NULL == pView || !IsWindow(pView->GetSafeHwnd()))
				{
					return 0;
				}

				pView->m_cOtherInfo.SetLineState(NotConnected);
			}
	}
		// Burn in
		if (g_pDoc->m_dataContainer.GetTestSettingData().m_bTestBurnIn)
		{
			pView->m_cOtherInfo.SetBurnInInfo(g_pDoc->m_dataContainer.GetTestSettingData().m_iBurnInONSeconds, g_pDoc->m_dataContainer.GetTestSettingData().m_iBurnInOFFSeconds);
		}
		else
		{
			pView->m_cOtherInfo.SetBurnInInfo("----");
		}

		// EMS61000-5A
		if (g_pDoc->m_dataContainer.GetTestSettingData().m_bTestLightning)
		{
			if (g_pDoc->m_bIsLightningSurgeRunning)
			{
				EMC5AREData data1;
				int iReturn = g_EMS61000_5AComm.Read(data1);
				if (NULL == pView || !IsWindow(pView->GetSafeHwnd()))
				{
					return 0;
				}

				if (1 == iReturn)
				{
					pView->m_cOtherInfo.Set5AInfo("");
				}
				else
				{
					CString strInfo;
					strInfo.Format("通道%d %s", 
						g_pDoc->m_TestContainer.m_iCurrentThunderChannel + 1, data1.strRe);
					pView->m_cOtherInfo.Set5AInfo(strInfo);
				}
			}
			else
			{
				pView->m_cOtherInfo.Set5AInfo("空闲中...");
			}
		}
		else
		{
			pView->m_cOtherInfo.Set5AInfo("----");
		}
	
		// EMS61000-11K
		if (g_pDoc->m_dataContainer.GetTestSettingData().m_bTestVoltageUpAndDips)
		{
			if (g_pDoc->m_bIsVoltageDipsAndUPRunning)
			{
				EMC11KREData data2;
				int iReturn = g_EMS61000_11KComm.Read(data2);
				if (NULL == pView || !IsWindow(pView->GetSafeHwnd()))
				{
					return 0;
				}

				if (1 == iReturn)
				{
					pView->m_cOtherInfo.Set11KInfo("");
				}
				else
				{
					pView->m_cOtherInfo.Set11KInfo(data2.strRe);
				}
			}
			else
			{
				pView->m_cOtherInfo.Set11KInfo("空闲中...");
			}
		}
		else
		{
			pView->m_cOtherInfo.Set11KInfo("----");
		}

		// Statistics information
		if (NULL == pView || !IsWindow(pView->GetSafeHwnd()))
		{
			return 0;
		}

		CString strTemp;
        if (g_pDoc->m_testStatisticsData.m_iTotalLEDNum > 0)
        {
            strTemp.Format("已测:%d  合格:%d(%.2f%%) \n不合格(超限值):%d(%.2f%%) 不合格(未亮或无灯):%d(%.2f%%)",
                g_pDoc->m_testStatisticsData.m_iTotalLEDNum,
                g_pDoc->m_testStatisticsData.m_iQualifiedLEDNum,
                g_pDoc->m_testStatisticsData.m_iQualifiedLEDNum * 1.0f / g_pDoc->m_testStatisticsData.m_iTotalLEDNum * 100,
                g_pDoc->m_testStatisticsData.m_iUnqualifiedLEDNum,
                g_pDoc->m_testStatisticsData.m_iUnqualifiedLEDNum * 1.0f / g_pDoc->m_testStatisticsData.m_iTotalLEDNum * 100,
				g_pDoc->m_testStatisticsData.m_iLEDUnONNum,
				g_pDoc->m_testStatisticsData.m_iLEDUnONNum * 1.0f / g_pDoc->m_testStatisticsData.m_iTotalLEDNum * 100);
        }
        else
        {
            strTemp.Format("已测:%d  合格:%d \n不合格(超限值):%d 不合格(未亮或无灯):%d",
                g_pDoc->m_testStatisticsData.m_iTotalLEDNum,
                g_pDoc->m_testStatisticsData.m_iQualifiedLEDNum,
                g_pDoc->m_testStatisticsData.m_iUnqualifiedLEDNum,
				g_pDoc->m_testStatisticsData.m_iLEDUnONNum);
        }
		pView->m_cOtherInfo.SetStatisticInfo(strTemp);

		Sleep(500);
	}

	return 0;
}


void CMainTestFormView::OnUpdateMenuPrint(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(TRUE);
}


void CMainTestFormView::OnMenuPrint()
{
	// TODO: 在此添加命令处理程序代码
	CLAT2000Doc * pDoc = (CLAT2000Doc *)GetDocument();

	CPrintDialog * pPrintDlg = new CPrintDialog(FALSE, PD_ALLPAGES | PD_RETURNDC, NULL);
	pPrintDlg->m_pd.nMinPage = 1;
	pPrintDlg->m_pd.nMaxPage = 10;
	pPrintDlg->m_pd.nFromPage = 1;
	pPrintDlg->m_pd.nToPage = 10;

	if (IDCANCEL == pPrintDlg->DoModal())
	{
		return;
	}

	CRect m_pageRect;
	HDC  m_hdcPrint;
	CDC *m_pPrintDC;

	m_hdcPrint = pPrintDlg->GetPrinterDC();
	if (NULL != m_hdcPrint)
	{
		m_pPrintDC = new CDC();
		m_pPrintDC->Attach(m_hdcPrint);
		m_pPrintDC->StartDoc(_T("LED Report"));

		m_pageRect.left = 0;
		m_pageRect.top = 0;
		m_pageRect.right = ::GetDeviceCaps(m_hdcPrint, HORZRES);
		m_pageRect.bottom = ::GetDeviceCaps(m_hdcPrint, VERTRES);

		//CRect rect = m_pageRect;
		//CRect printRect(rect.Width() / 2, rect.Height() / 2, rect.Width() / 12 * 11, rect.Height() / 12 * 10);

		// Page 1
		for (int i = pPrintDlg->m_pd.nFromPage; i <= pPrintDlg->m_pd.nToPage; i++)
		{
			m_pPrintDC->StartPage();
			PrintPage(m_pPrintDC, m_pageRect, i);
			m_pPrintDC->EndPage();
		}

		m_pPrintDC->EndDoc();
		m_pPrintDC->Detach();
		delete m_pPrintDC;
	}
	else
	{
		delete pPrintDlg;
		return;
	}

	delete pPrintDlg;
	return;
}


void CMainTestFormView::PrintPage(CDC * pDC, CRect printRect, int nPage)
{
	//
	int iLEDIndex = nPage - 1;
	CLAT2000Doc * pDoc = (CLAT2000Doc *)GetDocument();
	int iRow = iLEDIndex / pDoc->m_TestContainer.GetLEDColumnSize();
	int iColumn = iLEDIndex % pDoc->m_TestContainer.GetLEDColumnSize();

	TEXTMETRIC  tm;
	pDC->GetTextMetrics(&tm);
	int fontHeight = tm.tmHeight + tm.tmExternalLeading;
	int fontWidth = tm.tmAveCharWidth;		
	int RowSpace = printRect.Height()/320;
	int iX, iY;
	CString str;
	
	if (0)
	{
		// PageHeader
		pDC->SetTextAlign(TA_LEFT);
		iX = printRect.Width()/25;
		iY = printRect.Height()/15 - fontHeight - RowSpace;
		str = "Electrical Parameter Test Report";
		pDC->TextOut(iX, iY, str);
		
		iX = (int)(printRect.Width()*0.85);
		str.Format("Page %d", iLEDIndex + 1);
		pDC->TextOut(iX, iY, str);
		
		// line top
		iX = printRect.Width()/40;
		iY = printRect.Height()/14;
		pDC->MoveTo(iX, iY);
		iX = printRect.right - printRect.Width()/40;	
		pDC->LineTo(iX, iY);
		
		//line bottom
		iX = printRect.Width()/40;
		iY = printRect.Height()*13/14;
		pDC->MoveTo(iX,iY);
		iX = printRect.right - printRect.Width()/40;
		pDC->LineTo(iX,iY);
		
		//page footer
		iX = printRect.Width()/2;
		iY = printRect.Height()*14/15 + fontHeight;
		pDC->SetTextAlign(TA_CENTER);
		str = "EVERFINE LAT2000";
		pDC->TextOut(iX,iY,str);
	} 
	else
	{	
		// PageHeader
		pDC->SetTextAlign(TA_LEFT);
		iX = printRect.Width()/25;
		iY = printRect.Height()/15 - fontHeight - RowSpace;
		str = "LED测试报告";
		pDC->TextOut(iX, iY, str);
		
		iX = (int)(printRect.Width()*0.775);
		str.Format("第 %d 页，共 %d 页",
			iLEDIndex + 1, 10);
		pDC->TextOut(iX, iY, str);
		
		// line top
		iX = printRect.Width()/40;
		iY = printRect.Height()/14;
		pDC->MoveTo(iX, iY);
		iX = printRect.right - printRect.Width()/40;	
		pDC->LineTo(iX, iY);
		
		//line bottom
		iX = printRect.Width()/40;
		iY = printRect.Height()*13/14;
		pDC->MoveTo(iX,iY);
		iX = printRect.right - printRect.Width()/40;
		pDC->LineTo(iX,iY);
		
		//page footer
		iX = printRect.Width()/2;
		iY = printRect.Height()*14/15 + fontHeight;
		pDC->SetTextAlign(TA_CENTER);
		str = "远方(EVERFINE) LAT-2000";
		pDC->TextOut(iX,iY,str);
	}

	CRect rect(printRect.Width()/12, printRect.Height()/12, printRect.Width()/12*11, printRect.Height()/12*10);

	if (pDoc->m_TestContainer.GetLEDState(iLEDIndex).IsTested())
	{
		PrintLEDData(pDC, rect, iLEDIndex);
	}
	else
	{
		CString strTemp;
		strTemp.Format("LED%d[%d-%d] hasn't been tested!", iLEDIndex + 1, iRow + 1, iColumn + 1);
		pDC->TextOut(rect.CenterPoint().x, rect.CenterPoint().y, strTemp);
	}
	return;
}

void CMainTestFormView::PrintLEDData(CDC * pDC, CRect printRect, int iLEDIndex)
{
	CLAT2000Doc * pDoc = (CLAT2000Doc *)GetDocument();
	int iRow = iLEDIndex / pDoc->m_TestContainer.GetLEDColumnSize();
	int iColumn = iLEDIndex % pDoc->m_TestContainer.GetLEDColumnSize();

	CFont Font1, Font2, Font3, * pOldFont;
	Font1.CreateFont(printRect.Height()/40,0,0,0,700,FALSE,FALSE,0,
		GB2312_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"黑体");  

	Font2.CreateFont(printRect.Height()/45,0,0,0,400,FALSE,FALSE,0,
		GB2312_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"黑体"); 

	Font3.CreateFont(printRect.Height()/55,0,0,0,400,FALSE,FALSE,0,
		GB2312_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"黑体"); 


	if (pDoc->m_TestContainer.GetLEDState(iLEDIndex).IsSuccessful())
	{
		CLedData & data = pDoc->m_TestContainer.GetLEDData(iLEDIndex);
		pOldFont = pDC->SelectObject(&Font1);

		CString strTemp;
		strTemp.Format("LED%d (%d - %d)", iLEDIndex + 1, iRow + 1, iColumn + 1);
		pDC->SetTextAlign(TA_CENTER);
		pDC->TextOut(printRect.left + printRect.Width()/2,printRect.top + printRect.Height()/12, strTemp);

		pDC->SetTextAlign(TA_LEFT);
		int iX = printRect.left + printRect.Width()/25;
		int iY = printRect.top + printRect.Height()/6;;
		int iyStep = printRect.Height()/36;
		int ixTap = printRect.Width()/30;

		// Electrical
		pDC->SelectObject(&Font2);
		strTemp = "电参数";
		pDC->TextOut(iX, iY, strTemp);
		pDC->SelectObject(&Font3);

		// data...
		iY += iyStep * 2;
		iX += ixTap;
		strTemp.Format("电流：%.4f mA", 
			data.m_fCurrentA);
		pDC->TextOut(iX, iY, strTemp);

		iX += ixTap * 12;
		strTemp.Format("电压：%.4f V", 
			data.m_fVoltageV);
		pDC->TextOut(iX, iY, strTemp);

		// Spectrum
		pDC->SelectObject(&Font2);
		iY += iyStep * 3;
		iX -= ixTap * 12;
		iX -= ixTap;
		strTemp = "光参数";
		pDC->TextOut(iX, iY, strTemp);
		pDC->SelectObject(&Font3);

		// data...
		iY += iyStep * 2;
		iX += ixTap;
		strTemp.Format("CIE-x:%.4f", 
			data.m_ColorData.m_fCIEx);
		pDC->TextOut(iX, iY, strTemp);
	
		iX += ixTap * 12;
		strTemp.Format("CIE-u':%.4f", 
			data.m_ColorData.m_fCIEu_);
		pDC->TextOut(iX, iY, strTemp);


		iX -= ixTap * 12;
		iY += iyStep;
		strTemp.Format("CIE-y:%.4f", 
			data.m_ColorData.m_fCIEy);
		pDC->TextOut(iX, iY, strTemp);

		iX += ixTap * 12;
		strTemp.Format("CIE-v':%.4f", 
			data.m_ColorData.m_fCIEv_);
		pDC->TextOut(iX, iY, strTemp);


		iY += iyStep;
		iX -= ixTap * 12;
		strTemp.Format("Flux:%.4g lm", 
			data.m_ColorData.m_fPh);
		pDC->TextOut(iX, iY, strTemp);

		iX += ixTap * 12;
		strTemp.Format("Tc:%.4g K", 
			data.m_ColorData.m_fTc);
		pDC->TextOut(iX, iY, strTemp);


		iY += iyStep;
		iX -= ixTap * 12;
		strTemp.Format("Ld:%.1f nm", 
			data.m_ColorData.m_fLd);
		pDC->TextOut(iX, iY, strTemp);

		iX += ixTap * 12;
		strTemp.Format("Lp:%.1f nm", 
			data.m_ColorData.m_fLp);
		pDC->TextOut(iX, iY, strTemp);


		iY += iyStep;
		iX -= ixTap * 12;
		strTemp.Format("HW:%.1f", 
			data.m_ColorData.m_fHW);
		pDC->TextOut(iX, iY, strTemp);

		iX += ixTap * 12;
		strTemp.Format("Ip:%.0f", 
			data.m_ColorData.m_fIp);
		pDC->TextOut(iX, iY, strTemp);


		iY += iyStep;
		iX -= ixTap * 12;
		strTemp.Format("Pur:%.1f", 
			data.m_ColorData.m_fPur);
		pDC->TextOut(iX, iY, strTemp);

		iX += ixTap * 12;
		strTemp.Format("RGB(%.0f, %.0f, %.0f)", 
			data.m_ColorData.m_fRR,
			data.m_ColorData.m_fGR,
			data.m_ColorData.m_fBR);
		pDC->TextOut(iX, iY, strTemp);
	}
	else
	{
		CString strTemp;
		strTemp.Format("LED%d[%d-%d] is invalid!", iLEDIndex + 1, iRow + 1, iColumn + 1);
		pDC->TextOut(printRect.CenterPoint().x, printRect.CenterPoint().y, strTemp);
	}
}

void CMainTestFormView::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CFormView::OnClose();
}


void CMainTestFormView::OnDestroy()
{
	CFormView::OnDestroy();
	// TODO: 在此处添加消息处理程序代码
}


BOOL CMainTestFormView::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类

	return CFormView::DestroyWindow();
}


void CMainTestFormView::OnResetStatistics()
{
	// TODO: 在此添加命令处理程序代码
    if (NULL != g_pDoc)
    {
        g_pDoc->m_testStatisticsData.Reset();
        CString strTemp;
        if (g_pDoc->m_testStatisticsData.m_iTotalLEDNum > 0)
        {
            strTemp.Format("已测:%d 合格:%d(%.2f%%) \n不合格(超限值):%d(%.2f%%) 不合格(未亮或无灯):%d(%.2f%%)",
                g_pDoc->m_testStatisticsData.m_iTotalLEDNum,
                g_pDoc->m_testStatisticsData.m_iQualifiedLEDNum,
                g_pDoc->m_testStatisticsData.m_iQualifiedLEDNum * 1.0f / g_pDoc->m_testStatisticsData.m_iTotalLEDNum * 100,
                g_pDoc->m_testStatisticsData.m_iUnqualifiedLEDNum,
                g_pDoc->m_testStatisticsData.m_iUnqualifiedLEDNum * 1.0f / g_pDoc->m_testStatisticsData.m_iTotalLEDNum * 100,
				g_pDoc->m_testStatisticsData.m_iLEDUnONNum,
				g_pDoc->m_testStatisticsData.m_iLEDUnONNum * 1.0f / g_pDoc->m_testStatisticsData.m_iTotalLEDNum * 100);
        }
        else
        {
            strTemp.Format("已测:%d 合格:%d \n不合格(超限值):%d 不合格(未亮或无灯):%d",
                g_pDoc->m_testStatisticsData.m_iTotalLEDNum,
                g_pDoc->m_testStatisticsData.m_iQualifiedLEDNum,
                g_pDoc->m_testStatisticsData.m_iUnqualifiedLEDNum,
				g_pDoc->m_testStatisticsData.m_iLEDUnONNum);
        }
        m_cOtherInfo.SetStatisticInfo(strTemp);
    }
}
