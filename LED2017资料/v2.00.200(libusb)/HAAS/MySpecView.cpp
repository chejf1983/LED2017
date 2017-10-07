// MySpecView.cpp : implementation of the CMySpecView class
//

#include "stdafx.h"
#include "MySpec.h"

#include "MySpecDoc.h"
#include "MySpecView.h"
#include "TestInfo.h"
#include "MainFrm.h"
#include "Global_MySpec.h"

#include "DlgFluxCal.h"

#include "DlgInputPower.h"

#include "SheetOthers.h"
#include "CalFluxPLList.h"

#include "SortListCtrl.h"
#include "PowerComm.h"

#include "ExKeithley2420_GPIB_DLL.h"
#include "resource.h"
#include "ExWaitLampStableDLL.h"

#include "DaXinPowerComm.h"
#include "NPPowerMeterComm.h"


#include "DlgReGe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySpecView
extern BOOL g_bPowerMod;
extern BOOL g_bMoreGroup;
extern BOOL g_bFunDebug;

BOOL g_bUseScan;//稳态
BOOL g_bUseHLK;
BOOL g_bALL;
extern CCalFluxPLList g_CalFluxPLData;
extern BOOL g_bUseFluxPL;//使用多组系数
extern int  g_iSeleCalPLFlux;

extern float g_fSpect1;
extern float g_fSpect2;

CArray<BOOL,BOOL> g_bError;  //合格与否的标志
BOOL g_bCurErr;

COLORREF g_ErrTextColor, g_ErrBkColor;

extern CString g_strCompany;
extern CString g_strAddr;

extern int     g_iLEDClass_Type;
extern CString g_strListNewLevel;

extern int g_iOkTime;
extern int g_iOkNum;
extern int g_iFailTime;
extern int g_iFailNum;

CDaXinPowerComm g_cPower;
CNPPowerMeterComm g_cPowerMeter;

int g_iSeleTc;
int g_iSDCM1;
int g_iSDCM2;



extern BOOL __stdcall WT210_GPIB_ReadData(float &fU, float &fI, float &fP);

IMPLEMENT_DYNCREATE(CMySpecView, CListView)

BEGIN_MESSAGE_MAP(CMySpecView, CListView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CMySpecView)
	ON_NOTIFY_REFLECT( NM_CUSTOMDRAW, OnCustomdrawMyList )
	ON_MESSAGE(WM_TEST_START,OnWMTestStart)
	ON_MESSAGE(WM_UPDATE,OnWM_Update)
	ON_MESSAGE(WM_RE_HEAD,OnWMReHead)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_WM_SIZE()
	ON_COMMAND(ID_TEST_INFO, OnTestInfo)
	ON_UPDATE_COMMAND_UI(ID_TEST_INFO, OnUpdateTestInfo)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_ALL_SELE, OnAllSele)
	ON_UPDATE_COMMAND_UI(ID_ALL_SELE, OnUpdateAllSele)
	ON_COMMAND(ID_POWER, OnPower)
	ON_UPDATE_COMMAND_UI(ID_POWER, OnUpdatePower)
	ON_COMMAND(ID_MODE_INTTIME, OnModeInttime)
	ON_UPDATE_COMMAND_UI(ID_MODE_INTTIME, OnUpdateModeInttime)
	ON_MESSAGE(WM_PC2_PRO, OnWM_PC2_Pro)
	ON_COMMAND(ID_DELETE, OnDelete)
	ON_UPDATE_COMMAND_UI(ID_DELETE, OnUpdateDelete)
	ON_COMMAND(ID_EDIT_COPY_TXT_1, OnEditCopyTxt1)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY_TXT_1, OnUpdateEditCopyTxt1)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySpecView construction/destruction
HWND g_MainWnd;
extern BOOL g_bTest;
extern BOOL g_bTestCancel;
extern int  g_iTestType;

extern BOOL	g_bHavePower;
extern BOOL g_bManuP;
extern CString g_strPowCom;
extern CString g_strPowType;
//电源设置
extern int		g_iSouType;
extern CString	g_strSouComm;
extern BOOL		g_bAutoLamp;
extern int		g_iPerTime;
extern int		g_iSetType;
extern float	g_fSetVol;
extern float	g_fSetCurr;
extern float	g_fSetVol2;
extern float	g_fSetCurr2;
extern int		g_iSetType2;


extern CString g_strListWhite;
extern CString g_strListLevel;

extern BOOL g_bInsert;
BOOL g_bAllSele;

BOOL g_bHaveMode;

extern BOOL g_bHaveFluxDec;
extern BOOL g_bHaveTMPDec;
extern int  g_iTR80_or_90;


int g_iPrintG;

void EkChangePrintingOrientation( CDC* pDC, CPrintInfo* pInfo, short NewOrientation )
{
	ASSERT_VALID( pDC );
	ASSERT( pInfo != NULL );

	DEVMODE* pDevMode = pInfo->m_pPD->GetDevMode();

	// Only change if new orientation is different 
	if( pDevMode->dmOrientation != NewOrientation )
	{
		pDevMode->dmOrientation = NewOrientation;
		pDC->ResetDC( pDevMode );
	}
}

BOOL CMySpecView::m_bPC2Mode = FALSE;

CMySpecView::CMySpecView()
{
	m_iNumTMP		= 0;
	m_bFir			= TRUE;
	m_iPrintLineN	= 40;
	m_iPerInt		= 0;
	m_iPerBin		= 0;
	m_iPerCur		= 0;
	m_iPerSig		= -1;
	g_bAllSele		= TRUE;

	m_hEvents	= NULL;
	m_bSetStop	= FALSE;
}

CMySpecView::~CMySpecView()
{
}

BOOL CMySpecView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMySpecView drawing

void CMySpecView::OnDraw(CDC* pDC)
{
	CMySpecDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

void CMySpecView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CMySpecDoc *pDoc = GetDocument();

	CMainFrame *pMainFrame=(CMainFrame *)GetParentFrame();

	pMainFrame->SetDlgBarSet(0);
	pMainFrame->SetDlgBarSet(1);
	pMainFrame->SetDlgBarSet(2);

	g_MainWnd=m_hWnd;
	if(m_bFir)
	{
		// 图标
		m_SmallImageList.Create(IDB_SMALLICONS, 16, 1, RGB(255, 255, 255));
//		GetListCtrl().SetImageList(&m_SmallImageList, LVSIL_SMALL);

		// 横杠
		GetListCtrl().ModifyStyle(0,LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS);
		GetListCtrl().SetExtendedStyle(GetListCtrl().GetExtendedStyle()  | LVS_EX_FULLROWSELECT 
			| LVS_EX_GRIDLINES| LVS_EX_HEADERDRAGDROP|LVS_EX_CHECKBOXES);

		m_bFir=FALSE;
	}

	m_iCur = -1;

	m_bAllSele	 = TRUE;
	m_iPrintType = PRINT_TYPE_MAIN;

	BOOL bR;
	bR = pDoc->m_ledData.m_xyZone.WZ_Load(g_strListWhite);
	if(!bR)
	{
		g_strListWhite = g_strCurPath + "Class\\White_ANSI.WCL";

		bR = pDoc->m_ledData.m_xyZone.WZ_Load(g_strListWhite);
	}

	if(g_iLEDClass_Type == 0)
	{
		bR = pDoc->m_ledData.m_levelLimit.Open(g_strListLevel);
		if(!bR)
		{
			g_strListLevel = g_strCurPath + "Class\\LED_LEVEL_1.sta";
			bR = pDoc->m_ledData.m_levelLimit.Open(g_strListLevel);
		}
	}
	else
	{
		bR = pDoc->m_ledData.m_newClassLimit.NC_Load(g_strListNewLevel);
		if(!bR)
		{
			g_strListNewLevel = g_strCurPath + "Class\\New.NCL";
			pDoc->m_ledData.m_newClassLimit.NC_Load(g_strListNewLevel);
		}
	}

	int iN;
	iN = pDoc->m_ledData.m_listData.GetSize();
	if(iN <= 0)
	{
		SHOW_DATA();
	}
	pDoc->m_bReList = FALSE;

	pDoc->m_ledData.ListHead(GetListCtrl());
	pDoc->UpdateAllViews(NULL);

	m_pDoc = pDoc;

	static BOOL bStartTemp = TRUE;
	if(bStartTemp)
	{
		m_bPC2Mode = FALSE;
		m_bSetStop = FALSE;
		AfxBeginThread(Thread_NamePipe,this);
		
		bStartTemp = FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMySpecView printing

BOOL CMySpecView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMySpecView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CMySpecDoc *pDoc=GetDocument();
	pInfo->SetMaxPage(1);
	if(m_iPrintType == PRINT_TYPE_MAIN)
	{
		if(pDoc->m_ledData.m_listData.GetSize()<=0)
		{
			pInfo->SetMaxPage(0);
		}
		else
		{
			if(pDoc->m_ledData.m_opData.m_iReportType==0)
			{
				//找出要打印的选择组
				m_arra_iPrintSele.RemoveAll();
				for(int i=0;i<pDoc->m_ledData.m_listData.GetSize();i++)
				{
					BOOL bCheck=GetListCtrl().GetCheck(i);
					if(bCheck)
					{
						if(pDoc->m_ledData.m_listData[i]->m_spData.m_bHaveData)
						{
							m_arra_iPrintSele.Add(i);
						}
					}
				}
				//
				pInfo->SetMaxPage(m_arra_iPrintSele.GetSize());
			}
			if(pDoc->m_ledData.m_opData.m_iReportType==1)
			{
				int iN = pDoc->m_ledData.m_listData.GetSize();
				if(iN%m_iPrintLineN == 0)
				{
					pInfo->SetMaxPage(iN/m_iPrintLineN);
				}
				else
				{
					pInfo->SetMaxPage(iN/m_iPrintLineN+1);
				}
			}
		}
	}
}

void CMySpecView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	if( pInfo != NULL )
	{
		EkChangePrintingOrientation( pDC, pInfo, DMORIENT_PORTRAIT );
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMySpecView diagnostics

#ifdef _DEBUG
void CMySpecView::AssertValid() const
{
	CListView::AssertValid();
}

void CMySpecView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CMySpecDoc* CMySpecView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMySpecDoc)));
	return (CMySpecDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMySpecView message handlers

void CMySpecView::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(g_bInsert)
		return;
	//选择活动的某一个测试项目
	CMySpecDoc *pDoc=GetDocument();
	int iCur;
	iCur=pNMListView->iItem;
	m_iCur=iCur;
	if(iCur>=0&&iCur<pDoc->m_ledData.m_listData.GetSize()&&m_iPerCur!=iCur)
	{
		pDoc->Calc_B_Active(iCur);
		::PostMessage(g_MainWnd,WM_UPDATE,0,0);
	}
	m_iPerCur = iCur;
	*pResult  = 0;
}

