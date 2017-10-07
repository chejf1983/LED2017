// LEDTypeCal.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "LEDTypeCal.h"
#include "ProcessData.h"
#include "Global_MySpec.h"
#include "Note.h"
#include "math.h"
#include "MusterType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLEDTypeCal dialog
extern BOOL g_bEnglish;
extern CProcessData g_doData;

CLEDTypeCal::CLEDTypeCal(CWnd* pParent /*=NULL*/)
	: CDialog(CLEDTypeCal::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLEDTypeCal)
	m_strName = _T("");
	//}}AFX_DATA_INIT
	CString  strSection = "Patt Name";
	CString  strName_CN    = "Name1";
	CString  strName_EN    = "Name2";

	m_strName_CN = AfxGetApp()->GetProfileString(strSection,strName_CN,"红色LED");
	m_strName_EN = AfxGetApp()->GetProfileString(strSection,strName_EN,"Red LED");
	if(g_bEnglish)
	{
		m_strName = m_strName_EN;
	}
	else
	{
		m_strName = m_strName_CN;
	}
}


void CLEDTypeCal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLEDTypeCal)
	DDX_Control(pDX, IDC_BUTTON_OPEN, m_cOpen);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_cSave);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_cDel);
	DDX_Control(pDX, IDCANCEL, m_cCancel);
	DDX_Control(pDX, IDC_IP, m_cIP);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_cAdd);
	DDX_Control(pDX, IDC_BUTTON_CAL, m_cCal);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_cStop);
	DDX_Control(pDX, IDC_DRAW, m_cDraw);
	DDX_Control(pDX, IDC_LIST, m_cList);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLEDTypeCal, CDialog)
	//{{AFX_MSG_MAP(CLEDTypeCal)
	ON_BN_CLICKED(IDC_BUTTON_CAL, OnButtonCal)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	ON_BN_CLICKED(ID_SELE, OnSele)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLEDTypeCal message handlers

void CLEDTypeCal::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

BOOL CLEDTypeCal::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int iN=g_doData.m_sData.m_listLamp.GetSize();
	if(iN<=0)
		m_cDel.EnableWindow(FALSE);
	else
		m_cDel.EnableWindow(TRUE);

	m_spData.m_bHaveData=FALSE;	
	m_spData.m_iDataType=TYPE_CAL;

	m_drawData.bMouse=FALSE;
	m_drawData.iCurSele=0;
	m_drawData.bShowCur=FALSE;
	m_drawData.iDrawType=0;

	ReDraw();

	m_cIP.SetTextColor(RGB(0,0,255))
		.SetFontUnderline(TRUE);

	m_cIP.SetWindowText("");
	//图标
	m_SmallImageList.Create(IDB_SMALLICONS, 16, 1, RGB(255, 255, 255));
	m_cList.SetImageList(&m_SmallImageList, LVSIL_SMALL);

	m_cList.SetExtendedStyle(m_cList.GetExtendedStyle()  | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);

	ReList();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

UINT ThreadLEDCal(LPVOID pParam)
{
    CLEDTypeCal* pDlg=(CLEDTypeCal*)pParam;
	BOOL bR;
	while(!pDlg->m_bCancel)
	{
		bR=pDlg->Test();
		if(!bR)
			break;
		Sleep(100);
	}
//	pDlg->m_cSave.EnableWindow(TRUE);

	pDlg->m_bCancel=FALSE;
	pDlg->EnableShow(FALSE);
	return 0;
}

void CLEDTypeCal::OnButtonCal() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
		return;
	EnableShow(TRUE);
	m_bCancel=FALSE;
	AfxBeginThread(ThreadLEDCal,this);
}

void CLEDTypeCal::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	m_bCancel=TRUE;
	m_cStop.EnableWindow(FALSE);
}

void CLEDTypeCal::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_strName=="")
	{
		if(g_bEnglish)
			AfxMessageBox("Please input muster's name!");
		else
			AfxMessageBox("请输入样品类别名称!");
		return;
	}
	int i,iR,iCur;
	int iN=g_doData.m_sData.m_listLamp.GetSize();
	iCur=iN;
	for(i=0;i<iN;i++)
	{
		if(g_doData.m_sData.m_listLamp[i]->m_strName==m_strName)
		{
			if(g_bEnglish)
				iR=AfxMessageBox("Display "+m_strName+"?",MB_ICONINFORMATION|MB_YESNO);
			else
				iR=AfxMessageBox("是否替换"+m_strName+"?",MB_ICONINFORMATION|MB_YESNO);
			if(iR==IDYES)
			{
				iCur=i;
				g_doData.m_sData.m_listLamp.RemoveAt(i);
			}
			else
				return;
		}
	}

	CMusterType *temp = new CMusterType();
	temp->m_strName   = m_strName;
	for(i=0;i<m_spData.m_fRelSpect.GetSize();i++)
	{
		float fTemp;
		fTemp=m_fRefS[i];
		temp->m_fRefS.Add(fTemp);
		fTemp=m_fRefQ[i];
		temp->m_fRefQ.Add(fTemp);
	}
	g_doData.m_sData.m_listLamp.InsertAt(iCur,temp);

	ReList();
	m_cAdd.EnableWindow(FALSE);
	m_cDel.EnableWindow(TRUE);
}

