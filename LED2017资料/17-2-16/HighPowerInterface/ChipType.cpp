// ChipType.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "ChipType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChipType dialog


CChipType::CChipType(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CChipType::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChipType)
	//}}AFX_DATA_INIT
}


void CChipType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChipType)
	DDX_Control(pDX, IDC_type16, m_type16);
	DDX_Control(pDX, IDC_type15, m_type15);
	DDX_Control(pDX, IDC_type14, m_type14);
	DDX_Control(pDX, IDC_type13, m_type13);
	DDX_Control(pDX, IDC_type12, m_type12);
	DDX_Control(pDX, IDC_type11, m_type11);
	DDX_Control(pDX, IDC_type17, m_type17);
	DDX_Control(pDX, IDC_type10, m_type10);
	DDX_Control(pDX, IDC_type9, m_type9);
	DDX_Control(pDX, IDC_type8, m_type8);
	DDX_Control(pDX, IDC_type7, m_type7);
	DDX_Control(pDX, IDC_type6, m_type6);
	DDX_Control(pDX, IDC_type5, m_type5);
	DDX_Control(pDX, IDC_type4, m_type4);
	DDX_Control(pDX, IDC_type3, m_type3);
	DDX_Control(pDX, IDC_type2, m_type2);
	DDX_Control(pDX, IDC_type1, m_type1);
	DDX_Control(pDX, IDC_type0, m_type0);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChipType, CResizingDialog)
	//{{AFX_MSG_MAP(CChipType)
	ON_BN_CLICKED(IDC_type0, Ontype0)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_type1, Ontype1)
	ON_BN_CLICKED(IDC_type2, Ontype2)
	ON_BN_CLICKED(IDC_type3, Ontype3)
	ON_BN_CLICKED(IDC_type4, Ontype4)
	ON_BN_CLICKED(IDC_type5, Ontype5)
	ON_BN_CLICKED(IDC_type6, Ontype6)
	ON_BN_CLICKED(IDC_type7, Ontype7)
	ON_BN_CLICKED(IDC_type8, Ontype8)
	ON_BN_CLICKED(IDC_type9, Ontype9)
	ON_BN_CLICKED(IDC_type10, Ontype10)
	ON_BN_CLICKED(IDC_type11, Ontype11)
	ON_BN_CLICKED(IDC_type12, Ontype12)
	ON_BN_CLICKED(IDC_type13, Ontype13)
	ON_BN_CLICKED(IDC_type14, Ontype14)
	ON_BN_CLICKED(IDC_type15, Ontype15)
	ON_BN_CLICKED(IDC_type16, Ontype16)
	ON_BN_CLICKED(IDC_type17, Ontype17)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChipType message handlers
extern int tempchiptype;
extern int tempChip;
extern int tempPolarity;
BOOL CChipType::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	MoveWindow(140, 180, 370, 230);
	InitButton();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChipType::InitButton()
{
	///////Ö±²å
	m_type0.SetBitmaps(IDB_SmallZ21, IDB_SmallZ21, IDB_SmallZ21, IDB_SmallZ21);
	m_type1.SetBitmaps(IDB_SmallZ22, IDB_SmallZ22, IDB_SmallZ22, IDB_SmallZ22);
	m_type2.SetBitmaps(IDB_SmallZ3200, IDB_SmallZ3200, IDB_SmallZ3200, IDB_SmallZ3200);
	m_type3.SetBitmaps(IDB_SmallZ3201, IDB_SmallZ3201, IDB_SmallZ3201, IDB_SmallZ3201);
	m_type4.SetBitmaps(IDB_SmallZ3210, IDB_SmallZ3210, IDB_SmallZ3210, IDB_SmallZ3210);
	m_type5.SetBitmaps(IDB_SmallZ3211, IDB_SmallZ3211, IDB_SmallZ3211, IDB_SmallZ3211);
	m_type6.SetBitmaps(IDB_SmallZ4300, IDB_SmallZ4300, IDB_SmallZ4300, IDB_SmallZ4300);
	m_type7.SetBitmaps(IDB_SmallZ4301, IDB_SmallZ4301, IDB_SmallZ4301, IDB_SmallZ4301);
	m_type8.SetBitmaps(IDB_SmallZ4310, IDB_SmallZ4310, IDB_SmallZ4310, IDB_SmallZ4310);
	m_type9.SetBitmaps(IDB_SmallZ4311, IDB_SmallZ4311, IDB_SmallZ4311, IDB_SmallZ4311);

	///////ÌùÆ¬
	m_type10.SetBitmaps(IDB_SmallT21, IDB_SmallT21, IDB_SmallT21, IDB_SmallT21);
	m_type11.SetBitmaps(IDB_SmallT22, IDB_SmallT22, IDB_SmallT22, IDB_SmallT22);
	m_type12.SetBitmaps(IDB_SmallT42, IDB_SmallT42, IDB_SmallT42, IDB_SmallT42);
	m_type13.SetBitmaps(IDB_SmallT430A, IDB_SmallT430A, IDB_SmallT430A, IDB_SmallT430A);
	m_type14.SetBitmaps(IDB_SmallT430B, IDB_SmallT430B, IDB_SmallT430B, IDB_SmallT430B);
	m_type15.SetBitmaps(IDB_SmallT431A, IDB_SmallT431A, IDB_SmallT431A, IDB_SmallT431A);
	m_type16.SetBitmaps(IDB_SmallT431B, IDB_SmallT431B, IDB_SmallT431B, IDB_SmallT431B);
	m_type17.SetBitmaps(IDB_SmallT63, IDB_SmallT63, IDB_SmallT63, IDB_SmallT63);
}