void CMySpecView::OnWM_Update(UINT wParam, LONG lParam)
{
	CMySpecDoc *pDoc=GetDocument();
	int iCur=pDoc->m_nActive+pDoc->m_iB;
	m_iCur=iCur;
	if(m_iCur>=0&&m_iCur<pDoc->m_ledData.m_listData.GetSize())//&&m_iPerShow!=iCur)
	{
		pDoc->m_tempData=*pDoc->m_ledData.m_listData[m_iCur];
	}
	m_iPerCur = iCur;
	pDoc->UpdateAllViews(NULL);
}

void CMySpecView::OnWMReHead(UINT wParam, LONG lParam)
{
	CMySpecDoc *pDoc=GetDocument();
	pDoc->m_ledData.ListHead(GetListCtrl());
}

void CMySpecView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CMySpecDoc *pDoc=GetDocument();
	if(pDoc->m_bReList)
	{
		pDoc->m_ledData.ListHead(GetListCtrl());
		pDoc->m_bReList=FALSE;
	}
	SHOW_DATA();
}

void CMySpecView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	CMySpecDoc *pDoc=GetDocument();
	if(m_iPrintType==PRINT_TYPE_MAIN)
	{
		if(pDoc->m_ledData.m_listData.GetSize()<=0)
		{
		}
		else
		{
			if(pDoc->m_ledData.m_opData.m_iReportType==0)
			{
				int iSele=pInfo->m_nCurPage-1;
				if(iSele>=0&&iSele<m_arra_iPrintSele.GetSize())
				{
					CRect rect=pInfo->m_rectDraw;
					CRect printRect;
					if(g_iPrintG==0)
						printRect=CRect(0,0,rect.Width(),rect.Height());
					else
						printRect=CRect(rect.Width()/12,rect.Height()/12,rect.Width()/12*11,rect.Height()/12*10);

					//////METAFILE//////
					CMetaFileDC *m_pMetaDC=new CMetaFileDC();
					CString strWMF;
					strWMF.Format("REPORT%d.WMF",pInfo->m_nCurPage);
					strWMF=g_strCurPath+"REPORT\\"+strWMF;
					m_pMetaDC->CreateEnhanced(GetDC(),NULL,NULL,"whaterver");
					m_pMetaDC->SetAttribDC(GetDC()->m_hAttribDC);
					CPen  *pOldPen;
					CPen  Pen1;
					Pen1.CreatePen(PS_SOLID,1,RGB(255,255,255));
					pOldPen=m_pMetaDC->SelectObject(&Pen1);
					m_pMetaDC->Rectangle(rect);
					m_pMetaDC->SelectObject(pOldPen);
					//////METAFILE//////
					COLORREF color;
					CString strLevel=pDoc->m_ledData.GetLevel(m_arra_iPrintSele[iSele], color);
					CString strWhite=pDoc->m_ledData.GetWhite(m_arra_iPrintSele[iSele]);
					if(!pDoc->m_ledData.m_opData.m_bLevel)
					{
						strLevel = "";
					}
					if(!pDoc->m_ledData.m_opData.m_bWhite)
					{
						strWhite = "";
					}
					if(g_iPrintG==0)
					{
						
						pDoc->m_ledData.m_listData[m_arra_iPrintSele[iSele]]->m_spData.printReport_2(pDC,printRect,pDoc->m_ledData.m_opData.m_iShowCIE,pDoc->m_ledData.m_opData.m_iSeleTc,pDoc->m_ledData.m_opData.m_iSDCM1,pDoc->m_ledData.m_opData.m_iSDCM2,pDoc->m_ledData.m_iPhType,pDoc->m_ledData.m_xyZone,strLevel,strWhite,pDoc->m_ledData.m_opData.m_bPrintLogo,pDoc->m_ledData.m_opData.m_iPrintLogoPos);
						pDoc->m_ledData.m_listData[m_arra_iPrintSele[iSele]]->m_spData.printReport_2(m_pMetaDC,printRect,pDoc->m_ledData.m_opData.m_iShowCIE,pDoc->m_ledData.m_opData.m_iSeleTc,pDoc->m_ledData.m_opData.m_iSDCM1,pDoc->m_ledData.m_opData.m_iSDCM2,pDoc->m_ledData.m_iPhType,pDoc->m_ledData.m_xyZone,strLevel,strWhite,pDoc->m_ledData.m_opData.m_bPrintLogo,pDoc->m_ledData.m_opData.m_iPrintLogoPos);
					}
					else
					{
						pDoc->m_ledData.m_listData[m_arra_iPrintSele[iSele]]->m_spData.printHead(pDC,printRect,pInfo->m_nCurPage,pInfo->GetMaxPage(),pDoc->m_ledData.m_opData.m_bPrintLogo,pDoc->m_ledData.m_opData.m_iPrintLogoPos,pDoc->m_ledData.m_opData.m_bPrintPage);
						pDoc->m_ledData.m_listData[m_arra_iPrintSele[iSele]]->m_spData.printHead(m_pMetaDC,printRect,pInfo->m_nCurPage,pInfo->GetMaxPage(),pDoc->m_ledData.m_opData.m_bPrintLogo,pDoc->m_ledData.m_opData.m_iPrintLogoPos,pDoc->m_ledData.m_opData.m_bPrintPage);
						
						pDoc->m_ledData.m_listData[m_arra_iPrintSele[iSele]]->m_spData.printReport(pDC,printRect,
							pDoc->m_ledData.m_opData.m_iShowCIE,pDoc->m_ledData.m_opData.m_iSeleTc,
							pDoc->m_ledData.m_opData.m_iSDCM1,pDoc->m_ledData.m_opData.m_iSDCM2,
							pDoc->m_ledData.m_iPhType,pDoc->m_ledData.m_xyZone,strLevel,strWhite);
						pDoc->m_ledData.m_listData[m_arra_iPrintSele[iSele]]->m_spData.printReport(m_pMetaDC,printRect,pDoc->m_ledData.m_opData.m_iShowCIE,pDoc->m_ledData.m_opData.m_iSeleTc,pDoc->m_ledData.m_opData.m_iSDCM1,pDoc->m_ledData.m_opData.m_iSDCM2,pDoc->m_ledData.m_iPhType,pDoc->m_ledData.m_xyZone,strLevel,strWhite);
						
						pDoc->m_ledData.m_listData[m_arra_iPrintSele[iSele]]->m_spData.printFoot(pDC,printRect,pInfo->m_nCurPage,pInfo->GetMaxPage());
						pDoc->m_ledData.m_listData[m_arra_iPrintSele[iSele]]->m_spData.printFoot(m_pMetaDC,printRect,pInfo->m_nCurPage,pInfo->GetMaxPage());

					}

					//////METAFILE//////
					HENHMETAFILE hMF=m_pMetaDC->CloseEnhanced();
					OpenClipboard();
					EmptyClipboard();
					::SetClipboardData(CF_ENHMETAFILE,hMF);
					CloseClipboard();
					delete m_pMetaDC;
					//////METAFILE//////
				}
			}
			if(pDoc->m_ledData.m_opData.m_iReportType==1)
			{
				CRect rect=pInfo->m_rectDraw;
				CRect printRect(rect.Width()/22,rect.Height()/12,rect.Width()/22*21,rect.Height()/12*11);

				//////METAFILE//////
				CMetaFileDC *m_pMetaDC=new CMetaFileDC();
				CString strWMF;
				strWMF.Format("REPORT%d.WMF",pInfo->m_nCurPage);
				strWMF=g_strCurPath+"REPORT\\"+strWMF;
				m_pMetaDC->CreateEnhanced(GetDC(),NULL,NULL,"whaterver");
				m_pMetaDC->SetAttribDC(GetDC()->m_hAttribDC);
				CPen  *pOldPen;
				CPen  Pen1;
				Pen1.CreatePen(PS_SOLID,1,RGB(255,255,255));
				pOldPen=m_pMetaDC->SelectObject(&Pen1);
				m_pMetaDC->Rectangle(rect);
				m_pMetaDC->SelectObject(pOldPen);
				//////METAFILE//////
				pDoc->m_ledData.printListTable(pDC,printRect,pInfo->m_nCurPage,pInfo->GetMaxPage(),0,pDoc->GetPathName(),m_iPrintLineN);
				pDoc->m_ledData.printListTable(m_pMetaDC,printRect,pInfo->m_nCurPage,pInfo->GetMaxPage(),0,pDoc->GetPathName(),m_iPrintLineN);

				//////METAFILE//////
				HENHMETAFILE hMF=m_pMetaDC->CloseEnhanced();
				OpenClipboard();
				EmptyClipboard();
				::SetClipboardData(CF_ENHMETAFILE,hMF);
				CloseClipboard();
				delete m_pMetaDC;
				//////METAFILE//////
			}
		}
	}
