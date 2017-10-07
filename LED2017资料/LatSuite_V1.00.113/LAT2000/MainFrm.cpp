
// MainFrm.cpp : CMainFrame ���ʵ��

#include "stdafx.h"
#include "LAT2000.h"
#include "LAT2000Doc.h"
#include "ExitSelectionDlg.h"
#include "MainFrm.h"
#include "Splash.h"
#include "AccreditData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

extern BOOL	g_bTMPControllerON;
extern CMyDockablePaneData g_myDockablePaneData;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()  
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_MESSAGE(AFX_WM_RESETTOOLBAR, OnToolBarReset)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_LOGO, &CMainFrame::OnUpdateIndicatorLogo)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_TIME, &CMainFrame::OnUpdateIndicatorTime)
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI(ID_WATCH_PANE, &CMainFrame::OnUpdateWatchPane)
	ON_COMMAND(ID_WATCH_PANE, &CMainFrame::OnWatchPane)
    ON_WM_TIMER()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
    ID_INDICATOR_TEST_INFO,
	ID_INDICATOR_STATISTICINFO,
	ID_INDICATOR_LOGO,
	ID_INDICATOR_TIME,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_WINDOWS_7);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

    g_hMainFrm = m_hWnd;
	BOOL bNameValid;
	// ���ڳ־�ֵ�����Ӿ�����������ʽ
	OnApplicationLook(theApp.m_nAppLook);

	//�����壬Ĭ�ϵ�����Ƚ�ģ��
	//LOGFONT lfont;
	//afxGlobalData.fontRegular.GetLogFont(&lfont);
	//afxGlobalData.fontRegular.DeleteObject();
	//lstrcpy(lfont.lfFaceName,_T("����"));
	//lfont.lfHeight = -12;
	//afxGlobalData.fontRegular.CreateFontIndirect(&lfont);
    /*
    g_iExecutionLevel =  LOW_EXECUTION_LEVEL;
    int iD;
    if (ADMIN_EXECUTION_LEVEL == g_iExecutionLevel)
    {
        iD = IDR_MAINFRAME; 
    }
    if (HIGH_EXECUTION_LEVEL == g_iExecutionLevel)
    {
        iD = IDR_MAINFRAME_HIGHLEVEL; 
    }
    if (LOW_EXECUTION_LEVEL == g_iExecutionLevel)
    {
        iD = IDR_MAINFRAME_LOWLEVEL; 
    }    
    */
	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("δ�ܴ����˵���\n");
		return -1;      // δ�ܴ���
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | WS_CHILD | CBRS_TOP | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);
	// ��ֹ�˵����ڼ���ʱ��ý���
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	// 1. Create m_wndToolBar
	m_wndToolBar.EnableLargeIcons(FALSE);
	theApp.m_bHiColorIcons = TRUE;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(FALSE, ID_VIEW_CUSTOMIZE, strCustomize);
	m_wndToolBar.EnableTextLabels(TRUE);

	// 2. Create m_wndMyToolBar
	m_wndMyToolBar.EnableLargeIcons(FALSE); // Should be called before creat

	if (!m_wndMyToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_FLYBY | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS) 
		|| !m_wndMyToolBar.LoadToolBar(IDR_MY_TOOLBAR))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;
	}

	CMFCToolBar::AddToolBarForImageCollection(IDR_MY_TOOLBAR, IDB_BITMAP_CONTINUE_TEST, 20, 20, 20, 20);
// 	BOOL bR = m_wndMyToolBar.IsLocked();
// 	CSize size;
// 	size = m_wndMyToolBar.GetMenuButtonSize();
// 	size = m_wndMyToolBar.GetMenuImageSize();
// 	m_wndMyToolBar.SetSizes(CSize(38, 38), CSize(32, 32));
//	m_wndMyToolBar.SetMenuSizes(CSize(38, 38), CSize(32, 32));
	m_wndMyToolBar.SetWindowText("���Կ�����");
	m_wndMyToolBar.EnableTextLabels(TRUE);
	m_wndMyToolBar.EnableCustomizeButton(FALSE, ID_VIEW_CUSTOMIZE, "TestControlBar");
