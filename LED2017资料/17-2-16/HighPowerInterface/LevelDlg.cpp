// LevelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "LevelDlg.h"
#include "ShootDiagram.h"
#include "Functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLevelDlg dialog

CLevelDlg::CLevelDlg(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CLevelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLevelDlg)
	//}}AFX_DATA_INIT
}


void CLevelDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLevelDlg)
	DDX_Control(pDX, IDC_levelfile, m_levelFile);
	DDX_Control(pDX, IDC_Handlelevel, m_handleLevel);
	DDX_Control(pDX, IDC_levellist, m_levellist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLevelDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CLevelDlg)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_levelfile, Onlevelfile)
	ON_COMMAND(ID_Exportlevelfile, OnExportlevelfile)
	ON_COMMAND(ID_Inportlevelfile, OnInportlevelfile)
	ON_COMMAND(ID_Savelevelfile, OnSavelevelfile)
	ON_BN_CLICKED(IDC_Handlelevel, OnHandlelevel)
	ON_WM_CTLCOLOR()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_ClearBinCode, OnClearBinCode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLevelDlg message handlers
extern SystemSet systemset;
extern BinArray binArray;
extern int columns[3];
extern BinArray level_binArray;
extern int csvcolumns[3];
extern XYLEVEL xylevel[3];
extern sngPOINT point[3][4];
bool csvopen = false;
CString CSVFilePath;
CString CSVFile = ".csv";

extern CList<XYLEVELItem, XYLEVELItem> levelItem[3];
extern CList<XYLEVELItem, XYLEVELItem> tempBigRect[3];
extern CList<LevelItem, LevelItem> levelItemList;

BOOL CLevelDlg::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();	
	// TODO: Add extra initialization here
	/////////////////////////List初始化
	m_levellist.Init();
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 20;
	strcpy(lf.lfFaceName, "Verdana");
	font.CreateFontIndirect(&lf);
	m_levellist.SetFont(&font, TRUE);

	m_levellist.SetReadOnlyColumns(0);
	m_levellist.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	SetDlgItemText(IDC_Showlevelfile, CSVFile);
	///////////////////////////////////////////
	m_menu.LoadMenu(IDR_MENU2);

	if(csvopen)
	{
		m_menu.EnableMenuItem(ID_Savelevelfile, MF_ENABLED);
	}
	else
	{
		m_menu.EnableMenuItem(ID_Savelevelfile, MF_GRAYED);
	}
	initdlg(binArray.strBinArray, false);

	for(int i=0; i<3; i++)
	{
		InitXYLEVELItem(i);
		GetRange(i);
		SearchRange(i);
	}

	SetDialogFace();

	return TRUE;  
	// return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

bool CLevelDlg::initdlg(CString (*string)[LEVELCOLUMNS], bool level)
{
	int i;
	int chip = 1;
	CString str_item;
	
	m_levellist.DeleteAllItems();
	m_levellist.DeleteAllColumns();

	m_levellist.InsertColumn(0, "BIN", LVCFMT_CENTER, 45);
	m_levellist.InsertColumn(1, "BinCode", LVCFMT_CENTER, 100);
	m_levellist.InsertItem(0, "BIN");
	m_levellist.SetItemText(0, 1, "BinCode");
	CString str2;
	int totalnum = 0;
	if(level)
	{
		for(i=0; i<3; i++)
		{
			cols[i] = csvcolumns[i];
		}
		for(i=0; i<systemset.intMachineType; i++)
		{
			str2.Format("%d", i);
			m_levellist.InsertItem(i+1, str2);
			m_levellist.SetItemText(i+1, 1, "");
			m_levellist.SetItemText(i+1, 1, level_binArray.binName[i]);
		}
	}
	else
	{
		for(i=0; i<3; i++)
		{
			cols[i] = columns[i];
		}	
		for(i=0; i<systemset.intMachineType; i++)
		{
			str2.Format("%d", i);
			m_levellist.InsertItem(i+1, str2);
			m_levellist.SetItemText(i+1, 1, "");
			m_levellist.SetItemText(i+1, 1, binArray.binName[i]);
		}
	}

	totalnum = cols[0] + cols[1] + cols[2];

	for(i=0; i<totalnum; i+=2)
	{
		sscanf(string[0][i], "C%d-%[^(]", &chip, str_item);
		chip --;
		
		insertIteminit(string[0][i]);
		
		if(0 == strcmp(str_item, "XYZ"))
		{
			xylevel[chip].column = i + 2;
			i += 6;
		}
	}

	int nCount = m_levellist.GetHeaderCtrl()->GetItemCount();
	for(i=1; i <= systemset.intMachineType; i++)
	{
		for(int j=1; j<(nCount-1); j++)
		{
			m_levellist.SetItemText(i, j+1, ReformatString(string[i][j-1]));
		}
	}

	return true;
}

