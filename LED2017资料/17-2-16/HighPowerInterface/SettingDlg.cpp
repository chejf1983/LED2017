// SettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "SettingDlg.h"

#include "HighPowerInterfaceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog

CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingDlg)
	//}}AFX_DATA_INIT
}


void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDlg)
	DDX_Control(pDX, IDC_Exit, m_exit);
	DDX_Control(pDX, IDC_Authority, m_authority);
	DDX_Control(pDX, IDC_SaveSetting, m_saveset);
	DDX_Control(pDX, IDC_SettingTab, m_settingtab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CSettingDlg)
	ON_BN_CLICKED(IDC_Exit, OnExit)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(TCN_SELCHANGE, IDC_SettingTab, OnSelchangeSettingTab)
	ON_BN_CLICKED(IDC_SaveSetting, OnSaveSetting)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_Authority, OnAuthority)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg message handlers
extern bool engineer;
extern bool Operator;
extern bool row1;  //用于区别参数设置和分级的edit范围
extern BinArray binArray;
extern bool csvopen;
int setting_sel = 0;
bool changeset = false;
bool updatelevellist = false;
extern bool stopUpdate;

CList<CString, CString> tempItemforlevel[3];
extern TESTTYPE CHIP[3][18];

BOOL CSettingDlg::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int screen_width = 0, change_width = 0;
	screen_width = GetSystemMetrics(SM_CXSCREEN);
	if(screen_width > 1024)
	{
		change_width = (int)((screen_width - 1024)/2);
	}

	MoveWindow((20 + change_width), 10, 990, 720);
	CRgn rgn;
	rgn.CreateRoundRectRgn(0, 0, 990, 720, 10, 10);
	SetWindowRgn(rgn, true);

	m_settingtab.InsertItem(0, _T("晶片类型"));
	m_settingtab.InsertItem(1, _T("参数设置"));
	m_settingtab.InsertItem(2, _T("分级设置"));	
 
	m_chipfeet.Create(IDD_SetChipFeet, &m_settingtab);
	m_setparameter.Create(IDD_SetParameter, &m_settingtab);
	m_leveldlg.Create(IDD_Level, &m_settingtab);	
	
	CSize size;
	size.cx = 30;
	size.cy = 30;
	m_settingtab.SetItemSize(size);

	CRect rc;
	m_settingtab.GetClientRect(rc);
	rc.top += 30;
	
	m_chipfeet.MoveWindow(&rc);
	m_setparameter.MoveWindow(&rc);
	m_leveldlg.MoveWindow(&rc);
 
	pDialog[0] = &m_chipfeet;
	pDialog[1] = &m_setparameter;
	pDialog[2] = &m_leveldlg;

	m_CurSelTab = 0;
	setting_sel = 0;
	row1 = true;
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);		
	pDialog[2]->ShowWindow(SW_HIDE);

	if(engineer)
	{
		m_saveset.EnableWindow(true);
		SetDlgItemText(IDC_Authority, "工    程    师");
	}
	else if(Operator)
	{
		m_saveset.EnableWindow(true);
		SetDlgItemText(IDC_Authority, "操    作    员");
	}
	else
	{
		m_saveset.EnableWindow(false);
		SetDlgItemText(IDC_Authority, "普  通  用  户");
	}

	initTempItem();

	SetDialogFace();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CSettingDlg::initTempItem()
{
	extern int c[3];
	CString str;

	for(int i=0; i<3; i++)
	{
		tempItemforlevel[i].RemoveAll();

		for(int j=0; j<c[i]; j++)
		{
			str.Format("C%d-%s", i+1, CHIP[i][j].TestItem);
			tempItemforlevel[i].AddTail(str);
		}
	}
	
	return true;
}

void CSettingDlg::OnSelchangeSettingTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	m_CurSelTab = m_settingtab.GetCurSel();

	if(0 == m_CurSelTab)
	{
		pDialog[0]->ShowWindow(SW_SHOW); 
		pDialog[1]->ShowWindow(SW_HIDE);
		pDialog[2]->ShowWindow(SW_HIDE);
	}
	else if(1 == m_CurSelTab)
	{
		row1 = true;
		pDialog[0]->ShowWindow(SW_HIDE); 
		pDialog[1]->ShowWindow(SW_SHOW);
		pDialog[2]->ShowWindow(SW_HIDE);

		if(updatelevellist)
		{
			m_leveldlg.initdlg(binArray.strBinArray, csvopen);
			updatelevellist = false;
		}		
	}
	else if(2 == m_CurSelTab)
	{
		row1 = false;
		pDialog[0]->ShowWindow(SW_HIDE); 
		pDialog[1]->ShowWindow(SW_HIDE);
		pDialog[2]->ShowWindow(SW_SHOW);
	}
}

void CSettingDlg::OnAuthority() 
{
	// TODO: Add your control notification handler code here
	CHighPowerInterfaceDlg *pmain = (CHighPowerInterfaceDlg*)GetParent();
	if(engineer || Operator)
	{
		pmain->OnGuest();
		SetDlgItemText(IDC_Authority, "普  通  用  户");
		m_saveset.EnableWindow(false);
	}
	else
	{
		pmain->OnOperator();
		if(Operator)
		{
			SetDlgItemText(IDC_Authority, "操    作    员");
			m_saveset.EnableWindow(true);
		}
	}

	m_setparameter.ChipsAuthoritydlg();
}

void CSettingDlg::OnSaveSetting() 
{
	// TODO: Add your control notification handler code here
	stopUpdate = true;
	changeset = true;
	
	m_chipfeet.getParameter();
	m_setparameter.getParameter();
	m_leveldlg.getParameter();
	Mappingtestlevel();	
	seperateBincode();

	extern bool rectUpdate;
	rectUpdate = false;
	OnClose();
}

void CSettingDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	stopUpdate = true;
	changeset = false;
	csvopen = false;
	CResizingDialog::OnClose();
}

void CSettingDlg::SetDialogFace()
{
	m_saveset.SetBitmaps(IDB_Button_SureNormal, IDB_Button_SureDown,
		              IDB_Button_SureHigh, IDB_Button_SureDisable);
	m_saveset.SizeToContent();

	m_exit.SetBitmaps(IDB_Button_CancelNormal0, IDB_Button_CancelDown0,
		              IDB_Button_CancelHigh0, IDB_Button_CancelDisable0);
	m_exit.SizeToContent();

	m_authority.SetBitmaps(IDB_SetAuthorityNormal, IDB_SetAuthorityDown,
		                   IDB_SetAuthorityHigh, IDB_SetAuthorityDisable);
	m_authority.SizeToContent();
	m_authority.SetDrawText(true, false)
			.SetFont3D(true, 0, 0, false)
		    .SetFontSize(10, false)
			.SetForceColor(RGB(0, 0, 0), RGB(255, 255, 255), RGB(18, 16, 130), false);

}

void CSettingDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	CResizingDialog::OnLButtonDown(nFlags, point);
}

BOOL CSettingDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default	
//	return CResizingDialog::OnEraseBkgnd(pDC);
	return CResizingDialog::DrawBK(pDC, IDB_SettingBK, 0);
}