// 	BOOL bR = m_wndMyToolBar.IsCustomizeMode();
// 	UINT nID, nStyle;
// 	int iImage;
// 	m_wndMyToolBar.GetButtonInfo(0, nID, nStyle, iImage);
// 	bR = m_wndMyToolBar.IsLargeIcons();
	m_wndMyToolBar.SetMenuSizes(CSize(54, 54), CSize(48, 48));
//	m_wndMyToolBar.SetCustomizeMode();

	m_wndMenuBar.SetMenuSizes(CSize(21, 22), CSize(15, 16));
	// �����û�����Ĺ���������:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);
	
	// Status bar
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	m_wndStatusBar.SetPaneWidth(m_wndStatusBar.CommandToIndex(ID_INDICATOR_TEST_INFO), 50);
        m_wndStatusBar.SetPaneWidth(m_wndStatusBar.CommandToIndex(ID_INDICATOR_STATISTICINFO), 500);
	m_wndStatusBar.SetPaneWidth(m_wndStatusBar.CommandToIndex(ID_INDICATOR_LOGO), 280);
	m_wndStatusBar.SetPaneWidth(m_wndStatusBar.CommandToIndex(ID_INDICATOR_TIME), 140);
//	m_wndStatusBar.SetPaneTextColor(0, RGB(255, 0, 0), TRUE);
// 	m_wndStatusBar.EnablePaneProgressBar(0, 100);
// 	m_wndStatusBar.SetPaneProgress(0, 50, TRUE);

	// TODO: �������ϣ���������Ͳ˵�����ͣ������ɾ��������
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
 	m_wndMyToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);
	DockPaneLeftOf(&m_wndMyToolBar, &m_wndToolBar);

	//////////////////////////////////////////////////////////////////////////
 	//CRect rect;
 	//GetClientRect(&rect);
 	//rect.top = rect.bottom/2;
  //  if (!m_wndDialogPane.Create (_T("��������"), this, TRUE, 
  //                           MAKEINTRESOURCE (IDD_DIALOG_PANE), 
  //                           WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT |CBRS_FLOAT_MULTI, 
  //                           IDD_MY_PANE_DIALOG))
  //  {
  //      TRACE0("Failed to create Dialog pane\n");
  //      return FALSE;      // fail to create
  //  }

 	//m_wndDialogPane.EnableDocking(CBRS_RIGHT);
 	//DockPane(&m_wndDialogPane);

// 	m_wndDialogPane.Create("��������", 
// 		this, CRect(0, 0, 350, 0), TRUE, IDD_MY_PANE_DIALOG,
// 		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI);
// 	m_wndDialogPane.EnableDocking(CBRS_ALIGN_RIGHT);
// 	EnableDocking(CBRS_ALIGN_RIGHT);
// 	DockPane(&m_wndDialogPane);

	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// ����ͣ������
 	//if (!CreateDockingWindows())
 	//{
 	//	TRACE0("δ�ܴ���ͣ������\n");
 	//	return -1;
 	//}

 	//m_wndDlgBar.EnableDocking(CBRS_ALIGN_ANY);
 	//DockPane(&m_wndProperties);


	// ���ù�������ͣ�����ڲ˵��滻
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// ���ÿ���(��ס Alt �϶�)�������Զ���
 	CMFCToolBar::EnableQuickCustomization();
 
// 	if (CMFCToolBar::GetUserImages() == NULL)
// 	{
// 		// �����û�����Ĺ�����ͼ��
// 		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
// 		{
// 			CMFCToolBar::SetUserImages(&m_UserImages);
// 		}
// 	}

	// ���ò˵����Ի�(���ʹ�õ�����)
	// TODO: �������Լ��Ļ������ȷ��ÿ�������˵�������һ���������
	//CList<UINT, UINT> lstBasicCommands;

	//lstBasicCommands.AddTail(ID_FILE_NEW);
	//lstBasicCommands.AddTail(ID_FILE_OPEN);
	//lstBasicCommands.AddTail(ID_FILE_SAVE);
	//lstBasicCommands.AddTail(ID_FILE_PRINT);
	//lstBasicCommands.AddTail(ID_APP_EXIT);
	//lstBasicCommands.AddTail(ID_EDIT_CUT);
	//lstBasicCommands.AddTail(ID_EDIT_PASTE);
	//lstBasicCommands.AddTail(ID_EDIT_UNDO);
	//lstBasicCommands.AddTail(ID_APP_ABOUT);
	//lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	//lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);

	//CMFCToolBar::SetBasicCommands(lstBasicCommands);
    CSplashWnd::ShowSplashScreen(NULL);
    Sleep(500);

	SDCM_DLL_Judge_Init(0, 0, g_bEnglish);
 
	AfxBeginThread(threadConnectManager, this);
	return 0;
}