// 
// 	//单独的光谱对话框中的打印(一个小技巧)
// 	if(m_iPrintType==PRINT_TYPE_SPECT) //稳态测试打印
// 	{
// 		CRect rect=pInfo->m_rectDraw;
// 		CRect printRect(rect.Width()/12,rect.Height()/12,rect.Width()/12*11,rect.Height()/12*10);
// 
// 		if(m_dUSBScan.m_spData.m_bHaveData)
// 		{
// 			//////METAFILE//////
// 			CMetaFileDC *m_pMetaDC=new CMetaFileDC();
// 			CString strWMF;
// 			strWMF.Format("REPORT%d.WMF",pInfo->m_nCurPage);
// 			strWMF=g_strCurPath+"REPORT\\"+strWMF;
// 			m_pMetaDC->CreateEnhanced(GetDC(),NULL,NULL,"whaterver");
// 			m_pMetaDC->SetAttribDC(GetDC()->m_hAttribDC);
// 			CPen  *pOldPen;
// 			CPen  Pen1;
// 			Pen1.CreatePen(PS_SOLID,1,RGB(255,255,255));
// 			pOldPen=m_pMetaDC->SelectObject(&Pen1);
// 			m_pMetaDC->Rectangle(rect);
// 			m_pMetaDC->SelectObject(pOldPen);
// 			//////METAFILE//////
// 
// 			m_dUSBScan.m_spData.printHead(pDC,printRect,pInfo->m_nCurPage,pInfo->GetMaxPage(),pDoc->m_ledData.m_opData.m_bPrintLogo,pDoc->m_ledData.m_opData.m_iPrintLogoPos,pDoc->m_ledData.m_opData.m_bPrintPage);
// 			m_dUSBScan.m_spData.printHead((CDC *)m_pMetaDC,printRect,pInfo->m_nCurPage,pInfo->GetMaxPage(),pDoc->m_ledData.m_opData.m_bPrintLogo,pDoc->m_ledData.m_opData.m_iPrintLogoPos,pDoc->m_ledData.m_opData.m_bPrintPage);
// 
// 			CString strLevel="";
// 			CString strWhite="";
// 			m_dUSBScan.m_spData.printReport(pDC,printRect,m_dUSBScan.m_iTypeP,m_dUSBScan.m_iSeleK,m_dUSBScan.m_iSDCM1,m_dUSBScan.m_iSDCM2,0,pDoc->m_ledData.m_xyZone,strLevel,strWhite);
// 			m_dUSBScan.m_spData.printReport((CDC *)m_pMetaDC,printRect,m_dUSBScan.m_iTypeP,m_dUSBScan.m_iSeleK,m_dUSBScan.m_iSDCM1,m_dUSBScan.m_iSDCM2,0,pDoc->m_ledData.m_xyZone,strLevel,strWhite);
// 
// 			m_dUSBScan.m_spData.printFoot(pDC,printRect,pInfo->m_nCurPage,pInfo->GetMaxPage());
// 			m_dUSBScan.m_spData.printFoot((CDC *)m_pMetaDC,printRect,pInfo->m_nCurPage,pInfo->GetMaxPage());
// 
// 			//////METAFILE//////
// 			HENHMETAFILE hMF=m_pMetaDC->CloseEnhanced();
// 			OpenClipboard();
// 			EmptyClipboard();
// 			::SetClipboardData(CF_ENHMETAFILE,hMF);
// 			CloseClipboard();
// 			delete m_pMetaDC;
// 			//////METAFILE//////
// 		}
// 	}
// 	if(m_iPrintType==PRINT_TYPE_TR) //反射率测试打印
// 	{
// 		CRect rect=pInfo->m_rectDraw;
// 		CRect printRect(rect.Width()/12,rect.Height()/12,rect.Width()/12*11,rect.Height()/12*10);
// 
// 		if(m_dScanTR.m_spData.m_bHaveData)
// 		{
// 			//////METAFILE//////
// 			CMetaFileDC *m_pMetaDC=new CMetaFileDC();
// 			CString strWMF;
// 			strWMF.Format("REPORT%d.WMF",pInfo->m_nCurPage);
// 			strWMF=g_strCurPath+"REPORT\\"+strWMF;
// 			m_pMetaDC->CreateEnhanced(GetDC(),NULL,NULL,"whaterver");
// 			m_pMetaDC->SetAttribDC(GetDC()->m_hAttribDC);
// 			CPen  *pOldPen;
// 			CPen  Pen1;
// 			Pen1.CreatePen(PS_SOLID,1,RGB(255,255,255));
// 			pOldPen=m_pMetaDC->SelectObject(&Pen1);
// 			m_pMetaDC->Rectangle(rect);
// 			m_pMetaDC->SelectObject(pOldPen);
// 			//////METAFILE//////
// 
// 			m_dScanTR.m_spData.printHead(pDC,printRect,pInfo->m_nCurPage,pInfo->GetMaxPage(),
// 				pDoc->m_ledData.m_opData.m_bPrintLogo,pDoc->m_ledData.m_opData.m_iPrintLogoPos,
// 				pDoc->m_ledData.m_opData.m_bPrintPage);
// 			m_dScanTR.m_spData.printHead((CDC *)m_pMetaDC,printRect,pInfo->m_nCurPage,pInfo->GetMaxPage(),
// 				pDoc->m_ledData.m_opData.m_bPrintLogo,pDoc->m_ledData.m_opData.m_iPrintLogoPos,
// 				pDoc->m_ledData.m_opData.m_bPrintPage);
// 
// 			m_dScanTR.m_spData.printReport(pDC,printRect);
// 			m_dScanTR.m_spData.printReport((CDC *)m_pMetaDC,printRect);
// 
// 			m_dScanTR.m_spData.printFoot(pDC,printRect,pInfo->m_nCurPage,pInfo->GetMaxPage());
// 			m_dScanTR.m_spData.printFoot((CDC *)m_pMetaDC,printRect,pInfo->m_nCurPage,pInfo->GetMaxPage());
// 
// 			//////METAFILE//////
// 			HENHMETAFILE hMF=m_pMetaDC->CloseEnhanced();
// 			OpenClipboard();
// 			EmptyClipboard();
// 			::SetClipboardData(CF_ENHMETAFILE,hMF);
// 			CloseClipboard();
// 			delete m_pMetaDC;
// 			//////METAFILE//////
// 		}
// 	}

	CListView::OnPrint(pDC, pInfo);
}

void CMySpecView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	if( pInfo != NULL )
	{
		// Find out the orientation we want: every third page
		// will print in "landscape" mode
		CMySpecDoc *pDoc=GetDocument();
		if(m_iPrintType==PRINT_TYPE_MAIN)
		{
			if(pDoc->m_ledData.m_opData.m_iReportType==0)
			{
				EkChangePrintingOrientation( pDC, pInfo, DMORIENT_PORTRAIT );
			}
			if(pDoc->m_ledData.m_opData.m_iReportType==1)
			{
				if(pDoc->m_ledData.m_listData.GetSize()>0)
				{
					if(!pDoc->m_ledData.m_listData[0]->m_spData.m_bHaveData)
					{
						m_iPrintLineN=50;
						EkChangePrintingOrientation( pDC, pInfo, DMORIENT_PORTRAIT );
					}
					else
					{
						m_iPrintLineN=40;
						EkChangePrintingOrientation( pDC, pInfo, DMORIENT_LANDSCAPE );
					}
				}
			}
		}
		if(m_iPrintType==PRINT_TYPE_CURVE)
		{
			EkChangePrintingOrientation( pDC, pInfo, DMORIENT_PORTRAIT );
		}
	}

	CListView::OnPrepareDC(pDC, pInfo);
}

void CMySpecView::OnSize(UINT nType, int cx, int cy) 
{
	CListView::OnSize(nType, cx, cy);
}

void CMySpecView::OnTestInfo() 
{
	// TODO: Add your command handler code here
	CMySpecDoc *pDoc=GetDocument();

	if(1)
	{
		int iCur=pDoc->m_nActive+pDoc->m_iB;
		if(iCur>=0&&iCur<pDoc->m_ledData.m_listData.GetSize())
		{
			CTestInfo dlg;

			dlg.m_strModel   = pDoc->m_ledData.m_listData[iCur]->m_spData.m_strModel;
			dlg.m_strNumber  = pDoc->m_ledData.m_listData[iCur]->m_spData.m_strNumber;
			dlg.m_strFactory = pDoc->m_ledData.m_listData[iCur]->m_spData.m_strFactory;
			dlg.m_strT       = pDoc->m_ledData.m_listData[iCur]->m_spData.m_strT;
			dlg.m_strH       = pDoc->m_ledData.m_listData[iCur]->m_spData.m_strH;
			dlg.m_strTester  = pDoc->m_ledData.m_listData[iCur]->m_spData.m_strTester;
			dlg.m_strDate    = pDoc->m_ledData.m_listData[iCur]->m_spData.m_strDate;
			dlg.m_strRemark  = pDoc->m_ledData.m_listData[iCur]->m_spData.m_strRemark;

			dlg.m_strName  = pDoc->m_ledData.m_listData[iCur]->m_spData.m_strSampleName;
			dlg.m_strState  = pDoc->m_ledData.m_listData[iCur]->m_spData.m_strSampleState;
			dlg.m_strStandard  = pDoc->m_ledData.m_listData[iCur]->m_spData.m_strSampleStandard;

			if(dlg.DoModal()==IDOK)
			{
				pDoc->m_ledData.m_listData[iCur]->m_spData.m_strModel   = dlg.m_strModel;
				pDoc->m_ledData.m_listData[iCur]->m_spData.m_strNumber  = dlg.m_strNumber;
				pDoc->m_ledData.m_listData[iCur]->m_spData.m_strFactory = dlg.m_strFactory;
				pDoc->m_ledData.m_listData[iCur]->m_spData.m_strT       = dlg.m_strT;
				pDoc->m_ledData.m_listData[iCur]->m_spData.m_strH       = dlg.m_strH;
				pDoc->m_ledData.m_listData[iCur]->m_spData.m_strTester  = dlg.m_strTester;
				pDoc->m_ledData.m_listData[iCur]->m_spData.m_strDate    = dlg.m_strDate;
				pDoc->m_ledData.m_listData[iCur]->m_spData.m_strRemark  = dlg.m_strRemark;

				pDoc->m_ledData.m_listData[iCur]->m_spData.m_strSampleName = dlg.m_strName;
				pDoc->m_ledData.m_listData[iCur]->m_spData.m_strSampleState = dlg.m_strState;
				pDoc->m_ledData.m_listData[iCur]->m_spData.m_strSampleStandard = dlg.m_strStandard;

				pDoc->m_ledData.m_listData[iCur]->m_spData.WR_Info();

				pDoc->m_ledData.m_listData[iCur]->m_spData.m_fEnTMP	= (float)(atof)(dlg.m_strT);
				pDoc->m_tempData.m_spData.m_fEnTMP = (float)(atof)(dlg.m_strT);

				pDoc->m_strNumber = dlg.m_strNumber;

				SHOW_DATA();

				//修改列表中的数据
				if(pDoc->m_ledData.m_opData.m_bNote)
				{
					CListCtrl &cList=GetListCtrl();
					cList.SetItemText(iCur,1,dlg.m_strNumber);
				}
				pDoc->SetModifiedFlag(TRUE);
			}
		}
	}
}