bool CLevelDlg::insertIteminit(CString text)
{
	CString str_item;
	//总列数
	int nCount = m_levellist.GetHeaderCtrl()->GetItemCount();

	sscanf(text, "%*[^-]-%[^(]", str_item);
	if(0 == strcmp(str_item, "XYZ"))
	{
		for(int i=0; i<8; i++)
		{
			m_levellist.InsertColumn(nCount+i, text, LVCFMT_CENTER, 80);
		}
		m_levellist.SetItemText(0, nCount, "X1");
		m_levellist.SetItemText(0, nCount+1, "Y1");
		m_levellist.SetItemText(0, nCount+2, "X2");
		m_levellist.SetItemText(0, nCount+3, "Y2");
		m_levellist.SetItemText(0, nCount+4, "X3");
		m_levellist.SetItemText(0, nCount+5, "Y3");
		m_levellist.SetItemText(0, nCount+6, "X4");
		m_levellist.SetItemText(0, nCount+7, "Y4");
	}
	else
	{
		m_levellist.InsertColumn(nCount, text, LVCFMT_CENTER, 80);
		m_levellist.InsertColumn(nCount+1, text, LVCFMT_CENTER, 80);
		m_levellist.SetItemText(0, nCount, "MIN");
		m_levellist.SetItemText(0, nCount+1, "MAX");
	}
	
	return true;
}

//////////////分级文件处理
void CLevelDlg::Onlevelfile() 
{
	// TODO: Add your control notification handler code here
	PopupMenu(IDR_MENU2, 3, this);
}

void CLevelDlg::OnInportlevelfile() 
{
	// TODO: Add your control notification handler code here
	CString sz = "CSV file (*.csv)|*.csv|All File(*.*)|*.*||";
	CFileDialog dlg(true, ".csv", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sz, this);

	if(IDOK==dlg.DoModal())
	{
		CString path = dlg.GetPathName();
		CStdioFile m_file;
		if(m_file.Open((LPCTSTR)path, CFile::modeReadWrite))
		{
			if(ReadLevelCSVFile(&m_file))
			{
				m_file.Close();
				
				CSVFilePath = path;
				CString filename;
				filename = m_file.GetFileName();
				SetDlgItemText(IDC_Showlevelfile, path);
				csvopen = true;
				m_menu.EnableMenuItem(ID_Savelevelfile, MF_ENABLED);
				initdlg(level_binArray.strBinArray, true);

				for(int i=0; i<3; i++)
				{
					tempBigRect[i].RemoveAll();
					CSVLevel_InitXYLEVELItem(i);
					SearchRange(i);
				}
			}
			else
			{
				m_file.Close();
				MessageBox("文件类型不正确!");
			}
		}
		else
		{
			MessageBox("文件打开失败!");
		}
	}		
}

void CLevelDlg::OnSavelevelfile() 
{
	// TODO: Add your control notification handler code here
	getParameter2();
	
	CString path;
	path = CSVFilePath;

	CStdioFile m_file;
	if(m_file.Open((LPCTSTR)path, CFile::modeReadWrite))
	{
		WriteLevelCSVFile(&m_file);
		m_file.Close();
	}
	else
	{
		MessageBox("文件保存失败!");
	}
}

