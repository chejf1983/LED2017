#pragma once
#include "_grid.h"


// CContainerGridView 窗体视图

class CContainerGridView : public CFormView
{
	DECLARE_DYNCREATE(CContainerGridView)

protected:
	CContainerGridView();           // 动态创建所使用的受保护的构造函数
	virtual ~CContainerGridView();

public:
	enum { IDD = IDD_CONTAINER_GRID_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	C_Grid m_cDataGrid;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
protected:
	afx_msg LRESULT OnMsgTestEnded(WPARAM wParam, LPARAM lParam);
public:
	DECLARE_EVENTSINK_MAP()
	void RowColChangeGrid1(long Row, long Col);
protected:
	afx_msg LRESULT OnMsgGridExportData(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgGridRelistData(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void GetCellTextGrid1(long Row, long Col, BSTR* Text, BOOL* Changed);
	void SetCellTextGrid1(long Row, long Col, LPCTSTR Text, BOOL* Cancel);
	void HyperLinkClickGrid1(long Row, long Col, BSTR* URL, BOOL* Changed);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OwnerDrawCellGridMain(long Row, long Col, long hdc, long Left, long Top, long Right, long Bottom, BOOL* Handled);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnMsgExportData(UINT wParam, LONG lParam);
};