void CMySpecView::OnUpdateTestInfo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMySpecDoc *pDoc=GetDocument();
	int iCur=pDoc->m_nActive+pDoc->m_iB;
	m_iCur=iCur;
	if(iCur>=0&&iCur<pDoc->m_ledData.m_listData.GetSize())
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CMySpecView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnTestInfo();
	*pResult = 0;
}

void CMySpecView::SHOW_DATA()
{
	CMySpecDoc *pDoc=GetDocument();
	CMainFrame *pMainFrame=(CMainFrame *)GetParentFrame();

	if(g_bTest&&pDoc->m_bSet_AutoTime)
		pMainFrame->SetDlgBarSet(0);

	pMainFrame->SetTreeParameter(m_iCur,pMainFrame->m_wndTree,pDoc->m_tempData,pDoc->m_ledData.m_iPhType);
}

UINT ThreadTrig(LPVOID pParam)
{
	CMySpecView* pView=(CMySpecView*)pParam;

	if (g_iSouType==3)
	{
		Sleep(100);
		BOOL bR;
		bR=CPowerComm::KTY_Out_On(g_strSouComm,pView->m_fVf,pView->m_fIf);
		if(!bR)
		{
			return 0;
		}
	}
	
	return 0;
}

UINT ThreadTest(LPVOID pParam)
{
	CMySpecView* pView=(CMySpecView*)pParam;
	BOOL bR;
	CString strTemp;

	CMySpecDoc *pDoc = pView->m_pDoc;
	g_bTest			= TRUE;
	g_bTestCancel	= FALSE;

	int iNum		= g_SPEC.m_arra_iTimeNum.GetSize();
	int iTempNum	= 0;
	int iTempTime	= 0;
	pView->SetTimer(2, 10, NULL);
	while(1)
	{
		if(g_iTestType == 0 && g_SPEC.m_bTimeTest)
		{
			if(iTempNum >= iNum)
			{
				break;
			}
		}

		if(g_iTestType == 0 && g_SPEC.m_bTimeTest)
		{
			if(g_bEnglish)
				strTemp.Format("TimeTest Number:%d...",iTempNum+1);
			else
				strTemp.Format("正在进行定时测试 第%d次...",iTempNum+1);
			CMainFrame::ShowNote(strTemp);

			if(iTempNum == 0)
				iTempTime = g_SPEC.m_arra_iTimeNum[0];
			else
				iTempTime = g_SPEC.m_arra_iTimeNum[iTempNum] - g_SPEC.m_arra_iTimeNum[iTempNum-1];

			int iT1,iT2;
			iT1 = GetCurrentTime();
			CString sStr;
			pDoc->m_bTemp_PreheatTimeMode = TRUE;
			while(1)
			{
				if(g_bTestCancel == TRUE)
					break;

				Sleep(100);
				iT2 = GetCurrentTime();
				if((iT2 - iT1) >= (iTempTime * 60 * 1000))
					break;
				
				sStr.Format("%.1fs", (float)((iT2 - iT1) / 1000.0f));
				CMainFrame::ShowNote(strTemp + sStr);
			}

		}

		if(g_bTestCancel == TRUE)
		{
			if(1)
			{
				if(g_bEnglish)
					CMainFrame::ShowNote("Cancel!");
				else
					CMainFrame::ShowNote("取消测试!");	
			}
			pDoc->m_bTemp_PreheatTimeMode = FALSE;
			g_bTestCancel = FALSE;
			break;
		}

		pDoc->m_bTemp_PreheatTimeMode = FALSE;
		g_bTestCancel = FALSE;

		if(g_iTestType==0&&g_SPEC.m_bTimeTest)
		{
			iTempNum++;
		}
		
		pView->m_iTestResult = 0;

		bR=pView->Test();
		if(!bR)
		{
			/* 失败完成 */
			if(pView->m_iTestResult == 0)
				pView->m_iTestResult = 1;
			pView->m_EventTest.SetEvent();

			break;
		}

		/* 成功完成 */
		pView->m_iTestResult = 0;
		pView->m_EventTest.SetEvent();

		Sleep(10);

		if(g_bEnglish)
		{
			CMainFrame::ShowNote("Complete!");
		}
		else
		{
			CMainFrame::ShowNote("完成!");
		}

		if(g_iTestType == 0 && !g_SPEC.m_bTimeTest)
		{
			break;
		}

		if(g_bTestCancel)
		{
			if(g_bEnglish)
			{
				CMainFrame::ShowNote("Cancel!");
			}
			else
			{
				CMainFrame::ShowNote("取消测试!");
			}

			break;
		}
	}
	g_bTestCancel	= FALSE;
	g_bTest			= FALSE;
	pView->SetTimer(2, 10, NULL);
	return 0;
}

void CMySpecView::OnWMTestStart(UINT wParam, LONG lParam)
{
	CMySpecDoc *pDoc=GetDocument();

	// 开副线程
	AfxBeginThread(ThreadTest,this);
}

