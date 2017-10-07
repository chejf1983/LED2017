// StatisticGridView.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "StatisticGridView.h"
#include "LAT2000Doc.h"


// CStatisticGridView
IMPLEMENT_DYNCREATE(CStatisticGridView, CFormView)

CStatisticGridView::CStatisticGridView()
	: CFormView(CStatisticGridView::IDD)
{

}

CStatisticGridView::~CStatisticGridView()
{
}

void CStatisticGridView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_GRID_STATISTIC, m_cStatisticGrid);      
}

BEGIN_MESSAGE_MAP(CStatisticGridView, CFormView)
    ON_WM_SIZE()
    ON_MESSAGE(MSG_STATISTIC_GRID_RELIST_DATA, &CStatisticGridView::OnMsgStatisticGridRelistData)
    ON_WM_TIMER()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CStatisticGridView 诊断

#ifdef _DEBUG
void CStatisticGridView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStatisticGridView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStatisticGridView 消息处理程序


void CStatisticGridView::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();

    // TODO: 在此添加专用代码和/或调用基类

    if (NULL != g_pDoc)
    {
        g_pDoc->m_hWndStatisticGridView = m_hWnd;
        g_pDoc->m_StatisticLedDataContainer.ListStatisticData(m_cStatisticGrid);

    }
}


void CStatisticGridView::OnSize(UINT nType, int cx, int cy)
{
    CFormView::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码
    if (!IsWindow(m_cStatisticGrid.GetSafeHwnd()))
    {
        return;
    }

    m_cStatisticGrid.ShowWindow(SW_HIDE);
    CRect rect;
    GetClientRect(&rect);
    CRect RectTemp; 
    RectTemp = rect;
    m_cStatisticGrid.MoveWindow(&RectTemp);
    m_cStatisticGrid.ShowWindow(SW_SHOW);
 }
BEGIN_EVENTSINK_MAP(CStatisticGridView, CFormView)
    ON_EVENT(CStatisticGridView, IDC_GRID_STATISTIC, 29, CStatisticGridView::OwnerDrawCellGridStatistic, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_PBOOL)
    ON_EVENT(CStatisticGridView, IDC_GRID_STATISTIC, 12, CStatisticGridView::GetCellTextGridStatistic, VTS_I4 VTS_I4 VTS_PBSTR VTS_PBOOL)
END_EVENTSINK_MAP()


void CStatisticGridView::OwnerDrawCellGridStatistic(long Row, long Col, long hdc, long Left, long Top, long Right, long Bottom, BOOL* Handled)
{
    // TODO: 在此处添加消息处理程序代码
    CDC * pDc = CDC::FromHandle((HDC)hdc);
    pDc->SetTextAlign(TA_CENTER);   
    pDc->SetTextColor(RGB(0, 0, 0));

    CString strTemp = g_pDoc->m_StatisticLedDataContainer.GetStatisticItemText(Row, Col);

    pDc->TextOutA((Left + Right) / 2, Top + 2, strTemp);

    *Handled = TRUE;
}

afx_msg LRESULT CStatisticGridView::OnMsgStatisticGridRelistData(WPARAM wp, LPARAM lp)
{
    SetTimer(2, 100, NULL);
    return 0;
}

void CStatisticGridView::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    if (2 == nIDEvent)
    {
        BeginWaitCursor();
        g_pDoc->m_StatisticLedDataContainer.ListStatisticData(m_cStatisticGrid);
        EndWaitCursor();
        //m_cDataGrid.Refresh();
    }

    KillTimer(nIDEvent);
    CFormView::OnTimer(nIDEvent);
}

BOOL CStatisticGridView::OnEraseBkgnd(CDC* pDC)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    return CFormView::OnEraseBkgnd(pDC);
}

void CStatisticGridView::GetCellTextGridStatistic(long Row, long Col, BSTR* Text, BOOL* Changed)
{
    // TODO: 在此处添加消息处理程序代码
    if (NULL == g_pDoc)
    {
        return;
    }
    if (Row >= 0 && Col >= 0)
    {
        * Text = g_pDoc->m_StatisticLedDataContainer.GetStatisticItemText(Row, Col).AllocSysString();;
        * Changed = TRUE;
    }
}
