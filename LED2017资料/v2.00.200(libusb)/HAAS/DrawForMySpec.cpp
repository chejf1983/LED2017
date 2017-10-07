// DrawForMySpec.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DrawForMySpec.h"
#include "Global_MySpec.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawForMySpec
extern BOOL g_bUseScan;
BOOL g_bHalfWL;

CDrawForMySpec::CDrawForMySpec()
{
}

CDrawForMySpec::~CDrawForMySpec()
{
}


BEGIN_MESSAGE_MAP(CDrawForMySpec, CStatic)
	//{{AFX_MSG_MAP(CDrawForMySpec)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawForMySpec message handlers

void CDrawForMySpec::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CDC memDC;
	CBitmap *pOldBitmap,memBitmap;
	memDC.CreateCompatibleDC(&dc);
	memBitmap.CreateCompatibleBitmap(&dc,m_nClientWidth,m_nClientHeight);
	pOldBitmap=(CBitmap*)memDC.SelectObject(&memBitmap);
	if(memDC.GetSafeHdc()!=NULL||m_dcPlot.GetSafeHdc()!=NULL)
	{
		memDC.BitBlt(0,0,m_nClientWidth,m_nClientHeight,&m_dcPlot,0,0,SRCCOPY);
		dc.BitBlt(0,0,m_nClientWidth,m_nClientHeight,&m_dcPlot,0,0,SRCCOPY);
	}
	memDC.SelectObject(pOldBitmap);	
	// Do not call CStatic::OnPaint() for painting messages
}

