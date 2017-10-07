// Spectrum.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "Spectrum.h"
#include "Functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpectrum dialog
extern CString mainpath;
extern ORI_PARA g_dOriPara;

CSpectrum::CSpectrum(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CSpectrum::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpectrum)
	//}}AFX_DATA_INIT
}

void CSpectrum::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpectrum)
	//}}AFX_DATA_MAP

}

BEGIN_MESSAGE_MAP(CSpectrum, CResizingDialog)
	//{{AFX_MSG_MAP(CSpectrum)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_SpectrumPicture, OnSpectrumPicture)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpectrum message handlers
extern int screen_width, screen_height;
extern float change_width, change_height;
extern int after_width, after_height;
extern int after_top, after_left;
extern int intChip;
//extern int intTestType;
extern double *spectrum[3], *wavelengths;
extern double sngCurrentDark[3][PIXELNUM];
extern bool usespectrum[3];
extern double spectrum_USB2000[3][2048];

extern int Show_wl[256];
extern bool spectrumcheck;
int scaleRate2;

int Show_spec[3][256]; 
double staMaxPower = 4000;

BOOL CSpectrum::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	pWnd_picture = GetDlgItem(IDC_SpectrumPicture);
	pWnd_picture->GetClientRect(&rect);
	pDC_picture = pWnd_picture->GetDC(); 

	width = 0;
	MoveWindowSmall();

	if(1)
	{
		scaleRate2 = 12;
		staMaxPower = 60000;
	}
	else
	{
		scaleRate2 = 1;
		staMaxPower = 4000;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSpectrum::MoveWindowBig()
{
	after_left = (int)(225*change_width);
	after_top = (int)(356*change_height);
	after_width = (int)(845*change_width);
	after_height = (int)(312*change_height);

	MoveWindow(after_left, after_top, after_width, after_height);
	pWnd_picture->MoveWindow(50, 10, 780, 260);

	return true;
}

BOOL CSpectrum::MoveWindowSmall()
{
	after_left = (int)(195*change_width);
	after_top = (int)(350*change_height);
	after_width = (int)(510*change_width);
	after_height = (int)(308*change_height);
	MoveWindow(after_left, after_top, after_width, after_height);

	width = 365;  //(int)(486 * change_width);
	pWnd_picture->MoveWindow(35, 12, width, 260);

	return true;
}

void CSpectrum::setdrawY(int chip)
{
	int i;
	CString str;
	double fShowMaxpower = 0;
	for (i = 0; i < 2048; i++)
	{
		if (fShowMaxpower < spectrum_USB2000[chip][i])
		{
			fShowMaxpower = spectrum_USB2000[chip][i];
		}
	}
	str.Format("%0.1f", fShowMaxpower);
	SetDlgItemText(IDC_ShowPower, str);

	for(i=0; i<256; i++)
	{
		Show_spec[chip][i] = (int)(256 - 250 * (spectrum_USB2000[chip][i*8])/fShowMaxpower);// - sngCurrentDark[chip][i*8])/fShowMaxpower);///(20 * scaleRate2));
	}

}

void CSpectrum::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CDC MemDC;
	CBitmap MemBitmap;

	MemDC.CreateCompatibleDC(NULL);
	MemBitmap.CreateCompatibleBitmap(pDC_picture, width, 260);
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(0, 0, width, 260, RGB(0, 0, 0));

	int i;
	CString str;

	dc.SetBkMode(TRANSPARENT);

	dc.TextOut(20, 276, "150");
	for(i=0; i<7; i++)
	{
		str.Format("%d", 200 + i*100);
		dc.TextOut(48 + i*48, 276, str);
	}
	dc.TextOut(378, 276, "900");
	
	int scale = 0;
	for(i=0; i<5; i++)
	{
		scale = i * 20;
		str.Format("%d", scale);
		dc.TextOut(18, 262 - i*50, str);
	}
	dc.TextOut(10, 262 - i*50, "100");
/*	int scale = 0;
	for(i=0; i<6; i++)
	{
		scale = i * scaleRate2;
		str.Format("%d", scale);
		if(scale >= 10)
		{
			dc.TextOut(18, 262 - i*50, str);
		}
		else
		{
			dc.TextOut(25, 262 - i*50, str);
		}
	}*/
	

	CPen pen0, pen1, pen2, pen3;
	CPen *ptrPenOld;
	int nMode;
	pen0.CreatePen(PS_SOLID, 1, RGB(255,255,255));  //°×
	ptrPenOld = MemDC.SelectObject(&pen0);
	nMode = MemDC.SetROP2(R2_COPYPEN);

	CPoint st, en;
	for(i=0; i<9; i++)
	{
		st.x = 24 + i * 48;
		st.y = 255;
		en.x = 24 + i * 48;
		en.y = 260;

		MemDC.MoveTo(st);
		MemDC.LineTo(en);
	}
	for(i=0; i<6;i++)
	{
		st.x = 0;
		st.y = 256 - i * 50;
		en.x = 2;
		en.y = 256 - i * 50;

		MemDC.MoveTo(st);
		MemDC.LineTo(en);
	}

	if(spectrumcheck)
	{
		CPoint start, end;
		if(usespectrum[0])
		{
			pen1.CreatePen(PS_SOLID, 1, RGB(0,0,255));  //À¶
			ptrPenOld = MemDC.SelectObject(&pen1);
			nMode = MemDC.SetROP2(R2_COPYPEN);
			setdrawY(0);
			
			for(i=0; i<255; i++)
			{
				start.x = Show_wl[i];
				start.y = Show_spec[0][i];
				end.x = Show_wl[i+1];
				end.y = Show_spec[0][i+1];
				MemDC.MoveTo(start);
				MemDC.LineTo(end);	
			}
		}
		
		if((intChip > 0) && usespectrum[1])
		{
			pen2.CreatePen(PS_SOLID, 1, RGB(0,255,0)); //ÂÌ
			ptrPenOld = MemDC.SelectObject(&pen2);
			nMode = MemDC.SetROP2(R2_COPYPEN);		
			setdrawY(1);
			
			for(i=0; i<255; i++)
			{
				start.x = Show_wl[i];
				start.y = Show_spec[1][i];
				end.x = Show_wl[i+1];
				end.y = Show_spec[1][i+1];
				MemDC.MoveTo(start);
				MemDC.LineTo(end);	
			}
		}
		
		if((intChip > 3) && usespectrum[2])
		{	
			pen3.CreatePen(PS_SOLID, 1, RGB(255,0,0));  //ºì
			ptrPenOld = MemDC.SelectObject(&pen3);
			nMode = MemDC.SetROP2(R2_COPYPEN);
			setdrawY(2);
			
			for(i=0; i<255; i++)
			{
				start.x = Show_wl[i];
				start.y = Show_spec[2][i];
				end.x = Show_wl[i+1];
				end.y = Show_spec[2][i+1];
				MemDC.MoveTo(start);
				MemDC.LineTo(end);	
			}
		}
	}
	MemDC.SelectObject(ptrPenOld);
	MemDC.SetROP2(nMode);

	pWnd_picture->UpdateWindow(); 
	pDC_picture->BitBlt(0, 0, width, 260, &MemDC, 0, 0, SRCCOPY);

	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
	// Do not call CResizingDialog::OnPaint() for painting messages
}

HBRUSH CSpectrum::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

BOOL CSpectrum::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return true;
}

BOOL CSpectrum::PreTranslateMessage(MSG* pMsg) 
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

void CSpectrum::OnSpectrumPicture() 
{
	// TODO: Add your control notification handler code here
	MessageBox("OK");
}
