#pragma once
#include "_grid.h"
#include "iplotx.h"
#include "ipiechartx1.h"
#include "HistogramGraphCtrl.h"
// CStatisticDistributionGridView 窗体视图

class CStatisticDistributionGridView : public CFormView
{
	DECLARE_DYNCREATE(CStatisticDistributionGridView)

protected:
	CStatisticDistributionGridView();           // 动态创建所使用的受保护的构造函数
	virtual ~CStatisticDistributionGridView();

public:
	enum { IDD = IDD_STATISTIC_GRID_DISTRIBUTION_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
private:
    CIpiechartx1 m_PieChart;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    virtual void OnInitialUpdate();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    DECLARE_EVENTSINK_MAP()
    void OwnerDrawCellGridStatisticDistribution(long Row, long Col, long hdc, long Left, long Top, long Right, long Bottom, BOOL* Handled);
    void RowColChangeGridStatisticDistribution(long Row, long Col);
    afx_msg LRESULT OnMsgStatisticDistributionGridRelistData(WPARAM wp, LPARAM lp);

    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    CStatic m_cRect1;
    CHistogramGraphCtrl m_cRect2;

    void GetCellTextGridStatisticDistribution(long Row, long Col, BSTR* Text, BOOL* Changed);
public:
    C_Grid m_cStatisticDistributeGrid;    
};


