// DlgWhite.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgWhite.h"
#include "DlgName.h"
#include "Global_MySpec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWhite dialog
extern CString g_strListWhite;

CDlgWhite::CDlgWhite(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWhite::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWhite)
	m_fX = 0.32f;
	m_fY = 0.33f;
	//}}AFX_DATA_INIT
	m_iSeleName=0;
	m_iSeleXY=0;
	m_iSele12=0;

	CString strSection   = "White";
	CString strX         = "X";
	CString strY         = "Y";

	CString strTemp;
	strTemp=AfxGetApp()->GetProfileString(strSection,strX,"0.31");
	m_fX=(float)atof(strTemp);
	strTemp=AfxGetApp()->GetProfileString(strSection,strY,"0.31");
	m_fY=(float)atof(strTemp);

	        strSection   = g_strCurPath;
	CString strPathName  = "PathName_WCL";
	m_strPathName=AfxGetApp()->GetProfileString(strSection,strPathName,g_strCurPath+"Class\\White_ANSI.WCL");
}


void CDlgWhite::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWhite)
	DDX_Control(pDX, IDC_EV, m_cEV);
	DDX_Control(pDX, IDC_EDIT_NAME, m_cName);
	DDX_Control(pDX, IDC_EDIT_D, m_cD);
	DDX_Control(pDX, IDC_DRAW, m_cDraw);
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_cGridName);
	DDX_Control(pDX, IDC_MSFLEXGRID2, m_cGridLevel);
	DDX_Text(pDX, IDC_EDIT_X, m_fX);
	DDX_Text(pDX, IDC_EDIT_Y, m_fY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWhite, CDialog)
	//{{AFX_MSG_MAP(CDlgWhite)
	ON_BN_CLICKED(IDC_W_SAVE, OnWSave)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_ADD2, OnButtonAdd2)
	ON_BN_CLICKED(IDC_BUTTON_DEL2, OnButtonDel2)
	ON_EN_CHANGE(IDC_EDIT_NAME, OnChangeEditName)
	ON_EN_CHANGE(IDC_EDIT_D, OnChangeEditD)
	ON_BN_CLICKED(IDC_BUTTON_CHECK, OnButtonCheck)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_W_OPEN, OnWOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWhite message handlers

void CDlgWhite::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CDlgWhite::OnCancel() 
{
	// TODO: Add extra cleanup here
	m_xyZone.WZ_Save(g_strCurPath+"def2.TEMP");
	
	CString strSection   = "White";
	CString strX         = "X";
	CString strY         = "Y";

	CString strTemp;

	strTemp.Format("%f",m_fX);
	AfxGetApp()->WriteProfileString(strSection,strX,strTemp);
	strTemp.Format("%f",m_fY);
	AfxGetApp()->WriteProfileString(strSection,strY,strTemp);

	        strSection   = g_strCurPath;
	CString strPathName  = "PathName_WCL";

	AfxGetApp()->WriteProfileString(strSection,strPathName,m_strPathName);
	g_strListWhite=m_strPathName;

	CDialog::OnCancel();
}


void CDlgWhite::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	CDlgName dlg;
	if(dlg.DoModal()==IDCANCEL)
		return;

	CZOoneXY *temp=new CZOoneXY();
	temp->m_strName=dlg.m_strName;
	m_xyZone.m_arraXY.Add(temp);
	ReGridName();
	ReGridXY();
	ReDraw();
}

void CDlgWhite::OnButtonDel() 
{
	// TODO: Add your control notification handler code here
	int iN=m_xyZone.m_arraXY.GetSize();
	if(m_iSeleName<0||m_iSeleName>=iN)
		return;
	int iR;
	if(g_bEnglish)
		iR=MessageBox("Delete "+m_xyZone.m_arraXY[m_iSeleName]->m_strName+"?",NULL,MB_ICONINFORMATION|MB_OKCANCEL);
	else
		iR=MessageBox("确定删除 "+m_xyZone.m_arraXY[m_iSeleName]->m_strName+"?",NULL,MB_ICONINFORMATION|MB_OKCANCEL);
	if(iR==IDCANCEL)
		return;

	m_xyZone.m_arraXY.RemoveAt(m_iSeleName);

	ReGridName();
	ReGridXY();
	ReDraw();
}