void CLevelDlg::OnExportlevelfile() 
{
	// TODO: Add your control notification handler code here
	getParameter2();
	
	CString sz = "CSV file (*.csv)|*.csv|All File(*.*)|*.*||";
	CFileDialog dlg(false, ".csv", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sz, this);

	if(IDOK==dlg.DoModal())
	{
		CString path = dlg.GetPathName();
		CStdioFile m_file;
		if(m_file.Open((LPCTSTR)path, CFile::modeCreate|CFile::modeReadWrite))
		{
			WriteLevelCSVFile(&m_file);
			m_file.Close();
		}
		else
		{
			MessageBox("文件另存失败!");
		}
	}
}

void CLevelDlg::OnClearBinCode() 
{
	// TODO: Add your command handler code here
	for(int i=1; i <= systemset.intMachineType; i++)
	{
		m_levellist.SetItemText(i, 1, "");
	}
}

////////////////////分级处理
void CLevelDlg::OnHandlelevel() 
{
	// TODO: Add your control notification handler code here
//	PopupMenu(IDR_MENU2, 4, this);
	CAccumulateLevel m_autoaccu;
	m_autoaccu.DoModal();

	extern bool AccuSure;
	if(AccuSure)
	{
		updateLevelList();
	}
}

bool CLevelDlg::updateLevelList()
{
	LevelItem list_item;
	CString str_item, str;
	CString str_bincode[MAXBIN];
	int count = 2;
	int i = 0, j = 0;
	int colsnum = m_levellist.GetHeaderCtrl()->GetItemCount();
	int totallevelnum = 1, levelnum = 1;
	int lines = 2;
	int chipnum = 0;
	
	for(i=0; i<colsnum-1; i++)
	{
		m_levellist.DeleteColumn(1);
	}
	m_levellist.InsertColumn(1, "BinCode", LVCFMT_CENTER, 100);
	m_levellist.SetItemText(0, 1, "BinCode");

	POSITION pos = levelItemList.GetHeadPosition();
	while(pos != NULL)
	{
		list_item = levelItemList.GetNext(pos);
		totallevelnum *= list_item.levelnum;
	}

	for(i=0; i<3; i++)
	{
		cols[i] = 0;
	}
	
	for(i=0; i<totallevelnum+2; i++)
	{
		str_bincode[i] = "";
	}

	pos = levelItemList.GetHeadPosition();
	while(pos != NULL)
	{
		list_item = levelItemList.GetNext(pos);
		sscanf(list_item.item, "C%d-%[^(]", &chipnum, str_item);
		levelnum *= list_item.levelnum;
		lines = 2;
		if(0 == strcmp(str_item, "XYZ"))
		{
			cols[chipnum-1] += 8;
			for(int a=0; a<8; a++)
			{
				m_levellist.InsertColumn(count+a, list_item.item, LVCFMT_CENTER, 100);
			}

			m_levellist.SetItemText(0, count, "X1");
			m_levellist.SetItemText(0, count+1, "Y1");
			m_levellist.SetItemText(0, count+2, "X2");
			m_levellist.SetItemText(0, count+3, "Y2");
			m_levellist.SetItemText(0, count+4, "X3");
			m_levellist.SetItemText(0, count+5, "Y3");
			m_levellist.SetItemText(0, count+6, "X4");
			m_levellist.SetItemText(0, count+7, "Y4");
			
			for(int times=0; times<(levelnum/list_item.levelnum); times++)
			{
				for(j=0; j<list_item.levelnum; j++)
				{
					for(int linenum=0; linenum<(totallevelnum/levelnum); linenum++)
					{
					//	if(list_item.bincode[j] == "")
					//	{
					//	}
						str_bincode[lines] += "_" + list_item.bincode[j];

						str.Format("%0.4f", list_item.x[j][0]);
						m_levellist.SetItemText(lines, count, ReformatString(str));
						str.Format("%0.4f", list_item.y[j][0]);
						m_levellist.SetItemText(lines, count+1, ReformatString(str));
						
						str.Format("%0.4f", list_item.x[j][1]);
						m_levellist.SetItemText(lines, count+2, ReformatString(str));
						str.Format("%0.4f", list_item.y[j][1]);
						m_levellist.SetItemText(lines, count+3, ReformatString(str));
						
						str.Format("%0.4f", list_item.x[j][2]);
						m_levellist.SetItemText(lines, count+4, ReformatString(str));
						str.Format("%0.4f", list_item.y[j][2]);
						m_levellist.SetItemText(lines, count+5, ReformatString(str));
						
						str.Format("%0.4f", list_item.x[j][3]);
						m_levellist.SetItemText(lines, count+6, ReformatString(str));
						str.Format("%0.4f", list_item.y[j][3]);
						m_levellist.SetItemText(lines++, count+7, ReformatString(str));
					}
				}
			}
			
			count += 8;
		}
		else
		{
			cols[chipnum-1] += 2; 
			m_levellist.InsertColumn(count, list_item.item, LVCFMT_CENTER, 100);
			m_levellist.InsertColumn(count+1, list_item.item, LVCFMT_CENTER, 100);;
			m_levellist.SetItemText(0, count, "Min");
			m_levellist.SetItemText(0, count+1, "Max");

			for(int times=0; times<(levelnum/list_item.levelnum); times++)
			{
				for(j=0; j<list_item.levelnum; j++)
				{
					for(int linenum=0; linenum<(totallevelnum/levelnum); linenum++)
					{
					//	if(list_item.bincode[j] != "")
					//	{	
					//	}
						str_bincode[lines] += "_" + list_item.bincode[j];
					
						str.Format("%f", list_item.min[j]);
						m_levellist.SetItemText(lines, count, ReformatString(str));
						str.Format("%f", list_item.max[j]);
						m_levellist.SetItemText(lines++, count+1, ReformatString(str));
					}
				}
			}

			count += 2;
		}
	}
	
	CString str_code;
	for(i=2; i<(totallevelnum+2); i++)
	{
		str_code = "";
		sscanf(str_bincode[i], "_%s", str_code);
		m_levellist.SetItemText(i, 1, str_code);
	}

	return true;
}

