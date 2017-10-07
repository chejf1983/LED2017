// MainTabWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "MainTabWnd.h"
#include "MainTestFormView.h"
#include "LEDDataContainerView.h"
#include "LEDDataStatView.h"
#include "ContainerWatchView.h"

// CMainTabWnd

IMPLEMENT_DYNCREATE(CMainTabWnd, CTabView)

CMainTabWnd::CMainTabWnd()
{

}

CMainTabWnd::~CMainTabWnd()
{
}

BEGIN_MESSAGE_MAP(CMainTabWnd, CTabView)
	ON_WM_CREATE()
	ON_MESSAGE(MSG_MAINTABVIEW_RELIST, &CMainTabWnd::OnMsgMaintabviewRelist)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMainTabWnd ���

#ifdef _DEBUG
void CMainTabWnd::AssertValid() const
{
	CTabView::AssertValid();
}

#ifndef _WIN32_WCE
void CMainTabWnd::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMainTabWnd ��Ϣ�������


int CMainTabWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CCreateContext contex;
	contex.m_pCurrentDoc = GetDocument();

	contex.m_pNewViewClass = RUNTIME_CLASS(CMainTestFormView);
	AddView(RUNTIME_CLASS(CMainTestFormView), " ���Դ���", 0, &contex);

	contex.m_pNewViewClass = RUNTIME_CLASS(CLEDDataContainerView);
	AddView(RUNTIME_CLASS(CLEDDataContainerView), " ���ݴ���  ", 1, &contex);
	
	contex.m_pNewViewClass = RUNTIME_CLASS(CContainerWatchView);
	AddView(RUNTIME_CLASS(CContainerWatchView), " ���Ӵ���  ", 2, &contex);
		
    if (g_bStatistic)
    {
        contex.m_pNewViewClass = RUNTIME_CLASS(CLEDDataStatView);
        AddView(RUNTIME_CLASS(CLEDDataStatView), " ͳ�ƴ���  ", 3, &contex);
    }


	GetTabControl().SetTabBorderSize(4);

	return 0;
}


void CMainTabWnd::OnInitialUpdate()
{
	CTabView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	// style


    m_wndTabs.ModifyTabStyle(CMFCTabCtrl::STYLE_3D_ONENOTE);
    m_wndTabs.SetActiveTabBoldFont(FALSE);
    m_wndTabs.SetLocation(CMFCBaseTabCtrl::LOCATION_TOP);  

 	GetTabControl().HideSingleTab(TRUE);
 	GetTabControl().EnableTabSwap(FALSE);

	if (NULL != g_pDoc)
	{
		g_pDoc->m_hWndMainTabView = m_hWnd;
	}


    GetTabControl().SetImageList (IDB_TAB24, 24, RGB(255,255,255));
    HICON hicon1 = AfxGetApp()->LoadIcon(IDI_ICON_TAB3);
    HICON hicon2 = AfxGetApp()->LoadIcon(IDI_ICON_TAB1);
    HICON hicon3 = AfxGetApp()->LoadIcon(IDI_ICON_TAB2);

    GetTabControl().SetTabHicon(0, hicon1);
    GetTabControl().SetTabHicon(1, hicon2);
	GetTabControl().SetTabHicon(2, hicon3);
    if (g_bStatistic)
    {
        GetTabControl().SetTabHicon(3, hicon3);
    }

	GetTabControl().ShowTab(0, TRUE);
	GetTabControl().ShowTab(1, TRUE);
    if (g_bStatistic)
    {
        GetTabControl().ShowTab(3, TRUE);  
    }
    GetTabControl().RecalcLayout();
    m_wndTabs.RedrawWindow ();
}


afx_msg LRESULT CMainTabWnd::OnMsgMaintabviewRelist(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


BOOL CMainTabWnd::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CTabView::PreTranslateMessage(pMsg);
}


void CMainTabWnd::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CTabView::OnClose();
}
