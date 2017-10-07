/*******************************************************************************
	Author						: Aravindan Premkumar
	Unregistered Copyright 2003	: Aravindan Premkumar
	All Rights Reserved
	
	This piece of code does not have any registered copyright and is free to be 
	used as necessary. The user is free to modify as per the requirements. As a
	fellow developer, all that I expect and request for is to be given the 
	credit for intially developing this reusable code by not removing my name as 
	the author.
*******************************************************************************/

#include "stdafx.h"
#include "ComboListCtrl.h"
#include "InPlaceCombo.h"
#include "InPlaceEdit.h"
#include "wingdi.h" 
#include "..\..\HighPowerInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#defines
#define FIRST_COLUMN				0
#define MIN_COLUMN_WIDTH			10
#define MAX_DROP_DOWN_ITEM_COUNT	10

/////////////////////////////////////////////////////////////////////////////
// CComboListCtrl

CComboListCtrl::CComboListCtrl()
{
	m_ComboSupportColumnsList.RemoveAll();
	m_ReadOnlyColumnsList.RemoveAll();
	m_strValidEditCtrlChars.Empty();
	m_dwEditCtrlStyle = ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_LEFT | ES_NOHIDESEL;
	m_dwDropDownCtrlStyle = WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_AUTOVSCROLL | 
							CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL;

	g_MyClrBgHi = RGB(115,123,165);
	g_MyClrFgHi = RGB(229,229,229);
}

CComboListCtrl::~CComboListCtrl()
{
	CInPlaceCombo::DeleteInstance();
	CInPlaceEdit::DeleteInstance();  
}


BEGIN_MESSAGE_MAP(CComboListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CComboListCtrl)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndLabelEdit)
	ON_NOTIFY_REFLECT(LVN_BEGINLABELEDIT, OnBeginLabelEdit)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_MOUSEWHEEL()
	ON_WM_NCCALCSIZE()
	//}}AFX_MSG_MAP
//	ON_NOTIFY_REFLECT (NM_CUSTOMDRAW, OnCustomDrawList )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboListCtrl message handlers

CInPlaceCombo* CComboListCtrl::ShowInPlaceList(int iRowIndex, int iColumnIndex, CStringList& rComboItemsList, 
											   CString strCurSelecetion /*= ""*/, int iSel /*= -1*/)
{
	// The returned obPointer should not be saved
	
	// Make sure that the item is visible
	if (!EnsureVisible(iRowIndex, TRUE))
	{
		return NULL;
	}

	// Make sure that iColumnIndex is valid 
	CHeaderCtrl* pHeader = static_cast<CHeaderCtrl*> (GetDlgItem(FIRST_COLUMN));

	int iColumnCount = pHeader->GetItemCount();

	if (iColumnIndex >= iColumnCount || GetColumnWidth(iColumnIndex) < MIN_COLUMN_WIDTH) 
	{
		return NULL;
	}

	// Calculate the rectangle specifications for the combo box
	CRect obCellRect(0, 0, 0, 0);
	CalculateCellRect(iColumnIndex, iRowIndex, obCellRect);

	int iHeight = obCellRect.Height();  
	int iCount = rComboItemsList.GetCount();

	iCount = (iCount < MAX_DROP_DOWN_ITEM_COUNT) ? 
		iCount + MAX_DROP_DOWN_ITEM_COUNT : (MAX_DROP_DOWN_ITEM_COUNT + 1); 

	obCellRect.bottom += iHeight * iCount; 

	// Create the in place combobox
	CInPlaceCombo* pInPlaceCombo = CInPlaceCombo::GetInstance();
	pInPlaceCombo->ShowComboCtrl(m_dwDropDownCtrlStyle, obCellRect, this, 0, iRowIndex, iColumnIndex, &rComboItemsList, 
								 strCurSelecetion, iSel);
	
	return pInPlaceCombo;
}

CInPlaceEdit* CComboListCtrl::ShowInPlaceEdit(int iRowIndex, int iColumnIndex, CString& rstrCurSelection)
{
	// Create an in-place edit control
	CInPlaceEdit* pInPlaceEdit = CInPlaceEdit::GetInstance();
		
	CRect obCellRect(0, 0, 0, 0);
	CalculateCellRect(iColumnIndex, iRowIndex, obCellRect);
			
	pInPlaceEdit->ShowEditCtrl(m_dwEditCtrlStyle, obCellRect, this, 0, 
							   iRowIndex, iColumnIndex,
							   m_strValidEditCtrlChars, rstrCurSelection);

	return pInPlaceEdit;
}

