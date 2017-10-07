// SpectrumView.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "SpectrumView.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpectrumView

extern BOOL g_bEnglish;

IMPLEMENT_DYNCREATE(CSpectrumView, CFormView)

BOOL EkCreateEmbeddedPropertySheet(	CWnd* pParent, CPropertySheet* pPSheet,
								   DWORD dwStyle = WS_CHILD | WS_VISIBLE, DWORD dwExStyle = 0 )
{
	ASSERT_VALID( pParent );
	ASSERT_VALID( pPSheet );
	
	// 1 - Create the embedded property sheet window
	if( !pPSheet->Create( pParent,  dwStyle, dwExStyle ) )
	{
		TRACE0( "Embedded property sheet creation failed\n" );
		return FALSE;
	}
	
	// 2 - Add WS_TABSTOP and WS_EX_CONTROLPARENT to the property sheet styles
	pPSheet->ModifyStyle( 0, WS_TABSTOP );
	pPSheet->ModifyStyleEx ( 0, WS_EX_CONTROLPARENT );
	
	// 3 - Add WS_EX_CONTROLPARENT to the parent window styles
	pParent->ModifyStyleEx ( 0, WS_EX_CONTROLPARENT );
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// EkPositionEmbeddedPropertySheet

void EkPositionEmbeddedPropertySheet(	CWnd* pParent, CPropertySheet* pPSheet,
									 CRect rcNewPosition )
{
	ASSERT_VALID( pParent );
	ASSERT_VALID( pPSheet );
	
	// 1 - Get current coordinates of tab control
	// and property sheet window
	CTabCtrl* pTabCtrl = pPSheet->GetTabControl();
	ASSERT( pTabCtrl != NULL );
	
	CRect rcTabCtrl;
	pTabCtrl->GetWindowRect( &rcTabCtrl );
	pParent->ScreenToClient( &rcTabCtrl );
	
	CRect rcPSheet;
	pPSheet->GetWindowRect( &rcPSheet );
	pParent->ScreenToClient( &rcPSheet );
	
	// 2 - Calculate margin between property sheet
	// and tab control
	int dcx = rcPSheet.Width() - rcTabCtrl.Width();
	int dcy = rcPSheet.Height() - rcTabCtrl.Height();
	
	// 3 - Move and resize property sheet window
	// (also moves the tab window because it is a child
	// of the property sheet window)
	pPSheet->MoveWindow( 	rcNewPosition .left, rcNewPosition.top,
		rcNewPosition .Width(), rcNewPosition.Height() );
	
	// 4 - Resize tab control window to restore
	// right / bottom margins
	pTabCtrl->SetWindowPos(	NULL,
		0, 0,
		rcNewPosition.Width() - dcx,
		rcNewPosition.Height() - dcy, 
		SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE );
	
	// 5 - Activate each property page to prevent drawing
	// problem
	int nCurrentPage = pPSheet->GetActiveIndex();
	for( int i = 0; i < pPSheet->GetPageCount(); ++i )
	{
		pPSheet->SetActivePage( i );
	}
	
	pPSheet->SetActivePage( nCurrentPage );
}


void EkPositionEmbeddedPropertySheet(	CWnd* pParent, CPropertySheet* pPSheet,
									 UINT nIDPSheetArea )
{
	ASSERT_VALID( pParent );
	ASSERT_VALID( pPSheet );
	
	// 1 - Retrieve property sheet destination position
	CRect rcNewPosition;
	CWnd* pWndNewArea = pParent->GetDlgItem( nIDPSheetArea );
	if( pWndNewArea == NULL )
	{
		ASSERT( FALSE );	// Invalid nIDPSheetArea
		return;
	}
	
	pWndNewArea->GetWindowRect( &rcNewPosition );
	pParent->ScreenToClient( &rcNewPosition );
	
	// 2 - Call overloaded function
	EkPositionEmbeddedPropertySheet( pParent, pPSheet, rcNewPosition );
}

CSpectrumView::CSpectrumView()
	: CFormView(CSpectrumView::IDD)
{
	//{{AFX_DATA_INIT(CSpectrumView)
	//}}AFX_DATA_INIT
	m_bFir = TRUE;
	m_bShowAD = TRUE;
	m_iType = 0;

	CString strSection  = "Spectrum";

	CString strType     = "Type";
	m_iType = AfxGetApp()->GetProfileInt(strSection,strType,0);
}

CSpectrumView::~CSpectrumView()
{
	CString strSection  = "Spectrum";
	
	CString strType     = "Type";

	AfxGetApp()->WriteProfileInt(strSection,strType,m_iType);
}

void CSpectrumView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpectrumView)
	DDX_Control(pDX, IDC_DATA_SHEET, m_cSheet);
	DDX_Control(pDX, IDC_STATIC_WAVE, m_cSpecDraw);
	DDX_Control(pDX, IDC_NTGRAPHCTRL, m_cNTspec);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpectrumView, CFormView)
	//{{AFX_MSG_MAP(CSpectrumView)
	ON_WM_SIZE()
