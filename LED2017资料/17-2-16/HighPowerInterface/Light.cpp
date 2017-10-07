// Light.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "Light.h"
#include "Functions.h"
#include "ChipsHandle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLight dialog


CLight::CLight(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CLight::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLight)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLight::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLight)
	DDX_Control(pDX, IDC_LightOn, m_lightOn);
	DDX_Control(pDX, IDC_LightOff, m_lightOff);
	DDX_Control(pDX, IDC_Cancel, m_cancel);
	DDX_Control(pDX, IDC_Chiptype, m_chipType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLight, CResizingDialog)
	//{{AFX_MSG_MAP(CLight)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_LightOn, OnLightOn)
	ON_BN_CLICKED(IDC_LightOff, OnLightOff)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_Cancel, OnCancel)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLight message handlers
extern LightParam PolParam[3];
extern int selectchiptype;
extern int intSetway;

BOOL CLight::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	MoveWindow(300, 200, 260, 220);
	CRgn rgn;
	rgn.CreateRoundRectRgn(0, 0, 260, 220, 10, 10);
	SetWindowRgn(rgn, true);

	m_chipType.InsertString(0, "¾§Æ¬Ò»");
	m_chipType.InsertString(1, "¾§Æ¬¶þ");
	m_chipType.InsertString(2, "¾§Æ¬Èý");
	m_chipType.InsertString(3, "»ì¹â");

	chip = 0; 
	voltage = 5;
	current = 20;

	m_chipType.SetCurSel(chip);

	str.Format("%f", voltage);
	SetDlgItemText(IDC_Voltage, str);

	str.Format("%f", current);
	SetDlgItemText(IDC_Current, str);

	SetDialogFace();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLight::OnLightOn() 
{
	// TODO: Add your control notification handler code here
	chip = m_chipType.GetCurSel();
	GetDlgItemText(IDC_Voltage, str);
	voltage = atof(str);
	GetDlgItemText(IDC_Current, str);
	current = atof(str);
	
	OpenLightSet(selectchiptype, chip);
	OpenLight(voltage, current);
	
	if(chip >= 3)
	{
		OpenSupply(3);
		Supply(voltage, current, 2);
		Supply(voltage, current, 3);
	}
}

void CLight::OnLightOff() 
{
	// TODO: Add your control notification handler code here
	closeMixLight(1, 0);
}

void CLight::OnCancel() 
{
	// TODO: Add your control notification handler code here
	CResizingDialog::OnClose();
}

void CLight::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	CResizingDialog::OnLButtonDown(nFlags, point);
}

void CLight::SetDialogFace()
{
	m_lightOn.SetBitmaps(IDB_Button_LightNormal, IDB_Button_LightDown,
		                   IDB_Button_LightHigh, IDB_Button_LightDisable);
	m_lightOn.SizeToContent();

	m_lightOff.SetBitmaps(IDB_Button_CloseLightNormal, IDB_Button_CloseLightDown,
		                   IDB_Button_CloseLightHigh, IDB_Button_CloseLightDisable);
	m_lightOff.SizeToContent();

	m_cancel.SetBitmaps(IDB_Button_ExitNormal, IDB_Button_ExitDown,
		                 IDB_Button_ExitHigh, IDB_Button_ExitDisable);
	m_cancel.SizeToContent();	
}

BOOL CLight::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return CResizingDialog::DrawBK(pDC, IDB_LightBK, 0);
//	return CResizingDialog::OnEraseBkgnd(pDC);
}

HBRUSH CLight::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