void CDrawForMySpec::DrawMyDebug(float fAD[], int iN,BOOL bLine,DEBUG_DRAW &draw,float fHalf)
{
	//为了调试而作图

	GetClientRect(&m_rectPlot);
	m_nClientWidth=m_rectPlot.Width();
	m_nClientHeight=m_rectPlot.Height();
	
	if (m_dcPlot.GetSafeHdc() == NULL)
	{
		CClientDC dc(this);
		m_dcPlot.CreateCompatibleDC(&dc) ;
		m_bitmapPlot.CreateCompatibleBitmap(&dc, m_nClientWidth, m_nClientHeight) ;
		m_pbitmapOldPlot = m_dcPlot.SelectObject(&m_bitmapPlot) ;
	}
	CBrush BrushBack;
	BrushBack.CreateSolidBrush(RGB(0,0,0));
	m_dcPlot.FillRect(&m_rectPlot,&BrushBack);

	CDC *pDC=&m_dcPlot;

	CFont Font1,Font2;
	CFont *pOldFont;

	int HH=(int)(m_rectPlot.Height()/20.0f+1);
	if(HH<18)
		HH=18;
	if(HH>20)
		HH=20;
	Font1.CreateFont(HH,0,0,0,500,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"MS Sans Serif");  
	Font2.CreateFont(20,0,0,0,500,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"MS Sans Serif");  


	CPen *pOld;
	CPen Pen1,Pen2,Pen3,PenS,PenHalf;
	Pen1.CreatePen(PS_SOLID,1,RGB(0,255,0));
	Pen2.CreatePen(PS_SOLID,1,RGB(255,255,255));
	Pen3.CreatePen(PS_DOT,1,RGB(255,255,255));
	PenS.CreatePen(PS_SOLID,1,RGB(0,255,255));
	PenHalf.CreatePen(PS_SOLID,1,RGB(255,0,0));
	pOld=m_dcPlot.SelectObject(&Pen2);
	pOldFont=m_dcPlot.SelectObject(&Font1);

	int iFontH,iFontW;
	TEXTMETRIC  tm;

	pDC->GetTextMetrics(&tm);
	iFontH=tm.tmHeight+tm.tmExternalLeading;
	iFontW=tm.tmAveCharWidth;

	CRect drRect;
	drRect.left  = m_rectPlot.left+8*iFontW;
	drRect.right = m_rectPlot.right-4*iFontW;
	drRect.top = m_rectPlot.top+1*iFontH;
	drRect.bottom = m_rectPlot.bottom-3*iFontH;

	pDC->MoveTo(drRect.left,drRect.top);
	pDC->LineTo(drRect.left,drRect.bottom);
	pDC->LineTo(drRect.right,drRect.bottom);
	if(bLine)
	{
		pDC->LineTo(drRect.right,drRect.top);
		pDC->LineTo(drRect.left,drRect.top);
	}

	int i;
	int x,y;
	CString strTemp;

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));
	if(iN>0)
	{
		int MM=100;
		if(iN<=2048)
			MM=50;

		int iX1=0;
		int iX2=iN-1;
		if(draw.bSetZ)
		{
			iX1=draw.X1;
			iX2=draw.X2;

			if(iX2<iX1)
			{
				int iTemp=iX1;
				iX1=iX2;
				iX2=iTemp;
			}
			if(iX2==iX1)
			{
				iX1=iX1-300;
				iX2=iX2+300;
			}
		}
		if(iX1<0)
			iX1=0;
		if(iX2>=iN)
			iX2=iN-1;

		float fMax=100;
		for(i=iX1;i<iX2;i++)
		{
			if(fAD[i]>fMax)
				fMax=fAD[i];
		}
		fMax=g_SPEC.MAX_F(fMax);

		pDC->SetTextAlign(TA_CENTER);
		m_dcPlot.SelectObject(&Pen3);
		for(i=iX1;i<=iX2;i++)
		{
			if((iX2-iX1)>2000)
			{
				if(i%400!=0)
					continue;
			}
			else if((iX2-iX1)>1000)
			{
				if(i%200!=0)
					continue;
			}
			else if((iX2-iX1)>500)
			{
				if(i%100!=0)
					continue;
			}
			else if((iX2-iX1)>250)
			{
				if(i%50!=0)
					continue;
			}
			else
			{
				if(i%25!=0)
					continue;
			}
			x=(int)(drRect.left+(i-iX1)*drRect.Width()*1.0f/(iX2-iX1));
			if(bLine)
			{
				pDC->MoveTo(x,drRect.bottom);
				pDC->LineTo(x,drRect.top);
			}
			else
			{
				pDC->MoveTo(x,drRect.bottom);
				pDC->LineTo(x,drRect.bottom+iFontH/3);
			}
			strTemp.Format("%d",i);
			pDC->TextOut(x,drRect.bottom+iFontH/3,strTemp);

			strTemp.Format("%.1f",g_SPEC.SPEC_Pix2WL(i));
			pDC->TextOut(x,drRect.bottom+iFontH/3+iFontH,strTemp);
		}
		if(g_bEnglish)
		{
			pDC->TextOut(drRect.left-5*iFontW,drRect.bottom+iFontH/3,"Pixel");
			pDC->TextOut(drRect.left-5*iFontW,drRect.bottom+iFontH/3+iFontH,"Wavelength");
		}
		else
		{
			pDC->TextOut(drRect.left-5*iFontW,drRect.bottom+iFontH/3,"像素");
			pDC->TextOut(drRect.left-5*iFontW,drRect.bottom+iFontH/3+iFontH,"波长");
		}

		pDC->SetTextAlign(TA_RIGHT);
		for(i=0;i<=10;i++)
		{
			y=(int)(drRect.bottom-i*drRect.Height()*1.0f/10);
			if(bLine)
			{
				if(i<10)
				{
					pDC->MoveTo(drRect.right,y);
					pDC->LineTo(drRect.left,y);
				}
			}
			else
			{
				pDC->MoveTo(drRect.left-iFontH/3,y);
				pDC->LineTo(drRect.left,y);
			}

			if(i%2==0)
			{
				strTemp.Format("%.0f",0+fMax*i/10.0f);
				pDC->TextOut(drRect.left-iFontH/3,y-iFontH/2,strTemp);
			}
		}

		m_dcPlot.SelectObject(&Pen1);
		for(i=iX1;i<=iX2;i++)
		{
			x=(int)(drRect.left+(i-iX1)*drRect.Width()*1.0f/(iX2-iX1));
//			if(fAD[i]<=0)
//				fAD[i]=0;
			y=(int)(drRect.bottom-fAD[i]*drRect.Height()*1.0f/fMax);
			if(i==iX1)
				m_dcPlot.MoveTo(x,y);
			else
				m_dcPlot.LineTo(x,y);
		}

		if(draw.bMouse)
			draw.iCurSele=iX1+(int)((draw.pt.x-drRect.left)*(iX2-iX1)/drRect.Width()+0.5f);
		if(draw.iCurSele<=iX1)
			draw.iCurSele=iX1;
		if(draw.iCurSele>=iX2)
			draw.iCurSele=iX2;
		draw.bMouse=FALSE;

		if(fHalf!=0)
		{
			m_dcPlot.SelectObject(&PenS);
			x=(int)(drRect.left+(draw.fCurSele-iX1)*drRect.Width()*1.0f/(iX2-iX1));
			y=(int)(drRect.bottom-fAD[draw.iCurSele]*drRect.Height()*1.0f/fMax);
			m_dcPlot.MoveTo(x,y);
			m_dcPlot.LineTo(x,drRect.bottom);
		}
		else
		{
			m_dcPlot.SelectObject(&PenS);
			x=(int)(drRect.left+(draw.iCurSele-iX1)*drRect.Width()*1.0f/(iX2-iX1));
			y=(int)(drRect.bottom-fAD[draw.iCurSele]*drRect.Height()*1.0f/fMax);
			m_dcPlot.MoveTo(x,y);
			m_dcPlot.LineTo(x,drRect.bottom);
		}

		m_dcPlot.SelectObject(&Font2);
		if(!g_bHalfWL)
		{
			float fD=0;
			float fMaxN=0;
			int iMaxN=0;
			//计算平均值
			float fAve=0;
			for(i=iX1;i<iX2;i++)
			{
				fAve=fAve+fAD[i];
			}
			if(iX2 > iX1)
				fAve = fAve / (iX2 - iX1);

			y=(int)(drRect.bottom-fAve*drRect.Height()*1.0f/fMax);
			pDC->MoveTo(drRect.left,y);
			pDC->LineTo(drRect.right,y);
			
			float fTemp;
			for(i=iX1;i<iX2;i++)
			{
				fTemp=(float)fabs((fAve-fAD[i]));
				if(fMaxN<fTemp)
				{
					fMaxN=fTemp;
					iMaxN=i;
				}
				fD=fD+(float)(fTemp*fTemp);
			}
			if(iX2 > iX1)
				fD=(float)sqrt(fD/(iX2 - iX1));

			m_dcPlot.SetTextColor(RGB(255,0,255));
			
			m_dcPlot.SetTextAlign(TA_LEFT);
			CString sTemp,sStr;
			if(g_bEnglish == FALSE)
			{
				sStr.Format("平均值 :%.1f",fAve);
				sTemp.Format("  均方差 :%.2f",fD);
				sStr=sStr+sTemp;
				sTemp.Format("  最大值 :%.2f(%d)",fMaxN,iMaxN);
				sStr=sStr+sTemp;
			}
			else
			{
				sStr.Format("Avg :%.1f",fAve);
				sTemp.Format("  AveE :%.2f",fD);
				sStr=sStr+sTemp;
				sTemp.Format("  Max :%.2f(%d)",fMaxN,iMaxN);
				sStr=sStr+sTemp;
			}
			m_dcPlot.TextOut(drRect.left,(int)(0*iFontH),sStr);
		}
		if(g_bHalfWL)
		{
			float fHalfAD=0;
			float fMaxAD=fAD[iX1];
			int iMax=0;
			for(i=iX1;i<iX2;i++)
			{
				if(fMaxAD<fAD[i])
				{
					fMaxAD=fAD[i];
					iMax=i;
				}
			}
			fHalfAD=fMaxAD/2;
			int iHalfX1=0,iHalfX2=0;
			for(i=iX1+1;i<iMax;i++)
			{
				if(fAD[i]<fHalfAD&&fAD[i+1]>fHalfAD)
				{
					iHalfX1=i;
					break;
				}
			}
			for(i=iMax+1;i<iX2-1;i++)
			{
				if(fAD[i]>fHalfAD&&fAD[i+1]<fHalfAD)
				{
					iHalfX2=i;
					break;
				}
			}
			float fHalfX1=0,fHalfX2=0;
			if((fAD[iHalfX1+1]-fAD[iHalfX1])!=0)
				fHalfX1=(float)(iHalfX1+(fHalfAD-fAD[iHalfX1])/(fAD[iHalfX1+1]-fAD[iHalfX1]));
			if((fAD[iHalfX2+1]-fAD[iHalfX2])!=0)
				fHalfX2=(float)(iHalfX2+(fHalfAD-fAD[iHalfX2])/(fAD[iHalfX2+1]-fAD[iHalfX2]));
			
			m_dcPlot.SelectObject(&PenHalf);
			if(fMax<=0)
				fMax=1;
			y=(int)(drRect.bottom-fHalfAD*drRect.Height()*1.0f/fMax);
			m_dcPlot.MoveTo(drRect.left,y);
			m_dcPlot.LineTo(drRect.right,y);
			
			if(iX2==iX1)
				x=0;
			else
				x=(int)(drRect.left+(fHalfX1-iX1)*drRect.Width()*1.0f/(iX2-iX1));
			m_dcPlot.MoveTo(x,y);
			m_dcPlot.LineTo(x,drRect.bottom);
			
			pDC->SetTextAlign(TA_RIGHT);
			strTemp.Format("%.1f",fHalfX1);
			pDC->TextOut(x,y+iFontH/3,strTemp);
			strTemp.Format("%.1f",g_SPEC.SPEC_Pix2WL(iHalfX1));
			pDC->TextOut(x,y+iFontH/3+iFontH,strTemp);
			
			if(iX2==iX1)
				x=0;
			else
				x=(int)(drRect.left+(fHalfX2-iX1)*drRect.Width()*1.0f/(iX2-iX1));
			m_dcPlot.MoveTo(x,y);
			m_dcPlot.LineTo(x,drRect.bottom);

			pDC->SetTextAlign(TA_LEFT);
			strTemp.Format("%.1f",fHalfX2);
			pDC->TextOut(x,y+iFontH/3,strTemp);
			strTemp.Format("%.1f",g_SPEC.SPEC_Pix2WL(iHalfX2));
			pDC->TextOut(x,y+iFontH/3+iFontH,strTemp);
			if(g_bEnglish)
				strTemp.Format("FWHM:%.1f",g_SPEC.SPEC_Pix2WL(iHalfX2)-g_SPEC.SPEC_Pix2WL(iHalfX1));
			else
				strTemp.Format("半宽度%.1f",g_SPEC.SPEC_Pix2WL(iHalfX2)-g_SPEC.SPEC_Pix2WL(iHalfX1));
			pDC->TextOut(x,y+iFontH/3+iFontH*2,strTemp);
		}
	}
	if(fHalf!=0)
	{
		m_dcPlot.SelectObject(&PenHalf);
		int y=(int)(drRect.bottom-fHalf*drRect.Height()*1.0f/100);
		m_dcPlot.MoveTo(drRect.left,y);
		m_dcPlot.LineTo(drRect.right,y);
	}
	m_dcPlot.SelectObject(pOld);
	m_dcPlot.SelectObject(pOldFont);

	Invalidate();
}

