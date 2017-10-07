// SpectrumDiagram.cpp : implementation file
//

#include "stdafx.h"
#include "HighPowerInterface.h"
#include "SpectrumDiagram.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SpectrumDiagram dialog


SpectrumDiagram::SpectrumDiagram(CWnd* pParent /*=NULL*/)
	: CResizingDialog(SpectrumDiagram::IDD, pParent)
{
	//{{AFX_DATA_INIT(SpectrumDiagram)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SpectrumDiagram::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SpectrumDiagram)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SpectrumDiagram, CResizingDialog)
	//{{AFX_MSG_MAP(SpectrumDiagram)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SpectrumDiagram message handlers
