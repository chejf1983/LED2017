
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "PropertiesWnd.h"
#include "BCMenu.h"
#include "MyMFCToolBar.h"
#include "MyDockablePaneData.h"


class CMainFrame : public CFrameWndEx
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:
	CMFCStatusBar & GetStatusBar();
	CMFCToolBar   &	GetMyToolBar();

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar;
 	CMFCToolBar       m_wndToolBar;
 	CMFCStatusBar     m_wndStatusBar;
 	CMFCToolBarImages m_UserImages;
	CPropertiesWnd    m_wndProperties;

	CMyMFCToolBar	  m_wndMyToolBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg LRESULT OnToolBarReset(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

// 	BOOL CreateDockingWindows();
// 	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
	afx_msg void OnUpdateIndicatorLogo(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIndicatorTime(CCmdUI *pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnUpdateWatchPane(CCmdUI *pCmdUI);
	afx_msg void OnWatchPane();
	virtual void ActivateFrame(int nCmdShow = -1);
private:
    static UINT threadConnectManager(LPVOID pPar);

public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
};