void CComboListCtrl::OnHScroll(UINT iSBCode, UINT iPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	if (GetFocus() != this)
	{
		SetFocus();
	}

	CListCtrl::OnHScroll(iSBCode, iPos, pScrollBar);
}

void CComboListCtrl::OnVScroll(UINT iSBCode, UINT iPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	if (GetFocus() != this)
	{
		SetFocus();
	}

	CListCtrl::OnVScroll(iSBCode, iPos, pScrollBar);
}

void CComboListCtrl::OnMouseMove(UINT iFlags, CPoint obPoint) 
{
	// TODO: Add your message handler code here and/or call default
	CListCtrl::OnMouseMove(iFlags, obPoint);
}

bool row1 = true;
void CComboListCtrl::OnLButtonDown(UINT iFlags, CPoint obPoint) 
{
	// TODO: Add your message handler code here and/or call default

	int iColumnIndex = -1;
	int iRowIndex = -1;

	// Get the current column and row
	if (!HitTestEx(obPoint, &iRowIndex, &iColumnIndex))
	{
		return;
	}

	CListCtrl::OnLButtonDown(iFlags, obPoint);
	
	// If column is not read only then
	// If the SHIFT or CTRL key is down call the base class
	// Check the high bit of GetKeyState to determine whether SHIFT or CTRL key is down
	if ((GetKeyState(VK_SHIFT) & 0x80) || (GetKeyState(VK_CONTROL) & 0x80))
	{
		return;
	}

	// Get the current selection before creating the in place combo box
	CString strCurSelection = GetItemText(iRowIndex, iColumnIndex);
	
	if (-1 != iRowIndex)
	{
		UINT flag = LVIS_FOCUSED;
		
		if ((GetItemState(iRowIndex, flag ) & flag) == flag)
		{
			// Add check for LVS_EDITLABELS
			if (GetWindowLong(m_hWnd, GWL_STYLE) & LVS_EDITLABELS)
			{
				// If combo box is supported
				// Create and show the in place combo box
				if (IsCombo(iColumnIndex))
				{
					CStringList obComboItemsList;
										
					GetParent()->SendMessage(WM_SET_ITEMS, (WPARAM)iColumnIndex, (LPARAM)&obComboItemsList);  
					
					CInPlaceCombo* pInPlaceComboBox = ShowInPlaceList(iRowIndex, iColumnIndex, obComboItemsList, strCurSelection);
					ASSERT(pInPlaceComboBox); 
					
					// Set the selection to previous selection
					pInPlaceComboBox->SelectString(-1, strCurSelection);
				}
				// If combo box is not read only
				// Create and show the in place edit control
				else if (!IsReadOnly(iColumnIndex))
				{
					if(row1)
					{
						CInPlaceEdit* pInPlaceEdit = ShowInPlaceEdit(iRowIndex, iColumnIndex, strCurSelection);
					}
					else
					{
						if(iRowIndex != 0)
						{
							CInPlaceEdit* pInPlaceEdit = ShowInPlaceEdit(iRowIndex, iColumnIndex, strCurSelection);
						}
					}
				}
			}
		}
	}  
}

bool CComboListCtrl::HitTestEx(CPoint &obPoint, int* pRowIndex, int* pColumnIndex) const
{
	if (!pRowIndex || !pColumnIndex)
	{
		return false;
	}

	// Get the row index
	*pRowIndex = HitTest(obPoint, NULL);

	if (pColumnIndex)
	{
		*pColumnIndex = 0;
	}

	// Make sure that the ListView is in LVS_REPORT
	if ((GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT)
	{
		return false;
	}

	// Get the number of columns
	CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);

	int iColumnCount = pHeader->GetItemCount();

	// Get bounding rect of item and check whether obPoint falls in it.
	CRect obCellRect;
	GetItemRect(*pRowIndex, &obCellRect, LVIR_BOUNDS);
	
	if (obCellRect.PtInRect(obPoint))
	{
		// Now find the column
		for (*pColumnIndex = 0; *pColumnIndex < iColumnCount; (*pColumnIndex)++)
		{
			int iColWidth = GetColumnWidth(*pColumnIndex);
			
			if (obPoint.x >= obCellRect.left && obPoint.x <= (obCellRect.left + iColWidth))
			{
				return true;
			}
			obCellRect.left += iColWidth;
		}
	}
	return false;
}

