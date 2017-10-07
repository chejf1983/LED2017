// DlgCalFlux.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgCalFlux.h"
#include "Global_MySpec.h"
#include "CalFluxList.h"
#include "Note.h"
#include "MainFrm.h"
#include "WYDlg.h"

#include "DlgSelfPhK.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCalFlux dialog

extern CCalFluxList g_calFluxData;
extern BOOL g_bFluxMod;
extern BOOL g_bModeSelf;

extern	int g_iRange;	  //光度采样的档位
extern	int g_iPerRange;  //光度采样的前一档位

CDlgCalFlux::CDlgCalFlux(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCalFlux::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCalFlux)
	m_bUseCalFlux = TRUE;
	m_iSele = -1;
	m_fCurr = 0.0f;
	m_fFlux = 0.0f;
	m_strName = _T("");
	m_fK = 1.0f;
	m_fModeFluxK = 1.0f;
	m_fModeSelfK = 1.0f;
	//}}AFX_DATA_INIT

	CString strSection   =  "Cal  Flux";
	
	CString strName      =  "Name";
	CString strCurr      =  "Curr";
	CString strFlux      =  "Flux";
	
	CString strTemp;
	m_strName	= AfxGetApp()->GetProfileString(strSection,strName,"");
	strTemp		= AfxGetApp()->GetProfileString(strSection,strCurr,"0.5");
	m_fCurr		= (float)atof(strTemp);
	strTemp		= AfxGetApp()->GetProfileString(strSection,strFlux,"100");
	m_fFlux		= (float)atof(strTemp);
}


void CDlgCalFlux::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCalFlux)
	DDX_Control(pDX, IDC_TEST_SELF_K, m_cTestSelf);
	DDX_Control(pDX, IDC_STATIC_MOD2, m_cModeS2);
	DDX_Control(pDX, IDC_EDIT_MODE_K2, m_cModeSelfK);
	DDX_Control(pDX, IDC_EDIT_MODE_K, m_cModeK);
	DDX_Control(pDX, IDC_STATIC_MOD, m_cModeS);
	DDX_Control(pDX, IDC_EDIT_FLUX_CHECK, m_cFluxCheck);
	DDX_Control(pDX, IDC_BUTTON_CHECK, m_cCheck);
	DDX_Control(pDX, IDC_EDIT_NAME, m_cName);
	DDX_Control(pDX, IDC_EDIT_CURR, m_cCurr);
	DDX_Control(pDX, IDC_EDIT_FLUX, m_cFlux);
	DDX_Control(pDX, IDC_STATIC_SELE, m_cSeleS);
	DDX_Control(pDX, IDC_LIST, m_cList);
	DDX_Control(pDX, IDC_EDIT_K, m_cK);
	DDX_Control(pDX, IDC_COMBO_SELE, m_cSele);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_cSave);
	DDX_Check(pDX, IDC_CHECK_USB_CAL_FLUX, m_bUseCalFlux);
	DDX_CBIndex(pDX, IDC_COMBO_SELE, m_iSele);
	DDX_Text(pDX, IDC_EDIT_CURR, m_fCurr);
	DDX_Text(pDX, IDC_EDIT_FLUX, m_fFlux);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_K, m_fK);
	DDX_Text(pDX, IDC_EDIT_MODE_K, m_fModeFluxK);
	DDX_Text(pDX, IDC_EDIT_MODE_K2, m_fModeSelfK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalFlux, CDialog)
	//{{AFX_MSG_MAP(CDlgCalFlux)
	ON_BN_CLICKED(IDC_CHECK_USB_CAL_FLUX, OnCheckUsbCalFlux)
	ON_CBN_SELCHANGE(IDC_COMBO_SELE, OnSelchangeComboSele)
	ON_BN_CLICKED(IDC_BUTTON_ON, OnButtonOn)
	ON_BN_CLICKED(IDC_BUTTON_OFF, OnButtonOff)
	ON_BN_CLICKED(IDC_BUTTON_CAL, OnButtonCal)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	ON_EN_CHANGE(IDC_EDIT_K, OnChangeEditK)
	ON_BN_CLICKED(IDC_BUTTON_CHECK, OnButtonCheck)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_TEST_SELF_K, OnTestSelfK)
	ON_EN_CHANGE(IDC_EDIT_MODE_K, OnChangeEditModeK)
	ON_EN_CHANGE(IDC_EDIT_MODE_K2, OnChangeEditModeK2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalFlux message handlers

void CDlgCalFlux::OnCheckUsbCalFlux() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);	
	
	m_cSele.EnableWindow(m_bUseCalFlux);
	m_cSeleS.EnableWindow(m_bUseCalFlux);	
}

