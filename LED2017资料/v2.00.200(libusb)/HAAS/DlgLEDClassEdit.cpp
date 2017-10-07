// DlgLEDClassEdit.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgLEDClassEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLEDClassEdit dialog

extern BOOL g_bEnglish;
extern CString g_strCurPath;
extern CString g_strListNewLevel;

CDlgLEDClassEdit::CDlgLEDClassEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLEDClassEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLEDClassEdit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_strPathName = g_strCurPath + "Class\\*.NCL";
	m_bMod = FALSE;
}


void CDlgLEDClassEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLEDClassEdit)
	DDX_Control(pDX, IDC_LIST, m_cList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLEDClassEdit, CDialog)
	//{{AFX_MSG_MAP(CDlgLEDClassEdit)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_MOD, OnButtonMod)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, OnButtonExport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLEDClassEdit message handlers

void CDlgLEDClassEdit::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

void CDlgLEDClassEdit::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	int iR;
	if(m_classData.GetClassNum() > 0)
	{
		if(g_bEnglish)
			iR = MessageBox("Are you sure?",NULL,MB_ICONINFORMATION|MB_OKCANCEL);
		else
			iR = MessageBox("确定新建文件?",NULL,MB_ICONINFORMATION|MB_OKCANCEL);
		if(iR == IDCANCEL)
			return;
	}

	m_classData.EditDataPara();

	m_classData.ListData(m_cList);

	m_bMod = TRUE;
}

void CDlgLEDClassEdit::OnButtonOpen() 
{
	// TODO: Add your control notification handler code here
	static char szFilter[]="Class files(*.NCL)|*.NCL||";
	CFileDialog dOpen(TRUE,".NCL",m_strPathName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,NULL);
	if(dOpen.DoModal()==IDCANCEL)
	{
		m_strPathName = g_strCurPath+"Class\\new.ncl";
		g_strListNewLevel= m_strPathName;
		return;
	}
	
	m_strPathName = dOpen.GetPathName();
	m_classData.NC_Load(m_strPathName);	
	g_strListNewLevel= m_strPathName;


	m_classData.ListData(m_cList);

	m_bMod = FALSE;
}

void CDlgLEDClassEdit::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	static char szFilter[]="Class files(*.NCL)|*.NCL||";
	CFileDialog dOpen(FALSE,m_strPathName,m_strPathName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,NULL);
	if(dOpen.DoModal()==IDCANCEL)
		return;
	
	m_strPathName = dOpen.GetPathName();
	m_classData.NC_Save(m_strPathName);	

	m_bMod = FALSE;
}

void CDlgLEDClassEdit::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	m_classData.Add_Class();
	m_classData.ListData(m_cList);

	m_bMod = TRUE;
}

void CDlgLEDClassEdit::OnButtonDel() 
{
	// TODO: Add your control notification handler code here
	int iR;
	if(g_bEnglish)
		iR = MessageBox("Are you sure?",NULL,MB_ICONINFORMATION|MB_OKCANCEL);
	else
		iR = MessageBox("确定删除打勾的分类?",NULL,MB_ICONINFORMATION|MB_OKCANCEL);
	if(iR == IDCANCEL)
		return;

	int iN = m_classData.GetClassNum();
	for(int i = 0; i < iN; i ++)
	{
		if(m_cList.GetCheck(iN - 1 - i) == TRUE)
		{
			m_classData.Del_Class(iN - 1 - i);
			m_bMod = TRUE;
		}
	}

	m_classData.ListData(m_cList);
}

void CDlgLEDClassEdit::OnCancel() 
{
	// TODO: Add extra cleanup here
	int iR;
	if(m_bMod)
	{
		if(g_bEnglish)
			iR = MessageBox("Are you sure?",NULL,MB_ICONINFORMATION|MB_OKCANCEL);
		else
			iR = MessageBox("确定退出?",NULL,MB_ICONINFORMATION|MB_OKCANCEL);
		if(iR == IDCANCEL)
			return;
	}
	
	CDialog::OnCancel();
}

BOOL CDlgLEDClassEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_cList.SetExtendedStyle(m_cList.GetExtendedStyle()  | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES
		| LVS_EX_HEADERDRAGDROP | LVS_EX_CHECKBOXES);

	m_classData.NC_Load(g_strListNewLevel);	
	m_strPathName=g_strListNewLevel;

	m_classData.ListData(m_cList);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLEDClassEdit::OnButtonMod() 
{
	// TODO: Add your control notification handler code here
	int iR;
	if(g_bEnglish)
		iR = MessageBox("Are you sure?",NULL,MB_ICONINFORMATION|MB_OKCANCEL);
	else
		iR = MessageBox("对打勾的分类进行修改?",NULL,MB_ICONINFORMATION|MB_OKCANCEL);
	if(iR == IDCANCEL)
		return;

	int iN = m_classData.GetClassNum();
	for(int i = 0; i < iN; i ++)
	{
		if(m_cList.GetCheck(i) == TRUE)
		{
			m_classData.Mod_Class(i);
			m_bMod = TRUE;
		}
	}
	
	m_classData.ListData(m_cList);	
}

void CDlgLEDClassEdit::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_iSele = pNMListView->iItem;	
	*pResult = 0;
}

void CDlgLEDClassEdit::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	int iSaveSele = m_iSele;

	m_classData.Mod_Class(m_iSele);
	m_classData.ListData(m_cList);	

	m_cList.SetItemState(iSaveSele, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
	m_cList.EnsureVisible(iSaveSele, FALSE);

	*pResult = 0;
}

void CDlgLEDClassEdit::OnButtonExport() 
{
	// TODO: Add your control notification handler code here
	// 选择导出路径
	static char BASED_CODE szFilter[]="Excel Files(*.CSV)|*.CSV||";
	CFileDialog mOpenFile(FALSE, ".CSV",NULL,  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	if(mOpenFile.DoModal()==IDCANCEL) 
		return;
	CString strPathName=mOpenFile.GetPathName();	
	
	// 导出文件
	BOOL bR;
	bR = m_classData.Export_CSV(strPathName);
	if(!bR)
	{
		if(g_bEnglish)
			AfxMessageBox("Export fail!",MB_ICONSTOP);
		else
			AfxMessageBox("导出文件失败!",MB_ICONSTOP);
		return;
	}						
}
