#pragma once
#include "_grid.h"


// CStatisticGridView ������ͼ

class CStatisticGridView : public CFormView
{
	DECLARE_DYNCREATE(CStatisticGridView)

protected:
	CStatisticGridView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CStatisticGridView();

public:
	enum { IDD = IDD_STATISTIC_GRID_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif    
private:


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    virtual void OnInitialUpdate();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    DECLARE_EVENTSINK_MAP()
    void OwnerDrawCellGridStatistic(long Row, long Col, long hdc, long Left, long Top, long Right, long Bottom, BOOL* Handled);
    afx_msg LRESULT OnMsgStatisticGridRelistData(WPARAM wp, LPARAM lp);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    void GetCellTextGridStatistic(long Row, long Col, BSTR* Text, BOOL* Changed);
public:
    C_Grid m_cStatisticGrid;

};


