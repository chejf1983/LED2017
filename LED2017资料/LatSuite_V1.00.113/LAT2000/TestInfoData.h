#pragma once
class CTestInfoData
{
public:
    CTestInfoData(void);
    ~CTestInfoData(void);
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
    CString m_strTMP;
    CString m_strWet;
    float m_fTestRate;
    CString m_strRemark;
    CString m_strTestMachine;
    CString m_strTester;
    CString m_strTestDate;
    BOOL m_bCustomVol_Aging;
    BOOL m_bEMC_Test;
    BOOL m_bHighLowVol_Aging;
    BOOL m_bHighTMP_Aging;
    BOOL m_bNormalTMP_Aging;
    BOOL m_bStaVol_Aging;
    BOOL m_bSwitch_Aging;

    BOOL m_bPrintPageHeadLogo;
    int m_iPageHeadLogoPos;
    CString m_strPrintCap;

    CString m_strPageHeadCap;
    CString m_strPageHeadCapInfo;
    CString m_strPrintSubCap;
    BOOL m_bPrintSubCap;
	CTestInfoData & operator = (const CTestInfoData &data)
	{
		if (this == &data)
		{
			return *this;
		}
		m_strLampName = data.m_strLampName;
		m_strLampNote = data.m_strLampNote;
		m_strLampNum = data.m_strLampNum;
		m_strLampRule = data.m_strLampRule;
		m_fStaPow = data.m_fStaPow;
		m_fStaFlux = data.m_fStaFlux;
		m_fStaTc = data.m_fStaTc;
		m_fStaVol = data.m_fStaVol;
		m_strComboInerface = data.m_strComboInerface;
		m_strFactory = data.m_strFactory;
		m_strLampModel = data.m_strLampModel;
		m_strTMP = data.m_strTMP;
		m_strWet = data.m_strWet;
		m_fTestRate = data.m_fTestRate;
		m_strRemark = data.m_strRemark;
		m_strTestMachine = data.m_strTestMachine;
		m_strTester = data.m_strTester;
		m_strTestDate = data.m_strTestDate;
		m_bCustomVol_Aging = data.m_bCustomVol_Aging;
		m_bEMC_Test = data.m_bEMC_Test;
		m_bHighLowVol_Aging = data.m_bHighLowVol_Aging;
		m_bHighTMP_Aging = data.m_bHighTMP_Aging;
		m_bNormalTMP_Aging = data.m_bNormalTMP_Aging;
		m_bStaVol_Aging = data.m_bStaVol_Aging;
		m_bSwitch_Aging = data.m_bSwitch_Aging;

		m_bPrintPageHeadLogo = data.m_bPrintPageHeadLogo;
		m_iPageHeadLogoPos = data.m_iPageHeadLogoPos;
		m_strPrintCap = data.m_strPrintCap;

		m_strPageHeadCap = data.m_strPageHeadCap;
		m_strPageHeadCapInfo = data.m_strPageHeadCapInfo;
		m_strPrintSubCap = data.m_strPrintSubCap;
		m_bPrintSubCap = data.m_bPrintSubCap;
		return *this;		
	}
	void LoadTestInfoSection();
	void SaveTestInfoSection();
	BOOL Serialize(CArchive & ar)
	{
		CString strDev;
		if (ar.IsStoring())
		{
			strDev = "TestInfoData v1.00";
			ar << strDev;
			ar << m_strLampName;
			ar << m_strLampNote;
			ar << m_strLampNum;
			ar << m_strLampRule;
			ar << m_fStaPow;
			ar << m_fStaFlux;
			ar << m_fStaTc;
			ar << m_fStaVol;
			ar << m_strComboInerface;
			ar << m_strFactory;
			ar << m_strLampModel;
			ar << m_strTMP;
            ar << m_strWet;
            ar << m_fTestRate;
            ar << m_strRemark;
            ar << m_strTestMachine;
            ar << m_strTester;
            ar << m_strTestDate;
            ar << m_bCustomVol_Aging;
            ar << m_bEMC_Test;
            ar << m_bHighLowVol_Aging;
            ar << m_bHighTMP_Aging;
            ar << m_bNormalTMP_Aging;
            ar << m_bStaVol_Aging;
            ar << m_bSwitch_Aging;

            ar << m_bPrintPageHeadLogo;
            ar << m_iPageHeadLogoPos;
            ar << m_strPrintCap;

            ar << m_strPageHeadCap;
            ar << m_strPageHeadCapInfo;
            ar << m_strPrintSubCap;
            ar << m_bPrintSubCap;
        }
        else
        {
            ar >> strDev;
            if (strDev != "TestInfoData v1.00")
            {
                return FALSE;
            }
            ar >> m_strLampName;
            ar >> m_strLampNote;
            ar >> m_strLampNum;
            ar >> m_strLampRule;
            ar >> m_fStaPow;
            ar >> m_fStaFlux;
            ar >> m_fStaTc;
            ar >> m_fStaVol;
            ar >> m_strComboInerface;
            ar >> m_strFactory;
            ar >> m_strLampModel;
            ar >> m_strTMP;
            ar >> m_strWet;
            ar >> m_fTestRate;
            ar >> m_strRemark;
            ar >> m_strTestMachine;
            ar >> m_strTester;
            ar >> m_strTestDate;
            ar >> m_bCustomVol_Aging;
            ar >> m_bEMC_Test;
            ar >> m_bHighLowVol_Aging;
            ar >> m_bHighTMP_Aging;
            ar >> m_bNormalTMP_Aging;
            ar >> m_bStaVol_Aging;
            ar >> m_bSwitch_Aging;

            ar >> m_bPrintPageHeadLogo;
            ar >> m_iPageHeadLogoPos;
            ar >> m_strPrintCap;

            ar >> m_strPageHeadCap;
            ar >> m_strPageHeadCapInfo;
            ar >> m_strPrintSubCap;
            ar >> m_bPrintSubCap;
        }
        return TRUE;
    }
};

