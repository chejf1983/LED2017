// ContainerDrawFormView.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "ContainerDrawFormView.h"
#include "RegionToolDLL.h"
#include "LAT2000Doc.h"
#include "iplotchannelx.h"
#include "iplotdataviewx.h"
#include "iplotlegendx.h"


// CContainerDrawFormView

IMPLEMENT_DYNCREATE(CContainerDrawFormView, CFormView)

CContainerDrawFormView::CContainerDrawFormView()
	: CFormView(CContainerDrawFormView::IDD)
{
	m_iCurrentItem = 0;
	
	m_font.CreateFont(-18,0,0,60,400,FALSE,FALSE,0,
		GB2312_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"NONE");
    m_bFir = TRUE;
}

CContainerDrawFormView::~CContainerDrawFormView()
{
}

void CContainerDrawFormView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    //DDX_Control(pDX, IDC_IPLOTX1, m_cSpectrum);
    DDX_Control(pDX, IDC_NTGRAPHCTRL1, m_cRegion);
    DDX_Control(pDX, IDC_AXCIEXYZCTRL1, m_cCIE);
    DDX_Control(pDX, IDC_AX_SPECTRUMDRAWCTRL1, m_cSpectrum);
}

BEGIN_MESSAGE_MAP(CContainerDrawFormView, CFormView)
	ON_WM_SIZE()
	ON_MESSAGE(MSG_DATA_CONTAINER_DRAW, &CContainerDrawFormView::OnMsgDataContainerDraw)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CContainerDrawFormView::OnTcnSelchangeTab1)
	ON_MESSAGE(MSG_CONTAINER_DRAW_PRINT, &CContainerDrawFormView::OnMsgContainerDrawPrint)
	ON_WM_CTLCOLOR()
    ON_WM_CREATE()
END_MESSAGE_MAP()


// CContainerDrawFormView 诊断

#ifdef _DEBUG
void CContainerDrawFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CContainerDrawFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CContainerDrawFormView 消息处理程序


void CContainerDrawFormView::RedrawRegion()
{
	if (!UpdateData(TRUE) || NULL == g_pDoc)
	{
		return;
	}
	if (!IsWindow(m_cRegion.GetSafeHwnd()))
	{
		return;
	}
	
	// 1.1 Draw region element
 	HDC dHdc = ::GetDC(m_cRegion);
 	CRect dRect;
 	dRect.left = 0;
 	dRect.top = 0;
 	dRect.right = 200;
	dRect.bottom = 200;
 	//SDCM_DLL_DrawSDCM_OneGra(dHdc, dRect, 0.4f, 0.4f, FALSE, FALSE);
 	Region_DrawRegion(m_cRegion, -1);
	float fLeft = 0.0f, fTop = 0.0f, fRight = 0.0f, fBottom = 0.0f;
	Region_GetOutlineRect(fLeft, fTop, fRight, fBottom);
	
	// 1.3 Draw selected item point
	m_cRegion.AddElement();
	int iElementID = m_cRegion.GetElementCount() - 1;
	float fx = 0.0f, fy = 0.0f;

	m_cRegion.SetElement(iElementID);
	m_cRegion.SetElementName("");
	m_cRegion.SetElementLinetype(5);
	m_cRegion.SetElementIdentify(TRUE);
	m_cRegion.SetElementPointColor(RGB(255, 150, 150));
	m_cRegion.SetElementPointSymbol(4);
	m_cRegion.SetElementWidth (5);
	m_cRegion.SetElementSolidPoint(TRUE);

	if (m_iCurrentItem >= 0 && m_iCurrentItem < g_pDoc->m_dataContainer.GetSize())
	{
		fx = g_pDoc->m_dataContainer.GetAt(m_iCurrentItem).m_ColorData.m_fCIEx;
		fy = g_pDoc->m_dataContainer.GetAt(m_iCurrentItem).m_ColorData.m_fCIEy;

		m_cRegion.PlotXY(fx, fy, iElementID);
	}

	// Zoom
	float fXMin = fLeft		- (fRight - fLeft) / 4;
	float fXMax = fRight	+ (fRight - fLeft) / 10;
	float fYMin = fBottom	- (fTop - fBottom) / 10;
	float fYMax = fTop		+ (fTop - fBottom) / 10;
	m_cRegion.SetRange(fXMin, fXMax, fYMin, fYMax);
}