BOOL CMySpecView::Test()
{
	CMySpecDoc *pDoc=GetDocument();

	BOOL bR;
	CString strTemp;
	bR=g_SPEC.Get_PL();
	if(!bR)
		return FALSE;

	if(pDoc->m_ledData.m_listData.GetSize()>=50000)
	{
		g_bTestCancel=TRUE;
		if(!m_bPC2Mode)
		{
			if(g_bEnglish)
				AfxMessageBox("The Data has more than 10000,please new a file!");
			else
				AfxMessageBox("数据过多，请保存数据后新建文档，重新测量!");
		}
		return FALSE;
/*		CTime tNow;
		tNow=CTime::GetCurrentTime();
		//创建文件夹
		CString sTemp;
		sTemp=g_strCurPath+"\\Files\\";
		CreateDirectory(sTemp,NULL);
		SHChangeNotify(SHCNE_MKDIR,SHCNF_PATH,sTemp,0);

		CString sNow=tNow.Format("%Y-%m-%d-%H-%M-");

		CString sStr;
		sStr.Format(".gcs");
		sTemp=sTemp+sNow+sStr;
		pDoc->OnSaveDocument(sTemp);//自动保存

		pDoc->m_ledData.New();
		pDoc->m_ledData.ListHead(GetListCtrl());
*/	}

	CLED300Data *temp=new CLED300Data();

	if(g_bAutoLamp)
	{
		int iCOM = 1;
		sscanf(g_strSouComm, "COM%d", &iCOM);
		g_cPower.DX_Power_Init(iCOM);

		bR = g_cPower.DX_Power_Output(FALSE);
		if (!bR)
		{
			AfxMessageBox("FAIL!");
		}
		Sleep(1000);
		if(pDoc->m_fSet_IntTime<g_SPEC.m_fIntTime1||pDoc->m_fSet_IntTime>g_SPEC.m_fIntTime2)
		{
			CString sTemp;
			if(g_bEnglish)
				sTemp.Format("Integral time error,between %.0fms to %.0fms",g_SPEC.m_fIntTime1,g_SPEC.m_fIntTime2);
			else
				sTemp.Format("积分时间设置错误,应在%.0fms-%.0fms间",g_SPEC.m_fIntTime1,g_SPEC.m_fIntTime2);
			if(!m_bPC2Mode)
				AfxMessageBox(sTemp);
			EnableShow(FALSE);
			return FALSE;
		}
		if(pDoc->m_iSet_AvgN<=0||pDoc->m_iSet_AvgN>50)
		{
			CString sTemp;
			if(g_bEnglish)
				sTemp.Format("Average number error,between %d to %d",1,50);
			else
				sTemp.Format("平均次数设置错误,应在%d-%d间",1,50);
			if(!m_bPC2Mode)
				AfxMessageBox(sTemp);
			EnableShow(FALSE);
			return FALSE;
		}
		
		if(m_iPerInt!=(int)(pDoc->m_fSet_IntTime) || ((m_iPerBin!=g_SPEC.m_iBin)&&(!g_SPEC.m_bTrig)) || g_SPEC.m_iSigType != m_iPerSig)
		{
			if(g_bEnglish)
				strTemp.Format("Scan Get Dark[%.0fms]...",pDoc->m_fSet_IntTime);
			else
				strTemp.Format("正在采样系统暗电流[%.0fms]...",pDoc->m_fSet_IntTime);
			CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,0));
			bR=g_SPEC.SPEC_GetDark(pDoc->m_fSet_IntTime,pDoc->m_iSet_AvgN);
			if(!bR)
			{
				if(g_bEnglish)
					strTemp.Format("Fail[Spectrum]!");
				else
					strTemp.Format("控制光谱仪失败!");
				CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,0));
				g_SPEC.MyBeep(750);
				Sleep(1000);
				EnableShow(FALSE);
				return FALSE;
			}
			Sleep(200);
		}

		//正在点灯
		if(g_bEnglish)
			strTemp.Format("Lamp On...");
		else
			strTemp.Format("开灯,请等待...");
		CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,255));

		if(1)
		{
			bR = g_cPower.DX_Power_SetPara(g_fSetVol,g_fSetCurr*1000);
			if(!bR)
			{
				if(g_bEnglish)
					strTemp.Format("Lamp On fail...");
				else
					strTemp.Format("开灯失败,请检查电源设置...");
				CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,0));
				return FALSE;
			}
			bR=g_cPower.DX_Power_Output(TRUE);
			if(!bR)
			{
				if(g_bEnglish)
					strTemp.Format("Lamp On fail...");
				else
					strTemp.Format("开灯失败,请检查电源设置...");
				CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,0));
				return FALSE;
			}
		}
		//正在预热
		if(g_bEnglish)
			strTemp.Format("Waiting(%dms)...",g_iPerTime);
		else
			strTemp.Format("正在预热(%dms),请等待...",g_iPerTime);
		CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,255));
		int iT1,iT2;
		iT1=GetCurrentTime();
		pDoc->m_bTemp_PreheatTimeMode = TRUE;
		g_bTestCancel = FALSE;
		while(1)
		{
			if(g_bTestCancel == TRUE)
				break;

			Sleep(1);
			iT2=GetCurrentTime();
			if(iT2-iT1>g_iPerTime)
				break;
		}
		if(g_bTestCancel == TRUE)
		{
			if(g_bEnglish)
				strTemp.Format("Cancel preheat.");
			else
				strTemp.Format("取消预热.");
			CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,255));

			pDoc->m_bTemp_PreheatTimeMode = FALSE;
			g_bTestCancel = FALSE;
			return FALSE;
		}

		pDoc->m_bTemp_PreheatTimeMode = FALSE;
		g_bTestCancel = FALSE;
	}

	int iType=g_SPEC.m_iTestType;
	if(g_bMoreGroup&&g_iSeleCalFlux>=0)
	{
		int iN;
		iN=g_calFluxData.m_calData.GetSize();
		if(g_iSeleCalFlux>(iN-1))
			g_iSeleCalFlux=iN-1;
		g_SPEC.m_CAL_fFluxK[iType] = g_calFluxData.m_calData.GetAt(g_iSeleCalFlux)->m_fK;
	}

	EnableShow(TRUE);
	if(pDoc->m_bSet_AutoTime&&!g_SPEC.m_bTrig /*&&!g_bAutoLamp*/)
	{
		//Auto
		if(g_bEnglish)
			strTemp.Format("Auto Time...");
		else
			strTemp.Format("自动积分...");
		CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,255));

		float fIntTime;
		int iLimitTime=g_SPEC.m_iAutoLimitTime2;
		float fLK=0.8f;
		//对于STC4000的不同点
		fLK=0.6f;

		bR=g_SPEC.SPEC_GetAutoTime(fIntTime,iLimitTime,fLK,pDoc->m_fSet_IntTime);  //0.2f;
		if(!bR)
		{
			EnableShow(FALSE);
			if(g_bEnglish)
			{
				strTemp.Format("Fail[Spectrum]!");
			}
			else
			{
				strTemp.Format("自动积分失败!");
			}
			CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,0));
			return FALSE;
		}

		if(fIntTime<g_SPEC.m_fIntTime1)
		{
			fIntTime=g_SPEC.m_fIntTime1;
			if(g_bEnglish)
			{
				if(!m_bPC2Mode)
					AfxMessageBox("Single is too strong!");
			}
			else
			{
				if(!m_bPC2Mode)
					AfxMessageBox("信号太强！");
			}
		}
		if(fIntTime >= iLimitTime)
		{
			fIntTime = iLimitTime*1.0f;
		}

		pDoc->m_fSet_IntTime = fIntTime;
	}

	if(!g_bAutoLamp)
	{
		if(pDoc->m_fSet_IntTime < g_SPEC.m_fIntTime1 || pDoc->m_fSet_IntTime > g_SPEC.m_fIntTime2)
		{
			CString sTemp;
			if(g_bEnglish)
			{
				sTemp.Format("Integral time error,between %.0fms to %.0fms",g_SPEC.m_fIntTime1,g_SPEC.m_fIntTime2);
			}
			else
			{
				sTemp.Format("积分时间设置错误,应在%.0fms-%.0fms间",g_SPEC.m_fIntTime1,g_SPEC.m_fIntTime2);
			}
			if(!m_bPC2Mode)
				AfxMessageBox(sTemp);
			EnableShow(FALSE);
			return FALSE;
		}
		if(pDoc->m_iSet_AvgN<=0||pDoc->m_iSet_AvgN>50)
		{
			CString sTemp;
			if(g_bEnglish)
				sTemp.Format("Average number error,between %d to %d",1,50);
			else
				sTemp.Format("平均次数设置错误,应在%d-%d间",1,50);
			if(!m_bPC2Mode)
				AfxMessageBox(sTemp);
			EnableShow(FALSE);
			return FALSE;
		}
		
		if(0)//m_iPerInt!=(int)(pDoc->m_fSet_IntTime) || ((m_iPerBin!=g_SPEC.m_iBin)&&(!g_SPEC.m_bTrig)) || g_SPEC.m_iSigType != m_iPerSig)
		{
			if(g_bEnglish)
				strTemp.Format("Scan Get Dark[%.0fms]...",pDoc->m_fSet_IntTime);
			else
				strTemp.Format("正在采样系统暗电流[%.0fms]...",pDoc->m_fSet_IntTime);
			CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,0));
			bR=g_SPEC.SPEC_GetDark(pDoc->m_fSet_IntTime,pDoc->m_iSet_AvgN);
			if(!bR)
			{
				if(g_bEnglish)
					strTemp.Format("Fail[Spectrum]!");
				else
					strTemp.Format("控制光谱仪失败!");
				CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,0));
				g_SPEC.MyBeep(750);
				Sleep(1000);
				EnableShow(FALSE);
				return FALSE;
			}
			Sleep(200);
		}
	}

	//前一次的积分时间和灵敏度
	m_iPerInt = (int)(pDoc->m_fSet_IntTime);
	m_iPerBin = g_SPEC.m_iBin;
	m_iPerSig = g_SPEC.m_iSigType;

	temp->m_spData.RD_Info();
	temp->m_spData.m_iLamp		= g_SPEC.m_iLamp;
	temp->m_spData.m_fDistance	= g_SPEC.m_fDistance;
	//光谱测试
	float fMax;
	if(g_SPEC.m_bTrig&&g_SPEC.m_iTrigMode==0)  //输入触发模式
	{
		if(g_bEnglish)
			strTemp.Format("Waiting trigger signal...",pDoc->m_fSet_IntTime);
		else
			strTemp.Format("等待触发信号...",pDoc->m_fSet_IntTime);

		//开灯并发触发
		AfxBeginThread(ThreadTrig,this);
	}
	else
	{
		if(g_bEnglish)
			strTemp.Format("Scan Spectrum[%.0fms]...",pDoc->m_fSet_IntTime);
		else
			strTemp.Format("正在光谱扫描[%.0fms]...",pDoc->m_fSet_IntTime);
	}
	CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,0));
	if(g_SPEC.m_bTrig)
	{
		if(g_SPEC.m_iTrigMode==0)
		{
			if(pDoc->m_bSet_AutoTime)
				bR=g_SPEC.SPEC_DoScan(pDoc->m_fSet_IntTime,pDoc->m_iSet_AvgN,MY_TRIG_HARD_IN,fMax,FALSE,TYPE_SCAN);
			else
				bR=g_SPEC.SPEC_DoScan(pDoc->m_fSet_IntTime,pDoc->m_iSet_AvgN,MY_TRIG_HARD_IN,fMax,FALSE,TYPE_SCAN);
		}
		else
		{
			if(pDoc->m_bSet_AutoTime)
				bR=g_SPEC.SPEC_DoScan(pDoc->m_fSet_IntTime,pDoc->m_iSet_AvgN,MY_TRIG_HARD_OUT,fMax,FALSE,TYPE_SCAN);
			else
				bR=g_SPEC.SPEC_DoScan(pDoc->m_fSet_IntTime,pDoc->m_iSet_AvgN,MY_TRIG_HARD_OUT,fMax,FALSE,TYPE_SCAN);
		}
	}
	else
	{
		if(pDoc->m_bSet_AutoTime)
			bR=g_SPEC.SPEC_DoScan(pDoc->m_fSet_IntTime,pDoc->m_iSet_AvgN,MY_TRIG_NORMAL,fMax,FALSE,TYPE_SCAN);
		else
			bR=g_SPEC.SPEC_DoScan(pDoc->m_fSet_IntTime,pDoc->m_iSet_AvgN,MY_TRIG_NORMAL,fMax,FALSE,TYPE_SCAN);
	}
	if(!bR)
	{
		if(g_bEnglish)
			strTemp.Format("Fail[Spectrum]!");
		else
			strTemp.Format("控制光谱仪失败!");
		CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,0));
		g_SPEC.MyBeep(750);
		Sleep(1000);
		delete temp;
		EnableShow(FALSE);
		return FALSE;
	}
	if(g_bAutoLamp)
	{
		//正在关灯 采样完成即关掉
		if(g_bEnglish)
			strTemp.Format("Lamp Off...");
		else
			strTemp.Format("关灯...");
		CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,255));
		g_cPower.DX_Power_Output(FALSE);
	}

	//信号溢出
	bR=g_SPEC.SPEC_OVER(fMax);
	if(bR)
	{
		if(g_bEnglish)
			strTemp.Format("Ip Overflow,please retry...");
		else
			strTemp.Format("信号溢出,请减少积分时间,再重新测试...");
		CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,0));
		g_SPEC.MyBeep(750);
		Sleep(1000);
		delete temp;

		//溢出时调整积分时间
		/////////////////////////////////
		if(pDoc->m_bSet_AutoTime)
		{
			if(pDoc->m_fSet_IntTime<100)
				pDoc->m_fSet_IntTime=pDoc->m_fSet_IntTime*0.9f;
			else
				pDoc->m_fSet_IntTime=pDoc->m_fSet_IntTime*0.5f;
			if(pDoc->m_fSet_IntTime<g_SPEC.m_fIntTime1)
				pDoc->m_fSet_IntTime=g_SPEC.m_fIntTime1;
		}
		/////////////////////////////////

		//溢出不返回FALSE
		EnableShow(FALSE);
		return TRUE;  //overflow
	}

	//计算色度
	if(g_bEnglish)
		strTemp.Format("calculating...");
	else
		strTemp.Format("正在计算...");

	CMainFrame::ShowNote(strTemp);
	g_SPEC.SPEC_GetSpectData(TRUE,temp->m_spData,FALSE);

	if(g_bUseFluxPL)//使用多组系数
	{
		int iHave;
		iHave=g_CalFluxPLData.m_calData.GetSize();
		if(g_iSeleCalPLFlux<iHave)
		{
			float fK;
			fK=g_CalFluxPLData.m_calData[g_iSeleCalPLFlux]->m_fK;
			float fTemp;
			fTemp=temp->m_spData.m_fPh;
			temp->m_spData.m_fPh=temp->m_spData.m_fPh*fK;
			temp->m_spData.m_fPh_e=temp->m_spData.m_fPh_e*fK;
		}
	}
	else
	{
		//自吸收系数
		if(g_SPEC.m_fModeSelfK > 0 && g_SPEC.m_selfCorrectData.m_iType == 2)
		{
			temp->m_spData.m_fPh	= temp->m_spData.m_fPh*g_SPEC.m_fModeSelfK;
			temp->m_spData.m_fPh_e	= temp->m_spData.m_fPh_e*g_SPEC.m_fModeSelfK;
		}

		// 用光谱法自吸收系数
		if(g_SPEC.m_selfCorrectData.m_iType == 1)
		{
			temp->m_spData.DoSpectrumSelfCorrect(g_SPEC.m_selfCorrectData);
		}
	}
	/////////////////////////////////////////////////////////
	///光度测量
	temp->m_spData.m_iLamp=g_SPEC.m_iLamp;
	float fFlux,fFluxAD;
	if(g_SPEC.m_iLamp==0&&(temp->m_spData.m_iTestType!=3&&temp->m_spData.m_iTestType!=4))  //电光源
	{
		temp->m_spData.m_iTestType = g_SPEC.m_iTestType;
		if(g_SPEC.m_iTestType==0)
			temp->m_spData.m_bTestPH=FALSE;
		else
		{
			temp->m_spData.m_bTestPH=TRUE;
			if(g_bHaveFluxDec)
			{
				bR=g_SPEC.SPEC_FluxAuto(fFluxAD,fFlux);
				if(!bR)
				{
					if(g_bEnglish)
						strTemp.Format("Fail...");
					else
						strTemp.Format("采样光度失败...");
					CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,0));
					Sleep(100);
					EnableShow(FALSE);
					return FALSE;
				}
				temp->m_spData.m_fPH=fFlux;
			}
			else
			{
				fFluxAD=0;
				fFlux=0;
			}
		}
	}
	int iTMPAD;
	if(g_SPEC.m_HAAS_iVer>=3)
	{
		if(g_bHaveTMPDec)
		{
			bR=g_SPEC.SPEC_GetTMP(2,1,temp->m_spData.m_fEnTMP,iTMPAD);  //环境温度
			if(!bR)
			{
				if(g_bEnglish)
					strTemp.Format("Fail...");
				else
					strTemp.Format("采样温度失败...");
				CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,0));
				Sleep(100);
				EnableShow(FALSE);
				return FALSE;
			}

			if(temp->m_spData.m_fEnTMP < 100.0f)
				temp->m_spData.m_strT.Format("%.1f",temp->m_spData.m_fEnTMP);
		}
		else
		{
			temp->m_spData.m_fEnTMP = 250.0f;
		}

	}
	m_iNumTMP++;
	/////////////////////////////////
	if(g_SPEC.m_iParType>0)
		temp->m_spData.m_strName=g_doData.m_sData.m_listLamp[g_SPEC.m_iParType]->m_strName;

	//如果没接光通探头,则用光谱法测试的参数
	if(g_SPEC.m_iLamp==0)
	{
		if(g_SPEC.m_iTestType==0)
			temp->m_spData.m_bTestPH=FALSE;
		else
			temp->m_spData.m_bTestPH=TRUE;
		if(fFluxAD<=1000)
			temp->m_spData.m_fPH=temp->m_spData.m_fPh;
	}
	else
	{
		temp->m_spData.m_bTestPH=TRUE;
		temp->m_spData.m_fPH=g_SPEC.m_CAL_fPhoK[g_SPEC.m_iBin]*temp->m_spData.m_fPh;
	}

	// 光强计算　x 距离平方
	if(temp->m_spData.m_iTestType==3)
	{
		temp->m_spData.m_fPH   = (float)(temp->m_spData.m_fPH
									*temp->m_spData.m_fDistance
									*temp->m_spData.m_fDistance
									*g_SPEC.m_fIntK);
		temp->m_spData.m_fPh_e = (float)(temp->m_spData.m_fPh_e
									*temp->m_spData.m_fDistance
									*temp->m_spData.m_fDistance
									*g_SPEC.m_fIntK);
	}

	// 测试光亮度
	if(temp->m_spData.m_iTestType==4)
	{
		// 用分光法来测试光亮度值
		temp->m_spData.m_fPH = temp->m_spData.m_fPh;
	}

	temp->m_spData.m_bTestF = FALSE;
	if(g_bHavePower)
	{
		float fV1,fI1,fP1,fPF1;

		if(g_bManuP)
		{
			CDlgInputPower dlg;
			//保存上次输入的数据
			CString strSection  = "INPUT POWER";
			CString strI		= "I";
			CString strU		= "U";
			CString strP		= "P";
			CString strPF		= "PF";
			CString strTemp;
			strTemp   = AfxGetApp()->GetProfileString(strSection,strI,"0.02");
			dlg.m_fI  = (float)atof(strTemp);
			strTemp   = AfxGetApp()->GetProfileString(strSection,strU,"5");
			dlg.m_fU  = (float)atof(strTemp);
			strTemp   = AfxGetApp()->GetProfileString(strSection,strP,"0.1");
			dlg.m_fP  = (float)atof(strTemp);
			strTemp   = AfxGetApp()->GetProfileString(strSection,strPF,"1.000");
			dlg.m_fPF = (float)atof(strTemp);
			dlg.DoModal();

			strTemp.Format("%f",dlg.m_fI);
			AfxGetApp()->WriteProfileString(strSection,strI,strTemp);
			strTemp.Format("%f",dlg.m_fU);
			AfxGetApp()->WriteProfileString(strSection,strU,strTemp);
			strTemp.Format("%f",dlg.m_fP);
			AfxGetApp()->WriteProfileString(strSection,strP,strTemp);
			strTemp.Format("%f",dlg.m_fPF);
			AfxGetApp()->WriteProfileString(strSection,strPF,strTemp);

			fV1  = dlg.m_fU;
			fI1  = dlg.m_fI;
			fP1  = dlg.m_fP;
			fPF1 = dlg.m_fPF;
		}
		else
		{
			float fFreq;
			int iCOM;
			sscanf(g_strPowCom,"COM%d",&iCOM);
			g_cPowerMeter.NP_Power_Init(iCOM);
			bR = g_cPowerMeter.NP_Power_ReadData(fV1,fI1,fP1,fFreq,fPF1);
		}
		temp->m_spData.m_bTestF = TRUE;
		temp->m_spData.m_fVF  = fV1;
		temp->m_spData.m_fIF  = fI1;
		temp->m_spData.m_fPow = fP1;
		temp->m_spData.m_fPF  = fPF1;
	}

	if(g_SPEC.m_bHaveCool)
		temp->m_spData.m_iCoolState=1;
	else
		temp->m_spData.m_iCoolState=0;

	if(temp->m_spData.m_fEnTMP < 100.0f)
		temp->m_spData.m_strT.Format("%.1f",temp->m_spData.m_fEnTMP);

	pDoc->m_strNumber = AddNumber(pDoc->m_strNumber);
	temp->m_spData.m_strNumber=pDoc->m_strNumber;

	//处理辐射值
	if(g_SPEC.m_iLamp==0)
		temp->m_spData.DoPh_e(pDoc->m_ledData.m_iPhType);

	temp->m_spData.m_strCompany	= g_strCompany;
	temp->m_spData.m_strAddr	= g_strAddr;

	//增加数据
	pDoc->m_ledData.m_listData.Add(temp);
	//列表插入
	pDoc->m_ledData.LIST_Insert(GetListCtrl(),pDoc->m_ledData.m_listData.GetSize()-1);
	//更新界面
	pDoc->m_tempData=*temp;
	pDoc->Calc_B_Active(pDoc->m_ledData.m_listData.GetSize()-1);
	::PostMessage(g_MainWnd,WM_UPDATE,0,0);

	//选择到当前位置
	GetListCtrl().SetItemState(pDoc->m_ledData.m_listData.GetSize()-1, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
	GetListCtrl().EnsureVisible(pDoc->m_ledData.m_listData.GetSize()-1, FALSE);

	EnableShow(FALSE);
	///////////////////////////////////////////////////////////////////////////////////////////////

	SetTimer(1, 10, NULL);

	if(g_iTestType==0)//单次测试自动保存临时文件
	{
		CTime tNow;
		tNow=CTime::GetCurrentTime();
		//创建文件夹
		CString sTemp;
		sTemp=g_strCurPath+"\\Files\\";
		CreateDirectory(sTemp,NULL);
		SHChangeNotify(SHCNE_MKDIR,SHCNF_PATH,sTemp,0);

		sTemp=sTemp+"temp.gcs";
		pDoc->OnSaveDocument(sTemp);//自动保存
	}
	//文件修改标志
	pDoc->SetModifiedFlag(TRUE);

//	pDoc->m_ledData.Export_CSV(g_strCurPath + "Auto_Save.xls");
	return TRUE;
}

