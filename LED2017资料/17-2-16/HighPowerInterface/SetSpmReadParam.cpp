// SetSpmReadParam.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "SetSpmReadParam.h"

#include "Functions.h"
#include "math.h"
#include "Global_MySpecGCS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetSpmReadParam property page
double *Spm_spectrum;
double Spm_spec1[PIXELNUM];
int Spm_spec2[128], Spm_wl[128];

IMPLEMENT_DYNCREATE(CSetSpmReadParam, CPropertyPage)

CSetSpmReadParam::CSetSpmReadParam() : CPropertyPage(CSetSpmReadParam::IDD)
{
	//{{AFX_DATA_INIT(CSetSpmReadParam)
	//}}AFX_DATA_INIT
}

CSetSpmReadParam::~CSetSpmReadParam()
{
}

void CSetSpmReadParam::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetSpmReadParam)
	DDX_Control(pDX, IDC_AutoSetTime, m_autoset);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetSpmReadParam, CPropertyPage)
	//{{AFX_MSG_MAP(CSetSpmReadParam)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ShowSpectrum, OnShowSpectrum)
	ON_BN_CLICKED(IDC_AutoSetTime, OnAutoSetTime)
	ON_BN_CLICKED(IDC_Smaller, OnSmaller)
	ON_BN_CLICKED(IDC_Enlarge, OnEnlarge)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetSpmReadParam message handlers
CWinThread* pThread2;
bool threadgetSpectrum = false;
//extern Wrapper wrapper;
//extern DoubleArray SA;

OpticSetParam calParam;
//OOI_PARAM SetSpm_ooip;

double recommended = 0;
double gettime = 0;
double lastpower = 0;

int scaleRate = 1;
BOOL CSetSpmReadParam::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	pWnd_picture = GetDlgItem(IDC_Picture);
	pWnd_picture->GetClientRect(&Spm_rect);
	pWnd_picture->MoveWindow(250, 130, 180, 165);
	pDC_picture = pWnd_picture->GetDC(); 

	SetDlgItemText(IDC_InteTime, "4");
	SetDlgItemText(IDC_BoxcarWidth, "3");
	SetDlgItemText(IDC_ScanTimes, "1");

	if(1)
	{
		SetDlgItemText(IDC_Recommended, "55704");
		scaleRate = 16;
		for(int i=0; i<128; i++)
		{
			Spm_wl[i] = (int)(0.2 * wavelengths[i*16] - 20);
			Spm_spec2[i] = (int)(165 - (spectrum[0][i*16]/(25 * scaleRate)));
		}
	}
	else
	{
		SetDlgItemText(IDC_Recommended, "3400");
		scaleRate = 1;
		for(int i=0; i<128; i++)
		{
			Spm_wl[i] = (int)(0.2 * getWavelength(i*16) - 20);
//			Spm_spec2[i] = (int)(165 - (spectrum_PC2000[0][i*16]/(25 * scaleRate)));
		}
	}

	threadgetSpectrum = true;
	pThread2 = AfxBeginThread(getSpectrum, this);
	SetDlgItemText(IDC_ShowSpectrum, "暂停预览光谱");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetSpmReadParam::OnShowSpectrum() 
{
	// TODO: Add your control notification handler code here
	if(threadgetSpectrum)
	{
		threadgetSpectrum = false;
		SetDlgItemText(IDC_ShowSpectrum, "启动预览光谱");
	}
	else
	{
		threadgetSpectrum = true;
		pThread2 = AfxBeginThread(getSpectrum, this);
		SetDlgItemText(IDC_ShowSpectrum, "暂停预览光谱");
	}
}