///////////每项均分配bincode, 并显示在列表中
bool CLevelDlg::updateLevelList2()
{
	LevelItem list_item;
	CString str_item, str;
	int count = 1;
	int i = 0, j = 0;
	int colsnum = m_levellist.GetHeaderCtrl()->GetItemCount();
	int cols = 0;
	int totallevelnum = 1, levelnum = 1;
	int lines = 2;
	
	for(i=0; i<colsnum-1; i++)
	{
		m_levellist.DeleteColumn(1);
	}

	POSITION pos = levelItemList.GetHeadPosition();
	while(pos != NULL)
	{
		list_item = levelItemList.GetNext(pos);
		totallevelnum *= list_item.levelnum;
	}

	pos = levelItemList.GetHeadPosition();
	while(pos != NULL)
	{
		list_item = levelItemList.GetNext(pos);
		sscanf(list_item.item, "%*[^-]-%[^(]", str_item);
		levelnum *= list_item.levelnum;
		lines = 2;
		if(0 == strcmp(str_item, "XYZ"))
		{
			m_levellist.InsertColumn(count, "BinCode", LVCFMT_CENTER, 100);
			for(cols=1; cols<=8; cols++)
			{
				m_levellist.InsertColumn(count+cols, list_item.item, LVCFMT_CENTER, 100);
			}

			m_levellist.SetItemText(0, count, "BinCode");
			m_levellist.SetItemText(0, count+1, "X1");
			m_levellist.SetItemText(0, count+2, "Y1");
			m_levellist.SetItemText(0, count+3, "X2");
			m_levellist.SetItemText(0, count+4, "Y2");
			m_levellist.SetItemText(0, count+5, "X3");
			m_levellist.SetItemText(0, count+6, "Y3");
			m_levellist.SetItemText(0, count+7, "X4");
			m_levellist.SetItemText(0, count+8, "Y4");
			
			for(int times=0; times<(levelnum/list_item.levelnum); times++)
			{
				for(j=0; j<list_item.levelnum; j++)
				{
					for(int linenum=0; linenum<(totallevelnum/levelnum); linenum++)
					{
						m_levellist.SetItemText(lines, count, list_item.bincode[j]);

						str.Format("%0.4f", list_item.x[j][0]);
						m_levellist.SetItemText(lines, count+1, str);
						str.Format("%0.4f", list_item.y[j][0]);
						m_levellist.SetItemText(lines, count+2, str);
						
						str.Format("%0.4f", list_item.x[j][1]);
						m_levellist.SetItemText(lines, count+3, str);
						str.Format("%0.4f", list_item.y[j][1]);
						m_levellist.SetItemText(lines, count+4, str);
						
						str.Format("%0.4f", list_item.x[j][2]);
						m_levellist.SetItemText(lines, count+5, str);
						str.Format("%0.4f", list_item.y[j][2]);
						m_levellist.SetItemText(lines, count+6, str);
						
						str.Format("%0.4f", list_item.x[j][3]);
						m_levellist.SetItemText(lines, count+7, str);
						str.Format("%0.4f", list_item.y[j][3]);
						m_levellist.SetItemText(lines++, count+8, str);
					}
				}
			}
			
			count += 9;
		}
		else
		{
			m_levellist.InsertColumn(count, "BinCode", LVCFMT_CENTER, 100);
			m_levellist.InsertColumn(count+1, list_item.item, LVCFMT_CENTER, 100);
			m_levellist.InsertColumn(count+2, list_item.item, LVCFMT_CENTER, 100);
			m_levellist.SetItemText(0, count, "BinCode");
			m_levellist.SetItemText(0, count+1, "Min");
			m_levellist.SetItemText(0, count+2, "Max");

			for(int times=0; times<(levelnum/list_item.levelnum); times++)
			{
				for(j=0; j<list_item.levelnum; j++)
				{
					for(int linenum=0; linenum<(totallevelnum/levelnum); linenum++)
					{
						m_levellist.SetItemText(lines, count, list_item.bincode[j]);

						str.Format("%0.4f", list_item.min[j]);
						m_levellist.SetItemText(lines, count+1, str);
						str.Format("%0.4f", list_item.max[j]);
						m_levellist.SetItemText(lines++, count+2, str);
					}
				}
			}

			count += 3;
		}
	}
	
	return true;
}

