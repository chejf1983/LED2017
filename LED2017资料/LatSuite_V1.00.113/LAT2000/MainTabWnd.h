#pragma once

// CMainTabWnd ��ͼ

class CMainTabWnd : public CTabView
{
	DECLARE_DYNCREATE(CMainTabWnd)

protected:
	CMainTabWnd();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMainTabWnd();

	BOOL IsScrollBar() const
	{
		return FALSE;
	}

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();
protected:
	afx_msg LRESULT OnMsgMaintabviewRelist(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
};


