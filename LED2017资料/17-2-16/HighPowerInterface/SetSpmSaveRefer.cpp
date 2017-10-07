// SetSpmSaveRefer.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "SetSpmSaveRefer.h"

#include "Functions.h"
#include "SetSpmReadParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetSpmSaveRefer property page

IMPLEMENT_DYNCREATE(CSetSpmSaveRefer, CPropertyPage)

CSetSpmSaveRefer::CSetSpmSaveRefer() : CPropertyPage(CSetSpmSaveRefer::IDD)
{
	//{{AFX_DATA_INIT(CSetSpmSaveRefer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSetSpmSaveRefer::~CSetSpmSaveRefer()
{
}

void CSetSpmSaveRefer::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetSpmSaveRefer)
	DDX_Control(pDX, IDC_SaveAsSpec, m_saveas);
	DDX_Control(pDX, IDC_SaveRefer, m_saveRefer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetSpmSaveRefer, CPropertyPage)
	//{{AFX_MSG_MAP(CSetSpmSaveRefer)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_ScanFile, OnScanFile)
	ON_BN_CLICKED(IDC_SaveRefer, OnSaveRefer)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SaveAsSpec, OnSaveAsSpec)
	ON_BN_CLICKED(IDC_Enlarge, OnEnlarge)
	ON_BN_CLICKED(IDC_Smaller, OnSmaller)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetSpmSaveRefer message handlers
//extern OOI_PARAM SetSpm_ooip;
//extern Wrapper wrapper;
//extern DoubleArray SA;
extern double *spectrum[3], *wavelengths;
extern OpticSetParam calParam;

extern int scaleRate;

double *Refer_spectrum;
double Refer_spec1[PIXELNUM];
int Refer_spec2[128], Refer_wl[128];

BOOL CSetSpmSaveRefer::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	saverefer = false;
	m_saveRefer.SetBitmaps(IDB_Refer, IDB_Dark, IDB_Refer, IDB_Refer);
	m_saveRefer.SizeToContent();

	pWnd_picture=GetDlgItem(IDC_Picture);
	pWnd_picture->GetClientRect(&Refer_rect);
	pWnd_picture->MoveWindow(220, 40, 210, 170);
	pDC_picture = pWnd_picture->GetDC(); 

	if(1)
	{
		for(int i=0; i<128; i++)
		{
			Refer_wl[i] = (int)(0.24 * wavelengths[i*16] - 24);
			Refer_spec2[i] = (int)(170 - (spectrum[0][i*16]/(25 * scaleRate)));
		}
	}
	else
	{
		for(int i=0; i<128; i++)
		{
			Refer_wl[i] = (int)(0.24 * getWavelength(i*16) - 24);
//			Refer_spec2[i] = (int)(170 - (spectrum_PC2000[0][i*16]/(25 * scaleRate)));
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSetSpmSaveRefer::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	CPropertySheet* pParent = (CPropertySheet*)GetParent();
	if(saverefer)
	{
		pParent->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK);
	}
	else
	{
		pParent->SetWizardButtons(PSWIZB_BACK);
	}
	m_saveas.EnableWindow(saverefer);
	return CPropertyPage::OnSetActive();
}

void CSetSpmSaveRefer::OnScanFile() 
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
			ReadSpecFile(&m_file, Refer_spec1);
			m_file.Close();
			SetDlgItemText(IDC_FilePath, path);

			for(int i=0; i<128; i++)
			{
				Refer_spec2[i] = (int)(170 - (Refer_spec1[i*16]/(25 * scaleRate)));
			}
			
			InvalidateRect(&Refer_rect, false);	
			
			saverefer = true;
			OnSetActive(); 
		}
		else
		{
			MessageBox("文件打开失败!");
		}
	}
}

void CSetSpmSaveRefer::getSpectrumRefer()
{
	int i = 0;
	int time = 1;
	COLOR_PARA dColorPara;
	ORI_PARA dOriPara;
	JK_Emission_GetData_3LED(0, (float)calParam.inteTime, calParam.scanTimes, calParam.boxcarWidth, dColorPara,dOriPara);
	int j;
	double dDecAD[2048];
	for (j = 0; j < dOriPara.iPixN; j++)
	{
		dDecAD[j] = dOriPara.fDecPL[j];
	}
	Refer_spectrum = &dDecAD[0];
	
	for(j = 0; j < PIXELNUM; j++)
	{
		Refer_spec1[j] = dOriPara.fDecAD[j];//fDecAD[i];
	}
	for(i=0; i<128; i++)
	{
		Refer_spec2[i] = (int)(170 - (Refer_spec1[i*16]/(25 * scaleRate)));
	}
}

void CSetSpmSaveRefer::OnSaveRefer() 
{
	// TODO: Add your control notification handler code here
	getSpectrumRefer();
	InvalidateRect(&Refer_rect, false);	
	SetDlgItemText(IDC_FilePath, "");
	saverefer = true;
	OnSetActive(); 
}

void CSetSpmSaveRefer::OnSaveAsSpec() 
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
			WriteSpecFile(&m_file, Refer_spec1);
			m_file.Close();
		}
		else
		{
			MessageBox("文件另存失败!");
		}
	}
}

void CSetSpmSaveRefer::OnPaint() 
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
	pen.CreatePen(PS_SOLID, 1, RGB(255,255,255));
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
		start.x = Refer_wl[i];
		start.y = Refer_spec2[i];
		end.x = Refer_wl[i+1];
		end.y = Refer_spec2[i+1];
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

LRESULT CSetSpmSaveRefer::OnWizardBack() 
{
	// TODO: Add your specialized code here and/or call the base class
	return CPropertyPage::OnWizardBack();
}

BOOL CSetSpmSaveRefer::OnQueryCancel() 
{
	// TODO: Add your specialized code here and/or call the base class
	return CPropertyPage::OnQueryCancel();
}

void CSetSpmSaveRefer::OnEnlarge() 
{
	// TODO: Add your control notification handler code here
	if(scaleRate < 32)
	{
		scaleRate *= 2;
		for(int i=0; i<128; i++)
		{
			Refer_spec2[i] = 170 - (170 - Refer_spec2[i]) / 2;	
		}
		InvalidateRect(&Refer_rect, false);
		InvalidateRect(false);
	}
}

void CSetSpmSaveRefer::OnSmaller() 
{
	// TODO: Add your control notification handler code here
	if(scaleRate > 1)
	{
		scaleRate /= 2;
		for(int i=0; i<128; i++)
		{
			Refer_spec2[i] = 170 - (170 - Refer_spec2[i]) * 2;	
		}
		InvalidateRect(&Refer_rect, false);
		InvalidateRect(false);
	}
}

BOOL CSetSpmSaveRefer::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBitmap bmp;
	CBitmap *ptrBmpOld;
	BITMAP bm;

	bmp.LoadBitmap(IDB_ReferSpec);
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

HBRUSH CSetSpmSaveRefer::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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


