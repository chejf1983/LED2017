#pragma once
#include "TestSettingsData.h"
#include "resource.h"
#include "AlarmSettingsData.h"
#include "afxcmn.h"

// CEditLimitDlg 对话框

class CEditLimitDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEditLimitDlg)

public:
	CEditLimitDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEditLimitDlg();

	BOOL m_bHaveLightning;
	BOOL m_bHaveVoltageUpAndDips;
	BOOL m_bHaveBurnIn;
// 对话框数据
	enum { IDD = IDD_DIALOG_EDIT_LIMIT};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	static UINT ThreadAutoIntegral(LPVOID pPar);
	static float GetIp(float * fAD, int nNum);
	BOOL m_bAutoIntegral;

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOK();
	virtual void OnCancel();

	CTestSettingsData m_LimitData;
    CTestSettingsData m_LimitDataTemp;
	BOOL GetData(CTestSettingsData & data);
	BOOL SetData(CTestSettingsData & data);
	void SetEnable();
	BOOL IsInputModelAndBulbHigh();

	CString m_strCurrentFileName;

public:
	CAlarmSettingsData m_AlarmSettingsData;
	
	float m_fStdFlux[DATA_CAHNNEL_NUM];
	float m_fTestFlux[DATA_CAHNNEL_NUM];
	float m_pfTestFlux2[DATA_CAHNNEL_NUM];
	
	int m_iEMC5ASelectIndex;
	int m_iEMC11KSelectIndex;
	
	int m_iBurnInONSeconds;
	int m_iBurnInOFFSeconds;

	BOOL m_bCheckFlux;
	BOOL m_bCheckHW;
	BOOL m_bCheckLd;
	BOOL m_bCheckLp;
	BOOL m_bCheckPI;
	BOOL m_bCheckPV;

    BOOL m_bCheckP;
    BOOL m_bCheckPF;
    BOOL m_bCheckFre;

	BOOL m_bCheckRa;  
	BOOL m_bCheckTc;
	BOOL m_bChecku;
	BOOL m_bCheckv;
	BOOL m_bCheckx;
	BOOL m_bChecky;
	BOOL m_bCheckPur;
	float m_fLimitFlux;
	float m_fOffsetFlux;
	float m_fLimitHW;
	float m_fOffsetHW;
	float m_fIntegralTime;
	float m_fLimitLd;
	float m_fOffsetLd;
	float m_fLimitLp;
	float m_fOffsetLp;
	float m_fLimitPI;
	float m_fOffsetPI;
	float m_fLimitPur;
	float m_fOffsetPur;
	float m_fLimitPV;
	float m_fOffsetPV;

    float m_fLimitP;
    float m_fOffsetP;   
    float m_fLimitPF;
    float m_fOffsetPF;
    float m_fLimitFre;
    float m_fOffsetFre;

	float m_fLimitRa;
	float m_fOffsetRa;
	float m_fLimitTC;
	float m_fOffsetTc;
	float m_fLimitu;
	float m_fOffsetu;
	float m_fLimitv;
	float m_fOffsetv;
	float m_fLimitx;
	float m_fOffsetx;
	float m_fLimity;
	float m_fOffsety;
	CString m_strDateTime;
	CString m_strLedModel;
	CString m_strPersonName;
	CString m_strRemarks;

