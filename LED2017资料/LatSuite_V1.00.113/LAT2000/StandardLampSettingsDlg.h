#pragma once


// CStandardLampSettingsDlg �Ի���

class CStandardLampSettingsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStandardLampSettingsDlg)

public:
	CStandardLampSettingsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStandardLampSettingsDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_STANDARD_LAMP_SETTINGS};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	float m_fCurrent;
	float m_fProtectVoltage;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonOff();
};