void CComboListCtrl::SetComboColumns(int iColumnIndex, bool bSet /*= true*/)
{
	// If the Column Index is not present && Set flag is false
	// Then do nothing 
	// If the Column Index is present && Set flag is true
	// Then do nothing
	POSITION Pos = m_ComboSupportColumnsList.Find(iColumnIndex);

	// If the Column Index is not present && Set flag is true
	// Then Add to list
	if ((NULL == Pos) && bSet) 
	{
		m_ComboSupportColumnsList.AddTail(iColumnIndex); 
	}

	// If the Column Index is present && Set flag is false
	// Then Remove from list
	if ((NULL != Pos) && !bSet) 
	{
		m_ComboSupportColumnsList.RemoveAt(Pos); 
	}
}

void CComboListCtrl::SetReadOnlyColumns(int iColumnIndex, bool bSet /*= true*/)
{
	// If the Column Index is not present && Set flag is false
	// Then do nothing 
	// If the Column Index is present && Set flag is true
	// Then do nothing
	POSITION Pos = m_ReadOnlyColumnsList.Find(iColumnIndex);

	// If the Column Index is not present && Set flag is true
	// Then Add to list
	if ((NULL == Pos) && bSet) 
	{
		m_ReadOnlyColumnsList.AddTail(iColumnIndex); 
	}

	// If the Column Index is present && Set flag is false
	// Then Remove from list
	if ((NULL != Pos) && !bSet) 
	{
		m_ReadOnlyColumnsList.RemoveAt(Pos); 
	}
}

bool CComboListCtrl::IsReadOnly(int iColumnIndex)
{
	if (m_ReadOnlyColumnsList.Find(iColumnIndex))
	{
		return true;
	}
	
	return false;
}

bool CComboListCtrl::IsCombo(int iColumnIndex)
{
	if (m_ComboSupportColumnsList.Find(iColumnIndex))
	{
		return true;
	}

	return false;
}

void CComboListCtrl::CalculateCellRect(int iColumnIndex, int iRowIndex, CRect& robCellRect)
{
	GetItemRect(iRowIndex, &robCellRect, LVIR_BOUNDS);
	
	CRect rcClient;
	GetClientRect(&rcClient);

	if (robCellRect.right > rcClient.right) 
	{
		robCellRect.right = rcClient.right;
	}

	ScrollToView(iColumnIndex, robCellRect); 
}

void CComboListCtrl::OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	// Update the item text with the new text
	SetItemText(pDispInfo->item.iItem, pDispInfo->item.iSubItem, pDispInfo->item.pszText);

	GetParent()->SendMessage(WM_VALIDATE, GetDlgCtrlID(), (LPARAM)pDispInfo); 
	
	*pResult = 0;
}

void CComboListCtrl::SetValidEditCtrlCharacters(CString &rstrValidCharacters)
{
	m_strValidEditCtrlChars = rstrValidCharacters;
}

void CComboListCtrl::EnableHScroll(bool bEnable /*= true*/)
{
	if (bEnable)
	{
		m_dwDropDownCtrlStyle |= WS_HSCROLL;
	}
	else
	{
		m_dwDropDownCtrlStyle &= ~WS_HSCROLL;
	}	
}

void CComboListCtrl::EnableVScroll(bool bEnable /*= true*/)
{
	if (bEnable)
	{
		m_dwDropDownCtrlStyle |= WS_VSCROLL;
	}
	else
	{
		m_dwDropDownCtrlStyle &= ~WS_VSCROLL;
	}
}

void CComboListCtrl::ScrollToView(int iColumnIndex, /*int iOffSet, */CRect& robCellRect)
{
	// Now scroll if we need to expose the column
	CRect rcClient;
	GetClientRect(&rcClient);

	int iColumnWidth = GetColumnWidth(iColumnIndex);

	// Get the column iOffset
	int iOffSet = 0;
	for (int iIndex_ = 0; iIndex_ < iColumnIndex; iIndex_++)
	{
		iOffSet += GetColumnWidth(iIndex_);
	}

	// If x1 of cell rect is < x1 of ctrl rect or
	// If x1 of cell rect is > x1 of ctrl rect or **Should not ideally happen**
	// If the width of the cell extends beyond x2 of ctrl rect then
	// Scroll

	CSize obScrollSize(0, 0);

	if (((iOffSet + robCellRect.left) < rcClient.left) || 
		((iOffSet + robCellRect.left) > rcClient.right))
	{
		obScrollSize.cx = iOffSet + robCellRect.left;
	}
	else if ((iOffSet + robCellRect.left + iColumnWidth) > rcClient.right)
	{
		obScrollSize.cx = iOffSet + robCellRect.left + iColumnWidth - rcClient.right;
	}

	Scroll(obScrollSize);
	robCellRect.left -= obScrollSize.cx;
	
	// Set the width to the column width
	robCellRect.left += iOffSet;
	robCellRect.right = robCellRect.left + iColumnWidth;
}