CString CMySpecView::AddNumber(CString strNumber)
{
	CString strTemp,strTemp2;

	int i,iB,iN,iTemp;

	iN=strNumber.GetLength();
	iB=iN;
	char a;
	for(i=1;i<=iN;i++)
	{
		a=strNumber.GetAt(iN-i);

		if(a>='0'&&a<='9')  //查找有几位是数字
			iB=iN-i;
		else
			break;
	}
	strTemp=strNumber.Right(iN-iB);  //数字部分
	float fTemp;
	fTemp=(float)atof(strTemp);
	if(fTemp>10000)
	{
		strTemp=strNumber.Right(5);  //数字部分
		iTemp=(int)atoi(strTemp);

		strTemp2=strNumber.Left(iB+(iN-iB-5));  //字母部分
		strTemp.Format("%05d",iTemp+1);
	}
	else
	{
		iTemp=atoi(strTemp);

		strTemp2=strNumber.Left(iB);  //字母部分
		strTemp.Format("%d",iTemp+1);
		int N=strTemp.GetLength();
		for(i=0;i<iN-iB-N;i++)
			strTemp="0"+strTemp;
	}


	strTemp=strTemp2+strTemp;

	return strTemp;
}

void CMySpecView::EnableShow(BOOL bStart)
{
#ifdef _DEBUG
	return;
#endif

	CMenu *pMenu=GetParentOwner()->GetSystemMenu(FALSE);
	if(bStart)
		pMenu->EnableMenuItem(SC_CLOSE,MF_BYCOMMAND|MF_DISABLED);
	else
		pMenu->EnableMenuItem(SC_CLOSE,MF_BYCOMMAND|MF_ENABLED);
}

void CMySpecView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CListView::OnRButtonDown(nFlags, point);
}

void CMySpecView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(0)//g_bTest)
	{
		if(g_bEnglish)
			AfxMessageBox("Please stop test first!");
		else
			AfxMessageBox("请先停止测试!");
		return;
	}
	
	CListView::OnLButtonDown(nFlags, point);
}