void CLEDTypeCal::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	POSITION p = m_cList.GetFirstSelectedItemPosition();
	CString msg = _T("");
	while (p)
	{
		int nSelected = m_cList.GetNextSelectedItem(p);
		if (msg.IsEmpty())
			msg = _T("The following items are selected: ");

		CString str;
		str.Format(_T("%s"), m_cList.GetItemText(nSelected, 0));
		int iSele=atoi(str)-1;
		if(iSele>=0&&iSele<g_doData.m_sData.m_listLamp.GetSize())
		{
			int iR;
			if(g_bEnglish)
				iR=MessageBox("Delete?",NULL,MB_OKCANCEL|MB_ICONINFORMATION);
			else
				iR=MessageBox("确定删除所选定的定标系数?",NULL,MB_OKCANCEL|MB_ICONINFORMATION);
			if(iR==IDCANCEL)
				break;
			g_doData.m_sData.m_listLamp.RemoveAt(iSele);
			ReList();
		}
		break;
	}
}

void CLEDTypeCal::OnCancel() 
{
	// TODO: Add extra cleanup here
	CString  strSection  = "Patt Name";
	CString  strName_CN    = "Name1";
	CString  strName_EN    = "Name2";
	
	AfxGetApp()->WriteProfileString(strSection,strName_CN, m_strName_CN);
	AfxGetApp()->WriteProfileString(strSection,strName_EN, m_strName_EN);
	
	CDialog::OnCancel();
}

void CLEDTypeCal::ReList()
{
	m_cList.DeleteAllItems();
	while(1)
	{
		if(m_cList.DeleteColumn(0)==FALSE)
			break;
	}

	int iN=0;

	CString strTemp;

	if(g_bEnglish)
		strTemp="Number";
	else
		strTemp="序号";
	m_cList.InsertColumn(iN,strTemp);
	m_cList.SetColumnWidth(iN,60);
	iN++;

	if(g_bEnglish)
		strTemp="Name";
	else
		strTemp="名称";
	m_cList.InsertColumn(iN,strTemp);
	m_cList.SetColumnWidth(iN,80);
	iN++;

	int iTempN=g_doData.m_sData.m_listLamp.GetSize();
	for(int i=0;i<iTempN;i++)
	{
		iN=0;
		strTemp.Format("%d",i+1);
		m_cList.InsertItem(i,strTemp,2);
		iN++;

		m_cList.SetItemText(i,iN,g_doData.m_sData.m_listLamp.GetAt(i)->m_strName);
		iN++;
	}

	//选择到当前位置
	m_cList.SetItemState(m_iCur, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
	m_cList.EnsureVisible(m_iCur, FALSE);
}

void CLEDTypeCal::ReDraw()
{
	m_cDraw.DrawSpect(m_spData,m_drawData,"");
}

BOOL CLEDTypeCal::Test()
{
	int iTemp=g_SPEC.m_iMode;
	CCmdTarget::BeginWaitCursor();
	float fMax;
	BOOL bR;
	float fIntTime=10.0f;
	///先精确测试
	g_SPEC.m_iMode=1;
	bR=g_SPEC.SPEC_GetAutoTime(fIntTime,g_SPEC.m_iAutoLimitTime2,0.6f,fIntTime);
	if(!bR)
	{
		return FALSE;
	}
	bR=g_SPEC.SPEC_DoScan(fIntTime*1.0f,10,MY_TRIG_NORMAL,fMax,TRUE,m_spData.m_iDataType);
	if(!bR)
	{
		if(g_bEnglish)
			MessageBox("Sample fail!",NULL,MB_ICONSTOP);
		else
			MessageBox("采样失败!",NULL,MB_ICONSTOP);
		return FALSE;
	}
	CString strTemp;
	strTemp.Format("%.0f(%.0f%%)",fMax,fMax*100/(g_SPEC.m_nADW-1));
	m_cIP.SetWindowText(strTemp);
	m_cIP.SetFontUnderline(TRUE);
	if((fMax/(g_SPEC.m_nADW-1))<T_L||(fMax>=(g_SPEC.m_nADW-1)))
		m_cIP.SetTextColor(RGB(255,0,0));
	else
		m_cIP.SetTextColor(RGB(0,0,255));

	g_SPEC.SPEC_GetSpectData(FALSE,m_spData);
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
	int i,iN;
	iN=m_spData.m_fRelSpect.GetSize();
	for(i=0;i<iN;i++)
	{
		m_fRefS[i]=m_spData.m_fRelSpect.GetAt(i);
	}
	ReDraw();

	///再快速测试  不调节积分时间
	g_SPEC.m_iMode=0;
	bR=g_SPEC.SPEC_DoScan(fIntTime*1.0f,10,MY_TRIG_NORMAL,fMax,FALSE,m_spData.m_iDataType);
	if(!bR)
	{
		if(g_bEnglish)
			MessageBox("Sample fail!",NULL,MB_ICONSTOP);
		else
			MessageBox("采样失败!",NULL,MB_ICONSTOP);
		return FALSE;
	}
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

	g_SPEC.SPEC_GetSpectData(FALSE,m_spData);

	for(i=0;i<iN;i++)
	{
		m_fRefQ[i]=m_spData.m_fRelSpect.GetAt(i);
	}

	g_SPEC.m_iMode=iTemp;
	ReDraw();
/*	////保存
	FILE *fp;
	CString sTemp=g_strCurPath;
	if((fp=fopen(sTemp+"Data_SQ.dat","wt"))==0)
	{
	}
	else
	{
		for(int i=0;i<2001;i++)
			fprintf(fp,"%5d %10.2f %10.2f\n",i,m_fRefS[i],m_fRefQ[i]);
		fclose(fp);
	}
*/
	return TRUE;
}

void CLEDTypeCal::EnableShow(BOOL bStart)
{
	m_cCal.EnableWindow(!bStart);
	m_cStop.EnableWindow(bStart);
	m_cCancel.EnableWindow(!bStart);
	m_cAdd.EnableWindow(!bStart);
}

void CLEDTypeCal::OnButtonOpen() 
{
	// TODO: Add your control notification handler code here
	static char szFilter[]="Class files(*.sta)|*.sta||";
	CFileDialog dOpen(TRUE,".sta",m_strPathName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,NULL);
	if(dOpen.DoModal()==IDCANCEL)
		return;

	m_strPathName=dOpen.GetPathName();

	g_doData.m_sData.OPEN(m_strPathName);

	ReList();
	UpdateData(FALSE);
}

void CLEDTypeCal::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	static char szFilter[]="Class files(*.sta)|*.sta||";
	CFileDialog dSave(FALSE,".sta",m_strPathName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,NULL);
	if(dSave.DoModal()==IDCANCEL)
		return;
	CString sPathName;
	sPathName=dSave.GetPathName();

	g_doData.m_sData.SAVE(sPathName);	
}

