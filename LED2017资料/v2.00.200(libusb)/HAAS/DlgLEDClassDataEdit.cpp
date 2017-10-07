// DlgLEDClassDataEdit.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgLEDClassDataEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLEDClassDataEdit dialog


extern BOOL g_bEnglish;

CDlgLEDClassDataEdit::CDlgLEDClassDataEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLEDClassDataEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLEDClassDataEdit)
	m_fD1 = 0.0f;
	m_fD2 = 0.0f;
	m_strName = _T("New Class");
	//}}AFX_DATA_INIT
	m_bMod = FALSE;
}


void CDlgLEDClassDataEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLEDClassDataEdit)
	DDX_Control(pDX, IDC_COLOR, m_cColor);
	DDX_Control(pDX, IDC_BUTTON_MOD, m_cMod);
	DDX_Control(pDX, IDC_EDIT_D2, m_cD2);
	DDX_Control(pDX, IDC_EDIT_D1, m_cD1);
	DDX_Control(pDX, IDC_LIST, m_cList);
	DDX_Text(pDX, IDC_EDIT_D1, m_fD1);
	DDX_Text(pDX, IDC_EDIT_D2, m_fD2);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLEDClassDataEdit, CDialog)
	//{{AFX_MSG_MAP(CDlgLEDClassDataEdit)
	ON_BN_CLICKED(IDC_BUTTON_MOD, OnButtonMod)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	ON_EN_CHANGE(IDC_EDIT_NAME, OnChangeEditName)
	ON_BN_CLICKED(IDC_COLOR, OnColor)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLEDClassDataEdit message handlers

void CDlgLEDClassDataEdit::OnButtonMod() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	int iSele = m_cList.GetCurSel();
	if(iSele >= 0 && iSele < m_iListType.GetSize())
	{
		if(m_fD1 < m_fD2)
		{
			m_fLimit1[iSele] = m_fD1;
			m_fLimit2[iSele] = m_fD2;
		}
		else
		{
			m_fLimit1[iSele] = m_fD2;
			m_fLimit2[iSele] = m_fD1;
		}
		ReList();

		m_bMod = TRUE;
	}	
}

BOOL CDlgLEDClassDataEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	ReList();

	OnSelchangeList();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLEDClassDataEdit::ReList()
{
	int iSele = m_cList.GetCurSel();
	m_cList.ResetContent();

	CString strTemp1;
	CString strTemp2;

	for(int i = 0; i < m_iListType.GetSize(); i++)
	{
		strTemp1 = CLimitData::Type2NameStr(m_iListType[i]);
		int NN = strTemp1.GetLength();
		for(int t = 0; t < 20 - NN; t++)
			strTemp1 += " ";

		strTemp2.Format("%g - %g",m_fLimit1[i],m_fLimit2[i]);
		m_cList.AddString(strTemp1 + strTemp2);
	}

	if(iSele < 0)
		iSele = 0;
	m_cList.SetCurSel(iSele);
}

void CDlgLEDClassDataEdit::OnCancel() 
{
	// TODO: Add extra cleanup here
	int iR;
	if(m_bMod)
	{
		if(g_bEnglish)
			iR = MessageBox("Are you sure?",NULL,MB_ICONINFORMATION|MB_OKCANCEL);
		else
			iR = MessageBox("确定取消?",NULL,MB_ICONINFORMATION|MB_OKCANCEL);
		if(iR == IDCANCEL)
			return;
	}

	CDialog::OnCancel();
}

void CDlgLEDClassDataEdit::OnSelchangeList() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int iSele = m_cList.GetCurSel();
	if(iSele >= 0 && iSele < m_iListType.GetSize())
	{
		m_cD1.EnableWindow(TRUE);
		m_cD2.EnableWindow(TRUE);
		m_cMod.EnableWindow(TRUE);

		m_fD1 = m_fLimit1[iSele];
		m_fD2 = m_fLimit2[iSele];

		UpdateData(FALSE);
	}
	else
	{
		m_cD1.EnableWindow(FALSE);
		m_cD2.EnableWindow(FALSE);
		m_cMod.EnableWindow(FALSE);
	}
}

void CDlgLEDClassDataEdit::OnChangeEditName() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_bMod = TRUE;
}

void CDlgLEDClassDataEdit::OnColor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg(m_color);
	if(dlg.DoModal() == IDCANCEL)
		return;
	m_color = dlg.GetColor();
	Invalidate(TRUE);
}

void CDlgLEDClassDataEdit::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
	
	CDC *pDC = m_cColor.GetDC();
	m_cColor.Invalidate();
	m_cColor.UpdateWindow();

	CRect colorRect;
	m_cColor.GetClientRect(colorRect);
	CBrush brush;
	brush.CreateSolidBrush(m_color);
	pDC->FillRect(colorRect, &brush);
	CString strTemp;
	pDC->SetBkMode(TRANSPARENT);
	COLORREF color2 = (DWORD)(~m_color) & 0xFFFFFF;
	pDC->SetTextColor(color2);

	strTemp.Format("RGB=(%d,%d,%d)", GetRValue(m_color), GetGValue(m_color), GetBValue(m_color));
	pDC->DrawText(strTemp, colorRect, DT_CENTER);

	m_cColor.ReleaseDC(pDC);
}