void CDlgCalFlux::OnSelchangeComboSele() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_iSele>=0)
	{
		float fK;
		CString sTemp;
		fK = g_calFluxData.m_calData.GetAt(m_iSele)->m_fK;
		sTemp.Format("%.6f",fK);
		m_cK.SetWindowText(sTemp);
		m_fK=fK;

		fK = g_calFluxData.m_calData.GetAt(m_iSele)->m_fModeK;
		sTemp.Format("%.6f",fK);
		m_cModeK.SetWindowText(sTemp);
		m_fModeFluxK=fK;

		fK = g_calFluxData.m_calData.GetAt(m_iSele)->m_fSelfModeK;
		sTemp.Format("%.6f",fK);
		m_cModeSelfK.SetWindowText(sTemp);
		m_fModeSelfK=fK;

		sTemp = g_calFluxData.m_calData.GetAt(m_iSele)->m_strName;
		m_cName.SetWindowText(sTemp);

		fK = g_calFluxData.m_calData.GetAt(m_iSele)->m_fFlux;
		sTemp.Format("%.3f",fK);
		m_cFlux.SetWindowText(sTemp);
		m_fFlux=fK;

		fK = g_calFluxData.m_calData.GetAt(m_iSele)->m_fCurr;
		sTemp.Format("%.3f",fK);
		m_cCurr.SetWindowText(sTemp);
		m_fCurr=fK;
	}
	else
	{
		m_fModeFluxK=1;
		m_fModeSelfK=1;
	}
	g_SPEC.m_fModeFluxK = m_fModeFluxK;
	g_SPEC.m_fModeSelfK = m_fModeSelfK;
}

void CDlgCalFlux::OnButtonOn() 
{
	// TODO: Add your control notification handler code here
	BOOL bR=UpdateData(TRUE);
	if(!bR)
		return;
	CWYDlg dlg;
	dlg.m_fSetCurr=m_fCurr;
	dlg.DoModal();
}

void CDlgCalFlux::OnButtonOff() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CCmdTarget::BeginWaitCursor();
	float fFluxAD;
	int i;
	BOOL bR;
	float fZero[4];
	for(int t=0;t<4;t++)
	{
		fZero[t]=0;
		for(i=0;i<10;i++)
		{
			bR=g_SPEC.SPEC_FluxAD(t,fFluxAD);
			if(!bR)
			{
				if(g_bEnglish)
					AfxMessageBox("Communication Fail!");
				else
					AfxMessageBox("通讯失败!");
				return;
			}
			fZero[t]+=fFluxAD;
		}
		fZero[t]=fZero[t]/10;
	}
	CCmdTarget::EndWaitCursor();

	CString sStr;
	sStr.Format("REF1:%.1f,REF2:%.1f,REF3:%.1f,REF4:%.1f",fZero[0],fZero[1],fZero[2],fZero[3]);
	if(g_bEnglish)
		MessageBox("Adjusting Zero Succeed,Please Turn on Lamp,After Lamp Stable,go to Calibrate!",sStr,MB_ICONINFORMATION);
	else
		MessageBox("校零成功,请开灯,等灯稳定以后,再进行标定!",sStr,MB_ICONINFORMATION);
	UpdateData(FALSE);

	for(t=0;t<4;t++)
		g_SPEC.m_fZero[t]=fZero[t];

	////保存暗电流
	CString sTemp;
	FILE *fp;
	sTemp=g_strCurPath;
	if((fp=fopen(sTemp+"CAL\\FluxK.dat","wt"))==0)
	{
		if(g_bEnglish)
			AfxMessageBox("Save fail!",MB_ICONINFORMATION);
		else
			AfxMessageBox("保存失败!",MB_ICONINFORMATION);
		return;
	}
	else
	{
		fprintf(fp,"Zero1:%10.6f\n",g_SPEC.m_fZero[0]);
		fprintf(fp,"Zero2:%10.6f\n",g_SPEC.m_fZero[1]);
		fprintf(fp,"Zero3:%10.6f\n",g_SPEC.m_fZero[2]);
		fprintf(fp,"Zero4:%10.6f\n",g_SPEC.m_fZero[3]);

		fprintf(fp,"K12:%10.6f\n",g_SPEC.m_fRangeK[0]);
		fprintf(fp,"K23:%10.6f\n",g_SPEC.m_fRangeK[1]);
		fprintf(fp,"K34:%10.6f\n",g_SPEC.m_fRangeK[2]);

		fclose(fp);
		return;
	}
}