void CDrawForMySpec::DrawSpectBW(CSpectData &spData, DATA_DRAW &drawData, CString strNote,BOOL bShow)
{
	GetClientRect(&m_rectPlot);
	m_nClientWidth=m_rectPlot.Width();
	m_nClientHeight=m_rectPlot.Height();
	
	if (m_dcPlot.GetSafeHdc() == NULL)
	{
		CClientDC dc(this);
		m_dcPlot.CreateCompatibleDC(&dc) ;
		m_bitmapPlot.CreateCompatibleBitmap(&dc, m_nClientWidth, m_nClientHeight) ;
		m_pbitmapOldPlot = m_dcPlot.SelectObject(&m_bitmapPlot) ;
	}
	CBrush BrushBack;
	BrushBack.CreateSolidBrush(RGB(0,128,255));
	m_dcPlot.FillRect(&m_rectPlot,&BrushBack);
	
	spData.DrawSpectBW(&m_dcPlot,m_rectPlot,drawData,strNote,FALSE,bShow);
	Invalidate();
}

void CDrawForMySpec::DrawSpect(CSpectData &spData, DATA_DRAW &drawData, CString strNote,BOOL bShow)
{
	GetClientRect(&m_rectPlot);
	m_nClientWidth=m_rectPlot.Width();
	m_nClientHeight=m_rectPlot.Height();
	
	if (m_dcPlot.GetSafeHdc() == NULL)
	{
		CClientDC dc(this);
		m_dcPlot.CreateCompatibleDC(&dc) ;
		m_bitmapPlot.CreateCompatibleBitmap(&dc, m_nClientWidth, m_nClientHeight) ;
		m_pbitmapOldPlot = m_dcPlot.SelectObject(&m_bitmapPlot) ;
	}
	CBrush BrushBack;
	BrushBack.CreateSolidBrush(RGB(0,128,255));
	m_dcPlot.FillRect(&m_rectPlot,&BrushBack);

	spData.DrawSpect(&m_dcPlot,m_rectPlot,drawData,strNote,FALSE,bShow, PH_NONE);
	Invalidate();
}

