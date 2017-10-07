// Page1.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "Page1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPage1 dialog

IMPLEMENT_DYNCREATE(CPage1, CDialog);

CPage1::CPage1(CWnd* pParent /*=NULL*/)
	: CDialog(CPage1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPage1)
	//}}AFX_DATA_INIT
	m_bFir=TRUE;
	m_pSpData=NULL;
}


void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage1)
	DDX_Control(pDX, IDC_SDCM, m_cSDCM);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage1, CDialog)
	//{{AFX_MSG_MAP(CPage1)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage1 message handlers

BOOL CPage1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	SetPos();
	ReDraw();
	m_bFir=FALSE;
	SetPos();
	ReDraw();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPage1::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!m_bFir)
	{
		SetPos();
		ReDraw();
	}
}

void CPage1::SetPos()
{
	CRect clRect;
	GetClientRect(clRect);
	if(m_bFir)
	{
		clRect.left=0;
		clRect.right=1500;
		clRect.top=0;
		clRect.bottom=1500;
	}
	CRect drRect;

	float fHW=1.0f;
	if(clRect.Width()!=0)
		fHW=clRect.Height()*1.0f/clRect.Width();
	if(fHW<5/4.0f)
	{
		drRect.top=clRect.top+2;
		drRect.bottom=clRect.bottom-2;

		int iW=drRect.Height()*4/5;

		drRect.left=clRect.left+(clRect.Width()-iW)/2;
		drRect.right=clRect.right-(clRect.Width()-iW)/2;
	}
	else
	{
		drRect.left=clRect.left+2;
		drRect.right=clRect.right-2;

		int iH=drRect.Width()*5/4;

		drRect.top=clRect.top+(clRect.Height()-iH)/2;
		drRect.bottom=clRect.bottom-(clRect.Height()-iH)/2;
	}
	m_cSDCM.MoveWindow(drRect);
}

void CPage1::ReDraw(int iSele,int iSDCM1,int iSDCM2)
{
	if(m_pSpData==NULL)
	{
		CSpectData spTemp;
		m_cSDCM.DrawSDCM(spTemp,iSele,iSDCM1,iSDCM2);
	}
	else
	{
		m_cSDCM.DrawSDCM(*m_pSpData,iSele,iSDCM1,iSDCM2);
	}
}
