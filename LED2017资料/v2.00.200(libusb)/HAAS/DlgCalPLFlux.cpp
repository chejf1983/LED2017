// DlgCalPLFlux.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgCalPLFlux.h"
#include "Global_MySpec.h"
#include "math.h"
#include "Note.h"

#include "CalFluxPLData.h"
#include "CalFluxPLList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCalPLFlux dialog
extern CCalFluxPLList g_CalFluxPLData;
extern int g_iSeleCalPLFlux;
extern BOOL g_bUseFluxPL;

CDlgCalPLFlux::CDlgCalPLFlux(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCalPLFlux::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCalPLFlux)
	m_bUseFluxPL= FALSE;
	m_iSele		= -1;
	m_fFlux		= 0.0f;
	m_fK		= 0.0f;
	m_strName	= _T("");
	//}}AFX_DATA_INIT
	CString strSection   =  "Cal_PL_Flux1";

	CString strUseFluxPL =  "UseFluxPL";
	CString strNameE     =  "NameE";
	CString strNameC     =  "NameC";
	CString strFlux      =  "Flux";
//	CString strK	     =  "K";

	CString strTemp;
	m_bUseFluxPL= AfxGetApp()->GetProfileInt(strSection,strUseFluxPL,TRUE);
	m_strNameE	= AfxGetApp()->GetProfileString(strSection,strNameE,"LAMP");
	m_strNameC	= AfxGetApp()->GetProfileString(strSection,strNameC,"光通量标准灯");
	if(g_bEnglish)
	{
		m_strName = m_strNameE;
	}
	else
	{
		m_strName = m_strNameC;
	}
	strTemp		= AfxGetApp()->GetProfileString(strSection,strFlux,"1000");
	m_fFlux		= (float)atof(strTemp);
}


void CDlgCalPLFlux::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCalPLFlux)
	DDX_Control(pDX, IDC_COMBO_SELE, m_cSele);
	DDX_Control(pDX, IDCANCEL, m_cCancel);
	DDX_Control(pDX, IDC_LIST, m_cList);
	DDX_Control(pDX, IDC_EDIT_NAME, m_cName);
	DDX_Control(pDX, IDC_EDIT_K, m_cK);
	DDX_Control(pDX, IDC_EDIT_FLUX, m_cFlux);
	DDX_Control(pDX, IDC_DRAW, m_cDraw);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_cSave);
	DDX_Control(pDX, IDC_BUTTON_DEL, m_cDel);
	DDX_Check(pDX, IDC_CHECK_USB_CAL_FE, m_bUseFluxPL);
	DDX_CBIndex(pDX, IDC_COMBO_SELE, m_iSele);
	DDX_Text(pDX, IDC_EDIT_FLUX, m_fFlux);
	DDX_Text(pDX, IDC_EDIT_K, m_fK);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalPLFlux, CDialog)
	//{{AFX_MSG_MAP(CDlgCalPLFlux)
	ON_BN_CLICKED(IDC_BUTTON_CAL_FLUX, OnButtonCalFlux)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_CBN_SELCHANGE(IDC_COMBO_SELE, OnSelchangeComboSele)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalPLFlux message handlers

void CDlgCalPLFlux::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

