// ContainerGridView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "LAT2000Doc.h"
#include "ContainerGridView.h"
#include "MainFrm.h"
#include "_cell.h"


// CContainerGridView
extern CString g_strPathNameAuto;
extern CString g_strHaveSaveCsvName;

IMPLEMENT_DYNCREATE(CContainerGridView, CFormView)

CContainerGridView::CContainerGridView()
	: CFormView(CContainerGridView::IDD)
{

}

CContainerGridView::~CContainerGridView()
{
}

void CContainerGridView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID_MAIN, m_cDataGrid);
}

BEGIN_MESSAGE_MAP(CContainerGridView, CFormView)
	ON_WM_SIZE()
	ON_MESSAGE(MSG_TEST_ENDED, &CContainerGridView::OnMsgTestEnded)
	ON_MESSAGE(MSG_GRID_EXPORT_DATA, &CContainerGridView::OnMsgGridExportData)
	ON_MESSAGE(MSG_GRID_RELIST_DATA, &CContainerGridView::OnMsgGridRelistData)
	ON_MESSAGE(MSG_SAVE_CSV_DATA, &CContainerGridView::OnMsgExportData)
	ON_WM_TIMER()
	ON_WM_CREATE()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CContainerGridView ���

#ifdef _DEBUG
void CContainerGridView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CContainerGridView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CContainerGridView ��Ϣ�������


void CContainerGridView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (!IsWindow(m_cDataGrid.GetSafeHwnd()))
	{
		return;
	}

	m_cDataGrid.ShowWindow(SW_HIDE);
	CRect rect;
	GetClientRect(&rect);
	m_cDataGrid.MoveWindow(&rect);
	m_cDataGrid.ShowWindow(SW_SHOW);
}


void CContainerGridView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	m_cDataGrid.SetRegisterInformation("CNwinndy", "W]vyY-nonvk-u\\nty-Zbl_e-`hms^");
	if (NULL != g_pDoc)
	{
		g_pDoc->m_hWndDataContainerGridView = m_hWnd;
		g_pDoc->m_dataContainer.ListData(m_cDataGrid);
	}
}


afx_msg LRESULT CContainerGridView::OnMsgTestEnded(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

BEGIN_EVENTSINK_MAP(CContainerGridView, CFormView)
	ON_EVENT(CContainerGridView, IDC_GRID_MAIN, 23, CContainerGridView::RowColChangeGrid1, VTS_I4 VTS_I4)
	ON_EVENT(CContainerGridView, IDC_GRID_MAIN, 12, CContainerGridView::GetCellTextGrid1, VTS_I4 VTS_I4 VTS_PBSTR VTS_PBOOL)
	ON_EVENT(CContainerGridView, IDC_GRID_MAIN, 13, CContainerGridView::SetCellTextGrid1, VTS_I4 VTS_I4 VTS_BSTR VTS_PBOOL)
	ON_EVENT(CContainerGridView, IDC_GRID_MAIN, 27, CContainerGridView::HyperLinkClickGrid1, VTS_I4 VTS_I4 VTS_PBSTR VTS_PBOOL)
	ON_EVENT(CContainerGridView, IDC_GRID_MAIN, 29, CContainerGridView::OwnerDrawCellGridMain, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_PBOOL)
END_EVENTSINK_MAP()


void CContainerGridView::RowColChangeGrid1(long Row, long Col)
{
	// TODO: �ڴ˴������Ϣ����������
	::PostMessageA(g_pDoc->m_hWndDataContainerDrawView, MSG_DATA_CONTAINER_DRAW, Row - 1, Col - 1);
}


afx_msg LRESULT CContainerGridView::OnMsgGridExportData(WPARAM wParam, LPARAM lParam)
{
	CFileDialog dlg(FALSE, "CSV", "LED����1.CSV", 6UL, "CSV�ļ�(*.CSV)|*.CSV|");
	if (IDOK == dlg.DoModal())
	{
		if (!m_cDataGrid.ExportToCSV(dlg.GetPathName(), TRUE, TRUE))
		{
			AfxMessageBox("����ʧ�ܣ�");
		}
		else
		{
			AfxMessageBox("�������ݳɹ���");
		}
	}

	return 0;
}

afx_msg LRESULT CContainerGridView::OnMsgExportData(WPARAM wParam, LPARAM lParam)
{
	//�����б�����
	m_cDataGrid.ExportToCSV(g_strPathNameAuto, TRUE, TRUE);
	DeleteFileA(g_strHaveSaveCsvName);
	g_strHaveSaveCsvName = g_strPathNameAuto;
	return 0;
}

afx_msg LRESULT CContainerGridView::OnMsgGridRelistData(WPARAM wParam, LPARAM lParam)
{
	SetTimer(2, 100, NULL);
	return 0;
}

void CContainerGridView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	BeginWaitCursor();
	if (1 == nIDEvent)
	{
		BeginWaitCursor();
		g_pDoc->m_dataContainer.ListData(m_cDataGrid);
		EndWaitCursor();
		//m_cDataGrid.Refresh();
	}
	else if (2 == nIDEvent)
	{
		BeginWaitCursor();
		g_pDoc->m_dataContainer.ListData(m_cDataGrid);
		EndWaitCursor();
		//m_cDataGrid.Refresh();
	}
	else if (3 == nIDEvent)
	{
		//m_cDataGrid.Refresh();
	}
	EndWaitCursor();

	KillTimer(nIDEvent);
	CFormView::OnTimer(nIDEvent);
}