void CDrawForMySpec::DrawSDCM(CSpectData &spData, int iSeleK, int iSDCM1, int iSDCM2)
{
	GetClientRect(&m_rectPlot);
	m_nClientWidth=m_rectPlot.Width();
	m_nClientHeight=m_rectPlot.Height();
	
	if (m_dcPlot.GetSafeHdc() == NULL)
	{
		CClientDC dc(this);
		m_dcPlot.CreateCompatibleDC(&dc) ;
		m_bitmapPlot.CreateCompatibleBitmap(&dc, m_nClientWidth, m_nClientHeight) ;
		m_pbitmapOldPlot = m_dcPlot.SelectObject(&m_bitmapPlot) ;
	}
	int Wn=m_nClientWidth/20;
	int Hn=m_nClientHeight/20;
	CString sStr;
	CBrush m_BrushBack1;
//	m_BrushBack1.CreateSolidBrush(RGB(0,0,0));
	m_BrushBack1.CreateSolidBrush(RGB(0,128,255));

	m_dcPlot.FillRect(&m_rectPlot,&m_BrushBack1);
	m_dcPlot.SetBkMode(TRANSPARENT);
	m_dcPlot.SetTextColor(RGB(0,0,0));
	
	spData.ColorErr(&m_dcPlot,spData.m_bHaveData,m_rectPlot,spData.m_x,spData.m_y,iSeleK,iSDCM1,iSDCM2);
	Invalidate();
}

void CDrawForMySpec::DrawZONE(CWhiteZone &xyZone, int iSele)
{
	GetClientRect(&m_rectPlot);
	m_nClientWidth=m_rectPlot.Width();
	m_nClientHeight=m_rectPlot.Height();
	
	if (m_dcPlot.GetSafeHdc() == NULL)
	{
		CClientDC dc(this);
		m_dcPlot.CreateCompatibleDC(&dc) ;
		m_bitmapPlot.CreateCompatibleBitmap(&dc, m_nClientWidth, m_nClientHeight) ;
		m_pbitmapOldPlot = m_dcPlot.SelectObject(&m_bitmapPlot) ;
	}
	CBrush BrushBack;
	BrushBack.CreateSolidBrush(RGB(0,158,255));
	m_dcPlot.FillRect(&m_rectPlot,&BrushBack);

	xyZone.Draw(&m_dcPlot,m_rectPlot,iSele,FALSE,0);

	Invalidate();
}

