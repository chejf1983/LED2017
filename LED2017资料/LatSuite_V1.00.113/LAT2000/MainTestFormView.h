#pragma once
#include "iledroundx1.h"
#include "image1.h"
#include "iimagedisplayx1.h"
#include "afxwin.h"
#include "LedData.h"
#include "ColorDemo.h"
#include "LAT2000Doc.h"
#include "ButtonEx.h"
#include "MyCheckLED.h"
#include "StaticOtherInfo.h"

// CMainTestFormView 窗体视图

class CMainTestFormView : public CFormView
{

	DECLARE_DYNCREATE(CMainTestFormView)

protected:
	CMainTestFormView();           // 动态创建所使用的受保护的构造函数
	virtual ~CMainTestFormView();

public:
	enum { IDD = IDD_TEST_FORM_VIEW};
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	CStaticOtherInfo m_cOtherInfo;

	void InitLEDIndicator();

	void ShowLEDIndicator();

	void UpdateLEDIndicator();

	BOOL GetItemRect(int iColumn, int iItem, CRect & rect);

	void ListLimitFile();

	int  GetCheck();

protected:
	afx_msg LRESULT OnMsgTestEnded(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgShowMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgLimitFileRelist(WPARAM wParam, LPARAM lParam);
	
	static UINT ThreadGetLineState(LPVOID pPar);
	static UINT ThreadAlarmPlayRing(LPVOID pPar);

private:
	CArray<CMyCheckLED, CMyCheckLED &> m_LEDIndicator;
	int m_iRowIndex;
	int m_iColumnIndex;

	BYTE m_ucItemShowFlag;
	CMenu * m_PopupMenu;
	CColorDemo m_cColorDemo;

	// Every LED's check state stored in the Doc's boolean array
	// so that Retest thread can know which LED should be retested.
	// The value of the Doc's boolean array is updated by the ON_UPDATE_COMMAND_UI of retest button.
	int m_iCheckLEDCount;

	// Alarm
	AlarmType	m_eAlarmType;
	BOOL		m_bIsAlarming;
	BOOL		m_bStopAlarming;
	CEvent		m_PlayOneRing;		// Set when a new alarm is received
	BOOL		m_bMessageIsShowing;	// One alarm message dialog is showing, if another alarm message comes,
										// it will be ignored

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	void PrintLEDData(CDC * pDC, CRect printRect, int iLEDIndex);
	void PrintPage(CDC * pDC, CRect printRect, int nPage);

public:
	enum ITEM_SHOW_FLAG
	{
		SHOW_FLUX	= 0x01,
		SHOW_TC		= 0x02,
		SHOW_XY		= 0x04,
		SHOW_UV		= 0x08,
		SHOW_LD		= 0x10,
		SHOW_DISPERSION = 0x20,
	};

	afx_msg void OnPaint();
	DECLARE_EVENTSINK_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnMsgStartTest(UINT wParam, LONG lParam);
	afx_msg LRESULT OnMsgReListLED(UINT wParam, LONG lParam);
	virtual void OnInitialUpdate();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnUpdatePopFlux(CCmdUI *pCmdUI);
	afx_msg void OnPopFlux();
	afx_msg void OnUpdatePopTc(CCmdUI *pCmdUI);
	afx_msg void OnPopTc();
	afx_msg void OnUpdatePopXy(CCmdUI *pCmdUI);
	afx_msg void OnPopXy();
	afx_msg void OnUpdatePopUv(CCmdUI *pCmdUI);
	afx_msg void OnPopUv();
	afx_msg void OnUpdatePopLd(CCmdUI *pCmdUI);
	afx_msg void OnPopLd();
	afx_msg void OnUpdatePopDispersion(CCmdUI *pCmdUI);
	afx_msg void OnPopDispersion();
	afx_msg void OnBnClickedButtonTestFail();
	afx_msg void OnBnClickedButtonBad();
	afx_msg void OnBnClickedButtonNone();
	afx_msg void OnBnClickedButtonReverse();
	afx_msg void OnBnClickedButtonGood();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void PreSubclassWindow();
	afx_msg void OnKillfocusComboFile();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	afx_msg void OnUpdateMenuPrint(CCmdUI *pCmdUI);
	afx_msg void OnMenuPrint();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual BOOL DestroyWindow();
	afx_msg void OnResetStatistics();
};


