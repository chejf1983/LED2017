#pragma once


// CConfigure_ExaminationPage �Ի���

class CConfigure_ExaminationPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CConfigure_ExaminationPage)

public:
	CConfigure_ExaminationPage();
	virtual ~CConfigure_ExaminationPage();

// �Ի�������
	enum { IDD = IDD_CONFIGUE_EXAMINATION_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    BOOL m_bLightning;
    BOOL m_bVoltageUpAndDips;

    CString m_strLightningCOM;
    CString m_strVoltageUpAndDipsCOM;

    afx_msg void OnBnClickedButtonLightning();
    afx_msg void OnBnClickedButtonVoltageUpanddips();
    virtual BOOL OnInitDialog();
    BOOL m_bCustomVolAging;
    int m_iCustomVolAgingCOM;
    afx_msg void OnBnClickedButtonCustomVolAging();
};
