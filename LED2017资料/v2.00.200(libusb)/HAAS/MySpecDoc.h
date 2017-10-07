// MySpecDoc.h : interface of the CMySpecDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSPECDOC_H__799E038A_8CF0_11DB_949D_00055D02EEF1__INCLUDED_)
#define AFX_MYSPECDOC_H__799E038A_8CF0_11DB_949D_00055D02EEF1__INCLUDED_

#include "LED300ListData.h"	// Added by ClassView
#include "LED300Data.h"		// Added by ClassView
#include "OpSetupData.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//Doc把消息发到View,已便开副线程
#define    WM_TEST_START           (WM_USER+0x408)         
//class CHaasDatabase;

class CMySpecDoc : public CDocument
{
protected: // create from serialization only
	CMySpecDoc();
	DECLARE_DYNCREATE(CMySpecDoc)

// Attributes
public:

// Operations
public:
	BOOL m_bTemp_PreheatTimeMode;
	static int		m_iNType;
	static CString	m_strChecker;
	static BOOL	m_bPrintChecker;
	static CString m_strNewT;

//	CHaasDatabase *m_HaasData;
//	CDaoDatabase m_data;

	//是否需要刷新List表
	BOOL m_bReList;
	BOOL m_bInt;

	//TenView要用的变量
	const int PAGE_N;  //1组个数
	int   m_nActive;   //当前
	int   m_iB;        //起始号

	//
	float m_fSet_IntTime;
	BOOL  m_bSet_AutoTime;
	int   m_iSet_AvgN;

	//当前数据
	CLED300Data m_tempData;
	//保存的测量数据
	CLED300ListData	m_ledData;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySpecDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_strNumber;
	void Calc_B_Active(int iSele);
	virtual ~CMySpecDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMySpecDoc)
	afx_msg void OnExportCsv();
	afx_msg void OnUpdateExportCsv(CCmdUI* pCmdUI);
	afx_msg void OnTest();
	afx_msg void OnUpdateTest(CCmdUI* pCmdUI);
	afx_msg void OnTestCon();
	afx_msg void OnUpdateTestCon(CCmdUI* pCmdUI);
	afx_msg void OnExportSpecCav();
	afx_msg void OnUpdateExportSpecCav(CCmdUI* pCmdUI);
	afx_msg void OnOption();
	afx_msg void OnUpdateOption(CCmdUI* pCmdUI);
	afx_msg void OnSeleSdcm();
	afx_msg void OnUpdateSeleSdcm(CCmdUI* pCmdUI);
	afx_msg void OnTestStop();
	afx_msg void OnUpdateTestStop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAppExit(CCmdUI* pCmdUI);
	afx_msg void OnSetup();
	afx_msg void OnUpdateSetup(CCmdUI* pCmdUI);
	afx_msg void OnButtonTrig();
	afx_msg void OnUpdateButtonTrig(CCmdUI* pCmdUI);
	afx_msg void OnExportAccess();
	afx_msg void OnUpdateExportAccess(CCmdUI* pCmdUI);
	afx_msg void OnPower();
	afx_msg void OnUpdatePower(CCmdUI* pCmdUI);
	afx_msg void OnCheckBw();
	afx_msg void OnUpdateCheckBw(CCmdUI* pCmdUI);
	afx_msg void OnExportAllSpec();
	afx_msg void OnUpdateExportAllSpec(CCmdUI* pCmdUI);
	afx_msg void OnExportLampDat();
	afx_msg void OnUpdateExportLampDat(CCmdUI* pCmdUI);
	afx_msg void OnModGe();
	afx_msg void OnUpdateModGe(CCmdUI* pCmdUI);
	afx_msg void OnExportPhs();
	afx_msg void OnUpdateExportPhs(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSPECDOC_H__799E038A_8CF0_11DB_949D_00055D02EEF1__INCLUDED_)
