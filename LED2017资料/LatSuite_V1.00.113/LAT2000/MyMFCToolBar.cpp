// MyMFCToolBar.cpp : ʵ���ļ�
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



// CMyMFCToolBar ��Ϣ�������




int CMyMFCToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}