void CContainerDrawFormView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (!IsWindow(m_cCIE.GetSafeHwnd()))
	{
		return;
	}
	
	SetPos();
}

void CContainerDrawFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	m_cCIE.SetSzPath(g_strCurrentPath + "AX_CIE_XYZ\\");
	RedrawRegion();
	SetPos();
    if (m_bFir)
    {
        m_cTab.AddTab(&m_cRegion, "区域", 0);
        m_cTab.AddTab(&m_cCIE, "色品图", 1);
		m_cTab.AddTab(&m_wndSDCM, "SDCM", 2, FALSE);
        m_bFir = FALSE;
    }
	RedrawRegion();
	SetPos();
	m_cTab.SetImageList (IDB_TAB16, 16, RGB(255,255,255));
	m_cTab.SetTabIcon(1, 0);
	m_cTab.SetTabIcon(0, 1);

	CRect rect, rectItem;
	m_cRegion.ShowWindow(SW_SHOW);
	m_cCIE.ShowWindow(SW_HIDE);
	m_cTab.GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.DeflateRect(2, 20, 2, 2);
	m_cRegion.MoveWindow(&rect);
	m_cTab.SetActiveTab(0);
	m_cTab.RecalcLayout();
	SetPos();
	if (NULL != g_pDoc)
	{
		g_pDoc->m_hWndDataContainerDrawView = m_hWnd;
	}

	m_cSpectrum.SetWaveLengthStart(380.0f);
	m_cSpectrum.SetWaveLengthEnd(780.0f);
}

afx_msg LRESULT CContainerDrawFormView::OnMsgDataContainerDraw(WPARAM wParam, LPARAM lParam)
{
	int iRow = (int)wParam;
	int iCol = (int)lParam;
	if (iRow >=0 && iRow < g_pDoc->m_dataContainer.GetSize())
	{
		m_cSpectrum.ClearAllData();
		g_pDoc->m_iGridCurrentItem = iRow;
		CLedData & data = g_pDoc->m_dataContainer.GetAt(iRow);

		// 1.Relative spectrum value
		if (data.m_ColorData.m_bHaveColorData)
		{
			int iCount = 0;
            float fWLArray[4096];
            for (float fWL = data.m_ColorData.m_fWL1; fWL <= data.m_ColorData.m_fWL2 || iCount < 4096; fWL += data.m_ColorData.m_fIntervalWL)
            {
                fWLArray[iCount++] = fWL;
            }

            m_cSpectrum.SetSpectDrawPara(fWLArray, data.m_ColorData.m_fPL, iCount, data.m_ColorData.m_fIntervalWL);

			m_wndSDCM.ReDraw(data.m_ColorData.m_fCIEx, data.m_ColorData.m_fCIEy);
		}
		else
		{
			m_wndSDCM.ReDraw(0,0);
		}

		// 2.CIE
		m_cCIE.SetX(data.m_ColorData.m_fCIEx);
		m_cCIE.SetY(data.m_ColorData.m_fCIEy);

		// 3.Region
		m_iCurrentItem = iRow;
		RedrawRegion();
	}
	else
	{
		m_wndSDCM.ReDraw(0,0);
	}

	return 0;
}

void CContainerDrawFormView::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CRect rect;
// 	if (0 == m_cTab.GetActiveTab())
// 	{
// 		m_cRegion.ShowWindow(SW_SHOW);
// 		m_cCIE.ShowWindow(SW_HIDE);
// 		m_cTab.GetWindowRect(&rect);
// 		ScreenToClient(&rect);
// 		//rect.DeflateRect(2, 20, 2, 2);
// 		//m_cRegion.MoveWindow(&rect);
// 		SetPos();
// 	}
// 	else if (1 == m_cTab.GetActiveTab())
// 	{
// 		m_cRegion.ShowWindow(SW_HIDE);
// 		m_cCIE.ShowWindow(SW_SHOW);
// 		m_cTab.GetWindowRect(&rect);
// 		ScreenToClient(&rect);
// 		rect.DeflateRect(2, 20, 2, 2);
// 		//m_cCIE.MoveWindow(&rect);
// 		SetPos();
// 	}
}