void CDrawForMySpec::DrawC(COLORREF RgbColor)
{
	GetClientRect(&m_rectPlot);
	m_nClientWidth=m_rectPlot.Width();
	m_nClientHeight=m_rectPlot.Height();
	
	if (m_dcPlot.GetSafeHdc() == NULL)
	{
		CClientDC dc(this);
		m_dcPlot.CreateCompatibleDC(&dc) ;
		m_bitmapPlot.CreateCompatibleBitmap(&dc, m_nClientWidth, m_nClientHeight) ;
		m_pbitmapOldPlot = m_dcPlot.SelectObject(&m_bitmapPlot) ;
	}
	CBrush BrushBack;
	BrushBack.CreateSolidBrush(RgbColor);
	m_dcPlot.FillRect(&m_rectPlot,&BrushBack);

	Invalidate();
}

void CDrawForMySpec::DrawData(CSpectData &spData)
{
	GetClientRect(&m_rectPlot);
	m_nClientWidth=m_rectPlot.Width();
	m_nClientHeight=m_rectPlot.Height();
	
	if (m_dcPlot.GetSafeHdc() == NULL)
	{
		CClientDC dc(this);
		m_dcPlot.CreateCompatibleDC(&dc) ;
		m_bitmapPlot.CreateCompatibleBitmap(&dc, m_nClientWidth, m_nClientHeight) ;
		m_pbitmapOldPlot = m_dcPlot.SelectObject(&m_bitmapPlot) ;
	}
	CBrush BrushBack;
	BrushBack.CreateSolidBrush(CO_BK);
	m_dcPlot.FillRect(&m_rectPlot,&BrushBack);

	spData.DrawData(&m_dcPlot,m_rectPlot);
	Invalidate();
}

void CDrawForMySpec::DrawBk(COLORREF RgbColor)
{
	GetClientRect(&m_rectPlot);
	m_nClientWidth=m_rectPlot.Width();
	m_nClientHeight=m_rectPlot.Height();
	
	if (m_dcPlot.GetSafeHdc() == NULL)
	{
		CClientDC dc(this);
		m_dcPlot.CreateCompatibleDC(&dc) ;
		m_bitmapPlot.CreateCompatibleBitmap(&dc, m_nClientWidth, m_nClientHeight) ;
		m_pbitmapOldPlot = m_dcPlot.SelectObject(&m_bitmapPlot) ;
	}
	CBrush BrushBack;
	BrushBack.CreateSolidBrush(RgbColor);
	m_dcPlot.FillRect(&m_rectPlot,&BrushBack);
	m_dcPlot.SetBkMode(TRANSPARENT);

	Invalidate();
}


