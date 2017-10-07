// SpectData.cpp: implementation of the CSpectData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "SpectData.h"
#include "math.h"
#include "ProcessData.h"
#include "Global_MySpec.h"
#include "ProcessData.h"
#include "ExGetColorParaDLL.h"
#include "MySpecDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImageObject g_ImageLogo;
CImageObject g_ImageCompany;

extern CString g_strPrTitle_E;
extern CString g_strPrTitle_C;

extern CString g_strCompany;
extern CString g_strAddr;

extern BOOL g_bHaveCRI;
extern BOOL g_bPrintLogo;
extern g_bPhoEffSetAuto;
extern float g_fSpectB1,g_fSpectB2,g_fSpectY1,g_fSpectY2;
extern BOOL g_bHavePhoEff;

int   CSpectData::m_iv2Num = 0;
float CSpectData::m_fv2WL[421];
float CSpectData::m_fv2VL[421];
extern CProcessData g_doData;

BOOL CSpectData::m_bPrintPh_ = FALSE;

float CSpectData::m_fSetDoWL = 0;
float CSpectData::m_fSetDoLimitAD = 0;

CSpectData::CSpectData()
{
	Init();
}

CSpectData::~CSpectData()
{

}

void CSpectData::DrawSpectBW(CDC *pDC,CRect mRect,DATA_DRAW &drawData,CString strNote,BOOL bPrint,BOOL bShow)
{
	CFont *pOldFont;
	CFont Font1Landscape,Font1Portrait;
	if(!bPrint)
	{
		int iTemp;
		iTemp=mRect.Height()/20;
		if(iTemp<16)
			iTemp=16;
		if(iTemp>32)
			iTemp=32;
		Font1Landscape.CreateFont(iTemp,0,0,0,500,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Courier New");  

		Font1Portrait.CreateFont(iTemp,0,900,-900,500,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Courier New");  
	}
	else
	{
		Font1Landscape.CreateFont(mRect.Height()/25,0,0,0,600,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Courier New");  

		Font1Portrait.CreateFont(mRect.Height()/25,0,900,-900,600,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Courier New");  
	}
	CPen *pOldPen;
	CPen Pen1,Pen2,Pen3,PenC;
	if(!bPrint)
	{
		Pen1.CreatePen(PS_SOLID,2,RGB(255,255,255));
		Pen2.CreatePen(PS_SOLID,1,RGB(255,255,255));
		Pen3.CreatePen(PS_DOT,1,RGB(255,255,255));
		PenC.CreatePen(PS_SOLID,1,RGB(255,255,0));
	}
	else
	{
		Pen1.CreatePen(PS_SOLID,4,RGB(0,0,0));
		Pen2.CreatePen(PS_SOLID,2,RGB(0,0,0));
		Pen3.CreatePen(PS_SOLID,2,RGB(0,0,0));
		PenC.CreatePen(PS_SOLID,2,RGB(0,0,0));
	}

	pOldFont=pDC->SelectObject(&Font1Landscape);
	pOldPen =pDC->SelectObject(&Pen1);
	pDC->SetBkMode(TRANSPARENT);

	int i;
	CString sTemp;
	CRect spRect;

	int iFontH,iFontW;
	TEXTMETRIC  tm;

	pDC->GetTextMetrics(&tm);
	iFontH=tm.tmHeight+tm.tmExternalLeading;
	iFontW=tm.tmAveCharWidth;

	spRect.left		= mRect.left+iFontW*6;
	spRect.right	= mRect.right-iFontW*3;
	spRect.top		= mRect.top+iFontH*2;
	spRect.bottom	= (int)(mRect.bottom-iFontH*2.5f);

	if(bPrint)
		pDC->Rectangle(mRect);
    if(!m_bHaveData)
	{
		m_fSpect1  = g_SPEC.T_SPECT1;
		m_fSpect2  = g_SPEC.T_SPECT2;
		m_fInterval= 1.0f;
	}

	int iMax;
	float fMax=Max(m_fRelSpect,iMax);

	fMax = (int)(ceil((fMax + 1) / 100)) * 100.0f;

	int iN = (int)((drawData.fSetWL2 - drawData.fSetWL1) / m_fInterval + 1.0f + 0.5f);
	int iB = (int)((drawData.fSetWL1 - m_fSpect1) / m_fInterval + 1.0f + 0.5f);

	if(m_bHaveData)
	{
		for(i = 0; i < iN; i++)
		{
			CPen Pen;
			CPen *pOld;
			int R,G,B;
			if(1)//(m_fSpect2-m_fSpect1)<100)
			{
				R=96;
				G=255;
				B=128;
			}
			if(!bPrint)
				Pen.CreatePen(PS_SOLID,1,RGB(R,G,B));
			else
				Pen.CreatePen(PS_SOLID,2,RGB(R,G,B));
			
			pOld=pDC->SelectObject(&Pen);
			
			int x,y;
			x = (int)(spRect.left + spRect.Width() * i / (iN - 1.0f) + 0.5f);
			y = (int)(spRect.bottom - spRect.Height() * m_fRelSpect[i + iB] / fMax + 0.5f);
			if(i==0)
				pDC->MoveTo(x,y);
			else
				pDC->LineTo(x,y);
			
			pDC->SelectObject(pOld);
		}

		if(1)
		{
			if(drawData.bMouse)
			{
				drawData.iCurSele=(int)((drawData.pt.x-spRect.left)*(iN-1.0f)/spRect.Width()+0.5f);
			}

			if(drawData.iCurSele<=0)
			{
				drawData.iCurSele=0;
			}

			if(drawData.iCurSele>=(iN-1))
			{
				drawData.iCurSele=iN-1;
			}
			
			//			drawData.bMouse=FALSE;
			if(drawData.iCurSele>=0&&drawData.iCurSele<iN&&!bPrint&&drawData.bShowCur)
			{
				int x=(int)(spRect.left+spRect.Width()*drawData.iCurSele/(iN-1.0f)+0.5f);
				int y=(int)(spRect.bottom-spRect.Height()*m_fRelSpect[drawData.iCurSele + iB]/fMax+0.5f);
				pDC->MoveTo(x,spRect.top);
				pDC->LineTo(x,spRect.bottom);
				
				pDC->SetTextAlign(TA_LEFT);
				CString strTemp;
				
				if(g_bEnglish)
				{
					strTemp.Format("Wavelength(nm):%5.1f",drawData.fSetWL1 +drawData.iCurSele*m_fInterval);
					pDC->TextOut(spRect.right-17*iFontW,(int)(spRect.top+0.0f*iFontH),strTemp);
					strTemp.Format("Intensity :%5.0f",m_fRelSpect[drawData.iCurSele + iB]);
					pDC->TextOut(spRect.right-17*iFontW,(int)(spRect.top+1.0f*iFontH),strTemp);
				}
				else
				{
					strTemp.Format("波长(nm) : %5.1f",drawData.fSetWL1 + drawData.iCurSele*m_fInterval);
					pDC->TextOut(spRect.right-16*iFontW,(int)(spRect.top+(0.0f-0.3f)*iFontH),strTemp);
					strTemp.Format("强度     : %5.0f",m_fRelSpect[drawData.iCurSele + iB]);
					pDC->TextOut(spRect.right-16*iFontW,(int)(spRect.top+(1.0f-0.3f)*iFontH),strTemp);
				}
			}
		}
	}

	pDC->MoveTo(spRect.left,spRect.top);
	pDC->LineTo(spRect.left,spRect.bottom);
	pDC->LineTo(spRect.right,spRect.bottom);

	if(!bPrint)
		pDC->SetTextColor(RGB(255,255,255));
	else
		pDC->SetTextColor(RGB(0,0,0));

	pDC->SetTextAlign(TA_CENTER);
	pDC->SelectObject(&Font1Landscape);
	pDC->SelectObject(&Pen2);

	for(i=0;i<5;i++)
	{
		sTemp.Format("%.1f",drawData.fSetWL1+(drawData.fSetWL2-drawData.fSetWL1)*i/4.0f);

		pDC->TextOut(spRect.left+spRect.Width()*i/4,spRect.bottom+iFontH/4,sTemp);

		pDC->MoveTo(spRect.left+spRect.Width()*i/4,spRect.bottom);
		pDC->LineTo(spRect.left+spRect.Width()*i/4,spRect.bottom+iFontH/4);
	}

	if(g_bEnglish)
		pDC->TextOut(spRect.left+spRect.Width()/2,spRect.bottom+iFontH*5/4,"Wavelength(nm)");
	else
		pDC->TextOut(spRect.left+spRect.Width()/2,spRect.bottom+iFontH*5/4,"波 长(nm)");

	/////////////////////////////
	if(!bPrint)
		pDC->SetTextColor(RGB(255,255,0));
	else
		pDC->SetTextColor(RGB(0,0,0));
	if(!m_bHaveData)
		strNote="";
	pDC->TextOut(spRect.right-10*iFontW,(int)(spRect.top-1.5f*iFontH),strNote);
	if(!bPrint)
		pDC->SetTextColor(RGB(255,255,255));
	else
		pDC->SetTextColor(RGB(0,0,0));
	/////////////////////////////

	pDC->SetTextAlign(TA_RIGHT);
	int iXN;
	if(m_iDataType==0)
		iXN=6;
	else
		iXN=5;
	for(i=0;i<=iXN;i++)
	{
		if(m_iDataType==0)
			sTemp.Format("%.1f",0+(fMax-0.0f)*i/iXN);
		else
			sTemp.Format("%.0f",0+(fMax-0.0f)*i/iXN);
		pDC->TextOut(spRect.left-iFontW*3/4,(int)(spRect.bottom-spRect.Height()*i/iXN-iFontH/2),sTemp);

		pDC->MoveTo(spRect.left,(int)(spRect.bottom-spRect.Height()*i/iXN));
		pDC->LineTo(spRect.left-iFontW/2,(int)(spRect.bottom-spRect.Height()*i/iXN));
	}
	pDC->SetTextAlign(TA_CENTER);
//	pDC->SelectObject(&Font1Portrait);

	if(g_bEnglish)
	{
		if(m_iDataType==TYPE_SCAN)
			pDC->TextOut((int)(spRect.left-iFontW*1.1f),(int)(spRect.top-1.5*iFontH),"Spectrum");
		else
			pDC->TextOut((int)(spRect.left-iFontW*5.5f),(int)(spRect.top-1.5*iFontH),"Intensity");
	}
	else
	{
		if(m_iDataType==TYPE_SCAN)
			pDC->TextOut((int)(spRect.left-iFontW*1.0f),(int)(spRect.top-1.5*iFontH),"相对光谱");
		else
			pDC->TextOut((int)(spRect.left-iFontW*3.5f),(int)(spRect.top-1.5*iFontH),"强度");
	}
	pDC->SelectObject(&Font1Landscape);

	pDC->SelectObject(&PenC);
	if(m_iDataType==TYPE_CHECK)
	{
		for(i=0;i<drawData.iChekStaN;i++)
		{
			int iCur=(int)((drawData.fCheckStaWL[i] - drawData.fSetWL1) * (iN - 1) / (drawData.fSetWL2-drawData.fSetWL1));
			int x;
			x=(int)(spRect.left+spRect.Width()*iCur / (iN - 1.0f)+0.5f);
			pDC->MoveTo(x,spRect.top);
			pDC->LineTo(x,spRect.bottom);
		}
	}
	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldPen);
}

void CSpectData::DrawSpect(CDC *pDC,CRect mRect,DATA_DRAW &drawData,CString strNote,BOOL bPrint,BOOL bShow, int iPhType)
{
	CFont *pOldFont;
	CFont Font1Landscape,Font1Portrait;
	if(!bPrint)
	{
		int iTemp;
		iTemp=mRect.Height()/20;
		if(iTemp<16)
			iTemp=16;
		if(iTemp>32)
			iTemp=32;
		Font1Landscape.CreateFont(iTemp,0,0,0,500,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Courier New");  

		Font1Portrait.CreateFont(iTemp,0,900,-900,500,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Courier New");  
	}
	else
	{
		Font1Landscape.CreateFont(mRect.Height()/25,0,0,0,600,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Courier New");  

		Font1Portrait.CreateFont(mRect.Height()/25,0,900,-900,600,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Courier New");  
	}
	CPen *pOldPen;
	CPen Pen1,Pen2,Pen3,PenC;
	if(!bPrint)
	{
		Pen1.CreatePen(PS_SOLID,2,RGB(255,255,255));
		Pen2.CreatePen(PS_SOLID,1,RGB(255,255,255));
		Pen3.CreatePen(PS_DOT,1,RGB(255,255,255));
		PenC.CreatePen(PS_SOLID,1,RGB(255,255,0));
	}
	else
	{
		Pen1.CreatePen(PS_SOLID,4,RGB(0,0,0));
		Pen2.CreatePen(PS_SOLID,2,RGB(0,0,0));
		Pen3.CreatePen(PS_SOLID,2,RGB(0,0,0));
		PenC.CreatePen(PS_SOLID,2,RGB(0,0,0));
	}

	pOldFont=pDC->SelectObject(&Font1Landscape);
	pOldPen =pDC->SelectObject(&Pen1);
	pDC->SetBkMode(TRANSPARENT);

	int i;
	CString sTemp;
	CRect spRect;

	int iFontH,iFontW;
	TEXTMETRIC  tm;

	pDC->GetTextMetrics(&tm);
	iFontH=tm.tmHeight+tm.tmExternalLeading;
	iFontW=tm.tmAveCharWidth;

	if(m_iDataType==TYPE_SCAN)
		spRect.left = mRect.left+iFontW*5;
	else
		spRect.left = mRect.left+iFontW*6;
	spRect.right  = mRect.right-iFontW*3;
	spRect.top    = mRect.top+iFontH*2;
	spRect.bottom = (int)(mRect.bottom-iFontH*2.5f);

	if(bPrint)
		pDC->Rectangle(mRect);
    if(!m_bHaveData)
	{
		m_fSpect1  = g_SPEC.T_SPECT1;
		m_fSpect2  = g_SPEC.T_SPECT2;
		m_fInterval= 1.0f;
	}

	int iMax;
	float fMax=Max(m_fRelSpect,iMax);
	float fMaxWL=m_fSpect1+iMax*m_fInterval;
	if(m_iDataType==TYPE_SCAN)
		fMax=1.2f;
	else
		fMax=(int)(ceil((fMax+1)/100))*100.0f;

	int iN;
	iN = (int)((m_fSpect2-m_fSpect1)/m_fInterval+1.0f+0.5f);
	iN = m_fRelSpect.GetSize();
	if(m_bHaveData && iN > 10)
	{
		int iDrawType=drawData.iDrawType;
		if(iDrawType == 0)
		{
			for(i = 0; i < iN; i++)
			{
				float fCurSpect = m_fSpect1 + m_fInterval * i;
				CPen Pen;
				CPen *pOld;
				int R,G,B;
				if(1)//(m_fSpect2-m_fSpect1)<100)
				{
					R=96;
					G=255;
					B=128;
				}
				if(!bPrint)
					Pen.CreatePen(PS_SOLID,1,RGB(R,G,B));
				else
					Pen.CreatePen(PS_SOLID,2,RGB(R,G,B));

				pOld=pDC->SelectObject(&Pen);

				int x,y;
				x = (int)(spRect.left + spRect.Width() * i / (iN - 1.0f) + 0.5f);
				y = (int)(spRect.bottom - spRect.Height() * m_fRelSpect[i] / fMax + 0.5f);
				if(i==0)
					pDC->MoveTo(x,y);
				else
					pDC->LineTo(x,y);

				pDC->SelectObject(pOld);
			}
		}
		if(iDrawType == 1)
		{
			for(i = 0; (i + 1) <= iN - 1; i++)
			{
				float fCurSpect=m_fSpect1+m_fInterval*i;
				int R,G,B;
				g_doData.GetRGB(fCurSpect,R,G,B);
				if((m_fSpect2-m_fSpect1)<100)
				{
					R=96;
					G=255;
					B=128;
				}

				CPen *pOld;
				CPen Pen;
				Pen.CreatePen(PS_SOLID,1,RGB(R,G,B));
				pOld=pDC->SelectObject(&Pen);

				CBrush Brush;
				Brush.CreateSolidBrush(RGB(R,G,B));
				CBrush * pOldBrush=pDC->SelectObject(&Brush);

				POINT polygon[4];

				polygon[0].x=(int)(spRect.left   + (i) * spRect.Width() * 1.0f/(iN -1) + 0.5f);
				polygon[0].y=(int)(spRect.bottom);
				polygon[1].x=(int)(spRect.left   + (i ) * spRect.Width() * 1.0f/(iN -1) + 0.5f);
				polygon[1].y=(int)(spRect.bottom - m_fRelSpect[i] * spRect.Height() / fMax + 0.5f);
				polygon[2].x=(int)(spRect.left   + (i + 1) * spRect.Width() * 1.0f/(iN -1) + 0.5f);
				polygon[2].y=(int)(spRect.bottom - m_fRelSpect[i + 1] * spRect.Height() / fMax + 0.5f);
				polygon[3].x=(int)(spRect.left +(i + 1) * spRect.Width() * 1.0f / (iN -1) + 0.5f);
				polygon[3].y=(int)(spRect.bottom);
			
				pDC->Polygon(polygon,4);

				pDC->SelectObject(pOldBrush);
				pDC->SelectObject(pOld);
			}
		}
		
		if(drawData.iB == drawData.iE)
		{
			if(drawData.bMouse)
				drawData.iCurSele=(int)((drawData.pt.x-spRect.left)*(iN-1.0f)/spRect.Width()+0.5f);
			if(drawData.iCurSele<=0)
				drawData.iCurSele=0;
			if(drawData.iCurSele>=(iN-1))
				drawData.iCurSele=iN-1;

//			drawData.bMouse=FALSE;
			if(drawData.iCurSele>=0&&drawData.iCurSele<iN&&!bPrint&&drawData.bShowCur)
			{
				int x=(int)(spRect.left+spRect.Width()*drawData.iCurSele/(iN-1.0f)+0.5f);
				int y=(int)(spRect.bottom-spRect.Height()*m_fRelSpect[drawData.iCurSele]/fMax+0.5f);
				pDC->MoveTo(x,spRect.top);
				pDC->LineTo(x,spRect.bottom);

				pDC->SetTextAlign(TA_LEFT);
				CString strTemp;

				if(g_bEnglish)
				{
					strTemp.Format("Wavelength(nm):%5.1f",m_fSpect1+drawData.iCurSele*m_fInterval);
					pDC->TextOut(spRect.right-17*iFontW,(int)(spRect.top+0.0f*iFontH),strTemp);
					if(m_iDataType==TYPE_SCAN)
						strTemp.Format("Spectrum :%5.4f",m_fRelSpect[drawData.iCurSele]);
					else
						strTemp.Format("Intensity :%5.0f",m_fRelSpect[drawData.iCurSele]);
					pDC->TextOut(spRect.right-17*iFontW,(int)(spRect.top+1.0f*iFontH),strTemp);
				}
				else
				{
					strTemp.Format("波长(nm) : %5.1f",m_fSpect1+drawData.iCurSele*m_fInterval);
					pDC->TextOut(spRect.right-16*iFontW,(int)(spRect.top+(0.0f-0.3f)*iFontH),strTemp);
					if(m_iDataType==TYPE_SCAN)
						strTemp.Format("相对光谱 : %5.4f",m_fRelSpect[drawData.iCurSele]);
					else
						strTemp.Format("强度     : %5.0f",m_fRelSpect[drawData.iCurSele]);
					pDC->TextOut(spRect.right-16*iFontW,(int)(spRect.top+(1.0f-0.3f)*iFontH),strTemp);
				}
			}
		}
		else
		{
			int iB,iE;
			if(drawData.bMouse)
			{
				iB=(int)((drawData.iB-spRect.left)*(iN-1.0f)/spRect.Width()+0.5f);
				iE=(int)((drawData.iE-spRect.left)*(iN-1.0f)/spRect.Width()+0.5f);
				if(iB>iE)
				{
					int iTemp;
					iTemp=iB;
					iB=iE;
					iE=iTemp;
				}
			}
			if(iB<=0)
				iB=0;
			if(iB>=(iN-1))
				iB=iN-1;
			if(iE<=0)
				iE=0;
			if(iE>=(iN-1))
				iE=iN-1;

//			drawData.bMouse=FALSE;
			if(!bPrint&&drawData.bShowCur)
			{
				int x;
				x=(int)(spRect.left+spRect.Width()*iB/(iN-1.0f)+0.5f);
				pDC->MoveTo(x,spRect.top);
				pDC->LineTo(x,spRect.bottom);
				x=(int)(spRect.left+spRect.Width()*iE/(iN-1.0f)+0.5f);
				pDC->MoveTo(x,spRect.top);
				pDC->LineTo(x,spRect.bottom);

				pDC->SetTextAlign(TA_LEFT);
				CString strTemp;

				float fEe;
				fEe=GetEe(iB,iE);
				if(g_bEnglish)
				{
					strTemp.Format("Ee:%smW",g_SPEC.sFormat(fEe,4));
					pDC->TextOut(spRect.right-17*iFontW,(int)(spRect.top+1.0f*iFontH),strTemp);
				}
				else
				{
					strTemp.Format("辐射通量:%smW",g_SPEC.sFormat(fEe,4));
					pDC->TextOut(spRect.right-16*iFontW,(int)(spRect.top+(1.0f-0.3f)*iFontH),strTemp);
				}

				float fWL1,fWL2;
				fWL1=(float)(iB*m_fInterval+m_fSpect1);
				fWL2=(float)(iE*m_fInterval+m_fSpect1);
				if(g_bEnglish)
				{
					strTemp.Format("WL:%.1f-%.1fnm",fWL1,fWL2);
					pDC->TextOut(spRect.right-16*iFontW,(int)(spRect.top+(0.0f-0.3f)*iFontH),strTemp);
				}
				else
				{
					strTemp.Format("波长:%.1f-%.1fnm",fWL1,fWL2);
					pDC->TextOut(spRect.right-16*iFontW,(int)(spRect.top+(0.0f-0.3f)*iFontH),strTemp);
				}
			}
		}
		if(bShow)
		{
			sTemp = "";
			if(iPhType == PH_F)
				sTemp.Format("1.0 = %.3emW/nm",m_fPlambda);
			if(iPhType == PH_E)
				sTemp.Format("1.0 = %.3emW/m2/nm",m_fPlambda);
			pDC->TextOut(spRect.right-18*iFontW,(int)(spRect.top-1.2f*iFontH),sTemp);
		}
	}

	pDC->MoveTo(spRect.left,spRect.top);
	pDC->LineTo(spRect.left,spRect.bottom);
	pDC->LineTo(spRect.right,spRect.bottom);

	if(!bPrint)
		pDC->SetTextColor(RGB(255,255,255));
	else
		pDC->SetTextColor(RGB(0,0,0));

	pDC->SetTextAlign(TA_CENTER);
	pDC->SelectObject(&Font1Landscape);
	pDC->SelectObject(&Pen2);

	if(1)//m_fInterval==0.1f)
	{
		for(i=0;i<5;i++)
		{
			if(m_fInterval==0.1f)
				sTemp.Format("%.0f",m_fSpect1+(m_fSpect2-m_fSpect1)*i/4.0f);
			else
				sTemp.Format("%.0f",m_fSpect1+(m_fSpect2-m_fSpect1)*i/4.0f);
			pDC->TextOut(spRect.left+spRect.Width()*i/4,spRect.bottom+iFontH/4,sTemp);

			pDC->MoveTo(spRect.left+spRect.Width()*i/4,spRect.bottom);
			pDC->LineTo(spRect.left+spRect.Width()*i/4,spRect.bottom+iFontH/4);
		}
	}
	else
	{
		float fTemp;
		for(fTemp=m_fSpect1;fTemp<=m_fSpect2;fTemp=fTemp+1.0f)
		{
			BOOL bTemp=fabs(fTemp-m_fSpect1)>50&&fabs(fTemp-m_fSpect2)>50;
			if(fTemp==m_fSpect1||fTemp==m_fSpect2||((int)(fTemp)%100==0))
			{
				if(bTemp||fTemp==m_fSpect1||fTemp==m_fSpect2)
				{
					sTemp.Format("%.0f",fTemp);
					pDC->TextOut((int)(spRect.left+spRect.Width()*(fTemp-m_fSpect1)/(m_fSpect2-m_fSpect1)),spRect.bottom+iFontH/4,sTemp);
				}
				pDC->MoveTo((int)(spRect.left+spRect.Width()*(fTemp-m_fSpect1)/(m_fSpect2-m_fSpect1)),spRect.bottom);
				pDC->LineTo((int)(spRect.left+spRect.Width()*(fTemp-m_fSpect1)/(m_fSpect2-m_fSpect1)),spRect.bottom+iFontH/4);
			}
		}
	}

	if(g_bEnglish)
		pDC->TextOut(spRect.left+spRect.Width()/2,spRect.bottom+iFontH*5/4,"Wavelength(nm)");
	else
		pDC->TextOut(spRect.left+spRect.Width()/2,spRect.bottom+iFontH*5/4,"波 长(nm)");

	/////////////////////////////
	if(!bPrint)
		pDC->SetTextColor(RGB(255,255,0));
	else
		pDC->SetTextColor(RGB(0,0,0));
	if(!m_bHaveData)
		strNote="";
	pDC->TextOut(spRect.right-10*iFontW,(int)(spRect.top-1.5f*iFontH),strNote);
	if(!bPrint)
		pDC->SetTextColor(RGB(255,255,255));
	else
		pDC->SetTextColor(RGB(0,0,0));
	/////////////////////////////

	pDC->SetTextAlign(TA_RIGHT);
	int iXN;
	if(m_iDataType==0)
		iXN=6;
	else
		iXN=5;
	for(i=0;i<=iXN;i++)
	{
		if(m_iDataType==0)
			sTemp.Format("%.1f",0+(fMax-0.0f)*i/iXN);
		else
			sTemp.Format("%.0f",0+(fMax-0.0f)*i/iXN);
		pDC->TextOut(spRect.left-iFontW*3/4,(int)(spRect.bottom-spRect.Height()*i/iXN-iFontH/2),sTemp);

		pDC->MoveTo(spRect.left,(int)(spRect.bottom-spRect.Height()*i/iXN));
		pDC->LineTo(spRect.left-iFontW/2,(int)(spRect.bottom-spRect.Height()*i/iXN));
	}
	pDC->SetTextAlign(TA_CENTER);
//	pDC->SelectObject(&Font1Portrait);

	if(g_bEnglish)
	{
		if(m_iDataType==TYPE_SCAN)
			pDC->TextOut((int)(spRect.left-iFontW*1.1f),(int)(spRect.top-1.5*iFontH),"Spectrum");
		else
			pDC->TextOut((int)(spRect.left-iFontW*5.5f),(int)(spRect.top-1.5*iFontH),"Intensity");
	}
	else
	{
		if(m_iDataType==TYPE_SCAN)
			pDC->TextOut((int)(spRect.left-iFontW*1.0f),(int)(spRect.top-1.5*iFontH),"相对光谱");
		else
			pDC->TextOut((int)(spRect.left-iFontW*3.5f),(int)(spRect.top-1.5*iFontH),"强度");
	}
	pDC->SelectObject(&Font1Landscape);

	pDC->SelectObject(&PenC);
	if(m_iDataType==TYPE_CHECK)
	{
		for(i=0;i<drawData.iChekStaN;i++)
		{
			int iCur=(int)((drawData.fCheckStaWL[i]-m_fSpect1)*(iN-1)/(m_fSpect2-m_fSpect1));
			int x;
			x=(int)(spRect.left+spRect.Width()*iCur/(iN-1.0f)+0.5f);
			pDC->MoveTo(x,spRect.top);
			pDC->LineTo(x,spRect.bottom);
		}
	}
	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldPen);
}

void CSpectData::ColorErr(CDC *pControlDC, BOOL bHave, CRect mRect, float x, float y, int iSeleK,int iSDCM1,int iSDCM2)
{
	CFont *pOldFont;
	CFont *pFont1;
	CFont *pFont2;
	pFont1 =new CFont;
	pFont2 =new CFont;

	const int X_NUM = 7;
	const int Y_NUM = 10;

	int HH = mRect.Height() / 18;
	if(HH < 16)
	{
		HH = 16;
	}

	if(HH > 32)
	{
		HH = 32;
	}

	pFont1->CreateFont(HH,0,0,0,500,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"MS Sans Serif");  

	pFont2->CreateFont(HH,0,0,0,500,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"MS Sans Serif");  
	
	pOldFont = pControlDC->SelectObject(pFont1);

	float ou[21];
	ou[16] = x;
	ou[17] = y;
	CPen *pOldPen;
	CPen  Pen1;
	CPen  Pen2;
	CPen  Pen3;
	CPen  Pen4;

	Pen1.CreatePen(PS_SOLID,2,RGB(255,255,255));
	Pen2.CreatePen(PS_SOLID,2,RGB(255,0,0));
	Pen3.CreatePen(PS_DOT,1,RGB(255,255,255));
	Pen4.CreatePen(PS_SOLID,1,RGB(0,255,255));

	int i,j;
	 
	//float g[6][3]={86.0f,-40.0f,45.0f,56.0f,-25.0f,23.0f,39.5f,-21.5f,26.0f,38.0f,-20.0f,25.0f,39.0f,-19.5f,27.5f,44.0f,-18.6f,27.0f};
	float mina;//xy[6][2]={0.313f,0.337f,0.346f,0.359f,0.38f,0.38f,0.409f,0.394f,0.440f,0.403f,0.463f,0.42f};
	//float sxy[6][2]={0.3f,0.32f,0.33f,0.340f,0.365f,0.360f,0.395f,0.375f,0.425f,0.380f,0.45f,0.4f};
	float a[1000],deltx[2],delty[2],r,sita;
	const float pi = 3.14159f;
	int stp = 5, sig = -1, xs = 473, ys = 225, xe = 473 + 150, ye = 225 + 200, scalex, scaley;
	//int f[6]={6500,5000,4000,3500,3000,2700};
	char scal[40];
	int Xinterval = (mRect.Width())  / (X_NUM + 2);
	int Yinterval = (mRect.Height()) / (Y_NUM + 2);
	xs = Xinterval;
	ys = Yinterval;
	xe = (X_NUM + 1) * Xinterval;
	ye = (Y_NUM + 1) * Yinterval;
	scalex = (int)(X_NUM * Xinterval / 0.03);
	scaley = (int)(Y_NUM * Yinterval / 0.04);

	int NN = g_doData.m_sdcm.GetSize();

	for(i = 0; i < NN; i++)
	{
		deltx[0] = ou[16] - g_doData.m_sdcm.GetAt(i)->m_fx;
		delty[0] = ou[17] - g_doData.m_sdcm.GetAt(i)->m_fy;

		a[i] = g_doData.m_sdcm.GetAt(i)->m_fg11 * deltx[0] * deltx[0]
			 + 2 * g_doData.m_sdcm.GetAt(i)->m_fg12 * deltx[0] * delty[0]
			 +     g_doData.m_sdcm.GetAt(i)->m_fg22 * delty[0] * delty[0];

		a[i] = (float)(sqrt(a[i]) * 100.0);
	}

	if(iSeleK == NN)
	{
		mina = a[0];
		sig  = 0;
		for(i = 0; i < NN; i++)
		{	
			if(a[i] < mina)
			{
				mina = a[i];
				sig  = i;
			}
		}
	}
	else
	{
		mina = a[iSeleK];
		sig  = iSeleK;
	}
	pOldPen = pControlDC->SelectObject(&Pen1);

	pControlDC->MoveTo(mRect.Width() /(X_NUM + 2),				mRect.Height() / (Y_NUM + 2));
	pControlDC->LineTo(mRect.Width() /(X_NUM + 2),				mRect.Height() * (Y_NUM + 1) / (Y_NUM + 2));
	pControlDC->LineTo(mRect.Width() *(X_NUM + 1) / (X_NUM + 2),mRect.Height() * (Y_NUM + 1) / (Y_NUM + 2));
	pControlDC->LineTo(mRect.Width() *(X_NUM + 1) / (X_NUM + 2),mRect.Height() / (Y_NUM + 2));
	pControlDC->LineTo(mRect.Width() /(X_NUM + 2),				mRect.Height() / (Y_NUM + 2));

    pControlDC->SelectObject(&Pen3);
	for(i = 1; i < X_NUM; i++)
	{
		pControlDC->MoveTo(mRect.Width()*(i+1)/(X_NUM + 2), mRect.Height() / (Y_NUM + 2));
		pControlDC->LineTo(mRect.Width()*(i+1)/(X_NUM + 2), mRect.Height() * (Y_NUM + 1) / (Y_NUM + 2));
	}

	for(i = 1; i < Y_NUM; i++)
	{
		pControlDC->MoveTo(mRect.Width() * 1 / (X_NUM + 2),				mRect.Height() * (i + 1) / (Y_NUM + 2));
		pControlDC->LineTo(mRect.Width() * (X_NUM + 1) / (X_NUM + 2),	mRect.Height() * (i + 1) / (Y_NUM + 2));
	}

	if(g_bEnglish)
	{
		sprintf(scal,"   %5.1f SDCM", mina);
	}
	else
	{
		sprintf(scal,"色容差: %5.1f SDCM", mina);
	}
	pControlDC->SetTextColor(RGB(255, 255, 255));

	if(bHave)
	{
		pControlDC->TextOut(mRect.Width()/6,(int)(mRect.Height()*0.2/10),scal);
	}

	i = sig;

	sprintf(scal, "x=%.3f y=%.3f %s",
		g_doData.m_sdcm.GetAt(i)->m_fx,
		g_doData.m_sdcm.GetAt(i)->m_fy,
		g_doData.m_sdcm.GetAt(i)->m_strName);

	pControlDC->TextOut(mRect.Width()/6 - 10,mRect.Height() * (8 + 1) / 10 + 5,scal);
	pControlDC->SelectObject(&Pen4);

	sita = (float)(pi / 180.0);
	xe   = xs + (int)((g_doData.m_sdcm.GetAt(i)->m_fx - g_doData.m_sdcm.GetAt(i)->m_fxs) * scalex);
	ye   = ys + (int)(Yinterval * 8 - (g_doData.m_sdcm.GetAt(i)->m_fy - g_doData.m_sdcm.GetAt(i)->m_fys) * scaley);
	pControlDC->Ellipse(xe - 3, ye - 3, xe + 3, ye + 3);

	for(j = 1; j < 360; j+=stp)
	{
		r = (float)sqrt(g_doData.m_sdcm.GetAt(i)->m_fg11*(1+cos((2*j-2*stp)*sita))/2
			+g_doData.m_sdcm.GetAt(i)->m_fg12*sin((2*j-2*stp)*sita)
			+g_doData.m_sdcm.GetAt(i)->m_fg22*(1-cos((2*j-2*stp)*sita))/2);
		r = (float)(0.01f*iSDCM1/r);

		deltx[0] = (float)(r*cos((j-stp)*sita));
		delty[0] = (float)(r*sin((j-stp)*sita));

		r = (float)sqrt(g_doData.m_sdcm.GetAt(i)->m_fg11*(1+cos(2*j*sita))/2
			+g_doData.m_sdcm.GetAt(i)->m_fg12*sin(2*j*sita)
			+g_doData.m_sdcm.GetAt(i)->m_fg22*(1-cos(2*j*sita))/2);

		r = (float)(0.01f*iSDCM1/r);

		deltx[1] = (float)(r*cos(j*sita));
		delty[1] = (float)(r*sin(j*sita));

		pControlDC->MoveTo(xe+(int)(deltx[0] * scalex), ye - (int)(delty[0]*scaley));
		pControlDC->LineTo(xe+(int)(deltx[1] * scalex), ye - (int)(delty[1]*scaley));

		if(j % 2)
		{
			r = (float)sqrt(g_doData.m_sdcm.GetAt(i)->m_fg11*(1+cos((2*j-2*stp)*sita))/2
				+g_doData.m_sdcm.GetAt(i)->m_fg12*sin((2*j-2*stp)*sita)
				+g_doData.m_sdcm.GetAt(i)->m_fg22*(1-cos((2*j-2*stp)*sita))/2);
			r = (float)(0.01f*iSDCM2/r);

			deltx[0] = (float)(r*cos((j-stp)*sita));
			delty[0] = (float)(r*sin((j-stp)*sita));

			r = (float)sqrt(g_doData.m_sdcm.GetAt(i)->m_fg11*(1+cos(2*j*sita))/2
				+g_doData.m_sdcm.GetAt(i)->m_fg12*sin(2*j*sita)
				+g_doData.m_sdcm.GetAt(i)->m_fg22*(1-cos(2*j*sita))/2);
			r = (float)(0.01f*iSDCM2/r);

			deltx[1] = (float)(r*cos(j*sita));
			delty[1] = (float)(r*sin(j*sita));

			pControlDC->MoveTo(xe + (int)(deltx[0] * scalex), ye - (int)(delty[0] * scaley));
			pControlDC->LineTo(xe + (int)(deltx[1] * scalex), ye - (int)(delty[1] * scaley));
		}
	}
	if(ou[16] < g_doData.m_sdcm.GetAt(i)->m_fxs)
	{
		deltx[0] = g_doData.m_sdcm.GetAt(i)->m_fxs;
	}
	else if(ou[16] > (g_doData.m_sdcm.GetAt(i)->m_fxs+0.03))
	{
		deltx[0] = (float)(g_doData.m_sdcm.GetAt(i)->m_fxs+0.03);
	}
	else
	{
		deltx[0] = ou[16];
	}

	if(ou[17] < g_doData.m_sdcm.GetAt(i)->m_fys)
	{
		delty[0] = g_doData.m_sdcm.GetAt(i)->m_fys;
	}
	else if(ou[17] > (g_doData.m_sdcm.GetAt(i)->m_fys + 0.04))
	{
		delty[0] = (float)(g_doData.m_sdcm.GetAt(i)->m_fys + 0.04);
	}
	else
	{
		delty[0] = ou[17];
	}

	xs = xs + (int)((deltx[0] - g_doData.m_sdcm.GetAt(i)->m_fxs) * scalex);
	ys = ys + (int)(Yinterval * 8 - (delty[0] - g_doData.m_sdcm.GetAt(i)->m_fys) * scaley);
	pControlDC->SelectObject(&Pen2);

	if(bHave)
	{
		pControlDC->MoveTo(xs - 5, ys);
		pControlDC->LineTo(xs + 5, ys);
		pControlDC->MoveTo(xs, ys - 5);
		pControlDC->LineTo(xs, ys + 5);
	}

	pControlDC->SelectObject(pOldPen);
	pControlDC->SelectObject(pOldFont);
	delete pFont1;
	delete pFont2;
}

void CSpectData::DrawData(CDC *pDC, CRect mRect)
{
	CFont *pOldFont;
	CFont Font1;
	CFont Font2;

	int HH=(int)(mRect.Height()/8.0f+1);
	if(HH<18)
		HH=18;
	if(HH>32)
		HH=32;
	Font1.CreateFont(HH,0,0,0,500,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"MS Sans Serif");  

	Font2.CreateFont(HH,0,0,0,500,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"MS Sans Serif");  
	
	CPen  *pOldPen;
	CPen  Pen1;
	CPen  Pen2;
	CPen  Pen3;

	Pen1.CreatePen(PS_SOLID,1,RGB(255,255,0));
	Pen2.CreatePen(PS_SOLID,1,RGB(255,0,0));
	Pen3.CreatePen(PS_SOLID,1,RGB(255,255,255));

	int Wn=mRect.Width()/22;
	int Hn=mRect.Height()/22;
	CString sStr;
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));
	pOldFont=pDC->SelectObject(&Font1);
	pOldPen=pDC->SelectObject(&Pen1);
    

	pDC->SetTextAlign(TA_CENTER);	
	pDC->SetTextAlign(TA_LEFT);	
	pDC->TextOut((int)(0.6*Wn),2*Hn,"x =");
	pDC->TextOut((int)(0.6*Wn),6*Hn,"y =");
	pDC->TextOut((int)(0.6*Wn),10*Hn,"u'=");
	pDC->TextOut((int)(0.6*Wn),14*Hn,"v'=");
	pDC->TextOut((int)(0.4*Wn),18*Hn,"CCT:");

	if(g_bEnglish)
	{
		pDC->TextOut((int)(3.9*Wn),2*Hn,"Domi.WL:");
		pDC->TextOut((int)(3.9*Wn),6*Hn,"Purity:");
		pDC->TextOut((int)(3.9*Wn),10*Hn,"PeakWL:");
		pDC->TextOut((int)(3.9*Wn),14*Hn,"FWHM:");
		pDC->TextOut((int)(3.9*Wn),18*Hn,"RedRatio:");
	}
	else
	{
		pDC->TextOut((int)(3.9*Wn),2*Hn,"主波长:");
		pDC->TextOut((int)(3.9*Wn),6*Hn,"色纯度:");
		pDC->TextOut((int)(3.9*Wn),10*Hn,"峰值波长:");
		pDC->TextOut((int)(3.9*Wn),14*Hn,"半宽度:");
		pDC->TextOut((int)(3.9*Wn),18*Hn,"红色比:");
	}

	if(g_bEnglish)
		pDC->TextOut((int)(9.5*Wn),2*Hn,"Render Index");
	else
		pDC->TextOut((int)(9.5*Wn),2*Hn,"显色性指数");
	pDC->TextOut((int)(9.5*Wn),(int)(6.5*Hn),"Ra =");

	CString strPH,strUnit;
	int iPhType,iPhType_E;
	if(g_SPEC.m_iTestType==1||g_SPEC.m_iTestType==0)
	{
		iPhType=PH_F;
		iPhType_E=PH_Fe;
	}
	if(g_SPEC.m_iTestType==2)
	{
		iPhType=PH_E;
		iPhType_E=PH_Ee;
	}
	if(g_SPEC.m_iTestType==3)
	{
		iPhType=PH_I;
		iPhType_E=PH_Ie;
	}
	if(g_SPEC.m_iTestType==4)
	{
		iPhType=PH_L;
		iPhType_E=PH_Le;
	}
	strPH=PH_Name(m_iLamp,iPhType,strUnit,TRUE)+" = ";
	pDC->TextOut((int)(9.0*Wn),(int)(12.5*Hn),strPH);
	CString strPHe,strUnite;
	strPHe=PH_Name(m_iLamp,iPhType_E,strUnite,TRUE)+" = ";
	pDC->TextOut((int)(9.0*Wn),(int)(15.5*Hn),strPHe);

	sStr.Format("(%.0f-%.0fnm)",m_fE_SP1,m_fE_SP2);
	pDC->TextOut((int)(9.5*Wn),(int)(18.5*Hn),sStr);

	pDC->TextOut(15*Wn,(int)(2*Hn),"R1 =");
	pDC->TextOut(15*Wn,(int)(6*Hn),"R2 =");
	pDC->TextOut(15*Wn,(int)(10*Hn),"R3 =");
	pDC->TextOut(15*Wn,(int)(14*Hn),"R4 =");
	pDC->TextOut(15*Wn,(int)(18*Hn),"R5 =");
	pDC->TextOut((int)(17.3*Wn),(int)(2*Hn),"R6   =");
	pDC->TextOut((int)(17.3*Wn),(int)(6*Hn),"R7   =");
	pDC->TextOut((int)(17.3*Wn),(int)(10*Hn),"R8   =");
	pDC->TextOut((int)(17.3*Wn),(int)(14*Hn),"R9   =");
	pDC->TextOut((int)(17.3*Wn),(int)(18*Hn),"R10 =");
	pDC->TextOut((int)(19.7*Wn),(int)(2*Hn),"R11 =");
	pDC->TextOut((int)(19.7*Wn),(int)(6*Hn),"R12 =");
	pDC->TextOut((int)(19.7*Wn),(int)(10*Hn),"R13 =");
	pDC->TextOut((int)(19.7*Wn),(int)(14*Hn),"R14 =");
	pDC->TextOut((int)(19.7*Wn),(int)(18*Hn),"R15 =");


	pDC->SetTextAlign(TA_RIGHT);
	if(m_bHaveData)
	{
		pDC->SetTextAlign(TA_LEFT);
		pDC->SelectObject(&Font2);
		pDC->SetTextColor(RGB(255,255,255));
		if(m_bHaveColorPara)
			sStr.Format("%.1fnm",m_fMainlambda);
		else
			sStr="--";
		pDC->TextOut((int)(6.5*Wn),2*Hn,sStr);
		if(m_bHaveColorPara)
			sStr.Format("%.1f%%",m_fPurity);
		else
			sStr="--";
		pDC->TextOut((int)(6.5*Wn),6*Hn,sStr);
		sStr.Format("%.1fnm",m_fMaxlambda);
		pDC->TextOut((int)(6.5*Wn),10*Hn,sStr);
		sStr.Format("%.1fnm",m_fHalflambda);
		pDC->TextOut((int)(6.5*Wn),14*Hn,sStr);

		if(m_bHaveColorPara)
			sStr.Format("%.1f%%",m_fRedRatio);
		else
			sStr="--";
		pDC->TextOut((int)(6.5*Wn),18*Hn,sStr);

		pDC->SetTextAlign(TA_RIGHT);
		if(m_bHaveColorPara)
			sStr.Format("%.4f",m_x);
		else
			sStr="--";
		pDC->TextOut(3*Wn,2*Hn,sStr);
		if(m_bHaveColorPara)
			sStr.Format("%.4f",m_y);
		else
			sStr="--";
		pDC->TextOut(3*Wn,6*Hn,sStr);
		if(m_bHaveColorPara)
			sStr.Format("%.4f",m_u);
		else
			sStr="--";
		pDC->TextOut(3*Wn,10*Hn,sStr);
		if(m_bHaveColorPara)
			sStr.Format("%.4f",m_v);
		else
			sStr="--";
		pDC->TextOut(3*Wn,14*Hn,sStr);
		if(m_bHaveColorPara)
			sStr.Format("%.0fK",m_fCCT);
		else
			sStr="--";
		pDC->TextOut(3*Wn,18*Hn,sStr);

		if(m_bHaveColorPara)
			sStr.Format("%.1f",m_fRa);
		else
			sStr.Format("--",m_fRa);
		pDC->TextOut(12*Wn,(int)(6.5*Hn),sStr);

		if(m_bTestPH)
		{
			if(m_bHaveColorPara)
				sStr=g_SPEC.sFormat(m_fPH,5)+strUnit;
			else
				sStr="--";
			pDC->TextOut((int)(14.5*Wn),(int)(12.5*Hn),sStr);
		}
		if(m_bHaveData)
		{
			sStr=g_SPEC.sFormat(m_fPh_e*1000,5)+strUnite;
			pDC->TextOut((int)(14.5*Wn),(int)(15.5*Hn),sStr);
		}

		if(m_bHaveColorPara)
			sStr.Format("%.0f",m_fRi[0]);
		else
			sStr="--";
		pDC->TextOut((int)(16.8*Wn),(int)(2*Hn),sStr);
		if(m_bHaveColorPara)
			sStr.Format("%.0f",m_fRi[1]);
		else
			sStr="--";
		pDC->TextOut((int)(16.8*Wn),(int)(6*Hn),sStr);
		if(m_bHaveColorPara)
			sStr.Format("%.0f",m_fRi[2]);
		else
			sStr="--";
		pDC->TextOut((int)(16.8*Wn),(int)(10*Hn),sStr);
		if(m_bHaveColorPara)
			sStr.Format("%.0f",m_fRi[3]);
		else
			sStr="--";
		pDC->TextOut((int)(16.8*Wn),(int)(14*Hn),sStr);
		if(m_bHaveColorPara)
			sStr.Format("%.0f",m_fRi[4]);
		else
			sStr="--";
		pDC->TextOut((int)(16.8*Wn),(int)(18*Hn),sStr);
		if(m_bHaveColorPara)
			sStr.Format("%.0f",m_fRi[5]);
		else
			sStr="--";
		pDC->TextOut((int)(19.4*Wn),(int)(2*Hn),sStr);
		if(m_bHaveColorPara)
			sStr.Format("%.0f",m_fRi[6]);
		else
			sStr="--";
		pDC->TextOut((int)(19.4*Wn),(int)(6*Hn),sStr);
		if(m_bHaveColorPara)
			sStr.Format("%.0f",m_fRi[7]);
		else
			sStr="--";
		pDC->TextOut((int)(19.4*Wn),(int)(10*Hn),sStr);
		if(m_bHaveColorPara)
			sStr.Format("%.0f",m_fRi[8]);
		else
			sStr="--";
		pDC->TextOut((int)(19.4*Wn),(int)(14*Hn),sStr);
		if(m_bHaveColorPara)
			sStr.Format("%.0f",m_fRi[9]);
		else
			sStr="--";
		pDC->TextOut((int)(19.4*Wn),(int)(18*Hn),sStr);
		if(m_bHaveColorPara)
			sStr.Format("%.0f",m_fRi[10]);
		else
			sStr="--";
		pDC->TextOut((int)(21.8*Wn),(int)(2*Hn),sStr);
		if(m_bHaveColorPara)
			sStr.Format("%.0f",m_fRi[11]);
		else
			sStr="--";
		pDC->TextOut((int)(21.8*Wn),(int)(6*Hn),sStr);
		if(m_bHaveColorPara)
			sStr.Format("%.0f",m_fRi[12]);
		else
			sStr="--";
		pDC->TextOut((int)(21.8*Wn),(int)(10*Hn),sStr);
		if(m_bHaveColorPara)
			sStr.Format("%.0f",m_fRi[13]);
		else
			sStr="--";
		pDC->TextOut((int)(21.8*Wn),(int)(14*Hn),sStr);
		if(m_bHaveColorPara)
			sStr.Format("%.0f",m_fRi[14]);
		else
			sStr="--";
		pDC->TextOut((int)(21.8*Wn),(int)(18*Hn),sStr);
	}
	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldPen);
}

float CSpectData::Max(CArray<float,float> &f,int& iMax)
{
	float fMax=0;
	iMax=0;
	int iN=f.GetSize();
	for(int i=0;i<iN;i++)
	{
		if(f[i]>fMax)
		{
			fMax=f[i];
			iMax=i;
		}
	}
	return fMax;
}

void CSpectData::Serialize(CArchive &ar)
{
	CString strVer;
	int iN,i;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		strVer="NH_GCS_300_V101";
		ar<<strVer;

		ar<<m_bTestF;
		ar<<m_fVF;  //V
		ar<<m_fIF;  //mA
		ar<<m_fPow;
		ar<<m_fPF;

		ar<<m_iTestType;
		ar<<m_bTestPH;
		ar<<m_fDistance;
		ar<<m_fPH;

		ar<<m_bHaveData;
		ar<<m_bHaveColorPara;

		ar<<m_strModel;
		ar<<m_strNumber;
		ar<<m_strFactory;
		ar<<m_strT;
		ar<<m_strH;
		ar<<m_strTester;
		ar<<m_strDate;
		ar<<m_strRemark;

		ar<<m_iDataType; 
		ar<<m_fIntTime;
		ar<<m_fInterval;
		ar<<m_fSpect1<<m_fSpect2;
		iN=m_fRelSpect.GetSize();
		ar<<iN;
		for(i=0;i<iN;i++)
			ar<<m_fRelSpect[i]; 
		
		ar<<m_nADW;
		ar<<m_fIp;

		ar<<m_fPh;
		ar<<m_fPh_e;

		ar<<m_x<<m_y;
		ar<<m_u<<m_v;
		ar<<m_fCCT;
		ar<<m_fRedRatio;
		ar<<m_fMainlambda;
		ar<<m_fMaxlambda;
		ar<<m_fPurity;
		ar<<m_fHalflambda;
		ar<<m_fRa;
		for(i=0;i<15;i++)
			ar<<m_fRi[i];

		ar<<m_fEnTMP;

		ar<<m_strName;
		ar<<m_iLamp;

		ar<<m_fPlambda;
		ar<<m_fKuv;
		ar<<m_fK1;
		ar<<m_fK2;

		ar<<m_strAngleView;

		ar<<m_fdc;
		ar<<m_strAddr;
		ar<<m_strCompany;

		ar<<m_strSampleName;
		ar<<m_strSampleState;
		ar<<m_strSampleStandard;

		ar<<m_fBlueRatio;
		ar<<m_fGreenRatio;
		ar<<m_strColorCorrectStr;
		ar<<m_strFilter;

		ar << m_strSN;
	}
	else
	{
		// TODO: add loading code here
		ar>>strVer;
		if(strVer!="NH_GCS_300_V100" && strVer!="NH_GCS_300_V101")
		{
			if(g_bEnglish)
				AfxMessageBox("Can not open this file!\n"+strVer,MB_ICONSTOP);
			else
				AfxMessageBox("打开文件类型错误!\n"+strVer,MB_ICONSTOP);
			return;
		}
		ar>>m_bTestF;
		ar>>m_fVF;  //V
		ar>>m_fIF;  //mA
		ar>>m_fPow;
		ar>>m_fPF;

		ar>>m_iTestType;
		ar>>m_bTestPH;
		ar>>m_fDistance;
		ar>>m_fPH;

		ar>>m_bHaveData;
		ar>>m_bHaveColorPara;

		ar>>m_strModel;
		ar>>m_strNumber;
		ar>>m_strFactory;
		ar>>m_strT;
		ar>>m_strH;
		ar>>m_strTester;
		ar>>m_strDate;
		ar>>m_strRemark;

		ar>>m_iDataType;
		ar>>m_fIntTime;
		ar>>m_fInterval;
		ar>>m_fSpect1>>m_fSpect2;
		ar>>iN;
		m_fRelSpect.RemoveAll();
		for(i=0;i<iN;i++)
		{
			float fTemp;
			ar>>fTemp;
			if(fTemp>1)
				fTemp=1;
			m_fRelSpect.Add(fTemp); 
		}

		ar>>m_nADW;
		ar>>m_fIp;
		
		ar>>m_fPh;
		ar>>m_fPh_e;

		ar>>m_x>>m_y;
		ar>>m_u>>m_v;

		m_u=(4*m_x)/(-2*m_x+12*m_y+3);
		m_v=(9*m_y)/(-2*m_x+12*m_y+3);
		ar>>m_fCCT;
		ar>>m_fRedRatio;
		ar>>m_fMainlambda;
		ar>>m_fMaxlambda;
		ar>>m_fPurity;
		ar>>m_fHalflambda;
		ar>>m_fRa;
		for(i=0;i<15;i++)
			ar>>m_fRi[i];

		ar>>m_fEnTMP;

		ar>>m_strName;
		ar>>m_iLamp;

		ar>>m_fPlambda;
		ar>>m_fKuv;
		ar>>m_fK1;
		ar>>m_fK2;

		ar>>m_strAngleView;


		ar>>m_fdc;
		ar>>m_strAddr;
		ar>>m_strCompany;
		ar>>m_strSampleName;
		ar>>m_strSampleState;
		ar>>m_strSampleStandard;

		ar>>m_fBlueRatio;
		ar>>m_fGreenRatio;

		ar>>m_strColorCorrectStr;
		ar>>m_strFilter;

		if(strVer!="NH_GCS_300_V100")
		{
			ar >> m_strSN;
		}
		else
		{
			m_strSN = g_SPEC.m_strSN;
		}
	}
}

void CSpectData::printHead(CDC *pDC, CRect printRect, int iCur, int iMax,BOOL bPrintLogo,int iPrintLogoPos,BOOL bPrintPage)
{
	char buffer[20];
	CFont font;
	font.CreateFont(-(int)(printRect.Height()/52),0,0,0,600,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"Courier New");
	
	CFont* pOldFont=(CFont*)(pDC->SelectObject(&font));

	TEXTMETRIC  tm;
	pDC->GetTextMetrics(&tm);
	int nfontHeight=tm.tmHeight+tm.tmExternalLeading;
	int nfontWidth=tm.tmAveCharWidth;

	int x=printRect.left+nfontWidth/2;
	int y=printRect.top-nfontHeight;
	
	if(g_bEnglish)
	{
		pDC->TextOut(printRect.left+4*nfontWidth,printRect.top-nfontHeight,g_strPrTitle_E);
		sprintf(buffer,"%d Of %d ",iCur,iMax);
	}
	else
	{
		pDC->TextOut(printRect.left+4*nfontWidth,printRect.top-nfontHeight,g_strPrTitle_C);
		sprintf(buffer,"第 %d 页  共 %d 页",iCur,iMax);
	}

	if(bPrintPage)
		pDC->TextOut(printRect.right-20*nfontWidth,printRect.top-nfontHeight,buffer);

	pDC->SetTextAlign(TA_CENTER);
	pDC->TextOut(printRect.left+printRect.Width()/2,printRect.top- 2*nfontHeight,CMySpecDoc::m_strNewT);
	pDC->SetTextAlign(TA_LEFT);

	CPen Pen;
	CPen *PtrOldPen;
	Pen.CreatePen(PS_SOLID,3,RGB(0,0,0));
	PtrOldPen=pDC->SelectObject(&Pen);
	pDC->MoveTo(printRect.left,printRect.top);
	pDC->LineTo(printRect.right,printRect.top);

	pDC->SelectObject(pOldFont);
	pDC->SelectObject(PtrOldPen);

	if(!bPrintLogo)
		return;
	//打印图片标志
	CRect compRect;
	CBrush BrushBack;
	BrushBack.CreateSolidBrush(RGB(255,255,255));
	CRect Rect;

	compRect.left	= printRect.left;
	compRect.right	= printRect.left+printRect.Width()/4;
	compRect.top	= printRect.top-nfontHeight*3/2-compRect.Width()*125/370;
	compRect.bottom	= printRect.top-nfontHeight*3/2;

//	g_ImageLogo.Stretch( compRect.Width(), compRect.Height() );

	// Set the palette and draw.
//	if( GetFocus() == this )
//		m_ImageCompany.SetPalette( pDC );
	if(iPrintLogoPos==0)
	{
		g_ImageLogo.Draw( pDC,compRect.left,compRect.top,compRect.Width(),compRect.Height() );

		pDC->SetBkMode(OPAQUE);
		Rect.left=compRect.left;
		Rect.right=compRect.right;
		Rect.top=compRect.top;
		Rect.bottom=compRect.top+nfontHeight/2;
		pDC->FillRect(&Rect,&BrushBack);
	}

	compRect.left=printRect.right-printRect.Width()/4;
	compRect.right=printRect.right;

//	g_ImageLogo.Stretch( compRect.Width(), compRect.Height() );

	// Set the palette and draw.
//	if( GetFocus() == this )
//		m_ImageLogo.SetPalette( pDC );

	if(iPrintLogoPos==1)
	{
		g_ImageLogo.Draw( pDC,compRect.left,compRect.top,compRect.Width(),compRect.Height() );

		pDC->SetBkMode(OPAQUE);
		Rect.left=compRect.left;
		Rect.right=compRect.right;
		Rect.top=compRect.top;
		Rect.bottom=compRect.top+nfontHeight/2;
		pDC->FillRect(&Rect,&BrushBack);
	}
}

void CSpectData::printFoot(CDC *pDC, CRect printRect, int iCur, int iMax)
{
	char buffer[256];
	
	CFont font;
	font.CreateFont(-(int)(printRect.Height()/58),0,0,0,600,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"Courier New");
	
	CFont* pOldFont=(CFont*)(pDC->SelectObject(&font));

	TEXTMETRIC  tm;
	pDC->GetTextMetrics(&tm);
	int nfontHeight=tm.tmHeight+tm.tmExternalLeading;
	int nfontWidth=tm.tmAveCharWidth;
	int firstline=printRect.bottom+nfontHeight/2;
	pDC->SetTextAlign(TA_LEFT);


	if(g_bEnglish)
	{
		sprintf(buffer,"Model:%s",m_strModel);
		pDC->TextOut(printRect.left+4*nfontWidth,firstline,buffer);
		sprintf(buffer,"Number:%s",m_strNumber);
		pDC->TextOut(printRect.left+printRect.Width()/2,firstline,buffer);
		sprintf(buffer,"Tester:%s",m_strTester);
		pDC->TextOut(printRect.left+4*nfontWidth,firstline+1*nfontHeight,buffer);
		sprintf(buffer,"Date:%s",m_strDate);
		pDC->TextOut(printRect.left+printRect.Width()/2,firstline+1*nfontHeight,buffer);
		sprintf(buffer,"Temperature:%sDeg",m_strT);
		pDC->TextOut(printRect.left+4*nfontWidth,firstline+2*nfontHeight,buffer);
		sprintf(buffer,"Humidity:%s%%",m_strH);
		pDC->TextOut(printRect.left+printRect.Width()/2,firstline+2*nfontHeight,buffer);
		sprintf(buffer,"Manufacturer:%s",m_strFactory);
		pDC->TextOut(printRect.left+4*nfontWidth,firstline+3*nfontHeight,buffer);
		sprintf(buffer,"Remarks:%s",m_strRemark);
		pDC->TextOut(printRect.left+printRect.Width()/2,firstline+3*nfontHeight,buffer);

		if(CMySpecDoc::m_bPrintChecker)
		{
			sprintf(buffer,"Assessor:%s", CMySpecDoc::m_strChecker);
			pDC->TextOut(printRect.left+4*nfontWidth,firstline+4*nfontHeight,buffer);
		}

	}
	else
	{
		sprintf(buffer,"样品型号:%s",m_strModel);
		pDC->TextOut(printRect.left+4*nfontWidth,firstline,buffer);
		if(CMySpecDoc::m_iNType == 0)
			sprintf(buffer,"样品编号:%s",m_strNumber);
		if(CMySpecDoc::m_iNType == 1)
			sprintf(buffer,"检验编号:%s",m_strNumber);
		pDC->TextOut(printRect.left+printRect.Width()/2,firstline,buffer);
		sprintf(buffer,"测试人员:%s",m_strTester);
		pDC->TextOut(printRect.left+4*nfontWidth,firstline+1*nfontHeight,buffer);
		sprintf(buffer,"测试日期:%s",m_strDate);
		pDC->TextOut(printRect.left+printRect.Width()/2,firstline+1*nfontHeight,buffer);
		sprintf(buffer,"环境温度:%s℃",m_strT);
		pDC->TextOut(printRect.left+4*nfontWidth,firstline+2*nfontHeight,buffer);
		sprintf(buffer,"环境湿度:%s%%",m_strH);
		pDC->TextOut(printRect.left+printRect.Width()/2,firstline+2*nfontHeight,buffer);
		sprintf(buffer,"制造厂商:%s",m_strFactory);
		pDC->TextOut(printRect.left+4*nfontWidth,firstline+3*nfontHeight,buffer);
		sprintf(buffer,"备    注:%s",m_strRemark);
		pDC->TextOut(printRect.left+printRect.Width()/2,firstline+3*nfontHeight,buffer);

		if(CMySpecDoc::m_bPrintChecker)
		{
			sprintf(buffer,"审核人员:%s", CMySpecDoc::m_strChecker);
			pDC->TextOut(printRect.left+4*nfontWidth,firstline+4*nfontHeight,buffer);
		}
	}

	CPen Pen;
	CPen *PtrOldPen;
	Pen.CreatePen(PS_SOLID,2,RGB(0,0,0));
	PtrOldPen=pDC->SelectObject(&Pen);
	pDC->MoveTo(printRect.left,printRect.bottom);
	pDC->LineTo(printRect.right,printRect.bottom);

	pDC->SelectObject(pOldFont);
	pDC->SelectObject(PtrOldPen);
}

void CSpectData::printReport_2(CDC *pDC, CRect printRect,int iTypeP,int iSeleK,int iSDCM1,int iSDCM2,int iPhType,CWhiteZone &xyZone,CString strLevel,CString strWhite,BOOL bPrintLogo,int iPrintLogoPos)
{
	if(!m_bHaveData)
		return;

	CFont *pOldFont;
	CFont pFont1;
	CFont pFont2;
	CFont pFont3;
	CFont pFont3s;
	CFont pFont4;
	CFont pFont5;

	if(!g_bEnglish)
	{
		pFont1.CreateFont(printRect.Height()/55,0,0,0,700,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Arial");
		pFont2.CreateFont(printRect.Height()/70,0,0,0,500,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Arial");
		pFont3.CreateFont(printRect.Height()/70,0,0,0,500,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Arial");
		pFont3s.CreateFont(printRect.Height()/70,0,0,0,600,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Symbol");
		pFont4.CreateFont(printRect.Height()/85,0,0,0,500,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Arial");
		pFont5.CreateFont(printRect.Height()/70,0,0,0,500,TRUE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Arial");
	}
	else
	{
		pFont1.CreateFont(printRect.Height()/55,0,0,0,700,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Arial");
		pFont2.CreateFont(printRect.Height()/70,0,0,0,500,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Arial");
		pFont3.CreateFont(printRect.Height()/70,0,0,0,500,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Arial");
		pFont3s.CreateFont(printRect.Height()/70,0,0,0,600,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Symbol");
		pFont4.CreateFont(printRect.Height()/85,0,0,0,500,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Arial");
		pFont5.CreateFont(printRect.Height()/70,0,0,0,500,TRUE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Arial");
	}
	
	CPen  *pOldPen;
	CPen  pPen1;
	CPen  pPen2;
	CPen  pPen3;

	pPen1.CreatePen(PS_SOLID,1,RGB(255,255,0));
	pPen2.CreatePen(PS_SOLID,1,RGB(255,0,0));
	pPen3.CreatePen(PS_SOLID,1,RGB(255,255,255));
	pOldPen  = pDC->SelectObject(&pPen1);
	pOldFont = pDC->SelectObject(&pFont1);

	int Wn=printRect.Width()/50;
	int Hn=printRect.Height()/50;

	pDC->SetTextAlign(TA_CENTER);
	CString sStr;
	int i;

	//打印图片标志
	CRect compRect;
	CBrush BrushBack;
	BrushBack.CreateSolidBrush(RGB(255,255,255));
	CRect Rect;

	if(bPrintLogo)
	{
		if(iPrintLogoPos==0)
		{
			compRect.right	= printRect.left+printRect.Width()/6+Wn*3;
			compRect.left	= printRect.left+Wn*2;
			compRect.top	= printRect.top+Hn*2;
			compRect.bottom	= printRect.top+Hn*5;
			
			g_ImageLogo.Draw( pDC,compRect.left,compRect.top,compRect.Width(),compRect.Height() );
			
			pDC->SetBkMode(OPAQUE);
			Rect.right	= printRect.left+printRect.Width()/3;
			Rect.left	= printRect.left;
			Rect.top	= printRect.top+Hn*0;
			Rect.bottom	= printRect.top+Hn*3;
			pDC->FillRect(&Rect,&BrushBack);
		}
				
		if(iPrintLogoPos==1)
		{
			compRect.left	= printRect.right-printRect.Width()/6-Wn*3;
			compRect.right	= printRect.right-Wn*2;
			compRect.top	= printRect.top+Hn*2;
			compRect.bottom	= printRect.top+Hn*5;
			
			g_ImageLogo.Draw( pDC,compRect.left,compRect.top,compRect.Width(),compRect.Height() );
			
			pDC->SetBkMode(OPAQUE);
			Rect.left	= printRect.right-printRect.Width()/6-Wn*3;
			Rect.right	= printRect.right-Wn*2;
			Rect.top	= printRect.top+Hn*2;
			Rect.bottom	= printRect.top+Hn*3;
			pDC->FillRect(&Rect,&BrushBack);
		}
	}

	int iCurY;
	if(!g_bEnglish)
	{
		iCurY=(int)(printRect.top+3.5f*Hn);
		if(m_iLamp==0)
			sStr="光 源 光 谱 测 试 报 告";
		else
			sStr="荧 光 粉 光 谱 测 试 报 告";
		iCurY=iCurY+Hn;
		pDC->TextOut(printRect.left+printRect.Width()/2,iCurY,sStr);
	}
	else
	{
		iCurY=(int)(printRect.top+3.5f*Hn);
		if(m_iLamp==0)
			sStr="Spectrum Test Report";
		else
			sStr="Phosphor Test Report";
		iCurY=iCurY+Hn;
		pDC->TextOut(printRect.left+printRect.Width()/2,iCurY,sStr);
	}

	Hn=(int)(Hn*0.9f);
	pDC->SetTextAlign(TA_LEFT);
	pDC->SelectObject(&pFont2);

	if(!g_bEnglish)
	{
		iCurY=iCurY+Hn*4;
		sStr.Format("样品名称");
		pDC->TextOut(printRect.left+4*Wn,iCurY,sStr);
		sStr.Format(": %s",m_strSampleName);
		pDC->TextOut(printRect.left+11*Wn,iCurY,sStr);

		sStr.Format("测试日期");
		pDC->TextOut(printRect.left+4*Wn+printRect.Width()/2,iCurY,sStr);
		sStr.Format(": %s",m_strDate);
		pDC->TextOut(printRect.left+11*Wn+printRect.Width()/2,iCurY,sStr);

		iCurY=iCurY+Hn;

		
		sStr.Format("样品型号");
		pDC->TextOut(printRect.left+4*Wn,iCurY,sStr);
		sStr.Format(": %s",m_strModel);
		pDC->TextOut(printRect.left+11*Wn,iCurY,sStr);
	
		sStr.Format("样品状态");
		pDC->TextOut(printRect.left+4*Wn+printRect.Width()/2,iCurY,sStr);
		sStr.Format(": %s",m_strSampleState);
		pDC->TextOut(printRect.left+11*Wn+printRect.Width()/2,iCurY,sStr);

		iCurY=iCurY+Hn;
		if(CMySpecDoc::m_iNType == 0)
			sStr.Format("样品编号");
		if(CMySpecDoc::m_iNType == 1)
			sStr.Format("检验编号");
		pDC->TextOut(printRect.left+4*Wn,iCurY,sStr);
		sStr.Format(": %s",m_strNumber);
		pDC->TextOut(printRect.left+11*Wn,iCurY,sStr);

		sStr.Format("测试仪器");
		pDC->TextOut(printRect.left+4*Wn+printRect.Width()/2,iCurY,sStr);
		sStr.Format(": %s","GCS-300(NAHON)");
		pDC->TextOut(printRect.left+11*Wn+printRect.Width()/2,iCurY,sStr);

		iCurY=iCurY+Hn;
		sStr.Format("制造厂商");
		pDC->TextOut(printRect.left+4*Wn,iCurY,sStr);
		sStr.Format(": %s",m_strFactory);
		pDC->TextOut(printRect.left+11*Wn,iCurY,sStr);

		sStr.Format("测试人员");
		pDC->TextOut(printRect.left+4*Wn+printRect.Width()/2,iCurY,sStr);
		sStr.Format(": %s",m_strTester);
		pDC->TextOut(printRect.left+11*Wn+printRect.Width()/2,iCurY,sStr);
	}
	else
	{
		iCurY=iCurY+Hn*4;
		sStr.Format("Sample");
		pDC->TextOut(printRect.left+4*Wn,iCurY,sStr);
		sStr.Format(": %s",m_strSampleName);
		pDC->TextOut(printRect.left+11*Wn,iCurY,sStr);
		
		sStr.Format("Date");
		pDC->TextOut(printRect.left+4*Wn+printRect.Width()/2,iCurY,sStr);
		sStr.Format(": %s",m_strDate);
		pDC->TextOut(printRect.left+11*Wn+printRect.Width()/2,iCurY,sStr);
		
		iCurY=iCurY+Hn;
		
		
		sStr.Format("Specification");
		pDC->TextOut(printRect.left+4*Wn,iCurY,sStr);
		sStr.Format(": %s",m_strModel);
		pDC->TextOut(printRect.left+11*Wn,iCurY,sStr);
		
		sStr.Format("Sam. Status");
		pDC->TextOut(printRect.left+4*Wn+printRect.Width()/2,iCurY,sStr);
		sStr.Format(": %s",m_strSampleState);
		pDC->TextOut(printRect.left+11*Wn+printRect.Width()/2,iCurY,sStr);
		
		iCurY=iCurY+Hn;
		if(CMySpecDoc::m_iNType == 0)
			sStr.Format("Sample No.");
		if(CMySpecDoc::m_iNType == 1)
			sStr.Format("Sample No.");
		pDC->TextOut(printRect.left+4*Wn,iCurY,sStr);
		sStr.Format(": %s",m_strNumber);
		pDC->TextOut(printRect.left+11*Wn,iCurY,sStr);
		
		sStr.Format("Instrument");
		pDC->TextOut(printRect.left+4*Wn+printRect.Width()/2,iCurY,sStr);
		sStr.Format(": %s","GCS-300(NAHON)");
		pDC->TextOut(printRect.left+11*Wn+printRect.Width()/2,iCurY,sStr);
		
		iCurY=iCurY+Hn;
		sStr.Format("Manufacturer");
		pDC->TextOut(printRect.left+4*Wn,iCurY,sStr);
		sStr.Format(": %s",m_strFactory);
		pDC->TextOut(printRect.left+11*Wn,iCurY,sStr);
		
		sStr.Format("Test by");
		pDC->TextOut(printRect.left+4*Wn+printRect.Width()/2,iCurY,sStr);
		sStr.Format(": %s",m_strTester);
		pDC->TextOut(printRect.left+11*Wn+printRect.Width()/2,iCurY,sStr);


/*		iCurY=iCurY+Hn*4;
		sStr.Format("Product");
		pDC->TextOut(printRect.left+4*Wn,iCurY,sStr);
		sStr.Format(": %s",m_strModel);
		pDC->TextOut(printRect.left+11*Wn,iCurY,sStr);

		sStr.Format("Date");
		pDC->TextOut(printRect.left+4*Wn+printRect.Width()/2,iCurY,sStr);
		sStr.Format(": %s",m_strDate);
		pDC->TextOut(printRect.left+11*Wn+printRect.Width()/2,iCurY,sStr);

		iCurY=iCurY+Hn;
		sStr.Format("Sample No.");
		pDC->TextOut(printRect.left+4*Wn,iCurY,sStr);
		sStr.Format(": %s",m_strNumber);
		pDC->TextOut(printRect.left+11*Wn,iCurY,sStr);

		sStr.Format("Instrument");
		pDC->TextOut(printRect.left+4*Wn+printRect.Width()/2,iCurY,sStr);
		sStr.Format(": %s","GCS-300(NAHON)");
		pDC->TextOut(printRect.left+11*Wn+printRect.Width()/2,iCurY,sStr);

		iCurY=iCurY+Hn;
		sStr.Format("Manufacturer");
		pDC->TextOut(printRect.left+4*Wn,iCurY,sStr);
		sStr.Format(": %s",m_strFactory);
		pDC->TextOut(printRect.left+11*Wn,iCurY,sStr);

		sStr.Format("Tested by");
		pDC->TextOut(printRect.left+4*Wn+printRect.Width()/2,iCurY,sStr);
		sStr.Format(": %s",m_strTester);
		pDC->TextOut(printRect.left+11*Wn+printRect.Width()/2,iCurY,sStr);
//		sStr.Format("Client");
//		pDC->TextOut(printRect.left+4*Wn+printRect.Width()/2,iCurY,sStr);
//		sStr.Format(": %s",m_strFactory);
//		pDC->TextOut(printRect.left+11*Wn+printRect.Width()/2,iCurY,sStr);

//		iCurY=iCurY+Hn;
//		sStr.Format("Operator");
//		pDC->TextOut(printRect.left+4*Wn,iCurY,sStr);
//		sStr.Format(": %s",m_strTester);
//		pDC->TextOut(printRect.left+11*Wn,iCurY,sStr);

//		sStr.Format("Reviewed By");
//		pDC->TextOut(printRect.left+4*Wn+printRect.Width()/2,iCurY,sStr);
//		sStr.Format(": %s",m_strTester);
//		pDC->TextOut(printRect.left+11*Wn+printRect.Width()/2,iCurY,sStr);*/
	}

	//
	pDC->SetTextAlign(TA_LEFT);
	pDC->SelectObject(&pFont1);
	if(!g_bEnglish)
		sStr.Format("测试条件");
	else
		sStr.Format("Test Condition");
	iCurY=iCurY+Hn*2;
	pDC->TextOut(printRect.left+4*Wn,iCurY,sStr);

	pDC->SelectObject(&pFont2);
	if(!g_bEnglish)
	{
		iCurY=iCurY+Hn;
		sStr.Format("环境温度");
		pDC->TextOut(printRect.left+4*Wn,iCurY,sStr);
		sStr.Format(": %sDeg",m_strT);
		pDC->TextOut(printRect.left+11*Wn,iCurY,sStr);

		sStr.Format("环境湿度");
		pDC->TextOut(printRect.left+4*Wn+printRect.Width()/2,iCurY,sStr);
		sStr.Format(": %s%%",m_strH);
		pDC->TextOut(printRect.left+11*Wn+printRect.Width()/2,iCurY,sStr);

		iCurY=iCurY+Hn;
		sStr.Format("测试范围");
		pDC->TextOut(printRect.left+4*Wn,iCurY,sStr);
		sStr.Format(": %.0fnm-%.0fnm",m_fSpect1,m_fSpect2);
		pDC->TextOut(printRect.left+11*Wn,iCurY,sStr);

		sStr.Format("峰值IP");
		pDC->TextOut(printRect.left+4*Wn+printRect.Width()/2,iCurY,sStr);
		sStr.Format(": %.0f (%.0f%%)",m_fIp,m_fIp*100.0f/(m_nADW-1));
		pDC->TextOut(printRect.left+11*Wn+printRect.Width()/2,iCurY,sStr);

		iCurY=iCurY+Hn;

		sStr.Format("积分时间");
		pDC->TextOut(printRect.left+4*Wn+printRect.Width()/2,iCurY,sStr);
		sStr.Format(": %.0f ms",m_fIntTime);
		pDC->TextOut(printRect.left+11*Wn+printRect.Width()/2,iCurY,sStr);

		iCurY=iCurY+Hn;
	}
	else
	{
		iCurY=iCurY+Hn;
		sStr.Format("Temprature");
		pDC->TextOut(printRect.left+4*Wn,iCurY,sStr);
		sStr.Format(": %sDeg",m_strT);
		pDC->TextOut(printRect.left+11*Wn,iCurY,sStr);

		sStr.Format("RH");
		pDC->TextOut(printRect.left+4*Wn+printRect.Width()/2,iCurY,sStr);
		sStr.Format(": %s%%",m_strH);
		pDC->TextOut(printRect.left+11*Wn+printRect.Width()/2,iCurY,sStr);

		iCurY=iCurY+Hn;
		sStr.Format("WL Range");
		pDC->TextOut(printRect.left+4*Wn,iCurY,sStr);
		sStr.Format(": %.0fnm-%.0fnm",m_fSpect1,m_fSpect2);
		pDC->TextOut(printRect.left+11*Wn,iCurY,sStr);

		sStr.Format("IP");
		pDC->TextOut(printRect.left+4*Wn+printRect.Width()/2,iCurY,sStr);
		sStr.Format(": %.0f (%.0f%%)",m_fIp,m_fIp*100.0f/(m_nADW-1));
		pDC->TextOut(printRect.left+11*Wn+printRect.Width()/2,iCurY,sStr);

		iCurY=iCurY+Hn;
		sStr.Format("T");
		pDC->TextOut(printRect.left+4*Wn+printRect.Width()/2,iCurY,sStr);
		sStr.Format(": %.0f ms",m_fIntTime);
		pDC->TextOut(printRect.left+11*Wn+printRect.Width()/2,iCurY,sStr);

		sStr.Format("Test Mode");
		pDC->TextOut(printRect.left+4*Wn,iCurY,sStr);
		CString sTemp;
	}

	// 画波形
	pDC->SetTextAlign(TA_LEFT);
	pDC->SelectObject(&pFont1);

	if(!g_bEnglish)
		sStr.Format("光谱参数");
	else
		sStr.Format("Spectrum");
	iCurY=iCurY+Hn*2;
	pDC->TextOut(printRect.left+4*Wn,iCurY,sStr);

	pDC->SetTextAlign(TA_LEFT);
	pDC->SelectObject(&pFont2);
	CRect SpectRect,SDCMRect,Spect01Rect;

	SpectRect.left	= printRect.left+4*Wn;
	SpectRect.right	= printRect.left+30*Wn;
	iCurY	= (int)(iCurY+Hn*1.2f);
	SpectRect.top	= printRect.top+iCurY;
	iCurY	= iCurY+Hn*12;
	SpectRect.bottom= printRect.top+iCurY;

	SDCMRect.left	= SpectRect.right;
	SDCMRect.right	= printRect.right-4*Wn;
	SDCMRect.top	= SpectRect.top;
	SDCMRect.bottom	= SpectRect.bottom;
	
	Spect01Rect.left	= printRect.left+4*Wn;
	Spect01Rect.right	= printRect.right-0*Wn;

	Spect01Rect.top		= SpectRect.top;
	Spect01Rect.bottom	= SpectRect.bottom;

	DATA_DRAW drawData;
	drawData.iDrawType = 1;
	drawData.bShowCur  = FALSE;
	drawData.bMouse    = FALSE;
	DrawSpect(pDC,SpectRect,drawData,"",TRUE,TRUE, iPhType);
	
	if(m_bHaveColorPara)
	{
		if(iTypeP == 0)
		{
			printCIE(pDC,SDCMRect,m_x,m_y,m_fCCT);
		}
		else if(iTypeP == 1)
		{
			printCIE_UV(pDC,SDCMRect,m_u,m_v,m_fCCT);
		}
		else if(iTypeP == 2)
		{
			printColorErr(pDC,SDCMRect,m_x,m_y,iSeleK,iSDCM1,iSDCM2);
		}
		else
		{
			xyZone.m_fX = m_x;
			xyZone.m_fY = m_y;
			xyZone.Draw(pDC,SDCMRect,-1,TRUE,0);
		}
	}

	pDC->SetTextAlign(TA_LEFT);
	if(!g_bEnglish)
		sStr.Format("光谱分布");
	else
		sStr.Format("Spectral Distribution");
	pDC->TextOut(printRect.left+4*Wn,iCurY,sStr);

	pDC->SetTextAlign(TA_RIGHT);
	if(!g_bEnglish)
		sStr.Format("CIE1931色品图");
	else
		sStr.Format("CIE1931 Chromaticity Diagram");
	pDC->TextOut(printRect.right-4*Wn,iCurY,sStr);
	pDC->SetTextAlign(TA_LEFT);

	// 色参数
	iCurY = SpectRect.bottom;

	int iCurX=SpectRect.left;
	pDC->SetTextAlign(TA_LEFT);
	iCurY=(int)(iCurY+1.5*Hn);
	if(m_bHaveColorPara)
	{
		pDC->SelectObject(&pFont1);
		if(!g_bEnglish)
			sStr="CIE颜色参数";
		else
			sStr="Colorimetric Quantities";
		pDC->TextOut(iCurX,iCurY,sStr);
		pDC->SelectObject(&pFont2);
		
		//------------------------------------------------
		TEXTMETRIC  tm;
		pDC->GetTextMetrics(&tm);
		int nfontHeight=tm.tmHeight+tm.tmExternalLeading;
		int nfontWidth=tm.tmAveCharWidth;
		//------------------------------------------------

		iCurY=(int)(iCurY+1.0*Hn);
		if(!g_bEnglish)
			sStr.Format("色品坐标: x = %.4f y = %.4f / u' = %.4f v' = %.4f",m_x,m_y,m_u,m_v);
		else
			sStr.Format("Chromaticity Coordinate: x = %.4f y = %.4f / u' = %.4f v' = %.4f",m_x,m_y,m_u,m_v);

		CString dC;
		dC.Format(" (duv=%.2e)",m_fdc);
		dC.Replace("-00","-0");
		dC.Replace("+00","+0");
		sStr=sStr+dC;
		pDC->TextOut(iCurX,iCurY,sStr);

		iCurY=(int)(iCurY+1.0*Hn);
		if(!g_bEnglish)
		{
			if(m_fCCT>1000&&m_fCCT<100000)
				sStr.Format("相关色温:CCT=%.0fK    主波长:λd=%.1fnm     色纯度:Purity=%.1f%%",m_fCCT,m_fMainlambda,m_fPurity);
			else if(m_fCCT<=1000)
				sStr.Format("相关色温:CCT<=1000K    主波长:λd=%.1fnm     色纯度:Purity=%.1f%%",m_fMainlambda,m_fPurity);
			else
				sStr.Format("相关色温:CCT>=100000K    主波长:λd=%.1fnm     色纯度:Purity=%.1f%%",m_fMainlambda,m_fPurity);
		}
		else
		{
			if(m_fCCT>1000&&m_fCCT<100000)
				sStr.Format("CCT=%6.0fK         Prcp WL:    Ld=%.1fnm      Purity=%.1f%%",m_fCCT,m_fMainlambda,m_fPurity);
			else if(m_fCCT<=1000)
				sStr.Format("CCT<=1000K         Prcp WL:   Ld=%.1fnm      Purity=%.1f%%",m_fMainlambda,m_fPurity);
			else
				sStr.Format("CCT>=100000K        Prcp WL:   Ld=%.1fnm      Purity=%.1f%%",m_fMainlambda,m_fPurity);
		}
		pDC->TextOut(iCurX,iCurY,sStr);

		iCurY=(int)(iCurY+1.0*Hn);
		if(!g_bEnglish)
			sStr.Format("峰值波长:λp=%.0fnm  半宽度:FWHM=%.1fnm   色比:R=%.1f%% G=%.1f%% B=%.1f%%",m_fMaxlambda,m_fHalflambda,m_fRedRatio,m_fGreenRatio,m_fBlueRatio);
		else
			sStr.Format("Peak WL:  Lp=%3.0fnm  FWHM:   =%.1fnm  Ratio:R=%.1f%% G=%.1f%% B=%.1f%%",m_fMaxlambda,m_fHalflambda,m_fRedRatio,m_fGreenRatio,m_fBlueRatio);
		pDC->TextOut(iCurX,iCurY,sStr);
		iCurY=(int)(iCurY+1.0*Hn);

		if(g_bHaveCRI)
		{
			float fCRI=0;
			for(i=0;i<14;i++)
			{
				fCRI=fCRI+m_fRi[i];
			}
			fCRI=fCRI/14;
			
			iCurY=(int)(iCurY+1.0*Hn);
			if(g_bEnglish)
				sStr.Format("Render Index: Ra = %.1f   CRI = %.1f",m_fRa,fCRI);
			else
				sStr.Format("显色指数: Ra = %.1f   CRI = %.1f",m_fRa,fCRI);
			pDC->TextOut(iCurX,iCurY,sStr);
		}
		else
		{
			iCurY=(int)(iCurY+1.0*Hn);
			if(g_bEnglish)
				sStr.Format("Render Index: Ra = %.1f",m_fRa);
			else
				sStr.Format("显色指数: Ra = %.1f",m_fRa);
			pDC->TextOut(iCurX,iCurY,sStr);
		}
		
		int iRONE=(printRect.right-iCurX)/10;
		iCurY=(int)(iCurY+1.0*Hn);
		for(i=0;i<7;i++)
		{
			sStr.Format("R%-2d=%.0f",i+1,m_fRi[i]);
			pDC->TextOut(iCurX+i*iRONE,iCurY,sStr);
		}
		iCurY=(int)(iCurY+1.0*Hn);
		for(i=0;i<8;i++)
		{
			sStr.Format("R%-2d=%.0f",i+1+7,m_fRi[i+7]);
			pDC->TextOut(iCurX+i*iRONE,iCurY,sStr);
		}
		iCurY=(int)(iCurY+1.0*Hn);

		if(strLevel!=""||strWhite!="")
		{
			CString sStr1 = "";
			CString sStr2 = "";

			if(strLevel == "")
			{
				if(g_bEnglish)
				{
					sStr.Format("WHITE:%s",strWhite);
				}
				else
				{
					sStr.Format("白光分类:%s",strWhite);
				}
			}
			else if(strWhite == "")
			{
				if(g_bEnglish)
				{
					sStr.Format("LEVEL:%s",strLevel);
				}
				else
				{
					sStr.Format("分级:%s",strLevel);
				}

			}
			else
			{
				if(g_bEnglish)
				{
					sStr.Format("LEVEL:%s        WHITE:%s",strLevel,strWhite);
				}
				else
				{
					sStr.Format("分级:%s        白光分类:%s",strLevel,strWhite);
				}
			}
			pDC->TextOut(iCurX,iCurY,sStr);
		}
		iCurY=(int)(iCurY+1.0*Hn);
	}
	if(m_iLamp==0)
	{
		pDC->SelectObject(&pFont1);
		iCurY=(int)(iCurY+1.0*Hn);
		if(!g_bEnglish)
			sStr="光度&辐射度参数";
		else
			sStr=" Photometric & Radiometric Quantities";
		pDC->TextOut(iCurX,iCurY,sStr);
		iCurY=(int)(iCurY+1.0*Hn);
		pDC->SelectObject(&pFont2);

		//------------------------------------------------
		TEXTMETRIC  tm;
		pDC->GetTextMetrics(&tm);
		int nfontHeight=tm.tmHeight+tm.tmExternalLeading;
		int nfontWidth=tm.tmAveCharWidth;
		//-----------------------------------------------
		if(m_bTestPH)
		{
			CString strUnit;
			CString strFe;
			CString strPH=PH_Name(m_iLamp,iPhType,strUnit,TRUE);
			if(m_bHaveColorPara)
				sStr.Format("%s  = %s %s",strPH,g_SPEC.sFormat(m_fPH,5),strUnit);
			else
				sStr="";
			
			if(m_iLamp==0)
			{
				if(iPhType==PH_I||iPhType==PH_Ie)
				{
					if(m_fPh_e>1)
					{
						strPH=PH_Name(m_iLamp,PH_Ie,strUnit,TRUE);
						strFe.Format("  %s  = %s W/sr",strPH,g_SPEC.sFormat(m_fPh_e,5));
					}
					else
					{
						strPH=PH_Name(m_iLamp,PH_Ie,strUnit,TRUE);
						strFe.Format("  %s  = %s %s",strPH,g_SPEC.sFormat(m_fPh_e*1000,5),strUnit);
					}
					sStr=sStr+strFe;
					
					if(m_fDistance==0.316f)
					{
						if(g_bEnglish)
							sStr=sStr+" ( CIE A )";
						else
							sStr=sStr+" ( CIE A 条件)";
					}
					else if(m_fDistance==0.100f)
					{
						if(g_bEnglish)
							sStr=sStr+" ( CIE B )";
						else
							sStr=sStr+" ( CIE B 条件)";
					}
					else
					{
						strUnit.Format(" (%.3fm)",m_fDistance);
						if(m_bHaveColorPara)
							sStr=sStr+strUnit;
					}
				}
				if(iPhType==PH_F&&m_bTestF)
				{
					float fEff=0;
					if(m_fPow>0 && m_fIF > 0)
						fEff=m_fPH/(m_fPow);
					else
						fEff=0;
					if(g_bEnglish)
						strUnit.Format("   Eff. : %.2f lm/W",fEff);
					else
						strUnit.Format("   光效 : %.2f lm/W",fEff);
					if(m_bHaveColorPara)
						sStr=sStr+strUnit;
				}
				if(iPhType==PH_F)
				{
					if(m_fPh_e>1)
					{
						strPH=PH_Name(m_iLamp,PH_Fe,strUnit,TRUE);
						strFe.Format("  %s  = %s W",strPH,g_SPEC.sFormat(m_fPh_e,5));
					}
					else
					{
						strPH=PH_Name(m_iLamp,PH_Fe,strUnit,TRUE);
						strFe.Format("  %s  = %s %s",strPH,g_SPEC.sFormat(m_fPh_e*1000,5),strUnit);
					}
					sStr=sStr+strFe;
				}
				if(iPhType==PH_E)
				{
					strPH=PH_Name(m_iLamp,PH_Ee,strUnit,TRUE);
					strFe.Format("  %s  = %s %s",strPH,g_SPEC.sFormat(m_fPh_e,5),strUnit);
					sStr=sStr+strFe;
				}
				if(iPhType == PH_L)
				{
					CString strTemp;
					if(g_bEnglish)
						strTemp=" (AngleView:"+m_strAngleView+" Deg)";
					else
						strTemp=" (视场角:"+m_strAngleView+" 度)";
					sStr=sStr+strTemp;
				}
			}

			if(CSpectData::m_bPrintPh_)
			{
				if(iPhType == PH_F || iPhType == PH_E)
				{
					BOOL bPh_;
					float fPh_, fSP;
					
					bPh_ = CalcPh_(fPh_, fSP);
					if(bPh_ == TRUE)
					{
						CString strTemp2;
						
						if(g_bEnglish)
							strTemp2.Format(" Scotopic:%.5g S/P:%.5g", fPh_, fSP);
						else
							strTemp2.Format(" 暗视觉:%.5g S/P:%.5g", fPh_, fSP);
						
						sStr += strTemp2;
						
					}
				}
			}
			pDC->TextOut(iCurX,iCurY,sStr);
			iCurY=(int)(iCurY+1.0*Hn);

			if(g_bHavePhoEff)
			{
				float fMol  = 0;
				float fEff1 = 0;
				float fEff2 = 0;
				
				BOOL bPho = CalcPhoEff(fMol,fEff1,fEff2, iPhType);
				
				CString strTemp;
				sStr="";
				if(g_bEnglish)
				{
					strTemp = "Flux of emitted photons(umol/s)";
					if(iPhType == PH_E)
						strTemp = "Flux of emitted photons(umol/m2/s): ";
				}
				else
				{
					strTemp = "光量子数(umol/s)";
					if(iPhType == PH_E)
						strTemp = "光量子数(umol/m2/s): ";
				}
				sStr = sStr + strTemp;
				strTemp.Format(":%.5g ",fMol);
				if(bPho == FALSE)
					strTemp = "   ";
				sStr = sStr + strTemp;
				
				if(g_bEnglish)
				{
					strTemp="   Fluo. and blue light ratio:";
				}
				else
				{
					strTemp="   荧光蓝光比:";
				}
				sStr = sStr + strTemp;
				strTemp = g_SPEC.sFormat(fEff1,4);
				if(bPho == FALSE)
					strTemp = "   ";
				sStr = sStr + strTemp;
				
				if(g_bEnglish)
				{
					strTemp="   Fluorescent eff.:";
				}
				else
				{
					strTemp="   荧光效能:";
				}
				sStr = sStr + strTemp;
				strTemp = g_SPEC.sFormat(fEff2,4);
				if(bPho == FALSE)
					strTemp = "   ";
				sStr = sStr + strTemp;
				
				pDC->TextOut(iCurX,iCurY,sStr);
				iCurY=(int)(iCurY+1.0*Hn);
			}
		}

		iCurY=(int)(iCurY+0.5*Hn);
		pDC->SelectObject(&pFont5);
		pDC->TextOut(printRect.left+4*Wn,iCurY,"__________________________________________________________________________________");

		if(m_bTestF)
		{
			pDC->SelectObject(&pFont1);
			iCurY=(int)(iCurY+1.0*Hn);
			if(g_bEnglish)
				pDC->TextOut(iCurX,iCurY,"Electrical parameters");
			else
				pDC->TextOut(iCurX,iCurY,"电参数");
			
			pDC->SelectObject(&pFont2);
			iCurY=(int)(iCurY+1.3*Hn);
		}
		if(m_bTestF)
		{
			if(g_bEnglish)
				sStr.Format("V = %s V     I = %s A    P = %s W PF = %s",g_SPEC.sFormat(m_fVF,4),g_SPEC.sFormat(m_fIF,4),g_SPEC.sFormat(m_fPow,4),g_SPEC.sFormat(m_fPF,4));
			else
				sStr.Format("电压 V = %s V 电流 I = %s A 功率 P = %s W 功率因数 PF = %s",g_SPEC.sFormat(m_fVF,4),g_SPEC.sFormat(m_fIF,4),g_SPEC.sFormat(m_fPow,4),g_SPEC.sFormat(m_fPF,4));
			pDC->TextOut(iCurX,iCurY,sStr);
			iCurY=(int)(iCurY+1.0*Hn);
		}
	}
	pDC->SelectObject(&pFont1);
	pDC->SetTextAlign(TA_CENTER);

	iCurY=(int)(iCurY+1.0*Hn);
//	if(m_strCompany!="")
//		sStr=m_strCompany;
//	else
		sStr=g_strCompany;
	pDC->TextOut(printRect.left+printRect.Width()/2,iCurY,sStr);
	pDC->SelectObject(&pFont4);
	iCurY=(int)(iCurY+1.0*Hn);
//	if(m_strAddr!="")
//		sStr=m_strAddr;
//	else
		sStr=g_strAddr;
	pDC->TextOut(printRect.left+printRect.Width()/2,iCurY,sStr);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldFont);
	return;
}

void CSpectData::printReport(CDC *pDC, CRect printRect,int iTypeP,int iSeleK,int iSDCM1,int iSDCM2,int iPhType,CWhiteZone &xyZone,CString strLevel,CString strWhite)
{
	if(!m_bHaveData)
		return;

	CFont *pOldFont;
	CFont Font1;
	CFont Font2;
	CFont Font3;

	Font1.CreateFont(printRect.Height()/40,0,0,0,700,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"Courier New");

	Font2.CreateFont(printRect.Height()/57,0,0,0,600,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"Courier New");
	Font3.CreateFont(printRect.Height()/60,0,0,0,600,TRUE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"Courier New");
	
	CPen  *pOldPen;
	CPen  Pen1;
	CPen  Pen2;
	CPen  Pen3;

	Pen1.CreatePen(PS_SOLID,1,RGB(255,255,0));
	Pen2.CreatePen(PS_SOLID,1,RGB(255,0,0));
	Pen3.CreatePen(PS_SOLID,1,RGB(255,255,255));

	pOldPen=pDC->SelectObject(&Pen1);
	pOldFont=pDC->SelectObject(&Font1);

	int Wn=printRect.Width()/40;
	int Hn=printRect.Height()/40;

	CRect drRect;
	drRect.left=printRect.left+printRect.Width()/30;
	drRect.right=printRect.right-printRect.Width()/30;

	CRect SpectRect;
	SpectRect.left=drRect.left;
	if(m_bHaveColorPara)
		SpectRect.right=drRect.right-14*Wn;
	else
		SpectRect.right=drRect.right;
	SpectRect.top=printRect.top+8*Hn;
	SpectRect.bottom=printRect.top+8*Hn+7*22*Wn/9;

	pDC->SetTextAlign(TA_CENTER);
	if(m_iLamp==0)
	{
		if(g_bEnglish)
			pDC->TextOut(printRect.left+printRect.Width()/2,printRect.top+4*Hn,"Spectrum Test Report");
		else
			pDC->TextOut(printRect.left+printRect.Width()/2,printRect.top+4*Hn,"光 源 光 谱 测 试 报 告");
	}
	else
	{
		if(g_bEnglish)
			pDC->TextOut(printRect.left+printRect.Width()/2,printRect.top+4*Hn,"Phosphor Test Report");
		else
			pDC->TextOut(printRect.left+printRect.Width()/2,printRect.top+4*Hn,"荧 光 粉 光 谱 测 试 报 告");
	}
	CPoint pDis;
	int i;

	DATA_DRAW drawData;
	drawData.iDrawType = 1;
	drawData.bShowCur  = FALSE;
	drawData.bMouse    = FALSE;
	DrawSpect(pDC,SpectRect,drawData,"",TRUE,TRUE, iPhType);

	CRect sdcm;
	sdcm.left	= SpectRect.right;
	sdcm.right	= drRect.right;
	sdcm.top	= SpectRect.top;
	sdcm.bottom	= SpectRect.bottom;
	
	if(m_bHaveColorPara)
	{
		if(iTypeP == 0)
		{
			printCIE(pDC,sdcm,m_x,m_y,m_fCCT);
		}
		else if(iTypeP == 1)
		{
			printCIE_UV(pDC,sdcm,m_u,m_v,m_fCCT);
		}
		else if(iTypeP == 2)
		{
			printColorErr(pDC,sdcm,m_x,m_y,iSeleK,iSDCM1,iSDCM2);
		}
		else
		{
			xyZone.m_fX = m_x;
			xyZone.m_fY = m_y;
			xyZone.Draw(pDC, sdcm, -1, TRUE, 0);
		}
	}

	CString sStr;
	pDC->SetTextAlign(TA_LEFT);

	int iCurY;
	const int iX=printRect.left+1*Wn;
	iCurY=SpectRect.bottom+0*Hn;

	pDC->SelectObject(&Font1);
	iCurY=(int)(iCurY+1.0*Hn);

	if(m_bHaveColorPara)
	{

		if(g_bEnglish)
			pDC->TextOut(iX,iCurY,"Colorimetric Quantities");
		else
			pDC->TextOut(iX,iCurY,"颜色参数");

		pDC->SelectObject(&Font2);
		iCurY=(int)(iCurY+1.3*Hn);
		if(g_bEnglish)
			sStr.Format("Chromaticity Coordinate:x=%.4f  y=%.4f/u'=%.4f v'=%.4f",m_x,m_y ,m_u,m_v);
		else
			sStr.Format("色品坐标:x=%.4f  y=%.4f/u'=%.4f v'=%.4f",m_x,m_y ,m_u,m_v);
		pDC->TextOut(iX,iCurY,sStr);
		iCurY=(int)(iCurY+1.0*Hn);
		if(g_bEnglish)
			sStr.Format("CCT=%.0fK(Duv=%.4f) Dominant WL:Ld =%.1fnm Purity=%.1f%%",m_fCCT,m_fdc,m_fMainlambda,m_fPurity);
		else
			sStr.Format("相关色温:CCT=%.0fK(色差Duv=%.4f) 主波长:λd=%.1fnm 色纯度: Purity=%.1f%%",m_fCCT,m_fdc,m_fMainlambda,m_fPurity);
		pDC->TextOut(iX,iCurY,sStr);

		iCurY=(int)(iCurY+1.0*Hn);
		if(g_bEnglish)
			sStr.Format("Peak WL:Lp=%.1fnm  FWHM=%.1fnm",m_fMaxlambda,m_fHalflambda);
		else
			sStr.Format("峰值波长:λp=%.1fnm  半宽度:FWHM=%.1fnm",m_fMaxlambda,m_fHalflambda);
		pDC->TextOut(iX,iCurY,sStr);

		if(g_bHaveCRI)
		{
			float fCRI=0;
			for(i=0;i<14;i++)
			{
				fCRI=fCRI+m_fRi[i];
			}
			fCRI=fCRI/14;

			iCurY=(int)(iCurY+1.0*Hn);
			if(g_bEnglish)
				sStr.Format("Render Index:Ra=%.1f CRI=%.1f",m_fRa,fCRI);
			else
				sStr.Format("显色指数:Ra=%.1f CRI=%.1f",m_fRa,fCRI);
			pDC->TextOut(iX,iCurY,sStr);
		}
		else
		{
			iCurY=(int)(iCurY+1.0*Hn);
			if(g_bEnglish)
				sStr.Format("Render Index:Ra=%.1f",m_fRa);
			else
				sStr.Format("显色指数:Ra=%.1f",m_fRa);
			pDC->TextOut(iX,iCurY,sStr);
		}

		int iRONE=(printRect.right-iX)/8;
		iCurY=(int)(iCurY+1.0*Hn);
		for(i=0;i<7;i++)
		{
			sStr.Format("R%-2d=%.0f",i+1,m_fRi[i]);
			pDC->TextOut(iX+i*iRONE,iCurY,sStr);
		}
		iCurY=(int)(iCurY+1.0*Hn);
		for(i=0;i<8;i++)
		{
			sStr.Format("R%-2d=%.0f",i+1+7,m_fRi[i+7]);
			pDC->TextOut(iX+i*iRONE,iCurY,sStr);
		}
		iCurY=(int)(iCurY+1.0*Hn);
	}
	else
	{
		iCurY=(int)(iCurY+1.0*Hn);
		if(g_bEnglish)
			sStr.Format("Peak WL:Lp=%.1fnm  FWHM=%.1fnm",m_fMaxlambda,m_fHalflambda);
		else
			sStr.Format("峰值波长:λp=%.1fnm  半宽度:FWHM=%.1fnm",m_fMaxlambda,m_fHalflambda);
		pDC->TextOut(iX,iCurY,sStr);
		iCurY=(int)(iCurY+1.0*Hn);
	}

	if(m_bTestPH)
	{
		pDC->SelectObject(&Font1);
		iCurY=(int)(iCurY+0.6*Hn);
		if(g_bEnglish)
			pDC->TextOut(iX,iCurY,"Photometric & Radiometric Quantities");
		else
			pDC->TextOut(iX,iCurY,"光度&辐射度参数");

		pDC->SelectObject(&Font2);
		iCurY=(int)(iCurY+1.3*Hn);
	}

	if(0)
	{
		float fPh_e=GetWL12_Ee(m_fE_SP1,m_fE_SP2,m_fPh_e);
		CString strTemp;
		strTemp.Format("  (%.0f-%.0fnm)",m_fE_SP1,m_fE_SP2);
		if(g_bEnglish)
			sStr="F: "+g_SPEC.sFormat(m_fPh,4)+" lm   Fe: "+g_SPEC.sFormat(fPh_e*1000,4)+" mW"+strTemp;
		else
			sStr="光通量: "+g_SPEC.sFormat(m_fPh,4)+" lx   辐射通量: "+g_SPEC.sFormat(fPh_e*1000,4)+" mW/m2"+strTemp;
		pDC->TextOut(iX,iCurY,sStr);
		iCurY=(int)(iCurY+1.0*Hn);
	}

	if(m_bTestPH)
	{
		CString strUnit;
		CString strFe;
		CString strPH=PH_Name(m_iLamp,iPhType,strUnit,TRUE);
		if(m_bHaveColorPara)
			sStr.Format("%s  = %s %s",strPH,g_SPEC.sFormat(m_fPH,4),strUnit);
		else
			sStr="";

		if(m_iLamp==0)
		{
			if(iPhType==PH_I||iPhType==PH_Ie)
			{
				if(m_fPh_e>1)
				{
					strPH=PH_Name(m_iLamp,PH_Ie,strUnit,TRUE);
					strFe.Format("  %s  = %s W/sr",strPH,g_SPEC.sFormat(m_fPh_e,4));
				}
				else
				{
					strPH=PH_Name(m_iLamp,PH_Ie,strUnit,TRUE);
					strFe.Format("  %s  = %s %s",strPH,g_SPEC.sFormat(m_fPh_e*1000,4),strUnit);
				}
				sStr=sStr+strFe;

				if(m_fDistance==0.316f)
				{
					if(g_bEnglish)
						sStr=sStr+" ( CIE A )";
					else
						sStr=sStr+" ( CIE A 条件)";
				}
				else if(m_fDistance==0.100f)
				{
					if(g_bEnglish)
						sStr=sStr+" ( CIE B )";
					else
						sStr=sStr+" ( CIE B 条件)";
				}
				else
				{
					strUnit.Format(" (%.3fm)",m_fDistance);
					if(m_bHaveColorPara)
						sStr=sStr+strUnit;
				}
			}
			if(iPhType==PH_F&&m_bTestF)
			{
				float fEff=0;
				if(m_fPow>0)
					fEff=m_fPH/(m_fPow);
				else
					fEff=0;
				if(g_bEnglish)
					strUnit.Format("   Eff. : %.2f lm/W",fEff);
				else
					strUnit.Format("   光效 : %.2f lm/W",fEff);
				if(m_bHaveColorPara)
					sStr=sStr+strUnit;
			}
			if(iPhType==PH_F)
			{
				if(m_fPh_e>1)
				{
					strPH=PH_Name(m_iLamp,PH_Fe,strUnit,TRUE);
					strFe.Format("  %s  = %s W",strPH,g_SPEC.sFormat(m_fPh_e,4));
				}
				else
				{
					strPH=PH_Name(m_iLamp,PH_Fe,strUnit,TRUE);
					strFe.Format("  %s  = %s %s",strPH,g_SPEC.sFormat(m_fPh_e*1000,4),strUnit);
				}
				sStr=sStr+strFe;
			}
			if(iPhType==PH_E)
			{
				strPH=PH_Name(m_iLamp,PH_Ee,strUnit,TRUE);
				strFe.Format("  %s  = %s %s",strPH,g_SPEC.sFormat(m_fPh_e*1000,4),strUnit);
				sStr=sStr+strFe;
			}
			if(iPhType == PH_L)
			{
				CString strTemp;
				if(g_bEnglish)
				{
					strTemp=" (AngleView:"+m_strAngleView+" Deg)";
				}
				else
				{
					strTemp=" (视场角:"+m_strAngleView+" 度)";
				}
				sStr=sStr+strTemp;
			}
		}

		if(CSpectData::m_bPrintPh_)
		{
			if(iPhType == PH_F || iPhType == PH_E)
			{
				BOOL bPh_;
				float fPh_, fSP;

				bPh_ = CalcPh_(fPh_, fSP);
				if(bPh_ == TRUE)
				{
					CString strTemp2;
					
					if(g_bEnglish)
						strTemp2.Format(" Scotopic:%.5g S/P:%.5g", fPh_, fSP);
					else
						strTemp2.Format(" 暗视觉:%.5g S/P:%.5g", fPh_, fSP);

					sStr += strTemp2;

				}
			}
		}
		pDC->TextOut(iX,iCurY,sStr);
		iCurY=(int)(iCurY+1.0*Hn);

		if(g_bHavePhoEff)
		{
			float fMol  = 0;
			float fEff1 = 0;
			float fEff2 = 0;
			
			BOOL bPho = CalcPhoEff(fMol,fEff1,fEff2,iPhType);

			CString strTemp;
			sStr="";
			if(g_bEnglish)
			{
				strTemp = "Fmol(umol/s):";
				if(iPhType == PH_E)
					strTemp = "Fmol(umol/m2/s):";
			}
			else
			{
				strTemp = "光量子数(umol/s):";
				if(iPhType == PH_E)
					strTemp = "光量子数(umol/m2/s):";
			}
			sStr = sStr + strTemp;
			strTemp.Format("%.5g",fMol);
			if(bPho == FALSE)
				strTemp = "   ";
			sStr = sStr + strTemp;
			
			if(g_bEnglish)
			{
				strTemp=" Fluo. and blue light ratio:";
			}
			else
			{
				strTemp=" 荧光蓝光比:";
			}
			sStr = sStr + strTemp;
			strTemp = g_SPEC.sFormat(fEff1,4);
			if(bPho == FALSE)
				strTemp = "   ";
			sStr = sStr + strTemp;
		
			if(g_bEnglish)
			{
				strTemp=" Fluorescent eff.:";
			}
			else
			{
				strTemp=" 荧光效能:";
			}
			sStr = sStr + strTemp;
			strTemp = g_SPEC.sFormat(fEff2,4);
			if(bPho == FALSE)
				strTemp = "   ";
			sStr = sStr + strTemp;

			pDC->TextOut(iX,iCurY,sStr);
			iCurY=(int)(iCurY+1.0*Hn);
		}

		if(m_bHaveData&&m_fSpect1<300.0f)
		{
			CString strTemp;
			sStr="";
			strTemp=g_SPEC.sFormat(m_fKuv,4);
			strTemp="Kuv= "+strTemp;
			sStr=sStr+strTemp+"  ";
			strTemp=g_SPEC.sFormat(m_fK1,4);
			strTemp="K1= "+strTemp;
			sStr=sStr+strTemp+"  ";
			strTemp=g_SPEC.sFormat(m_fK2,4);
			strTemp="K2= "+strTemp;
			sStr=sStr+strTemp;
			pDC->TextOut(iX,iCurY,sStr);
		  	iCurY=(int)(iCurY+1.0*Hn);
		}
	}
	if(m_bTestF)
	{
		pDC->SelectObject(&Font1);
//		iCurY=(int)(iCurY+0.6*Hn);
		if(g_bEnglish)
			pDC->TextOut(iX,iCurY,"Electrical parameters");
		else
			pDC->TextOut(iX,iCurY,"电参数");

		pDC->SelectObject(&Font2);
		iCurY=(int)(iCurY+1.3*Hn);
	}
	if(m_bTestF)
	{
		if(g_bEnglish)
			sStr.Format("V = %s V     I = %s A    P = %s W PF = %s",g_SPEC.sFormat(m_fVF,4),g_SPEC.sFormat(m_fIF,4),g_SPEC.sFormat(m_fPow,4),g_SPEC.sFormat(m_fPF,4));
		else
			sStr.Format("电压 V = %s V 电流 I = %s A 功率 P = %s W 功率因数 PF = %s",g_SPEC.sFormat(m_fVF,4),g_SPEC.sFormat(m_fIF,4),g_SPEC.sFormat(m_fPow,4),g_SPEC.sFormat(m_fPF,4));
		pDC->TextOut(iX,iCurY,sStr);
		iCurY=(int)(iCurY+1.0*Hn);
	}

	if(strLevel!=""||strWhite!="")
	{
		CString sStr1 = "";
		CString sStr2 = "";
		
		if(strLevel == "")
		{
			if(g_bEnglish)
			{
				sStr.Format("WHITE:%s",strWhite);
			}
			else
			{
				sStr.Format("白光分类:%s",strWhite);
			}
		}
		else if(strWhite == "")
		{
			if(g_bEnglish)
			{
				sStr.Format("LEVEL:%s",strLevel);
			}
			else
			{
				sStr.Format("分级:%s",strLevel);
			}
			
		}
		else
		{
			if(g_bEnglish)
			{
				sStr.Format("LEVEL:%s        WHITE:%s",strLevel,strWhite);
			}
			else
			{
				sStr.Format("分级:%s        白光分类:%s",strLevel,strWhite);
			}
		}

		iCurY=(int)(iCurY+0.3*Hn);
		pDC->TextOut(iX,iCurY,sStr);
		iCurY=(int)(iCurY+1.0*Hn);
	}

	iCurY=(int)(iCurY+1.0*Hn);
	pDC->SelectObject(&Font3);
	if(g_bEnglish)
		sStr.Format("Status:  Integral T = %.0f ms  Ip = %.0f (%.0f%%)",m_fIntTime,m_fIp,m_fIp*100.0f/(m_nADW-1));
	else
		sStr.Format("仪器状态:  积分时间 T = %.0f ms  Ip = %.0f (%.0f%%)",m_fIntTime,m_fIp,m_fIp*100.0f/(m_nADW-1));
	pDC->TextOut(iX,iCurY,sStr);

	iCurY=(int)(iCurY+1.0*Hn);
	pDC->SelectObject(&Font3);
	CString sTemp;
	pDC->TextOut(iX,iCurY,sStr);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldFont);
}

void CSpectData::printColorErr(CDC *pDC, CRect mRect, float x, float y, int iSeleK, int iSDCM1, int iSDCM2)
{
	CFont *pOldFont;
	CFont Font1;


	Font1.CreateFont(mRect.Height()/22,0,0,0,600,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"MS Sans Serif");  

	const int X_NUM = 7;
	const int Y_NUM = 10;

	float ou[21];
	ou[16]=x;
	ou[17]=y;
	CPen  *pOldPen;
	CPen  Pen1;
	CPen  Pen2;
	CPen  Pen3;
	CPen  Pen4;

	if(0)
	{
		Pen1.CreatePen(PS_SOLID,2,RGB(0,0,0));
		Pen2.CreatePen(PS_SOLID,3,RGB(255,0,0));
		Pen3.CreatePen(PS_DASH,2,RGB(0,0,0));
		Pen4.CreatePen(PS_SOLID,2,RGB(0,0,0));
	}
	else
	{
		Pen1.CreatePen(PS_SOLID,2,RGB(0,0,0));
		Pen2.CreatePen(PS_SOLID,3,RGB(255,0,0));
		Pen3.CreatePen(PS_DASH,2,RGB(0,0,0));
		Pen4.CreatePen(PS_SOLID,2,RGB(0,0,255));
	}
	pOldFont=pDC->SelectObject(&Font1);
	int i,j;

	//float g[6][3]={86.0f,-40.0f,45.0f,56.0f,-25.0f,23.0f,39.5f,-21.5f,26.0f,38.0f,-20.0f,25.0f,39.0f,-19.5f,27.5f,44.0f,-18.6f,27.0f};
	float mina;//,xy[6][2]={0.313f,0.337f,0.346f,0.359f,0.38f,0.38f,0.409f,0.394f,0.440f,0.403f,0.463f,0.42f};
	//float sxy[6][2]={0.3f,0.32f,0.33f,0.340f,0.365f,0.360f,0.395f,0.375f,0.425f,0.380f,0.45f,0.4f};
	float a[1000],deltx[2],delty[2],r,sita;
	const float pi=3.14159f;
	int stp=5,sig=-1,xs=473,ys=225,xe=473+150,ye=225+200,scalex,scaley;
	//int f[6]={6500,5000,4000,3500,3000,2700};
	char scal[40];
	int Xinterval = (mRect.Width())  / (X_NUM + 2);
	int Yinterval = (mRect.Height()) / (Y_NUM + 2);
	xs=Xinterval;
	ys=Yinterval;
	xe = (X_NUM + 1) * Xinterval;
	ye = (Y_NUM + 1) * Yinterval;
	scalex = (int)(X_NUM * Xinterval / 0.03);
	scaley = (int)(Y_NUM * Yinterval / 0.04);

	int NN=g_doData.m_sdcm.GetSize();
	for(i=0;i<NN;i++)
	{
		deltx[0]=ou[16]-g_doData.m_sdcm.GetAt(i)->m_fx;
		delty[0]=ou[17]-g_doData.m_sdcm.GetAt(i)->m_fy;
		a[i]=g_doData.m_sdcm.GetAt(i)->m_fg11*deltx[0]*deltx[0]+2*g_doData.m_sdcm.GetAt(i)->m_fg12*deltx[0]*delty[0]+g_doData.m_sdcm.GetAt(i)->m_fg22*delty[0]*delty[0];
		a[i]=(float)(sqrt(a[i])*100.0);
	}
	if(iSeleK==NN)
	{
		mina=a[0];
		sig=0;
		for(i=0;i<NN;i++)
		{	
			if(a[i]<mina)
			{
				mina=a[i];
				sig=i;
			}
		}
	}
	else
	{
		mina=a[iSeleK];
		sig=iSeleK;
	}
	pOldPen=pDC->SelectObject(&Pen1);
	pDC->SetTextAlign(TA_LEFT);
	pDC->Rectangle(mRect);
	/*pDC->MoveTo(mRect.left+Xinterval,mRect.top+Yinterval);
	pDC->LineTo(mRect.right-Xinterval,mRect.top+Yinterval);
	pDC->LineTo(mRect.right-Xinterval,mRect.bottom-Yinterval);
	pDC->LineTo(mRect.left+Xinterval,mRect.bottom-Yinterval);
	pDC->LineTo(mRect.left+Xinterval,mRect.top+Yinterval);*/

	CRect xRect;
	xRect.left=mRect.left+Xinterval;
	xRect.right=mRect.right-Xinterval;
	xRect.top=mRect.top+Yinterval;
	xRect.bottom=mRect.bottom-Yinterval;
	pDC->Rectangle(xRect);

    pDC->SelectObject(&Pen3);
	for(i=1;i<X_NUM;i++)
	{
		pDC->MoveTo((int)(xRect.left+xRect.Width()*i*1.0f/X_NUM),xRect.top);
		pDC->LineTo((int)(xRect.left+xRect.Width()*i*1.0f/X_NUM),xRect.bottom);
	}

	for(i=1;i<Y_NUM;i++)
	{
		pDC->MoveTo(xRect.left,(int)(xRect.top+xRect.Height()*(i*1.0f)/Y_NUM));
		pDC->LineTo(xRect.right,(int)(xRect.top+xRect.Height()*(i*1.0f)/Y_NUM));
	}

	pDC->SetTextColor(RGB(255,0,0));
	if(!g_bEnglish)
		sprintf(scal,"色容差 %5.1f SDCM",mina);
	else
		sprintf(scal,"  %5.1f SDCM",mina);
	pDC->SetTextColor(RGB(0,0,0));
	pDC->TextOut(mRect.left+mRect.Width()/6-mRect.Width()/20,mRect.top+(int)(mRect.Height()*0.3/10),scal);
	i=sig;
	sprintf(scal,"x=%.3f y=%.3f %s",g_doData.m_sdcm.GetAt(i)->m_fx,g_doData.m_sdcm.GetAt(i)->m_fy,g_doData.m_sdcm.GetAt(i)->m_strName);
	pDC->TextOut(mRect.left+mRect.Width()/6-mRect.Width()/20,mRect.bottom-(int)(mRect.Height()*1.5f/20),scal);
	pDC->SelectObject(&Pen4);
	sita=(float)(pi/180.0);
	xe=xs+(int)((g_doData.m_sdcm.GetAt(i)->m_fx-g_doData.m_sdcm.GetAt(i)->m_fxs)*scalex);
	ye=ys+(int)(Yinterval*8-(g_doData.m_sdcm.GetAt(i)->m_fy-g_doData.m_sdcm.GetAt(i)->m_fys)*scaley);
	int iE=mRect.Width()/70;
	pDC->Ellipse(mRect.left+xe-iE,mRect.top+ye-iE,mRect.left+xe+iE,mRect.top+ye+iE);
	for(j=1;j<360;j+=stp)
	{
		r=(float)sqrt(g_doData.m_sdcm.GetAt(i)->m_fg11*(1+cos((2*j-2*stp)*sita))/2+g_doData.m_sdcm.GetAt(i)->m_fg12*sin((2*j-2*stp)*sita)+g_doData.m_sdcm.GetAt(i)->m_fg22*(1-cos((2*j-2*stp)*sita))/2);
		r=(float)(0.01f*iSDCM1/r);
		deltx[0]=(float)(r*cos((j-stp)*sita));
		delty[0]=(float)(r*sin((j-stp)*sita));
		r=(float)sqrt(g_doData.m_sdcm.GetAt(i)->m_fg11*(1+cos(2*j*sita))/2+g_doData.m_sdcm.GetAt(i)->m_fg12*sin(2*j*sita)+g_doData.m_sdcm.GetAt(i)->m_fg22*(1-cos(2*j*sita))/2);
		r=(float)(0.01f*iSDCM1/r);
		deltx[1]=(float)(r*cos(j*sita));
		delty[1]=(float)(r*sin(j*sita));
		pDC->MoveTo(mRect.left+xe+(int)(deltx[0]*scalex),mRect.top+ye-(int)(delty[0]*scaley));
		pDC->LineTo(mRect.left+xe+(int)(deltx[1]*scalex),mRect.top+ye-(int)(delty[1]*scaley));

		if(j%2)
		{
			r=(float)sqrt(g_doData.m_sdcm.GetAt(i)->m_fg11*(1+cos((2*j-2*stp)*sita))/2+g_doData.m_sdcm.GetAt(i)->m_fg12*sin((2*j-2*stp)*sita)+g_doData.m_sdcm.GetAt(i)->m_fg22*(1-cos((2*j-2*stp)*sita))/2);
			r=(float)(0.01f*iSDCM2/r);
			deltx[0]=(float)(r*cos((j-stp)*sita));
			delty[0]=(float)(r*sin((j-stp)*sita));
			r=(float)sqrt(g_doData.m_sdcm.GetAt(i)->m_fg11*(1+cos(2*j*sita))/2+g_doData.m_sdcm.GetAt(i)->m_fg12*sin(2*j*sita)+g_doData.m_sdcm.GetAt(i)->m_fg22*(1-cos(2*j*sita))/2);
			r=(float)(0.01f*iSDCM2/r);
			deltx[1]=(float)(r*cos(j*sita));
			delty[1]=(float)(r*sin(j*sita));
			pDC->MoveTo(mRect.left+xe+(int)(deltx[0]*scalex),mRect.top+ye-(int)(delty[0]*scaley));
			pDC->LineTo(mRect.left+xe+(int)(deltx[1]*scalex),mRect.top+ye-(int)(delty[1]*scaley));
		}
	}
	if(ou[16]<g_doData.m_sdcm.GetAt(i)->m_fxs) deltx[0]=g_doData.m_sdcm.GetAt(i)->m_fxs;
	else if(ou[16]>(g_doData.m_sdcm.GetAt(i)->m_fxs+0.03)) deltx[0]=(float)(g_doData.m_sdcm.GetAt(i)->m_fxs+0.03);
	else deltx[0]=ou[16];
	if(ou[17]<g_doData.m_sdcm.GetAt(i)->m_fys) delty[0]=g_doData.m_sdcm.GetAt(i)->m_fys;
	else if(ou[17]>(g_doData.m_sdcm.GetAt(i)->m_fys+0.04)) delty[0]=(float)(g_doData.m_sdcm.GetAt(i)->m_fys+0.04);
	else delty[0]=ou[17];
	xs=xs+(int)((deltx[0]-g_doData.m_sdcm.GetAt(i)->m_fxs)*scalex);
	ys=ys+(int)(Yinterval*8-(delty[0]-g_doData.m_sdcm.GetAt(i)->m_fys)*scaley);
	pDC->SelectObject(&Pen2);
	pDC->MoveTo(mRect.left+xs-mRect.Height()/50,mRect.top+ys);
	pDC->LineTo(mRect.left+xs+mRect.Height()/50,mRect.top+ys);
	pDC->MoveTo(mRect.left+xs,mRect.top+ys-mRect.Height()/50);
	pDC->LineTo(mRect.left+xs,mRect.top+ys+mRect.Height()/50);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldFont);
}

void CSpectData::DrawCIE(CDC *pDC,CRect mRect)
{
	CPen *pOldPen;
	CPen Pen1,Pen2;
	Pen1.CreatePen(PS_SOLID,1,RGB(0,0,255));
	Pen2.CreatePen(PS_SOLID,2,RGB(0,0,255));
	
	CRect xRect;
	
	xRect.left	= (int)(mRect.Width() * 0.0f / 100);
	xRect.right	= (int)(mRect.Width() - mRect.Width() * 1 / 100.0f);
	xRect.top	= (int)(mRect.Height() * 0 / 11.0f);
	xRect.bottom= (int)(mRect.Height()-mRect.Height() * 1 / 100.0f);
	
	pOldPen		= pDC->SelectObject(&Pen1);
	
	if(0)
	{
		pDC->MoveTo(xRect.left,	xRect.top);
		pDC->LineTo(xRect.left,	xRect.bottom);
		pDC->LineTo(xRect.right,xRect.bottom);
		pDC->LineTo(xRect.right,xRect.top);
	}
	
	pDC->SelectObject(&Pen2);
	pDC->SetTextAlign(TA_RIGHT);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0,0,255));
	CString sTemp;
	sTemp.Format("x = %.4f y = %.4f",m_x, m_y);

	if(m_bHaveData)
	{
		pDC->TextOut(xRect.right - xRect.Width() / 20,xRect.top + xRect.Height() / 20, sTemp);
	}
	
	if(m_fCCT > 1000 && m_fCCT < 100000)
	{
		sTemp.Format("CCT = %.0fK", m_fCCT);
	}
	else if(m_fCCT <= 1000)
	{
		sTemp.Format("CCT <= 1000K");
	}
	else
	{
		sTemp.Format("CCT >= 100000K");
	}

	if(m_bHaveData)
	{
		pDC->TextOut(xRect.right-xRect.Width()/10, xRect.top+xRect.Height()/8,sTemp);
	}
	
	int xx,yy;
	
	xx	= (int)(xRect.left+m_x*xRect.Width()/0.8f+0.5f);
	yy	= (int)(xRect.bottom-m_y*xRect.Height()/0.9f+0.5f);

	int x,y;
	
	x	= (int)(xRect.left	 + (m_x + 0.1f) * xRect.Width() + 0.5f);
	y	= (int)(xRect.bottom - (m_y + 0.1f) * xRect.Height() *10 / 11 + 0.5f);
	
	int iM = 5;
	if(m_bHaveData)
	{
		pDC->MoveTo(x-iM,y);
		pDC->LineTo(x+iM,y);
		pDC->MoveTo(x,y-iM);
		pDC->LineTo(x,y+iM);
	}
	
	pDC->SelectObject(pOldPen);
}

void CSpectData::DrawCIE_UV(CDC *pDC,CRect mRect)
{
	//画CIE1976
	CPen *pOldPen;
	CPen Pen1,Pen2;
	Pen1.CreatePen(PS_SOLID,1,RGB(0,0,255));
	Pen2.CreatePen(PS_SOLID,2,RGB(0,0,255));
	
	CRect xRect;
	
	xRect.left	= (int)(mRect.Width() * 5.0f / 100);
	xRect.right	= (int)(mRect.Width() - mRect.Width() * 6 / 100.0f);
	xRect.top	= (int)(mRect.Height() * 12 / 100.0f);
	xRect.bottom= (int)(mRect.Height()-mRect.Height() * 7.7f / 100.0f);
	
	pOldPen		= pDC->SelectObject(&Pen1);
	
	if(0)
	{
		pDC->MoveTo(xRect.left,	xRect.top);
		pDC->LineTo(xRect.left,	xRect.bottom);
		pDC->LineTo(xRect.right,xRect.bottom);
		pDC->LineTo(xRect.right,xRect.top);
	}
	
	pDC->SelectObject(&Pen2);
	pDC->SetTextAlign(TA_RIGHT);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0,0,255));
	CString sTemp;
	sTemp.Format("u'= %.4f v'= %.4f",m_u, m_v);
	
	if(m_bHaveData)
	{
		pDC->TextOut(xRect.right - xRect.Width() / 20,xRect.top + xRect.Height() / 20, sTemp);
	}
	
	if(m_fCCT > 1000 && m_fCCT < 100000)
	{
		sTemp.Format("CCT = %.0fK", m_fCCT);
	}
	else if(m_fCCT <= 1000)
	{
		sTemp.Format("CCT <= 1000K");
	}
	else
	{
		sTemp.Format("CCT >= 100000K");
	}
	
	if(m_bHaveData)
	{
		pDC->TextOut(xRect.right-xRect.Width()/10, xRect.top+xRect.Height()/8,sTemp);
	}
	
	
	int x,y;

	x	= (int)(xRect.left + m_u * xRect.Width() * 10.0f / 7.0f + 0.5f);
	y	= (int)(xRect.bottom - m_v * xRect.Height() * 10.0f / 6.0f + 0.5f);
	
	int iM = 5;
	if(m_bHaveData)
	{
		pDC->MoveTo(x-iM,y);
		pDC->LineTo(x+iM,y);
		pDC->MoveTo(x,y-iM);
		pDC->LineTo(x,y+iM);
	}
	
	pDC->SelectObject(pOldPen);
}

void CSpectData::printCIE(CDC *pDC, CRect mRect, float x, float y, float fTc)
{
	CFont *pOldFont;
	CFont Font1;
	Font1.CreateFont(mRect.Height()/20,0,0,0,800,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"Courier New");

	pOldFont=pDC->SelectObject(&Font1);

	CPen *pOldPen;
	CPen Pen1,Pen2;
	Pen1.CreatePen(PS_SOLID,3,RGB(0,0,0));
	Pen2.CreatePen(PS_SOLID,2,RGB(0,0,0));

	pOldPen=pDC->SelectObject(&Pen1);

	// Scale the temporary image.
	g_doData.m_ImageCIE_xy.Stretch( mRect.Width(), mRect.Height() );

	// Set the palette and draw.
//	if( GetFocus() == this )
//		m_Image.SetPalette( pDC );
	g_doData.m_ImageCIE_xy.Draw( pDC,mRect.left,mRect.top,mRect.Width(),mRect.Height() );

	CRect xRect;

	xRect.left	= (int)(mRect.left);
	xRect.right	= (int)(mRect.right);
	xRect.top	= (int)(mRect.top);
	xRect.bottom= (int)(mRect.bottom);

	if(1)
	{
		pDC->MoveTo(xRect.left,xRect.top);
		pDC->LineTo(xRect.left,xRect.bottom);
		pDC->LineTo(xRect.right,xRect.bottom);
		pDC->LineTo(xRect.right,xRect.top);
	}
	if(1)
	{
		pDC->MoveTo(mRect.left,mRect.top);
		pDC->LineTo(mRect.left,mRect.bottom);
		pDC->LineTo(mRect.right,mRect.bottom);
		pDC->LineTo(mRect.right,mRect.top);
		pDC->LineTo(mRect.left,mRect.top);
	}

//	pDC->SelectObject(&Pen2);
	pDC->SetTextAlign(TA_LEFT);
	pDC->SetBkMode(OPAQUE);
	pDC->TextOut(mRect.left,mRect.top+mRect.Height()/150,"CIE1931  NAHON   ");

	pDC->SetTextAlign(TA_RIGHT);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0,0,0));
	CString sTemp;
	sTemp.Format("x = %.4f y = %.4f",x,y);
	pDC->TextOut(xRect.right-xRect.Width()/20,xRect.top+xRect.Height()/20,sTemp);

	if(fTc>1000&&fTc<100000)
	{
		sTemp.Format("CCT = %.0fK",fTc);
	}
	else if(fTc<=1000)
	{
		sTemp.Format("CCT <= 1000K");
	}
	else
	{
		sTemp.Format("CCT >= 100000K");
	}

	pDC->TextOut(xRect.right-xRect.Width()/10,xRect.top+xRect.Height()/8,sTemp);

	int xx,yy;

//	xx	= (int)(xRect.left+x*xRect.Width()/0.8f+0.5f);
//	yy	= (int)(xRect.bottom-y*xRect.Height()/0.9f+0.5f);
	xx	= (int)(xRect.left	 + (m_x + 0.1f) * xRect.Width() + 0.5f);
	yy	= (int)(xRect.bottom - (m_y + 0.1f) * xRect.Height() *10 / 11 + 0.5f);

	int iM = xRect.Width()/30;
	pDC->MoveTo(xx-iM,yy);
	pDC->LineTo(xx+iM,yy);
	pDC->MoveTo(xx,yy-iM);
	pDC->LineTo(xx,yy+iM);

	pDC->SetTextColor(RGB(0,0,0));
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldFont);
}

void CSpectData::printCIE_UV(CDC *pDC, CRect mRect, float u, float v, float fTc)
{
	CFont *pOldFont;
	CFont Font1;
	Font1.CreateFont(mRect.Height()/20,0,0,0,800,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"Courier New");
	
	pOldFont=pDC->SelectObject(&Font1);
	
	CPen *pOldPen;
	CPen Pen1,Pen2;
	Pen1.CreatePen(PS_SOLID,3,RGB(0,0,0));
	Pen2.CreatePen(PS_SOLID,2,RGB(0,0,0));
	
	pOldPen=pDC->SelectObject(&Pen1);
	
	// Scale the temporary image.
	g_doData.m_ImageCIE_uv.Stretch( mRect.Width(), mRect.Height() );
	
	// Set the palette and draw.
	//	if( GetFocus() == this )
	//		m_Image.SetPalette( pDC );
	g_doData.m_ImageCIE_uv.Draw( pDC,mRect.left,mRect.top,mRect.Width(),mRect.Height() );
	
	CRect xRect;
	
	xRect.left	= (int)(mRect.left + mRect.Width() * 5.0f / 100);
	xRect.right	= (int)(mRect.left + mRect.Width() - mRect.Width() * 6 / 100.0f);
	xRect.top	= (int)(mRect.top  + mRect.Height() * 12 / 100.0f);
	xRect.bottom= (int)(mRect.top  + mRect.Height()-mRect.Height() * 7.7f / 100.0f);

	if(1)
	{
		pDC->MoveTo(xRect.left,	xRect.top);
		pDC->LineTo(xRect.left,	xRect.bottom);
		pDC->LineTo(xRect.right,xRect.bottom);
		pDC->LineTo(xRect.right,xRect.top);
	}
	if(1)
	{
		pDC->MoveTo(mRect.left,	mRect.top);
		pDC->LineTo(mRect.left,	mRect.bottom);
		pDC->LineTo(mRect.right,mRect.bottom);
		pDC->LineTo(mRect.right,mRect.top);
		pDC->LineTo(mRect.left,	mRect.top);
	}
	
	//	pDC->SelectObject(&Pen2);
	pDC->SetTextAlign(TA_LEFT);
	pDC->SetBkMode(OPAQUE);
	pDC->TextOut(mRect.left,mRect.top+mRect.Height()/150,"CIE1976 NAHON");
	
	pDC->SetTextAlign(TA_RIGHT);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0,0,0));
	CString sTemp;
	sTemp.Format("u'= %.4f v'= %.4f",u,v);
	pDC->TextOut(xRect.right-xRect.Width()/20,xRect.top+xRect.Height()/20,sTemp);
	
	if(fTc>1000&&fTc<100000)
	{
		sTemp.Format("CCT = %.0fK",fTc);
	}
	else if(fTc<=1000)
	{
		sTemp.Format("CCT <= 1000K");
	}
	else
	{
		sTemp.Format("CCT >= 100000K");
	}
	
	pDC->TextOut(xRect.right-xRect.Width()/10,xRect.top+xRect.Height()/8,sTemp);
	
	int xx,yy;
	

	xx	= (int)(xRect.left + m_u * xRect.Width() * 10.0f / 7.0f + 0.5f);
	yy	= (int)(xRect.bottom - m_v * xRect.Height() * 10.0f / 6.0f + 0.5f);
	
	int iM = xRect.Width() / 30;
	pDC->MoveTo(xx - iM, yy);
	pDC->LineTo(xx + iM, yy);
	pDC->MoveTo(xx, yy - iM);
	pDC->LineTo(xx, yy + iM);
	
	pDC->SetTextColor(RGB(0,0,0));
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldFont);
}

void CSpectData::Copy(const CSpectData &spData)
{
	//
	m_bTestF  = spData.m_bTestF;
	m_fVF     = spData.m_fVF;
	m_fIF     = spData.m_fIF;
	m_fPow    = spData.m_fPow;
	m_fPF     = spData.m_fPF;

	m_iTestType = spData.m_iTestType;
	m_bTestPH   = spData.m_bTestPH;
	m_fDistance = spData.m_fDistance;
	m_fPH       = spData.m_fPH;

	//sp
	m_bHaveData      = spData.m_bHaveData;
	m_bHaveColorPara = spData.m_bHaveColorPara;

	m_iDataType  = spData.m_iDataType;
	m_fIntTime   = spData.m_fIntTime;
	m_fInterval  = spData.m_fInterval;
	m_fSpect1    = spData.m_fSpect1;
	m_fSpect2    = spData.m_fSpect2;

	int i,iN;
	iN = spData.m_fRelSpect.GetSize();
	m_fRelSpect.RemoveAll();
	for(i = 0; i < iN; i++)
	{
		m_fRelSpect.Add(spData.m_fRelSpect[i]);
	}

	m_fIntTime   = spData.m_fIntTime;
	m_nADW       = spData.m_nADW;
	m_fPlambda   = spData.m_fPlambda;

	m_fPh        = spData.m_fPh;
	m_fPh_e      = spData.m_fPh_e;
	m_strAngleView=spData.m_strAngleView;

	m_x          = spData.m_x;
	m_y          = spData.m_y;
	m_u          = spData.m_u;
	m_v          = spData.m_v;
	m_fCCT       = spData.m_fCCT;
	m_fdc		 = spData.m_fdc;
	m_fRedRatio  = spData.m_fRedRatio;
	m_fGreenRatio= spData.m_fGreenRatio;
	m_fBlueRatio = spData.m_fBlueRatio;
	m_fMainlambda= spData.m_fMainlambda;
    m_fMaxlambda = spData.m_fMaxlambda;
	m_fPurity    = spData.m_fPurity;
	m_fHalflambda= spData.m_fHalflambda;
	m_fRa        = spData.m_fRa;

	for(i=0;i<15;i++)
		m_fRi[i] = spData.m_fRi[i];

	m_fKuv		= spData.m_fKuv;
	m_fK1		= spData.m_fK1;
	m_fK2		= spData.m_fK2;

	m_fEnTMP	= spData.m_fEnTMP;

	m_strName	= spData.m_strName;
	m_iLamp		= spData.m_iLamp;

	//测试信息
	m_strModel   = spData.m_strModel;
	m_strNumber  = spData.m_strNumber;
	m_strFactory = spData.m_strFactory;
	m_strT       = spData.m_strT;
	m_strH       = spData.m_strH;
	m_strTester  = spData.m_strTester;
	m_strDate    = spData.m_strDate;
	m_strRemark  = spData.m_strRemark;

	m_strCompany = spData.m_strCompany;
	m_strAddr	 = spData.m_strAddr;

	m_strSampleName = spData.m_strSampleName;
	m_strSampleState = spData.m_strSampleState;
	m_strSampleStandard = spData.m_strSampleStandard;
	m_strColorCorrectStr = spData.m_strColorCorrectStr;

	m_strFilter = spData.m_strFilter;

	m_strSN = spData.m_strSN;
}

CSpectData& CSpectData::operator =(const CSpectData &spData)
{
	Copy(spData);
	return *this;
}

void CSpectData::Init()
{
	m_iCoolState = 1;
	m_strFilter = "";
	m_iLamp	 = 0;
	//
	m_bTestF = FALSE;
	m_fVF    = 0;  //V
	m_fIF    = 0;  //mA
	m_fPow   = 0;
	m_fPF    = 1;

	m_iTestType = 1;
	m_bTestPH   = FALSE;
	m_fDistance = 0.1f;
	m_fPH       = 0;
	m_fPh		= 0;

	//
	m_bHaveData      = FALSE;
	m_bHaveColorPara = FALSE;

	m_nADW      = 65535;
	m_iDataType = TYPE_SCAN;

	m_fRelSpect.RemoveAll();

	m_fSpect1   = g_SPEC.T_SPECT1;
	m_fSpect2   = g_SPEC.T_SPECT2;
	m_fInterval = 1.0f;
	int iN = 421;
	int i;

	m_x = m_y = 0;
	m_u = m_v = 0;
	m_fCCT       = 0;
	m_fRedRatio  = 0;
	m_fMainlambda= 0;
    m_fMaxlambda = 0;
	m_fPurity    = 0;
	m_fHalflambda= 0;
	m_fRa        = 0;

	for(i = 0; i < 15; i++)
	{
		m_fRi[i] = i * 1.0f;
	}

	m_fE_SP1	= g_SPEC.T_SPECT1;
	m_fE_SP2	= g_SPEC.T_SPECT2;

	m_fEnTMP	= 20;

	m_strAngleView = g_SPEC.m_strViewL_Name[g_SPEC.m_iSeleL];

	m_fKuv		= 0;
	m_fK1		= 0;
	m_fK2		= 0;
	m_strColorCorrectStr = "";
}

void CSpectData::RD_Info()
{
	CString strSection    = "SpectraNexus Info";

	CString strModel      = "Model";
	CString strNumber     = "Number";
	CString strFactory    = "Factory";
	CString strT          = "T";
	CString strH          = "H";
	CString strTester     = "Tester";
	CString strRemark     = "Remark";

	m_strModel   = AfxGetApp()->GetProfileString(strSection,strModel,	"LIGHT");
	m_strNumber  = AfxGetApp()->GetProfileString(strSection,strNumber,	"N-00000");
	m_strFactory = AfxGetApp()->GetProfileString(strSection,strFactory,	"NAHON");
	m_strT       = AfxGetApp()->GetProfileString(strSection,strT,	"25.3");
	m_strH       = AfxGetApp()->GetProfileString(strSection,strH,	"65.0");
	m_strTester  = AfxGetApp()->GetProfileString(strSection,strTester,	"DAMIN");
	m_strRemark  = AfxGetApp()->GetProfileString(strSection,strRemark,	"---");

	CString str_m_strSampleName = _T("m_strSampleName");
	CString str_m_strSampleStandard = _T("m_strSampleStandard");
	CString str_m_strSampleState = _T("m_strSampleState");
	
	m_strSampleName = AfxGetApp()->GetProfileString(strSection, str_m_strSampleName, _T(""));
	m_strSampleStandard = AfxGetApp()->GetProfileString(strSection, str_m_strSampleStandard, _T(""));
	m_strSampleState = AfxGetApp()->GetProfileString(strSection, str_m_strSampleState, _T(""));
}

void CSpectData::WR_Info()
{
	CString strSection    = "SpectraNexus Info";

	CString strModel      = "Model";
	CString strNumber     = "Number";
	CString strFactory    = "Factory";
	CString strT          = "T";
	CString strH          = "H";
	CString strTester     = "Tester";
	CString strRemark     = "Remark";

	AfxGetApp()->WriteProfileString(strSection,strModel,m_strModel);
	AfxGetApp()->WriteProfileString(strSection,strNumber,m_strNumber);
	AfxGetApp()->WriteProfileString(strSection,strFactory,m_strFactory);
	AfxGetApp()->WriteProfileString(strSection,strT,m_strT);
	AfxGetApp()->WriteProfileString(strSection,strH,m_strH);
	AfxGetApp()->WriteProfileString(strSection,strTester,m_strTester);
	AfxGetApp()->WriteProfileString(strSection,strRemark,m_strRemark);

	CString str_m_strSampleName = _T("m_strSampleName");
	CString str_m_strSampleStandard = _T("m_strSampleStandard");
	CString str_m_strSampleState = _T("m_strSampleState");
	
	AfxGetApp()->WriteProfileString(strSection, str_m_strSampleName, m_strSampleName);
	AfxGetApp()->WriteProfileString(strSection, str_m_strSampleStandard, m_strSampleStandard);
	AfxGetApp()->WriteProfileString(strSection, str_m_strSampleState, m_strSampleState);
}

BOOL CSpectData::Export_CSV(CString strPathName,float fIntervalWL)
{
	FILE *fp;
    if((fp = fopen(strPathName,"wt")) == 0)
	{
		if(g_bEnglish)
		{
			AfxMessageBox("Save file fail!", MB_ICONINFORMATION);
		}
		else
		{
			AfxMessageBox("保存文件失败!", MB_ICONINFORMATION);
		}
		return FALSE;
	}
    else
	{    
		int i;
		CString strTemp;
		CString sUnit = " ";

		if(m_iTestType == 0)
		{
			sUnit = "";
		}
		else if(m_iTestType == 1)
		{
			sUnit = "(mW/nm)";
		}
		else if(m_iTestType == 2)
		{
			sUnit = "(mW/m2/nm)";
		}
		else if(m_iTestType == 3)
		{
			sUnit = "(mW/sr/nm)";
		}
		else if(m_iTestType == 4)
		{
			sUnit = "(mW/m2/sr/nm)";
		}

		if(g_bEnglish)
		{
			strTemp = "WL(nm)";
			fprintf(fp,strTemp);
			fprintf(fp,"	");

			strTemp = "PL";
			fprintf(fp,strTemp);
			fprintf(fp,"	");

			strTemp = "PE" + sUnit;
			fprintf(fp,strTemp);
			fprintf(fp,"	");
		}
		else
		{
			strTemp = "WL(nm)";
			fprintf(fp,strTemp);
			fprintf(fp,"	");

			strTemp = "相对光谱";
			fprintf(fp,strTemp);
			fprintf(fp,"	");

			strTemp = "绝对光谱" + sUnit;
			fprintf(fp,strTemp);
			fprintf(fp,"	");
		}
		fprintf(fp,"\n");

		int NN;
		if(fIntervalWL < m_fInterval)
		{
			fIntervalWL = m_fInterval;
		}

		NN	= (int)(fIntervalWL / m_fInterval + 0.5f);
		int iN = m_fRelSpect.GetSize();

		iN = (iN - 1) / NN + 1;
		for(i = 0; i < iN; i++)
		{
			strTemp.Format("%.1f", m_fSpect1 + fIntervalWL * i);
			fprintf(fp, strTemp);
			fprintf(fp,"	");

			strTemp.Format("%.4f", m_fRelSpect[i * NN]);
			fprintf(fp, strTemp);
			fprintf(fp,"	");

			strTemp.Format("%.4g",m_fRelSpect[i * NN] * m_fPlambda);
			fprintf(fp,strTemp);
//			fprintf(fp,"	");
			fprintf(fp,"\n");
		}
		fclose(fp);
		return TRUE;
	}
}

BOOL CSpectData::SP_Save(CString strPathName)
{
	CFile sFile;
	if(!sFile.Open(strPathName,CFile::modeCreate|CFile::modeReadWrite))
	{
		return FALSE;
	}

    CArchive ar(&sFile,CArchive::store);
	Serialize(ar);
	ar.Close();
	sFile.Close();	
	return TRUE;
}

float CSpectData::GetWL12_Ee(float fSP1, float fSP2, float fE)
{
	if(!m_bHaveData)
	{
		return 0.0f;
	}

	int iB = (int)((fSP1 - m_fSpect1) / m_fInterval + 0.5f);
	int iE = (int)((fSP2 - m_fSpect1) / m_fInterval + 0.5f);

	int i;
	int iN;
	iN = m_fRelSpect.GetSize();
	float fA = 0;

	for(i = 0; i < iN; i++)
	{
		fA = fA + m_fRelSpect[i];
	}

	float fD = 0;
	for(i = iB; i <= iE; i++)
	{
		fD = fD + m_fRelSpect[i];
	}

	if(fA <= 0)
	{
		return 0.0f;
	}

	return fD * fE / fA;
}

CString CSpectData::PH_Name(int iLamp,int iPhType,CString &strUnit,BOOL bAddCH)
{
	CString strTemp = "";
	if(iLamp == 0)
	{
		if(iPhType == PH_F)
		{
			if(g_bEnglish)
			{
				strTemp = "Flux";
			}
			else
			{
				strTemp = "Φ";
			}

			if(!g_bEnglish && bAddCH)
			{
				strTemp = "光通量   " + strTemp;
			}

			strUnit = "lm";
		}
		if(iPhType == PH_I)
		{
			strTemp = "I";
			
			if(!g_bEnglish && bAddCH)
			{
				strTemp = "光强     " + strTemp;
			}

			strUnit = "cd";
		}
		if(iPhType == PH_L)
		{
			strTemp = "L";
			if(!g_bEnglish && bAddCH)
			{
				strTemp = "光亮度   " + strTemp;
			}

			strUnit = "cd/m2";
		}
		if(iPhType == PH_Fe)
		{
			if(g_bEnglish)
			{
				strTemp = "Fe";
			}
			else
			{
				strTemp = "Φe";
			}
			if(!g_bEnglish && bAddCH)
			{
				strTemp = "辐射通量 " + strTemp;
			}
			strUnit = "mW";
		}
		if(iPhType == PH_Ie)
		{
			strTemp = "Ie";
			if(!g_bEnglish && bAddCH)
			{
				strTemp = "辐射强度 " + strTemp;
			}
			strUnit = "mW/Sr";
		}
		if(iPhType == PH_Le)
		{
			strTemp = "Le";
			if(!g_bEnglish && bAddCH)
			{
				strTemp = "辐射亮度 " + strTemp;
			}
			strUnit = "W/m2/Sr";
		}
		if(iPhType == PH_E)
		{
			strTemp = "E";
			if(!g_bEnglish && bAddCH)
			{
				strTemp = "光照度   " + strTemp;
			}
			strUnit = "lx";
		}
		if(iPhType == PH_Ee)
		{
			strTemp = "Ee";
			if(!g_bEnglish && bAddCH)
			{
				strTemp = "辐射照度 " + strTemp;
			}
			strUnit = "W/m2";
		}
	}
	else
	{
		if(iPhType == PH_F)
		{
			strTemp = "L";
			if(!g_bEnglish && bAddCH)
			{
				strTemp = "相对亮度 " + strTemp;
			}
			strUnit = "";
		}
	}
	return strTemp;
}

CString CSpectData::PH_Name(int iLamp,int iPhType,BOOL bAddCH)
{
	CString strUnit;
	return PH_Name(iLamp,iPhType,strUnit,bAddCH) + "(" + strUnit + ")";
}

CString CSpectData::DATA_Name(int iPara, int iPhType)
{
	if(iPara == PARA_None)
	{
		return "NONE";
	}
	if(iPara == PARA_Ip)
	{
		return "Ip";
	}
	if(iPara == PARA_VF)
	{
		if(g_bEnglish)
		{
			return "U(V)";
		}
		else
		{
			return "电压 U(V)";
		}
	}
	if(iPara == PARA_IF)
	{
		if(g_bEnglish)
		{
			return "I(A)";
		}
		else
		{
			return "电流 I(A)";
		}
	}
	if(iPara == PARA_P)
	{
		if(g_bEnglish)
		{
			return "P(W)";
		}
		else
		{
			return "功率 P(W)";
		}
	}
	if(iPara == PARA_VR)
	{
		if(g_bEnglish)
		{
			return "VR(V)";
		}
		else
		{
			return "反向电压 VR(V)";
		}
	}
	if(iPara == PARA_IR)
	{
		if(g_bEnglish)
		{
			return "IR(uA)";
		}
		else
		{
			return "反向漏电流 IR(uA)";
		}
	}
	if(iPara == PARA_PH)
	{
//		return PH_Name(iPhType)+"";
	}
	if(iPara == PARA_EFF)
	{
		if(g_bEnglish)
		{
			return "Eff.(lm/W)";
		}
		else
		{
			return "光效(lm/W)";
		}
	}
	if(iPara == PARA_x)
	{
		if(g_bEnglish)
		{
			return "x";
		}
		else
		{
			return "色坐标 x";
		}
	}
	if(iPara == PARA_y)
	{
		if(g_bEnglish)
		{
			return "y";
		}
		else
		{
			return "色坐标 y";
		}
	}
	if(iPara == PARA_u)
	{
		if(g_bEnglish)
		{
			return "u'";
		}
		else
		{
			return "色坐标 u'";
		}
	}
	if(iPara == PARA_v)
	{
		if(g_bEnglish)
		{
			return "v'";
		}
		else
		{
			return "色坐标 v'";
		}
	}
	if(iPara == PARA_Tc)
	{
		if(g_bEnglish)
		{
			return "CCT(K)";
		}
		else
		{
			return "色温(K)";
		}
	}
	if(iPara == PARA_Ld)
	{
		if(g_bEnglish)
		{
			return "Ld(nm)";
		}
		else
		{
			return "主波长(nm)";
		}
	}
	if(iPara == PARA_Pur)
	{
		if(g_bEnglish)
		{
			return "Pur(%)";
		}
		else
		{
			return "色纯度(%)";
		}
	}
	if(iPara == PARA_Lp)
	{
		if(g_bEnglish)
		{
			return "Lp(nm)";
		}
		else
		{
			return "峰值波长(nm)";
		}
	}
	if(iPara == PARA_HW)
	{
		if(g_bEnglish)
		{
			return "FWHM(nm)";
		}
		else
		{
			return "半宽度(nm)";
		}
	}
	if(iPara == PARA_RR)
	{
		if(g_bEnglish)
		{
			return "Red Ratio(%)";
		}
		else
		{
			return "红色比(%)";
		}
	}
	if(iPara == PARA_Ra)
	{
		return "Ra";
	}
	return "";
}
extern BOOL g_Use_FluxLamp_SelfCal;

void CSpectData::DoPh_e(int iPhType)
{
	//使用光度探头的光通量来计算辐射通量
	//m_fPH   探头测试的光通量数据
	//m_fPh   光谱仪计算的光通量数据
	//m_fPh_e 光谱仪计算的辐射通量数据
	//理论上　m_fPH  == m_fPh的
	//修改m_fPh的同时，要修改m_fPh_e
	if(iPhType == PH_F && m_bTestPH)
	{
		//有光谱数据
		if(m_bHaveData)
		{
			if(m_fPh > 0 && m_fPH > 0)
			{
				m_fPh_e	= m_fPh_e / m_fPh * m_fPH;
				m_fPh	= m_fPH;


				if(g_Use_FluxLamp_SelfCal == TRUE)
				{
					m_fPH *= g_SPEC.m_fluxLampSelfCalData.m_fCalK;
					m_fPh *= g_SPEC.m_fluxLampSelfCalData.m_fCalK;
					m_fPh_e *= g_SPEC.m_fluxLampSelfCalData.m_fCalK;
				}
			}
		}
	}
}

void CSpectData::Demo()
{
	m_bHaveData	= TRUE;
	
	m_bTestPH   = true;
	m_fDistance = 0.316f;  //测试距离 对光强与辐射强度有用
	m_fPH       = 1.3f + rand() * 1.0f / RAND_MAX;

	m_bTestF  = TRUE;
	m_fVF     = 2.341f;	//V
	m_fIF     = 20.0f;	//mA
	m_fPow    = 40.0f;
	m_fPF     = 1.00f;

	m_x = m_y = rand() * 0.5f / RAND_MAX;
	m_u = m_v = rand() * 0.5f / RAND_MAX;
	m_fCCT       = 2856;
	m_fRedRatio  = 12.5f;
	m_fMainlambda= 560.1f;
	m_fMaxlambda = 599.8f;
	m_fPurity    = 75.1f;
	m_fHalflambda= 12.9f;
	m_fRa        = 99.4f;

	m_fPh		 = 10.01f;
	m_fPh_e		 = 0.0124f;
	m_fPlambda	 = 1;
	m_fIp		 = 50000;

	m_fIntTime  = 100;                 //积分时间
	m_fInterval = 1.0f;                //间隔波长
	m_fSpect1   = g_SPEC.T_SPECT1;
	m_fSpect2   = g_SPEC.T_SPECT2;     //波长范围

	m_fRelSpect.RemoveAll();

	for(int i = 0; i < (g_SPEC.T_SPECT2 - g_SPEC.T_SPECT1 + 1); i++)
	{
		m_fRelSpect.Add(i * 1.0f / (g_SPEC.T_SPECT2 - g_SPEC.T_SPECT1));
	}

	m_fEnTMP  = 20;
}

float CSpectData::GetEe(int iB1,int iB2)
{
	float fEe = 0;
	if(iB1 == iB2)
	{
		return 0;
	}
	
	int iN = m_fRelSpect.GetSize();
	if(iN <= 0)
	{
		return 0;
	}

	for(int i = iB1; i < iB2; i++)
	{
		fEe = (float)(fEe + m_fPlambda * m_fRelSpect[i] * m_fInterval);
	}
	return fEe;
}

BOOL CSpectData::CalcPhoEff(float &fMol, float &fEff1, float &fEff2, int iPhType)
{
	if(iPhType != PH_F
		&& iPhType != PH_E)
	{
		return FALSE;
	}

	// 
	// 计算 转换效率
	//
	fMol  = 0; // 光量子数  单位为umol/s
	fEff1 = 0; // 转换效率
	fEff2 = 0; // 转换光效 W/W
	
	if(!m_bHaveData)
	{
		return FALSE;
	}
	
	
	int i;
	
	float fPh_e = 0;
	for(i = 0; i < m_fRelSpect.GetSize(); i++)
	{
		fPh_e += m_fRelSpect[i] * m_fInterval;
	}
	
	float fK;
	if(fPh_e > 0)
	{
		fK = m_fPh_e / fPh_e;
	}
	else
	{
		fK = 1.0f;
	}
	
	int iN = m_fRelSpect.GetSize();
	float *pWL = new float [iN];
	float *pPL = new float [iN];
	
	for(i = 0; i < iN; i++)
	{
		pWL[i] = m_fSpect1 + i * m_fInterval;
		pPL[i] = m_fRelSpect[i] * fK;  // W/nm
	}
	
	float fPower = m_fVF * m_fIF / 1000.0f;  // W
	
	g_SPEC.SPEC_CalcPhoEff(iN, pWL, pPL, fPower, g_bPhoEffSetAuto,
							g_fSpectB1, g_fSpectB2, 
							g_fSpectY1, g_fSpectY2,
							fMol, fEff1, fEff2);
	
	if(!m_bTestF)
	{
		fEff2 = 0.0f;
	}
	
	delete [] pWL;
	delete [] pPL;
	return TRUE;
}

float CSpectData::GetSDCM(int iSeleK)
{
	float ou[21];
	ou[16] = m_x;
	ou[17] = m_y;
	
	int i;
	
	//float g[6][3]={86.0f,-40.0f,45.0f,56.0f,-25.0f,23.0f,39.5f,-21.5f,26.0f,38.0f,-20.0f,25.0f,39.0f,-19.5f,27.5f,44.0f,-18.6f,27.0f};
	float mina;//xy[6][2]={0.313f,0.337f,0.346f,0.359f,0.38f,0.38f,0.409f,0.394f,0.440f,0.403f,0.463f,0.42f};
	//float sxy[6][2]={0.3f,0.32f,0.33f,0.340f,0.365f,0.360f,0.395f,0.375f,0.425f,0.380f,0.45f,0.4f};
	float a[1000],deltx[2],delty[2];
	const float pi = 3.14159f;
	//int f[6]={6500,5000,4000,3500,3000,2700};
	
	int NN = g_doData.m_sdcm.GetSize();
	
	for(i = 0; i < NN; i++)
	{
		deltx[0] = ou[16] - g_doData.m_sdcm.GetAt(i)->m_fx;
		delty[0] = ou[17] - g_doData.m_sdcm.GetAt(i)->m_fy;
		
		a[i] = g_doData.m_sdcm.GetAt(i)->m_fg11 * deltx[0] * deltx[0]
			+ 2 * g_doData.m_sdcm.GetAt(i)->m_fg12 * deltx[0] * delty[0]
			+     g_doData.m_sdcm.GetAt(i)->m_fg22 * delty[0] * delty[0];
		
		a[i] = (float)(sqrt(a[i]) * 100.0);
	}
	
	int sig = 0;
	if(iSeleK == NN)
	{
		mina = a[0];
		sig  = 0;
		for(i = 0; i < NN; i++)
		{	
			if(a[i] < mina)
			{
				mina = a[i];
				sig  = i;
			}
		}
	}
	else
	{
		mina = a[iSeleK];
		sig  = iSeleK;
	}

	return mina;
}

BOOL CSpectData::GetDW(float fPosWL, float &fDW)
{
	if(!m_bHaveData)
		return FALSE;

	if(fPosWL <= m_fSpect1)
		return FALSE;

	if(fPosWL >= m_fSpect2)
		return FALSE;

	const float fBW = 10.0f; //左右10nm查找
	int i;
	int iN = m_fRelSpect.GetSize();

	int iBW1 = 0;
	int iBW2 = iN - 1;

	for(i = 0; i < iN; i++)
	{
		float fWL = m_fSpect1 + i * m_fInterval;
		if(fWL >= (fPosWL - fBW))
		{
			iBW1 = i;
			break;
		}
	}
	
	for(i = 0; i < iN; i++)
	{
		float fWL = m_fSpect1 + i * m_fInterval;
		if(fWL >= (fPosWL + fBW))
		{
			iBW2 = i;
			break;
		}
	}


	float fPer = 0.5f;
	
	float fMax = m_fRelSpect[iBW1];
	int iMax = iBW1;
	for(i = iBW1; i < iBW2; i++)
	{
		if(fMax < m_fRelSpect[i])
		{
			fMax = m_fRelSpect[i];
			iMax = i;
		}
	}
	
	int iL = iBW1;
	int iR = iBW2;
	for(i = iMax; i > iBW1; i--)
	{
		if(m_fRelSpect[i] < (fMax * fPer))
		{
			iL = i + 1;
			break;
		}
	}
	
	for(i = iMax; i < iBW2; i++)
	{
		if(m_fRelSpect[i] < (fMax * fPer))
		{
			iR = i - 1;
			break;
		}
	}
	
	fDW = (float)(iR - iL) * m_fInterval;

	return TRUE;
}

void CSpectData::ProGetWL12(float fWL1, float fWL2)
{
	if(!m_bHaveData)
		return;

	CArray<int, int> iRemovePos;
	for(int i = 0; i < m_fRelSpect.GetSize(); i++)
	{
		float fTempWL = m_fSpect1 + m_fInterval * i;
		if(fTempWL < fWL1 || fTempWL > fWL2)
			iRemovePos.Add(i);
	}

	int iNum = m_fRelSpect.GetSize();
	for(i = 0; i < iRemovePos.GetSize(); i++)
	{
		int iSele = iNum - 1 - iRemovePos[i];
		m_fRelSpect.RemoveAt(iSele);
	}

	if(m_fSpect1 < fWL1)
		m_fSpect1 = fWL1;

	if(m_fSpect2 > fWL2)
		m_fSpect2 = fWL2;

	return;
}

BOOL CSpectData::ReadV2(CString strPathName)
{
	FILE *fp;
	if((fp = fopen(strPathName, "rt")) == NULL)
	{
		return FALSE;
	}
	else
	{
		fscanf(fp,"NUM:%d\n", &m_iv2Num);
		for(int i = 0; i < m_iv2Num; i++)
			fscanf(fp, "%f %f\n", &m_fv2WL[i], &m_fv2VL[i]);
	}    
	
	fclose(fp);
	return TRUE;
}

/* 计算暗觉光度值及比值 */
BOOL CSpectData::CalcPh_(float &fPh_, float &fSP)
{
	if(m_iv2Num < 401)
		return FALSE;

	if(!m_bHaveData)
		return FALSE;

	if(m_fSpect1 > 380)
		return FALSE;

	if(m_fSpect2 < 780)
		return FALSE;

	int iTestNum = m_fRelSpect.GetSize();
	float *pWL = new float [iTestNum];
	float *pPL = new float [iTestNum];

	int i;
	for(i = 0; i < iTestNum; i++)
	{
		pWL[i] = m_fSpect1 + m_fInterval * i;
		pPL[i] = m_fRelSpect[i];
	}

	float fTempPh, fTempPh_;

	fTempPh = 0;
	fTempPh_ = 0;

	for(i = 0; i < 401; i++)
	{
		float fWL = 380 + i * 1.0f;

		float fPL = g_doData.NewInt_float(pWL, pPL, iTestNum, fWL);
		float fV = NH_GetV(fWL);
		float fV_ = g_doData.NewInt_float(m_fv2WL, m_fv2VL, m_iv2Num, fWL);

		fTempPh += (683 * fPL * fV);
		fTempPh_ += (1700 * fPL * fV_);
	}

	delete [] pWL;
	delete [] pPL;


	if(fTempPh <= 0)
		return FALSE;

	fSP = fTempPh_ / fTempPh;
	fPh_ = m_fPH * fSP;
	return TRUE;
}

void CSpectData::DoADSpecForCal(float fLimitWL, float fSetAD)
{
	int iN = m_fRelSpect.GetSize();
	if(iN <= 0)
		return;

	if(fabsf(m_fSpect2 -m_fSpect1) <= fLimitWL * 2)
		return;

	if(fLimitWL <= 0.0f)
		return;

	int i;

	float fStartWL1 = m_fSpect1;
	float fStartWL2 = m_fSpect1 + fLimitWL;

	float fEndWL1 = m_fSpect2 - fLimitWL;
	float fEndWL2 = m_fSpect2;

	float fWL;

	for(i = 0; i < iN; i++)
	{
		fWL = m_fSpect1 + i * m_fInterval;
		if(fWL >= fStartWL1 && fWL <= fStartWL2)
		{
			if(m_fRelSpect[i] > fSetAD)
				return;
		}

		if(fWL >= fEndWL1 && fWL <= fEndWL2)
		{
			if(m_fRelSpect[i] > fSetAD)
				return;
		}
	}

	float fStartPL1 = 0;
	float fStartPL2 = 0;

	float fEndPL1 = 0;
	float fEndPL2 = 0;

	for(i = 0; i < iN; i++)
	{
		fWL = m_fSpect1 + i * m_fInterval;
		if(fWL == fStartWL2)
		{
			fStartPL2 = m_fRelSpect[i];
			break;
		}
	}
	fStartPL1 = 0.6f * fStartPL2;

	for(i = 0; i < iN; i++)
	{
		fWL = m_fSpect1 + i * m_fInterval;
		if(fWL == fEndWL1)
		{
			fEndPL1 = m_fRelSpect[i];
			break;
		}
	}
	fEndPL2 = 0.6f * fEndPL1;

	for(i = 0; i < iN; i++)
	{
		fWL = m_fSpect1 + i * m_fInterval;
		if(fWL >= fStartWL1 && fWL <= fStartWL2)
		{
			m_fRelSpect[i] = fStartPL1 +  (fWL - fStartWL1) * (fStartPL2 - fStartPL1) /(fStartWL2 - fStartWL1);
		}
		
		if(fWL >= fEndWL1 && fWL <= fEndWL2)
		{
			m_fRelSpect[i] = fEndPL1 +  (fWL - fEndWL1) * (fEndPL2 - fEndPL1) /(fEndWL2 - fEndWL1);
		}
	}

	return;
}

BOOL CSpectData::DoSpectrumSelfCorrect(CSelfCorrectData &data)
{
	if(m_bHaveData == FALSE)
		return FALSE;

	if(m_fRelSpect.GetSize() <=  0)
		return FALSE;

	if(m_fSpect1 > 380)
		return FALSE;

	if(m_fSpect2 < 780)
		return FALSE;

	if(data.m_iSaveTestNum <= 10)
		return FALSE;

	if(data.m_iSaveRefNum <= 10)
		return FALSE;

	int iN = m_fRelSpect.GetSize();
	float *pWL = new float [iN];
	float *pPL = new float [iN];

	int i;
	for(i = 0; i < iN; i++)
	{
		pWL[i] = m_fSpect1 + i * m_fInterval;
		pPL[i] = m_fRelSpect[i];
	}

	float fPh1 = 0;
	float fPh2 = 0;
	for(i = 0; i < 401; i++)
	{
		float fWL		= 380 + i * 1.0f;
		float fPL		= g_doData.NewInt_float(pWL, pPL, iN, fWL);
		float fTEST_PL	= g_doData.NewInt_float(data.m_fSave_TestWL, data.m_fSave_TestPL, data.m_iSaveTestNum, fWL);
		float fREF_PL	= g_doData.NewInt_float(data.m_fSave_RefWL, data.m_fSave_RefPL, data.m_iSaveRefNum, fWL);

		fPh1 += (fPL * NH_GetV(fWL));
		fPh2 += (((fPL * 1)/(fTEST_PL / fREF_PL)) *  NH_GetV(fWL));
	}
	delete [] pWL;
	delete [] pPL;

	float fK = 1;

	if(fPh1 > 0)
		fK = fPh2 / fPh1;

	m_fPh *= fK;
	m_fPH *= fK;
	m_fPh_e *= fK;
	m_fPlambda *= fK;

	return TRUE;
}
