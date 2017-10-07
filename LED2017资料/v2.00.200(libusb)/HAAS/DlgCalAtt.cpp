// DlgCalAtt.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgCalAtt.h"
#include "Note.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCalAtt dialog


CDlgCalAtt::CDlgCalAtt(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCalAtt::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCalAtt)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgCalAtt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCalAtt)
	DDX_Control(pDX, IDCANCEL, m_cExit);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_cStop);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_cSave);
	DDX_Control(pDX, IDC_BUTTON_CAL, m_cCal);
	DDX_Control(pDX, IDC_DRAW, m_cDraw);
	DDX_Control(pDX, IDC_IP, m_cIP);
	DDX_Control(pDX, IDC_LIST, m_cList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalAtt, CDialog)
	//{{AFX_MSG_MAP(CDlgCalAtt)
	ON_BN_CLICKED(IDC_BUTTON_CAL, OnButtonCal)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalAtt message handlers

void CDlgCalAtt::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

BOOL CDlgCalAtt::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_spData.m_bHaveData=FALSE;	
	m_spData.m_iDataType=TYPE_CAL;

	m_fIntTime1=100;
	m_fIntTime2=100;

	m_drawData.bMouse   = FALSE;
	m_drawData.iCurSele = 0;
	m_drawData.bShowCur = FALSE;
	m_drawData.iDrawType= 0;

	ReDraw();

	m_cIP.SetTextColor(RGB(0,0,255))
		.SetFontUnderline(TRUE);

	m_cIP.SetWindowText("");

	//图标
	m_SmallImageList.Create(IDB_SMALLICONS, 16, 1, RGB(255, 255, 255));
	m_cList.SetImageList(&m_SmallImageList, LVSIL_SMALL);

	m_cList.SetExtendedStyle(m_cList.GetExtendedStyle()  | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);

	ReList();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

UINT ThreadCalAttK(LPVOID pParam)
{
    CDlgCalAtt* pDlg=(CDlgCalAtt*)pParam;
	BOOL bR;
	while(!pDlg->m_bCancel)
	{
		bR=pDlg->Test();
		if(!bR)
			break;
		Sleep(100);
	}
	pDlg->m_cSave.EnableWindow(TRUE);

	pDlg->m_bCancel=FALSE;
	pDlg->EnableShow(FALSE);
	return 0;
}

void CDlgCalAtt::OnButtonCal() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
		return;
	g_SPEC.m_fInterval=0.1f;

	EnableShow(TRUE);

	m_bCancel=FALSE;
	AfxBeginThread(ThreadCalAttK,this);
}

void CDlgCalAtt::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	m_bCancel=TRUE;
	m_cStop.EnableWindow(FALSE);
}

void CDlgCalAtt::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	//光谱定标数据
	FILE *fp;
	CString strPathName=g_strCurPath+"CAL\\Att_K.dat";
	if((fp=fopen(strPathName,"wt"))==NULL)
		return;
	else
	{
		int iN=m_spData.m_fRelSpect.GetSize();
		fprintf(fp,"%d %.0f %.0f\n",iN,m_fIntTime1,m_fIntTime2);

		for(int i=0;i<iN;i++)
			fprintf(fp,"%.1f %.1f\n",m_fRelN[i],m_fRelR[i]);
	}
	fclose(fp);
	if(g_bEnglish)
		AfxMessageBox("Save the data succeed!");
	else
		AfxMessageBox("数据保存成功!");
}

void CDlgCalAtt::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlgCalAtt::ReDraw()
{
	m_cDraw.DrawSpect(m_spData,m_drawData,"");
}

void CDlgCalAtt::EnableShow(BOOL bStart)
{
	m_cCal.EnableWindow(!bStart);
	m_cStop.EnableWindow(bStart);
	m_cExit.EnableWindow(!bStart);
}