void CDlgCalFlux::OnButtonCal() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
		return;
	
	CCmdTarget::BeginWaitCursor();
	
	BOOL bR;
	CString strTemp;
	//////////用光谱仪的光度探头测试的光通量///////////////
	if(g_bEnglish)
		strTemp.Format("Get photo flux...");
	else
		strTemp.Format("正在测试光通量...");
	CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,0));
	float fFlux;
	while(1)
	{
		int iN=2;
		float fSum=0;
		bR=g_SPEC.SPEC_FluxAD(g_iRange,fFlux);
		Sleep(200);
		for(int i=0;i<iN;i++)
		{
			bR=g_SPEC.SPEC_FluxAD(g_iRange,fFlux);
			if(!bR)
			{
				if(g_bEnglish)
					AfxMessageBox("Communication fail!");
				else
					AfxMessageBox("通讯失败!");
				return;
			}
			fSum=fSum+fFlux;
		}
		fFlux=fSum/iN;
		if(fFlux>AD_FLUX_MAX)
		{
			Sleep(20);
			g_iRange++;
		}
		else if(fFlux<AD_FLUX_MIN)
		{
			Sleep(20);
			g_iRange--;
		}
		else
			break;

		if(g_iRange<0)
		{
			g_iRange=0;
			bR=g_SPEC.SPEC_FluxAD(g_iRange,fFlux);
			if(!bR)
			{
				if(g_bEnglish)
					AfxMessageBox("Communication fail!");
				else
					AfxMessageBox("通讯失败!");
				return;
			}
			break;
		}
		if(g_iRange>=3)
		{
			g_iRange=3;
			bR=g_SPEC.SPEC_FluxAD(g_iRange,fFlux);
			if(!bR)
			{
				if(g_bEnglish)
					AfxMessageBox("Communication fail!");
				else
					AfxMessageBox("通讯失败!");
				return;
			}
			break;
		}
	}
	//AD
	CString sTemp;
	sTemp.Format("AD:%.1f",fFlux);

	fFlux=fFlux-g_SPEC.m_fZero[g_iRange];
	float fFluxK;
	if(fFlux<100)
	{
		fFluxK=1;
		if(g_bEnglish)
			AfxMessageBox("Single is too weak");
		else
			AfxMessageBox("信号太弱，无法定标,请检查！");
		return;
	}
	else
	{
		if(g_iRange==0)
			fFlux=(float)(fFlux/g_SPEC.m_fRangeK[0]);
		else if(g_iRange==1)
			fFlux=(float)(fFlux);
		else if(g_iRange==2)
			fFlux=(float)(fFlux*g_SPEC.m_fRangeK[1]);
		else
			fFlux=(float)(fFlux*g_SPEC.m_fRangeK[1]*g_SPEC.m_fRangeK[2]);
		fFluxK=(float)(m_fFlux/fFlux);
	}

	int iType=g_SPEC.m_iTestType;

	m_fK=fFluxK;
	g_SPEC.m_CAL_fFluxK[iType] = fFluxK;
	CMainFrame::ShowNote("",TRUE,RGB(255,0,0));
	m_spData.m_bTestPH=TRUE;
	m_spData.m_fPH=m_fFlux;
	/////////////////////////////////////////////
	CCmdTarget::BeginWaitCursor();
	
	if(m_spData.m_fPh_e<0)
		return;

	strTemp.Format("%.6f",m_fK);
	m_cK.SetWindowText(strTemp);

	m_cSave.EnableWindow(TRUE);
	if(g_bEnglish)
		MessageBox("OK!",sTemp,MB_ICONINFORMATION);
	else
		MessageBox("完成定标,按'保存'保存定标数据!",sTemp,MB_ICONINFORMATION);
	return;
}

