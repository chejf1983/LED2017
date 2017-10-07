// BinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HighPowerInterface.h"
#include "BinDlg.h"
#include "Functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBinDlg dialog


CBinDlg::CBinDlg(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CBinDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBinDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	SetControlInfo(IDC_Bin_List, RESIZE_BOTH);
	SetControlInfo(ID_ShowBinNum, RESIZE_HOR);
}


void CBinDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBinDlg)
	DDX_Control(pDX, ID_ShowBinNum, m_BinNum);
	DDX_Control(pDX, IDC_Bin_List, m_bin_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBinDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CBinDlg)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
//	ON_NOTIFY(LVN_ODCACHEHINT, IDC_Bin_List, OnOdcachehintBinList)
//	ON_NOTIFY(LVN_ODFINDITEM, IDC_Bin_List, OnOdfinditemBinList)
//	ON_NOTIFY(LVN_GETDISPINFO, IDC_Bin_List, OnGetdispinfoBinList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBinDlg message handlers
extern SystemSet systemset;
extern CString BinData[MAXBIN][2];
extern int binnum[MAXBIN];
extern LEDNumStatistic ledStatistic;
extern BinArray binArray;

BOOL CBinDlg::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	extern int screen_width, screen_height;
	extern float change_width, change_height;
	extern int after_width, after_height;
	extern int after_top, after_left;
	
	after_left = (int)(1060*change_width);
	after_top = (int)(30*change_height);
	after_width = (int)(210*change_width);
	after_height = (int)(637*change_height);
	MoveWindow(after_left, after_top, after_width, after_height);

	m_bin_list.Init();
	m_bin_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	m_BinNum.SetBitmaps(IDB_BinNum2, IDB_BinNum2, IDB_BinNum2, IDB_BinNum2);
	m_BinNum.SizeToContent();
	m_BinNum.SetDrawText(true, false)
			.SetFont3D(true, 3, 2, false)
		    .SetFontSize(28, false)
			.SetForceColor(RGB(255, 255, 255), RGB(255, 255, 255), RGB(255, 255, 255), false);


	Initbin();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBinDlg::Initbin()
{
	if(systemset.intMachineType != m_bin_list.GetItemCount())
	{
		CString str;
		int i = 0;

		str.Format("       %d", systemset.intMachineType);
//		SetDlgItemText(ID_ShowBinNum, str);
		m_BinNum.SetWindowText(TEXT(str));
		
		m_bin_list.InsertColumn(0, "BIN", LVCFMT_LEFT, 30);
		m_bin_list.InsertColumn(1, "Num", LVCFMT_CENTER, 50);
		m_bin_list.InsertColumn(2, "Percent", LVCFMT_CENTER, 75);
		m_bin_list.DeleteAllItems();

	    for(i=0; i<systemset.intMachineType; i++)
		{
			str.Format("%d", i);
			m_bin_list.InsertItem(i,str);
		}
	}
}

void CBinDlg::Savebin()
{
	for(int i=0; i<systemset.intMachineType; i++)
	{
		BinData[i][0] = m_bin_list.GetItemText(i, 1);
		BinData[i][1] = m_bin_list.GetItemText(i, 2);
	}
}

void CBinDlg::ShowResults()
{
	CString str;
	double percent = 0; 

	for(int i=0; i<systemset.intMachineType; i++)
	{
		percent = 0;
		str.Format("%d", binnum[i]);
		m_bin_list.SetItemText(i, 1, str);

		if((binnum[i] != 0) && (ledStatistic.ledtotalnum > 1))
		{
			percent = (double)binnum[i] / (ledStatistic.ledtotalnum - 1);
		}
		str.Format("%0.1f", percent * 100);
		m_bin_list.SetItemText(i, 2, str);
	}
}

void CBinDlg::UpdateData(int bin)
{
	CString str;
	double percent = 0;

	str.Format("%d", binnum[bin]);
	m_bin_list.SetItemText(bin, 1, str);
}

BOOL CBinDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
//	return CResizingDialog::OnEraseBkgnd(pDC);
	return true;
}

HBRUSH CBinDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CResizingDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL CBinDlg::PreTranslateMessage(MSG* pMsg) 
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

void CBinDlg::OnGetdispinfoBinList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	LV_ITEM* pItem = &(pDispInfo)->item;

	if(pItem->mask & LVIF_TEXT)
	{   		
//		lstrcpy(pItem->pszText, databuffer[pItem->iSubItem][pItem->iItem]);		
	}

	*pResult = 0;
}

void CBinDlg::OnOdcachehintBinList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLVCACHEHINT* pCacheHint = (NMLVCACHEHINT*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CBinDlg::OnOdfinditemBinList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLVFINDITEM* pFindInfo = (NMLVFINDITEM*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
