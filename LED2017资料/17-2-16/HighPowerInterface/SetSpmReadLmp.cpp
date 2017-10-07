// SetSpmReadLmp.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "SetSpmReadLmp.h"

#include "Functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetSpmReadLmp property page

IMPLEMENT_DYNCREATE(CSetSpmReadLmp, CPropertyPage)

CSetSpmReadLmp::CSetSpmReadLmp() : CPropertyPage(CSetSpmReadLmp::IDD)
{
	//{{AFX_DATA_INIT(CSetSpmReadLmp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSetSpmReadLmp::~CSetSpmReadLmp()
{
}

void CSetSpmReadLmp::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetSpmReadLmp)
	DDX_Control(pDX, IDC_LmpList, m_lmplist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetSpmReadLmp, CPropertyPage)
	//{{AFX_MSG_MAP(CSetSpmReadLmp)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_OpenLmpFile, OnOpenLmpFile)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetSpmReadLmp message handlers
extern int powernum;
extern double standardWL[PIXELNUM], power[PIXELNUM];
extern double Dark_spec1[PIXELNUM];
extern double Refer_spec1[PIXELNUM];
extern OpticSetParam calParam;
extern CalCoeff calcoeff;
double ListPwr[PIXELNUM];
StandardLightResource tempstandardCal;

BOOL CSetSpmReadLmp::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	openlmp = false;

	pWnd_picture=GetDlgItem(IDC_Picture);
	pWnd_picture->GetClientRect(&rect);
	pDC_picture=pWnd_picture->GetDC(); 

	pWnd_picture->MoveWindow(290, 85, 150, 180);

	////////////////////listcontrol
	m_lmplist.Init();
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 20;
	strcpy(lf.lfFaceName, "Verdana");
	font.CreateFontIndirect(&lf);
	m_lmplist.SetFont(&font, TRUE);
	
	m_lmplist.SetReadOnlyColumns(0);
	m_lmplist.SetReadOnlyColumns(1);
	m_lmplist.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	m_lmplist.InsertColumn(0, "波长(nm)", LVCFMT_CENTER, 80);
	m_lmplist.InsertColumn(1, "强度(uW/cm^2/nm)", LVCFMT_CENTER, 150);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSetSpmReadLmp::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	CPropertySheet* pParent = (CPropertySheet*)GetParent();
	if(openlmp)
	{
		pParent->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK);
	}
	else
	{
		pParent->SetWizardButtons(PSWIZB_BACK);
	}
	return CPropertyPage::OnSetActive();
}

BOOL CSetSpmReadLmp::CalWavePower(double *wl) 
{
	for(int i=0; i<PIXELNUM; i++)
	{
		if((wl[i] < 370) || (wl[i] > 1000) 
			|| (wl[i] < standardWL[0])
			|| (wl[i] > standardWL[powernum-1]))
		{
			ListPwr[i] = 0;
		}
		else 
		{
			for(int j=0; j<(powernum-1); j++)
			{
				if(wl[i] == standardWL[j])
				{
					ListPwr[i] = power[j];
				}
				else if((wl[i] > standardWL[j]) && (wl[i] < standardWL[j+1]))
				{
					ListPwr[i] = (power[j+1] - power[j]) / (standardWL[j+1] - standardWL[j]) * (wl[i] - standardWL[j]) + power[j];
				}
			}	
		}	
	}
	return true;
}

LRESULT CSetSpmReadLmp::OnWizardNext() 
{
	// TODO: Add your specialized code here and/or call the base class
	int i=0; 
	double dTemp = 0, dTemp1 = 0;
	double wavelength[PIXELNUM];
	int DiameterOptic = 400;

	for(i=0; i<PIXELNUM; i++)
	{
		wavelength[i] = calcoeff.intercept + i * (calcoeff.firstCoeff 
			+ calcoeff.secondCoeff * i + calcoeff.thirdCoeff * i * i);		
	}
	CalWavePower(wavelength);
	for(i=0; i<PIXELNUM; i++)
	{
		tempstandardCal.sngReference[i] = Refer_spec1[i];
		tempstandardCal.sngDark[i] = Dark_spec1[i];
		tempstandardCal.sngListPower[i] = ListPwr[i];
		
		dTemp1 = Refer_spec1[i] - Dark_spec1[i];
		if((0 == dTemp1) || (0 == ListPwr[i]))
		{
			tempstandardCal.uJoulesCount[i] = 0;
		}
		else
		{
			dTemp = calParam.inteTime * DiameterOptic;
//			dTemp = calParam.inteTime * 4 * 3.14159265358979/ 1000000000;
			dTemp *= ListPwr[i]; 
			dTemp /= dTemp1;
			tempstandardCal.uJoulesCount[i] = dTemp;
		}
	}
	
	return CPropertyPage::OnWizardNext();
}