int CLevelDlg::CalculateLevelNum(int column, int colsnum)
{
	CString str[8];
	CList<CString, CString> ColumnParam[8];
	POSITION pos[8];
	int num = 0;
	bool tail = false;
	bool exist = false;
	int j = 0;

	for(j=0; j<colsnum; j++)
	{
		str[j] = m_levellist.GetItemText(2, column+j); 
		if(str[j] == "")
		{
			return num;
		}
	}

	for(j=0; j<colsnum; j++)
	{
		ColumnParam[j].RemoveAll();
		ColumnParam[j].AddTail(str[j]);
	}

	for(int i=2; i<systemset.intMachineType; i++)
	{
		tail = false;
		exist = false;
		num = 1;

		for(j=0; j<colsnum; j++)
		{
			str[j] = m_levellist.GetItemText(i+1, column+j);
			pos[j] = ColumnParam[j].GetHeadPosition();
			if(str[j] == "")
			{
				num = ColumnParam[j].GetCount();
				return num;
			}
		}

		while(!tail)
		{
			for(j=0; j<colsnum; j++)
			{
				if(str[j] != ColumnParam[j].GetNext(pos[j]))
				{
					j = colsnum;
				}
				else
				{
					tail = true;
					exist = true;
				}
			}

            if(!exist)
			{
				for(j=0; j<colsnum; j++)
				{
					if(pos[j] == NULL)
					{
						tail = true;
						j = colsnum;
					}
				}
			}
		}

		if(!exist)
		{
			for(j=0; j<colsnum; j++)
			{
				ColumnParam[j].AddTail(str[j]);
			}
		}
	}

	num = ColumnParam[0].GetCount();
	return num;
}

