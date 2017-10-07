// SetPrint.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "SetPrint.h"
#include "SetPrintForm.h"
#include "Functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetPrint dialog


CSetPrint::CSetPrint(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CSetPrint::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetPrint)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSetPrint::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetPrint)
	DDX_Control(pDX, IDC_selectItem, m_selectItem);
	DDX_Control(pDX, IDC_printlist, m_printlist);
	DDX_Control(pDX, IDC_printMode, m_printMode);
	DDX_Control(pDX, IDC_ItemCode, m_itemCode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetPrint, CResizingDialog)
	//{{AFX_MSG_MAP(CSetPrint)
	ON_BN_CLICKED(IDC_printForm, OnprintForm)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_Save, OnSave)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_selectItem, OnSelchangeselectItem)
	ON_CBN_SELCHANGE(IDC_ItemCode, OnSelchangeItemCode)
	ON_BN_CLICKED(IDC_clearSet, OnclearSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetPrint message handlers
extern SystemSet systemset;
extern int columns[3];
extern BinArray binArray;

extern PrintItem printItem[10];
PrintItem tempprintItem[10];
extern CArray<CString,CString> getbincode[30];
extern int CAT[3];
int tempCAT[3] = {0, 0, 0};

BOOL CSetPrint::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitSelectItem();

	m_itemCode.InsertString(0, "CAT");
	m_itemCode.InsertString(1, "HUE");
	m_itemCode.InsertString(2, "REF");

	m_printMode.InsertString(0, "扫描模式");
	m_printMode.InsertString(1, "扫描比对模式");
	m_printMode.InsertString(2, "自动比对模式");
	m_printMode.SetCurSel(2);

	m_printlist.Init();
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 20;
	strcpy(lf.lfFaceName, "Verdana");
	font.CreateFontIndirect(&lf);
	m_printlist.SetFont(&font, TRUE);
	m_printlist.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	CString str;
	m_printlist.InsertColumn(0, "", LVCFMT_CENTER, 50);
	m_printlist.InsertColumn(1, "No Item", LVCFMT_CENTER, 80);
	m_printlist.InsertColumn(2, "No Item", LVCFMT_CENTER, 80);
	m_printlist.InsertColumn(3, "No Item", LVCFMT_CENTER, 80);
	m_printlist.InsertColumn(4, "编码一", LVCFMT_CENTER, 80);
	m_printlist.InsertColumn(5, "编码二", LVCFMT_CENTER, 80);
	for(int i=0; i<systemset.intMachineType-1; i++)
	{
		str.Format("%d", i+1);
		m_printlist.InsertItem(i, str);
	}

	InitPrintSet();

	m_itemCode.SetCurSel(0);
	m_selectItem.SetCurSel(CAT[0]);
	InitPrintList();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CSetPrint::InitSelectItem()
{
	int num = 0;
	CString str_item;
	int totalcol = 0;
	totalcol = columns[0] + columns[1] + columns[2];

	m_selectItem.InsertString(0, "");

	for(int i=0; i<totalcol; i+=2)
	{
		num++;
		m_selectItem.InsertString(num, binArray.strBinArray[0][i]);

		sscanf(binArray.strBinArray[0][i], "%*[^-]-%[^(]", str_item);
		if(0 == strcmp(str_item, "XYZ"))
		{
			i += 6;
		}	
	}

	return true;
}

bool CSetPrint::InitPrintList()
{
	for(int i=0; i<3; i++)
	{
		if(CAT[i] != 0)
		{
			for(int j=0; j<systemset.intMachineType-1; j++)
			{
				m_printlist.SetItemText(j, i+1, getbincode[CAT[i]-1][j]);
			}
		}
	}

	return true;
}

bool CSetPrint::InitPrintSet()
{
	for(int i=0; i<10; i++)
	{
		tempprintItem[i].ItemCheck = printItem[i].ItemCheck;
		tempprintItem[i].name = printItem[i].name;
		tempprintItem[i].namecode = printItem[i].namecode;
		tempprintItem[i].data = printItem[i].data;
		tempprintItem[i].datacode = printItem[i].datacode;
		tempprintItem[i].pos_X = printItem[i].pos_X;
		tempprintItem[i].pos_Y = printItem[i].pos_Y;
	}

	for(i=0; i<3; i++)
	{
		tempCAT[i] = CAT[i];
	}

	return true;
}

void CSetPrint::OnSave() 
{
	// TODO: Add your control notification handler code here
	int i = 0;
	for(i=0; i<10; i++)
	{
		printItem[i].ItemCheck = tempprintItem[i].ItemCheck;
		printItem[i].name = tempprintItem[i].name;
		printItem[i].namecode = tempprintItem[i].namecode;
		printItem[i].data = tempprintItem[i].data;
		printItem[i].datacode = tempprintItem[i].datacode;
		printItem[i].pos_X = tempprintItem[i].pos_X;
		printItem[i].pos_Y = tempprintItem[i].pos_Y;
	}

	for(i=0; i<3; i++)
	{
		CAT[i] = tempCAT[i];
	}

	CString path;
	path = "System\\PrintSet.print";

	CStdioFile m_file;
	if(m_file.Open((LPCTSTR)path, CFile::modeReadWrite))
	{
		WritePrintSetFile(&m_file);
		m_file.Close();
	}
	else
	{
		MessageBox("打印设置文件保存失败!");
	}
	
}

void CSetPrint::OnCancel() 
{
	// TODO: Add extra cleanup here
	CString str = ",,,,";
	char str2[20];
	CString str3;
	strcpy(str2, "");
	sscanf(str, "%[^,]", str2);
	str3 = str2;
	MessageBox(str3);

//	CResizingDialog::OnClose();
}


void CSetPrint::OnprintForm() 
{
	// TODO: Add your control notification handler code here
	CSetPrintForm m_formdlg;
	m_formdlg.DoModal();
}

BOOL CSetPrint::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
//	return CResizingDialog::OnEraseBkgnd(pDC);
	return CResizingDialog::DrawBK(pDC, IDB_SettingBK, 1);
}

void CSetPrint::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
//	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(20, 50, "列印代号");
	dc.TextOut(95, 90, "CAT");
	dc.TextOut(175, 90, "HUE");
	dc.TextOut(255, 90, "REF");
	dc.TextOut(520, 220, "条码列印模式");

	// Do not call CResizingDialog::OnPaint() for painting messages
}

void CSetPrint::OnSelchangeselectItem() 
{
	// TODO: Add your control notification handler code here
	int num = m_selectItem.GetCurSel()-1;
	int num2 = m_itemCode.GetCurSel();
	
	if(num >= 0)
	{
		int size = getbincode[num].GetSize();
		
		tempCAT[num2] = num+1;
		for(int i=0; i<systemset.intMachineType-1; i++)
		{
			m_printlist.SetItemText(i, num2+1, getbincode[num][i]);
		}	
	}
	else
	{
		tempCAT[num2] = 0;
		for(int i=0; i<systemset.intMachineType-1; i++)
		{
			m_printlist.SetItemText(i, num2+1, "");
		}
	}
}

void CSetPrint::OnSelchangeItemCode() 
{
	// TODO: Add your control notification handler code here
	int num = m_itemCode.GetCurSel();
	m_selectItem.SetCurSel(CAT[num]);
	OnSelchangeselectItem();
}

void CSetPrint::OnclearSet() 
{
	// TODO: Add your control notification handler code here
}
