#pragma once


// CTestInfoPage_LampInfoPage 对话框

class CTestInfoPage_LampInfoPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CTestInfoPage_LampInfoPage)

public:
	CTestInfoPage_LampInfoPage();
	virtual ~CTestInfoPage_LampInfoPage();

// 对话框数据
	enum { IDD = IDD_TESTINFO_PAGE_LED_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    CString m_strLampName;
    CString m_strLampNote;
    CString m_strLampNum;
    CString m_strLampRule;
    float m_fStaPow;
    float m_fStaFlux;
    float m_fStaTc;
    float m_fStaVol;
    CString m_strComboInerface;
    CString m_strFactory;
    CString m_strLampModel;
};