void CDrawForMySpec::DrawMyDebug_2()
{
	//为了调试而作图
	GetClientRect(&m_rectPlot);
	m_nClientWidth=m_rectPlot.Width();
	m_nClientHeight=m_rectPlot.Height();
	
	if (m_dcPlot.GetSafeHdc() == NULL)
	{
		CClientDC dc(this);
		m_dcPlot.CreateCompatibleDC(&dc) ;
		m_bitmapPlot.CreateCompatibleBitmap(&dc, m_nClientWidth, m_nClientHeight) ;
		m_pbitmapOldPlot = m_dcPlot.SelectObject(&m_bitmapPlot) ;
	}
	CBrush BrushBack;
	BrushBack.CreateSolidBrush(RGB(0,0,0));
	m_dcPlot.FillRect(&m_rectPlot,&BrushBack);

	CDC *pDC=&m_dcPlot;

	CFont Font1,Font2;
	CFont *pOldFont;

	int HH=(int)(m_rectPlot.Height()/20.0f+1);
	if(HH<18)
		HH=18;
	if(HH>20)
		HH=20;
	Font1.CreateFont(HH,0,0,0,700,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"MS Sans Serif");  
	Font2.CreateFont(20,0,0,0,600,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"MS Sans Serif");  


	CPen *pOld;
	CPen Pen1,Pen2,Pen3,PenS,PenHalf;
	Pen1.CreatePen(PS_SOLID,1,RGB(0,255,0));
	Pen2.CreatePen(PS_SOLID,1,RGB(255,255,255));
	Pen3.CreatePen(PS_DOT,1,RGB(255,255,255));
	PenS.CreatePen(PS_SOLID,1,RGB(0,255,255));
	PenHalf.CreatePen(PS_SOLID,1,RGB(255,0,0));
	pOld=m_dcPlot.SelectObject(&Pen2);
	pOldFont=m_dcPlot.SelectObject(&Font1);

	int iFontH,iFontW;
	TEXTMETRIC  tm;

	pDC->GetTextMetrics(&tm);
	iFontH=tm.tmHeight+tm.tmExternalLeading;
	iFontW=tm.tmAveCharWidth;

	CRect drRect;
	drRect.left  = m_rectPlot.left+10*iFontW;
	drRect.right = m_rectPlot.right-2*iFontW;
	drRect.top	 = m_rectPlot.top+1*iFontH;
	drRect.bottom= m_rectPlot.bottom-3*iFontH;

	pDC->MoveTo(drRect.left,drRect.top);
	pDC->LineTo(drRect.left,drRect.bottom);
	pDC->LineTo(drRect.right,drRect.bottom);
	pDC->LineTo(drRect.right,drRect.top);
	pDC->LineTo(drRect.left,drRect.top);

	CString strTemp;

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	int i,j;
	
	float fMaxPh = 0.0f;
	float fMinPh = 0.0f;
	float fZL[40];
	for(i=0;i<5;i++)
	{
		fZL[i]=(float)(i);
		for(j=0;j<501;j++)
		{		
			if(i==0&&j==0)
			{
				fMaxPh = m_fPL[i][j];
				fMinPh = m_fPL[i][j];
			}
			else
			{
				if(m_fPL[i][j]>fMaxPh)
					fMaxPh = m_fPL[i][j];
				if(m_fPL[i][j]<fMinPh)
					fMinPh = m_fPL[i][j];
			}
		}
	}
	
	if(fMaxPh<=0)
	{
		fMaxPh = 1.0f;
		fMinPh = 0.0f;
	}
	
	if(fMaxPh==fMinPh)
		fMaxPh = fMinPh*1.01f;
	
	int iYn=5;
	int iXn=400;
	int DN=1;
	for(i=0;i<4;i++)
	{
		for(j=0;j<500;j++)
		{
			if(m_fWL[j]>=380&&m_fWL[j]<=780)
			{
				int R,G,B;
				GetRGB(m_fPL[i][j]/fMaxPh,R,G,B);
				//			float fCurSpect=m_fWL[j];
				//			GetRGB(fCurSpect,R,G,B);
				
				CPen *pOld;
				CPen Pen;
				Pen.CreatePen(PS_SOLID,1,RGB(R,G,B));
				pOld=pDC->SelectObject(&Pen);
				
				CBrush Brush;
				Brush.CreateSolidBrush(RGB(R,G,B));
				CBrush * pOldBrush=pDC->SelectObject(&Brush);
				
				POINT polygon[4];
				
				polygon[0].x=(int)(drRect.left + (j-80)*drRect.Width()*1.0f/(iXn-1)+0.5f);
				polygon[0].y=(int)(drRect.top  + i*drRect.Height()*1.0f/(iYn-1)+0.5f);
				
				polygon[1].x=(int)(drRect.left + (j-80)*drRect.Width()*1.0f/(iXn-1)+0.5f);
				polygon[1].y=(int)(drRect.top  + (i+1)*drRect.Height()*1.0f/(iYn-1)+0.5f);
				
				polygon[2].x=(int)(drRect.left + ((j-80)+1)*drRect.Width()*1.0f/(iXn-1)+0.5f);
				polygon[2].y=(int)(drRect.top  + (i+1)*drRect.Height()*1.0f/(iYn-1)+0.5f);
				
				polygon[3].x=(int)(drRect.left + ((j-80)+1)*drRect.Width()*1.0f/(iXn-1)+0.5f);
				polygon[3].y=(int)(drRect.top  + i*drRect.Height()*1.0f/(iYn-1)+0.5f);
				
				pDC->Polygon(polygon,4);
				
				pDC->SelectObject(pOldBrush);
				pDC->SelectObject(pOld);
			}
		}
	}

	CRect mRect;
	mRect.left  = m_rectPlot.left+1*iFontW;
	mRect.right = m_rectPlot.left+8*iFontW;
	mRect.top	= m_rectPlot.top+1*iFontH;
	mRect.bottom= m_rectPlot.bottom-3*iFontH;
	
	iYn=81;
	for(i=0;i<iYn;i++)
	{
		int R,G,B;
		float fTemp=(float)(fMinPh/fMaxPh+i*1.0f/iYn);
		GetRGB(fTemp,R,G,B);
		
		CPen *pOld;
		CPen Pen;
		Pen.CreatePen(PS_SOLID,1,RGB(R,G,B));
		pOld=pDC->SelectObject(&Pen);
		
		CBrush Brush;
		Brush.CreateSolidBrush(RGB(R,G,B));
		CBrush * pOldBrush=pDC->SelectObject(&Brush);
		
		POINT polygon[4];
		
		polygon[0].x=(int)(mRect.left);
		polygon[0].y=(int)(mRect.bottom - i*drRect.Height()*1.0f/(iYn-1)+0.5f);
		
		polygon[1].x=(int)(mRect.left);
		polygon[1].y=(int)(mRect.bottom - (i+1)*drRect.Height()*1.0f/(iYn-1)+0.5f);
		
		polygon[2].x=(int)(mRect.right);
		polygon[2].y=(int)(mRect.bottom - (i+1)*drRect.Height()*1.0f/(iYn-1)+0.5f);
		
		polygon[3].x=(int)(mRect.right);
		polygon[3].y=(int)(mRect.bottom - i*drRect.Height()*1.0f/(iYn-1)+0.5f);
		
		pDC->Polygon(polygon,4);
		
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOld);
	}

	fMinPh=0;
	fMaxPh=(float)(164);
	for(i=0;i<=5;i++)
	{
		CString strTemp;
		strTemp.Format("%.2e",(fMaxPh-fMinPh)*i/5+fMinPh);
		strTemp.Replace("+00","+0");
		strTemp.Replace("-00","-0");
		pDC->TextOut(mRect.left,mRect.bottom-i*mRect.Height()/5,strTemp);
	}

	
	m_dcPlot.SelectObject(pOld);
	m_dcPlot.SelectObject(pOldFont);

	Invalidate();