void CDlgCalFlux::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
		return;	

	g_SPEC.m_fModeFluxK = m_fModeFluxK;
	g_SPEC.m_fModeSelfK = m_fModeSelfK;

	int iType=g_SPEC.m_iTestType;
	g_SPEC.m_CAL_fStaFlux[iType] = m_fFlux;
	g_SPEC.m_CAL_iRange[iType]   = g_iRange;
	g_SPEC.m_CAL_fFluxK[iType]   = m_fK;
	g_SPEC.FLUX_SaveCalK(g_strCurPath+"CAL\\Flux.cal");

	CCalFluxData *temp	= new CCalFluxData();
	temp->m_fCurr		= (float)m_fCurr;
	temp->m_fFlux		= (float)m_fFlux;
	temp->m_fK			= (float)m_fK;
	temp->m_fModeK		= (float)m_fModeFluxK;
	temp->m_fSelfModeK	= (float)m_fModeSelfK;
	temp->m_strName		= m_strName;

	CTime tNow;
	tNow=CTime::GetCurrentTime();
	temp->m_strDate=tNow.Format("%Y-%m-%d,%I:%M");

	int iN,iCurN=-1;
	iN=g_calFluxData.m_calData.GetSize();
	if(iN>0)
	{
		for(int i=0;i<iN;i++)
		{
			if(g_calFluxData.m_calData.GetAt(i)->m_strName==m_strName)
			{
				iCurN=i;
			}
		}
	}
	if(iCurN==-1)
		g_calFluxData.m_calData.Add(temp);
	else
	{
		g_calFluxData.m_calData.GetAt(iCurN)->m_fCurr	= temp->m_fCurr;
		g_calFluxData.m_calData.GetAt(iCurN)->m_fFlux	= temp->m_fFlux;
		g_calFluxData.m_calData.GetAt(iCurN)->m_fK		= temp->m_fK;
		g_calFluxData.m_calData.GetAt(iCurN)->m_fModeK	= temp->m_fModeK;
		g_calFluxData.m_calData.GetAt(iCurN)->m_fSelfModeK= temp->m_fSelfModeK;
		g_calFluxData.m_calData.GetAt(iCurN)->m_strName	= temp->m_strName;
		g_calFluxData.m_calData.GetAt(iCurN)->m_strDate	= temp->m_strDate;
	}
	g_calFluxData.F_Save(g_strCurPath+"Cal\\Flux_multi.cal");

	m_cSave.EnableWindow(FALSE);

	ReList();

	m_cSele.SetCurSel(g_calFluxData.m_calData.GetSize()-1);	
}

void CDlgCalFlux::OnButtonDel() 
{
	// TODO: Add your control notification handler code here
	if(m_iCurSele<0||m_iCurSele>=g_calFluxData.m_calData.GetSize())
		return;
	
	int iR;
	if(g_bEnglish)
		iR=MessageBox("Are you sure?",NULL,MB_ICONINFORMATION|MB_OKCANCEL);
	else
		iR=MessageBox("确定删除所选定标数据?",NULL,MB_ICONINFORMATION|MB_OKCANCEL);
	if(iR==IDCANCEL)
		return;
	g_calFluxData.m_calData.RemoveAt(m_iCurSele);
	ReList();
}