void CMySpecView::OnAllSele() 
{
	// TODO: Add your command handler code here
	CMySpecDoc *pDoc=GetDocument();
	int iN;
	g_bInsert=TRUE;
	iN=pDoc->m_ledData.m_listData.GetSize();
	for(int i=0;i<iN;i++)
	{
		if(!m_bAllSele)
			GetListCtrl().SetCheck(i);
		else
			GetListCtrl().SetCheck(i,FALSE);
	}
	g_bInsert=FALSE;
	m_bAllSele=!m_bAllSele;
	g_bAllSele=m_bAllSele;
}

void CMySpecView::OnUpdateAllSele(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMySpecDoc *pDoc=GetDocument();
	int iN;
	iN=pDoc->m_ledData.m_listData.GetSize();
	pCmdUI->Enable(!g_bTest&&iN>0);
}

void CMySpecView::OnPower() 
{
	// TODO: Add your command handler code here
	CMySpecDoc *pDoc=GetDocument();

	if(1)
	{
		int iCur=pDoc->m_nActive+pDoc->m_iB;
		if(iCur>=0&&iCur<pDoc->m_ledData.m_listData.GetSize())
		{
			CDlgInputPower dlg;

			dlg.m_fI   = pDoc->m_ledData.m_listData[iCur]->m_spData.m_fIF;
			dlg.m_fU   = pDoc->m_ledData.m_listData[iCur]->m_spData.m_fVF;
			dlg.m_fP   = pDoc->m_ledData.m_listData[iCur]->m_spData.m_fPow;
			dlg.m_fPF  = pDoc->m_ledData.m_listData[iCur]->m_spData.m_fPF;

			if(dlg.DoModal()==IDOK)
			{
				pDoc->m_ledData.m_listData[iCur]->m_spData.m_bTestF=TRUE;
				pDoc->m_ledData.m_listData[iCur]->m_spData.m_fIF  = dlg.m_fI;
				pDoc->m_ledData.m_listData[iCur]->m_spData.m_fVF  = dlg.m_fU;
				pDoc->m_ledData.m_listData[iCur]->m_spData.m_fPow = dlg.m_fP;
				pDoc->m_ledData.m_listData[iCur]->m_spData.m_fPF  = dlg.m_fPF;

				//更新界面
				pDoc->m_tempData.m_spData.m_fIF  = dlg.m_fI;
				pDoc->m_tempData.m_spData.m_fVF  = dlg.m_fU;
				pDoc->m_tempData.m_spData.m_fPow = dlg.m_fP;
				pDoc->m_tempData.m_spData.m_fPF  = dlg.m_fPF;

				g_bHaveMode		= TRUE;
				pDoc->m_bReList	= TRUE;
				pDoc->UpdateAllViews(NULL);
				g_bHaveMode		= FALSE;

				pDoc->SetModifiedFlag(TRUE);
			}
		}
	}
}

void CMySpecView::OnUpdatePower(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(g_bPowerMod)
	{
		CMySpecDoc *pDoc=GetDocument();
		int iCur=pDoc->m_nActive+pDoc->m_iB;
		if(iCur>=0&&iCur<pDoc->m_ledData.m_listData.GetSize())
			pCmdUI->Enable(g_bPowerMod);
		else
			pCmdUI->Enable(FALSE);
	}
}

void CMySpecView::OnModeInttime() 
{
	// TODO: Add your command handler code here
	
}

void CMySpecView::OnUpdateModeInttime(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMySpecView::OnCustomdrawMyList(NMHDR *pNMHDR, LRESULT *pResult)
{
	//This code based on Michael Dunn's excellent article on
	//list control custom draw at http://www.codeproject.com/listctrl/lvcustomdraw.asp
	
	CMySpecDoc *pDoc = GetDocument();
	if(pDoc != 0)
		pDoc->m_ledData.ReCalcLeve();

	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );

	// Take the default processing unless we set this to something else below.
	*pResult = CDRF_DODEFAULT;

	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.
	if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		// This is the notification message for an item.  We'll request
		// notifications before each subitem's prepaint stage.
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
	{
		CMySpecDoc *pDoc=GetDocument();
		
		COLORREF clrNewTextColor, clrNewBkColor;
		int    nItem = static_cast<int>( pLVCD->nmcd.dwItemSpec );
		CString strTemp = GetListCtrl().GetItemText(nItem,pLVCD->iSubItem);
/*
		// Item 
		if(pLVCD->iSubItem==0)
		{
			clrNewTextColor = RGB(128,64,255);
			clrNewBkColor = RGB(233, 218, 233);
		}
*/
		clrNewTextColor = RGB(0,0,0);
		clrNewBkColor   = RGB(255,255,255);

		int iN;
		iN = g_bError.GetSize();
		if(iN > 0)
		{
/*			if(g_bError[nItem])
			{
				clrNewTextColor = g_ErrTextColor;	//Leave the text black
				clrNewBkColor   = g_ErrBkColor;		//leave the bkgrnd color white
			}
			else
			{
				clrNewTextColor = RGB(0,0,0);
				clrNewBkColor   = RGB(255,255,255);
			}*/

			if(CLED300ListData::m_failFlagData.IsFail(nItem, pLVCD->iSubItem) == TRUE)
			{
				clrNewTextColor = g_ErrTextColor;	//Leave the text black
				clrNewBkColor   = g_ErrBkColor;		//leave the bkgrnd color white
			}
			else
			{
				clrNewTextColor = RGB(0,0,0);
				clrNewBkColor   = RGB(255,255,255);
			}

		}

		pLVCD->clrText = clrNewTextColor;
		pLVCD->clrTextBk = clrNewBkColor;

		// Tell Windows to paint the control itself.
		*pResult = CDRF_DODEFAULT;
	}
}


/*
*  Pipe通讯副线程
*/
UINT CMySpecView::Thread_NamePipe(LPVOID pParam)
{
	CMySpecView *pView = (CMySpecView *)pParam;
	pView->NamePipe();
	return 0;
}