BOOL CDlgCalPLFlux::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_spData.m_bHaveData= FALSE;
	m_spData.m_iDataType= TYPE_SCAN;

	m_drawData.bMouse	= FALSE;
	m_drawData.iCurSele	= 0;
	m_drawData.bShowCur	= TRUE;
	m_drawData.iDrawType= 1;

	ReDraw();
	
	ReList();

	m_cK.SetWindowText("1.0");

	m_cList.SetExtendedStyle(m_cList.GetExtendedStyle()  | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES| LVS_EX_HEADERDRAGDROP);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCalPLFlux::OnButtonCalFlux() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
		return;

	CCmdTarget::BeginWaitCursor();

	BOOL bR;
	bR=g_SPEC.Get_PL();
	if(!bR)
	{
		if(g_bEnglish)
			AfxMessageBox("Please first Spectrum Calibration!");
		else
			AfxMessageBox("请先进行光谱定标!");
		return;
	}

	float fIntTime;
	bR=AUTO(fIntTime);
	if(!bR)
		return;

	if(g_bEnglish)
		CNote::Passtext(CString(_T("Preheat,wait...")));
	else
		CNote::Passtext(CString(_T("正在预热,请等待...")));
	CNote::Show(this);
	Sleep(2000);
	CNote::Destroy();

	bR=g_SPEC.SPEC_GetDark(fIntTime,2);
	if(!bR)
		return;
	Sleep(200);

	float fMax;
	bR=g_SPEC.SPEC_DoScan(fIntTime*1.0f,10,MY_TRIG_NORMAL,fMax,FALSE,m_spData.m_iDataType);
	if(!bR)
	{
		if(g_bEnglish)
			MessageBox("Sample fail!",NULL,MB_ICONSTOP);
		else
			MessageBox("采样失败!",NULL,MB_ICONSTOP);
		return;
	}

	bR=g_SPEC.SPEC_OVER(fMax);
	if(bR)
	{
		if(g_bEnglish)
			CNote::Passtext(CString(_T("Overflow,please adjust...")));
		else
			CNote::Passtext(CString(_T("信号溢出!请调节...")));
		CNote::Show(this);
		Sleep(500);
		CNote::Destroy();
		return;
	}

	Sleep(500);
	// Calc. spectrum
	g_SPEC.SPEC_GetSpectData(TRUE,m_spData);

	m_drawData.bShowCur = FALSE;

	ReDraw();
	CCmdTarget::BeginWaitCursor();

	if(m_spData.m_fPH<0)
		return;

	float fK;
	fK=m_fFlux/(m_spData.m_fPh);

	CString strTemp;
	strTemp.Format("%e",fK);
	m_cK.SetWindowText(strTemp);

	m_cSave.EnableWindow(TRUE);

	if(g_bEnglish)
		MessageBox("OK!",NULL,MB_ICONINFORMATION);
	else
		MessageBox("完成定标,按'保存'保存定标数据!",NULL,MB_ICONINFORMATION);
	return;
}

void CDlgCalPLFlux::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
		return;	

	CCalFluxPLData *temp=new CCalFluxPLData();

	temp->m_fFlux	= m_fFlux;
	temp->m_fK		= (float)m_fK;
	temp->m_strName=m_strName;

	CTime tNow;
	tNow=CTime::GetCurrentTime();
	temp->m_strDate=tNow.Format("%Y-%m-%d,%I:%M");

	g_CalFluxPLData.m_calData.Add(temp);

	m_cSave.EnableWindow(FALSE);

	ReList();

	m_cSele.SetCurSel(g_CalFluxPLData.m_calData.GetSize()-1);
}

void CDlgCalPLFlux::OnButtonDel() 
{
	// TODO: Add your control notification handler code here
	if(m_iCurSele<0||m_iCurSele>=g_CalFluxPLData.m_calData.GetSize())
		return;

	int iR;
	if(g_bEnglish)
		iR=MessageBox("Are you sure?",NULL,MB_ICONINFORMATION|MB_OKCANCEL);
	else
		iR=MessageBox("确定删除所选定标数据?",NULL,MB_ICONINFORMATION|MB_OKCANCEL);
	if(iR==IDCANCEL)
		return;
	g_CalFluxPLData.m_calData.RemoveAt(m_iCurSele);
	ReList();
}

void CDlgCalPLFlux::OnCancel() 
{
	// TODO: Add extra cleanup here
	UpdateData(TRUE);
	if(g_bEnglish)
	{
		m_strNameE = m_strName;
	}
	else
	{
		m_strNameC = m_strName;
	}
	g_CalFluxPLData.F_Save(g_strCurPath+"Cal\\PLFlux.cal");
	CString strSection   =  "Cal_PL_Flux1";

	CString strUseFluxPL =  "UseFluxPL";
	CString strNameE     =  "NameE";
	CString strNameC     =  "NameC";
	CString strFlux      =  "Flux";
//	CString strK	     =  "K";

	CString strTemp;
	AfxGetApp()->WriteProfileInt(strSection,strUseFluxPL,m_bUseFluxPL);
	AfxGetApp()->WriteProfileString(strSection,strNameE,m_strNameE);
	AfxGetApp()->WriteProfileString(strSection,strNameC,m_strNameC);
	strTemp.Format("%f",m_fFlux);
	AfxGetApp()->WriteProfileString(strSection,strFlux,strTemp);
	
	CDialog::OnCancel();
}

