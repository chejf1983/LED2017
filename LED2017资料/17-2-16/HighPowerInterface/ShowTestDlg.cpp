// ShowTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HighPowerInterface.h"
#include "ShowTestDlg.h"
#include "Functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowTestDlg dialog

CShowTestDlg::CShowTestDlg(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CShowTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	SetControlInfo(IDC_Popup, ANCHORE_RIGHT);
	SetControlInfo(IDC_Maximize, ANCHORE_RIGHT);
	SetControlInfo(IDC_ShowTest_List, RESIZE_BOTH);
}


void CShowTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowTestDlg)
	DDX_Control(pDX, IDC_ShowTest_List, m_showtest_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowTestDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CShowTestDlg)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_ShowTest_List, OnGetdispinfoShowTestList)
	ON_NOTIFY(LVN_ODFINDITEM, IDC_ShowTest_List, OnOdfinditemShowTestList)
	ON_NOTIFY(LVN_ODCACHEHINT, IDC_ShowTest_List, OnOdcachehintShowTestList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowTestDlg message handlers
extern int c[3];
extern TESTTYPE CHIP[3][18];
extern int intChip;
extern BinArray binArray;
extern bool showone;
extern bool showsetting;
extern CArray<CString,CString> dataList;
extern int failItem[3];
int MaxDataNum = 10000;

BOOL CShowTestDlg::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	extern int screen_width, screen_height;
	extern float change_width, change_height;
	extern int after_width, after_height;
	extern int after_top, after_left;

	after_left = (int)(210*change_width);
	after_top = (int)(30*change_height);
	after_width = (int)(845*change_width);
	after_height = (int)(220*change_height);
	MoveWindow(after_left, after_top, after_width, after_height);
	
	m_showtest_list.Init();
	m_showtest_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);//
	Initshowtest();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CShowTestDlg::Initshowtest()
{ 
	int i;
	for(i=0; i<50; i++)
	{
		databuffer[i].RemoveAll();
	}
	m_showtest_list.DeleteAllItems();
	m_showtest_list.DeleteAllColumns();
	m_showtest_list.InsertColumn(0, "Num", LVCFMT_LEFT, 50);
	m_showtest_list.InsertColumn(1, "BIN", LVCFMT_CENTER, 60);
	m_showtest_list.InsertColumn(2, "BinCode", LVCFMT_CENTER, 100);

	CString str, str_item;
	int num = 1;
	int chipnum = 3;
	if(0 == intChip)
	{
		chipnum = 1;
	}
	else if(intChip < 4)
	{
		chipnum = 2;
	}
	for(i=0; i<chipnum; i++)
	{
		for(int j=0; j<c[i]; j++)
		{
			str_item = "NULL";
			sscanf(CHIP[i][j].TestItem, "%[^(]", str_item);
			if(0 == strcmp(str_item, "XYZ"))
			{
				str.Format("C%d-XYZ-X", (i+1));
				m_showtest_list.InsertColumn(num, str, LVCFMT_CENTER, 80);
				num++;
				str.Format("C%d-XYZ-Y", (i+1));
				m_showtest_list.InsertColumn(num, str, LVCFMT_CENTER, 80);
				num++;
			}
			else if(0 == strcmp(str_item, "IR"))
			{
				str.Format("C%d-%s", (i+1), CHIP[i][j].TestItem);
				m_showtest_list.InsertColumn(num, str, LVCFMT_CENTER, 90);
				num++;
			}
			else
			{
				str.Format("C%d-%s", (i+1), CHIP[i][j].TestItem);
				m_showtest_list.InsertColumn(num, str, LVCFMT_CENTER, 70);
				num++;
			}		
		}
	}
}

void CShowTestDlg::ShowNULL(int chip, int line, int bin)
{
	CString str, str_item;
	int columns = 1;

	str.Format("%d", line+1);
	databuffer[0].Add(str);
	if(databuffer[0].GetSize()>MaxDataNum)
	{
		databuffer[0].RemoveAt(0);
	}

	for(int i=0; i<chip; i++)
	{
		for(int j=0; j<c[i]; j++)
		{
			str = "NULL";
			str_item = "NULL";
			sscanf(CHIP[i][j].TestItem, "%[^(]", str_item);
			if(0 == strcmp(str_item, "XYZ"))
			{
				databuffer[columns++].Add(str);
				databuffer[columns++].Add(str);
				if(databuffer[columns-1].GetSize()>MaxDataNum)
				{
					databuffer[columns-2].RemoveAt(0);
					databuffer[columns-1].RemoveAt(0);
				}
			}
			else
			{	
				databuffer[columns++].Add(str);
				if(databuffer[columns-1].GetSize()>MaxDataNum)
				{
					databuffer[columns-1].RemoveAt(0);
				}
			}
		}
	}
	
	str.Format("%d", bin);
	databuffer[columns++].Add(str);
	str.Format("%s", binArray.binName[bin]);
	databuffer[columns].Add(str);
	if(databuffer[columns-1].GetSize()>MaxDataNum)
	{
		databuffer[columns-1].RemoveAt(0);
		databuffer[columns].RemoveAt(0);
	}
	
	if(showsetting)
	{
		m_showtest_list.SetItemCountEx(databuffer[0].GetSize() + 6);
		m_showtest_list.Invalidate();	
	}
	else
	{
		m_showtest_list.SetItemCountEx(databuffer[0].GetSize());
		m_showtest_list.Invalidate();
	}
}

