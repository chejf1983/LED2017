// AccumulateLevel.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "AccumulateLevel.h"
#include "Functions.h"
#include "ShootDiagram.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAccumulateLevel dialog


CAccumulateLevel::CAccumulateLevel(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CAccumulateLevel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAccumulateLevel)
	m_chip = 0;
	//}}AFX_DATA_INIT
}


void CAccumulateLevel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAccumulateLevel)
	DDX_Control(pDX, IDC_delway, m_delway);
	DDX_Control(pDX, IDC_ShootCal, m_shootcal);
	DDX_Control(pDX, IDC_AutoList, m_autolist);
	DDX_Control(pDX, IDC_AutoList2, m_autolist2);
	DDX_Control(pDX, IDC_AutoListTotal, m_autolistTotal);
	DDX_Control(pDX, IDC_ShowItem, m_showItem);
	DDX_Control(pDX, IDC_LevelWay, m_levelway);
	DDX_Control(pDX, IDC_AddItem, m_addItem);
	DDX_Control(pDX, IDC_SURE, m_sure);
	DDX_Control(pDX, IDC_DeleteItem, m_delItem);
	DDX_Control(pDX, IDC_Cancel, m_cancel);
	DDX_Radio(pDX, IDC_levelchip1, m_chip);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAccumulateLevel, CResizingDialog)
	//{{AFX_MSG_MAP(CAccumulateLevel)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_Exit, OnExit)
	ON_BN_CLICKED(IDC_AddItem, OnAddItem)
	ON_BN_CLICKED(IDC_DeleteItem, OnDeleteItem)
	ON_COMMAND(ID_IF, OnIf)
	ON_COMMAND(ID_IR, OnIr)
	ON_COMMAND(ID_VF, OnVf)
	ON_COMMAND(ID_VR, OnVr)
	ON_COMMAND(ID_DVF, OnDvf)
	ON_COMMAND(ID_THY, OnThy)
	ON_COMMAND(ID_IV, OnIv)
	ON_COMMAND(ID_WL, OnWl)
	ON_COMMAND(ID_PWL, OnPwl)
	ON_COMMAND(ID_DeltaWL, OnDeltaWL)
	ON_COMMAND(ID_CCT, OnCct)
	ON_COMMAND(ID_CRI, OnCri)
	ON_COMMAND(ID_PUR, OnPur)
	ON_COMMAND(ID_XYZ, OnXyz)
	ON_BN_CLICKED(IDC_levelchip1, Onlevelchip1)
	ON_BN_CLICKED(IDC_levelchip2, Onlevelchip2)
	ON_BN_CLICKED(IDC_levelchip3, Onlevelchip3)
	ON_BN_CLICKED(IDC_SURE, OnSure)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_ShootCal, OnShootCal)
	ON_BN_CLICKED(IDC_fastLevel, OnfastLevel)
	ON_BN_CLICKED(IDC_Applylevels, OnApplylevels)
	ON_BN_CLICKED(IDC_Cancel, OnCancel)
	ON_CBN_SELCHANGE(IDC_ShowItem, OnSelchangeShowItem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAccumulateLevel message handlers
extern bool row1;
extern SystemSet systemset;
int AcStartBin = 2;
bool AccuSure = false;
int tempAcItemNum = 0;
int AcItemNum = 0;
TempAccuItem AccuItem[40];
CList<LevelItem, LevelItem> levelItemList;
extern CList<XYLEVELItem, XYLEVELItem> levelItem[3];
extern CList<CString, CString> tempItemforlevel[3];

BOOL CAccumulateLevel::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	MoveWindow(240, 150, 576, 400);
//	CRgn rgn;
//	rgn.CreateRoundRectRgn(0, 0, 576, 400, 10, 10);
//	SetWindowRgn(rgn, true);

	MoveWindow(50, 50, 900, 600);
	CRgn rgn;
	rgn.CreateRoundRectRgn(0, 0, 900, 600, 10, 10);
	SetWindowRgn(rgn, true);

	/////////////////////////List初始化
	m_autolist.Init();
	m_autolist2.Init();
	m_autolistTotal.Init();
	
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 20;
	strcpy(lf.lfFaceName, "Verdana");
	font.CreateFontIndirect(&lf);

	m_autolist.SetFont(&font, TRUE);
	m_autolist.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_autolist2.SetFont(&font, TRUE);
	m_autolist2.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_autolistTotal.SetFont(&font, TRUE);
	m_autolistTotal.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	row1 = true;

	m_levelway.InsertString(0, "等差");
	m_levelway.InsertString(1, "等比");
	m_levelway.SetCurSel(0);

	m_delway.InsertString(0, "删除代码");
	m_delway.InsertString(1, "删除项目");
	m_delway.SetCurSel(0);

	m_autolist.InsertColumn(0, "BinCode", LVCFMT_CENTER, 90);
	m_autolist.InsertColumn(1, "Min", LVCFMT_CENTER, 80);
	m_autolist.InsertColumn(2, "Max", LVCFMT_CENTER, 80);

	m_autolist2.InsertColumn(0, "BinCode", LVCFMT_CENTER, 70);
	m_autolist2.InsertColumn(1, "X1", LVCFMT_CENTER, 56);
	m_autolist2.InsertColumn(2, "Y1", LVCFMT_CENTER, 56);
	m_autolist2.InsertColumn(3, "X2", LVCFMT_CENTER, 56);
	m_autolist2.InsertColumn(4, "Y2", LVCFMT_CENTER, 56);
	m_autolist2.InsertColumn(5, "X3", LVCFMT_CENTER, 56);
	m_autolist2.InsertColumn(6, "Y3", LVCFMT_CENTER, 56);
	m_autolist2.InsertColumn(7, "X4", LVCFMT_CENTER, 56);
	m_autolist2.InsertColumn(8, "Y4", LVCFMT_CENTER, 56);

	tempAcItemNum = AcItemNum;

	for(int i=0; i<systemset.intMachineType; i++)
	{
		m_autolist.InsertItem(i, "");
		m_autolist2.InsertItem(i, "");
		m_autolistTotal.InsertItem(i, "");
	}

	AcStartBin = 2;
	AccuSure = false;	
	
//	m_showItem.InsertString(i, str);
//	m_showItem.Clear();

	shootlevel = false;
	ShowLevelTool(shootlevel);
	updateTotalList();

	OnInitShowItem();

	SetDialogFace();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CAccumulateLevel::OnInitShowItem()
{	
	int i = 0;
	int num = 1;
	int lines = m_showItem.GetCount();
	
	CString str, str_item;
	for(i=0; i<lines; i++)
	{
		m_showItem.DeleteString(0);
	}

	m_showItem.InsertString(0, "");
	for(i=0; i<3; i++)
	{
		POSITION pos = tempItemforlevel[i].GetHeadPosition();
		while(pos != NULL)
		{
			str = tempItemforlevel[i].GetNext(pos);
			sscanf(str, "%*[^-]-%[^(]", str_item);
			m_showItem.InsertString(num++, str);	
		}
	}
	
	m_showItem.SetCurSel(0);

	return true;
}

void CAccumulateLevel::OnInitList() 
{
	CString str;
	for(int i=0; i<AcItemNum; i++)
	{
		str.Format("%d", i+1);
		m_autolist.InsertItem(i, str);
		m_autolist.SetItemText(i, 1, AccuItem[i].AccuItem);
		str.Format("%f", AccuItem[i].base);
		m_autolist.SetItemText(i, 2, ReformatString(str));
		if(AccuItem[i].way == 0)
		{
			m_autolist.SetItemText(i, 3, "+");
		}
		else
		{
			m_autolist.SetItemText(i, 3, "*");
		}
		str.Format("%f", AccuItem[i].step); 
		m_autolist.SetItemText(i, 4, ReformatString(str));
		str.Format("%d", AccuItem[i].levelnum);
		m_autolist.SetItemText(i, 5, str);
	}
}

void CAccumulateLevel::OnXYZCheck() 
{
	// TODO: Add your control notification handler code here
}

void CAccumulateLevel::OnAddItem() 
{
	// TODO: Add your control notification handler code here
//	PopupMenu(IDR_MENU3, 0, this);
}

bool CAccumulateLevel::ShowLevelTool(bool shoot)
{	
	m_autolist.ShowWindow(!shoot);
	m_autolist.m_SkinHorizontalScrollbar.ShowWindow(!shoot);
	m_autolist.m_SkinVerticleScrollbar.ShowWindow(!shoot);

	m_autolist2.ShowWindow(shoot);
	m_autolist2.m_SkinHorizontalScrollbar.ShowWindow(shoot);
	m_autolist2.m_SkinVerticleScrollbar.ShowWindow(shoot);

	m_shootcal.ShowWindow(shoot);
			
	GetDlgItem(IDC_BaseData)->ShowWindow(!shoot);
	GetDlgItem(IDC_Average)->ShowWindow(!shoot);
	GetDlgItem(IDC_levelsnum)->ShowWindow(!shoot);
	GetDlgItem(IDC_LevelWay)->ShowWindow(!shoot);
	GetDlgItem(IDC_fastLevel)->ShowWindow(!shoot);
	GetDlgItem(IDC_fastSTATIC)->ShowWindow(!shoot);
	
	if(shoot)
	{
		for(int i=0; i<systemset.intMachineType; i++)
		{
			m_autolist.SetItemText(i, 0, "");
			m_autolist.SetItemText(i, 1, "");
			m_autolist.SetItemText(i, 2, "");
		}
	}
	else
	{
		for(int i=0; i<systemset.intMachineType; i++)
		{
			m_autolist2.SetItemText(i, 0, "");
			m_autolist2.SetItemText(i, 1, "");
			m_autolist2.SetItemText(i, 2, "");
			m_autolist2.SetItemText(i, 3, "");
			m_autolist2.SetItemText(i, 4, "");
			m_autolist2.SetItemText(i, 5, "");
			m_autolist2.SetItemText(i, 6, "");
			m_autolist2.SetItemText(i, 7, "");
			m_autolist2.SetItemText(i, 8, "");
		}
	}
	
	return true;
}

void CAccumulateLevel::OnDeleteItem() 
{
	// TODO: Add your control notification handler code here
	if(0 == m_delway.GetCurSel())
	{
		POSITION pos;
		int num = 0;
		if(shootlevel)
		{
			pos = m_autolist2.GetFirstSelectedItemPosition();
			if(pos==NULL)
			{
				MessageBox("请选择要删除行!");
			}
			else
			{
				num = (int)pos - 1;
				m_autolist2.DeleteItem(num);
			}
		}
		else
		{
			pos = m_autolist.GetFirstSelectedItemPosition();
			if(pos==NULL)
			{
				MessageBox("请选择要删除行!");
			}
			else
			{
				num = (int)pos - 1;
				m_autolist.DeleteItem(num);
			}
		}
	}
	else
	{
		CString str;
		int colnum = 0;
		int i = 0;
		
		GetDlgItemText(IDC_ShowItem, str);
		POSITION pos = levelItemList.GetHeadPosition();
		while(pos != NULL)
		{
			if(levelItemList.GetAt(pos).item == str)
			{
				levelItemList.RemoveAt(pos);
				m_autolistTotal.DeleteColumn(colnum);
				pos = NULL;
			}
			else
			{
				colnum++;
				levelItemList.GetNext(pos);
			}	
		}	

		updateTotalList();
		
		if(shootlevel)
		{
			for(i=0; i<systemset.intMachineType; i++)
			{
				for(int j=0; j<9; j++)
				{
					m_autolist2.SetItemText(i, j, "");
				}
			}
		}
		else
		{
			for(i=0; i<systemset.intMachineType; i++)
			{
				m_autolist.SetItemText(i, 0, "");
				m_autolist.SetItemText(i, 1, "");
				m_autolist.SetItemText(i, 2, "");
			}
		}
	}
}

void CAccumulateLevel::InsertItem(CString str)
{
	CString str2, str_min, str_max;
	LevelItem list_item;
	int i=0;

	shootlevel = false;
	ShowLevelTool(shootlevel);

	for(i=0; i<systemset.intMachineType; i++)
	{
		m_autolist.SetItemText(i, 0, "");
		m_autolist.SetItemText(i, 1, "");
		m_autolist.SetItemText(i, 2, "");
	}

	str2 = "0";
	SetDlgItemText(IDC_BaseData, str2);
	SetDlgItemText(IDC_Average, str2);
	SetDlgItemText(IDC_levelsnum, str2);

	str2.Format("C%d-%s", m_chip+1, str);
	SetDlgItemText(IDC_ShowItem, str2);
	
	POSITION pos = levelItemList.GetHeadPosition();
	while(pos != NULL)
	{
		list_item = levelItemList.GetAt(pos);
		if(list_item.item == str2)
		{
			for(i=0; i<list_item.levelnum; i++)
			{
				m_autolist.SetItemText(i, 0, list_item.bincode[i]);

				str_min.Format("%0.4f", list_item.min[i]);
				str_max.Format("%0.4f", list_item.max[i]);
				m_autolist.SetItemText(i, 1, ReformatString(str_min));
				m_autolist.SetItemText(i, 2, ReformatString(str_max));
			}
			pos = NULL;
		}
		else
		{
			levelItemList.GetNext(pos);
		}
	}
}


void CAccumulateLevel::OnIf() 
{
	// TODO: Add your command handler code here
	InsertItem("IF");
}

void CAccumulateLevel::OnIr() 
{
	// TODO: Add your command handler code here
	InsertItem("IR");
}

void CAccumulateLevel::OnVf() 
{
	// TODO: Add your command handler code here
	InsertItem("VF");
}

void CAccumulateLevel::OnVr() 
{
	// TODO: Add your command handler code here
	InsertItem("VR");
}

void CAccumulateLevel::OnDvf() 
{
	// TODO: Add your command handler code here
	InsertItem("DVF");
}

void CAccumulateLevel::OnThy() 
{
	// TODO: Add your command handler code here
	InsertItem("THY");
}

void CAccumulateLevel::OnIv() 
{
	// TODO: Add your command handler code here
	InsertItem("IV");
}

void CAccumulateLevel::OnXyz() 
{
	// TODO: Add your command handler code here
	CString str, str_X[4], str_Y[4];
	LevelItem list_item;
	int i=0;

	shootlevel = true;
	ShowLevelTool(shootlevel);

	for(i=0; i<systemset.intMachineType; i++)
	{
		m_autolist2.SetItemText(i, 0, "");
		m_autolist2.SetItemText(i, 1, "");
		m_autolist2.SetItemText(i, 2, "");
		m_autolist2.SetItemText(i, 3, "");
		m_autolist2.SetItemText(i, 4, "");
		m_autolist2.SetItemText(i, 5, "");
		m_autolist2.SetItemText(i, 6, "");
		m_autolist2.SetItemText(i, 7, "");
		m_autolist2.SetItemText(i, 8, "");
	}

	m_showItem.GetWindowText(str);

	POSITION pos = levelItemList.GetHeadPosition();
	while(pos != NULL)
	{
		list_item = levelItemList.GetAt(pos);
		if(list_item.item == str)
		{
			for(i=0; i<list_item.levelnum; i++)
			{
				m_autolist2.SetItemText(i, 0, list_item.bincode[i]);
				
				for(int j=0; j<4; j++)
				{
					str_X[j].Format("%0.4f", list_item.x[i][j]);
					str_Y[j].Format("%0.4f", list_item.y[i][j]);
				}

				m_autolist2.SetItemText(i, 1, str_X[0]);
				m_autolist2.SetItemText(i, 2, str_Y[0]);
				m_autolist2.SetItemText(i, 3, str_X[1]);
				m_autolist2.SetItemText(i, 4, str_Y[1]);
				m_autolist2.SetItemText(i, 5, str_X[2]);
				m_autolist2.SetItemText(i, 6, str_Y[2]);
				m_autolist2.SetItemText(i, 7, str_X[3]);
				m_autolist2.SetItemText(i, 8, str_Y[3]);
			}
			pos = NULL;
		}
		else
		{
			levelItemList.GetNext(pos);
		}
	}
}
void CAccumulateLevel::OnWl() 
{
	// TODO: Add your command handler code here
	InsertItem("WL");
}

void CAccumulateLevel::OnPwl() 
{
	// TODO: Add your command handler code here
	InsertItem("PWL");
}

void CAccumulateLevel::OnDeltaWL() 
{
	// TODO: Add your command handler code here
	InsertItem("DeltaWL");
}

void CAccumulateLevel::OnPur() 
{
	// TODO: Add your command handler code here
	InsertItem("PUR");
}

void CAccumulateLevel::OnCct() 
{
	// TODO: Add your command handler code here
	InsertItem("CCT");
}

void CAccumulateLevel::OnCri() 
{
	// TODO: Add your command handler code here
	InsertItem("CRI");
}

void CAccumulateLevel::Onlevelchip1() 
{
	// TODO: Add your control notification handler code here
	m_chip = 0;
}

void CAccumulateLevel::Onlevelchip2() 
{
	// TODO: Add your control notification handler code here
	m_chip = 1;
}

void CAccumulateLevel::Onlevelchip3() 
{
	// TODO: Add your control notification handler code here
	m_chip = 2;
}

bool CAccumulateLevel::OnfastLevel() 
{
	// TODO: Add your control notification handler code here
	double value1 = 0, value2 = 0;
	int startbin = 1;
	CString str;
	TempAccuItem AccuParam;
	HDITEM hdi;
	TCHAR lpBuffer[256];
	bool fFound = false;
	hdi.mask = HDI_TEXT;
	hdi.pszText = lpBuffer;
	hdi.cchTextMax = 256;

	for(int i=0; i<systemset.intMachineType; i++)
	{
		m_autolist.SetItemText(i, 0, "");
		m_autolist.SetItemText(i, 1, "");
		m_autolist.SetItemText(i, 2, "");
	}

	GetDlgItemText(IDC_ShowItem, AccuParam.AccuItem);
	if(AccuParam.AccuItem != "")
	{
		GetDlgItemText(IDC_BaseData, str);
		if(str == "")
		{
			MessageBox("请设置分级最小值!");
			return false;
		}
		AccuParam.base = atof(str);
		if(AccuParam.base < 0)
		{
			AccuParam.base = 0;
			str = "0";
			SetDlgItemText(IDC_BaseData, str);
		}
		
		GetDlgItemText(IDC_Average, str);
		if(str == "")
		{
			MessageBox("请设置分级步长!");
			return false;
		}
		AccuParam.step = atof(str);
		if(AccuParam.step < 0)
		{
			AccuParam.step = 1;
			str = "1";
			SetDlgItemText(IDC_Average, str);
		}
		
		GetDlgItemText(IDC_levelsnum, str);
		if(str == "")
		{
			MessageBox("请设置分级数!");
			return false;
		}
		AccuParam.levelnum = atoi(str);
		
		if(AccuParam.levelnum < 0)
		{
			AccuParam.levelnum = 0;
			str = "0";
			SetDlgItemText(IDC_levelsnum, str);
		}
		
		if(AccuParam.levelnum > (systemset.intMachineType - startbin))
		{
			MessageBox("分级数过多, 应用失败!");
			return false;
		}
		else
		{
			value1 = AccuParam.base;
			AccuParam.way = m_levelway.GetCurSel();
			if(0 == AccuParam.way)
			{
				value2 = AccuParam.base + AccuParam.step;
			}
			else
			{
				value2 = AccuParam.base * AccuParam.step;
			}
			
			for(int i=0; i<AccuParam.levelnum; i++)
			{
				str.Format("%s-%d", AccuParam.AccuItem, i+1);
				m_autolist.SetItemText(i, 0, ReformatString(str));
				str.Format("%f", value1);
				m_autolist.SetItemText(i, 1, ReformatString(str));
				str.Format("%f", value2);
				m_autolist.SetItemText(i, 2, ReformatString(str));
				
				if(0 == AccuParam.way)
				{
					value1 += AccuParam.step;
					value2 += AccuParam.step;
				}
				else
				{
					value1 *= AccuParam.step;
					value2 *= AccuParam.step;
				}
			}
		}
	}
	else
	{
		MessageBox("请选择要分级项目!");
	}
	
	return true;
}

void CAccumulateLevel::OnShootCal() 
{
	// TODO: Add your control notification handler code here
	extern int shootchip; 
	shootchip = 0;
	CShootDiagram m_shootdiagram;
	m_shootdiagram.DoModal();
	m_shootdiagram.m_shootchip = 0;
	SetAutoList2();
}

bool CAccumulateLevel::SetAutoList2()
{
	XYLEVELItem item;
	CString str;
	int rownum = 0;

	for(int i=0; i<systemset.intMachineType; i++)
	{
		for(int j=0; j<9; j++)
		{
			m_autolist2.SetItemText(i, j, "");
		}
	}

	POSITION pos = levelItem[m_chip].GetHeadPosition();
	while(pos != NULL)
	{
		item = levelItem[m_chip].GetNext(pos);

		str.Format("C%d-XYZ-%d", m_chip+1, rownum+1);
		m_autolist2.SetItemText(rownum, 0, str);
		str.Format("%0.4f", item.x[0]);
		m_autolist2.SetItemText(rownum, 1, str);
		str.Format("%0.4f", item.y[0]);
		m_autolist2.SetItemText(rownum, 2, str);
		str.Format("%0.4f", item.x[1]);
		m_autolist2.SetItemText(rownum, 3, str);
		str.Format("%0.4f", item.y[1]);
		m_autolist2.SetItemText(rownum, 4, str);
		str.Format("%0.4f", item.x[2]);
		m_autolist2.SetItemText(rownum, 5, str);
		str.Format("%0.4f", item.y[2]);
		m_autolist2.SetItemText(rownum, 6, str);
		str.Format("%0.4f", item.x[3]);
		m_autolist2.SetItemText(rownum, 7, str);
		str.Format("%0.4f", item.y[3]);
		m_autolist2.SetItemText(rownum, 8, str);
		rownum++;
	}
	return false;
}

void CAccumulateLevel::OnApplylevels() 
{
	// TODO: Add your control notification handler code here
	CString str, str2, str_max, str_min, str_x[4], str_y[4];
	LevelItem list_item;
	XYLEVELItem item;
	bool exist = false, before = false;
	POSITION itempos = NULL;
	POSITION pos = levelItemList.GetHeadPosition();
	int i=0;
	CString itemName;
	int chipnum = 1, chipnum2 = 1;
	bool applyOK = false;
	
	m_showItem.GetWindowText(str);
	sscanf(str, "C%d", &chipnum);

	if(str != "")
	{
		while(pos != NULL)
		{
			itempos = pos;
			itemName = levelItemList.GetNext(pos).item;
			if(itemName == str)
			{
				exist = true;
				pos = NULL;
			}
			else
			{
				sscanf(itemName, "C%d", &chipnum2);
				if(chipnum2 > chipnum)
				{
					before = true;
					pos = NULL;
				}
			}	
		}
		
		if(shootlevel)
		{
			levelItem[m_chip].RemoveAll();
			list_item.item = str;
			list_item.levelnum = 0;
			str = m_autolist2.GetItemText(list_item.levelnum, 1);
			
			while(str != "")
			{
				if(list_item.levelnum < systemset.intMachineType)
				{
					applyOK = true;
					str_x[0] = m_autolist2.GetItemText(list_item.levelnum, 1);
					str_y[0] = m_autolist2.GetItemText(list_item.levelnum, 2);
					str_x[1] = m_autolist2.GetItemText(list_item.levelnum, 3);
					str_y[1] = m_autolist2.GetItemText(list_item.levelnum, 4);
					str_x[2] = m_autolist2.GetItemText(list_item.levelnum, 5);
					str_y[2] = m_autolist2.GetItemText(list_item.levelnum, 6);
					str_x[3] = m_autolist2.GetItemText(list_item.levelnum, 7);
					str_y[3] = m_autolist2.GetItemText(list_item.levelnum, 8);
					
					for(i=0; i<4; i++)
					{
						list_item.x[list_item.levelnum][i] = atof(str_x[i]);
						list_item.y[list_item.levelnum][i] = atof(str_y[i]);
						item.x[i] = atof(str_x[i]);
						item.y[i] = atof(str_y[i]);
					}
					
					
					list_item.bincode[list_item.levelnum++] = m_autolist2.GetItemText(list_item.levelnum, 0);
					
					item.num = 0;
					levelItem[m_chip].AddTail(item);
					SetOrderNum(m_chip);
					
					str = m_autolist2.GetItemText(list_item.levelnum, 1);
				}
			}

			SearchRange(m_chip);
		}
		else
		{
			list_item.item = str;
			list_item.levelnum = 0;
			str = m_autolist.GetItemText(list_item.levelnum, 1);
			
			while(str != "")
			{
				if(list_item.levelnum < systemset.intMachineType)
				{
					applyOK = true;
					str_min = m_autolist.GetItemText(list_item.levelnum, 1);
					str_max = m_autolist.GetItemText(list_item.levelnum, 2);
					list_item.min[list_item.levelnum] = atof(str_min);
					list_item.max[list_item.levelnum] = atof(str_max);
					list_item.bincode[list_item.levelnum++] = m_autolist.GetItemText(list_item.levelnum, 0);
					
					str = m_autolist.GetItemText(list_item.levelnum, 1);
				}
			}
		}
		
		if(applyOK)
		{
			if(exist)
			{
				levelItemList.GetAt(itempos) = list_item;
			}
			else
			{
				if(before)
				{
					levelItemList.InsertBefore(itempos, list_item);
				}
				else
				{
					levelItemList.AddTail(list_item);
				}	
			}	
		}
	}
	
	updateTotalList();
}

bool CAccumulateLevel::updateTotalList()
{
	LevelItem list_item;
	int count = 0;
	int i = 0;
	int colsnum = m_autolistTotal.GetHeaderCtrl()->GetItemCount();
	
	for(i=0; i<colsnum; i++)
	{
		m_autolistTotal.DeleteColumn(0);
	}

	POSITION pos = levelItemList.GetHeadPosition();
	while(pos != NULL)
	{
		list_item = levelItemList.GetNext(pos);
		
		m_autolistTotal.InsertColumn(count, list_item.item, LVCFMT_CENTER, 80);
		for(i=0; i<systemset.intMachineType; i++)
		{
			m_autolistTotal.SetItemText(i, count, "");
		}

		for(i=0; i<list_item.levelnum; i++)
		{
			m_autolistTotal.SetItemText(i, count, list_item.bincode[i]);
		}
		count++;
	}
	
	return true;
}

void CAccumulateLevel::OnSure() 
{
	// TODO: Add your control notification handler code here
	int binnum = 1;
	int levelnum = 1;
	CString str, str2, strHead[3];
	int i = 0;
	int XYBinNum[3] = {0, 0, 0};
	int num = 0;

	strHead[0] = "C1";
	strHead[1] = "C2";
	strHead[2] = "C3";

/*	GetDlgItemText(IDC_startbin, str);
	if(str == "")
	{
		MessageBox("起始BIN不能为空!");
		return;
	}
	else
	{
		AcStartBin = atoi(str)+1;++
	}
	*/
	AcStartBin = 2;
	AcItemNum = tempAcItemNum;
	for(i=0; i<AcItemNum; i++)
	{
		str = m_autolist.GetItemText(i, 2);
		if(str == "")
		{
			MessageBox("请将数据填写完整!");
			return;
		}
		str = m_autolist.GetItemText(i, 4);
		if(str == "")
		{
			MessageBox("请将数据填写完整!");
			return;
		}
		str = m_autolist.GetItemText(i, 5);
		if(str == "")
		{
			MessageBox("请将数据填写完整!");
			return;
		}
		else if(str == "0")
		{
			MessageBox("分级数不能为0!");
			return;
		}
	}

	for(i=0; i<AcItemNum; i++)
	{
		str = m_autolist.GetItemText(i, 5);
		levelnum = atoi(str);
		binnum *= levelnum;
	}

	for(i=0; i<3; i++)
	{
		XYBinNum[i] = CountNum(i);
		if(XYBinNum[i] != 0)
		{
			binnum *= XYBinNum[i];
		}
	}

	if(binnum > systemset.intMachineType)
	{
		MessageBox("分级数过多，超出总BIN数!");
		return;
	}
	else
	{
		num = 0;
		for(i=0; i<3; i++)
		{
			for(int j=0; j<AcItemNum; j++)
			{
				str = m_autolist.GetItemText(j, 1);
				sscanf(str, "%[^_]", str2);
				if(0 == strcmp(str2, strHead[i]))
				{
					AccuItem[num].AccuItem = m_autolist.GetItemText(j, 1);
					AccuItem[num].base = atof(m_autolist.GetItemText(j, 2));
					if(m_autolist.GetItemText(j, 3) == "+")
					{
						AccuItem[num].way = 0;
					}
					else
					{
						AccuItem[num].way = 1;
					}
					AccuItem[num].step = atof(m_autolist.GetItemText(j, 4));
					AccuItem[num].levelnum = atoi(m_autolist.GetItemText(j, 5));
					num++;
				}
			}	
		}
	}

	row1 = false;
	AccuSure = true;
	OnClose();
}

void CAccumulateLevel::OnCancel() 
{
	// TODO: Add your control notification handler code here
	row1 = false;
	AccuSure = false;
	OnClose();
}

void CAccumulateLevel::OnExit() 
{
	// TODO: Add your control notification handler code here
	row1 = false;
	OnClose();
}

void CAccumulateLevel::SetDialogFace()
{
	m_addItem.SetBitmaps(IDB_Button_AddItemNormal, IDB_Button_AddItemDown,
		              IDB_Button_AddItemHigh, IDB_Button_AddItemDisable);
	m_addItem.SizeToContent();

	m_delItem.SetBitmaps(IDB_Button_DelItemNormal, IDB_Button_DelItemDown,
		                 IDB_Button_DelItemHigh, IDB_Button_DelItemDisable);
	m_delItem.SizeToContent();

	m_sure.SetBitmaps(IDB_Button_SureNormal3, IDB_Button_SureDown3,
		              IDB_Button_SureHigh3, IDB_Button_SureDisable3);
	m_sure.SizeToContent();

	m_cancel.SetBitmaps(IDB_Button_CancelNormal5, IDB_Button_CancelDown5,
		                 IDB_Button_CancelHigh5, IDB_Button_CancelDisable5);
	m_cancel.SizeToContent();
}

void CAccumulateLevel::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	CResizingDialog::OnLButtonDown(nFlags, point);
}