//	ON_COMMAND(ID_SPEC_BMP_COPY, OnSpecBmpCopy)
//	ON_UPDATE_COMMAND_UI(ID_SPEC_BMP_COPY, OnUpdateSpecBmpCopy)
//	ON_COMMAND(ID_SHOW_AD, OnShowAd)
//	ON_UPDATE_COMMAND_UI(ID_SHOW_AD, OnUpdateShowAd)
	ON_WM_LBUTTONDOWN()
//	ON_COMMAND(ID_TYPE1, OnType1)
//	ON_UPDATE_COMMAND_UI(ID_TYPE1, OnUpdateType1)
//	ON_COMMAND(ID_TYPE2, OnType2)
//	ON_UPDATE_COMMAND_UI(ID_TYPE2, OnUpdateType2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpectrumView diagnostics

#ifdef _DEBUG
void CSpectrumView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSpectrumView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMySpecDoc* CSpectrumView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMySpecDoc)));
	return (CMySpecDoc*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSpectrumView message handlers

void CSpectrumView::SetPos()
{
	CRect clRect;
	GetClientRect(clRect);
	
	int MM = 5;
	
	CRect cieRect;
	
	cieRect.top = clRect.top+(-5);
	cieRect.bottom = clRect.bottom-(-5);
	cieRect.right = clRect.right-MM/2;
	cieRect.left = clRect.right-(int)(cieRect.Height()*0.9f);
	
	m_cSheet.MoveWindow(cieRect);
	
	CRect specRect;
	
	specRect.top = clRect.top+MM;
	specRect.bottom = clRect.bottom-MM;
	specRect.left = clRect.left+MM;
	specRect.right = cieRect.left-MM/2;
	
	if(m_bFir)
	{
		specRect.left = 0;
		specRect.right = 1300;
		specRect.top = 0;
		specRect.bottom = 1300;
	}

	m_cNTspec.MoveWindow(specRect);
	m_cSpecDraw.MoveWindow(specRect);


	if(!m_bFir)
	{
		// 内入属性页处理
		EkPositionEmbeddedPropertySheet( this, &m_cDataSheet, IDC_DATA_SHEET );
	}
}

void CSpectrumView::ReDraw()
{
	CMySpecDoc *pDoc = GetDocument();

	CString strTemp;
	float x,y;	
	int i;
	float fMax;

	m_cNTspec.ClearGraph();
	
	if(m_bShowAD)
		m_cNTspec.AddElement();

	if(g_bEnglish)
	{
		m_cNTspec.SetXLabel("Wavelength(nm)");
		m_cNTspec.SetYLabel("Spectrum");
		m_cNTspec.SetCaption("Spectrum Cruve");
	}
	else
	{
		m_cNTspec.SetXLabel("波 长(nm)");
		m_cNTspec.SetYLabel("相 对 光 谱");
		m_cNTspec.SetCaption("相 对 光 谱 曲 线");
	}
	m_cNTspec.SetXGridNumber(10);
	m_cNTspec.SetYGridNumber(6);

	m_cNTspec.SetElement(0);
	m_cNTspec.SetElementName("");
	m_cNTspec.SetElementLineColor(RGB(0,0,255));
	m_cNTspec.SetElementIdentify(TRUE);
	m_cNTspec.SetElementPointColor(RGB(0,0,255));
	m_cNTspec.SetElementPointSymbol(0);
	m_cNTspec.SetElementWidth (2);
	m_cNTspec.SetElementSolidPoint(TRUE);
	m_cNTspec.SetElementLinetype(0);

	if (pDoc->m_tempData.m_spData.m_fRelSpect.GetSize() > 0)
	{
		for (i=0;i<pDoc->m_tempData.m_spData.m_fRelSpect.GetSize();i++)
		{
			x = pDoc->m_tempData.m_spData.m_fSpect1 + i * pDoc->m_tempData.m_spData.m_fInterval;
			y = pDoc->m_tempData.m_spData.m_fRelSpect[i];
			m_cNTspec.PlotXY(x,y ,0);
		}	
		
		float fWL1 = pDoc->m_tempData.m_spData.m_fSpect1;
		float fWL2 = pDoc->m_tempData.m_spData.m_fSpect2;
		
		m_cNTspec.SetRange(fWL1,fWL2,0,1.2f);
		
		if(0)
		{	
			fMax = 0;
			for (i=0;i<pDoc->m_tempData.m_spData.m_fRelSpect.GetSize();i++)
			{
				x = pDoc->m_tempData.m_spData.m_fSpect1 + i * pDoc->m_tempData.m_spData.m_fInterval;
				y = pDoc->m_tempData.m_spData.m_fRelSpect[i];
				if(y>fMax)
					fMax = y;
			}
			if(fMax==0.0f)
				fMax = 1.0;
			
			strTemp.Format("Max AD = %.0f",fMax);
			
			m_cNTspec.SetElement(1);
			m_cNTspec.SetElementName(strTemp);
			m_cNTspec.SetElementLineColor(RGB(255,0,0));
			m_cNTspec.SetElementIdentify(TRUE);
			m_cNTspec.SetElementPointColor(RGB(0,0,255));
			m_cNTspec.SetElementPointSymbol(0);
			m_cNTspec.SetElementWidth (1);
			m_cNTspec.SetElementSolidPoint(TRUE);
			m_cNTspec.SetElementLinetype(0);
			
			for (i=0;i<pDoc->m_tempData.m_spData.m_fRelSpect.GetSize();i++)
			{
				x = pDoc->m_tempData.m_spData.m_fSpect1 + i * pDoc->m_tempData.m_spData.m_fInterval;
				y = pDoc->m_tempData.m_spData.m_fRelSpect[i];
				m_cNTspec.PlotXY(x,y/fMax,1);
			}	
		}
	}
	else
	{
		m_cNTspec.SetRange(380.0f,780.0f,0,1.2f);
	}

 	m_cDataSheet.m_pageData1.m_pSpData = pDoc->m_tempData.m_spData;
 	if(!m_bFir)
 		m_cDataSheet.m_pageData1.ReDraw();

	BOOL bHaveXY;
	float fx,fy,fCCT;
	bHaveXY = pDoc->m_tempData.m_spData.m_bHaveColorPara;
	fx   = pDoc->m_tempData.m_spData.m_x;
	fy   = pDoc->m_tempData.m_spData.m_y;
	fCCT = pDoc->m_tempData.m_spData.m_fCCT;
	
	m_cDataSheet.m_pageData2.m_bHaveData = bHaveXY;
	m_cDataSheet.m_pageData2.m_fx   = fx;
	m_cDataSheet.m_pageData2.m_fy   = fy;
	m_cDataSheet.m_pageData2.m_fCCT = fCCT;
	if(!m_bFir)
	{
		m_cDataSheet.m_pageData2.Invalidate(TRUE);
	}

	m_cDataSheet.m_pageData4.m_bHaveData = bHaveXY;
	m_cDataSheet.m_pageData4.m_fu   = pDoc->m_tempData.m_spData.m_u;
	m_cDataSheet.m_pageData4.m_fv   = pDoc->m_tempData.m_spData.m_v;
	m_cDataSheet.m_pageData4.m_fCCT = fCCT;
	if(!m_bFir)
	{
		m_cDataSheet.m_pageData4.Invalidate(TRUE);
	}
 	// 光谱曲线
 	m_cSpecDraw.DrawSpect(pDoc->m_tempData.m_spData,m_drawData,"");

}

void CSpectrumView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
	if(m_bFir)
	{
		// 内入属性页处理
		EkCreateEmbeddedPropertySheet( this, &m_cDataSheet );
	}

	m_drawData.iDrawType = 1;
	m_drawData.bShowCur = TRUE;
	m_drawData.bMouse = FALSE;

	SetPos();
	ReDraw();

	m_bFir = FALSE;

	SetPos();
	ReDraw();
}

