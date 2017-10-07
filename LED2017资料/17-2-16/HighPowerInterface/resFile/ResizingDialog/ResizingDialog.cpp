////////////////////////////////////////////////////////////////////////
// ResizingDialog.cpp : implementation file
//
// The base class for the dialog box you want to allow resizing
// Use SetConrolInfo() to determine how each control behaves when
// the user resize the dialog box.
// (The "Windows default" is ANCHORE_TOP | ANCHORE_LEFT)
//
// e.g. For a right aligned OK button you'll probably call:
// SetControlInfo(IDOK, ANCHORE_RIGHT)
// For a text control that needs to resize with the dialog you may do:
// SetControlInfo(IDD_MYEDITOR, RESIZE_BOTH)
//
// Note: The dialog box "remebers" its size on destroy and the next time
// you launch it, it'll set the dialog size back to the previous size.
// If you don't like this behavior, call SetRememberSize(FALSE)
//
// LIMITATIONS:
// 1) This class does not handle overlapping controls, 
//    e.g., you cannot place two controls one (RESIZE_VER) and the other
//    with (RESIZE_VER | ANCHORE_BOTTOM) one below the other, they may ovelapp.
//
// 2) This class does not remember the mode of the dialog (Maximized/Minimized)
//	  it would be easy to add this feature, though.

#include "stdafx.h"
#include "ResizingDialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResizingDialog dialog

CResizingDialog::CResizingDialog(UINT nIDTemplate, CWnd* pParentWnd) : 
				CDialog(nIDTemplate,pParentWnd)
{
	m_minWidth = m_minHeight = 0;	// flag that GetMinMax wasn't called yet
	m_old_cx = m_old_cy = 0;
	m_bSizeChanged = FALSE;
	m_nIDTemplate = nIDTemplate;
	m_bRememberSize = TRUE;
}

void CResizingDialog::SetControlInfo(WORD CtrlId,WORD Anchore)			
{
	if(Anchore == ANCHORE_LEFT)
		return; // Do nothing

	// Add resizing behaviour for the control
	DWORD c_info = CtrlId | (Anchore << 16);
	m_control_info.Add(c_info);
}

BEGIN_MESSAGE_MAP(CResizingDialog, CDialog)
	//{{AFX_MSG_MAP(CResizingDialog)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////////
// CResizingDialog message handlers



//////////////////////////////////////////////////////////////////////////
// OnInitDialog()
//
BOOL CResizingDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(m_bRememberSize)
	{
		// Load the previous size of the dialog box from the INI/Registry
		char dialog_name[7];
		
		itoa(m_nIDTemplate, dialog_name, 16);
		int cx = AfxGetApp()->GetProfileInt(dialog_name,"CX",0);
		int cy = AfxGetApp()->GetProfileInt(dialog_name,"CY",0);
		
		if(cx && cy)
		{
			SetWindowPos( NULL, 0, 0, cx, cy, SWP_NOMOVE );
		}
	}
	
	return FALSE;  // return TRUE  unless you set the focus to a control
}


void CResizingDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	int dx = cx - m_old_cx;
	int dy = cy - m_old_cy;

	if(m_old_cx)
	{
		// Move and Size the controls using the information
		// we got in SetControlInfo()
		//
		m_bSizeChanged = TRUE;
		CRect WndRect;
		CWnd *pWnd;
		DWORD c_info;
		short Anchore;
		for(int i = 0; i < m_control_info.GetSize(); i++)
		{
			c_info = m_control_info[i];
			pWnd = GetDlgItem(LOWORD(c_info));
			if(!pWnd)
			{
				TRACE("Control ID - %d NOT FOUND!!\n",LOWORD(c_info));
				continue;
			}

			if(!HIWORD(c_info))
				continue; // do nothing if anchored to top and or left

			Anchore = HIWORD(c_info);
			pWnd->GetWindowRect(&WndRect);  ScreenToClient(&WndRect);
			
			if(Anchore & RESIZE_HOR)
				WndRect.right += dx;
			else if(Anchore & ANCHORE_RIGHT)
				WndRect.OffsetRect(dx,0);

			if(Anchore & RESIZE_VER)
				WndRect.bottom += dy;
			else if(Anchore & ANCHORE_BOTTOM)
				WndRect.OffsetRect(0,dy);

			pWnd->MoveWindow(&WndRect);
		}

	}
	m_old_cx = cx;
	m_old_cy = cy;
}

void CResizingDialog::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
    if (!m_minWidth) // first time
		{
		CDialog::OnGetMinMaxInfo(lpMMI);
		return;
		}
    lpMMI->ptMinTrackSize.x = m_minWidth;
    lpMMI->ptMinTrackSize.y = m_minHeight;
}

void CResizingDialog::OnDestroy() 
{
	// Save the size of the dialog box, so next time
	// we'll start with this size
	if(m_bRememberSize && m_bSizeChanged && m_old_cx && m_old_cy)
		{
		CRect rc;
		GetWindowRect(&rc);
		char dialog_name[7];	
		itoa(m_nIDTemplate, dialog_name, 16);				

		AfxGetApp()->WriteProfileInt(dialog_name,"CX",rc.Width());
		AfxGetApp()->WriteProfileInt(dialog_name,"CY",rc.Height());
		}
	m_minWidth = m_minHeight = m_old_cx = m_old_cy = 0;
	m_bSizeChanged = FALSE;
	CDialog::OnDestroy();
}


int CResizingDialog::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Remember the original size so later we can calculate
	// how to place the controls on dialog Resize
	m_minWidth  = lpCreateStruct->cx;
	m_minHeight = lpCreateStruct->cy;
	return 0;
}


void CResizingDialog::OnOK() 
{
	// TODO: Add extra validation here	
//	CDialog::OnOK();
}

void CResizingDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
//	CDialog::OnCancel();
}

void CResizingDialog::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	EndDialog(IDCANCEL);
//	CDialog::OnClose(); 
}

void CResizingDialog::ChangeSize(UINT nID, float x, float y) 
{ 
	CWnd *pWnd; 
	pWnd = GetDlgItem(nID);   
	if(pWnd) 
	{ 
		CRect rect;  //��ȡ�ؼ��仯ǰ��С 
		pWnd->GetWindowRect(&rect); 
		ScreenToClient(&rect); 
		rect.left  = (long)(rect.left * x);    // �����ؼ���С 
		rect.right = (long)(rect.right * x); 
		rect.top  = (long)(rect.top * y); 
		rect.bottom = (long)(rect.bottom * y); 
		pWnd->MoveWindow(rect);  
	}
} 

BOOL CResizingDialog::DrawBK(CDC* pDC, UINT nID, int style) 
{
	// TODO: Add your message handler code here and/or call default
	CBitmap bmp;
	CBitmap *ptrBmpOld;
	BITMAP bm;

	bmp.LoadBitmap(nID);
	bmp.GetBitmap(&bm);

	CRect rect;
	GetClientRect(rect);

	int w,h;
	w=rect.Width()/bm.bmWidth+1;
	h=rect.Height()/bm.bmHeight+1;

	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	ptrBmpOld=dcMemory.SelectObject(&bmp);

	if(0 == style)
	{
		pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMemory, 0,0, bm.bmWidth, bm.bmHeight, SRCCOPY);
	}
	else
	{
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
	}	

	return true;
}


