// CIEDiagram.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "CIEDiagram.h"
#include "Functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCIEDiagram dialog


CCIEDiagram::CCIEDiagram(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CCIEDiagram::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCIEDiagram)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCIEDiagram::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCIEDiagram)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCIEDiagram, CResizingDialog)
	//{{AFX_MSG_MAP(CCIEDiagram)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_CIEPicture, OnCIEPicture)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCIEDiagram message handlers
extern int screen_width, screen_height;
extern float change_width, change_height;
extern int after_width, after_height;
extern int after_top, after_left;
extern int intChip;
extern bool usespectrum[3];
extern double x[3], y[3];
extern CList<XYLEVELItem, XYLEVELItem> levelItem[3];
extern bool CIEDiagram;

PictureParam picParam2;
double rate;
double xstart2 = 0;
double xend2 = 0.8;
double ystart2 = 0;
double yend2 = 0.9;
double ChangeRate2 = 0;

extern CList<sngPOINT, sngPOINT> dot[3];

CDC MemDC;

BOOL CCIEDiagram::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	pWnd_picture=GetDlgItem(IDC_CIEPicture);
	pWnd_picture->GetClientRect(&rect);
	
	pDC_picture=pWnd_picture->GetDC(); 

	width = 0;
	MoveWindowSmall();

	standard.x = (int)(0.3333 * 300);
	standard.y = (int)(270 - 0.3333 * 300);

	InitPictureParam();
	DrawPic();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCIEDiagram::DrawPic()
{
	int i = 0;

	MemDC.DeleteDC();
	CBitmap MemBitmap;

	MemDC.CreateCompatibleDC(NULL);
	MemBitmap.CreateCompatibleBitmap(pDC_picture, width, 270);
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(0, 0, width, 270, RGB(120, 195, 232));

	CBitmap bitmapbk;
	BITMAP bm;
	bitmapbk.LoadBitmap(IDB_CIE);
	bitmapbk.GetBitmap(&bm);
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(&MemDC);
	CBitmap* pOldBitmap = dcMemory.SelectObject(&bitmapbk);	
	int bmpstartX = 0, bmpstartY = 0;
	bmpstartX = (int)(xstart2 * 300);
	bmpstartY = (int)(270 - yend2 * 300);
	MemDC.StretchBlt(0, 0, (int)(240 * rate), (int)(270 * rate), 
		&dcMemory, bmpstartX, bmpstartY, 240, 270, SRCCOPY);
	
	CBrush brush, *oldbrush;
	brush.CreateSolidBrush(RGB(0, 0, 0));
	oldbrush = MemDC.SelectObject(&brush);
	CPoint dotPoint;
	sngPOINT point;
	POSITION pos = dot[0].GetHeadPosition();
	while(pos != NULL)
	{
		point = dot[0].GetNext(pos);
		dotPoint.x = (int)((point.x - xstart2) * picParam2.ratex);
		dotPoint.y = (int)(picParam2.height - (point.y - ystart2) * picParam2.ratey);
		MemDC.Ellipse(dotPoint.x-1, dotPoint.y-1, dotPoint.x+1, dotPoint.y+1);
	}
	MemDC.SelectObject(oldbrush);
	
	////////////////////////////
	CPoint p[4]; 
	XYLEVELItem item;
	
	POSITION pos2 = levelItem[0].GetHeadPosition();
	while(pos2 != NULL)
	{
		item = levelItem[0].GetNext(pos2);
		for(i=0; i<4; i++)
		{
			p[i].x = (int)((item.x[i] - xstart2) * picParam2.ratex);
			p[i].y = (int)(picParam2.height - (item.y[i] - ystart2) * picParam2.ratey);
		}
		DrawRect(p, &MemDC);
	}
	
	MemBitmap.DeleteObject();
}

BOOL CCIEDiagram::MoveWindowBig()
{	
	after_left = (int)(225*change_width);	
	after_top = (int)(360*change_height);
	after_width = (int)(845*change_width);	
	after_height = (int)(308*change_height);

	MoveWindow(after_left, after_top, after_width, after_height);
	pWnd_picture->MoveWindow(24, 10, 800, 275);

	return true;
}