void CLEDTypeCal::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION p = m_cList.GetFirstSelectedItemPosition();
	CString msg = _T("");
	while (p)
	{
		int nSelected = m_cList.GetNextSelectedItem(p);
		if (msg.IsEmpty())
			msg = _T("The following items are selected: ");

		CString str;
		str.Format(_T("%s"), m_cList.GetItemText(nSelected, 0));
		int iSele=atoi(str)-1;
		if(iSele>=0&&iSele<g_doData.m_sData.m_listLamp.GetSize())
		{
			m_strName=g_doData.m_sData.m_listLamp[iSele]->m_strName;
			UpdateData(FALSE);
//			fKFlux = g_doData.m_CalFluxK.m_listK[iSele]->m_fFluxK;
//			m_cUSE.SetWindowText(g_doData.m_CalFluxK.m_listK[iSele]->m_strName);
/*
			CString sTitle="\\def\\cal\\Flux2.cal";
			gPmsIo.m_fluxK.m_strName=g_doData.m_CalFluxK.m_listK[iSele]->m_strName;
			gPmsIo.m_fluxK.m_strDate=g_doData.m_CalFluxK.m_listK[iSele]->m_strDate;
			gPmsIo.m_fluxK.m_fStaFlux=g_doData.m_CalFluxK.m_listK[iSele]->m_fStaFlux;
			gPmsIo.m_fluxK.m_fFluxK=fKFlux;
			gPmsIo.m_fluxK.SAVE(g_strCurPath+sTitle);

			FILE *fp;
			sTitle="\\def\\Cal\\Flux.cal";
			if((fp=fopen(g_strCurPath+sTitle,"w++"))==NULL)
			{
				if(g_bEnglish)
					MessageBox("Can not open file!","Flux.cal",MB_ICONINFORMATION);
				else
					MessageBox("打开文件失败!","Flux.cal",MB_ICONINFORMATION);
				return;
			}
			else
			{
				fprintf(fp,"K: %f\n",fKFlux);
				CTime tNow;
				tNow=CTime::GetCurrentTime();
				CString sNow=tNow.Format("%Y:%m:%d %H:%M");
				fprintf(fp,sNow);
				fclose(fp);
			}
			g_doData.m_iFluxLampN = gPmsIo.m_fluxK.m_StaLamp.m_iN;
			for(int i=0;i<g_doData.m_iFluxLampN;i++)
			{
				g_doData.m_fFluxLampWL[i] = gPmsIo.m_fluxK.m_StaLamp.m_fWL[i];
				g_doData.m_fFluxLampPL[i] = gPmsIo.m_fluxK.m_StaLamp.m_fPL[i];
			}
			g_doData.FX_LAMP_Save(g_strCurPath+"def\\cal\\");

			m_cSetOK.EnableWindow(TRUE);
*/		}
		break;
	}
	
	*pResult = 0;
}

void CLEDTypeCal::OnSele() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	g_SPEC.m_iParType=m_iCur;
}
