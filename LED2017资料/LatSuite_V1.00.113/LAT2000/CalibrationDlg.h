#pragma once
#include "LAT2000Doc.h"

// CCalibrationDlg 对话框

class CCalibrationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCalibrationDlg)

public:
	CCalibrationDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCalibrationDlg();

	void ShowUData(int iRangeU);
	void ShowIData(int iRangeI);

	CLAT2000Doc * m_pDoc;
// 对话框数据
	enum { IDD = IDD_DIALOG_CALIBRATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	CString m_strCalPath;

public:
	int m_iRangeI;
	int m_iRangeU;
	float m_fbI;
	float m_fbU;
	float m_fDAI1;
	float m_fDAI2;
	float m_fDAU1;
	float m_fDAU2;
	float m_fI1;
	float m_fI2;
	float m_fkI;
	float m_fkU;
	float m_fStdI1;
	float m_fStdI2;
	float m_fStdU1;
	float m_fStdU2;
	float m_fU1;
	float m_fU2;
	afx_msg void OnBnClickedButtonCalVoltage();
	afx_msg void OnBnClickedButtonOutputU1();
	afx_msg void OnBnClickedButtonOutputU2();
	afx_msg void OnBnClickedButtonOutputI1();
	afx_msg void OnBnClickedButtonOutputI2();
	afx_msg void OnBnClickedButtonCalCurrent();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboRangeVoltage();
	afx_msg void OnCbnSelchangeComboRangeCurrent();
	afx_msg void OnBnClickedButtonUpload();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonDownload();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonWyReset1();
	afx_msg void OnBnClickedButtonWyReset2();
};