CMFCStatusBar & CMainFrame::GetStatusBar()
{
	return m_wndStatusBar;
}

CMFCToolBar & CMainFrame::GetMyToolBar()
{
	return m_wndMyToolBar;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// BOOL CMainFrame::CreateDockingWindows()
// {
// 	BOOL bNameValid;
// 	// �������Դ���
// 	CString strPropertiesWnd;
// 	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
// 	ASSERT(bNameValid);
// 	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
// 	{
// 		TRACE0("δ�ܴ��������ԡ�����\n");
// 		return FALSE; // δ�ܴ���
// 	}
// 
// 	SetDockingWindowIcons(theApp.m_bHiColorIcons);
// 	return TRUE;
// }
// 
// void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
// {
// 	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
// 	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);
// 
// }

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	��Ʒ��Ȩ
	//CFrameWndEx::AssertValid();
	return;
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* ɨ��˵�*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// ���ཫִ�������Ĺ���

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// Ϊ�����û������������Զ��尴ť
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(FALSE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}
	return TRUE;
}

LRESULT CMainFrame::OnToolBarReset(WPARAM wp, LPARAM lp)
{
// 	CMFCToolBarComboBoxButton * combo = new CMFCToolBarComboBoxButton(ID_BUTTON_COMBO_FILE, GetCmdMgr()->GetCmdImage(ID_BUTTON_COMBO_FILE), CBS_DROPDOWN, 50);
// 	combo->EnableWindow(TRUE);
// 	combo->SetFlatMode();
// 	combo->SetCenterVert();
// 	combo->AddItem("hello");
// 
// 	combo->SetDropDownHeight(100);
// 	combo->Show(TRUE);
// 	m_wndMyToolBar.ReplaceButton(ID_BUTTON_COMBO_FILE, *combo, FALSE);
// 
 	return 0;
}

