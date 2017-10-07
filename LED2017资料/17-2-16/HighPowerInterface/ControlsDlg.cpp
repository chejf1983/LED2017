// ControlsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HighPowerInterface.h"
#include "ControlsDlg.h"
#include "HighPowerInterfaceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControlsDlg dialog


CControlsDlg::CControlsDlg(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CControlsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CControlsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CControlsDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControlsDlg)
	DDX_Control(pDX, IDC_Total, m_EditTotal);
	DDX_Control(pDX, IDC_Auto, m_auto);
	DDX_Control(pDX, IDC_Stoptest, m_stop);
	DDX_Control(pDX, IDC_MinusDark, m_minusdark);
	DDX_Control(pDX, IDC_Single, m_single);
	DDX_Control(pDX, IDC_Retest, m_retest);
	DDX_Control(pDX, IDC_Continuous, m_continue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CControlsDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CControlsDlg)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_Single, OnSingle)
	ON_BN_CLICKED(IDC_Continuous, OnContinuous)
	ON_BN_CLICKED(IDC_Retest, OnRetest)
	ON_BN_CLICKED(IDC_MinusDark, OnMinusDark)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_Stoptest, OnStoptest)
	ON_BN_CLICKED(IDC_Auto, OnAuto)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControlsDlg message handlers
extern CString passpercentpara[4];
extern double intIntegrationTime[3];
extern int intChip; 

BOOL CControlsDlg::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();

	// TODO: Add extra initialization here
	extern int screen_width, screen_height;
	extern float change_width, change_height;
	extern int after_width, after_height;
	extern int after_top, after_left;

	after_left = (int)(0*change_width);
	after_top = (int)(30*change_height);
	after_width = (int)(170*change_width);
	after_height = (int)(637*change_height);
	MoveWindow(after_left, after_top, after_width, after_height);

//	ChangeSize(IDC_MinusDark, change_width, change_height);
//	ChangeSize(IDC_Once, change_width, change_height);
//	ChangeSize(IDC_Continuous, change_width, change_height);
//	ChangeSize(IDC_Auto, change_width, change_height);
//	ChangeSize(IDC_Stoptest, change_width, change_height);
//	ChangeSize(IDC_Retest, change_width, change_height);
//	ChangeSize(IDC_Total, change_width, change_height);
//	ChangeSize(IDC_Passnum, change_width, change_height);
//	ChangeSize(IDC_Failnum, change_width, change_height);
//	ChangeSize(IDC_Passper, change_width, change_height);
//	ChangeSize(IDC_TestTime, change_width, change_height);
//	ChangeSize(IDC_TestSpeed, change_width, change_height);
	ChangeSize(IDC_BUTTON1, change_width, change_height);
	ChangeSize(IDC_BUTTON2, change_width, change_height);
	ChangeSize(IDC_BUTTON3, change_width, change_height);
	ChangeSize(IDC_BUTTON4, change_width, change_height);
	ChangeSize(IDC_BUTTON5, change_width, change_height);
	ChangeSize(IDC_BUTTON7, change_width, change_height);
	ChangeSize(IDC_unit, change_width, change_height);
	ChangeSize(IDC_unit2, change_width, change_height);

//	SetDialogFace();
	SetDialogFace2();

	OnMinusDark();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CControlsDlg::Savepasspercent()
{
	GetDlgItemText(IDC_Total, passpercentpara[0]);
	GetDlgItemText(IDC_Passnum, passpercentpara[1]);
	GetDlgItemText(IDC_Failnum, passpercentpara[2]);
	GetDlgItemText(IDC_Passper, passpercentpara[3]);
}

void CControlsDlg::OnMinusDark() 
{
	// TODO: Add your control notification handler code here
	int chip = 3;
	if(0 == intChip)
	{
		chip = 1;
	}
	else if(intChip < 4)
	{
		chip = 2;
	}
	
	for(int i=0; i<chip; i++)
	{
		setCalDarkParam(i, intIntegrationTime[i]);
	}
}

void CControlsDlg::OnSingle() 
{
	// TODO: Add your control notification handler code here
	CHighPowerInterfaceDlg *pmain = (CHighPowerInterfaceDlg*)GetParent();
	pmain->OnTestSingle();
}

void CControlsDlg::OnContinuous() 
{
	// TODO: Add your control notification handler code here
	CHighPowerInterfaceDlg *pmain = (CHighPowerInterfaceDlg*)GetParent();
	pmain->OnTestContinuous();
}