void CSpectrumView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!m_bFir)
	{
		SetPos();
		ReDraw();	
	}
}

BEGIN_EVENTSINK_MAP(CSpectrumView, CFormView)
    //{{AFX_EVENTSINK_MAP(CSpectrumView)
	ON_EVENT(CSpectrumView, IDC_NTGRAPHCTRL, -600 /* Click */, OnClickNtgraphctrl, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CSpectrumView::OnClickNtgraphctrl() 
{
	// TODO: Add your control notification handler code here
	m_cNTspec.CopyToClipboard();	
}

void CSpectrumView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class

	if(!m_bFir)
	{
		ReDraw();
	}	
}

void CSpectrumView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CRect Rect1,Rect2;
   	if(1)
	{
		GetClientRect(&Rect1);
		ClientToScreen(&Rect1);
		m_cSpecDraw.GetClientRect(&Rect2);
		m_cSpecDraw.ClientToScreen(&Rect2);
		if(((point.y+Rect1.top)>=Rect2.top)&&((point.y+Rect1.top)<=Rect2.bottom)&&((point.x+Rect1.left)>=Rect2.left)&&((point.x+Rect1.left)<=Rect2.right))
		{
			m_drawData.pt = point; 
			m_drawData.bMouse = TRUE;
			ReDraw();
			m_drawData.bMouse = FALSE;
			ReDraw();			
		}
	}
	
	CFormView::OnLButtonDown(nFlags, point);
}
