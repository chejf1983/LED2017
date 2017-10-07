// TenView.cpp : implementation of the CTenView class
//

#include "stdafx.h"
#include "MySpec.h"

#include "TenView.h"
#include <stdlib.h>
#include "math.h"
#include "MainFrm.h"
#include "Global_MySpec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTenView

IMPLEMENT_DYNCREATE(CTenView, CRowView)

BEGIN_MESSAGE_MAP(CTenView, CRowView)
	//{{AFX_MSG_MAP(CRowView)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CTenView construction/destruction

extern BOOL g_bTest;
extern int g_iLEDClass_Type;

CTenView::CTenView()
{
	// TODO: add construction code here
}

CTenView::~CTenView()
{
}

 
void CTenView::OnUpdate(CView*, LPARAM lHint, CObject* pHint)
{
	// OnUpdate() is called whenever the document has changed and,
	// therefore, the view needs to redisplay some or all of itself.


	if (0)
	{
		int nRow = LOWORD(lHint);
		UpdateRow(nRow);
	}
	else
	{

		CMySpecDoc* pDoc = GetDocument();
		UpdateRow(pDoc->m_nActive);
		ChangeSelectionToRow(pDoc->m_nActive);

		if(pDoc->m_ledData.m_listData.GetSize()==0)
			Invalidate();
	}
}

void CTenView::GetRowWidthHeight(CDC* pDC, int& nRowWidth, int& nRowHeight)
{
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	nRowWidth  = tm.tmAveCharWidth * (ROWV_W_SN+ROWV_W_DATA+ROWV_W_SPECT);
	nRowHeight = tm.tmHeight * ROWV_H; 
}

int CTenView::GetActiveRow()
{
	CMySpecDoc* pDoc = GetDocument();
	return pDoc->m_nActive;
}

int CTenView::GetRowCount()
{
	CMySpecDoc* pDoc = GetDocument();
	int iN=pDoc->m_ledData.m_listData.GetSize();
	int NN=iN-pDoc->m_iB;
	if(NN<0)
		NN=0;
	if(NN>pDoc->PAGE_N)
		NN=pDoc->PAGE_N;
	return NN;
}

void CTenView::ChangeSelectionNextRow(BOOL bNext)
{
	CMySpecDoc* pDoc = GetDocument();
	if(bNext)
	{
		if((pDoc->m_nActive+pDoc->m_iB)<(pDoc->m_ledData.m_listData.GetSize()-1))
		{
			pDoc->m_nActive++;
			if((pDoc->m_nActive+pDoc->m_iB)%pDoc->PAGE_N==0)
			{
				pDoc->m_iB=pDoc->m_nActive+pDoc->m_iB;
				pDoc->m_nActive=0;
			}
			GetRowCount();
			UpdateRow(pDoc->m_nActive);
			::PostMessage(g_MainWnd,WM_UPDATE,0,0);
		}
	}
	else
	{
		if((pDoc->m_nActive+pDoc->m_iB)>0)
		{
			pDoc->m_nActive--;
			if(pDoc->m_nActive==-1&&pDoc->m_iB!=0)
			{
				pDoc->m_iB=pDoc->m_iB-pDoc->PAGE_N;;
				if(pDoc->m_iB<0)
				{
					pDoc->m_iB=0;
					pDoc->m_nActive=pDoc->m_ledData.m_listData.GetSize()-1;
				}
				else
				{
					pDoc->m_nActive=pDoc->PAGE_N-1;
				}
			}
			GetRowCount();
			UpdateRow(pDoc->m_nActive);
			::PostMessage(g_MainWnd,WM_UPDATE,0,0);
		}
	}
}

void CTenView::ChangeSelectionToRow(int nRow)
{
	CMySpecDoc* pDoc = GetDocument();
	if(pDoc->m_nActive==nRow)
		return;
	pDoc->m_nActive=nRow;
	GetRowCount();
	UpdateRow(pDoc->m_nActive);
	::PostMessage(g_MainWnd,WM_UPDATE,0,0);
}

