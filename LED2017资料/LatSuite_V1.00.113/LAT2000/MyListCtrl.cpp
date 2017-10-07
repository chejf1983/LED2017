// MyListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "MyListCtrl.h"
#include <intsafe.h>


// CMyListCtrl

IMPLEMENT_DYNAMIC(CMyListCtrl, CListCtrl)

CMyListCtrl::CMyListCtrl()
{

}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CMyListCtrl::OnNMCustomdraw)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CMyListCtrl 消息处理程序




void CMyListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CString strTemp;
	LPNMLVCUSTOMDRAW  lplvcd = (LPNMLVCUSTOMDRAW)pNMCD;

	switch(lplvcd->nmcd.dwDrawStage)
		{
		case CDDS_PREPAINT :
			*pResult = CDRF_NOTIFYITEMDRAW;
			break;

		case CDDS_ITEMPREPAINT:
			/* At this point, you can change the background colors for the item
			and any subitems and return CDRF_NEWFONT. If the list-view control
			is in report mode, you can simply return CDRF_NOTIFYSUBITEMREDRAW
			to customize the item's subitems individually */

//			lplvcd->clrText = RGB(255, 0, 0);
//			*pResult = CDRF_NEWFONT;

			*pResult = CDRF_NOTIFYSUBITEMDRAW;
			break;
	
		case CDDS_SUBITEM | CDDS_ITEMPREPAINT:
			/* This notification is received only if you are in report mode and
			returned CDRF_NOTIFYSUBITEMREDRAW in the previous step. At
			this point, you can change the background colors for the
			subitem and return CDRF_NEWFONT.*/
			int iItemData = 0;
			DWordPtrToInt(lplvcd->nmcd.lItemlParam, &iItemData);
			if (0 == iItemData)
			{
				lplvcd->clrText = g_ColorInvalid;
				//lplvcd->clrTextBk = g_ColorInvalid;
			}
			if (1 == iItemData)
			{
				lplvcd->clrText = g_ColorGood;
				//lplvcd->clrTextBk = g_ColorGood;
// 				if (1 == lplvcd->iSubItem)
// 				{	
// 					lplvcd->clrText = RGB(0, 255, 0);
// 				}
// 				else
// 				{
// 					lplvcd->clrText = RGB(0, 0, 0);
// 				}
			}
			if (2 == iItemData)
			{
				lplvcd->clrText = g_ColorBad;
				//lplvcd->clrTextBk = g_ColorBad;
			}
			if (3 == iItemData)
			{
				lplvcd->clrText = g_ColorNotTest;
				//lplvcd->clrTextBk = g_ColorNotTest;
			}

			*pResult = CDRF_NEWFONT;  
			break;
		}
}


int CMyListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}
