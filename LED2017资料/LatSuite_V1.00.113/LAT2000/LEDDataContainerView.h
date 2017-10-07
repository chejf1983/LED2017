#pragma once

// CLEDDataContainerView 窗体视图

class CLEDDataContainerView : public CFormView
{
	DECLARE_DYNCREATE(CLEDDataContainerView)

protected:
	CLEDDataContainerView();           // 动态创建所使用的受保护的构造函数
	virtual ~CLEDDataContainerView();

public:
	enum { IDD = IDD_LED_DATA_CONTAINER };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CFrameWnd * m_pFrame;
	CSplitterWnd m_cSplitterLeft;
	CSplitterWnd m_cSplitterRight;

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnButtonExport();
	afx_msg void OnUpdateButtonExport(CCmdUI *pCmdUI);
	afx_msg void OnFileSaveAs();
	afx_msg void OnUpdateFileSaveAs(CCmdUI *pCmdUI);
	afx_msg void OnFileOpen();
	afx_msg void OnUpdateFileOpen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuPrint(CCmdUI *pCmdUI);
	afx_msg void OnMenuPrint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};