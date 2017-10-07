// DlgSelfKEdit.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgSelfKEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSelfKEdit dialog


CDlgSelfKEdit::CDlgSelfKEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelfKEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSelfKEdit)
	m_fK = 1.0f;
	m_strName = _T("Lamp");
	//}}AFX_DATA_INIT
	m_iSele = 0;

	CString strSection = "SelfKEdit";
	CString str_m_fK = _T("m_fK");
	CString str_m_strName = _T("m_strName");
	CString str_m_iSele = _T("m_iSele");
	CString strTemp;

	strTemp = AfxGetApp()->GetProfileString(strSection, str_m_fK, _T("1.0"));
	m_fK = (float)atof(strTemp);
	m_strName = AfxGetApp()->GetProfileString(strSection, str_m_strName, _T("Lamp"));
	m_iSele = AfxGetApp()->GetProfileInt(strSection, str_m_iSele, 0);
}


void CDlgSelfKEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelfKEdit)
	DDX_Control(pDX, IDC_COMBO_SELE, m_cSele);
	DDX_Text(pDX, IDC_EDIT_K, m_fK);
	DDV_MinMaxFloat(pDX, m_fK, 1.e-003f, 1000.f);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelfKEdit, CDialog)
	//{{AFX_MSG_MAP(CDlgSelfKEdit)
	ON_BN_CLICKED(IDC_BUTTON_MOD, OnButtonMod)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_CBN_SELCHANGE(IDC_COMBO_SELE, OnSelchangeComboSele)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSelfKEdit message handlers

void CDlgSelfKEdit::OnButtonMod() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE) == FALSE)
		return;

	m_iSele = m_cSele.GetCurSel();
	if(m_iSele < 0 || m_iSele >= m_strListName.GetSize())
		return;

	m_fListK[m_iSele] = m_fK;
	m_strListName[m_iSele] = m_strName;
	ReLIst();
	m_cSele.SetCurSel(m_iSele);	
	Save();
}

void CDlgSelfKEdit::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE) == FALSE)
		return;

	m_strListName.Add(m_strName);
	m_fListK.Add(m_fK);
	ReLIst();
	m_cSele.SetCurSel(m_strListName.GetSize() - 1);
	Save();
}

void CDlgSelfKEdit::OnButtonDel() 
{
	// TODO: Add your control notification handler code here
	m_iSele = m_cSele.GetCurSel();
	if(m_iSele < 0 || m_iSele >= m_strListName.GetSize())
		return;
	m_fListK.RemoveAt(m_iSele);
	m_strListName.RemoveAt(m_iSele);
	ReLIst();
	if(m_iSele < 0)
		m_iSele = 0;
	if(m_iSele >= (m_strListName.GetSize() - 1))
		m_iSele = m_strListName.GetSize() - 1;
	m_cSele.SetCurSel(m_iSele);
	Save();
}

BOOL CDlgSelfKEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	Load();
	ReLIst();
	m_cSele.SetCurSel(m_iSele);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSelfKEdit::ReLIst()
{
	CString strTemp;
	m_cSele.ResetContent();
	for(int i = 0; i < m_strListName.GetSize(); i++)
	{
		strTemp.Format("#%02d.%-16s  %.3f", i + 1, m_strListName[i], m_fListK[i]);
		m_cSele.InsertString(i, strTemp);
	}
}

void CDlgSelfKEdit::OnOK() 
{
	// TODO: Add extra validation here
	if(UpdateData(TRUE) == FALSE)
		return;

	CString strSection = "SelfKEdit";
	CString str_m_fK = _T("m_fK");
	CString str_m_strName = _T("m_strName");
	CString str_m_iSele = _T("m_iSele");
	CString strTemp;

	strTemp.Format(_T("%g"), m_fK);
	AfxGetApp()->WriteProfileString(strSection, str_m_fK, strTemp);
	AfxGetApp()->WriteProfileString(strSection, str_m_strName, m_strName);
	AfxGetApp()->WriteProfileInt(strSection, str_m_iSele, m_iSele);

	CDialog::OnOK();
}

BOOL CDlgSelfKEdit::Load()
{
	CString strPathName = g_strCurPath + "cal\\self_k_list.dat";
	CFile oFile;
	if(!oFile.Open(strPathName,CFile::modeRead))
		return FALSE;
	
    CArchive ar(&oFile,CArchive::load);
	Serialize(ar);
	ar.Close();
	oFile.Close();
	return TRUE;
}

BOOL CDlgSelfKEdit::Save()
{
	CString strPathName = g_strCurPath + "cal\\self_k_list.dat";
	CFile sFile;
	if(!sFile.Open(strPathName,CFile::modeCreate|CFile::modeReadWrite))
		return FALSE;
	CArchive ar(&sFile,CArchive::store);
	Serialize(ar);
	ar.Close();
	sFile.Close();
	return TRUE;
}

void CDlgSelfKEdit::Serialize(CArchive &ar)
{
	CString strVer;
	int i, iN;
	if(ar.IsStoring())
	{
		strVer = _T("SKL_A");
		ar<<strVer;
		iN = m_fListK.GetSize();
		ar<< iN;
		for(i = 0; i < iN; i++)
		{
			ar<< m_fListK[i];
			ar<< m_strListName[i];
		}
	}
	else
	{
		ar>>strVer;
		if(strVer != "SKL_A")
			return;

		m_fListK.RemoveAll();
		m_strListName.RemoveAll();

		ar>>iN;
		for(i = 0; i < iN; i++)
		{
			m_fListK.Add(0);
			m_strListName.Add("");

			ar>> m_fListK[i];
			ar>> m_strListName[i];
		}

	}
}

void CDlgSelfKEdit::OnSelchangeComboSele() 
{
	// TODO: Add your control notification handler code here
	m_iSele = m_cSele.GetCurSel();
	if(m_iSele < 0 || m_iSele >= m_strListName.GetSize())
		return;

	m_strName = m_strListName[m_iSele];
	m_fK = m_fListK[m_iSele];
	UpdateData(FALSE);
}