BOOL CDlgWhite::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	if(m_strPathName!=g_strListWhite)
		g_strListWhite=m_strPathName;
	m_xyZone.WZ_Load(g_strListWhite);

	ReGridName();

	ReGridXY();
	ReDraw();

	m_cEV.SetLink(TRUE)
		.SetTextColor(RGB(0,0,0))
		.SetFontUnderline(TRUE)
		.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));		

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgWhite::ReGridName()
{
	m_cGridName.Clear();

	m_cGridName.SetCol(0);

	m_cGridName.SetRow(0);
	m_cGridName.SetText("SN");

	m_cGridName.SetRow(1);
	if(g_bEnglish)
		m_cGridName.SetText("CLASS");
	else
		m_cGridName.SetText("分级名");

	int iN=m_xyZone.m_arraXY.GetSize();
	for(int i=0;i<iN;i++)
	{
		CString strTemp;

		m_cGridName.SetCol(0);
		m_cGridName.SetRow(i+1);
		strTemp.Format("%4d",i+1);
		m_cGridName.SetText(strTemp);
	
		m_cGridName.SetCol(1);
		m_cGridName.SetRow(i+1);
		strTemp=m_xyZone.m_arraXY[i]->m_strName;
		m_cGridName.SetText(strTemp);
	}
}

void CDlgWhite::ReGridXY()
{
	int iSele=m_iSeleName;

	m_cGridLevel.Clear();

	m_cGridLevel.SetCol(0);
	m_cGridLevel.SetRow(0);
	m_cGridLevel.SetText("SN.");

	m_cGridLevel.SetCol(1);
	m_cGridLevel.SetRow(0);
	m_cGridLevel.SetText("x");

	m_cGridLevel.SetCol(2);
	m_cGridLevel.SetRow(0);
	m_cGridLevel.SetText("y");

	int iT=m_xyZone.m_arraXY.GetSize();
	if(iSele<0||iSele>=iT)
		return;

	int iN,i;

	iN=m_xyZone.m_arraXY[iSele]->m_fx.GetSize();
	for(i=0;i<iN;i++)
	{
		CString strTemp;

		m_cGridLevel.SetCol(0);
		m_cGridLevel.SetRow(1+i);
		strTemp.Format("%d",i+1);
		m_cGridLevel.SetText(strTemp);

		m_cGridLevel.SetCol(1);
		m_cGridLevel.SetRow(1+i);
		strTemp.Format("%.4f",m_xyZone.m_arraXY[iSele]->m_fx[i]);
		m_cGridLevel.SetText(strTemp);

		m_cGridLevel.SetCol(2);
		m_cGridLevel.SetRow(1+i);
		strTemp.Format("%.4f",m_xyZone.m_arraXY[iSele]->m_fy[i]);
		m_cGridLevel.SetText(strTemp);
	}
}

