// SetParameter.cpp : implementation file
//

#include "stdafx.h"
#include "HighPowerInterface.h"
#include "SetParameter.h"
#include "Functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////
// CSetParameter dialog
CSetParameter::CSetParameter(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CSetParameter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetParameter)
	//}}AFX_DATA_INIT
}

void CSetParameter::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetParameter)
	DDX_Control(pDX, IDC_VFaverage, m_VFaverage);
	DDX_Control(pDX, IDC_DeadLed, m_deadLed);
	DDX_Control(pDX, IDC_MixLight, m_mixlight);
	DDX_Control(pDX, IDC_SetOrderbyhand, m_setorderhyhand);
	DDX_Control(pDX, IDC_testway, m_testway);
	DDX_Control(pDX, IDC_cbWLSteptypeset, m_cbWLSteptypeset);
	DDX_Control(pDX, IDC_cbLighttype, m_cbLighttype);
	DDX_Control(pDX, IDC_cbWLSteptype, m_cbWLSteptype);
	DDX_Control(pDX, IDC_cbIVtype, m_cbIVtype);
	DDX_Control(pDX, IDC_TAB_Chip, m_tabChip);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetParameter, CResizingDialog)
	//{{AFX_MSG_MAP(CSetParameter)
	ON_WM_ERASEBKGND()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_Chip, OnSelchangeTABChip)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_MixLight, OnMixLight)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_DeadLed, OnDeadLed)
	ON_BN_CLICKED(IDC_VFaverage, OnVFaverage)
	ON_BN_CLICKED(IDC_SetOrderbyhand, OnSetOrderbyhand)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////
// CSetParameter message handlers
extern double DiameterOptic;
extern int intTestWay;
extern int intTestType;
extern int intMixLight;
extern int intVfAverage;
extern int intIVTestWay; //0为探头测IV 1为光谱仪测IV
extern int intWLStepSetWay;  //0为统一设置主波步长  1为分别设置
extern int intWLStep;    //0为步长1nm，1为步长5nm
extern int intWLSteps[3];
extern int intSampleAverage;
extern int intBoxcar;
extern int intFailBin;
extern int DeadLed;

extern bool engineer;
extern bool Operator;
//extern Wrapper wrapper;
extern double sngCurrentDark[3][PIXELNUM];
extern LightParam KeepLight[3];
int setpara_sel = 0;
bool updateRect = false;
bool stopUpdate = false;
CWinThread* pThread_SetParamRect;
int setting_wl[128];
int setting_spec[128];
double setting_spectrum[PIXELNUM];
bool tempmixopen = false;
bool tempVFaverage = false;
int setorderhyhand = 0;

extern int scaleRate2;

BOOL CSetParameter::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	pWnd_picture=GetDlgItem(IDC_SpectrumPicture);
	pWnd_picture->GetClientRect(&rect);
	pDC_picture=pWnd_picture->GetDC(); 

	pWnd_picture->MoveWindow(50, 442, 200, 150);

	setpara_sel = 0;

	m_setorderhyhand.SetCheck(setorderhyhand);

	m_cbLighttype.InsertString(0, "可见光");
	m_cbLighttype.InsertString(1, "不可见光");

	m_cbIVtype.InsertString(0, "探头");
	m_cbIVtype.InsertString(1, "光谱仪");

	m_cbWLSteptypeset.InsertString(0, "多晶统一设置");
	m_cbWLSteptypeset.InsertString(1, "各晶分别设置");

	m_cbWLSteptype.InsertString(0, "1nm");
	m_cbWLSteptype.InsertString(1, "5nm");
	
	m_tabChip.InsertItem(0, _T("晶片一"));
	m_tabChip.InsertItem(1, _T("晶片二"));
	m_tabChip.InsertItem(2, _T("晶片三"));
	m_tabChip.ShowWindow(SW_SHOW);

	m_chip1dlg.Create(IDD_Chip1Dlg, &m_tabChip);
	m_chip2dlg.Create(IDD_Chip2Dlg, &m_tabChip);
	m_chip3dlg.Create(IDD_Chip3Dlg, &m_tabChip);
	
	CSize size;
	size.cx = 30;
	size.cy = 30;
	m_tabChip.SetItemSize(size);

	CRect rc3;
	m_tabChip.GetClientRect(rc3);
	rc3.top += 30;
	m_chip1dlg.MoveWindow(&rc3);
	m_chip2dlg.MoveWindow(&rc3);
	m_chip3dlg.MoveWindow(&rc3);

	pDialog[0] = &m_chip1dlg;
	pDialog[1] = &m_chip2dlg;
	pDialog[2] = &m_chip3dlg;

	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	pDialog[2]->ShowWindow(SW_HIDE);
	
	m_CurSelTab = 0;

	initdlg();