void CShowTestDlg::ShowResults(int chip, int line, int bin)
{
	CString str, str_item;
	int columns = 1;

	str.Format("%d", line+1);
	databuffer[0].Add(str);
	if(databuffer[0].GetSize()>MaxDataNum)
	{
		databuffer[0].RemoveAt(0);
	}

	for(int i=0; i<chip; i++)
	{
		for(int j=0; j<c[i]; j++)
		{
			str_item = "NULL";
			sscanf(CHIP[i][j].TestItem, "%[^(]", str_item);

			if(j <= failItem[i])
			{
				if(0 == strcmp(str_item, "XYZ"))
				{
					str.Format("%0.4f", CHIP[i][j].XValue);
					databuffer[columns++].Add(str);
					str.Format("%0.4f", CHIP[i][j].YValue);
					databuffer[columns++].Add(str);

					if(databuffer[columns-1].GetSize()>MaxDataNum)
					{
						databuffer[columns-2].RemoveAt(0);
						databuffer[columns-1].RemoveAt(0);
					}
				}
				else
				{
					if((0 == strcmp(str_item, "VF")) 
						|| (0 == strcmp(str_item, "VR"))
						|| (0 == strcmp(str_item, "VZ"))
						|| (0 == strcmp(str_item, "IF"))
						|| (0 == strcmp(str_item, "DVF"))
						|| (0 == strcmp(str_item, "THY"))
						|| (0 == strcmp(str_item, "IV"))
						|| (0 == strcmp(str_item, "IE"))
						|| (0 == strcmp(str_item, "LV"))
						|| (0 == strcmp(str_item, "LE")))
					{
						str.Format("%0.3f", CHIP[i][j].TestValue);
					}
					else if(0 == strcmp(str_item, "IR")) 
					{
						str.Format("%0.6f", CHIP[i][j].TestValue);
					}
					else
					{
						str.Format("%0.2f", CHIP[i][j].TestValue);
					}
					
					databuffer[columns++].Add(str);
					if(databuffer[columns-1].GetSize()>MaxDataNum)
					{
						databuffer[columns-1].RemoveAt(0);
					}
				}
			}
			else
			{
				str = "--";
				if(0 == strcmp(str_item, "XYZ"))
				{
					databuffer[columns++].Add(str);
					databuffer[columns++].Add(str);
					if(databuffer[columns-1].GetSize()>MaxDataNum)
					{
						databuffer[columns-2].RemoveAt(0);
						databuffer[columns-1].RemoveAt(0);
					}
				}
				else
				{	
					databuffer[columns++].Add(str);
					if(databuffer[columns-1].GetSize()>MaxDataNum)
					{
						databuffer[columns-1].RemoveAt(0);
					}
				}
			}
		}
	}

	str.Format("%d", bin);
	databuffer[columns++].Add(str);
	str.Format("%s", binArray.binName[bin]);
	databuffer[columns].Add(str);
	if(databuffer[columns-1].GetSize()>MaxDataNum)
	{
		databuffer[columns-1].RemoveAt(0);
		databuffer[columns].RemoveAt(0);
	}
	
	if(showone)
	{
		if(showsetting)
		{
			m_showtest_list.SetItemCountEx(7);	
		}
		else
		{
			m_showtest_list.SetItemCountEx(1);
		}
	}
	else
	{
		if(databuffer[0].GetSize() > 1000)
		{
			if(showsetting)
			{
				m_showtest_list.SetItemCountEx(1006);	
			}
			else
			{
				m_showtest_list.SetItemCountEx(1000);
			}
		}
		else
		{
			if(showsetting)
			{
				m_showtest_list.SetItemCountEx(databuffer[0].GetSize() + 6);
				//		m_showtest_list.EnsureVisible(line+7, false);	
			}
			else
			{
				m_showtest_list.SetItemCountEx(databuffer[0].GetSize());
				//		m_showtest_list.EnsureVisible(line, false);
				//		m_showtest_list.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			}
		}
	}

	m_showtest_list.Invalidate();
}

void CShowTestDlg::ShowSetting(int chip, int count)
{
	CString str;
	int columns = 1;
	int i=0, j=0;

	settingbuffer[0][0] = "V";
	settingbuffer[1][0] = "I";
	settingbuffer[2][0] = "Delay";
	settingbuffer[3][0] = "Min";
	settingbuffer[4][0] = "Max";
	settingbuffer[5][0] = "Fail";
	
	for(i=0; i<chip; i++)
	{
		for(j=0; j<c[i]; j++)
		{	
			str.Format("%0.1f", CHIP[i][j].VCom);
			settingbuffer[0][columns] = str;
			str.Format("%0.1f", CHIP[i][j].ICom);
			settingbuffer[1][columns] = str;
			str.Format("%d", CHIP[i][j].Delay);
			settingbuffer[2][columns] = str;
			str.Format("%d", CHIP[i][j].Fail);
			settingbuffer[5][columns] = str;
			if(0 == strcmp(CHIP[i][j].TestItem, "XYZ"))
			{
				settingbuffer[3][columns] = "NULL";
				settingbuffer[3][columns] = "";
				settingbuffer[4][columns] = "NULL";
				settingbuffer[4][columns] = "";
				columns ++;
				settingbuffer[0][columns] = "NULL";
				settingbuffer[0][columns] = "";
				settingbuffer[1][columns] = "NULL";
				settingbuffer[1][columns] = "";
				settingbuffer[2][columns] = "NULL";
				settingbuffer[2][columns] = "";
				settingbuffer[3][columns] = "NULL";
				settingbuffer[3][columns] = "";
				settingbuffer[4][columns] = "NULL";
				settingbuffer[4][columns] = "";
				settingbuffer[5][columns] = "NULL";
				settingbuffer[5][columns] = "";
				columns ++;
			}
			else
			{
				str.Format("%0.3f", CHIP[i][j].Lower);
				settingbuffer[3][columns] = str;
				str.Format("%0.3f", CHIP[i][j].Upper);
				settingbuffer[4][columns++] = str;
			}
		}
	}

	for(i=0; i<6; i++)
	{
		for(j=0; j<2; j++)
		{
			settingbuffer[i][columns+j] = "NULL";
			settingbuffer[i][columns+j] = "";
		}
	}

	m_showtest_list.SetItemCountEx(count + 6);
	m_showtest_list.Invalidate();
//	m_showtest_list.EnsureVisible(count + 6, true);
}

void CShowTestDlg::Saveshowtest()
{
	dataList.RemoveAll();
	CString str, string;
	int line = 0, column = 0;
	column = m_showtest_list.GetHeaderCtrl()->GetItemCount();
	line = databuffer[0].GetSize();//m_showtest_list.GetItemCount();
	if(showsetting)
	{
		line -= 6;
	}
	
	for(int i=0; i<line; i++)
	{
		string = "";
		for(int j=0; j<column; j++)
		{
			str = databuffer[j][i];//m_showtest_list.GetItemText(i, j);
			string += str + ",    ";
		}
		dataList.Add(string);
	}
}

void CShowTestDlg::OnGetdispinfoShowTestList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	LV_ITEM* pItem = &(pDispInfo)->item;
	
	if(pItem->mask & LVIF_TEXT)
	{   
		if(showsetting)
		{
			if(pItem->iItem < 6)
			{
				lstrcpy(pItem->pszText, settingbuffer[pItem->iItem][pItem->iSubItem]);
			}
			else
			{
				lstrcpy(pItem->pszText, databuffer[pItem->iSubItem].GetAt(databuffer[0].GetSize()-pItem->iItem+5));
			}
		}
		else
		{
			lstrcpy(pItem->pszText, databuffer[pItem->iSubItem].GetAt(databuffer[0].GetSize()-pItem->iItem-1));
		}
	}
	
	*pResult = 0;
}

void CShowTestDlg::OnOdfinditemShowTestList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLVFINDITEM* pFindInfo = (NMLVFINDITEM*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CShowTestDlg::OnOdcachehintShowTestList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLVCACHEHINT* pCacheHint = (NMLVCACHEHINT*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

BOOL CShowTestDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
//	return CResizingDialog::OnEraseBkgnd(pDC);
	return true;
}

HBRUSH CShowTestDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CResizingDialog::OnCtlColor(pDC, pWnd, nCtlColor);	
	// TODO: Change any attributes of the DC here
	// TODO: Return a different brush if the default is not desired
	return hbr;
}


BOOL CShowTestDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_F5:
			return true;
		}
	}
	return CResizingDialog::PreTranslateMessage(pMsg);
}