void CDlgCalFlux::OnCancel() 
{
	// TODO: Add extra cleanup here
	UpdateData(TRUE);
	g_SPEC.m_fModeFluxK = m_fModeFluxK;
	g_SPEC.m_fModeSelfK = m_fModeSelfK;

	g_calFluxData.F_Save(g_strCurPath+"Cal\\Flux_multi.cal");
	
	CString strSection   = "Cal  Flux";
	
	CString strName      = "Name";
	CString strCurr      = "Curr";
	CString strFlux      = "Flux";
	
	CString strTemp;
	AfxGetApp()->WriteProfileString(strSection,strName,m_strName);
	strTemp.Format("%f",m_fCurr);
	AfxGetApp()->WriteProfileString(strSection,strCurr,strTemp);
	strTemp.Format("%f",m_fFlux);
	AfxGetApp()->WriteProfileString(strSection,strFlux,strTemp);
	
	CDialog::OnCancel();
}

void CDlgCalFlux::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

BOOL CDlgCalFlux::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cList.ModifyStyle(0,LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS);
	m_cList.SetExtendedStyle(m_cList.GetExtendedStyle()  |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES| LVS_EX_HEADERDRAGDROP/*|LVS_EX_CHECKBOXES*/);

	m_spData.m_bHaveData = FALSE;
	m_spData.m_iDataType = TYPE_SCAN;

	m_cFluxCheck.EnableWindow(FALSE);

	
	bGo	= FALSE;
	m_drawData.bMouse	= FALSE;
	m_drawData.iCurSele	= 0;
	m_drawData.bShowCur	= TRUE;
	m_drawData.iDrawType= 0;

	//
	if(g_bFluxMod)
	{
		m_cModeS.ShowWindow(TRUE);
		m_cModeK.ShowWindow(TRUE);
	}
	else
	{
		m_cModeS.ShowWindow(FALSE);
		m_cModeK.ShowWindow(FALSE);
		m_fModeFluxK=1;
	}
	if(g_bModeSelf)
	{
		m_cTestSelf.ShowWindow(TRUE);
		m_cModeS2.ShowWindow(TRUE);
		m_cModeSelfK.ShowWindow(TRUE);
	}
	else
	{
		m_cTestSelf.ShowWindow(FALSE);
		m_cModeS2.ShowWindow(FALSE);
		m_cModeSelfK.ShowWindow(FALSE);
	}
	
	ReList();
	
	m_cSele.EnableWindow(m_bUseCalFlux);
	m_cSeleS.EnableWindow(m_bUseCalFlux);

	OnSelchangeComboSele();
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCalFlux::ReList()
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

	//增加修正系数和自吸收系数
	if(!g_bEnglish)
		strTemp=" 修正系数";
	else
		strTemp=" Mode K";
	m_cList.InsertColumn(iN,strTemp);
	m_cList.SetColumnWidth(iN,120);
	iN++;

	if(!g_bEnglish)
		strTemp=" 自吸收系数";
	else
		strTemp=" Self K";
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

	for(int i=0;i<g_calFluxData.m_calData.GetSize();i++)
	{
		iN=0;
		
		strTemp.Format(" %04d",i+1);
		m_cList.InsertItem(i,strTemp,6);
		iN++;
		
		strTemp=g_calFluxData.m_calData.GetAt(i)->m_strName;
		m_cList.SetItemText(i,iN,strTemp);
		iN++;
		
		strTemp.Format("%.6f",g_calFluxData.m_calData.GetAt(i)->m_fK);
		m_cList.SetItemText(i,iN,strTemp);
		iN++;

		strTemp.Format("%.6f",g_calFluxData.m_calData.GetAt(i)->m_fModeK);
		m_cList.SetItemText(i,iN,strTemp);
		iN++;

		strTemp.Format("%.6f",g_calFluxData.m_calData.GetAt(i)->m_fSelfModeK);
		m_cList.SetItemText(i,iN,strTemp);
		iN++;
		
		strTemp=g_calFluxData.m_calData.GetAt(i)->m_strDate;
		m_cList.SetItemText(i,iN,strTemp);
		iN++;
	}
	ReListSele();

}