//	InvalidateRect(&rect, false);
	stopUpdate = false;
	updateRect = false;
	pThread_SetParamRect = AfxBeginThread(UpdateRect, this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
////////////////////////////////初始化
bool CSetParameter::initdlg()
{
	m_testway.SetCheck(intTestWay);
	m_mixlight.SetCheck(intMixLight);
	if(1 == intMixLight)
	{
		tempmixopen = true;
	}
	else
	{
		tempmixopen = false;
	}
	
	m_VFaverage.EnableWindow(tempmixopen);
	m_VFaverage.SetCheck(intVfAverage);
	if(1 == intVfAverage)
	{
		tempVFaverage = true;
	}
	else
	{
		tempVFaverage = false;
	}
	
	m_deadLed.SetCheck(DeadLed);

	CString str;
	str.Format("%f", DiameterOptic);
	SetDlgItemText(IDC_DiameterOptic, ReformatString(str));
	
	m_cbLighttype.SetCurSel(intTestType);
	
	m_cbIVtype.SetCurSel(intIVTestWay);
	m_cbWLSteptypeset.SetCurSel(intWLStepSetWay);
	m_cbWLSteptype.SetCurSel(intWLStep);

	str.Format("%d", intSampleAverage);
	SetDlgItemText(IDC_ScanTimes, str);

	str.Format("%d", intBoxcar);
	SetDlgItemText(IDC_Boxcar, str);

	str.Format("%d", intFailBin);
	SetDlgItemText(IDC_FailBin, str);

	for(int i=0; i<128; i++)
	{
//		setting_wl[i] = (int)(0.26 * getWavelength(i*16) - 39);
		setting_spec[i] = 100;
	}
	return true;
}

void CSetParameter::OnSelchangeTABChip(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
    m_CurSelTab = m_tabChip.GetCurSel();
    pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);
	*pResult = 0;
}

bool CSetParameter::ChipsAuthoritydlg()
{
	if(engineer || Operator)
	{
		m_chip1dlg.initAuthorityItem();	
		m_chip2dlg.initAuthorityItem();	
		m_chip3dlg.initAuthorityItem();	
	}
	else
	{
		m_chip1dlg.hideAuthorityItem();
		m_chip2dlg.hideAuthorityItem();
		m_chip3dlg.hideAuthorityItem();
	}
	return true;
}

void CSetParameter::OnMixLight() 
{
	// TODO: Add your control notification handler code here
	if(1 == m_mixlight.GetCheck())
	{
		m_chip2dlg.SetMixLightParam(false);
		m_chip3dlg.SetMixLightParam(false);
		MessageBox("混光部分的测试项目以晶片一的设置为准");
		tempmixopen = true;
	}
	else
	{
		m_chip2dlg.SetMixLightParam(true);
		m_chip3dlg.SetMixLightParam(true);
		tempmixopen = false;
	}

	m_VFaverage.SetCheck(0);
	m_VFaverage.EnableWindow(tempmixopen);
	OnVFaverage(); 
}

