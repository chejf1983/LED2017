#pragma once


// CConfigure_OthersPage �Ի���

class CConfigure_OthersPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CConfigure_OthersPage)

public:
	CConfigure_OthersPage();
	virtual ~CConfigure_OthersPage();

// �Ի�������
	enum { IDD = IDD_CONFIGUE_OTHERS_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    // Cal Range
    CString m_strCalibrationRange;
    // Total Board
    UINT m_iTotalBoard;
    int m_iLEDTestAndLEDDownRange;
    int m_iLEDOnAndLEDTestRange;
	int m_iSpectialLEDOnAndLEDTestRange;
	int m_iJydzLedTestRange;
	int m_iNyyLedTestRange;
	int m_iXldlLedTestRange;
};