afx_msg LRESULT CContainerDrawFormView::OnMsgContainerDrawPrint(WPARAM wParam, LPARAM lParam)
{
	CLAT2000Doc * pDoc = g_pDoc;

	CPrintDialog * pPrintDlg = new CPrintDialog(FALSE, PD_ALLPAGES | PD_RETURNDC, NULL);
	pPrintDlg->m_pd.nMinPage	= 1;
	pPrintDlg->m_pd.nMaxPage	= 1;
	pPrintDlg->m_pd.nFromPage	= 1;
	pPrintDlg->m_pd.nToPage		= 1;

	if (IDCANCEL == pPrintDlg->DoModal())
	{
		return 1;
	}

	CRect	m_pageRect;
	HDC		m_hdcPrint;
	CDC		*m_pPrintDC;

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
		return 1;
	}

	delete pPrintDlg;
	return 0;
}

void CContainerDrawFormView::PrintPage(CDC * pDC, CRect printRect, int nPage)
{
	CLAT2000Doc * pDoc = g_pDoc;
	int iLEDIndex = g_pDoc->m_iGridCurrentItem;
	int iRow = iLEDIndex / pDoc->m_TestContainer.GetLEDColumnSize();
	int iColumn = iLEDIndex % pDoc->m_TestContainer.GetLEDColumnSize();

	TEXTMETRIC  tm;
	pDC->GetTextMetrics(&tm);
	int fontHeight = tm.tmHeight+tm.tmExternalLeading;
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
			1, 1);
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

	CRect rect(printRect.Width()/12,printRect.Height()/12,printRect.Width()/12*11,printRect.Height()/12*10);

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

