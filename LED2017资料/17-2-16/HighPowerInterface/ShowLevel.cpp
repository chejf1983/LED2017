// ShowLevel.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "ShowLevel.h"
//#include "Functions.h"
#include "HighPowerInterfaceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ShowLevel dialog


ShowLevel::ShowLevel(CWnd* pParent /*=NULL*/)
	: CDialog(ShowLevel::IDD, pParent)
{
	//{{AFX_DATA_INIT(ShowLevel)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ShowLevel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ShowLevel)
	DDX_Control(pDX, IDC_temptest, m_temptest);
	DDX_Control(pDX, IDC_outboxnum, m_outboxnum);
	DDX_Control(pDX, IDC_outboxdetail, m_outboxdetail);
	DDX_Control(pDX, IDC_tempcode, m_tempcode);
	DDX_Control(pDX, IDC_CodeFromHardware, m_codefromhardware);
	DDX_Control(pDX, IDC_BoxFullNum, m_boxfullnum);
	DDX_Control(pDX, IDC_feedingClowNum, m_feedingClowNum);
	DDX_Control(pDX, IDC_NumInBox, m_numInBox);
	DDX_Control(pDX, IDC_StopClear, m_stopclear);
	DDX_Control(pDX, IDC_StartClear, m_startclear);
	DDX_Control(pDX, IDC_BinMapList, m_binmaplist);
	DDX_Control(pDX, IDC_offsetList, m_offsetlist);
	DDX_Control(pDX, IDC_levellist, m_levellist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ShowLevel, CDialog)
	//{{AFX_MSG_MAP(ShowLevel)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_StartClear, OnStartClear)
	ON_BN_CLICKED(IDC_StopClear, OnStopClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ShowLevel message handlers
extern bool engineer;
extern SystemSet systemset;
extern BinArray binArray;
extern int columns[3];
extern int binBox[MAXBIN][2];
extern CArray<int, int>feedingClowBox;
extern int MaxLedNum;
extern unsigned char read_data[1024];
CString str_showcode;

BOOL ShowLevel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(engineer)
	{
		MoveWindow(100, 120, 800, 700);
	}
	else
	{
		MoveWindow(100, 60, 800, 500);
	}

	m_levellist.Init();
	m_binmaplist.Init();

	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 20;
	strcpy(lf.lfFaceName, "Verdana");
	font.CreateFontIndirect(&lf);
		
	m_levellist.SetFont(&font, TRUE);
	m_levellist.SetReadOnlyColumns(0);
	m_levellist.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	
	m_binmaplist.SetFont(&font, TRUE);
	m_binmaplist.SetReadOnlyColumns(0);
	m_binmaplist.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	m_numInBox.SetFont(&font, TRUE);
	m_numInBox.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	m_feedingClowNum.SetFont(&font, TRUE);
	m_feedingClowNum.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	InitBinMapList();
	initdlg();
	initoffsetlist();
	InitExchangeParam();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ShowLevel::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

bool ShowLevel::InitExchangeParam()
{
	int i = 0;
	CString str;

	m_numInBox.InsertColumn(0, "BoxNO.", LVCFMT_CENTER, 100);
	m_numInBox.InsertColumn(1, "Num", LVCFMT_CENTER, 100);

	for(i=0; i<80; i++)
	{
		str.Format("%d", i);
		m_numInBox.InsertItem(i, str);
	}

	m_feedingClowNum.InsertColumn(0, "ClowNO.", LVCFMT_CENTER, 100);
	m_feedingClowNum.InsertColumn(1, "BoxNO.", LVCFMT_CENTER, 100);
	for(i=0; i<105; i++)
	{
		str.Format("%d", i);
		m_feedingClowNum.InsertItem(i, str);
	}

	return true;
}

bool ShowLevel::UpdataExchangeParam()
{
	int i = 0;
	CString str;

	str = str_showcode;
	m_codefromhardware.SetWindowText(str);

	str.Format("%d", MaxLedNum);
	m_boxfullnum.SetWindowText(str);

	for(i=0; i<80; i++)
	{
		str.Format("%d", binBox[i][1]);
		m_numInBox.SetItemText(i, 1, str);
	}

	for(i=0; i<105; i++)
	{
		str.Format("%d", feedingClowBox[i]);
		m_feedingClowNum.SetItemText(i, 1, str);
	}

	return true;
}

bool ShowLevel::initoffsetlist()
{
	CString str;
	m_offsetlist.InsertColumn(0, "NUM", LVCFMT_CENTER, 100);
	m_offsetlist.InsertColumn(1, "VF", LVCFMT_CENTER, 100);
	m_offsetlist.InsertColumn(2, "VFOffset", LVCFMT_CENTER, 100);
	m_offsetlist.InsertColumn(3, "VR", LVCFMT_CENTER, 100);
	m_offsetlist.InsertColumn(4, "VROffset", LVCFMT_CENTER, 100);
	
	for(int i=0; i<11; i++)
	{
		str.Format("%d", i+1);
		m_offsetlist.InsertItem(i, str);
		str.Format("%f", outportResult(true, i));
		m_offsetlist.SetItemText(i, 1, str);
		str.Format("%f", outportOffset(true, i));
		m_offsetlist.SetItemText(i, 2, str);
		str.Format("%f", outportResult(false, i));
		m_offsetlist.SetItemText(i, 3, str);
		str.Format("%f", outportOffset(false, i));
		m_offsetlist.SetItemText(i, 4, str);
	}

	return true;
}

bool ShowLevel::InitBinMapList()
{
	CString str;

	m_binmaplist.InsertColumn(0, "料盒", LVCFMT_CENTER, 50);
	m_binmaplist.InsertColumn(1, "数    量", LVCFMT_CENTER, 100);
	m_binmaplist.InsertColumn(2, "对应Bin", LVCFMT_CENTER, 70);

	for(int i=0; i<systemset.intMachineType; i++)
	{
		str.Format("%d", i);
		m_binmaplist.InsertItem(i+1, str);
	}

	return true;
}

bool ShowLevel::SetBinMapList()
{
	CString str;
	
	for(int i=0; i<systemset.intMachineType; i++)
	{	
		if(binBox[i][1] > 0)
		{
			str.Format("%d", binBox[i][1]);	
			m_binmaplist.SetItemText(i, 1, str);
			
			if(binBox[i][0] < 80)
			{
				str.Format("%d", binBox[i][0]);
			}
			else
			{
				str = "";
			}
			m_binmaplist.SetItemText(i, 2, str);
		}
		else
		{
			str = "";
			m_binmaplist.SetItemText(i, 1, str);
			m_binmaplist.SetItemText(i, 2, str);
		}	
	}
	
	return true;
}

bool ShowLevel::updataBinMapList(int bin)
{
	CString str;

	if(binBox[bin][1] > 0)
	{
		str.Format("%d", binBox[bin][1]);
		m_binmaplist.SetItemText(bin, 1, str);
		
		if(binBox[bin][0] < 80)
		{
			str.Format("%d", binBox[bin][0]);
		}
		else
		{
			str = "";
		}
		m_binmaplist.SetItemText(bin, 2, str);
	}
	else
	{
		str = "";
		m_binmaplist.SetItemText(bin, 1, str);
		m_binmaplist.SetItemText(bin, 2, str);
	}
	
	return true;
}

bool ShowLevel::initdlg()
{
	int i;
	int chip = 1;
	int totalnum = 0;
	CString str_item, str;
	
	m_levellist.DeleteAllItems();
	m_levellist.DeleteAllColumns();

	m_levellist.InsertColumn(0, "BIN", LVCFMT_CENTER, 45);
	m_levellist.InsertColumn(1, "BinCode", LVCFMT_CENTER, 100);
	m_levellist.InsertItem(0, "BIN");
	m_levellist.SetItemText(0, 1, "BinCode");
	
	for(i=0; i<systemset.intMachineType; i++)
	{
		str.Format("%d", i);
		m_levellist.InsertItem(i+1, str);
		m_levellist.SetItemText(i+1, 1, "");
		m_levellist.SetItemText(i+1, 1, binArray.binName[i]);
	}

	totalnum = columns[0] + columns[1] + columns[2];

	for(i=0; i<totalnum; i+=2)
	{
		sscanf(binArray.strBinArray[0][i], "C%d-%[^(]", &chip, str_item);
		chip --;
		
		insertIteminit(binArray.strBinArray[0][i]);
		
		if(0 == strcmp(str_item, "XYZ"))
		{
			i += 6;
		}
	}

	int nCount = m_levellist.GetHeaderCtrl()->GetItemCount();
	for(i=1; i <= systemset.intMachineType; i++)
	{
		for(int j=1; j<(nCount-1); j++)
		{
			m_levellist.SetItemText(i, j+1, ReformatString(binArray.strBinArray[i][j-1]));
		}
	}

	return true;
}

bool ShowLevel::insertIteminit(CString text)
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

void ShowLevel::OnStartClear() 
{
	// TODO: Add your control notification handler code here
	CHighPowerInterfaceDlg *pmain = (CHighPowerInterfaceDlg*)GetParent();
	pmain->OnStartClearBox();
}

void ShowLevel::OnStopClear() 
{
	// TODO: Add your control notification handler code here
	CHighPowerInterfaceDlg *pmain = (CHighPowerInterfaceDlg*)GetParent();
	pmain->OnStopClearBox();
}

BOOL ShowLevel::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBitmap bmp;
	CBitmap *ptrBmpOld;
	BITMAP bm;
	
	bmp.LoadBitmap(IDB_SettingBK);
	bmp.GetBitmap(&bm);
	
	CRect rect;
	GetClientRect(rect);
	
	int w,h;
	w=rect.Width()/bm.bmWidth+1;
	h=rect.Height()/bm.bmHeight+1;
	
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	ptrBmpOld=dcMemory.SelectObject(&bmp);
	
	for(int i=0;i<w;i++)
	{
		for(int j=0;j<h;j++)
		{
			pDC->BitBlt
				(
				i*bm.bmWidth,
				j*bm.bmHeight,
				bm.bmWidth,
				bm.bmHeight,
				&dcMemory,
				10,
				40,
				SRCCOPY
				);
		}
	}	

	return true;
//	return CDialog::OnEraseBkgnd(pDC);
}