void CSetParameter::OnVFaverage() 
{
	// TODO: Add your control notification handler code here
	if(1 == m_VFaverage.GetCheck())
	{
		m_chip2dlg.SetVFaverage(false);
		m_chip3dlg.SetVFaverage(false);
		tempVFaverage = true;
	}
	else
	{
		m_chip2dlg.SetVFaverage(true);
		m_chip3dlg.SetVFaverage(true);
		tempVFaverage = false;
	}
}

void CSetParameter::OnDeadLed() 
{
	// TODO: Add your control notification handler code here
	if(0 == m_deadLed.GetCheck())
	{
		m_chip1dlg.GetDlgItem(IDC_DLedBin)->EnableWindow(false);
		m_chip2dlg.GetDlgItem(IDC_DLedBin)->EnableWindow(false);
		m_chip3dlg.GetDlgItem(IDC_DLedBin)->EnableWindow(false);
	}
	else
	{
		m_chip1dlg.GetDlgItem(IDC_DLedBin)->EnableWindow(true);
		m_chip2dlg.GetDlgItem(IDC_DLedBin)->EnableWindow(true);
		m_chip3dlg.GetDlgItem(IDC_DLedBin)->EnableWindow(true);
	}
}

void CSetParameter::getParameter() 
{
	// TODO: Add your control notification handler code here
	CString str;

	intTestWay = m_testway.GetCheck();
	intMixLight = m_mixlight.GetCheck();
	intVfAverage = m_VFaverage.GetCheck();
	DeadLed = m_deadLed.GetCheck();

	GetDlgItemText(IDC_DiameterOptic, str);
	DiameterOptic = atof(str);

	intTestType = m_cbLighttype.GetCurSel();
	intIVTestWay = m_cbIVtype.GetCurSel();
	intWLStepSetWay = m_cbWLSteptypeset.GetCurSel();
	intWLStep = m_cbWLSteptype.GetCurSel();
	
	GetDlgItemText(IDC_ScanTimes, str);
	intSampleAverage = atoi(str);

	GetDlgItemText(IDC_Boxcar, str);
	intBoxcar = atoi(str);

	GetDlgItemText(IDC_FailBin, str);
	intFailBin = atoi(str);

	setorderhyhand = m_setorderhyhand.GetCheck();
	if(0 == m_setorderhyhand.GetCheck())
	{
		m_chip1dlg.getParameter();
		m_chip2dlg.getParameter();
		m_chip3dlg.getParameter();
	}
	else
	{
		m_chip1dlg.getParameterbyhand();
		m_chip2dlg.getParameterbyhand();
		m_chip3dlg.getParameterbyhand();
	}

	if(0 == intWLStepSetWay)
	{
		intWLSteps[0] = intWLStep;
		intWLSteps[1] = intWLStep;
		intWLSteps[2] = intWLStep;
	}

//	wrapper.setBoxcarWidth(0, intBoxcar);
//	wrapper.setScansToAverage(0, intSampleAverage);

	if(1 == intMixLight)
	{
		SetSupplyParam(KeepLight[1].Voltage, KeepLight[2].Voltage,
			           KeepLight[1].Current, KeepLight[2].Current);
	}
}

void CSetParameter::setdrawY()
{
	int i;
	CString str;
	double fshowMaxpower = getMaxPower(false);
	for (i = 0; i < 2048; i++)
	{
		if (fshowMaxpower < setting_spectrum[i])
		{
			fshowMaxpower = setting_spectrum[i];
		}
	}
	str.Format("%0.1f", fshowMaxpower);
	SetDlgItemText(IDC_MaxPwr, str);

	for(i=0; i<128; i++)
	{
		setting_spec[i] = (int)(150 - 150 * setting_spectrum[i*16] / fshowMaxpower);//(setting_spectrum[i*16]*3/(100*scaleRate2)));
	}

// 	if (1)
// 	{
// 		//文件保存看看
// 		FILE *fp;
// 		if((fp=fopen("c:\\Test.dat","wt"))==0)
// 		{
// 		}
// 		else
// 		{
// 			for(int i=0;i<128;i++)
// 			{
// 				fprintf(fp,"%d %d\n",setting_wl[i],setting_spec[i]);
// 			}
// 			
// 			fclose(fp);
// 		}
// 	}
}