UINT getSpectrum(LPVOID lpParam)
{
	CSetSpmReadParam* pInfo = (CSetSpmReadParam*)lpParam;
	ASSERT(pInfo);
	double maxpower = 0;
	double dark[PIXELNUM];
	double Spm_spec3 = 0;
	int scale = 0;
	int i=0, j=0; 
	CString str;

	while(threadgetSpectrum)
	{
		pInfo->GetDlgItemText(IDC_ScanTimes, str);
		calParam.scanTimes = atoi(str);
		if(calParam.scanTimes < 1)
		{
			calParam.scanTimes = 1;
		}

		pInfo->GetDlgItemText(IDC_BoxcarWidth, str);
		calParam.boxcarWidth = atoi(str);
		if(calParam.boxcarWidth < 0)
		{
			calParam.boxcarWidth = 0;
		}
		
		pInfo->GetDlgItemText(IDC_InteTime, str);
		calParam.inteTime = atof(str);
		if(calParam.inteTime < 1)
		{
			calParam.inteTime = 1;
		}
		else if(calParam.inteTime > 1000)
		{
			calParam.inteTime = 1000;
		}

		COLOR_PARA dColorPara;
		ORI_PARA dOriPara;
		JK_Emission_GetData_3LED(0, (float)calParam.inteTime, calParam.scanTimes, calParam.boxcarWidth, dColorPara,dOriPara);
		int j;
		double dDecAD[2048];
		for (j = 0; j < dOriPara.iPixN; j++)
		{
			dDecAD[j] = dOriPara.fDecPL[j];
		}
		Spm_spectrum = &dDecAD[0];
		
		for(j = 0; j < PIXELNUM; j++)
		{
			dark[j] = 0;
			Spm_spec1[j] = dOriPara.fDecAD[j];//fDecAD[i];
		}

		for(i=0; i<128; i++)
		{
			Spm_spec2[i] = (int)(165 - (Spm_spec1[i*16]/(25 * scaleRate)));
		}
		
		setsngCounts(Spm_spec1, dark);
			
		maxpower = getMaxPower(false);
		str.Format("%0.2f", maxpower);
		if(threadgetSpectrum)
		{
			pInfo->InvalidateRect(&pInfo->Spm_rect, false);
			pInfo->SetDlgItemText(IDC_MaxPwr, str);	
		}
	}

	DWORD dwExitCode;
	GetExitCodeThread(pThread2->m_hThread, &dwExitCode);
	AfxEndThread(dwExitCode, true);
	return 0;
}

BOOL CSetSpmReadParam::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	CPropertySheet* pParent = (CPropertySheet*)GetParent();
	pParent->SetWizardButtons(PSWIZB_NEXT);

	return CPropertyPage::OnSetActive();
}

void CSetSpmReadParam::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	int i;
	CString str;
	int scale = 0;

	dc.SetBkMode(TRANSPARENT);
	
	for(i=0; i<5; i++)
	{
		scale = i * scaleRate;
		str.Format("%d", scale);
		if(scale >= 10)
		{
			dc.TextOut(232, 285 - i*40, str);
		}
		else
		{
			dc.TextOut(235, 285 - i*40, str);
		}
	}
	
	CDC MemDC;
	CBitmap MemBitmap;

	MemDC.CreateCompatibleDC(NULL);
	MemBitmap.CreateCompatibleBitmap(pDC_picture, 180, 165);
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(0, 0, 180, 165, RGB(0, 0, 0));

	CPen pen;
	CPen *ptrPenOld;
	int nMode;
	pen.CreatePen(PS_SOLID, 1, RGB(255,255,255));
	ptrPenOld = MemDC.SelectObject(&pen);
	nMode = MemDC.SetROP2(R2_COPYPEN);

	CPoint st, en;
	for(i=1; i<9; i++)
	{
		st.x = i * 20;
		st.y = 163;
		en.x = i * 20;
		en.y = 165;

		MemDC.MoveTo(st);
		MemDC.LineTo(en);
	}
	for(i=0; i<7;i++)
	{
		st.x = 0;
		st.y = 162 - i * 40;
		en.x = 2;
		en.y = 162 - i * 40;

		MemDC.MoveTo(st);
		MemDC.LineTo(en);
	}

	CPoint start, end;
	for(i=0; i<127; i++)
	{
		start.x = Spm_wl[i];
		start.y = Spm_spec2[i];
		end.x = Spm_wl[i+1];
		end.y = Spm_spec2[i+1];
		MemDC.MoveTo(start);
		MemDC.LineTo(end);	
	}

	MemDC.SelectObject(ptrPenOld);
	MemDC.SetROP2(nMode);

	pWnd_picture->UpdateWindow(); 
	pDC_picture->BitBlt(0, 0, 180, 165, &MemDC, 0, 0, SRCCOPY);

	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
	// Do not call CPropertyPage::OnPaint() for painting messages
}