void CDlgCalPLFlux::OnSelchangeComboSele() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CDlgCalPLFlux::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_iCurSele=pNMListView->iItem;
	
	*pResult = 0;
}

void CDlgCalPLFlux::ReList()
{
	m_cList.DeleteAllItems();
	while(1)
	{
		if(m_cList.DeleteColumn(0)==FALSE)
			break;
	}
	
	CString strTemp;
	int iN=0;
	
	if(g_bEnglish)
		strTemp="SN.";
	else
		strTemp="序号";
	m_cList.InsertColumn(iN,strTemp);
	m_cList.SetColumnWidth(iN,60);
	iN++;
	
	
	if(!g_bEnglish)
		strTemp=" 类型";
	else
		strTemp=" Name";
	m_cList.InsertColumn(iN,strTemp);
	m_cList.SetColumnWidth(iN,120);
	iN++;
	
	if(!g_bEnglish)
		strTemp=" 定标系数";
	else
		strTemp=" K";
	m_cList.InsertColumn(iN,strTemp);
	m_cList.SetColumnWidth(iN,120);
	iN++;
	
	if(!g_bEnglish)
		strTemp=" 标准灯光通量(nm)";
	else
		strTemp=" Flux(nm)";
	m_cList.InsertColumn(iN,strTemp);
	m_cList.SetColumnWidth(iN,120);
	iN++;

	if(!g_bEnglish)
		strTemp=" 时间";
	else
		strTemp=" Time";
	m_cList.InsertColumn(iN,strTemp);
	m_cList.SetColumnWidth(iN,120);
	iN++;
	
	for(int i=0;i<g_CalFluxPLData.m_calData.GetSize();i++)
	{
		iN=0;
		
		strTemp.Format(" %04d",i+1);
		m_cList.InsertItem(i,strTemp,6);
		iN++;
		
		strTemp=g_CalFluxPLData.m_calData.GetAt(i)->m_strName;
		m_cList.SetItemText(i,iN,strTemp);
		iN++;
		
		strTemp.Format("%e",g_CalFluxPLData.m_calData.GetAt(i)->m_fK);
		m_cList.SetItemText(i,iN,strTemp);
		iN++;

		strTemp.Format("%.1f",g_CalFluxPLData.m_calData.GetAt(i)->m_fFlux);
		m_cList.SetItemText(i,iN,strTemp);
		iN++;
	
		strTemp=g_CalFluxPLData.m_calData.GetAt(i)->m_strDate;
		m_cList.SetItemText(i,iN,strTemp);
		iN++;
	}
	ReListSele();
}

void CDlgCalPLFlux::ReListSele()
{
	int iSele=m_cSele.GetCurSel();
	if(iSele==-1)
		iSele=g_iSeleCalPLFlux;
	m_cSele.ResetContent();
	CString strTemp;
	for(int i=0;i<g_CalFluxPLData.m_calData.GetSize();i++)
	{
		strTemp.Format("%2d.  %s",i+1,g_CalFluxPLData.m_calData.GetAt(i)->m_strName);
		m_cSele.InsertString(i,strTemp);
	}
	m_cSele.SetCurSel(iSele);
	if(iSele<0||iSele>=g_CalFluxPLData.m_calData.GetSize())
		m_cSele.SetCurSel(0);
}

BOOL CDlgCalPLFlux::AUTO(float &fIntTime)
{
	BOOL bR;
	CString sStr;
	
	if(g_bEnglish)
		CNote::Passtext(CString(_T("Please waiting...")));
	else
		CNote::Passtext(CString(_T("自动选择积分时间,请等待...")));
	CNote::Show(this);
	
	bR=g_SPEC.SPEC_GetAutoTime(fIntTime,10000);
	
	CNote::Destroy();
	return bR;
}

void CDlgCalPLFlux::ReDraw()
{
	m_cDraw.DrawSpect(m_spData,m_drawData,"");
}