void CControlsDlg::OnAuto() 
{
	// TODO: Add your control notification handler code here
	CHighPowerInterfaceDlg *pmain = (CHighPowerInterfaceDlg*)GetParent();
	pmain->OnTestAuto();
}

void CControlsDlg::OnRetest() 
{
	// TODO: Add your control notification handler code here
	CHighPowerInterfaceDlg *pmain = (CHighPowerInterfaceDlg*)GetParent();
	pmain->OnRestartTest();
}

void CControlsDlg::OnStoptest() 
{
	// TODO: Add your control notification handler code here
	CHighPowerInterfaceDlg *pmain = (CHighPowerInterfaceDlg*)GetParent();
	pmain->OnStopTest();
}

void CControlsDlg::ShowResults(int total, int pass)
{
	CString str_total, str_pass, str_fail, str_percent;
	int fail = 0;
	double passpercent = 0;

	str_total.Format("%d", total);
	SetDlgItemText(IDC_Total, str_total);

	str_pass.Format("%d", pass);
	SetDlgItemText(IDC_Passnum, str_pass);

	fail = total - pass;
	str_fail.Format("%d", fail);
	SetDlgItemText(IDC_Failnum, str_fail);

	if(total != 0)
	{
		passpercent = (double)(pass * 100) / total;
	}
	str_percent.Format("%0.2f", passpercent);
	str_percent += "%";
	SetDlgItemText(IDC_Passper, str_percent);
}

HBRUSH CControlsDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

BOOL CControlsDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return true;
}

void CControlsDlg::SetDialogFace()
{
	m_minusdark.SetBitmaps(IDB_Button_MinusDarkNormal, IDB_Button_MinusDarkDown,
		                   IDB_Button_MinusDarkHigh, IDB_Button_MinusDarkDisable);
	m_minusdark.SizeToContent();

	m_single.SetBitmaps(IDB_Button_SingleNormal, IDB_Button_SingleDown,
		                IDB_Button_SingleHigh, IDB_Button_SingleDisable);
	m_single.SizeToContent();	

	m_continue.SetBitmaps(IDB_Button_ContinueNormal, IDB_Button_ContinueDown,
		                  IDB_Button_ContinueHigh, IDB_Button_ContinueDisable);
	m_continue.SizeToContent();

	m_auto.SetBitmaps(IDB_Button_AutoNormal, IDB_Button_AutoDown, 
		              IDB_Button_AutoHigh, IDB_Button_AutoDisable);
	m_auto.SizeToContent();

	m_stop.SetBitmaps(IDB_Button_StopNormal, IDB_Button_StopDown,
		              IDB_Button_StopHigh, IDB_Button_StopDisable);
	m_stop.SizeToContent();
}

void CControlsDlg::SetDialogFace2()
{
	m_minusdark.SetBitmaps(IDB_Button_MinusDarkNormal2, IDB_Button_MinusDarkDown2,
		                   IDB_Button_MinusDarkHigh2, IDB_Button_MinusDarkDisable2);
	m_minusdark.SizeToContent();

	m_single.SetBitmaps(IDB_Button_SingleNormal2, IDB_Button_SingleDown2,
		                IDB_Button_SingleHigh2, IDB_Button_SingleDisable2);
	m_single.SizeToContent();	

	m_continue.SetBitmaps(IDB_Button_ContinueNormal2, IDB_Button_ContinueDown2,
		                  IDB_Button_ContinueHigh2, IDB_Button_ContinueDisable2);
	m_continue.SizeToContent();

	m_auto.SetBitmaps(IDB_Button_AutoNormal2, IDB_Button_AutoDown2, 
		              IDB_Button_AutoHigh2, IDB_Button_AutoDisable2);
	m_auto.SizeToContent();

	m_stop.SetBitmaps(IDB_Button_StopNormal2, IDB_Button_StopDown2,
		              IDB_Button_StopHigh2, IDB_Button_StopDisable2);
	m_stop.SizeToContent();
}


BOOL CControlsDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_F5:
			CHighPowerInterfaceDlg *pmain = (CHighPowerInterfaceDlg*)GetParent();
			pmain->OnTestSingle();
			return true;
		}
	}
	return CResizingDialog::PreTranslateMessage(pMsg);
}

void CControlsDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	CString str;

	str = "IR";
	if(strcmp(str, "IR") > 0)
	{
		MessageBox("bigger");
	}
	else if(strcmp(str, "IR") < 0)
	{
		MessageBox("smaller");
	}
	else
	{
		MessageBox("OK!!!");
	}
		
}