void CContainerGridView::GetCellTextGrid1(long Row, long Col, BSTR* Text, BOOL* Changed)
{
	// TODO: �ڴ˴������Ϣ����������
	if (NULL == g_pDoc)
	{
		return;
	}
	if (Row >= 0 && Col >= 0)
	{
		BOOL bQualified = FALSE;
		int iTypeFail = 0;
		*Text = g_pDoc->m_dataContainer.GetVirtualItemText(Row, Col, g_pDoc->m_dataContainer.GetTestSettingData(), bQualified,iTypeFail).AllocSysString();
		*Changed = TRUE;
	}
}

void CContainerGridView::SetCellTextGrid1(long Row, long Col, LPCTSTR Text, BOOL* Cancel)
{
	// TODO: �ڴ˴������Ϣ����������
}

void CContainerGridView::HyperLinkClickGrid1(long Row, long Col, BSTR* URL, BOOL* Changed)
{
	// TODO: �ڴ˴������Ϣ����������
	CString strAlarm;
	strAlarm.Format("ȷ��ɾ���� %s ���Ե� %d ������ô��",
		m_cDataGrid.Cell(Row, Col).GetText(),
		g_pDoc->m_dataContainer.GetDataNumberTestAtTime(Row - 1));
	if (IDCANCEL == AfxMessageBox(strAlarm, MB_OKCANCEL))
	{
		CString strTemp = "";
		*URL = strTemp.AllocSysString();
		*Changed = TRUE;

		SetTimer(3, 200, NULL);
		return;
	}

	if (Row >= 0)
	{
		if (g_pDoc->m_dataContainer.DeleteDataTestAtTime(Row - 1))
		{
			g_pDoc->m_dataContainer.ListData(m_cDataGrid);
		}
	}
	
	CString strTemp = "";
	*URL = strTemp.AllocSysString();
	SetTimer(3, 200, NULL);
	*Changed = TRUE;
}


void CContainerGridView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (NULL != g_pDoc)
	{
		g_pDoc->m_hWndDataContainerGridView = m_hWnd;
		
		if (IsWindow(m_cDataGrid.GetSafeHwnd()))
		{
			int iiii = m_cDataGrid.GetCols();
			//m_cDataGrid.SetRegisterInformation("CNwinndy", "W]vyY-nonvk-u\\nty-Zbl_e-`hms^");
			g_pDoc->m_dataContainer.ListData(m_cDataGrid);
		}
	}
}

int CContainerGridView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}

void CContainerGridView::OwnerDrawCellGridMain(long Row, long Col, long hdc, long Left, long Top, long Right, long Bottom, BOOL* Handled)
{
	// TODO: �ڴ˴������Ϣ����������
	CDC * pDc = CDC::FromHandle((HDC)hdc);
	pDc->SetTextAlign(TA_CENTER);

	BOOL bQualified = FALSE;
	int iTypeFail = 0;
	CString strTemp = g_pDoc->m_dataContainer.GetVirtualItemText(Row, Col, g_pDoc->m_dataContainer.GetTestSettingData(), bQualified,iTypeFail);
	if (!bQualified)
	{
		pDc->SetTextColor(RGB(255, 0, 0));
	}
	else
	{
		pDc->SetTextColor(RGB(0, 0, 0));
	}
	if (1 == Col && Row > 0)
	{
		pDc->SetTextColor(RGB(0, 0, 255));
	}
    pDc->TextOutA((Left + Right) / 2, Top + 2, strTemp);

	*Handled = TRUE;
}

BOOL CContainerGridView::OnEraseBkgnd(CDC* pDC)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    return CFormView::OnEraseBkgnd(pDC);
}