void CSetParameter::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CDC MemDC;
	CBitmap MemBitmap;
	
	MemDC.CreateCompatibleDC(NULL);
	MemBitmap.CreateCompatibleBitmap(pDC_picture, 200, 150);
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(0, 0, 200, 150, RGB(0, 0, 0));
	
	CPen pen0, pen1;
	CPen *ptrPenOld;
	int nMode;
	pen0.CreatePen(PS_SOLID, 1, RGB(255,255,255));  //白
	ptrPenOld = MemDC.SelectObject(&pen0);
	nMode = MemDC.SetROP2(R2_COPYPEN);
	
	int i;
	CString str;
	
	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(35, 597, "1.5");
	for(i=1; i<9; i++)
	{
		str.Format("%d", i+1);
		dc.TextOut(35 + i*26, 597, str);
	}

	dc.TextOut(95, 612, "波长(*100nm)");
	
	dc.TextOut(37, 582, "0");
	for(i=1; i<5; i++)
	{
		str.Format("%d", i*20);
		dc.TextOut(30, 586 - 30 * i, str);
	}
	dc.TextOut(25, 586 - 30 * i, "100");
/*	for(i=1; i<6; i++)
	{
		str.Format("%d", i*scaleRate2);
		dc.TextOut(30, 586 - 30 * i, str);
	}
	dc.TextOut(50, 425, "(*1000)");*/
	
	CPoint st, en;
	for(i=0; i<9; i++)
	{
		st.x = 13 + i * 26;
		st.y = 145;
		en.x = 13 + i * 26;
		en.y = 150;
		
		MemDC.MoveTo(st);
		MemDC.LineTo(en);
	}
	for(i=0; i<6;i++)
	{
		st.x = 0;
		st.y = 150 - i * 30;
		en.x = 2;
		en.y = 150 - i * 30;
		
		MemDC.MoveTo(st);
		MemDC.LineTo(en);
	}
	
	CPoint start, end;
	
	pen1.CreatePen(PS_SOLID, 1, RGB(255,0,0));  //红
	ptrPenOld = MemDC.SelectObject(&pen1);
	nMode = MemDC.SetROP2(R2_COPYPEN);
	setdrawY();
	
	for(i=0; i<127; i++)
	{
		start.x = setting_wl[i];
		start.y = setting_spec[i];
		end.x = setting_wl[i+1];
		end.y = setting_spec[i+1];
		MemDC.MoveTo(start);
		MemDC.LineTo(end);	
	}

	MemDC.SelectObject(ptrPenOld);
	MemDC.SetROP2(nMode);
	
	pWnd_picture->UpdateWindow(); 
	pDC_picture->BitBlt(0, 0, 200, 150, &MemDC, 0, 0, SRCCOPY);
	
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
	// Do not call CResizingDialog::OnPaint() for painting messages
}

UINT UpdateRect(LPVOID lpParam)
{
	CSetParameter* pInfo = (CSetParameter*)lpParam;
	ASSERT(pInfo);
	while(!stopUpdate)
	{
		if(updateRect)
		{
			pInfo->InvalidateRect(&pInfo->rect, false);
		}
	}

	DWORD dwExitCode;
	GetExitCodeThread(pThread_SetParamRect->m_hThread, &dwExitCode);
	AfxEndThread(dwExitCode, true);

	return 0;
}

HBRUSH CSetParameter::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

BOOL CSetParameter::OnEraseBkgnd(CDC* pDC) 
{
//	return CResizingDialog::OnEraseBkgnd(pDC);
	return CResizingDialog::DrawBK(pDC, IDB_SetParamBK, 1);	
}


void CSetParameter::OnSetOrderbyhand() 
{
	// TODO: Add your control notification handler code here
	if(0 == m_setorderhyhand.GetCheck())
	{
		setorderhyhand = 0;
	}
	else
	{
		setorderhyhand = 1;
	}
}