void CTenView::OnDrawRow(CDC* pDC, int nRow, int y, BOOL bSelected)
{
	// Prepare for highlighting or un-highlighting the check, depending
	// on whether it is the currently selected check or not.  And
	// paint the background (behind the text) accordingly.
	//draw data

	CMySpecDoc* pDoc = GetDocument();
	if((nRow+pDoc->m_iB)<0||(nRow+pDoc->m_iB)>(pDoc->m_ledData.m_listData.GetSize()-1))
		return;
	CLED300Data *temp=pDoc->m_ledData.m_listData[nRow+pDoc->m_iB];
	CBrush brushBackground;
	CFont *pOldFont=NULL;
	CFont Font;
	// save colors for drawing selected item on the screen
	COLORREF crOldText = 0;
	COLORREF crOldBackground = 0;

	if(!pDC->IsPrinting())
	{
		Font.CreateFont(16,0,0,0,600,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Courier New");  
		pOldFont=pDC->SelectObject(&Font);
		pDC->SetTextColor(RGB(0,0,0));
	}
	else
	{
		Font.CreateFont(80,0,0,0,600,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Courier New");  
		pOldFont=pDC->SelectObject(&Font);
		pDC->SetTextColor(RGB(0,0,0));
	}
	if (!pDC->IsPrinting())
	{
		if (bSelected)
		{
			brushBackground.CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT));
			crOldBackground = pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
			crOldText = pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		}
		else
		{
			brushBackground.CreateSolidBrush(::GetSysColor(COLOR_WINDOW));
		}

		CRect rectSelection;
		pDC->GetClipBox(&rectSelection);
		rectSelection.top = y;
		rectSelection.bottom = y + m_nRowHeight;
		if (bSelected)
			pDC->FillRect(&rectSelection, &brushBackground);
	}

	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);

	int y2=(int)(y+0.2f*tm.tmHeight);
	pDC->SetTextAlign(TA_LEFT);
	pDC->SetBkMode(TRANSPARENT);

	CString strTemp;
	strTemp.Format("SN.:%04d",nRow+1+pDoc->m_iB);
	pDC->TextOut(0*tm.tmAveCharWidth,y2,strTemp);
	strTemp.Format("Number:"+temp->m_spData.m_strNumber);
	pDC->TextOut(0*tm.tmAveCharWidth,(int)(y+1.2f*tm.tmHeight),strTemp);

	COLORREF color;
	if(g_iLEDClass_Type == 1)
		strTemp = pDoc->m_ledData.m_newClassLimit.GetLevel(*temp,pDoc->m_ledData.m_iPhType, color);
	else
		strTemp=pDoc->m_ledData.m_levelLimit.GetLevel(*temp,pDoc->m_ledData.m_iPhType);

	if(pDoc->m_ledData.m_opData.m_bWhite)
		pDC->TextOut(0*tm.tmAveCharWidth,y2+(int)(2.1*tm.tmHeight),"LEVEL:"+strTemp);
	if(temp->m_spData.m_bHaveData)
		strTemp=pDoc->m_ledData.m_xyZone.IN_ZONE(temp->m_spData.m_x,temp->m_spData.m_y);
	else
		strTemp="";
	if(pDoc->m_ledData.m_opData.m_bWhite)
		pDC->TextOut(0*tm.tmAveCharWidth,y2+(int)(3.2*tm.tmHeight),"WHITE:"+strTemp);

	if(temp->m_spData.m_bTestF)
	{
		strTemp.Format("U=%sV  I=%sA  P=%sW PF=%s",
			g_SPEC.sFormat(temp->m_spData.m_fVF,4),g_SPEC.sFormat(temp->m_spData.m_fIF,4),
			g_SPEC.sFormat(temp->m_spData.m_fPow,4),g_SPEC.sFormat(temp->m_spData.m_fPF,4));
		pDC->TextOut((ROWV_W_SN+ROWV_W_SPECT+1)*tm.tmAveCharWidth,y2+0*tm.tmHeight,strTemp);
	}
	int iLamp=g_SPEC.m_iLamp;
	iLamp=temp->m_spData.m_iLamp;
	if(temp->m_spData.m_bTestPH&&temp->m_spData.m_bHaveColorPara)
	{
		CString strPh,strUnit;
		strPh=temp->m_spData.PH_Name(iLamp,pDoc->m_ledData.m_iPhType,strUnit);

		strTemp.Format("%s = %s %s",strPh,g_SPEC.sFormat(temp->m_spData.m_fPH,5),strUnit);
		pDC->TextOut((ROWV_W_SN+ROWV_W_SPECT+1)*tm.tmAveCharWidth,y2+1*tm.tmHeight,strTemp);

		if(pDoc->m_ledData.m_iPhType==PH_F&&temp->m_spData.m_bTestF)
		{
			float fEff;
			if(temp->m_spData.m_fPow<=0 || temp->m_spData.m_fIF <= 0)
				fEff=0;
			else
				fEff=temp->m_spData.m_fPH/(temp->m_spData.m_fPow);
			if(g_bEnglish)
				strTemp.Format("Eff. = %.2f lm/W",fEff);
			else
				strTemp.Format("η = %.2f lm/W",fEff);
			pDC->TextOut((ROWV_W_SN+ROWV_W_SPECT+15)*tm.tmAveCharWidth,y2+1*tm.tmHeight,strTemp);
		}
	}
	if(temp->m_spData.m_bTestPH&&!temp->m_spData.m_bHaveColorPara)
	{
		if(pDoc->m_ledData.m_iPhType==PH_F)
		{
			CString strUnit,strPH,strFe;
			strPH=CSpectData::PH_Name(temp->m_spData.m_iLamp,PH_Fe,strUnit);
			if(temp->m_spData.m_fPh_e>1)
			{
				strFe.Format("  %s  = %s W",strPH,g_SPEC.sFormat(temp->m_spData.m_fPh_e,5));
			}
			else
				strFe.Format("  %s  = %s %s",strPH,g_SPEC.sFormat(temp->m_spData.m_fPh_e*1000,5),strUnit);
			pDC->TextOut((ROWV_W_SN+ROWV_W_SPECT+1)*tm.tmAveCharWidth,y2+1*tm.tmHeight,strFe);
		}
	}
	if(temp->m_spData.m_bHaveData)
	{
		if(temp->m_spData.m_bHaveColorPara)
		{
			strTemp.Format(" x = %.4f   y = %.4f (CCT=%.0fK)",temp->m_spData.m_x,temp->m_spData.m_y,temp->m_spData.m_fCCT);
			pDC->TextOut((ROWV_W_SN+ROWV_W_SPECT+1)*tm.tmAveCharWidth,y2+2*tm.tmHeight,strTemp);

			strTemp.Format(" u'= %.4f   v'= %.4f",temp->m_spData.m_u,temp->m_spData.m_v);
			pDC->TextOut((ROWV_W_SN+ROWV_W_SPECT+1)*tm.tmAveCharWidth,y2+3*tm.tmHeight,strTemp);

			if(g_bEnglish)
				strTemp.Format("Ld = %.1fnm   Pur = %.1f%%",temp->m_spData.m_fMainlambda,temp->m_spData.m_fPurity);
			else
				strTemp.Format("λd= %.1fnm   Pur = %.1f%%",temp->m_spData.m_fMainlambda,temp->m_spData.m_fPurity);
			pDC->TextOut((ROWV_W_SN+ROWV_W_SPECT+1)*tm.tmAveCharWidth,y2+4*tm.tmHeight,strTemp);
		}

		if(g_bEnglish)
			strTemp.Format("Lp = %.1fnm Lhp = %.1fnm",temp->m_spData.m_fMaxlambda,temp->m_spData.m_fHalflambda);
		else
			strTemp.Format("λp= %.1fnm Δλp = %.1fnm",temp->m_spData.m_fMaxlambda,temp->m_spData.m_fHalflambda);
		pDC->TextOut((ROWV_W_SN+ROWV_W_SPECT+1)*tm.tmAveCharWidth,y2+5*tm.tmHeight,strTemp);

		if(temp->m_spData.m_bHaveColorPara)
		{		
			strTemp.Format("Red Ratio=%.1f%%  Ra = %.1f",temp->m_spData.m_fRedRatio,temp->m_spData.m_fRa);
			pDC->TextOut((ROWV_W_SN+ROWV_W_SPECT+1)*tm.tmAveCharWidth,y2+6*tm.tmHeight,strTemp);
		}

		strTemp.Format("Ip = %.0f(%.0f%%)  T = %.0fms",temp->m_spData.m_fIp,temp->m_spData.m_fIp*100.0f/(temp->m_spData.m_nADW-1),temp->m_spData.m_fIntTime);
		pDC->TextOut((ROWV_W_SN+ROWV_W_SPECT+1)*tm.tmAveCharWidth,y2+7*tm.tmHeight,strTemp);
	}

	int i;
	CRect specRect;
	specRect.left   = (ROWV_W_SN)*tm.tmAveCharWidth;
	specRect.right  = (ROWV_W_SN+ROWV_W_SPECT)*tm.tmAveCharWidth;
	specRect.top    = y;
	specRect.bottom = y+ROWV_H*tm.tmHeight;

	if(1)
	{
		pDC->MoveTo(0,(int)(y+0.0f*tm.tmHeight));
		pDC->LineTo((ROWV_W_SN+ROWV_W_SPECT+ROWV_W_DATA)*tm.tmAveCharWidth,(int)(y+0.0f*tm.tmHeight));

		pDC->MoveTo(0,y+(int)((ROWV_H-0.0f)*tm.tmHeight));
		pDC->LineTo((ROWV_W_SN+ROWV_W_SPECT+ROWV_W_DATA)*tm.tmAveCharWidth,y+(int)((ROWV_H-0.0f)*tm.tmHeight));
	}
	CRect spRect;
	spRect.left   = (ROWV_W_SN)*tm.tmAveCharWidth+2*tm.tmAveCharWidth;
	spRect.right  = (ROWV_W_SN+ROWV_W_SPECT)*tm.tmAveCharWidth-2*tm.tmAveCharWidth;
	spRect.top    = (int)(y+1.2f*tm.tmHeight);
	spRect.bottom = (int)(y+ROWV_H*tm.tmHeight-2.8f*tm.tmHeight);

	pDC->MoveTo(spRect.left,spRect.bottom);
	pDC->LineTo(spRect.right,spRect.bottom);

	pDC->SetTextAlign(TA_CENTER);
	for(i=0;i<=4;i++)
	{
		pDC->MoveTo((int)(spRect.left+spRect.Width()*i/4.0f),spRect.bottom-tm.tmHeight/4);
	 	pDC->LineTo((int)(spRect.left+spRect.Width()*i/4.0f),spRect.bottom+tm.tmHeight/4);

		strTemp.Format("%.0f",temp->m_spData.m_fSpect1+(temp->m_spData.m_fSpect2-temp->m_spData.m_fSpect1)*i/4.0f);
		pDC->TextOut((int)(spRect.left+spRect.Width()*i/4.0f),spRect.bottom+tm.tmHeight*1/4,strTemp);
	}
	strTemp.Format("SPECTRUM");
	pDC->TextOut(spRect.left+spRect.Width()/2,y+tm.tmHeight*1/5,strTemp);

	pDC->TextOut(spRect.left+spRect.Width()/2,spRect.bottom+tm.tmHeight*1/4+tm.tmHeight,"Wavelength(nm)");
	if(temp->m_spData.m_bHaveData)
	{
		int iN=temp->m_spData.m_fRelSpect.GetSize();
		int DN=1;
		if(g_bTest)
			DN=20;
		for(i=0;i<iN-DN;i=i+DN)
		{
			int xx,yy;
			xx=(int)(spRect.left+spRect.Width()*i/(iN-1.0f));
			yy=(int)(spRect.bottom-temp->m_spData.m_fRelSpect[i]*spRect.Height());

			float fCurSpect=temp->m_spData.m_fSpect1+temp->m_spData.m_fInterval*i;
			int R,G,B;
			g_doData.GetRGB(fCurSpect,R,G,B);
				
			CBrush Brush;
			Brush.CreateSolidBrush(RGB(R,G,B));		
			CBrush * pOldBrush=pDC->SelectObject(&Brush);

			CPen Pen;
			Pen.CreatePen(PS_SOLID,1,RGB(R,G,B));
			CPen * pOld=pDC->SelectObject(&Pen);

			POINT polygon[4];

			polygon[0].x=(int)(spRect.left+i*spRect.Width()*1.0f/(iN-1)+0.5f);
			polygon[0].y=(int)(spRect.bottom);
			polygon[1].x=(int)(spRect.left+i*spRect.Width()*1.0f/(iN-1)+0.5f);
			polygon[1].y=(int)(spRect.bottom-temp->m_spData.m_fRelSpect[i]*spRect.Height()/1+0.5f);
			polygon[2].x=(int)(spRect.left+(i+DN)*spRect.Width()*1.0f/(iN-1)+0.5f);
			polygon[2].y=(int)(spRect.bottom-temp->m_spData.m_fRelSpect[i+DN]*spRect.Height()/1+0.5f);
			polygon[3].x=(int)(spRect.left+(i+DN)*spRect.Width()*1.0f/(iN-1)+0.5f);
			polygon[3].y=(int)(spRect.bottom);

			pDC->Polygon(polygon,4);
			pDC->SelectObject(pOldBrush);
			pDC->SelectObject(pOld);
		}
	}
	// Restore the DC.
	if (!pDC->IsPrinting() && bSelected)
	{
		pDC->SetBkColor(crOldBackground);
		pDC->SetTextColor(crOldText);
	}

	if(!pDC->IsPrinting())
		pDC->SelectObject(pOldFont);
}

BOOL CTenView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
//	return CView::OnEraseBkgnd(pDC);

	CBrush Brush(RGB(190, 223, 255));               //创建一个紫色刷子

	CBrush* pOldBrush = pDC->SelectObject(&Brush); 	//将紫色刷子选入设备环境

	// 取得重绘区
	CRect rcClip ;
	pDC->GetClipBox (&rcClip);

	pDC->PatBlt(rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), PATCOPY); 	 //重绘该区域
	pDC->SelectObject(pOldBrush); 	                    //恢复设备环境
	return TRUE;
}
