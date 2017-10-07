// DlgLevel.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgLevel.h"

#include "DlgFastLevel.h"
#include "DlgSelePara.h"

#include "LevelLimit.h"
#include "Global_MySpec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLevel dialog
extern CString g_strListLevel;

CDlgLevel::CDlgLevel(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLevel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLevel)
	//}}AFX_DATA_INIT

	CString strSection   = g_strCurPath;
	CString strPathName  = "PathName";
	m_strPathName=AfxGetApp()->GetProfileString(strSection,strPathName,g_strCurPath+"Class\\LED_LEVEL_1.sta");
}


void CDlgLevel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLevel)
	DDX_Control(pDX, IDC_STATIC_S1, m_cS1);
	DDX_Control(pDX, IDOK, m_cOK);
	DDX_Control(pDX, IDC_EDIT_D, m_cD);
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_Grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLevel, CDialog)
	//{{AFX_MSG_MAP(CDlgLevel)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MOD, OnButtonMod)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_EN_CHANGE(IDC_EDIT_D, OnChangeEditD)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BEGIN_EVENTSINK_MAP(CDlgLevel, CDialog)
    //{{AFX_EVENTSINK_MAP(CDlgLevel)
	ON_EVENT(CDlgLevel, IDC_MSFLEXGRID1, -601 /* DblClick */, OnDblClickMsflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgLevel message handlers

BOOL CDlgLevel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iX=0;
	m_iY=0;

	if(m_strPathName!=g_strListLevel)
		g_strListLevel=m_strPathName;
	m_levelLimit.Open(m_strPathName);

	SetList();
	m_cS1.SetWindowText("");
	ReShow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLevel::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}

void CDlgLevel::OnCancel() 
{
	// TODO: Add extra cleanup here
	m_levelLimit.Save(g_strCurPath+"def1.TEMP");
	
	CString strSection   = g_strCurPath;
	CString strPathName  = "PathName";

	AfxGetApp()->WriteProfileString(strSection,strPathName,m_strPathName);
	g_strListLevel=m_strPathName;

	CDialog::OnCancel();
}

void CDlgLevel::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	BOOL bR;
	bR=m_levelLimit.AddLimitPara();
	if(!bR)
		return;
	ReShow();
}

void CDlgLevel::OnButtonMod() 
{
	// TODO: Add your control notification handler code here
	BOOL bR;
	bR=m_levelLimit.EditLimitPara();
	if(!bR)
		return;

	ReShow();
}

void CDlgLevel::OnButtonDel() 
{
	// TODO: Add your control notification handler code here
	BOOL bR;
	bR=m_levelLimit.DelLimitPara();
	if(!bR)
		return;
	ReShow();
}

void CDlgLevel::OnOpen() 
{
	// TODO: Add your control notification handler code here
	static char szFilter[]="Class files(*.sta)|*.sta||";
	CFileDialog dOpen(TRUE,".sta",m_strPathName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,NULL);
	if(dOpen.DoModal()==IDCANCEL)
		return;

	m_strPathName=dOpen.GetPathName();

	m_levelLimit.Open(m_strPathName);
	g_strListLevel=m_strPathName;

	ReShow();
	UpdateData(FALSE);
}

void CDlgLevel::ReShow()
{
	m_Grid.SetRow(0);
	m_Grid.SetCol(0);
	if(g_bEnglish)
		m_Grid.SetText("Level");
	else
		m_Grid.SetText("级别");
	SetList();
	ListData();

	SetPos();
}

void CDlgLevel::SetList()
{
	for(int i=0;i<21;i++)
	{
		for(int j=1;j<37;j++)
		{
			m_Grid.SetRow(i);
			m_Grid.SetCol(j);
			m_Grid.SetText("");
		}
	}
	CString strTemp;
	int iN;
	iN=m_levelLimit.m_arraLevelLimit.GetSize();
	int iCol;
	for(i=0;i<iN;i++)  //参数个数
	{
		iCol=i*2+1;  //该参数对应的列数
		m_Grid.SetRow(0);      //选择第一行
		m_Grid.SetCol(iCol);   //选择列

		strTemp=m_levelLimit.m_arraLevelLimit[i]->GetTypeName();
		m_Grid.SetText(strTemp);

		m_Grid.SetRow(1);      //选择第二行
		m_Grid.SetCol(iCol);   //选择列
		m_Grid.SetText("  MIN");

		m_Grid.SetRow(1);      //选择第二行
		m_Grid.SetCol(iCol+1); //选择列
		m_Grid.SetText("  MAX");
	}
}

