#pragma once
#include "LAT2000.h"

// CAlarmSettingsDlg 对话框

class CAlarmSettingsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAlarmSettingsDlg)

public:
	CAlarmSettingsDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAlarmSettingsDlg();

// 对话框数据
	enum { IDD = IDD_ALARM_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bStopTest;

    // Region
    BOOL m_bCurRegion;
    CArray<BOOL, BOOL>m_bRegion;

    int m_iCurRegionRingIndex;
    CArray<int, int> m_iRegionRingIndex;

	float m_fCurCurrentH;
    CArray<float, float>m_fCurrentH;

	float m_fCurCurrentL;
    CArray<float, float>m_fCurrentL;

	float m_fCurPowerH;
    CArray<float, float>m_fPowerH;

	float m_fCurPowerL;
    CArray<float, float>m_fPowerL;

    float m_fCurVoltageH;
    CArray<float, float>m_fVoltageH;

    float m_fCurVoltageL;
    CArray<float, float>m_fVoltageL;

    // TMP
    BOOL m_bCurTMP;
    CArray<BOOL, BOOL>m_bTMP;    

    int m_iCurTMPRingIndex;
    CArray<int, int> m_iTMPRingIndex;

	float m_fCurTMPH;
    CArray<float, float>m_fTMPH;    

	float m_fCurTMPL;
    CArray<float, float>m_fTMPL;

	float m_fCurTMPOPEN;
    CArray<float, float>m_fTMPOPEN;

	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	BOOL m_bLampTooHigh;
	BOOL m_bManualStop;

	CComboBox m_cComboLampTooHigh;
	CComboBox m_cComboManualStop;
	CComboBox m_cComboRegion;

	CComboBox m_cComboTMP;
	int m_iLampTooHighRingIndex;
	int m_iManualStopRingIndex;

	afx_msg void OnBnClickedCheckRegion();
	void SetEnable();

    afx_msg void OnBnClickedCheckTmp();
    afx_msg void OnBnClickedCheckLampTooHigh();
    afx_msg void OnBnClickedCheckManualStop();
	void CAlarmSettingsDlg::EnaleControls_bDisor_LowExecu();

    int m_iScanerOverTimeRingIndex;
    BOOL m_bScanerOverTimeAlarm;
    CComboBox m_cScanerOverTime;
    afx_msg void OnBnClickedCheckScanerOvertime();
    CListCtrl m_cListRegion;
    CListCtrl m_cListTMP;
    afx_msg void OnNMClickListRegion(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMClickListTmp(NMHDR *pNMHDR, LRESULT *pResult);

    int m_iListTMPIndex;
    int m_iListRegionIndex;
    afx_msg void OnTimer(UINT_PTR nIDEvent);

    
    void  SetRegionLimittoView();
    void  ListRegionLimit();
    void  SetTMPLimittoView();
    void  ListTMPLimit();

    BOOL m_bLowELorDisOnly;

    // Region
    CButton m_btCurRegionAlarm;
    CEdit m_cCurCurrentH;
    CEdit m_cCurCurrentL;
    CEdit m_cCurPowerH;
    CEdit m_cCurPowerL;
    CEdit m_cCurVoltageH;
    CEdit m_cCurVoltageL;   

    //TMP
    CButton m_btCurTMPAlarm;
    CEdit m_cCurTMPH;
    CEdit m_cCurTMPL;
	CEdit m_cCurTMPOPEN;

    afx_msg void OnBnClickedButtonChangeRegion();
    afx_msg void OnBnClickedButtonChangeTmp();
    CString m_strRegionName;
    CString m_strTMPControlName;
	CEdit m_cTmpOpen;
	float m_fTmpOpen;
	
};
