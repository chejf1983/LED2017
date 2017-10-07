#pragma once
#include "iplotx.h"
#include "ntgraph.h"
#include "ax_cie_xyz.h"
#include "ax_spectrumdrawctrl1.h"
#include "PageSDCM.h"

// CContainerDrawFormView 窗体视图

class CContainerDrawFormView : public CFormView
{
	DECLARE_DYNCREATE(CContainerDrawFormView)

protected:
	CContainerDrawFormView();           // 动态创建所使用的受保护的构造函数
	virtual ~CContainerDrawFormView();

	void RedrawRegion();

public:
	enum { IDD = IDD_CONTAINER_DRAW_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	int m_iCurrentItem;

private:
	CNTGraph m_cRegion;
	CAX_CIE_XYZ m_cCIE;
	
	CPageSDCM m_wndSDCM;
	CFont  m_font;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	void PrintPage(CDC * pDC, CRect printRect, int nPage);
	void PrintLEDData(CDC * pDC, CRect printRect, int iLEDIndex);

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
protected:
	afx_msg LRESULT OnMsgDataContainerDraw(WPARAM wParam, LPARAM lParam);
public:
	CMFCTabCtrl m_cTab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	afx_msg LRESULT OnMsgContainerDrawPrint(WPARAM wParam, LPARAM lParam);
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    CAx_spectrumdrawctrl1 m_cSpectrum;
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    void SetPos(void);
    BOOL m_bFir;
};


