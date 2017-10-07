// SetChipFeet.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "SetChipFeet.h"
#include "Functions.h"
#include "ChipsHandle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetChipFeet dialog
extern int intSetway;
CSetChipFeet::CSetChipFeet(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CSetChipFeet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetChipFeet)
	m_setway = intSetway;
	//}}AFX_DATA_INIT
}


void CSetChipFeet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetChipFeet)
	DDX_Control(pDX, IDC_FigureChipstyle, m_ChipsType);
	DDX_Control(pDX, IDC_GetMiddleWave2, m_MiddleWave2);
	DDX_Control(pDX, IDC_GetMiddleWave1, m_MiddleWave1);
	DDX_Control(pDX, IDC_Packageway, m_packageway);
	DDX_Control(pDX, IDC_Commonfoot, m_commonfoot);
	DDX_Control(pDX, IDC_Selectchip, m_Showchip);
	DDX_Control(pDX, IDC_WLType, m_wltype);
	DDX_Control(pDX, IDC_Polarity, m_polarity);
	DDX_Control(pDX, IDC_Chiptype, m_chiptype);
	DDX_Radio(pDX, IDC_SetwayIF, m_setway);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetChipFeet, CResizingDialog)
	//{{AFX_MSG_MAP(CSetChipFeet)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_GetMiddleWave1, OnGetMiddleWave1)
	ON_BN_CLICKED(IDC_GetMiddleWave2, OnGetMiddleWave2)
	ON_BN_CLICKED(IDC_SetwayIF, OnSetwayIF)
	ON_BN_CLICKED(IDC_SetwayIV, OnSetwayIV)
	ON_BN_CLICKED(IDC_SetwayWL, OnSetwayWL)
	ON_BN_CLICKED(IDC_FigureChipstyle, OnFigureChipstyle)
	ON_BN_CLICKED(IDC_Selectchip, OnSelectchip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetChipFeet message handlers
extern int intPackageway;
extern int intChip;
extern int intCommonfoot;
extern int intPolarity;
extern int intWLType;    //0Îª·åÖµ²¨³¤  1ÎªÖ÷²¨³¤
extern int intMiddlePin;
extern int intMiddleWave1;
extern int intMiddleWave2;
extern LightParam PolParam[3];
extern int selectchiptype;

int BmpID[20];
int tempPackageway = 0;
int tempChip = 0;
int tempchiptype = 0;
int tempPolarity = 0;

BOOL CSetChipFeet::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitBitmap();
	m_Showchip.SetBitmaps(BmpID[selectchiptype], BmpID[selectchiptype],
		                  BmpID[selectchiptype], BmpID[selectchiptype]);

	m_packageway.InsertString(0, "Ö±²å");
	m_packageway.InsertString(1, "ÌùÆ¬");
	m_packageway.SetCurSel(intPackageway);

	m_chiptype.InsertString(0, "Ë«½Åµ¥¾§");
	m_chiptype.InsertString(1, "Ë«½ÅË«¾§");
	m_chiptype.InsertString(2, "Èý½ÅË«¾§");
	m_chiptype.InsertString(3, "ËÄ½ÅË«¾§");
	m_chiptype.InsertString(4, "ËÄ½ÅÈý¾§");
	m_chiptype.InsertString(5, "Áù½ÅÈý¾§");
	m_chiptype.SetCurSel(intChip);

	m_commonfoot.InsertString(0, "½ÅD");
	m_commonfoot.InsertString(1, "½ÅA");
	m_commonfoot.InsertString(2, "½ÅB");
	m_commonfoot.InsertString(3, "½ÅC"); 
	m_commonfoot.SetCurSel(intCommonfoot);

	m_polarity.InsertString(0, "¹²Ñô");
	m_polarity.InsertString(1, "¹²Òõ");
	m_polarity.SetCurSel(intPolarity);

	m_wltype.InsertString(0, "PeakWL");
	m_wltype.InsertString(1, "WL");
	m_wltype.SetCurSel(intWLType);

	CString str;
	str.Format("%d", intMiddlePin);
	SetDlgItemText(IDC_MiddlePin, str);

	str.Format("%d", intMiddleWave1);
	SetDlgItemText(IDC_MiddleWave1, str);

	str.Format("%d", intMiddleWave2);
	SetDlgItemText(IDC_MiddleWave2, str);

	str.Format("%f", PolParam[0].Voltage);
	SetDlgItemText(IDC_POLV, ReformatString(str));
	str.Format("%f", PolParam[0].Current);
	SetDlgItemText(IDC_POLI, ReformatString(str));
	str.Format("%d", PolParam[0].Delay);
	SetDlgItemText(IDC_POLDelay, str);

	SetDialogFace();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetChipFeet::InitBitmap()
{
	BmpID[0] = IDB_BigZ21;
	BmpID[1] = IDB_BigZ22;
	BmpID[2] = IDB_BigZ3200;
	BmpID[3] = IDB_BigZ3201;
	BmpID[4] = IDB_BigZ3210;
	BmpID[5] = IDB_BigZ3211;
	BmpID[6] = IDB_BigZ4300;
	BmpID[7] = IDB_BigZ4301;
	BmpID[8] = IDB_BigZ4310;
	BmpID[9] = IDB_BigZ4311;

	BmpID[10] = IDB_BigT21;
	BmpID[11] = IDB_BigT22;
	BmpID[12] = IDB_BigT42;
	BmpID[13] = IDB_BigT430A;
	BmpID[14] = IDB_BigT430B;
	BmpID[15] = IDB_BigT431A;
	BmpID[16] = IDB_BigT431B;
	BmpID[17] = IDB_BigT63;

	tempPackageway = intPackageway;
	tempChip = intChip;
	tempCommonfoot = intCommonfoot;
	tempPolarity = intPolarity;
	tempWLType =  intWLType; 
	tempchiptype = selectchiptype;
}

void CSetChipFeet::OnSelectchip() 
{
	// TODO: Add your control notification handler code here
	m_chiptypedlg.DoModal();
	m_Showchip.SetBitmaps(BmpID[tempchiptype], BmpID[tempchiptype],
		                  BmpID[tempchiptype], BmpID[tempchiptype]);
	m_chiptype.SetCurSel(tempChip);
	m_polarity.SetCurSel(tempPolarity);
	if(tempchiptype < 10)
	{
		tempPackageway = 0;
	}
	else 
	{
		tempPackageway = 1;
	}
	m_packageway.SetCurSel(tempPackageway);
}


void CSetChipFeet::OnSetwayIF() 
{
	// TODO: Add your control notification handler code here
	m_setway = 0;
}

void CSetChipFeet::OnSetwayIV() 
{
	// TODO: Add your control notification handler code here
	m_setway = 1;
}

void CSetChipFeet::OnSetwayWL() 
{
	// TODO: Add your control notification handler code here
	m_setway = 2;
}

void CSetChipFeet::OnFigureChipstyle() 
{
	// TODO: Add your control notification handler code here
	tempPackageway = m_packageway.GetCurSel();
	tempChip = m_chiptype.GetCurSel();
	tempPolarity = -1;
	
	CString str;
	double voltage = 0, current = 0;
	long delay = 0;

	GetDlgItemText(IDC_POLV, str);
	voltage = atof(str);
	GetDlgItemText(IDC_POLI, str);
	current = atof(str);
	GetDlgItemText(IDC_POLDelay, str);
	delay = atoi(str);

	if(0 == tempPackageway)
	{
		if(0 == tempChip)
		{
			tempchiptype = 0;
		}
		else if(1 == tempChip)
		{
			tempchiptype = 1;
		}
		else if(2 == tempChip)
		{
			//////2 3 4 5
			tempchiptype = OnFigureZ32style(voltage, current, delay);
		}
		else if(4 == tempChip)
		{   ////// 6 7 8 9 
			tempchiptype = OnFigureZ43style(voltage, current, delay);
		}
	}
	else if(1 == tempPackageway)
	{
		if(0 == tempChip)
		{
			tempchiptype = 10;
		}
		else if(1 == tempChip)
		{
			tempchiptype = 11;
		}
		else if(3 == tempChip)
		{
			tempchiptype = 12;
		}
		else if(4 == tempChip)
		{   /////13 14 15 16
			tempchiptype = OnFigureT43style(voltage, current, delay);
		}
		else if(5 == tempChip)
		{
			tempchiptype = 17;
		}
	}

	m_polarity.SetCurSel(tempPolarity);
	m_Showchip.SetBitmaps(BmpID[tempchiptype], BmpID[tempchiptype],
		                  BmpID[tempchiptype], BmpID[tempchiptype]);
}

void CSetChipFeet::getParameter() 
{
	CString str;

	selectchiptype = tempchiptype;
	intPackageway = m_packageway.GetCurSel();
	intChip = m_chiptype.GetCurSel();
	intPolarity = m_polarity.GetCurSel();
	intWLType = m_wltype.GetCurSel();
	intCommonfoot = m_commonfoot.GetCurSel();
	intSetway = m_setway;

	GetDlgItemText(IDC_MiddlePin, str);
	intMiddlePin = atoi(str);

	GetDlgItemText(IDC_MiddleWave1, str);
	intMiddleWave1 = atoi(str);

	GetDlgItemText(IDC_MiddleWave2, str);
	intMiddleWave2 = atoi(str);
}

void CSetChipFeet::OnGetMiddleWave1() 
{
	// TODO: Add your control notification handler code here
	int Chip = m_chiptype.GetCurSel();
	int wlType = m_wltype.GetCurSel();

	if(0 == wlType)
	{
		//Ë«½ÅË«¾§
		if(1 == Chip)
		{}
		//Èý½ÅË«¾§
		else if(2 == Chip)
		{}
		//ËÄ½ÅË«¾§
		else if(3 == Chip)
		{}
	}
	else
	{
		if(1 == Chip)
		{}
		else if(2 == Chip)
		{}
		else if(3 == Chip)
		{}
	}
}

void CSetChipFeet::OnGetMiddleWave2() 
{
	// TODO: Add your control notification handler code here
	
}

void CSetChipFeet::SetDialogFace()
{
	m_ChipsType.SetBitmaps(IDB_GetTypeNormal, IDB_GetTypeDown,
		                  IDB_GetTypeHigh, IDB_GetTypeDisable);
	m_ChipsType.SizeToContent();

	m_MiddleWave1.SetBitmaps(IDB_GetWL1Normal, IDB_GetWL1Down,
		                     IDB_GetWL1High, IDB_GetWL1Disable);
	m_MiddleWave1.SizeToContent();

	m_MiddleWave2.SetBitmaps(IDB_GetWL2Normal, IDB_GetWL2Down,
		                     IDB_GetWL2High, IDB_GetWL2Disable);
	m_MiddleWave2.SizeToContent();
}


BOOL CSetChipFeet::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return CResizingDialog::DrawBK(pDC, IDB_SetChipBK, 1);
//	return CResizingDialog::OnEraseBkgnd(pDC);
}

HBRUSH CSetChipFeet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

