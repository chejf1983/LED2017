// LEDDataStatView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "LEDDataStatView.h"
#include "StatisticGridView.h"
#include "StatisticDistributionGridView.h"
#include "LAT2000Doc.h"
#include "_grid.h"


// CLEDDataStatView

IMPLEMENT_DYNCREATE(CLEDDataStatView, CFormView)

CLEDDataStatView::CLEDDataStatView()
	: CFormView(CLEDDataStatView::IDD)
{
    m_pFrame = NULL;
}

CLEDDataStatView::~CLEDDataStatView()
{
}

void CLEDDataStatView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLEDDataStatView, CFormView)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_ERASEBKGND()
    ON_COMMAND(ID_FILE_PRINT, &CLEDDataStatView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CLEDDataStatView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CLEDDataStatView::OnFilePrintPreview)
    ON_COMMAND(ID_EXPORT_STATISTIC_DATA, &CLEDDataStatView::OnExportStatisticData)
END_MESSAGE_MAP()


// CLEDDataStatView ���

#ifdef _DEBUG
void CLEDDataStatView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLEDDataStatView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLEDDataStatView ��Ϣ�������


int CLEDDataStatView::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

    m_cSplitterLeft.CreateView(0, 0, RUNTIME_CLASS(CStatisticGridView), CSize(300, 170), &context);		//��һ��һ��
    m_cSplitterLeft.CreateView(1, 0, RUNTIME_CLASS(CStatisticDistributionGridView), CSize(10,10), &context);	//��һ�ж���


    return 0;
}


void CLEDDataStatView::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();

    // TODO: �ڴ����ר�ô����/����û���

}


void CLEDDataStatView::OnSize(UINT nType, int cx, int cy)
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


BOOL CLEDDataStatView::OnEraseBkgnd(CDC* pDC)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    return TRUE;
    return CFormView::OnEraseBkgnd(pDC);
}


void CLEDDataStatView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
    // TODO: �ڴ����ר�ô����/����û���

    CFormView::OnBeginPrinting(pDC, pInfo);
}


void CLEDDataStatView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
    // TODO: �ڴ����ר�ô����/����û���
    CRect rect = pInfo->m_rectDraw;
    int iCur = pInfo->m_nCurPage;
    int iMax = pInfo->GetMaxPage();
    CRect printRect;
    if (rect.Height() > rect.Width())
    {
        printRect.SetRect(rect.Width() / 12, rect.Height() / 12, 
            rect.Width() / 12 * 11, rect.Height() / 24 * 23);
    }
    else
    {
        printRect.SetRect(rect.Width() / 12, rect.Height() / 9, 
            rect.Width() / 12 * 11, rect.Height() / 15 * 14);
    }

    g_pDoc->m_StatisticLedDataContainer.printHead(pDC, printRect);

    g_pDoc->m_StatisticLedDataContainer.printReport(pDC, printRect, iCur);

    g_pDoc->m_StatisticLedDataContainer.printFoot(pDC, printRect, iCur, iMax);
}


void CLEDDataStatView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
    // TODO: �ڴ����ר�ô����/����û���

    CFormView::OnEndPrinting(pDC, pInfo);
}


BOOL CLEDDataStatView::OnPreparePrinting(CPrintInfo* pInfo)
{

    // TODO:  ���� DoPreparePrinting �Ե��á���ӡ���Ի���

    int iMax = 3; 
    if (g_pDoc->m_StatisticLedDataContainer.GetStatisticParaNum() <= 20)
    {
        iMax = 3;
    }
    else
    {
        iMax = 5;
    }
    pInfo->SetMaxPage(iMax);
    return DoPreparePrinting(pInfo);
}


void CLEDDataStatView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
    // TODO: �ڴ����ר�ô����/����û���
    if (pInfo != NULL)
    {
        if (pInfo->m_nCurPage == 1)
        {
            DEVMODE *pDevMode = pInfo->m_pPD->GetDevMode();
            if (pDevMode->dmOrientation != DMORIENT_PORTRAIT)
            {
                pDevMode->dmOrientation = DMORIENT_PORTRAIT;
                pDC->ResetDC( pDevMode );
            }
        }
        else
        {
            DEVMODE *pDevMode = pInfo->m_pPD->GetDevMode();
            if (pDevMode->dmOrientation != DMORIENT_LANDSCAPE)
            {
                pDevMode->dmOrientation = DMORIENT_LANDSCAPE;
                pDC->ResetDC( pDevMode );
            }
        }  		

    }
    CFormView::OnPrepareDC(pDC, pInfo);
}


