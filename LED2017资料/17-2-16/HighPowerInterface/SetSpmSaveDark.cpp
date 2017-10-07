// SetSpmSaveDark.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "SetSpmSaveDark.h"

#include "Functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetSpmSaveDark property page

IMPLEMENT_DYNCREATE(CSetSpmSaveDark, CPropertyPage)

CSetSpmSaveDark::CSetSpmSaveDark() : CPropertyPage(CSetSpmSaveDark::IDD)
{
	//{{AFX_DATA_INIT(CSetSpmSaveDark)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSetSpmSaveDark::~CSetSpmSaveDark()
{
}

void CSetSpmSaveDark::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetSpmSaveDark)
	DDX_Control(pDX, IDC_SaveAsSpec, m_saveas);
	DDX_Control(pDX, IDC_SaveDark, m_saveDark);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetSpmSaveDark, CPropertyPage)
	//{{AFX_MSG_MAP(CSetSpmSaveDark)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_ScanFile, OnScanFile)
	ON_BN_CLICKED(IDC_SaveDark, OnSaveDark)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SaveAsSpec, OnSaveAsSpec)
	ON_BN_CLICKED(IDC_Enlarge, OnEnlarge)
	ON_BN_CLICKED(IDC_Smaller, OnSmaller)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetSpmSaveDark message handlers
//extern Wrapper wrapper;
//extern DoubleArray SA;
extern double *spectrum[3], *wavelengths;
double *Dark_spectrum;
double Dark_spec1[PIXELNUM];
extern OpticSetParam calParam;
int Dark_spec2[128], Dark_wl[128];

//extern OOI_PARAM SetSpm_ooip;
extern double Refer_spec1[PIXELNUM];
extern double standardWL[PIXELNUM], power[PIXELNUM];
extern double DiameterOptic;
extern int powernum;
extern bool engineer;

extern int scaleRate;

BOOL CSetSpmSaveDark::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	savedark = false;
	m_saveDark.SetBitmaps(IDB_Dark, IDB_Refer, IDB_Dark, IDB_Dark);
	m_saveDark.SizeToContent();

	pWnd_picture=GetDlgItem(IDC_Picture);
	pWnd_picture->GetClientRect(&Dark_rect);
	pWnd_picture->MoveWindow(220, 40, 210, 170);
	pDC_picture = pWnd_picture->GetDC(); 

	if(1)
	{
		for(int i=0; i<128; i++)
		{
			Dark_wl[i] = (int)(0.24 * wavelengths[i*16] - 24);
			Dark_spec2[i] = (int)(170 - (spectrum[0][i*16]/(25 * scaleRate)));
		}
	}
	else
	{
		for(int i=0; i<128; i++)
		{
			Dark_wl[i] = (int)(0.24 * getWavelength(i*16) - 24);
//			Dark_spec2[i] = (int)(170 - (spectrum_PC2000[0][i*16]/(25 * scaleRate)));
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSetSpmSaveDark::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	CPropertySheet* pParent = (CPropertySheet*)GetParent();
	if(savedark)
	{
		pParent->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK);
	}
	else
	{
		pParent->SetWizardButtons(PSWIZB_BACK);
	}
	m_saveas.EnableWindow(savedark);
	return CPropertyPage::OnSetActive();
}

void CSetSpmSaveDark::OnScanFile() 
{
	// TODO: Add your control notification handler code here
	CString sz = "spectrum file (*.spec)|*.spec|All File(*.*)|*.*||";
	CFileDialog dlg(true, ".spec", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sz, this);

	if(IDOK==dlg.DoModal())
	{
		CString path = dlg.GetPathName();
		CStdioFile m_file;
		if(m_file.Open((LPCTSTR)path, CFile::modeReadWrite))
		{	
			ReadSpecFile(&m_file, Dark_spec1);
			m_file.Close();
			SetDlgItemText(IDC_FilePath, path);
			
			for(int i=0; i<128; i++)
			{
				Dark_spec2[i] = (int)(170 - (Dark_spec1[i*16]/(25 * scaleRate)));
			}
			
			InvalidateRect(&Dark_rect, false);
			
			savedark = true;
			OnSetActive();
		}
		else
		{
			MessageBox("文件打开失败!");
		}
	}
}

void CSetSpmSaveDark::getSpectrumDark()
{	
	int i = 0;
	int time = 0;
	if(1)
	{
		time = (int)(calParam.inteTime * 1000);
//		wrapper.setIntegrationTime(0, time);
//		SA = wrapper.getSpectrum(0);
//		Dark_spectrum = SA.getDoubleValues();
		for(i=0; i<PIXELNUM; i++)
		{
			Dark_spec1[i] = Dark_spectrum[i];
		}
	}
	else
	{
//		SingleScan_PC2000(&SetSpm_ooip, calParam.inteTime, calParam.scanTimes, calParam.boxcarWidth);
		for(i=0; i<PIXELNUM; i++)
		{
//			Dark_spec1[i] = SetSpm_ooip.chdat[0][i];
		}		
	}

	for(i=0; i<128; i++)
	{
		Dark_spec2[i] = (int)(170 - (Dark_spec1[i*16]/(25 * scaleRate)));
	}
}

