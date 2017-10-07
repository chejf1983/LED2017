// HighPowerInterfaceDlg.h : header file
//
//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES

#if !defined(AFX_HIGHPOWERINTERFACEDLG_H__C5B72339_1035_4858_9B37_4F730F9B11B1__INCLUDED_)
#define AFX_HIGHPOWERINTERFACEDLG_H__C5B72339_1035_4858_9B37_4F730F9B11B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resFile\coolmenu\CoolMenu.h"
#include "Functions.h"
#include "ChipsHandle.h"
#include "highpower.h"
#include "HolyChipOptics.h"
#include "ControlsDlg.h"
#include "ShowTestDlg.h"
#include "StatisticDlg.h"
#include "BinDlg.h"
#include "AuthorityView.h"
#include "ShootDiagram.h"
#include "CIEDiagram.h"
#include "Spectrum.h"
#include "Status.h"
#include "AddUsersDlg.h"
#include "DeleteUsersDlg.h"
#include "RegisterDlg.h"
#include "INITIALDlg.h"
#include "Wizard.h"
#include "SpectrumSetting.h"
#include "SetSpmReadParam.h"
#include "SetSpmSaveRefer.h"
#include "SetSpmSaveDark.h"
#include "SetSpmReadLmp.h"
#include "SetSpmCompen.h"
#include "Light.h"
#include "SettingDlg.h"
#include "SystemSetting.h"
#include "ShowLevel.h"
#include "SetPrint.h"
/////////////////////////////////////////////////////////////////////////////
// CHighPowerInterfaceDlg dialog
struct threadInfo
{
	CShowTestDlg *m_showtest;
	CControlsDlg *m_control;
	CSpectrum *m_spectrum;
	CCIEDiagram *m_CIEdiagram;
	CStatisticDlg *m_statistic;
	CBinDlg *m_bin;
	CShootDiagram *m_shoot;
	ShowLevel *m_showlevel;
	CAuthorityView *m_authorityview;
};
class CHighPowerInterfaceDlg : public CDialog
{
// Construction
public:
	CHighPowerInterfaceDlg(CWnd* pParent = NULL);	// standard constructor
	CCoolMenu m_menu;
	CReBar m_rebar;
	CImageList m_Imagelist;
	CStatus m_status;
	CAddUsersDlg m_addusers;
	CDeleteUsersDlg m_deleteusers;
	CRegisterDlg m_register;
	CINITIALDlg m_initial;
	CSystemSetting m_systemsetting;
	CSpectrumSetting m_spectrumsetting;
	CShootDiagram m_shootdiagram;
	ShowLevel m_showlevel;
	
// Dialog Data
	//{{AFX_DATA(CHighPowerInterfaceDlg)
	enum { IDD = IDD_HIGHPOWERINTERFACE_DIALOG };
	CMSComm	m_ctrlComm;
	//}}AFX_DATA
	void InitMenu();
	bool InitToolBar();
	bool InitWindows();
	bool InitMultipleTest();
	void OnInitDlgs();
	bool InitComm(bool response);
	void OnTestSingle();
	void OnTestContinuous();
    void OnTestAuto();
	void OnStopTest();
	void OnRestartTest();
	void OnEngineer();
	void OnOperator();
	void OnGuest();
	void StartSingleTest();
	bool showMenu();
	bool HideMenu();

	bool checkprint(int num);

	afx_msg void OnStartClearBox();
	afx_msg void OnStopClearBox();
		
//	afx_msg LONG OnDataReady(UINT wParam,LONG lParam);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHighPowerInterfaceDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	HICON m_hIcon;
	CToolBar m_toolbar;
	CToolBarCtrl *btn;
	CControlsDlg m_controlsdlg;
	CShowTestDlg m_showtestdlg;
	CStatisticDlg m_statisticdlg;
	CBinDlg m_bindlg;
	CAuthorityView m_authorityview;
	CSpectrum m_spectrum;
	CCIEDiagram m_CIEdiagram;
	// Generated message map functions
	//{{AFX_MSG(CHighPowerInterfaceDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnClearUp();
	afx_msg void OnOpenFile();
	afx_msg void OnSaveFile();
	afx_msg void OnSaveAs();
	afx_msg void OnShoot();
	afx_msg void OnSpectrum();
	afx_msg void OnColorTemperature();
	afx_msg void OnCheckLog();
	afx_msg void OnRegistInformation();
	afx_msg void OnManual();
	afx_msg void OnAbout();
	afx_msg void OnConnect();
	afx_msg void OnToolOpenFile();
	afx_msg void OnToolSaveFile();
	afx_msg void OnToolSaveAs();
	afx_msg void OnExit();
	afx_msg void OnSetParameter();
	afx_msg void OnSystemSetting();
	afx_msg void OnNewFile();
	afx_msg void CheckMenuHandle(UINT nID, CString text);
	afx_msg void OnAddUsers();
	afx_msg void OnDeleteUsers();
	afx_msg void OnSetSpectrum();
	afx_msg void OnSaveTestedData();
	afx_msg void OnSettingParam();
	afx_msg void OnSetSpm();
	afx_msg void OnCheckShowSetting();
	afx_msg void OnRADIOOneLine();
	afx_msg void OnRADIOList();
	afx_msg bool OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnResistance();
	afx_msg void OnRegist();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnExportBinCode();
	afx_msg void OnExportNewCIE();
	afx_msg void OnshowLevelSet();
	afx_msg void OnSetPrint();
	afx_msg void OnClearBinBox();
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HIGHPOWERINTERFACEDLG_H__C5B72339_1035_4858_9B37_4F730F9B11B1__INCLUDED_)