void CContainerDrawFormView::PrintLEDData(CDC * pDC, CRect printRect, int iLEDIndex)
{
	int iRow, iColumn;
	if (!g_pDoc->m_dataContainer.GetLEDRowColumn(iLEDIndex, iRow, iColumn))
	{
		return;
	}
	CLedData & data = g_pDoc->m_dataContainer.GetAt(iLEDIndex);

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

	if (data.IsValid())
	{
		pOldFont = pDC->SelectObject(&Font1);

		CString strTemp = "L E D 测 试 报 告";
		pDC->SetTextAlign(TA_CENTER);
		pDC->TextOut(printRect.left + printRect.Width()/2,printRect.top + printRect.Height()/15, strTemp);

		// Picture			
		CDC dcComp;
		BITMAP bm;
		CBitmap m_bmp;
		CBitmap *oldbmp;
		
		OpenClipboard();
		HBITMAP hbmp = (HBITMAP)GetClipboardData(CF_BITMAP);
		m_bmp.Attach(hbmp);
		m_bmp.GetBitmap(&bm);
		if(!dcComp.CreateCompatibleDC(pDC))
		{
			CloseClipboard();
			return;
		}
		
		CRect drRect, drRectRight;
		
		drRect.left		= printRect.left + printRect.Width()/136;
		drRect.right	= printRect.right - printRect.Width()/3;
		drRect.top		= printRect.top + printRect.Height()/6;
		drRect.bottom	= drRect.top + (int)(drRect.Width() * bm.bmHeight * 1.0f / bm.bmWidth); 
		
		oldbmp = (CBitmap *)dcComp.SelectObject(&m_bmp);
		pDC->StretchBlt(drRect.left,drRect.top,drRect.Width(),drRect.Height()
			,&dcComp,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
		dcComp.SelectObject(oldbmp);
		
		// CIE bitmap
		drRectRight.left	= drRect.right;
		drRectRight.top		= drRect.top;
		drRectRight.right	= printRect.right - printRect.Width() / 136;
		drRectRight.bottom	= drRect.bottom;
		
		if (m_cCIE.IsWindowVisible())
		{
			m_cCIE.CopyBMP();
		}
		else
		{
			m_cRegion.CopyToClipboard();
		}
		OpenClipboard();
		hbmp = (HBITMAP)GetClipboardData(CF_BITMAP);
		m_bmp.Detach();
		m_bmp.Attach(hbmp);
		m_bmp.GetBitmap(&bm);
		
		oldbmp = (CBitmap *)dcComp.SelectObject(&m_bmp);
		pDC->StretchBlt(drRectRight.left, drRectRight.top, drRectRight.Width(), drRectRight.Height()
			,&dcComp,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
		dcComp.SelectObject(oldbmp);
		
		DeleteObject(m_bmp.Detach());
		DeleteDC(dcComp);
		CloseClipboard();


		// Print data
		printRect.top = drRect.bottom + printRect.Height() / 72;
		pDC->SetTextAlign(TA_LEFT);
		int iX = printRect.left + printRect.Width()/25;
		int iY = printRect.top + printRect.Height()/6;
		int iyStep = printRect.Height()/20;
		int ixTap = printRect.Width()/25;

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


		// Test information
		pDC->SelectObject(&Font2);
		iY += iyStep * 3;
		iX -= ixTap * 12;
		iX -= ixTap;
		strTemp = "测试信息";
		pDC->TextOut(iX, iY, strTemp);
		pDC->SelectObject(&Font3);

		iY += iyStep * 2;
		iX += ixTap;
		strTemp.Format("LED行列: %d (%d,%d)",
			iLEDIndex + 1, iRow + 1, iColumn + 1);
		pDC->TextOut(iX, iY, strTemp);

		iX += ixTap * 12;
		CTime time = g_pDoc->m_dataContainer.GetLEDTestTime(iLEDIndex);
		strTemp = "测试时间:";
		strTemp +=  time.Format("%Y/%m/%d %H:%M:%S");
		pDC->TextOut(iX, iY, strTemp);
	}
	else
	{
		CString strTemp;
		strTemp.Format("LED%d[%d-%d] is invalid!", iLEDIndex + 1, iRow + 1, iColumn + 1);
		pDC->TextOut(printRect.CenterPoint().x, printRect.CenterPoint().y, strTemp);
	}
}

HBRUSH CContainerDrawFormView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


int CContainerDrawFormView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CFormView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  在此添加您专用的创建代码
    m_cTab.Create(CMFCTabCtrl::STYLE_3D_ONENOTE, CRect(0, 0, 0, 0), this, IDC_TAB1, 
        CMFCTabCtrl::LOCATION_TOP);
	if (!m_wndSDCM.Create (IDD_SDCM, &m_cTab))
	{
		AfxMessageBox("Error");
	}
	m_wndSDCM.SetFont (&afxGlobalData.fontRegular);

    return 0;
}


void CContainerDrawFormView::SetPos(void)
{
/*	CRect rectClient;
	GetClientRect(&rectClient);

	// rect1 | rect 2
	CRect rect1 = rectClient, rect2 = rectClient;
	rect1.right = rect1.left + rectClient.Width() * 2 / 3;
	rect2.left = rect1.right;
	rect1.DeflateRect(2, 2);
	rect2.DeflateRect(2, 2);

	m_cSpectrum.MoveWindow(&rect1);

	m_cTab.MoveWindow(&rect2);
	CRect rect;
	m_cTab.GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.DeflateRect(2, 20, 2, 2);
	m_cRegion.MoveWindow(&rect);
	m_cCIE.MoveWindow(&rect);*/
     CRect rectClient;
     GetClientRect(&rectClient);

	if (m_bFir)
	{
		m_cSpectrum.MoveWindow(&rectClient);
		m_cTab.MoveWindow(&rectClient);
		m_cRegion.MoveWindow(&rectClient);
		m_cCIE.MoveWindow(&rectClient);
		return;
	}

    // rect1 | rect 2
	CRect dRect1;
	CRect dRect2;

	dRect1.left		= rectClient.left;
	dRect1.right	= rectClient.left + rectClient.Width() * 2 / 3;
	dRect1.top		= rectClient.top;
	dRect1.bottom	= rectClient.bottom;
    m_cSpectrum.MoveWindow(&dRect1);
	
	dRect2.left		= dRect1.right;
	dRect2.right	= rectClient.right;
	dRect2.top		= rectClient.top;
	dRect2.bottom	= rectClient.bottom;

    m_cTab.MoveWindow(&dRect2);

    CRect rect;
    m_cTab.GetWindowRect(&rect);
    ScreenToClient(&rect);
    rect.DeflateRect(2, 26, 2, 2);
	
    m_cRegion.MoveWindow(&rect);
    m_cCIE.MoveWindow(&rect);
}