BOOL CCIEDiagram::MoveWindowSmall()
{	
	after_left = (int)(710*change_width);	
	after_top = (int)(350*change_height);
	after_width = (int)(335*change_width);
	after_height = (int)(308*change_height);
	MoveWindow(after_left, after_top, after_width, after_height);

	width = 240;
	pWnd_picture->MoveWindow(22, 15, width, 270);

	return true;
}


void CCIEDiagram::InitPictureParam() 
{
	xstart2 = 0;
	xend2 = 0.8;
	ystart2 = 0;
	yend2 = 0.9;
	
	ChangeRate2 = 0.5;
	rate = 1;

	picParam2.width = 240;
	picParam2.height = 270;
	picParam2.top = 22;
	picParam2.left = 15;
	picParam2.scalex = picParam2.width / 8;
	picParam2.scaley = picParam2.height / 9;
	picParam2.ratex = picParam2.scalex / 0.1;
	picParam2.ratey = picParam2.scaley / 0.1;
}


void CCIEDiagram::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	int i;
	CString str;

	dc.SetBkMode(TRANSPARENT);

	for(i=0; i<8; i++)
	{
		str.Format("%0.1f", i*0.1);
		dc.TextOut(14 + i*30, 290, str);
	}
	dc.TextOut(246, 290, "0.8");
	
	for(i=1; i<10; i++)
	{
		str.Format("%0.1f", i*0.1);
		dc.TextOut(2, 278 - i*30, str);
	}
	
	if(0)
	{	
		CPen pen0, pen1, pen2, pen3;
		CPen *ptrPenOld;
		int nMode;
		pen0.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		ptrPenOld = MemDC.SelectObject(&pen0);
		nMode = MemDC.SetROP2(R2_COPYPEN);
		
		CPoint st, en;
		for(i=1; i<9; i++)
		{
			st.x = i * 30;
			st.y = 266;
			en.x = i * 30;
			en.y = 270;
			
			MemDC.MoveTo(st);
			MemDC.LineTo(en);
		}
		for(i=1; i<10;i++)
		{
			st.x = 0;
			st.y = 270 - i * 30;
			en.x = 2;
			en.y = 270 - i * 30;
			
			MemDC.MoveTo(st);
			MemDC.LineTo(en);
		}
		
		MemDC.Ellipse(standard.x-2, standard.y-2, standard.x+2, standard.y+2);
		
		if(usespectrum[0])
		{
			getpoint[0].x = (int)(x[0] * 300);
			getpoint[0].y = (int)(270 - y[0] * 300);
			
			pen1.CreatePen(PS_SOLID, 1, RGB(0,0,255));
			ptrPenOld = MemDC.SelectObject(&pen1);
			nMode = MemDC.SetROP2(R2_COPYPEN);
			
			MemDC.Ellipse(getpoint[0].x-2, getpoint[0].y-2, getpoint[0].x+2, getpoint[0].y+2);
			MemDC.MoveTo(standard);
			MemDC.LineTo(getpoint[0]);
		}
		
		if((intChip > 0) && usespectrum[1])
		{
			getpoint[1].x = (int)(x[1] * 300);
			getpoint[1].y = (int)(270 - y[1] * 300);
			
			pen2.CreatePen(PS_SOLID, 1, RGB(0,255,0));
			ptrPenOld = MemDC.SelectObject(&pen2);
			nMode = MemDC.SetROP2(R2_COPYPEN);
			
			MemDC.Ellipse(getpoint[1].x-2, getpoint[1].y-2, getpoint[1].x+2, getpoint[1].y+2);
			MemDC.MoveTo(standard);
			MemDC.LineTo(getpoint[1]);
		}
		
		if((intChip > 3) && usespectrum[2])
		{
			getpoint[2].x = (int)(x[2] * 300);
			getpoint[2].y = (int)(270 - y[2] * 300);
			
			pen3.CreatePen(PS_SOLID, 1, RGB(255,0,0));
			ptrPenOld = MemDC.SelectObject(&pen3);
			nMode = MemDC.SetROP2(R2_COPYPEN);
			
			MemDC.Ellipse(getpoint[2].x-2, getpoint[2].y-2, getpoint[2].x+2, getpoint[2].y+2);
			MemDC.MoveTo(standard);
			MemDC.LineTo(getpoint[2]);
		}
		
		MemDC.SelectObject(ptrPenOld);
		MemDC.SetROP2(nMode);
	}
	else
	{
		if(CIEDiagram)
		{
			CBrush brush, *oldbrush;
			brush.CreateSolidBrush(RGB(0, 0, 0));
			oldbrush = MemDC.SelectObject(&brush);
			CPoint dotPoint;
			sngPOINT point;
			if(!dot[0].IsEmpty())
			{
				point = dot[0].GetTail();
				dotPoint.x = (int)((point.x - xstart2) * picParam2.ratex);
				dotPoint.y = (int)(picParam2.height - (point.y - ystart2) * picParam2.ratey);
				MemDC.Ellipse(dotPoint.x-1, dotPoint.y-1, dotPoint.x+1, dotPoint.y+1);
			}
			MemDC.SelectObject(oldbrush);
		}
	}

	pWnd_picture->UpdateWindow(); 
	pDC_picture->BitBlt(0, 0, width, 270, &MemDC, 0, 0, SRCCOPY);