BOOL CAccumulateLevel::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return CResizingDialog::DrawBK(pDC, IDB_AccumulateBK, 0);
	return CResizingDialog::OnEraseBkgnd(pDC);
}

HBRUSH CAccumulateLevel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CResizingDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO: Change any attributes of the DC here
/*	if(nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr=(HBRUSH)::GetStockObject(NULL_BRUSH);
	}*/
	// TODO: Return a different brush if the default is not desired
	return hbr;
}


BOOL CAccumulateLevel::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_DELETE:
			OnDeleteItem();
			return true;
		}
	}
	return CResizingDialog::PreTranslateMessage(pMsg);
}

void CAccumulateLevel::OnSelchangeShowItem() 
{
	// TODO: Add your control notification handler code here
	CString str, str_item;
	CString str_min, str_max;
	LevelItem list_item;
	int i=0, j=0;
	int num = m_showItem.GetCurSel();
	m_showItem.GetLBText(num, str);
	sscanf(str, "%*[^-]-%[^(]", str_item);
	if(0 == strcmp(str_item, "XYZ"))
	{
		OnXyz();

		for(i=0; i<systemset.intMachineType; i++)
		{
			for(j=0; j<9; j++)
			{
				m_autolist2.SetItemText(i, j, "");
			}
		}

		POSITION pos = levelItemList.GetHeadPosition();
		while(pos != NULL)
		{
			list_item = levelItemList.GetAt(pos);
			if(list_item.item == str)
			{
				for(i=0; i<list_item.levelnum; i++)
				{
					m_autolist2.SetItemText(i, 0, list_item.bincode[i]);
					
					for(j=1; j<5; j++)
					{
						str_min.Format("%0.4f", list_item.x[i][j-1]);
						str_max.Format("%0.4f", list_item.y[i][j-1]);
						m_autolist2.SetItemText(i, j*2-1, ReformatString(str_min));
						m_autolist2.SetItemText(i, j*2, ReformatString(str_max));
					}
				}
				pos = NULL;
			}
			else
			{
				levelItemList.GetNext(pos);
			}
		}
	}
	else
	{
		shootlevel = false;
		ShowLevelTool(shootlevel);
		
		for(i=0; i<systemset.intMachineType; i++)
		{
			m_autolist.SetItemText(i, 0, "");
			m_autolist.SetItemText(i, 1, "");
			m_autolist.SetItemText(i, 2, "");
		}
		
		SetDlgItemText(IDC_BaseData, "0");
		SetDlgItemText(IDC_Average, "0");
		SetDlgItemText(IDC_levelsnum, "0");
		
		POSITION pos = levelItemList.GetHeadPosition();
		while(pos != NULL)
		{
			list_item = levelItemList.GetAt(pos);
			if(list_item.item == str)
			{
				for(i=0; i<list_item.levelnum; i++)
				{
					m_autolist.SetItemText(i, 0, list_item.bincode[i]);
					
					str_min.Format("%0.4f", list_item.min[i]);
					str_max.Format("%0.4f", list_item.max[i]);
					m_autolist.SetItemText(i, 1, ReformatString(str_min));
					m_autolist.SetItemText(i, 2, ReformatString(str_max));
				}
				pos = NULL;
			}
			else
			{
				levelItemList.GetNext(pos);
			}
		}
	}
}