void CMainFrame::OnUpdateIndicatorLogo(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnUpdateIndicatorTime(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	CTime time = CTime::GetCurrentTime();
	pCmdUI->SetText(time.Format("%y-%m-%d %H:%M:%S"));
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CLAT2000Doc * pDoc = (CLAT2000Doc *)GetActiveDocument();
	if (NULL != pDoc)
	{
		if (pDoc->IsRunning())
		{
			AfxMessageBox("�в������ڽ��У���ֹͣ���Ժ����˳������");
			return;
		}
	}

	BeginWaitCursor();
	if (g_pDoc->m_CommSettingsData.m_bHaveEMS61000_11K)
	{
		g_EMS61000_11KComm.SetEUT(FALSE);
	}

	CExitSelectionDlg dlg;
	RealTimeData data;
	//�رղ��Ե�Դ
	if (g_DPSComm.IsRunning())
	{
		if (g_DPSComm.GetRealTimeData(data))
		{
			dlg.m_bResetDPS = data.fVoltageValue > 3 && data.fVoltageValue < 303;
		}
		else
		{
			dlg.m_bResetDPS = FALSE;
			dlg.m_bDPSEnable = FALSE;
		}
	}
	else
	{
		dlg.m_bResetDPS = FALSE;
		dlg.m_bDPSEnable = FALSE;
	}
	//�ر��¿�
	float fTMP;
	int nAlarm = 0;
	BOOL *bTMPControllerON;
	bTMPControllerON = new BOOL[g_iTMPControlNum];
	for (int i = 0; i < g_iTMPControlNum; i++)
	{
		if (g_FujiTMPComm.ReadTemperature(g_FujiTMPComm.m_ucAddress[i], fTMP, nAlarm))
		{
			bTMPControllerON[i] = TRUE;
			dlg.m_bResetTMPController = g_bTMPControllerON;
		}
		else
		{
			dlg.m_bResetTMPController = FALSE;
			dlg.m_bTMPControllerEnable = FALSE;
			bTMPControllerON[i] = FALSE;
		}
	}
	for (int i = 0; i < g_iTMPControlNum; i++)
	{
		if (bTMPControllerON[i] == TRUE)
		{
			dlg.m_bResetTMPController = g_bTMPControllerON;
			break;
		}
	}
	if (IDCANCEL == dlg.DoModal())
	{
		return;
	}
	if (dlg.m_bResetDPS)
	{
		if (!g_DPSComm.StopOutput())
		{
			AfxMessageBox("���Ե�Դֹͣʧ�ܣ�");
		}
	}
	if (dlg.m_bResetTMPController)
	{
		for (int i = 0; i < g_iTMPControlNum; i++)
		{
			if (bTMPControllerON[i] == FALSE)
			{
				continue;
			}
			if (!g_FujiTMPComm.SetTemperature(g_FujiTMPComm.m_ucAddress[i], 0, 0 , 0))
			{
				AfxMessageBox(g_myDockablePaneData.m_strTemperatureControllerText[i] + "ֹͣʧ�ܣ�");
			}
		}
	}
	ChannelState channelState[30];
	for (int i = 0; i < 30; i ++)
	{
		channelState[i] = CHANNEL_OFF;
	}
	if (g_pDoc->m_CommSettingsData.m_bHaveLEDIndicator)
	{
		g_IndicatorComm.SetAllChannelState(channelState);
	}
	if (g_pDoc->m_CommSettingsData.m_bHaveLRA)
		g_LRAComm.SwitchAllChannel(FALSE);
	EndWaitCursor();

	CFrameWndEx::OnClose();
}


void CMainFrame::OnUpdateWatchPane(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	//pCmdUI->Enable(TRUE);
	//pCmdUI->SetCheck(m_wndDialogPane.IsVisible());
}


void CMainFrame::OnWatchPane()
{
	// TODO: �ڴ���������������
	//m_wndDialogPane.ShowPane(!m_wndDialogPane.IsVisible(), FALSE, TRUE);
}


void CMainFrame::ActivateFrame(int nCmdShow)
{
	// TODO: �ڴ����ר�ô����/����û���
	nCmdShow = SW_SHOWMAXIMIZED;

	CFrameWndEx::ActivateFrame(nCmdShow);
}


UINT CMainFrame::threadConnectManager(LPVOID pPar)
{
	return 0;
    CMainFrame * pMain = (CMainFrame *)pPar;
    CAccreditData AccreditData;
    BOOL bR;

    char szName[256];
    char szNewName[256];

    sprintf_s(szName, _T("%s"), "LatSuite");
    CAccreditData::Name2NewName(szName, szNewName);
    CString strName = szNewName;

    CString strPathName = "C:\\Windows\\inf\\" + strName + ".PNF";		

    bR = AccreditData.Open(strPathName);
    if(bR == FALSE)
    {
        pMain->SetTimer(112, 30000, NULL);
         ::MessageBox(pMain->m_hWnd, "T1:��������ѹ��ڣ�����ϵԶ����˾�ṩ��ʽ�����!", NULL, MB_ICONWARNING);
        pMain->PostMessage(WM_QUIT,0,0);
        return 0;
    }

    while(1)
    {
        AccreditData.Add(CTime::GetCurrentTime());
        bR = AccreditData.Save(strPathName);
        if(bR == FALSE)
        {
            pMain->SetTimer(112, 30000, NULL);
           ::MessageBox(pMain->m_hWnd, "T2:��������ѹ��ڣ�����ϵԶ����˾�ṩ��ʽ�����!", 
               NULL, MB_ICONWARNING);       
            pMain->PostMessage(WM_QUIT,0,0);
            return 0;
        }

        if (AccreditData.CanUse() == FALSE)
        {
            pMain->SetTimer(112, 30000, NULL);
            ::MessageBox(pMain->m_hWnd, "T3:��������ѹ��ڣ�����ϵԶ����˾�ṩ��ʽ�����!", 
                NULL, MB_ICONWARNING);
            pMain->PostMessage(WM_QUIT,0,0);
            return 0;

        }

        Sleep(1000 * 60 * 5);
    }

    return 0;


}



void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if (112 == nIDEvent)
    {
        PostMessage(WM_QUIT,0,0);
        KillTimer(112);
    }
    CFrameWndEx::OnTimer(nIDEvent);
}