bool CSetSpmReadParam::OnAutoSetTime() 
{
	// TODO: Add your control notification handler code here
	if(threadgetSpectrum)
	{
		MessageBox("请先暂停光谱预览!");
		return false;
	}
	
	CString str;
	double maxpower = 0;
	double time = 0; 
	double max = 1000, min = 1;

	SetDlgItemText(IDC_AutoSetTime, "正在获取");
	GetDlgItemText(IDC_Recommended, str);
	recommended = atof(str);

	maxpower = Spm_getMaxpower(min);
	SetDlgItemText(IDC_AutoSetTime, "正在获取 .");
	if(maxpower > (recommended * 1.1))
	{
		MessageBox("光子太强, 无法获得积分时间!");
		SetDlgItemText(IDC_AutoSetTime, "自动获取积分时间");
		return false;
	}

	maxpower = Spm_getMaxpower(max);

	SetDlgItemText(IDC_AutoSetTime, "正在获取 . .");
	if(maxpower < (recommended * 0.9))
	{
		MessageBox("光子太弱, 无法获得积分时间!");
		SetDlgItemText(IDC_AutoSetTime, "自动获取积分时间");
		return false;
	}
	
	time = getTime(max, min);
	str.Format("%0.1f", time);
	SetDlgItemText(IDC_InteTime, str);
	str.Format("%f", lastpower);
	SetDlgItemText(IDC_MaxPwr, str);
	SetDlgItemText(IDC_AutoSetTime, "自动获取积分时间");
	return true;
}

double CSetSpmReadParam::getTime(double max, double min)
{
	double maxpower = 0;	
	double differ1 = 0, differ2 = 0;
	double middle = 0;
	CString str;
	
	if((max - min) < 0.2)
	{
		differ1 = fabs(Spm_getMaxpower(max) - recommended);
		differ2 = fabs(Spm_getMaxpower(min) - recommended);
		if(differ1 < differ2)
		{
			return max;
		}
		else if(differ1 > differ2)
		{
			return min;
		}
		else
		{
			getTime(max, min);
		}
		return gettime;
	}
	middle = (max + min) * 0.5;
	str.Format("%0.1f", middle);
	SetDlgItemText(IDC_InteTime, str);

	maxpower = Spm_getMaxpower(middle);
	if(maxpower > (recommended * 1.1))
	{
		SetDlgItemText(IDC_AutoSetTime, "正在获取 . . .");
		max = middle;
		getTime(max, min);
	}
	else if(maxpower < (recommended * 0.9))
	{
		SetDlgItemText(IDC_AutoSetTime, "正在获取 . . .");
		min = middle;
		getTime(max, min);
	}
	else
	{ 
		SetDlgItemText(IDC_AutoSetTime, "存在合适的积分时间,请稍后...");
		differ1 = fabs(maxpower - recommended);
		differ2 = fabs(lastpower - recommended);
		if(differ1 < differ2)
		{
			gettime = middle;
			lastpower = maxpower;
		}

		if(maxpower > recommended)
		{
			max = middle;
			getTime(max, min);
		}
		else if(maxpower < recommended)
		{
			min = middle;
			getTime(max, min);
		}
		else
		{
			str.Format("%0.1f", lastpower);
			SetDlgItemText(IDC_MaxPwr, str);
			return gettime;
		}
	}
	
	str.Format("%0.1f", lastpower);
	SetDlgItemText(IDC_MaxPwr, str);
	return gettime;
}