/*
	GetClientRect(&m_rectPlot);
	m_nClientWidth=m_rectPlot.Width();
	m_nClientHeight=m_rectPlot.Height();
	
	if (m_dcPlot.GetSafeHdc() == NULL)
	{
		CClientDC dc(this);
		m_dcPlot.CreateCompatibleDC(&dc) ;
		m_bitmapPlot.CreateCompatibleBitmap(&dc, m_nClientWidth, m_nClientHeight) ;
		m_pbitmapOldPlot = m_dcPlot.SelectObject(&m_bitmapPlot) ;
	}
	CBrush BrushBack;
	BrushBack.CreateSolidBrush(RGB(0,0,0));
	m_dcPlot.FillRect(&m_rectPlot,&BrushBack);

	CDC *pDC=&m_dcPlot;

	CFont Font1,Font2;
	CFont *pOldFont;

	int HH=(int)(m_rectPlot.Height()/20.0f+1);
	if(HH<18)
		HH=18;
	if(HH>20)
		HH=20;
	Font1.CreateFont(HH,0,0,0,500,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"MS Sans Serif");  
	Font2.CreateFont(20,0,0,0,500,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"MS Sans Serif");  


	CPen *pOld;
	CPen Pen1,Pen2,Pen3,PenS,PenHalf;
	Pen1.CreatePen(PS_SOLID,1,RGB(0,255,0));
	Pen2.CreatePen(PS_SOLID,1,RGB(255,255,255));
	Pen3.CreatePen(PS_DOT,1,RGB(255,255,255));
	PenS.CreatePen(PS_SOLID,1,RGB(0,255,255));
	PenHalf.CreatePen(PS_SOLID,1,RGB(255,0,0));
	pOld=m_dcPlot.SelectObject(&Pen2);
	pOldFont=m_dcPlot.SelectObject(&Font1);

	int iFontH,iFontW;
	TEXTMETRIC  tm;

	pDC->GetTextMetrics(&tm);
	iFontH=tm.tmHeight+tm.tmExternalLeading;
	iFontW=tm.tmAveCharWidth;

	CRect drRect;
	drRect.left  = m_rectPlot.left+10*iFontW;
	drRect.right = m_rectPlot.right-2*iFontW;
	drRect.top	 = m_rectPlot.top+1*iFontH;
	drRect.bottom= m_rectPlot.bottom-3*iFontH;

	pDC->MoveTo(drRect.left,drRect.top);
	pDC->LineTo(drRect.left,drRect.bottom);
	pDC->LineTo(drRect.right,drRect.bottom);
	pDC->LineTo(drRect.right,drRect.top);
	pDC->LineTo(drRect.left,drRect.top);

	CString strTemp;

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	int i,j;
	
	float fMaxPh = 0.0f;
	float fMinPh = 0.0f;
	float fZL[40];
	for(i=0;i<40;i++)
	{
		if(i%5==0)
		{
			fZL[i]=(float)(i);
			for(j=0;j<501;j++)
			{		
				if(i==0&&j==0)
				{
					fMaxPh = m_fPL[i][j];
					fMinPh = m_fPL[i][j];
				}
				else
				{
					if(m_fPL[i][j]>fMaxPh)
						fMaxPh = m_fPL[i][j];
					if(m_fPL[i][j]<fMinPh)
						fMinPh = m_fPL[i][j];
				}
			}
		}
	}
	
	if(fMaxPh<=0)
	{
		fMaxPh = 1.0f;
		fMinPh = 0.0f;
	}
	
	if(fMaxPh==fMinPh)
		fMaxPh = fMinPh*1.01f;
	
	int iYn=40;
	int iXn=400;
	int DN=1;
	for(i=0;i<39;i++)
	{
		if(i%5==0)
		{
			for(j=0;j<500;j++)
			{
				if(m_fWL[j]>=380&&m_fWL[j]<=780)
				{
					int R,G,B;
					GetRGB(m_fPL[i][j]/fMaxPh,R,G,B);
					//			float fCurSpect=m_fWL[j];
					//			GetRGB(fCurSpect,R,G,B);
					
					CPen *pOld;
					CPen Pen;
					Pen.CreatePen(PS_SOLID,1,RGB(R,G,B));
					pOld=pDC->SelectObject(&Pen);
					
					CBrush Brush;
					Brush.CreateSolidBrush(RGB(R,G,B));
					CBrush * pOldBrush=pDC->SelectObject(&Brush);
					
					POINT polygon[4];
					
					polygon[0].x=(int)(drRect.left	 + (j-80)*drRect.Width()*1.0f/(iXn-1)+0.5f);
					polygon[0].y=(int)(drRect.top	 + i*drRect.Height()*1.0f/(iYn-1)+0.5f);
					
					polygon[1].x=(int)(drRect.left	 + (j-80)*drRect.Width()*1.0f/(iXn-1)+0.5f);
					polygon[1].y=(int)(drRect.top	 + (i+5)*drRect.Height()*1.0f/(iYn-1)+0.5f);
					
					polygon[2].x=(int)(drRect.left	 + ((j-80)+1)*drRect.Width()*1.0f/(iXn-1)+0.5f);
					polygon[2].y=(int)(drRect.top	 + (i+5)*drRect.Height()*1.0f/(iYn-1)+0.5f);
					
					polygon[3].x=(int)(drRect.left	 + ((j-80)+1)*drRect.Width()*1.0f/(iXn-1)+0.5f);
					polygon[3].y=(int)(drRect.top	 + i*drRect.Height()*1.0f/(iYn-1)+0.5f);
					
					pDC->Polygon(polygon,4);
					
					pDC->SelectObject(pOldBrush);
					pDC->SelectObject(pOld);
				}
			}

		}
	}

	CRect mRect;
	mRect.left  = m_rectPlot.left+1*iFontW;
	mRect.right = m_rectPlot.left+8*iFontW;
	mRect.top	= m_rectPlot.top+1*iFontH;
	mRect.bottom= m_rectPlot.bottom-3*iFontH;
	
	iYn=81;
	for(i=0;i<iYn;i++)
	{
		int R,G,B;
		float fTemp=(float)(fMinPh/fMaxPh+i*1.0f/iYn);
		GetRGB(fTemp,R,G,B);
		
		CPen *pOld;
		CPen Pen;
		Pen.CreatePen(PS_SOLID,1,RGB(R,G,B));
		pOld=pDC->SelectObject(&Pen);
		
		CBrush Brush;
		Brush.CreateSolidBrush(RGB(R,G,B));
		CBrush * pOldBrush=pDC->SelectObject(&Brush);
		
		POINT polygon[4];
		
		polygon[0].x=(int)(mRect.left);
		polygon[0].y=(int)(mRect.bottom - i*drRect.Height()*1.0f/(iYn-1)+0.5f);
		
		polygon[1].x=(int)(mRect.left);
		polygon[1].y=(int)(mRect.bottom - (i+1)*drRect.Height()*1.0f/(iYn-1)+0.5f);
		
		polygon[2].x=(int)(mRect.right);
		polygon[2].y=(int)(mRect.bottom - (i+1)*drRect.Height()*1.0f/(iYn-1)+0.5f);
		
		polygon[3].x=(int)(mRect.right);
		polygon[3].y=(int)(mRect.bottom - i*drRect.Height()*1.0f/(iYn-1)+0.5f);
		
		pDC->Polygon(polygon,4);
		
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOld);
	}

	for(i=0;i<=5;i++)
	{
		CString strTemp;
		strTemp.Format("%.1e",(fMaxPh-fMinPh)*i/5+fMinPh);
		strTemp.Replace("+00","+0");
		strTemp.Replace("-00","-0");
		pDC->TextOut(mRect.left,mRect.bottom-i*mRect.Height()/5,strTemp);
	}

	
	m_dcPlot.SelectObject(pOld);
	m_dcPlot.SelectObject(pOldFont);

	Invalidate();*/
}