BEGIN_EVENTSINK_MAP(CDlgWhite, CDialog)
    //{{AFX_EVENTSINK_MAP(CDlgWhite)
	ON_EVENT(CDlgWhite, IDC_MSFLEXGRID1, -600 /* Click */, OnClickMsflexgrid1, VTS_NONE)
	ON_EVENT(CDlgWhite, IDC_MSFLEXGRID2, -600 /* Click */, OnClickMsflexgrid2, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDlgWhite::OnClickMsflexgrid1() 
{
	// TODO: Add your control notification handler code here
	m_iSeleName=m_cGridName.GetRow()-1;
	ReGridXY();

	m_cGridName.SetCol(0);
	m_cGridName.SetRow(m_iSeleName+1);

	m_cGridName.SetColSel(1);
	m_cGridName.SetRowSel(m_iSeleName+1);

	int iN=m_xyZone.m_arraXY.GetSize();
	if(m_iSeleName<0||m_iSeleName>=iN)
		return;

	CString strTemp;
	strTemp=m_xyZone.m_arraXY[m_iSeleName]->m_strName;
		
	m_cName.SetFocus();
	m_cName.SetSel(0,100);

	ReDraw();
}

void CDlgWhite::OnButtonAdd2() 
{
	// TODO: Add your control notification handler code here
	int iN=m_xyZone.m_arraXY.GetSize();
	if(m_iSeleName<0||m_iSeleName>=iN)
		return;

	m_xyZone.m_arraXY[m_iSeleName]->m_fx.Add(0.0);
	m_xyZone.m_arraXY[m_iSeleName]->m_fy.Add(0.0);
	ReGridXY();	
	ReDraw();
}

void CDlgWhite::OnButtonDel2() 
{
	// TODO: Add your control notification handler code here
	int iN=m_xyZone.m_arraXY.GetSize();
	if(m_iSeleName<0||m_iSeleName>=iN)
		return;
	
	iN=m_xyZone.m_arraXY[m_iSeleName]->m_fx.GetSize();
	if(m_iSeleXY<0||m_iSeleXY>=iN)
		return;

	int iR;
	if(g_bEnglish)
		iR=MessageBox("Delete?",NULL,MB_ICONINFORMATION|MB_OKCANCEL);
	else
		iR=MessageBox("确定删除?",NULL,MB_ICONINFORMATION|MB_OKCANCEL);
	if(iR==IDCANCEL)
		return;

	m_xyZone.m_arraXY[m_iSeleName]->m_fx.RemoveAt(m_iSeleXY);
	m_xyZone.m_arraXY[m_iSeleName]->m_fy.RemoveAt(m_iSeleXY);

	ReGridXY();
	ReDraw();
}

void CDlgWhite::OnClickMsflexgrid2() 
{
	// TODO: Add your control notification handler code here
	int iN=m_xyZone.m_arraXY.GetSize();
	if(m_iSeleName<0||m_iSeleName>=iN)
		return;

	m_iSeleXY=m_cGridLevel.GetRow()-1;

	int iRow,iCol;

	iRow=m_cGridLevel.GetRow();
	iCol=m_cGridLevel.GetCol();

	int ix,iy;
	ix=(iCol-1)/2;
	iy=(iRow-1);

	float fD;
	CString strTemp;

	//m_iType=ED_NONE;

	if(ix>=0&&ix<2)
	{
		iN=m_xyZone.m_arraXY[m_iSeleName]->m_fx.GetSize();
		if(iy>=0&&iy<iN)
		{
			m_iSele12=(iCol-1)%2;
			if(m_iSele12==0)
				fD=m_xyZone.m_arraXY[m_iSeleName]->m_fx[iy];
			else
				fD=m_xyZone.m_arraXY[m_iSeleName]->m_fy[iy];
			
			m_cD.SetFocus();
			m_cD.SetSel(0,100);

			m_cGridLevel.SetCol(iCol-1);
			m_cGridLevel.SetRow(iRow);

			m_cGridLevel.SetColSel(iCol);
			m_cGridLevel.SetRowSel(iRow);

			m_iX=ix;
			m_iY=iy;
		}
	}
}

void CDlgWhite::OnChangeEditName() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	int iN=m_xyZone.m_arraXY.GetSize();
	if(m_iSeleName<0||m_iSeleName>=iN)
		return;
	CString strTemp;
	m_cName.GetWindowText(strTemp);
	m_xyZone.m_arraXY[m_iSeleName]->m_strName=strTemp;
	
	m_cGridName.SetCol(1);
	m_cGridName.SetRow(m_iSeleName+1);
	m_cGridName.SetText(strTemp);

	m_cGridName.SetCol(0);
	m_cGridName.SetRow(m_iSeleName+1);

	m_cGridName.SetColSel(1);
	m_cGridName.SetRowSel(m_iSeleName+1);
}