double CSetSpmReadParam::Spm_getMaxpower(double time)
{
	double maxpower = 0;
	double dark[PIXELNUM];
	double Spm_spec3 = 0;
	int scale = 0;
	int i=0; 
	CString str;

	GetDlgItemText(IDC_ScanTimes, str);
	calParam.scanTimes = atoi(str);
	if(calParam.scanTimes < 1)
	{
		calParam.scanTimes = 1;
	}
	
	GetDlgItemText(IDC_BoxcarWidth, str);
	calParam.boxcarWidth = atoi(str);
	if(calParam.boxcarWidth < 0)
	{
		calParam.boxcarWidth = 0;
	}
	COLOR_PARA dColorPara;
	ORI_PARA dOriPara;

	JK_Emission_GetData_3LED(0, (float)time, calParam.scanTimes, calParam.boxcarWidth, dColorPara,dOriPara);
	int j;
	double dDecAD[2048];
	maxpower = 0;
	for (j = 0; j < dOriPara.iPixN; j++)
	{
		dDecAD[j] = dOriPara.fDecPL[j];
		if (maxpower < dDecAD[j])
		{
			maxpower = dDecAD[j];
		}
	}
	Spm_spectrum = &dDecAD[0];
	
	for(j = 0; j < PIXELNUM; j++)
	{
		Spm_spec1[j] = dOriPara.fDecAD[j];
	}

	setsngCounts(Spm_spec1, dark);

	for(i=0; i<128; i++)
	{
		Spm_spec2[i] = (int)(165 - (Spm_spec1[i*16]/(25 * scaleRate)));
	}

	//maxpower = getMaxPower(false);
	InvalidateRect(&Spm_rect, false);

	return maxpower;
}

LRESULT CSetSpmReadParam::OnWizardNext() 
{
	// TODO: Add your specialized code here and/or call the base class
	CString str;
	int time = 0;
	GetDlgItemText(IDC_InteTime, str);
	calParam.inteTime = atof(str);
	if(calParam.inteTime > 1000)
	{
		calParam.inteTime = 1000;
	}

	if(threadgetSpectrum)
	{
		threadgetSpectrum = false;
		time = (int)calParam.inteTime;
		Delay(time);
	}

	GetDlgItemText(IDC_BoxcarWidth, str);
	calParam.boxcarWidth = atoi(str);
	GetDlgItemText(IDC_ScanTimes, str);
	calParam.scanTimes = atoi(str);

	SetDlgItemText(IDC_ShowSpectrum, "启动预览光谱");
	return CPropertyPage::OnWizardNext();
}

BOOL CSetSpmReadParam::OnQueryCancel() 
{
	// TODO: Add your specialized code here and/or call the base class
	threadgetSpectrum = false;
	return CPropertyPage::OnQueryCancel();
}

void CSetSpmReadParam::OnEnlarge() 
{
	// TODO: Add your control notification handler code here
	if(scaleRate < 32)
	{
		scaleRate *= 2;
		InvalidateRect(&Spm_rect, false);
		InvalidateRect(false);
	}
}

void CSetSpmReadParam::OnSmaller() 
{
	// TODO: Add your control notification handler code here
	if(scaleRate > 1)
	{
		scaleRate /= 2;
		InvalidateRect(&Spm_rect, false);
		InvalidateRect(false);
	}
}

BOOL CSetSpmReadParam::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBitmap bmp;
	CBitmap *ptrBmpOld;
	BITMAP bm;

	bmp.LoadBitmap(IDB_SpmReadParam);
	bmp.GetBitmap(&bm);

	CRect rect;
	GetClientRect(rect);

	int w,h;
	w = rect.Width()/bm.bmWidth+1;
	h = rect.Height()/bm.bmHeight+1;

	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	ptrBmpOld = dcMemory.SelectObject(&bmp);
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

HBRUSH CSetSpmReadParam::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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


