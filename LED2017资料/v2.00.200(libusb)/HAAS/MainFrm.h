// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__799E0388_8CF0_11DB_949D_00055D02EEF1__INCLUDED_)
#define AFX_MAINFRM_H__799E0388_8CF0_11DB_949D_00055D02EEF1__INCLUDED_

#include "MatrixStatic.h"

#include "MPCStatusBar.h"
#include "MPCLogoPane.h"
#include "Label.h"
#include "LED300Data.h"
#include "DlgWhite.h"
#include "DlgLevel.h"

// #include "Page1.h"
// #include "Page2.h"
// #include "Page3.h"
// #include "Page4.h"
// #include "Page5.h"
// #include "CoolTabCtrl.h"

#include "BCMenu.h"

//信息文字
#define WM_SHOW_NOTE    WM_USER+485

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:
	static BOOL m_bWaitLamp;
	static BOOL m_bEverySetColoCorrect;
	int m_iSetPassword1;
	int m_iSetPassword2;
	BOOL ReadPasswordFile(CString strPathName);
	// 色容差 CIE色品图 光谱曲线
// 	CCoolBar  m_wndBar1;
// 	CCoolTabCtrl m_TabCtrl;
// 	CPage1 *m_pPage1;
// 	CPage2 *m_pPage2;
// 	CPage3 *m_pPage3;
// 	CPage4 *m_pPage4;
// 	CPage5 *m_pPage5;

	int m_iPerCur;
	//测量参数
	CCoolBar  m_wndBar2;
	CTreeCtrl m_wndTree;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL SetPassFile();
	BOOL GetPasFun(CString strCurPath);
	//测试设置
	void SetDlgBarSet(int iSele);
	//显示树形参数
	void SetTreeParameter(int iCur, CTreeCtrl &m_cTree,CLED300Data &data,int iPhType);
	//图标
	CImageList m_SmallImageList;
	//是否显示 m_wndBar1 
	BOOL       m_bShowCIEBar;
	//
	static void ShowNote(CString strNote,BOOL bSet=FALSE,COLORREF ref=RGB(0,0,0));
	void DockControlBarLeftOf(CToolBar *Bar, CToolBar *LeftOf);
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	MPCStatusBar  m_wndStatusBar;
	CToolBar      m_wndToolBar;

// Generated message map functions
protected:
	//测试设置工具栏
	CDialogBar m_wndMyTestBar;
	//初始化
	int InitSystem();
	int InitNoteBar();
	int InitBar();
	int InitTestBar();
	//信息条
	CLabel m_cNote;
	//信息栏
	CDialogBar m_wndMyNoteBar;
	//记录窗口位置
	int m_cyCur, m_cyMin;
	CSplitterWnd m_wndSplitter1; 
	//{{AFX_MSG(CMainFrame)
	afx_msg void OnUpdateMode(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCalList(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnViewSetbar();
	afx_msg void OnUpdateViewSetbar(CCmdUI* pCmdUI);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnWMShowNote(UINT wParam, LONG lParam);
	afx_msg void OnDebug();
	afx_msg void OnUpdateDebug(CCmdUI* pCmdUI);
	afx_msg void OnSpectrumCal();
	afx_msg void OnUpdateSpectrumCal(CCmdUI* pCmdUI);
	afx_msg void OnSetWy();
	afx_msg void OnUpdateSetWy(CCmdUI* pCmdUI);
	afx_msg void OnCheckAutoTime();
	afx_msg void OnChangeEditIntTime();
	afx_msg void OnChangeEditAvgN();
	afx_msg void OnWlCheck();
	afx_msg void OnUpdateWlCheck(CCmdUI* pCmdUI);
	afx_msg void OnDark();
	afx_msg void OnUpdateDark(CCmdUI* pCmdUI);
	afx_msg void OnButtonFlux();
	afx_msg void OnUpdateButtonFlux(CCmdUI* pCmdUI);
	afx_msg void OnPara();
	afx_msg void OnUpdatePara(CCmdUI* pCmdUI);
	afx_msg void OnCalFlux();
	afx_msg void OnUpdateCalFlux(CCmdUI* pCmdUI);
	afx_msg void OnCalType();
	afx_msg void OnUpdateCalType(CCmdUI* pCmdUI);
	afx_msg void OnCalAttK();
	afx_msg void OnUpdateCalAttK(CCmdUI* pCmdUI);
	afx_msg void OnTestUp();
	afx_msg void OnUpdateTestUp(CCmdUI* pCmdUI);
	afx_msg void OnDebugSoft();
	afx_msg void OnUpdateDebugSoft(CCmdUI* pCmdUI);
	afx_msg void OnEditWhite();
	afx_msg void OnUpdateEditWhite(CCmdUI* pCmdUI);
	afx_msg void OnEditLevel();
	afx_msg void OnUpdateEditLevel(CCmdUI* pCmdUI);
	afx_msg void OnTestStc();
	afx_msg void OnUpdateTestStc(CCmdUI* pCmdUI);
	afx_msg void OnSpectCalU();
	afx_msg void OnUpdateSpectCalU(CCmdUI* pCmdUI);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	afx_msg void OnTpsMeters();
	afx_msg void OnUpdateTpsMeters(CCmdUI* pCmdUI);
	afx_msg void OnVpsMeters();
	afx_msg void OnUpdateVpsMeters(CCmdUI* pCmdUI);
	afx_msg void OnCalPlFlux();
	afx_msg void OnUpdateCalPlFlux(CCmdUI* pCmdUI);
	afx_msg void OnPower();
	afx_msg void OnUpdatePower(CCmdUI* pCmdUI);
	afx_msg void OnSelfPh();
	afx_msg void OnUpdateSelfPh(CCmdUI* pCmdUI);
	afx_msg void OnGpibKeithley2420();
	afx_msg void OnUpdateGpibKeithley2420(CCmdUI* pCmdUI);
	afx_msg void OnRs232RemoteComm();
	afx_msg void OnUpdateRs232RemoteComm(CCmdUI* pCmdUI);
	afx_msg void OnWaitLamp();
	afx_msg void OnUpdateWaitLamp(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnDpsPc();
	afx_msg void OnUpdateDpsPc(CCmdUI* pCmdUI);
	afx_msg void OnExdtr();
	afx_msg void OnUpdateExdtr(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static UINT threadConnectManager(LPVOID pPar);
	BCMenu m_default;
	HMENU NewDefaultMenu();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__799E0388_8CF0_11DB_949D_00055D02EEF1__INCLUDED_)