void CComboListCtrl::OnBeginLabelEdit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	if (IsReadOnly(pDispInfo->item.iSubItem))
	{
		*pResult = 1;
		return;
	}

	*pResult = 0;
}

//////////////////////////DRAWLIST

void CComboListCtrl::PreSubclassWindow() 
{
	//use our custom CHeaderCtrl as long as there
	//is a headerctrl object to subclass
	if(GetHeaderCtrl())
		m_SkinHeaderCtrl.SubclassWindow(GetHeaderCtrl()->m_hWnd);

	CListCtrl::PreSubclassWindow();
}


void CComboListCtrl::OnCustomDrawList ( NMHDR* pNMHDR, LRESULT* pResult )
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
	static bool bHighlighted = false;
	
    *pResult = CDRF_DODEFAULT;

    if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
        *pResult = CDRF_NOTIFYITEMDRAW;
	}
    else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
        int iRow = (int)pLVCD->nmcd.dwItemSpec;
		
		bHighlighted = IsRowHighlighted(m_hWnd, iRow);
		if (bHighlighted)
		{
			pLVCD->clrText   = g_MyClrFgHi; // Use my foreground hilite color
			pLVCD->clrTextBk = g_MyClrBgHi; // Use my background hilite color
			
			EnableHighlighting(m_hWnd, iRow, false);
		}
		
		*pResult = CDRF_DODEFAULT | CDRF_NOTIFYPOSTPAINT;
		
	}
	else if(CDDS_ITEMPOSTPAINT == pLVCD->nmcd.dwDrawStage)
	{
	if (bHighlighted)
      {
        int  iRow = (int)pLVCD->nmcd.dwItemSpec;

        EnableHighlighting(m_hWnd, iRow, true);
      }

      *pResult = CDRF_DODEFAULT;

	}
}

void CComboListCtrl::EnableHighlighting(HWND hWnd, int row, bool bHighlight)
{
	ListView_SetItemState(hWnd, row, bHighlight? 0xff: 0, LVIS_SELECTED);
}

bool CComboListCtrl::IsRowSelected(HWND hWnd, int row)
{
	return ListView_GetItemState(hWnd, row, LVIS_SELECTED) != 0;
}

bool CComboListCtrl::IsRowHighlighted(HWND hWnd, int row)
{
	return IsRowSelected(hWnd, row) /*&& (::GetFocus() == hWnd)*/;
}

void CComboListCtrl::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	UpdateWindow();
	CListCtrl::OnNcCalcSize(bCalcValidRects, lpncsp);
}

BOOL CComboListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	m_SkinVerticleScrollbar.UpdateThumbPosition();
	m_SkinHorizontalScrollbar.UpdateThumbPosition();
	
	return CListCtrl::OnMouseWheel(nFlags, zDelta, pt);
}


void CComboListCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	m_SkinVerticleScrollbar.UpdateThumbPosition();
	m_SkinHorizontalScrollbar.UpdateThumbPosition();

	CListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CComboListCtrl::Init()
{
	//another way to hide scrollbars
	InitializeFlatSB(m_hWnd);
	FlatSB_EnableScrollBar(m_hWnd, SB_BOTH, ESB_DISABLE_BOTH);

	CWnd* pParent = GetParent();

	//Create scrollbars at runtime
	m_SkinVerticleScrollbar.Create(NULL, WS_CHILD|SS_LEFT|SS_NOTIFY|WS_VISIBLE|WS_GROUP,CRect(0,0,0,0), pParent);
	m_SkinHorizontalScrollbar.Create(NULL, WS_CHILD|SS_LEFT|SS_NOTIFY|WS_VISIBLE|WS_GROUP,CRect(0,0,0,0), pParent);
	m_SkinVerticleScrollbar.pList = this;
	m_SkinHorizontalScrollbar.pList = this;

	//call this to position the scrollbars properly
	PositionScrollBars();
}

void CComboListCtrl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	m_SkinVerticleScrollbar.UpdateThumbPosition();
	m_SkinHorizontalScrollbar.UpdateThumbPosition();

	CListCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
}

BOOL CComboListCtrl::OnEraseBkgnd(CDC* pDC) 
{
	m_SkinVerticleScrollbar.UpdateThumbPosition();
	m_SkinHorizontalScrollbar.UpdateThumbPosition();
	return true;
//	return CListCtrl::OnEraseBkgnd(pDC);
}