void CChipType::Ontype0() 
{
	// TODO: Add your control notification handler code here
	tempchiptype = 0;
	tempChip = 0;
	tempPolarity = -1;
	OnClose();
}

void CChipType::Ontype1() 
{
	// TODO: Add your control notification handler code here
	tempchiptype = 1;
	tempChip = 1;
	tempPolarity = -1;
	OnClose();
}

void CChipType::Ontype2() 
{
	// TODO: Add your control notification handler code here
	tempchiptype = 2;
	tempChip = 2;
	tempPolarity = 0;
	OnClose();
}

void CChipType::Ontype3() 
{
	// TODO: Add your control notification handler code here
	tempchiptype = 3;
	tempChip = 2;
	tempPolarity = 0;
	OnClose();
}

void CChipType::Ontype4() 
{
	// TODO: Add your control notification handler code here
	tempchiptype = 4;
	tempChip = 2;
	tempPolarity = 1;
	OnClose();
}

void CChipType::Ontype5() 
{
	// TODO: Add your control notification handler code here
	tempchiptype = 5;
	tempChip = 2;
	tempPolarity = 1;
	OnClose();
}

void CChipType::Ontype6() 
{
	// TODO: Add your control notification handler code here
	tempchiptype = 6;
	tempChip = 4;
	tempPolarity = 0;
	OnClose();
}

void CChipType::Ontype7() 
{
	// TODO: Add your control notification handler code here
	tempchiptype = 7;
	tempChip = 4;
	tempPolarity = 0;
	OnClose();
}

void CChipType::Ontype8() 
{
	// TODO: Add your control notification handler code here
	tempchiptype = 8;
	tempChip = 4;
	tempPolarity = 1;
	OnClose();
}

void CChipType::Ontype9() 
{
	// TODO: Add your control notification handler code here
	tempchiptype = 9;
	tempChip = 4;
	tempPolarity = 1;
	OnClose();
}

void CChipType::Ontype10() 
{
	// TODO: Add your control notification handler code here
	tempchiptype = 10;
	tempChip = 0;
	tempPolarity = -1;
	OnClose();
}

void CChipType::Ontype11() 
{
	// TODO: Add your control notification handler code here
	tempchiptype = 11;
	tempChip = 1;
	tempPolarity = -1;
	OnClose();
}

void CChipType::Ontype12() 
{
	// TODO: Add your control notification handler code here
	tempchiptype = 12;
	tempChip = 3;
	tempPolarity = -1;
	OnClose();
}

void CChipType::Ontype13() 
{
	// TODO: Add your control notification handler code here
	tempchiptype = 13;
	tempChip = 4;
	tempPolarity = 0;
	OnClose();
}

void CChipType::Ontype14() 
{
	// TODO: Add your control notification handler code here
	tempchiptype = 14;
	tempChip = 4;
	tempPolarity = 0;
	OnClose();
}

void CChipType::Ontype15() 
{
	// TODO: Add your control notification handler code here
	tempchiptype = 15;
	tempChip = 4;
	tempPolarity = 1;
	OnClose();
}

void CChipType::Ontype16() 
{
	// TODO: Add your control notification handler code here
	tempchiptype = 16;
	tempChip = 4;
	tempPolarity = 1;
	OnClose();
}

void CChipType::Ontype17() 
{
	// TODO: Add your control notification handler code here
	tempchiptype = 17;
	tempChip = 5;
	tempPolarity = -1;
	OnClose();
}


BOOL CChipType::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return CResizingDialog::DrawBK(pDC, IDB_TypeBK, 0);
//	return CResizingDialog::OnEraseBkgnd(pDC);
}

