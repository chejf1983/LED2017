#pragma once
#include "TestSettingsData.h"

// CRectificationTestDlg 对话框

class CRectificationTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRectificationTestDlg)

public:
	CRectificationTestDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRectificationTestDlg();

	float m_fStdValue[DATA_CAHNNEL_NUM];
	float m_fShowValue[DATA_CAHNNEL_NUM];
	float m_fTestValue1[DATA_CAHNNEL_NUM];
	float m_fTestValue2[DATA_CAHNNEL_NUM];
    float m_fCurrentA[DATA_CAHNNEL_NUM];

// 对话框数据
	enum { IDD = IDD_RECTIFICATION_TEST };

public:
	BOOL IsTesting();
	BOOL m_bCancel; //取消校正
	void EnableAllData(BOOL bTest);

protected:
	CTime m_timeStart;
	BOOL m_bIsElectricalRunning;
	BOOL m_bIsSpectrumRunning;
	CEvent m_eventOneLEDSpectrumOK;
	CEvent m_eventOneLEDON;
	static UINT ThreadElectrical(LPVOID pPar);
	static UINT ThreadSpectrum(LPVOID pPar);

	//2013.8.31 杨 增加校正简单方式
	static UINT ThreadSpectrumCorr(LPVOID pPar);

	void SetResult(int iIndex, float fFlux);

public:
	BOOL m_pbTestChannel[DATA_CAHNNEL_NUM];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonTest();
	CString m_strFlux1;
	CString m_strFlux10;
	CString m_strFlux2;
	CString m_strFlux3;
	CString m_strFlux4;
	CString m_strFlux5;
	CString m_strFlux6;
	CString m_strFlux7;
	CString m_strFlux8;
	CString m_strFlux9;
	int m_iWarmUpTimeMinute;
	int m_iElectricalHeatingmsec;
	float m_fFrequency;
	float m_fVoltage;
	float m_fIntegralTimems;
	virtual void OnCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOneStep();
	afx_msg void OnBnClickedButtonInPosition();
	CString m_strStdFlux1;
	CString m_strStdFlux2;
	CString m_strStdFlux3;
	CString m_strStdFlux4;
	CString m_strStdFlux5;
	CString m_strStdFlux6;
	CString m_strStdFlux7;
	CString m_strStdFlux8;
	CString m_strStdFlux9;
	CString m_strStdFlux10;
	void CRectificationTestDlg::EnaleControls_bDisor_LowExecu();
    float m_fSetFrequency;
    float m_fSetVoltage;
	int m_iRangeU;
	int m_iRangeI;
	int m_iRangeCF;
	CComboBox m_cRangeV;
	CComboBox m_cRangeI;
	afx_msg void OnCbnSelchangeComboCf2();
	afx_msg void OnBnClickedButtonTestStop();
};