void CComboListCtrl::OnPaint() 
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	CMemDC memDC(&dc, rect);
	CString str;
	//funky code to allow use to double buffer
	//the onpaint calls for flicker free drawing
	//of the list items

	CRect headerRect;
	GetDlgItem(0)->GetWindowRect(&headerRect);
	ScreenToClient(&headerRect);
	dc.ExcludeClipRect(&headerRect);
	   
	CRect clip;
	memDC.GetClipBox(&clip);
	memDC.FillSolidRect(clip, RGB(255, 255, 255));//CLR_NONE);

/*	CBitmap bitmapbk;
	BITMAP bm;
	bitmapbk.LoadBitmap(IDB_ListBK);
	bitmapbk.GetBitmap(&bm);
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(&memDC);
	CBitmap* pOldBitmap = dcMemory.SelectObject(&bitmapbk);	

	memDC.StretchBlt(0, 0, 1000, 700, &dcMemory, 0,0, 566, 123, SRCCOPY);
	   
	SetTextBkColor(CLR_NONE);
*/
	m_SkinVerticleScrollbar.UpdateThumbPosition();
	m_SkinHorizontalScrollbar.UpdateThumbPosition();
	   
/*	BLENDFUNCTION   bf; 
	bf.AlphaFormat=0; 
	bf.BlendFlags=0; 
	bf.BlendOp=AC_SRC_OVER; 
	bf.SourceConstantAlpha=255;//Í¸Ã÷¶È0-255 
	
	AlphaBlend(dc,0,0,clip.Width(),clip.Height(),memDC,0,0,clip.Width(),clip.Height(),bf); 
*/
	DefWindowProc(WM_PAINT, (WPARAM)memDC->m_hDC, (LPARAM)0);
}

void CComboListCtrl::PositionScrollBars()
{
	//Thanks goes to mindows for this function
	//he posted on the message forums. He modified
	//it a bit based on the original init function,
	//and now I have modified his version a tiny bit ;)
	//The pParent->ScreenToClient that you did made it
	//possible for me to make the scrollbars position
	//properly based on any dialog size/borders/titlebar etc... :D

	CWnd* pParent = GetParent();
	
	CRect windowRect;
	GetWindowRect(&windowRect);
	
	int nTitleBarHeight = 0;
	
	if(pParent->GetStyle() & WS_CAPTION)
		nTitleBarHeight = GetSystemMetrics(SM_CYSIZE);
	
	
	int nDialogFrameHeight = 0;
	int nDialogFrameWidth = 0;
	if((pParent->GetStyle() & WS_BORDER))
	{
		nDialogFrameHeight = GetSystemMetrics(SM_CYDLGFRAME);
		nDialogFrameWidth = GetSystemMetrics(SM_CYDLGFRAME);
	}
	
	if(pParent->GetStyle() & WS_THICKFRAME)
	{
		nDialogFrameHeight+=1;
		nDialogFrameWidth+=1;
	}
	
	pParent->ScreenToClient(&windowRect);

	windowRect.top+=nTitleBarHeight+nDialogFrameHeight;
	windowRect.bottom+=nTitleBarHeight+nDialogFrameHeight;
	windowRect.left +=nDialogFrameWidth;
	windowRect.right+=nDialogFrameWidth;
	
	CRect vBar(windowRect.right-nDialogFrameWidth,windowRect.top-nTitleBarHeight-nDialogFrameHeight,windowRect.right+12-nDialogFrameWidth,windowRect.bottom+12-nTitleBarHeight-nDialogFrameHeight);
	CRect hBar(windowRect.left-nDialogFrameWidth,windowRect.bottom-nTitleBarHeight-nDialogFrameHeight,windowRect.right+1-nDialogFrameWidth,windowRect.bottom+12-nTitleBarHeight-nDialogFrameHeight);
	
	m_SkinVerticleScrollbar.SetWindowPos(NULL,vBar.left,vBar.top,vBar.Width(),vBar.Height(),SWP_NOZORDER);
	m_SkinHorizontalScrollbar.SetWindowPos(NULL,hBar.left,hBar.top,hBar.Width(),hBar.Height(),SWP_NOZORDER);
	
	m_SkinHorizontalScrollbar.UpdateThumbPosition();
	m_SkinVerticleScrollbar.UpdateThumbPosition();	
}

void CComboListCtrl::DeleteAllColumns()
{
	int nCount = GetHeaderCtrl()->GetItemCount();
	for(int i=0; i<nCount; i++)
	{
		DeleteColumn(0);
	}
}
