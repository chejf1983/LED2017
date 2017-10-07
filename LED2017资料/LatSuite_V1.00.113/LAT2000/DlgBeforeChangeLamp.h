#pragma once
#include "TestSettingsData.h"
#include "TestInfoData.h"

// CDlgBeforeChangeLamp �Ի���

class CDlgBeforeChangeLamp : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBeforeChangeLamp)

public:
	CDlgBeforeChangeLamp(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgBeforeChangeLamp();

// �Ի�������
	enum { IDD = IDD_DIALOG_BEFORE_CHANGE_LAMP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonParaSet();
public:
	CTestSettingsData m_TestSettingsData;
	CString m_strFileName;
	BOOL m_bAutoSave;
	CString m_strFilePath;
	CString m_strFileDataNum;
	CTestInfoData TestInfoData;


    afx_msg void OnBnClickedButtonScan2();
    afx_msg void OnBnClickedRadioAutoSave1();
    afx_msg void OnBnClickedRadioAutoSave2();
    afx_msg void OnBnClickedButtonTestinfo();
    int m_iSaveType;
    int m_iPrefixInputMode;
    afx_msg void OnBnClickedRadioNum();
    afx_msg void OnBnClickedRadioDay();
    afx_msg void OnBnClickedRadioManuInput();
    afx_msg void OnBnClickedRadioManuInput2();
};