public:
	afx_msg void OnBnClickedButtonSave();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonSaveAs();

	afx_msg void OnBnClickedButtonQuit();
	afx_msg void OnBnClickedCheckFlux();
	afx_msg void OnBnClickedCheckTc();
	afx_msg void OnBnClickedCheckX();
	afx_msg void OnBnClickedCheckY();
	afx_msg void OnBnClickedCheckU();
	afx_msg void OnBnClickedCheckV();
	afx_msg void OnBnClickedCheckLd();
	afx_msg void OnBnClickedCheckLp();
	afx_msg void OnBnClickedCheckPur();
	afx_msg void OnBnClickedCheckHw();
	afx_msg void OnBnClickedCheckPv();
	afx_msg void OnBnClickedCheckNv();
	afx_msg void OnBnClickedCheckPi();
	afx_msg void OnBnClickedCheckNi();
	afx_msg void OnBnClickedCheckRa();
	afx_msg void OnBnClickedCheckTestReverse();
	afx_msg void OnBnClickedButtonAutoIntegral();
	afx_msg void OnClose();
	float m_fTestVoltage;
	float m_fLEDWarmUPTimemsec;
	float m_fTestFrequency;
	BOOL m_bTestCh1;
	BOOL m_bTestCh10;
	BOOL m_bTestCh2;
	BOOL m_bTestCh3;
	BOOL m_bTestCh4;
	BOOL m_bTestCh5;
	BOOL m_bTestCh6;
	BOOL m_bTestCh7;
	BOOL m_bTestCh8;
	float m_fK1;
	float m_fK10;
	float m_fK2;
	float m_fK3;
	float m_fK4;
	float m_fK5;
	float m_fK6;
	float m_fK7;
	float m_fK8;
	float m_fK9;
	BOOL m_bTestCh9;
	afx_msg void OnBnClickedButtonSetK1();
	afx_msg void OnBnClickedButtonLightning();
	afx_msg void OnBnClickedButtonUpanddips();
	afx_msg void OnBnClickedButtonBurnIn();
	afx_msg void OnBnClickedButtonTest();
	float m_fOffsetFlux_;
	float m_fOffsetHW_;
	float m_fOffsetLd_;
	float m_fOffsetLp_;
	float m_fOffsetPI_;
	float m_fOffsetPur_;
	float m_fOffsetPV_;

    float m_fOffsetP_;
    float m_fOffsetPF_;
    float m_fOffsetFre_;

	float m_fOffsetRa_;
	float m_fOffsetTc_;
	float m_fOffsetu_;
	float m_fOffsetv_;
	float m_fOffsetx_;
	float m_fOffsety_;
	int m_iRangeCF;
	int m_iRangeI;
	int m_iRangeU;
	BOOL m_bCheckLuminousPower;
	float m_fLimitLuminousPower;
	float m_fOffsetLuminousPower;
	float m_fOffsetLuminousPower_;
	afx_msg void OnBnClickedCheckLpower();
	BOOL m_bThunderChannel1;
	BOOL m_bThunderChannel2;
	BOOL m_bThunderChannel3;
	BOOL m_bThunderChannel4;
	BOOL m_bThunderChannel5;
	BOOL m_bThunderChannel6;
	BOOL m_bThunderChannel7;
	BOOL m_bThunderChannel8;
	BOOL m_bThunderChannel9;
	BOOL m_bThunderChannel10;
	afx_msg void OnBnClickedButtonAlarm();
	float m_fBallHigh;
    afx_msg void OnCbnSelchangeComboCf();
    CComboBox m_cRangeV;
    CComboBox m_cRangeI;
    afx_msg void OnBnClickedCheckPf();
    afx_msg void OnBnClickedCheckP();
    afx_msg void OnBnClickedCheckFre();

    BOOL m_bTestLightning;
    BOOL m_bTestVoltageUpAndDips;
    BOOL m_bTestBurnIn;
    int m_iTestMinSeconds;
    BOOL m_bTestDirectionOpposite;
	BOOL m_bTestAutoHand;

    void Enable_bDisor_LowExecu(void);
	void EnaleControls_bDisor_LowExecu(void);

    BOOL m_bCheckR9;
    float m_fOffsetR9;
    float m_fOffsetR9_;
    float m_fLimitR9;
    CListCtrl m_cList;
    CButton m_btAdd;
    CButton m_btMod;
    CButton m_btDel;
    float m_fLimitVal;
    float m_fLimitVal_Offset1;
    float m_fLimitVal_Offset2;
    BOOL m_bCheckJudge;
    CComboBox m_comboLimitParaName;
    CEdit m_cLimitVal;
    CEdit m_cLimitVal_Offset1;
    CEdit m_cLimitVal_Offset2;
    afx_msg void OnBnClickedCheckJudge();
    afx_msg void OnBnClickedButtonAdd();
    afx_msg void OnBnClickedButtonMod();
    afx_msg void OnBnClickedButtonDel();
    int m_iListSel;
    int m_iCurParaLimit;
    LimitStruct m_OneParaLimit;
    void GetLimitFromView();
    void SetLimittoView();
    afx_msg void OnNMClickListLimit(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
    BOOL m_bLowELorDisOnly;
    float m_fStaPow;
    float m_fStaFlux;
    float m_fStaTc;
    float m_fStaVol;

    float m_fLEDUnOnPow;
    float m_fLEDUnOnFlux;

    BOOL m_bStatistic;
    BOOL m_bLoadFile_WhenStart;
	afx_msg void OnBnClickedCheckAutorange();
	afx_msg void OnBnClickedButtonMy();

	BOOL m_bTestMyLast;
	BOOL m_bTestSaft;
	afx_msg void OnBnClickedButton5();

	afx_msg void OnBnClickedButtonSdcm();
};