void CDlgWhite::OnChangeEditD() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	int iN=m_xyZone.m_arraXY.GetSize();
	if(m_iSeleName<0||m_iSeleName>=iN)
		return;
	CString strTemp;
	m_cD.GetWindowText(strTemp);

	float fD;
	fD=(float)atof(strTemp);
	if(m_iX>=0&&m_iX<2)
	{
		iN=m_xyZone.m_arraXY[m_iSeleName]->m_fx.GetSize();
		if(m_iY>=0&&m_iY<iN)
		{
			if(m_iSele12==0)
				m_xyZone.m_arraXY[m_iSeleName]->m_fx[m_iY]=fD;
			else
				m_xyZone.m_arraXY[m_iSeleName]->m_fy[m_iY]=fD;

			int iCol=1+m_iSele12;
			int iRow=m_iY+1;

			m_cGridLevel.SetRow(iRow);
			m_cGridLevel.SetCol(iCol);

			strTemp.Format("%.4f",fD);
			m_cGridLevel.SetText(strTemp);

			m_cGridLevel.SetCol(iCol-1);
			m_cGridLevel.SetRow(iRow);

			m_cGridLevel.SetColSel(iCol);
			m_cGridLevel.SetRowSel(iRow);

			ReDraw();
		}
	}
}

void CDlgWhite::ReDraw()
{
	UpdateData(TRUE);
	
	m_xyZone.m_fX=m_fX;
	m_xyZone.m_fY=m_fY;

	m_cDraw.DrawZONE(m_xyZone,m_iSeleName);
}

void CDlgWhite::OnButtonCheck() 
{
	// TODO: Add your control notification handler code here
	ReDraw();
}

void CDlgWhite::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect Rect1,Rect2;
	GetClientRect(&Rect1);
	ClientToScreen(&Rect1);
	m_cDraw.GetClientRect(&Rect2);
	m_cDraw.ClientToScreen(&Rect2);
	if(((point.y+Rect1.top)>=Rect2.top)&&((point.y+Rect1.top)<=Rect2.bottom)&&((point.x+Rect1.left)>=Rect2.left)&&((point.x+Rect1.left)<=Rect2.right))
	{
		m_xyZone.m_xyPoint.x=point.x-(Rect2.left-Rect1.left);
		m_xyZone.m_xyPoint.y=point.y-(Rect2.top-Rect1.top);

		m_xyZone.m_bMouse=TRUE;
		ReDraw();
		m_xyZone.m_bMouse=FALSE;

		m_fX=m_xyZone.m_fX;
		m_fY=m_xyZone.m_fY;
		UpdateData(FALSE);
	}
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgWhite::OnWOpen() 
{
	// TODO: Add your control notification handler code here
	static char szFilter[]="Class files(*.WCL)|*.WCL||";
	CFileDialog dOpen(TRUE,".WCL",m_strPathName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,NULL);
	if(dOpen.DoModal()==IDCANCEL)
		return;

	m_strPathName=dOpen.GetPathName();
	m_xyZone.WZ_Load(m_strPathName);

	ReGridName();

	ReGridXY();
	ReDraw();

	g_strListWhite=m_strPathName;
}

void CDlgWhite::OnWSave() 
{
	// TODO: Add your control notification handler code here
	static char szFilter[]="Class files(*.WCL)|*.WCL||";
	CFileDialog dSave(FALSE,".WCL",m_strPathName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,NULL);
	if(dSave.DoModal()==IDCANCEL)
		return;

	m_strPathName=dSave.GetPathName();
	m_xyZone.WZ_Save(m_strPathName);
	g_strListWhite=m_strPathName;
}