void CDlgCalFlux::ReListSele()
{
	int iSele=m_cSele.GetCurSel();
	if(iSele==-1)
		iSele=g_iSeleCalFlux;
	m_cSele.ResetContent();
	CString strTemp;
	for(int i=0;i<g_calFluxData.m_calData.GetSize();i++)
	{
		strTemp.Format("%2d.  %s",i+1,g_calFluxData.m_calData.GetAt(i)->m_strName);
		m_cSele.InsertString(i,strTemp);
	}
	m_cSele.SetCurSel(iSele);
	if(iSele<0||iSele>=g_calFluxData.m_calData.GetSize())
		m_cSele.SetCurSel(0);

}

void CDlgCalFlux::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	m_iCurSele=pNMListView->iItem;
	if(m_iCurSele>=0)
	{
		m_iSele=m_iCurSele;
		UpdateData(FALSE);
		OnSelchangeComboSele();
	}

	*pResult = 0;
}

BOOL CDlgCalFlux::AUTO(float &fIntTime)
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

void CDlgCalFlux::OnChangeEditK() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_cSave.EnableWindow(TRUE);
}

void CDlgCalFlux::OnButtonCheck() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_iSele>=0)
		g_SPEC.m_CAL_fFluxK[g_SPEC.m_iTestType] = g_calFluxData.m_calData.GetAt(m_iSele)->m_fK;
	BOOL bR;
	if(!bGo)
	{
		bGo=TRUE;
		bR=FluxCheck();
		if(g_bEnglish)
			m_cCheck.SetWindowText("Stop");
		else
			m_cCheck.SetWindowText("停止检验");
		if(!bR)
		{
			bGo=FALSE;
			if(g_bEnglish)
			{
				m_cCheck.SetWindowText("Check");
			}
			else
			{
				m_cCheck.SetWindowText("检验(&k)");
			}
		}
		else
		{
			SetTimer(1,1,NULL);
		}
	}
	else
	{
		bGo=FALSE;
		if(g_bEnglish)
		{
			m_cCheck.SetWindowText("Check");
		}
		else
		{
			m_cCheck.SetWindowText("检验(&k)");
		}
		KillTimer(1);
	}
}

BOOL CDlgCalFlux::FluxCheck()
{
	CCmdTarget::BeginWaitCursor();
	UpdateData(TRUE);
	float fFlux1,fAD;
	BOOL bR=g_SPEC.SPEC_FluxAuto(fAD,fFlux1);
	if(!bR)
		return FALSE;
	CString sTemp;
	sTemp=g_SPEC.sFormat(fFlux1,5);
	m_cFluxCheck.SetWindowText(sTemp);
	return TRUE;
}

void CDlgCalFlux::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(bGo)
	{
		KillTimer(1);
		CCmdTarget::BeginWaitCursor();
		FluxCheck();
		CCmdTarget::EndWaitCursor();
		SetTimer(1,500,NULL);
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CDlgCalFlux::OnTestSelfK() 
{
	// TODO: Add your control notification handler code here
	CDlgSelfPhK dlg;
	dlg.m_fSelfPhK	= m_fModeSelfK;
	dlg.DoModal();
	m_fModeSelfK	= dlg.m_fSelfPhK;
	g_SPEC.m_fModeSelfK = dlg.m_fSelfPhK;
	UpdateData(FALSE);
}

void CDlgCalFlux::OnChangeEditModeK() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_cSave.EnableWindow(TRUE);
}

void CDlgCalFlux::OnChangeEditModeK2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_cSave.EnableWindow(TRUE);
}
