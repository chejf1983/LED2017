// SetSpmCompen.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "SetSpmCompen.h"

#include "Functions.h"
#include "Global_MySpecGCS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetSpmCompen property page

IMPLEMENT_DYNCREATE(CSetSpmCompen, CPropertyPage)

CSetSpmCompen::CSetSpmCompen() : CPropertyPage(CSetSpmCompen::IDD)
{
	//{{AFX_DATA_INIT(CSetSpmCompen)
	m_areaway = 1;
	//}}AFX_DATA_INIT
}

CSetSpmCompen::~CSetSpmCompen()
{
}

void CSetSpmCompen::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetSpmCompen)
	DDX_Control(pDX, IDC_CompenList, m_compenlist);
	DDX_Radio(pDX, IDC_AreaWay0, m_areaway);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetSpmCompen, CPropertyPage)
	//{{AFX_MSG_MAP(CSetSpmCompen)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SaveAs, OnSaveAs)
	ON_BN_CLICKED(IDC_AreaWay0, OnAreaWay0)
	ON_BN_CLICKED(IDC_AreaWay1, OnAreaWay1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetSpmCompen message handlers

bool saveReferParam = false;

BOOL CSetSpmCompen::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_compenlist.Init();
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 20;
	strcpy(lf.lfFaceName, "Verdana");
	font.CreateFontIndirect(&lf);
	m_compenlist.SetFont(&font, TRUE);
	
	m_compenlist.SetReadOnlyColumns(0);
	m_compenlist.SetReadOnlyColumns(1);
	m_compenlist.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	m_compenlist.InsertColumn(0, "波长(nm)", LVCFMT_CENTER, 80);
	m_compenlist.InsertColumn(1, "补偿(uJ/count)", LVCFMT_CENTER, 125);

	SetList();
	SetDlgItemText(IDC_Diameter, "400");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CSetSpmCompen::SetList()
{
	m_compenlist.DeleteAllItems();
	double wavelength[PIXELNUM];
	for(int i=0; i<PIXELNUM; i++)
	{
		wavelength[i] = calcoeff.intercept + i * (calcoeff.firstCoeff 
			            + calcoeff.secondCoeff * i + calcoeff.thirdCoeff * i * i);	
		CString str;
		str.Format("%0.1f", wavelength[i]);
		m_compenlist.InsertItem(i, str);
		str.Format("%0.4e", tempstandardCal.uJoulesCount[i]);
		m_compenlist.SetItemText(i, 1, str);
	}
}


BOOL CSetSpmCompen::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	extern bool engineer;
	CPropertySheet* pParent = (CPropertySheet*)GetParent();
	if(engineer)
	{
		pParent->SetWizardButtons(PSWIZB_FINISH|PSWIZB_BACK);
	}
	else
	{
		pParent->SetWizardButtons(PSWIZB_BACK);
	}

	return CPropertyPage::OnSetActive();
}


void CSetSpmCompen::OnAreaWay0() 
{
	// TODO: Add your control notification handler code here
	SetList();
}


void CSetSpmCompen::OnAreaWay1() 
{
	// TODO: Add your control notification handler code here
	SetList();
}


void CSetSpmCompen::OnSaveAs() 
{
	// TODO: Add your control notification handler code here
	CString sz = "补偿文件 (*.Spm)|*.Spm|All File(*.*)|*.*||";
	CFileDialog dlg(false, ".spec", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sz, this);

	if(IDOK==dlg.DoModal())
	{
		CString path = dlg.GetPathName();
		CStdioFile m_file;
		if(m_file.Open((LPCTSTR)path, CFile::modeCreate|CFile::modeReadWrite))
		{
			WriteReferFile(&m_file, &tempstandardCal);
			m_file.Close();
		}
		else
		{
			MessageBox("文件另存失败!");
		}
	}
}


BOOL CSetSpmCompen::OnWizardFinish() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(AfxMessageBox("是否使用此次校正？", MB_YESNO) == IDYES) 
	{
		CStdioFile m_file;
		CString path;
		CFileException e;

//		if(AfxMessageBox("是否要用此次校正覆盖先前校正？", MB_YESNO) == IDYES) 
//		{
			path = mainpath + "\\System\\Calibration.Spm";
/*		}
		else
		{
			path = mainpath + "\\System\\Caltemporary.Spm";
		}
*/
		if(!m_file.Open((LPCTSTR)path, CFile::modeCreate|CFile::modeReadWrite, &e))
		{
			CString sss;
			sss.Format("%d", e.m_cause);
			MessageBox(sss);
			MessageBox("文件保存失败!");
		}
		else
		{
			WriteReferFile(&m_file, &tempstandardCal);
			m_file.Close();
			
			if(m_file.Open((LPCTSTR)path, CFile::modeReadWrite))
			{
				saveReferParam = true;
				ReadReferFile(&m_file);
				m_file.Close();
			}
		}
	} 
	else
	{
		MessageBox("标准灯文件设置失败!");
	}

	return CPropertyPage::OnWizardFinish();
}


void CSetSpmCompen::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CPropertyPage::OnPaint() for painting messages
}


BOOL CSetSpmCompen::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBitmap bmp;
	CBitmap *ptrBmpOld;
	BITMAP bm;

	bmp.LoadBitmap(IDB_FinalCal);
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
				12,
				SRCCOPY
				);
		}
	}
	return true;
//	return CPropertyPage::OnEraseBkgnd(pDC);
}


HBRUSH CSetSpmCompen::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr=(HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}






