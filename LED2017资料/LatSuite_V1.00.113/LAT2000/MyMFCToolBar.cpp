// MyMFCToolBar.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "MyMFCToolBar.h"


// CMyMFCToolBar

IMPLEMENT_DYNAMIC(CMyMFCToolBar, CMFCToolBar)

CMyMFCToolBar::CMyMFCToolBar()
{

}

CMyMFCToolBar::~CMyMFCToolBar()
{
}


BEGIN_MESSAGE_MAP(CMyMFCToolBar, CMFCToolBar)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CMyMFCToolBar 消息处理程序




int CMyMFCToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}