void CLEDDataStatView::OnExportStatisticData()
{
    // TODO: �ڴ���������������
    CStatisticGridView *pStatisticGridView = (CStatisticGridView*)FromHandle(g_pDoc->m_hWndStatisticGridView);
    CStatisticDistributionGridView *pStatisticDistributionGridView = (CStatisticDistributionGridView*)FromHandle(g_pDoc->m_hWndStatisticDisbuteGridView);
   
    CFileDialog dlg(FALSE, "CSV", "ͳ�Ʒ���1.CSV", 6UL, "CSV�ļ�(*.CSV)|*.CSV|");
    if (IDCANCEL == dlg.DoModal())
    {
        return;
    }
    pStatisticGridView->m_cStatisticGrid.ExportToCSV(g_strCurrentPath + "1.CSV", TRUE, TRUE);
    CFile file1;
    if (!file1.Open(g_strCurrentPath + "1.CSV", CFile::modeRead))
    {
        return ;
    }

    int iLength = (int)file1.GetLength();
    CString strTemp1;

    strTemp1.GetBufferSetLength(iLength + 1);
    file1.Read(strTemp1.GetBuffer(), iLength);
    file1.Close();
    DeleteFile(g_strCurrentPath + "1.CSV");

    pStatisticDistributionGridView->m_cStatisticDistributeGrid.ExportToCSV(g_strCurrentPath + "2.CSV", TRUE, TRUE);


    CFile file2;
    if (!file2.Open(g_strCurrentPath + "2.CSV", CFile::modeRead))
    {
        return ;
    }

    iLength = (int)file2.GetLength();
    CString strTemp2;

    strTemp2.GetBufferSetLength(iLength + 1);
    file2.Read(strTemp2.GetBuffer(), iLength);
    file2.Close();
    DeleteFile(g_strCurrentPath + "2.CSV");

    CFile file3;
    if (!file3.Open(dlg.GetPathName(), CFile::modeCreate|CFile::modeWrite))
    {
        return ;
    }
    CString strTemp;
    strTemp = "�������ݽ������";
    file3.Write(strTemp.GetBuffer(), strTemp.GetLength());
    strTemp = "\n";
    file3.Write(strTemp.GetBuffer(), strTemp.GetLength());
    strTemp.Format("�ܸ���%d��, �ϸ���%d(%.2f%%)��, ���ϸ���(����ֵ)%d(%.2f%%)��, ���ϸ���(�޵ƻ�δ��)%d(%.2f%%)��",
        g_pDoc->m_StatisticLedDataContainer.GetQLEDNum() + g_pDoc->m_StatisticLedDataContainer.GetUnQLEDNum() + g_pDoc->m_StatisticLedDataContainer.GetUnONLEDNum(),
        g_pDoc->m_StatisticLedDataContainer.GetQLEDNum(), g_pDoc->m_StatisticLedDataContainer.GetQLEDNumPer(),
        g_pDoc->m_StatisticLedDataContainer.GetUnQLEDNum(), g_pDoc->m_StatisticLedDataContainer.GetUnQLEDNumPer(),
        g_pDoc->m_StatisticLedDataContainer.GetUnONLEDNum(), g_pDoc->m_StatisticLedDataContainer.GetUnONLEDNumPer());
    file3.Write(strTemp.GetBuffer(), strTemp.GetLength());
    strTemp = "\n";
    file3.Write(strTemp.GetBuffer(), strTemp.GetLength());
    strTemp = "\n";
    file3.Write(strTemp.GetBuffer(), strTemp.GetLength());

    strTemp = "ͳ�Ʋ������ݷ���";
    file3.Write(strTemp.GetBuffer(), strTemp.GetLength());
    strTemp = "\n";
    file3.Write(strTemp.GetBuffer(), strTemp.GetLength());
    file3.Write(strTemp1.GetBuffer(),strTemp1.GetLength());
    strTemp = "\n";
    file3.Write(strTemp.GetBuffer(), strTemp.GetLength());
    file3.Write(strTemp.GetBuffer(), strTemp.GetLength());
    file3.Write(strTemp.GetBuffer(), strTemp.GetLength());

    strTemp = "ͳ�Ʋ�������ֲ�ͳ��";
    file3.Write(strTemp.GetBuffer(), strTemp.GetLength());
    strTemp = "\n";
    file3.Write(strTemp.GetBuffer(), strTemp.GetLength());
    file3.Write(strTemp2.GetBuffer(), strTemp2.GetLength());
    strTemp = "\n";
    file3.Write(strTemp.GetBuffer(), strTemp.GetLength());
    file3.Close();
    strTemp1.ReleaseBuffer();
    strTemp2.ReleaseBuffer();

}