BOOL CDlgCalAtt::Test()
{
	CCmdTarget::BeginWaitCursor();
	float fMax;
	BOOL bR;
	//////////////////////////////////////////
	////首先测量快速高灵敏
	g_SPEC.m_bAtt=FALSE;
	g_SPEC.m_iMode=0;
	g_SPEC.m_iBin =0;
	bR=g_SPEC.SPEC_GetAutoTime(m_fIntTime1,g_SPEC.m_iAutoLimitTime2,0.6f,m_fIntTime1);
	if(!bR)
	{
		if(g_bEnglish)
			AfxMessageBox("Communication fail！");
		else
			AfxMessageBox("通讯失败，请检查仪器连接！");
		return FALSE;
	}
	bR=g_SPEC.SPEC_DoScan(m_fIntTime1,10,MY_TRIG_NORMAL,fMax,TRUE,m_spData.m_iDataType);
	if(!bR)
	{
		if(g_bEnglish)
			MessageBox("Sample fail!",NULL,MB_ICONSTOP);
		else
			MessageBox("采样失败!",NULL,MB_ICONSTOP);
		return FALSE;
	}
	g_SPEC.SPEC_GetSpectData(FALSE,m_spData);
	int i,iN;
	iN=m_spData.m_fRelSpect.GetSize();
	for(i=0;i<iN;i++)
		m_fRelN[i]=m_spData.m_fRelSpect[i];
	//////////////////////////////////////////
	/////测量快速低灵敏
	g_SPEC.m_iMode=0;
	g_SPEC.m_iBin =1;
	bR=g_SPEC.SPEC_GetAutoTime(m_fIntTime2,g_SPEC.m_iAutoLimitTime2,0.6f,m_fIntTime2);
	if(!bR)
	{
		if(g_bEnglish)
			AfxMessageBox("Communication fail！");
		else
			AfxMessageBox("通讯失败，请检查仪器连接！");
		return FALSE;
	}
	bR=g_SPEC.SPEC_DoScan(m_fIntTime2,10,MY_TRIG_NORMAL,fMax,TRUE,m_spData.m_iDataType);
	if(!bR)
	{
		if(g_bEnglish)
			MessageBox("Sample fail!",NULL,MB_ICONSTOP);
		else
			MessageBox("采样失败!",NULL,MB_ICONSTOP);
		return FALSE;
	}
	g_SPEC.SPEC_GetSpectData(FALSE,m_spData);
	iN=m_spData.m_fRelSpect.GetSize();
	for(i=0;i<iN;i++)
		m_fRelR[i]=m_spData.m_fRelSpect[i];
	/////////////////////////////////////////
	CString strTemp;
	strTemp.Format("%.0f(%.0f%%)",fMax,fMax*100/(g_SPEC.m_nADW-1));
	m_cIP.SetWindowText(strTemp);
	m_cIP.SetFontUnderline(TRUE);
	if((fMax/(g_SPEC.m_nADW-1))<T_L||(fMax>=(g_SPEC.m_nADW-1)))
		m_cIP.SetTextColor(RGB(255,0,0));
	else
		m_cIP.SetTextColor(RGB(0,0,255));

	CCmdTarget::EndWaitCursor();
	bR=g_SPEC.SPEC_OVER(fMax);
	if(bR)
	{
		if(g_bEnglish)
			CNote::Passtext(CString(_T("Overflow!please adjust...")));
		else
			CNote::Passtext(CString(_T("信号溢出!请调节...")));
		CNote::Show(this);
		Sleep(800);
		CNote::Destroy();
	}

	ReDraw();
	ReList();

	return TRUE;
}

void CDlgCalAtt::ReList()
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
		strTemp="WL(nm)";
	else
		strTemp="波长(nm)";
	m_cList.InsertColumn(iN,strTemp);
	m_cList.SetColumnWidth(iN,60);
	iN++;

	if(g_bEnglish)
		strTemp="NONE AD";
	else
		strTemp="高灵敏";
	m_cList.InsertColumn(iN,strTemp);
	m_cList.SetColumnWidth(iN,60);
	iN++;

	if(g_bEnglish)
		strTemp="TINE AD";
	else
		strTemp="低灵敏";
	m_cList.InsertColumn(iN,strTemp);
	m_cList.SetColumnWidth(iN,60);
	iN++;

	int NN=(int)(1/g_SPEC.m_fInterval+0.5f);
	for(int i=0;i<m_spData.m_fRelSpect.GetSize();i++)
	{
		if((i*10)>=m_spData.m_fRelSpect.GetSize())
			break;
		iN=0;
		strTemp.Format("%6.1f",m_spData.m_fSpect1+i*10*m_spData.m_fInterval);
		m_cList.InsertItem(i,strTemp,2);
		iN++;

		strTemp.Format("%6.0f",m_fRelN[i*10]);
		m_cList.SetItemText(i,iN,strTemp);
		iN++;

		strTemp.Format("%6.0f",m_fRelR[i*10]);
		m_cList.SetItemText(i,iN,strTemp);
		iN++;
	}
}
