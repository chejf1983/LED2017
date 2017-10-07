#pragma once
#include "ianalogdisplayx_tmp1.h"
#include "MyDockablePaneData.h"
#include "ieditx_tmp1.h"


// CContainerWatchView 窗体视图

class CContainerWatchView : public CFormView
{
	DECLARE_DYNCREATE(CContainerWatchView)

protected:
	CContainerWatchView();           // 动态创建所使用的受保护的构造函数
	virtual ~CContainerWatchView();

public:
	enum { IDD = IDD_CONTAINER_WATCH_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

//	CArray <CButton, CButton&> m_cTMPRange;
	CArray <CStatic, CStatic&>				m_cTMPConName;
	CArray<CIanalogdisplayx_tmp1, CIanalogdisplayx_tmp1 &> m_cTMP;
	CArray<CStatic, CStatic &>				m_cStaticSetTMP;
	CArray<CIeditx_tmp1, CIeditx_tmp1 &>	m_cSetTMP;

	CArray <CButton, CButton&> m_cRegionName;
	CArray<CStatic, CStatic &> m_cStaticU;
	CArray<CStatic, CStatic &> m_cStaticI;
	CArray<CStatic, CStatic &> m_cStaticP;
	CArray<CIanalogdisplayx_tmp1, CIanalogdisplayx_tmp1 &> m_cU;
	CArray<CIanalogdisplayx_tmp1, CIanalogdisplayx_tmp1 &> m_cI;
	CArray<CIanalogdisplayx_tmp1, CIanalogdisplayx_tmp1 &> m_cP;

	BOOL m_bFir;
protected:
	afx_msg LRESULT OnMsgDockablePaneUpdateInfo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgDockablePaneUpdateTmp(WPARAM wParam, LPARAM lParam);
private:
	BOOL SetTemp1();
	BOOL SetTemp2();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void InitControls();   
	void SetPos();
	CFont m_font;

	CButton m_cTMPOn;
	CButton m_cTMPOff;

	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButtonTmpOn();
	afx_msg void OnBnClickedButtonTmpOff();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CIanalogdisplayx_tmp1 m_cSample;

	afx_msg void OnBnClickedButtonTmpOn2();
	afx_msg void OnBnClickedButtonTmpOff3();
	afx_msg void OnBnClickedButtonTmpOn4();
	afx_msg void OnBnClickedButtonTmpOff5();
	afx_msg void OnBnClickedButtonTmpOn3();
	afx_msg void OnBnClickedButtonTmpOff4();
};