void CDlgLevel::ListData()
{
	int i,j,iN,iCol,iRow;
	iN=m_levelLimit.m_arraLevelLimit.GetSize();
	CString strTemp;
	for(i=0;i<iN;i++)  //参数个数
	{
		iCol=i*2+1;  //该参数对应的列数
		iRow=m_levelLimit.m_arraLevelLimit[i]->m_iN;  //该参数的分级数
		for(j=0;j<iRow;j++)
		{
			int iLevel;
			float fTemp;
			m_Grid.SetRow(j+2);

			m_Grid.SetCol(0);
			iLevel=j;
			if(g_bEnglish)
				strTemp.Format("%4d",iLevel);
			else
				strTemp.Format("%4d级",iLevel);
			m_Grid.SetText(strTemp);

			m_Grid.SetCol(iCol);
			fTemp=m_levelLimit.m_arraLevelLimit[i]->m_fLevel1[j];
			GetData(i,fTemp,strTemp);
			m_Grid.SetText(strTemp);

			m_Grid.SetCol(iCol+1);
			fTemp=m_levelLimit.m_arraLevelLimit[i]->m_fLevel2[j];
			GetData(i,fTemp,strTemp);
			m_Grid.SetText(strTemp);
		}
	}
}

void CDlgLevel::OnChangeEditD() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString strTemp;
	m_cD.GetWindowText(strTemp);

	float fTemp;
	fTemp=(float)atof(strTemp);

	if(m_iType==ED_MOD)
	{
		strTemp.Format("%9.2f",fTemp);
		GetData(m_iX,fTemp,strTemp);

		int iCol=m_iX*2+1+m_iSele12;
		int iRow=m_iY+2;

		if(m_iSele12%2==0)
			m_levelLimit.m_arraLevelLimit[m_iX]->m_fLevel1[m_iY]=fTemp;
		else
			m_levelLimit.m_arraLevelLimit[m_iX]->m_fLevel2[m_iY]=fTemp;

		m_Grid.SetRow(iRow);
		m_Grid.SetCol(iCol);

		m_Grid.SetText(strTemp);

		m_Grid.SetRow(iRow);
		m_Grid.SetCol(iCol-1);

		m_Grid.SetColSel(iCol);
		m_Grid.SetRowSel(iRow);
		return;
	}
}

void CDlgLevel::OnDblClickMsflexgrid1() 
{
	// TODO: Add your control notification handler code here
	int iRow,iCol;

	iRow=m_Grid.GetRow();
	iCol=m_Grid.GetCol();

	int ix,iy;
	ix=(iCol-1)/2;
	iy=iRow-2;

	float fD;
	CString strTemp;
	m_iType=ED_NONE;
	int iN,iM;
	iM=m_levelLimit.m_arraLevelLimit.GetSize();
	if(ix>=0&&ix<iM)
	{
		iN=m_levelLimit.m_arraLevelLimit[ix]->m_iN;
		if(iy>=0&&iy<iN)
		{
			m_iSele12=(iCol-1)%2;
			if((iCol-1)%2==0)
				fD=m_levelLimit.m_arraLevelLimit[ix]->m_fLevel1[iy];
			else
				fD=m_levelLimit.m_arraLevelLimit[ix]->m_fLevel2[iy];
			
			GetData(ix,fD,strTemp);
			strTemp.Format("%.f",fD);
			m_cD.SetWindowText(strTemp);

			m_cD.SetFocus();
			m_cD.SetSel(0,100);

			m_Grid.SetCol(iCol-1);
			m_Grid.SetRow(iRow);

			m_Grid.SetColSel(iCol);
			m_Grid.SetRowSel(iRow);

			m_iX=ix;
			m_iY=iy;
			m_iType=ED_MOD;
		}
	}
}

void CDlgLevel::SetPos()
{
	CString strRe,strTemp;
	int iN;
	iN=m_levelLimit.m_arraLevelLimit.GetSize();
	if(iN<=0)
	{
		strRe="";
		m_cS1.SetWindowText(strRe);
		return;
	}
	if(g_bEnglish)
		strRe=" Example:  Num";
	else
		strRe=" 示例说明: 级数";

	for(int i=0;i<iN;i++)  //参数个数
	{
		strTemp.Format("%d",1);
		strRe=strRe+strTemp;
	}
	if(g_bEnglish)
		strRe=strRe+"  express: ";
	else
		strRe=strRe+"  表示: ";
	for(i=0;i<iN;i++)     //参数个数
	{
		strTemp=m_levelLimit.m_arraLevelLimit[i]->GetTypeName();
		strRe=strRe+strTemp;
		if(g_bEnglish)
			strTemp.Format(" Level%d; ",1);
		else
			strTemp.Format(" 第%d级; ",1);
		strRe=strRe+strTemp;
	}
	if(g_bEnglish)
		strRe=strRe+" * is out.";
	else
		strRe=strRe+"如有*则表明该参数级别未分出!";
	m_cS1.SetWindowText(strRe);
}

void CDlgLevel::GetData(int iN,float fTemp,CString &sTemp)
{
	int iType;
	iType=m_levelLimit.m_arraLevelLimit[iN]->m_iDataType;
	sTemp=g_SPEC.sFormat(fTemp,4);
	return;
}

void CDlgLevel::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	static char szFilter[]="Class files(*.sta)|*.sta||";
	CFileDialog dSave(FALSE,".sta",m_strPathName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,NULL);
	if(dSave.DoModal()==IDCANCEL)
		return;
	CString sPathName;
	sPathName=dSave.GetPathName();

	m_levelLimit.Save(sPathName);	
}
