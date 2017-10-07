#pragma once



// CLEDDataStatView ������ͼ

class CLEDDataStatView : public CFormView
{
	DECLARE_DYNCREATE(CLEDDataStatView)

protected:
	CLEDDataStatView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CLEDDataStatView();

public:
	enum { IDD = IDD_LED_DATA_STAT_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
    CFrameWnd * m_pFrame;
    CSplitterWnd m_cSplitterLeft;
    CSplitterWnd m_cSplitterRight;
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    virtual void OnInitialUpdate();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
    afx_msg void OnExportStatisticData();
};