void CSetSpmSaveDark::OnSaveDark() 
{
	// TODO: Add your control notification handler code here
	getSpectrumDark();
	InvalidateRect(&Dark_rect, false);	
	SetDlgItemText(IDC_FilePath, "");
	savedark = true;
	OnSetActive();	
}

void CSetSpmSaveDark::OnSaveAsSpec() 
{
	// TODO: Add your control notification handler code here
	CString sz = "spectrum file (*.spec)|*.spec|All File(*.*)|*.*||";
	CFileDialog dlg(false, ".spec", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sz, this);

	if(IDOK==dlg.DoModal())
	{
		CString path = dlg.GetPathName();
		CStdioFile m_file;
		if(m_file.Open((LPCTSTR)path, CFile::modeCreate|CFile::modeReadWrite))
		{
			WriteSpecFile(&m_file, Dark_spec1);
			m_file.Close();
		}
		else
		{
			MessageBox("文件另存失败!");
		}
	}
}

void CSetSpmSaveDark::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CDC MemDC;
	CBitmap MemBitmap;

	MemDC.CreateCompatibleDC(NULL);
	MemBitmap.CreateCompatibleBitmap(pDC_picture, 210, 170);
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(0, 0, 210, 170, RGB(0, 0, 0));

	int i;
	CPen pen;
	CPen *ptrPenOld;
	int nMode;
	pen.CreatePen(PS_SOLID, 1, RGB(255,255,255));  //红
	ptrPenOld = MemDC.SelectObject(&pen);
	nMode = MemDC.SetROP2(R2_COPYPEN);

	CString str;
	dc.SetBkMode(TRANSPARENT);
	for(i=0; i<9; i++)
	{
		str.Format("%d", i+1);
		dc.TextOut(217+i*24, 210, str);
	}
	
	int scale = 0;
	for(i=0; i<5; i++)
	{
		scale = i * scaleRate;
		str.Format("%d", scale);
		if(scale >= 10)
		{
			dc.TextOut(201, 202-i*40, str);
		}
		else
		{
			dc.TextOut(205, 202-i*40, str);
		}
	}

	CPoint st, en;
	for(i=1; i<9; i++)
	{
		st.x = i * 24;
		st.y = 170;
		en.x = i * 24;
		en.y = 168;

		MemDC.MoveTo(st);
		MemDC.LineTo(en);
	}
	for(i=0; i<5;i++)
	{
		st.x = 0;
		st.y = 170 - i * 40;
		en.x = 2;
		en.y = 170 - i * 40;

		MemDC.MoveTo(st);
		MemDC.LineTo(en);
	}

	CPoint start, end;
	for(i=0; i<127; i++)
	{
		start.x = Dark_wl[i];
		start.y = Dark_spec2[i];
		end.x = Dark_wl[i+1];
		end.y = Dark_spec2[i+1];
		MemDC.MoveTo(start);
		MemDC.LineTo(end);	
	}

	MemDC.SelectObject(ptrPenOld);
	MemDC.SetROP2(nMode);

	pWnd_picture->UpdateWindow(); 
	pDC_picture->BitBlt(0, 0, 210, 170, &MemDC, 0, 0, SRCCOPY);

	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
	// Do not call CPropertyPage::OnPaint() for painting messages
}



BOOL CSetSpmSaveDark::OnWizardFinish() 
{
	// TODO: Add your specialized code here and/or call the base class

	return CPropertyPage::OnWizardFinish();
}

LRESULT CSetSpmSaveDark::OnWizardNext() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnWizardNext();
}

BOOL CSetSpmSaveDark::OnQueryCancel() 
{
	// TODO: Add your specialized code here and/or call the base class
	return CPropertyPage::OnQueryCancel();
}

void CSetSpmSaveDark::OnEnlarge() 
{
	// TODO: Add your control notification handler code here
	if(scaleRate < 32)
	{
		scaleRate *= 2;
		for(int i=0; i<128; i++)
		{
			Dark_spec2[i] = 170 - (170 - Dark_spec2[i]) / 2;	
		}
		InvalidateRect(&Dark_rect, false);
		InvalidateRect(false);
	}
}

void CSetSpmSaveDark::OnSmaller() 
{
	// TODO: Add your control notification handler code here
	if(scaleRate > 1)
	{
		scaleRate /= 2;
		for(int i=0; i<128; i++)
		{
			Dark_spec2[i] = 170 - (170 - Dark_spec2[i]) * 2;	
		}
		InvalidateRect(&Dark_rect, false);
		InvalidateRect(false);
	}
}

BOOL CSetSpmSaveDark::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBitmap bmp;
	CBitmap *ptrBmpOld;
	BITMAP bm;

	bmp.LoadBitmap(IDB_DarkSpec);
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

HBRUSH CSetSpmSaveDark::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