void CLevelDlg::getParameter() 
{
	int i;
	HDITEM hdi;
	TCHAR lpBuffer[256];
	bool fFound = false;
	hdi.mask = HDI_TEXT;
	hdi.pszText = lpBuffer;
	hdi.cchTextMax = 256;
	int nCount = m_levellist.GetHeaderCtrl()->GetItemCount();

	for(i=1; i<(nCount-1); i+=2)
	{
		m_levellist.GetHeaderCtrl()->GetItem((i+1), &hdi);
		binArray.strBinArray[0][i-1] = hdi.pszText;
		binArray.strBinArray[0][i] = hdi.pszText;
	}
	for(i=1; i <= systemset.intMachineType; i++)
	{
		binArray.binName[i-1] = m_levellist.GetItemText(i, 1);
		for(int j=2; j<nCount; j++)
		{
			binArray.strBinArray[i][j-2] = "NULL";
			binArray.strBinArray[i][j-2] = m_levellist.GetItemText(i, j);
		}
	}
	for(i=0; i<3; i++)
	{
		columns[i] = cols[i];
		InitXYLEVELItem(i);
		SetRange(i);
	}

	GetDlgItemText(IDC_Showlevelfile, CSVFile);
}

void CLevelDlg::getParameter2() 
{
	int i;
	HDITEM hdi;
	TCHAR lpBuffer[256];
	bool fFound = false;
	hdi.mask = HDI_TEXT;
	hdi.pszText = lpBuffer;
	hdi.cchTextMax = 256;
	int nCount = m_levellist.GetHeaderCtrl()->GetItemCount();

	for(i=1; i<nCount; i+=2)
	{
		m_levellist.GetHeaderCtrl()->GetItem((i+1), &hdi);
		level_binArray.strBinArray[0][i-1] = hdi.pszText;
		level_binArray.strBinArray[0][i] = hdi.pszText;
	}
	for(i=1; i <= systemset.intMachineType; i++)
	{
		level_binArray.binName[i-1] = m_levellist.GetItemText(i, 1);
		for(int j=2; j<nCount; j++)
		{
			level_binArray.strBinArray[i][j-2] = m_levellist.GetItemText(i, j);
		}
	}
	for(i=0; i<3; i++)
	{
		csvcolumns[i] = cols[i];
	}
}


void CLevelDlg::SetDialogFace()
{
	m_levelFile.SetBitmaps(IDB_Button_LevelFileNormal, IDB_Button_LevelFileDown,
		              IDB_Button_LevelFileHigh, IDB_Button_LevelFileDisable);
	m_levelFile.SizeToContent();

	m_handleLevel.SetBitmaps(IDB_Button_HandleLevelNormal, IDB_Button_HandleLevelDown,
		              IDB_Button_HandleLevelHigh, IDB_Button_HandleLevelDisable);
	m_handleLevel.SizeToContent();
}

BOOL CLevelDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default	
//	return CResizingDialog::OnEraseBkgnd(pDC);
	return CResizingDialog::DrawBK(pDC, IDB_SetLevelBK, 1);
//	return true;
}

HBRUSH CLevelDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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


void CLevelDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd *pwnd;
	pwnd = GetDlgItem(IDC_levellist);
	PopupMenu(IDR_MENU4, 0, pwnd);
	CResizingDialog::OnRButtonDown(nFlags, point);
}