void CMySpecView::NamePipe()
{
    HANDLE                  hPipe = INVALID_HANDLE_VALUE;
    HANDLE                  hEvents[1] = {NULL};

    TCHAR                   szIn[80];
    TCHAR                   szOut[65535 * 4 * 2 + 100];
    LPTSTR                  lpszPipeName = HAAS_PIPE_NAME_SREVER;
    BOOL                    bRet;
    DWORD                   cbRead;
    DWORD                   cbWritten;
    DWORD                   dwWait;
    SECURITY_ATTRIBUTES     sa;
    PSECURITY_DESCRIPTOR    pSD = NULL;
    OVERLAPPED              os;

    // create the event object object use in overlapped i/o
    //
    hEvents[0] = CreateEvent(
        NULL,    // no security attributes
        TRUE,    // manual reset event
        FALSE,   // not-signalled
        NULL);   // no name
	
    if ( hEvents[0] == NULL)
        goto cleanup;

	m_hEvents = hEvents[0];

    // create a security descriptor that allows anyone to write to
    //  the pipe...
    //
    pSD = (PSECURITY_DESCRIPTOR) malloc( SECURITY_DESCRIPTOR_MIN_LENGTH );
	
    if (pSD == NULL)
        goto cleanup;
	
    if (!InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION))
        goto cleanup;
	
    // add a NULL disc. ACL to the security descriptor.
    //
    if (!SetSecurityDescriptorDacl(pSD, TRUE, (PACL) NULL, FALSE))
        goto cleanup;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = pSD;
    sa.bInheritHandle = TRUE;

	// open our named pipe...
    //
    hPipe = CreateNamedPipe(
		lpszPipeName         ,  // name of pipe
		FILE_FLAG_OVERLAPPED |
		PIPE_ACCESS_DUPLEX,     // pipe open mode
		PIPE_TYPE_MESSAGE |
		PIPE_READMODE_MESSAGE |
		PIPE_WAIT,              // pipe IO type
		1,                      // number of instances
		0,                      // size of outbuf (0 == allocate as necessary)
		0,                      // size of inbuf
		10000,                   // default time-out value
		&sa);                   // security attributes
	
    if (hPipe == INVALID_HANDLE_VALUE) {

        // AfxMessageBox(TEXT("Unable to create named pipe"));

        goto cleanup;
    }

	while ( 1 )
    {
		if(m_bSetStop)
			break;

        // init the overlapped structure
        //
        memset( &os, 0, sizeof(OVERLAPPED) );
        os.hEvent = hEvents[0];
        ResetEvent( hEvents[0] );
		
        // wait for a connection...
        //
        ConnectNamedPipe(hPipe, &os);
		
        if ( GetLastError() == ERROR_IO_PENDING )
        {
            dwWait = WaitForMultipleObjects( 1, hEvents, FALSE, INFINITE );
            if ( dwWait != WAIT_OBJECT_0+0 )     // not overlapped i/o event - error occurred,
                break;                           // or server stop signaled

			if(m_bSetStop)
				break;
        }

        // init the overlapped structure
        //
        memset( &os, 0, sizeof(OVERLAPPED) );
        os.hEvent = hEvents[0];
        ResetEvent( hEvents[0] );
		
        // grab whatever's coming through the pipe...
        //
        bRet = ReadFile(
			hPipe,          // file to read from
			szIn,           // address of input buffer
			sizeof(szIn),   // number of bytes to read
			&cbRead,        // number of bytes read
			&os);           // overlapped stuff, not needed
		
        if ( !bRet && ( GetLastError() == ERROR_IO_PENDING ) )
        {
            dwWait = WaitForMultipleObjects( 1, hEvents, FALSE, INFINITE );
            if ( dwWait != WAIT_OBJECT_0+0 )     // not overlapped i/o event - error occurred,
                break;                           // or server stop signaled
        }

		/* 处理 */
		int iCmdNum = strlen(HAAS_SAMPLE);

		int iOutN = 0;
		
		if( (int)strlen(szIn) >= iCmdNum)
		{
			CString strCmd = szIn;
			strCmd = strCmd.Left(iCmdNum);

			/* 采样 */
			if(strCmd == HAAS_SAMPLE)
			{
				CMySpecDoc *pDoc = GetDocument();

				if(pDoc->m_ledData.m_listData.GetSize() > 100)
				{
					pDoc->SetModifiedFlag(FALSE);
					AfxGetMainWnd()->SendMessage(WM_COMMAND,ID_FILE_NEW);	
					Sleep(100);
				}

				int iCalSele = 0;
				/* 取出采样设置 */
				CString strType =  szIn;
				strType = strType.Mid(iCmdNum + 1, strlen(szIn) - iCmdNum - 1);	
				sscanf(strType,"%d %f %d %d %d %d", &m_bRemoteAutoIntTime, &m_fRemoteIntTime, &m_iRemoteGainRange, &m_iRemoteGainRange, &iCalSele);

				if(iCalSele < 0)
					iCalSele = 0;

				if(iCalSele > 100)
					iCalSele = 0;

				g_SPEC.m_bUseListCalSele = TRUE;
				g_SPEC.m_iTestListCalSele = iCalSele;

				::PostMessage(m_hWnd, WM_PC2_PRO, 0, 0);

				BOOL bR;
				
				/* 采样 */
				
				/* 进入PC2模式,不提示错误 */
				m_bPC2Mode = TRUE;
				
				/* 事件复位 */
				m_EventTest.ResetEvent();
				
				/* 测试 */
				::PostMessage(m_hWnd,WM_COMMAND,ID_TEST,0);
				
				/* 等待测试完成 */
				int iOutTime = (int)m_fRemoteIntTime * 2 + 10000;
				if(m_bRemoteAutoIntTime)
					iOutTime = 180000;
				bR = m_EventTest.Lock( iOutTime);

				/* 恢复常规模式 */
				m_bPC2Mode = FALSE;
				
				if(!bR)
				{
					/* 超时出错 */
					_stprintf(szOut, TEXT("[TimeOut]"));
					iOutN = strlen(szOut) + 1;
				}
				else if(m_iTestResult != 0)
				{
					/* 测试失败 */
					_stprintf(szOut, TEXT("[Fail:%d]"), m_iTestResult);
					iOutN = strlen(szOut) + 1;
				}
				else
				{
					_stprintf(szOut, TEXT("[OK]"), m_iTestResult);
					iOutN = strlen(szOut) + 1;
					
					m_iCurrRead = 0;
				}
			}

			/* 读取数据 */
			if(strCmd == HAAS_READ_DATA)
			{
				CMySpecDoc *pDoc = GetDocument();
				_stprintf(szOut,"x=%.4f,y=%.4f,CCT=%.0fK,Lp=%.1fnm,Ld=%.1fnm,Pur=%.2f%%,Ph=%.5g Ra=%.1f T=%.0fms,Ip=%.0f,Phe=%.5g",
					pDoc->m_tempData.m_spData.m_x, 
					pDoc->m_tempData.m_spData.m_y, 
					pDoc->m_tempData.m_spData.m_fCCT, 
					pDoc->m_tempData.m_spData.m_fMaxlambda,
					pDoc->m_tempData.m_spData.m_fMainlambda,
					pDoc->m_tempData.m_spData.m_fPurity,
					pDoc->m_tempData.m_spData.m_fPh, 
					pDoc->m_tempData.m_spData.m_fRa, 
					pDoc->m_tempData.m_spData.m_fIntTime,
					pDoc->m_tempData.m_spData.m_fIp,
					pDoc->m_tempData.m_spData.m_fPh_e);
				iOutN = strlen(szOut) + 1;
			}

			/* 清除数据 */
			if(strCmd == HAAS_CLEAR_ALL)
			{
				CMySpecDoc *pDoc = GetDocument();
				pDoc->SetModifiedFlag(FALSE);
				AfxGetMainWnd()->SendMessage(WM_COMMAND,ID_FILE_NEW);	
				Sleep(100);
				iOutN = 0;
			}
		}

        // init the overlapped structure
        //
        memset( &os, 0, sizeof(OVERLAPPED) );
        os.hEvent = hEvents[0];
        ResetEvent( hEvents[0] );
		
        // send it back out...
        //
        bRet = WriteFile(
			hPipe,          // file to write to
			szOut,          // address of output buffer
			iOutN,      // number of bytes to write
			&cbWritten,     // number of bytes written
			&os);           // overlapped stuff, not needed
		
        if ( !bRet && ( GetLastError() == ERROR_IO_PENDING ) )
        {
            dwWait = WaitForMultipleObjects( 1, hEvents, FALSE, INFINITE );
            if ( dwWait != WAIT_OBJECT_0+0 )     // not overlapped i/o event - error occurred,
                break;                           // or server stop signaled
        }
		
        // drop the connection...
        //
        DisconnectNamedPipe(hPipe);
    }	
cleanup:
	
    if (hPipe != INVALID_HANDLE_VALUE )
        CloseHandle(hPipe);
	
    if (hEvents[0]) // overlapped i/o event
        CloseHandle(hEvents[0]);
	
    if ( pSD )
        free( pSD );
}

/*
*  更新界面数据
*/
void CMySpecView::OnWM_PC2_Pro(UINT wParam, LONG lParam)
{
	CMySpecDoc *pDoc = GetDocument();
	pDoc->m_bSet_AutoTime = m_bRemoteAutoIntTime;
	
	if(!pDoc->m_bSet_AutoTime)
		pDoc->m_fSet_IntTime = m_fRemoteIntTime;
	
	pDoc->m_iSet_AvgN = 1;
	
	CMainFrame *pMainFrame = (CMainFrame *)GetParentFrame();
	
	pMainFrame->SetDlgBarSet(0);
	pMainFrame->SetDlgBarSet(1);
	pMainFrame->SetDlgBarSet(2);
}

void CMySpecView::OnDelete() 
{
	// TODO: Add your command handler code here
	CMySpecDoc *pDoc = GetDocument();

	int iSeleNum = 0;
	int i;
	for(i = 0; i < pDoc->m_ledData.m_listData.GetSize(); i++)
	{
		if(GetListCtrl().GetCheck(i) == TRUE)
			iSeleNum++;
	}

	if(iSeleNum <= 0)
	{
		if(g_bEnglish)
			AfxMessageBox("Please Select!");
		else
			AfxMessageBox("请打勾要删除的数据!");
		return;
	}

	int iR;
	if(g_bEnglish)
	{
		iR=AfxMessageBox("Delete?",MB_ICONINFORMATION|MB_OKCANCEL);
	}
	else
	{
		iR=AfxMessageBox("确定删除所有打勾的数据?",MB_ICONINFORMATION|MB_OKCANCEL);
	}
	if(iR==IDCANCEL)
		return;

	int iN = pDoc->m_ledData.m_listData.GetSize();
	for(i = 0; i < iN; i++)
	{
		int iSele = iN - 1 - i;
		if(GetListCtrl().GetCheck(iSele) == TRUE)
			pDoc->m_ledData.m_listData.RemoveAt(iSele);
	}	

	pDoc->SetModifiedFlag(TRUE);
	pDoc->m_bReList=TRUE;
	pDoc->UpdateAllViews(NULL);

}

void CMySpecView::OnUpdateDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMySpecView::OnContextMenu(CWnd*, CPoint point)
{

	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_MY_SPEC_VIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

void CMySpecView::OnEditCopyTxt1() 
{
	// TODO: Add your command handler code here
	CMySpecDoc *pDoc = GetDocument();
	int iSeleNum = 0;
	int i;
	CString strData;
	for(i = 0; i < pDoc->m_ledData.m_listData.GetSize(); i++)
	{
		if(GetListCtrl().GetCheck(i) == TRUE)
		{
			strData += pDoc->m_ledData.m_listData.GetAt(i)->GetFormatData();
		}
	}

	HANDLE hGlobaLMemory; 
	LPSTR   lpGlobalMemory;  
	DWORD length = 66536; 
	
	hGlobaLMemory = GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT,(length+1)); 
	lpGlobalMemory = (LPSTR)(GlobalLock(hGlobaLMemory)); 
	
	sprintf(lpGlobalMemory, "%s", strData);
	lpGlobalMemory[length] = strlen(lpGlobalMemory); 
	
	if(::OpenClipboard(m_hWnd)) 
	{   
		::EmptyClipboard(); 
		::SetClipboardData(CF_TEXT,hGlobaLMemory); 
		::CloseClipboard(); 
	} 	
}

void CMySpecView::OnUpdateEditCopyTxt1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMySpecView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == 1)
	{
		KillTimer(1);
		SHOW_DATA();
	}

	if(nIDEvent == 2)
	{
		KillTimer(2);
		CMainFrame *pMainFrame = (CMainFrame *)GetParentFrame();
		
		pMainFrame->SetDlgBarSet(0);
		pMainFrame->SetDlgBarSet(1);
		pMainFrame->SetDlgBarSet(2);
	}
	CListView::OnTimer(nIDEvent);
}

BOOL CMySpecView::CommPh(void *p, float &fPh)
{
	CMySpecDoc *pDoc = (CMySpecDoc *)p;
	float fAD;
	if(g_bHaveFluxDec == TRUE)
	{
		return g_SPEC.SPEC_FluxAuto(fAD, fPh);
	}
	else
	{
		float m_fIntTime = pDoc->m_fSet_IntTime;

		CSpectData m_spData;
		float fMax;
		BOOL bR;
		
		if(g_SPEC.m_fIntTimeDark!=m_fIntTime)
		{
			g_SPEC.SPEC_GetDark(m_fIntTime,1);
		}

		bR = g_SPEC.SPEC_DoScan(m_fIntTime*1.0f,1,MY_TRIG_NORMAL,fMax,FALSE,m_spData.m_iDataType);
		if(!bR)
		{
			if(g_bEnglish)
			{
				AfxMessageBox("Sample fail!",MB_ICONSTOP);
			}
			else
			{
				AfxMessageBox("采样失败!",MB_ICONSTOP);
			}
			return FALSE;
		}
		
		bR = g_SPEC.SPEC_OVER(fMax);
		if(bR)
		{
			if(g_bEnglish)
			{
				AfxMessageBox("Signal is overflow!",MB_ICONSTOP);
			}
			else
			{
				AfxMessageBox("信号溢出!",MB_ICONSTOP);
			}

			return FALSE;
		}

		g_SPEC.SPEC_GetSpectData(TRUE, m_spData);

		fPh = m_spData.m_fPh;
		return TRUE;
	}
}

