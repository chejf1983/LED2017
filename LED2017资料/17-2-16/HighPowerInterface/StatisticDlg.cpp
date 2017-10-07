// StatisticDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HighPowerInterface.h"
#include "StatisticDlg.h"
#include "Functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatisticDlg dialog
CStatisticDlg::CStatisticDlg(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CStatisticDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatisticDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	SetControlInfo(IDC_Average, ANCHORE_RIGHT);
	SetControlInfo(IDC_Statistic_List, RESIZE_BOTH);
}


void CStatisticDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatisticDlg)
	DDX_Control(pDX, IDC_Statistic_List, m_statistic_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatisticDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CStatisticDlg)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatisticDlg message handlers
extern int c[3];
extern TESTTYPE CHIP[3][18];
extern int intChip;
extern LEDNumStatistic ledStatistic;
extern CString StatisticData[3][54];

BOOL CStatisticDlg::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	extern int screen_width, screen_height;
	extern float change_width, change_height;
	extern int after_width, after_height;
	extern int after_top, after_left;

	after_left = (int)(210*change_width);
	after_top = (int)(248*change_height);
	after_width = (int)(845*change_width);
	after_height = (int)(85*change_height);
	MoveWindow(after_left, after_top, after_width, after_height);

	m_statistic_list.Init();
	m_statistic_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	Initstatistics();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStatisticDlg::Initstatistics()
{
	m_statistic_list.DeleteAllItems();
	m_statistic_list.DeleteAllColumns();
	m_statistic_list.InsertColumn(0, "", LVCFMT_LEFT, 80);
	m_statistic_list.InsertItem(0, "最小值");
	m_statistic_list.InsertItem(1, "最大值");
	m_statistic_list.InsertItem(2, "平均值");

	int num = 1;
	CString str, str_item;
	int chipnum = 2;
	if(0 == intChip)
	{
		chipnum = 0;
	}
	else if(intChip < 4)
	{
		chipnum = 1;
	}

	chipnum += 1;
	for(int i=0; i<chipnum; i++)
	{
		for(int j=0; j<c[i]; j++)
		{
			str_item = "NULL";
			sscanf(CHIP[i][j].TestItem, "%[^(]", str_item);

			if(0 == strcmp(str_item, "XYZ"))
			{
				str.Format("C%d-XYZ-X", (i+1));
				m_statistic_list.InsertColumn(num, str, LVCFMT_CENTER, 80);
				num++;
				str.Format("C%d-XYZ-Y", (i+1));
				m_statistic_list.InsertColumn(num, str, LVCFMT_CENTER, 80);
				num++;
			}
			else if(0 == strcmp(str_item, "IR"))
			{
				str.Format("C%d-%s", (i+1), CHIP[i][j].TestItem);
				m_statistic_list.InsertColumn(num, str, LVCFMT_CENTER, 90);
				num++;
			}
			else
			{
				str.Format("C%d-%s", (i+1), CHIP[i][j].TestItem);
				m_statistic_list.InsertColumn(num, str, LVCFMT_CENTER, 70);
				num++;
			}			
		}
	}
}

void CStatisticDlg::ShowResults()
{
	int columns = 0;
	CString str[3], str_item;
	
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<c[i]; j++)
		{
			str_item = "NULL";
			sscanf(CHIP[i][j].TestItem, "%[^(]", str_item);

			if(0 == ledStatistic.ledpassnum)
			{
				columns++;
				m_statistic_list.SetItemText(0, columns, "0");
				m_statistic_list.SetItemText(1, columns, "0");
				m_statistic_list.SetItemText(2, columns, "0");
			}
			else
			{
				if(0 == strcmp(str_item, "IR"))
				{
					str[0].Format("%0.6f", CHIP[i][j].min);
					str[1].Format("%0.6f", CHIP[i][j].max);

					CHIP[i][j].average = CHIP[i][j].total / ledStatistic.ledpassnum;
					str[2].Format("%0.6f", CHIP[i][j].average);
				}
				else if((0 == strcmp(str_item, "VF")) 
					|| (0 == strcmp(str_item, "VR"))
					|| (0 == strcmp(str_item, "VZ"))
					|| (0 == strcmp(str_item, "IF"))
					|| (0 == strcmp(str_item, "DVF"))
					|| (0 == strcmp(str_item, "THY")))
				{
					str[0].Format("%0.3f", CHIP[i][j].min);
					str[1].Format("%0.3f", CHIP[i][j].max);
					
					CHIP[i][j].average = CHIP[i][j].total / ledStatistic.ledpassnum;
					str[2].Format("%0.3f", CHIP[i][j].average);
				}
				else if(0 == strcmp(str_item, "XYZ"))
				{
					str[0].Format("%0.4f", CHIP[i][j].min_X);
					str[1].Format("%0.4f", CHIP[i][j].max_X);

					CHIP[i][j].average_X = CHIP[i][j].total_X / ledStatistic.ledpassnum;
					str[2].Format("%0.4f", CHIP[i][j].average_X);
					columns++;
					m_statistic_list.SetItemText(0, columns, str[0]);
					m_statistic_list.SetItemText(1, columns, str[1]);
					m_statistic_list.SetItemText(2, columns, str[2]);
					
					str[0].Format("%0.4f", CHIP[i][j].min_Y);
					str[1].Format("%0.4f", CHIP[i][j].max_Y);

					CHIP[i][j].average_Y = CHIP[i][j].total_Y / ledStatistic.ledpassnum;
					str[2].Format("%0.4f", CHIP[i][j].average_Y);
				}
				else
				{
					str[0].Format("%0.2f", CHIP[i][j].min);
					str[1].Format("%0.2f", CHIP[i][j].max);

					CHIP[i][j].average = CHIP[i][j].total / ledStatistic.ledpassnum;
					str[2].Format("%0.2f", CHIP[i][j].average);
				}

				columns++;
				m_statistic_list.SetItemText(0, columns, str[0]);
				m_statistic_list.SetItemText(1, columns, str[1]);
				m_statistic_list.SetItemText(2, columns, str[2]);
			}
		}
	}
}

void CStatisticDlg::Savestatistics()
{
	int nCount = m_statistic_list.GetHeaderCtrl()->GetItemCount();
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<nCount; j++)
		{
			StatisticData[i][j] = m_statistic_list.GetItemText(i, (j+1));
		}
	}
}

BOOL CStatisticDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
//	return CResizingDialog::OnEraseBkgnd(pDC);
	return true;
}

BOOL CStatisticDlg::PreTranslateMessage(MSG* pMsg) 
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