void CSetSpmReadLmp::OnOpenLmpFile() 
{
	// TODO: Add your control notification handler code here
	CString sz = "Lamp file (*.LMP)|*.LMP|All File(*.*)|*.*||";
	CFileDialog dlg(true, ".LMP", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sz, this);

	if(IDOK==dlg.DoModal())
	{
		CString path = dlg.GetPathName();
		CStdioFile m_file;
		if(m_file.Open((LPCTSTR)path, CFile::modeReadWrite))
		{	
			ReadLMPFile(&m_file);
			m_file.Close();
			SetList();
			openlmp = true;
			OnSetActive();
			SetDlgItemText(IDC_FilePath, path);
			InvalidateRect(&rect, false);
			InvalidateRect(false);
		}
		else
		{
			MessageBox("文件打开失败!");
		}
	}
}

void CSetSpmReadLmp::SetList()
{
	m_lmplist.DeleteAllItems();
	for(int i=0; i<powernum; i++)
	{
		CString str;
		str.Format("%0.1f", standardWL[i]);
		m_lmplist.InsertItem(i, str);
		str.Format("%0.4e", power[i]);
		m_lmplist.SetItemText(i, 1, str);
	}
}

void CSetSpmReadLmp::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CDC MemDC;
	CBitmap MemBitmap;
	
	MemDC.CreateCompatibleDC(NULL);
	MemBitmap.CreateCompatibleBitmap(pDC_picture, 150, 180);
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(0, 0, 150, 180, RGB(0, 0, 0));
	
	CPen pen0, pen1;
	CPen *ptrPenOld;
	int nMode;
	pen0.CreatePen(PS_SOLID, 1, RGB(255,255,255));  //白
	ptrPenOld = MemDC.SelectObject(&pen0);
	nMode = MemDC.SetROP2(R2_COPYPEN);
	
	int i;
	CString str;
	
	dc.SetBkMode(TRANSPARENT);
	for(i=0; i<4; i++)
	{
		str.Format("%d", (i+2) * 200);
		dc.TextOut(295 + i*40, 270, str);
	}
	
	dc.TextOut(278, 258, "0");
	
	int rate = 100;
	if(power[powernum - 1] < 50)
	{
		rate = 4; 
	}

	int scale = 0;
	for(i=1; i<4; i++)
	{
		scale = i * rate;
		str.Format("%d", scale);
		if(scale > 10)
		{
			dc.TextOut(272, 258 - 45 * i, str);
		}
		else
		{
			dc.TextOut(278, 258 - 45 * i, str);
		}	
	}
	
	CPoint st, en;
	for(i=0; i<4; i++)
	{
		st.x = 20 + i * 40;
		st.y = 175;
		en.x = 20 + i * 40;
		en.y = 180;
		
		MemDC.MoveTo(st);
		MemDC.LineTo(en);
	}
	for(i=1; i<4;i++)
	{
		st.x = 0;
		st.y = 180 - i * 45;
		en.x = 2;
		en.y = 180 - i * 45;
		
		MemDC.MoveTo(st);
		MemDC.LineTo(en);
	}
	
	
	CPoint start, end;
	
	pen1.CreatePen(PS_SOLID, 1, RGB(255,0,0));  //红
	ptrPenOld = MemDC.SelectObject(&pen1);
	nMode = MemDC.SetROP2(R2_COPYPEN);
	
	for(i=0; i<(powernum-1); i++)
	{
		start.x = (int)((standardWL[i] - 300) * 0.2);
		start.y = (int)(180 - power[i] * 45 / rate);
		end.x = (int)((standardWL[i+1] - 300) * 0.2);
		end.y = (int)(180 - power[i+1] * 45 / rate);
		MemDC.MoveTo(start);
		MemDC.LineTo(end);	
	}
			
	
	MemDC.SelectObject(ptrPenOld);
	MemDC.SetROP2(nMode);
	
	pWnd_picture->UpdateWindow(); 
	pDC_picture->BitBlt(0, 0, 150, 180, &MemDC, 0, 0, SRCCOPY);
	
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
	// Do not call CPropertyPage::OnPaint() for painting messages
}


BOOL CSetSpmReadLmp::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBitmap bmp;
	CBitmap *ptrBmpOld;
	BITMAP bm;

	bmp.LoadBitmap(IDB_LampFile);
	bmp.GetBitmap(&bm);

	CRect rect;
	GetClientRect(rect);

	int w,h;
	w=rect.Width()/bm.bmWidth+1;
	h=rect.Height()/bm.bmHeight+1;

	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	ptrBmpOld=dcMemory.SelectObject(&bmp);
	for(int i=0;i<w;i++)
	{
		for(int j=0;j<h;j++)
		{
			pDC->BitBlt
				(
				i*bm.bmWidth,
				j*bm.bmHeight,
				bm.bmWidth,
				bm.bmHeight,
				&dcMemory,
				10,
				12,
				SRCCOPY
				);
		}
	}
	return true;
//	return CPropertyPage::OnEraseBkgnd(pDC);
}

HBRUSH CSetSpmReadLmp::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr=(HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}