void CDrawForMySpec::GetRGB(float fSpect, int &R, int &G, int &B)
{
	//380-650
	fSpect=(400+fSpect*250);
	if(fSpect<380)
		fSpect=380;
	if(fSpect>780)
		fSpect=780;
	
	int iSPE1=450;
	int iSPE2=520;
	int iSPE3=620;
	if(fSpect<=iSPE1)
	{
		R=0;
		G=0;
		B=(int)(255*(fSpect-380)/(iSPE1-380));
	}
	else if(fSpect<iSPE2)
	{
		float k1=255*2.0f/(iSPE2-iSPE1);
		float b1=-iSPE1*k1;
		int m1=(int)(k1*fSpect+b1);
		
		float k2=255*2.0f/(iSPE1-iSPE2);
		float b2=-iSPE2*k2;
		int m2=(int)(k2*fSpect+b2);
		if(m1>=255)
			m1=255;
		if(m1<=0)
			m1=0;
		if(m2>=255)
			m2=255;
		if(m2<=0)
			m2=0;
		R=0;
		G=m1;
		B=m2;
	}
	else if(fSpect<iSPE3)
	{
		float k1=255*2.0f/(iSPE3-iSPE2);
		float b1=-iSPE2*k1;
		int m1=(int)(k1*fSpect+b1);
		
		float k2=255*2.0f/(iSPE2-iSPE3);
		float b2=-iSPE3*k2;
		int m2=(int)(k2*fSpect+b2);
		if(m1>=255)
			m1=255;
		if(m1<=0)
			m1=0;
		if(m2>=255)
			m2=255;
		if(m2<=0)
			m2=0;
		R=m1;
		G=m2;
		B=0;
	}
	else
	{
		R=(int)((780-fSpect)*255/(780-iSPE3));
		G=0;
		B=0;
	}
}
