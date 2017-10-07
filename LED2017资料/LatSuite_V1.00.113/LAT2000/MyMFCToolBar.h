#pragma once


// CMyMFCToolBar

class CMyMFCToolBar : public CMFCToolBar
{
	DECLARE_DYNAMIC(CMyMFCToolBar)

public:
	CMyMFCToolBar();
	virtual ~CMyMFCToolBar();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