//	MemBitmap.DeleteObject();
//	MemDC.DeleteDC();
	// Do not call CResizingDialog::OnPaint() for painting messages
}


void CCIEDiagram::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CResizingDialog::OnMouseMove(nFlags, point);
}


void CCIEDiagram::enlarge(double staPointX, double staPointY) 
{
	double start[2], end[2];
	start[0] = xstart2;
	start[1] = ystart2;
	end[0] = xend2;
	end[1] = yend2;
	
	if(((end[0] - start[0]) >= 0.2) && ((end[1] - start[1]) >= 0.2))
	{
		xstart2 = staPointX - (staPointX - start[0]) * ChangeRate2;
		xend2 = staPointX + (end[0] - staPointX) * ChangeRate2;
		ystart2 = staPointY - (staPointY - start[1]) * ChangeRate2;
		yend2 = staPointY + (end[1] - staPointY) * ChangeRate2;
		
		rate /= ChangeRate2;
		InvalidateRect(&rect, false);
	}
}

void CCIEDiagram::smaller(double staPointX, double staPointY)
{
	double start[2], end[2];
	start[0] = xstart2;
	start[1] = ystart2;
	end[0] = xend2;
	end[1] = yend2;

	if((start[0] >= 0) && (start[1] >= 0) 
		&& (staPointX >= (staPointX - start[0]) / ChangeRate2)
		&& (staPointY >= (staPointY - start[1]) / ChangeRate2))
	{
		xstart2 = staPointX - (staPointX - start[0]) / ChangeRate2;
		xend2 = staPointX + (end[0] - staPointX) / ChangeRate2;
		ystart2 = staPointY - (staPointY - start[1]) / ChangeRate2;
		yend2 = staPointY + (end[1] - staPointY) / ChangeRate2;
		
		rate *= ChangeRate2;
		InvalidateRect(&rect, false);
	}
	else if(rate != 1)
	{
		xstart2 = 0;
		xend2 = 0.8;
		ystart2 = 0;
		yend2 = 0.9;
		rate = 1;
		
		InvalidateRect(&rect, false);
	}
}

BOOL CCIEDiagram::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	if((pt.x >= picParam2.left) && (pt.x <= (picParam2.left + picParam2.width)) 
		&& (pt.y >= picParam2.top) && (pt.y <= picParam2.top + picParam2.height))
	{
		double x, y;
		double staPointX, staPointY;
		
		x = pt.x - picParam2.left;
		y = pt.y - picParam2.top;
		staPointX = xstart2 + (double)x / picParam2.ratex;
		staPointY = ystart2 + (double)(picParam2.height - y) / picParam2.ratey;
		
		if(zDelta == 120)
		{
			enlarge(staPointX, staPointY); 
		}
		else if(zDelta == -120)
		{
			smaller(staPointX, staPointY);
		}
	}
	return CResizingDialog::OnMouseWheel(nFlags, zDelta, pt);
}


BOOL CCIEDiagram::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return true;
}

HBRUSH CCIEDiagram::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CResizingDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr=(HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CCIEDiagram::OnCIEPicture() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_CIEPicture)->SetFocus();
}

BOOL CCIEDiagram::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_F5:
			return true;
		}
	}
	return CResizingDialog::PreTranslateMessage(pMsg);
}
