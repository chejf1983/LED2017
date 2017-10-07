// LEDDataContainerView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "LEDDataContainerView.h"
#include "ContainerDrawFormView.h"
#include "ContainerGridView.h"
#include "LAT2000Doc.h"


// CLEDDataContainerView

IMPLEMENT_DYNCREATE(CLEDDataContainerView, CFormView)

CLEDDataContainerView::CLEDDataContainerView()
	: CFormView(CLEDDataContainerView::IDD)
{
	m_pFrame = NULL;
}

CLEDDataContainerView::~CLEDDataContainerView()
{
}

void CLEDDataContainerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLEDDataContainerView, CFormView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_COMMAND(ID_BUTTON_EXPORT, &CLEDDataContainerView::OnButtonExport)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_EXPORT, &CLEDDataContainerView::OnUpdateButtonExport)
	//ON_COMMAND(ID_FILE_SAVE_AS, &CLEDDataContainerView::OnFileSaveAs)
	//ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, &CLEDDataContainerView::OnUpdateFileSaveAs)
	//ON_COMMAND(ID_FILE_OPEN, &CLEDDataContainerView::OnFileOpen)
	//ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, &CLEDDataContainerView::OnUpdateFileOpen)
	ON_UPDATE_COMMAND_UI(ID_MENU_PRINT, &CLEDDataContainerView::OnUpdateMenuPrint)
	ON_COMMAND(ID_MENU_PRINT, &CLEDDataContainerView::OnMenuPrint)
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CLEDDataContainerView ���

#ifdef _DEBUG
void CLEDDataContainerView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLEDDataContainerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLEDDataContainerView ��Ϣ�������


void CLEDDataContainerView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (NULL == m_pFrame)
	{
		return;
	}

	CRect rect;
	GetClientRect(&rect);
	m_pFrame->MoveWindow(&rect);
	m_pFrame->ShowWindow(SW_SHOW);
}


void CLEDDataContainerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
}


int CLEDDataContainerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CString strMyClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW,  
            ::LoadCursor(NULL, IDC_ARROW), (HBRUSH)::GetStockObject(WHITE_BRUSH),   
            ::LoadIcon(NULL, IDI_APPLICATION));

	CRect rect;
	GetClientRect(&rect);
	CSize size = rect.Size();
	size.cy = size.cy / 2;

	// Create the frame window with "this" as the parent
	m_pFrame = new CFrameWnd();
    m_pFrame->Create(strMyClass, "", WS_CHILD, rect, this);
    m_pFrame->ShowWindow(SW_SHOW);

    // and finally, create the splitter with the frame as the parent
    m_cSplitterLeft.CreateStatic(m_pFrame,2, 1); //��Frame���з���ͼ����Ϊ1��2������һ������
	//m_cSplitterLeft.SetColumnInfo(0, size.cx, 50);

	// 1. Left
	//m_csplitterright.createstatic( &m_csplitterleft, 2, 1, ws_child | ws_visible, m_csplitterleft.idfromrowcol(0, 0) );

	//m_csplitterright.createview(0, 0, runtime_class(cregionlistformview), size, null);
	//
	//m_csplitterright.createview(1, 0, runtime_class(cvertexlistformview), csize(10,10), null);
	
	// 2. Right
	CCreateContext context;
	context.m_pCurrentFrame = (CFrameWnd *)AfxGetApp()->GetMainWnd();
	context.m_pCurrentDoc = GetDocument();

    m_cSplitterLeft.CreateView(0, 0, RUNTIME_CLASS(CContainerDrawFormView), CSize(300, 300), &context);		//��һ��һ��
    m_cSplitterLeft.CreateView(1, 0, RUNTIME_CLASS(CContainerGridView), CSize(10,10), &context);	//��һ�ж���
	
	return 0;
}



void CLEDDataContainerView::OnButtonExport()
{
	// TODO: �ڴ���������������
	if (NULL != g_pDoc)
	{
		::PostMessageA(g_pDoc->m_hWndDataContainerGridView, MSG_GRID_EXPORT_DATA, 0, 0);
	}
}


void CLEDDataContainerView::OnUpdateButtonExport(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (NULL != g_pDoc)
	{
		pCmdUI->Enable(!g_pDoc->IsRunning());
	}
}


void CLEDDataContainerView::OnFileSaveAs()
{
	// TODO: �ڴ���������������
	if (NULL == g_pDoc)
	{
		return;
	}

	CFileDialog dlg(FALSE, "dat", "LED�����ļ�.dat", 6UL, "LED�����ļ�(*.dat)|*.dat");
	if (IDOK == dlg.DoModal())
	{
		CFile file;
		if (!file.Open(dlg.GetPathName(), CFile::modeCreate | CFile::modeWrite))
		{
			AfxMessageBox("�����ļ�ʧ�ܣ�");
			return;
		}
		
		CArchive ar(&file, CArchive::store);
		g_pDoc->m_dataContainer.Serialize(ar);

		ar.Close();
		file.Close();
	}
}


void CLEDDataContainerView::OnUpdateFileSaveAs(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (NULL != g_pDoc)
	{
		pCmdUI->Enable(!g_pDoc->IsRunning());
	}
}


void CLEDDataContainerView::OnFileOpen()
{
	// TODO: �ڴ���������������
	if (NULL == g_pDoc)
	{
		return;
	}

	CFileDialog dlg(TRUE, NULL, NULL, 6UL, "LED�����ļ�(*.dat)|*.dat|", this);
	if (IDOK == dlg.DoModal())
	{
		CFile file;
		if (!file.Open(dlg.GetPathName(), CFile::modeRead))
		{
			AfxMessageBox("���ļ�ʧ�ܣ�");
			return;
		}
		
		CArchive ar(&file, CArchive::load);
		g_pDoc->m_dataContainer.Serialize(ar);

		ar.Close();
		file.Close();
		
		::PostMessageA(g_pDoc->m_hWndDataContainerGridView, MSG_GRID_RELIST_DATA, 0, 0);
	}
}


void CLEDDataContainerView::OnUpdateFileOpen(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (NULL != g_pDoc)
	{
		pCmdUI->Enable(!g_pDoc->IsRunning());
	}
}


void CLEDDataContainerView::OnUpdateMenuPrint(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (NULL != g_pDoc)
	{
		pCmdUI->Enable(!g_pDoc->IsRunning());
	}
}


void CLEDDataContainerView::OnMenuPrint()
{
	// TODO: �ڴ���������������
	if (NULL != g_pDoc)
	{
		::PostMessageA(g_pDoc->m_hWndDataContainerDrawView, MSG_CONTAINER_DRAW_PRINT, 0, 0);
	}
}


BOOL CLEDDataContainerView::OnEraseBkgnd(CDC* pDC)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    return TRUE;
    return CFormView::OnEraseBkgnd(pDC);
}
