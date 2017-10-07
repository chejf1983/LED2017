
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "PropertiesWnd.h"
#include "BCMenu.h"
#include "MyMFCToolBar.h"
#include "MyDockablePaneData.h"


class CMainFrame : public CFrameWndEx
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:
	CMFCStatusBar & GetStatusBar();
	CMFCToolBar   &	GetMyToolBar();

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCMenuBar       m_wndMenuBar;
 	CMFCToolBar       m_wndToolBar;
 	CMFCStatusBar     m_wndStatusBar;
 	CMFCToolBarImages m_UserImages;
	CPropertiesWnd    m_wndProperties;

	CMyMFCToolBar	  m_wndMyToolBar;

// 生成的消息映射函数
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


