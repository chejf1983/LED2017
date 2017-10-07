#include "StdAfx.h"
#include "TestInfoData.h"


CTestInfoData::CTestInfoData(void)
{
    LoadTestInfoSection();
}


CTestInfoData::~CTestInfoData(void)
{
    SaveTestInfoSection();
}


void CTestInfoData::LoadTestInfoSection()
{
    CString strSection= _T("TestInfoSection");
    CString str_m_strLampName = _T("m_strLampName");
    CString str_m_strLampNote = _T("m_strLampNote");
    CString str_m_strLampNum = _T("m_strLampNum");
    CString str_m_strLampRule = _T("m_strLampRule");
    CString str_m_fStaPow = _T("m_fStaPow");
    CString str_m_fStaFlux = _T("m_fStaFlux");
    CString str_m_fStaTc = _T("m_fStaTc");
    CString str_m_fStaVol = _T("m_fStaVol");
    CString str_m_strComboInerface = _T("m_strComboInerface");
    CString str_m_strFactory = _T("m_strFactory");
    CString str_m_strLampModel = _T("m_strLampModel");
    CString str_m_strTMP = _T("m_strTMP");
    CString str_m_strWet = _T("m_strWet");
    CString str_m_fTestRate = _T("m_fTestRate");
    CString str_m_strRemark = _T("m_strRemark");
    CString str_m_strTestMachine = _T("m_strTestMachine");
    CString str_m_strTester = _T("m_strTester");
    CString str_m_strTestDate = _T("m_strTestDate");
    CString str_m_bCustomVol_Aging = _T("m_bCustomVol_Aging");
    CString str_m_bEMC_Test = _T("m_bEMC_Test");
    CString str_m_bHighLowVol_Aging = _T("m_bHighLowVol_Aging");
    CString str_m_bHighTMP_Aging = _T("m_bHighTMP_Aging");
    CString str_m_bNormalTMP_Aging = _T("m_bNormalTMP_Aging");
    CString str_m_bStaVol_Aging = _T("m_bStaVol_Aging");
    CString str_m_bSwitch_Aging = _T("m_bSwitch_Aging");

    CString strTemp;
    m_strLampName = AfxGetApp()->GetProfileString(strSection, str_m_strLampName, _T("LEDÇòÅÝµÆ"));
    m_strLampNote = AfxGetApp()->GetProfileString(strSection, str_m_strLampNote, _T(""));
    m_strLampNum = AfxGetApp()->GetProfileString(strSection, str_m_strLampNum, _T("L20130617"));
    m_strLampRule = AfxGetApp()->GetProfileString(strSection, str_m_strLampRule, _T("LR2013"));
    strTemp = AfxGetApp()->GetProfileString(strSection, str_m_fStaPow, _T("9"));
    m_fStaPow = (float)atof(strTemp);
    strTemp = AfxGetApp()->GetProfileString(strSection, str_m_fStaFlux, _T("470"));
    m_fStaFlux = (float)atof(strTemp);
    strTemp = AfxGetApp()->GetProfileString(strSection, str_m_fStaTc, _T("2700"));
    m_fStaTc = (float)atof(strTemp);
    strTemp = AfxGetApp()->GetProfileString(strSection, str_m_fStaVol, _T("220"));
    m_fStaVol = (float)atof(strTemp);
    m_strComboInerface = AfxGetApp()->GetProfileString(strSection, str_m_strComboInerface, _T("E27"));
    m_strFactory = AfxGetApp()->GetProfileString(strSection, str_m_strFactory, _T("JXSH"));
    m_strLampModel = AfxGetApp()->GetProfileString(strSection, str_m_strLampModel, _T("L20130617"));
    m_strTMP = AfxGetApp()->GetProfileString(strSection, str_m_strTMP, _T("20"));
    m_strWet = AfxGetApp()->GetProfileString(strSection, str_m_strWet, _T("60"));
    strTemp = AfxGetApp()->GetProfileString(strSection, str_m_fTestRate, _T("1200"));
    m_fTestRate = (float)atof(strTemp);
    m_strRemark = AfxGetApp()->GetProfileString(strSection, str_m_strRemark, _T(""));
    m_strTestMachine = AfxGetApp()->GetProfileString(strSection, str_m_strTestMachine, _T("Ô¶·½LAT-2000 LEDµÆ×Ô¶¯ÀÏÁ·²âÊÔÉú²úÏß"));
    m_strTester = AfxGetApp()->GetProfileString(strSection, str_m_strTester, _T("John"));
    m_strTestDate = AfxGetApp()->GetProfileString(strSection, str_m_strTestDate, _T("2013.6.17"));
    m_bCustomVol_Aging = AfxGetApp()->GetProfileInt(strSection, str_m_bCustomVol_Aging, 1);
    m_bEMC_Test = AfxGetApp()->GetProfileInt(strSection, str_m_bEMC_Test, 1);
    m_bHighLowVol_Aging = AfxGetApp()->GetProfileInt(strSection, str_m_bHighLowVol_Aging, 1);
    m_bHighTMP_Aging = AfxGetApp()->GetProfileInt(strSection, str_m_bHighTMP_Aging, 1);
    m_bNormalTMP_Aging = AfxGetApp()->GetProfileInt(strSection, str_m_bNormalTMP_Aging, 1);
    m_bStaVol_Aging = AfxGetApp()->GetProfileInt(strSection, str_m_bStaVol_Aging, 1);
    m_bSwitch_Aging = AfxGetApp()->GetProfileInt(strSection, str_m_bSwitch_Aging, 1);



    CString str_m_bPrintPageHeadLogo = _T("m_bPrintPageHeadLogo");
    CString str_m_iPageHeadLogoPos = _T("m_iPageHeadLogoPos");
    CString str_m_strPrintCap = _T("m_strPrintCap");
    CString str_m_strPageHeadCap = _T("m_strPageHeadCap");
    CString str_m_strPageHeadCapInfo = _T("m_strPageHeadCapInfo");
    CString str_m_strPrintSubCap = _T("m_strPrintSubCap");
    CString str_m_bPrintSubCap = _T("m_bPrintSubCap");

    m_bPrintPageHeadLogo = AfxGetApp()->GetProfileInt(strSection, str_m_bPrintPageHeadLogo, 1);
    m_iPageHeadLogoPos = AfxGetApp()->GetProfileInt(strSection, str_m_iPageHeadLogoPos, 0);
    m_strPrintCap = AfxGetApp()->GetProfileString(strSection, str_m_strPrintCap, _T("LEDÇòÅÝµÆ²âÊÔ±¨¸æ"));
    m_strPageHeadCap = AfxGetApp()->GetProfileString(strSection, str_m_strPageHeadCap, _T("LEDÇòÅÝµÆ²âÊÔ±¨¸æ"));
    m_strPageHeadCapInfo = AfxGetApp()->GetProfileString(strSection, str_m_strPageHeadCapInfo, _T("°æ±¾ºÅV1.00"));
    m_strPrintSubCap = AfxGetApp()->GetProfileString(strSection, str_m_strPrintSubCap, _T(""));
    m_bPrintSubCap = AfxGetApp()->GetProfileInt(strSection, str_m_bPrintSubCap, 1);
}


void CTestInfoData::SaveTestInfoSection()
{
    CString strSection= _T("TestInfoSection");
    CString str_m_strLampName = _T("m_strLampName");
    CString str_m_strLampNote = _T("m_strLampNote");
    CString str_m_strLampNum = _T("m_strLampNum");
    CString str_m_strLampRule = _T("m_strLampRule");
    CString str_m_fStaPow = _T("m_fStaPow");
    CString str_m_fStaFlux = _T("m_fStaFlux");
    CString str_m_fStaTc = _T("m_fStaTc");
    CString str_m_fStaVol = _T("m_fStaVol");
    CString str_m_strComboInerface = _T("m_strComboInerface");
    CString str_m_strFactory = _T("m_strFactory");
    CString str_m_strLampModel = _T("m_strLampModel");
    CString str_m_strTMP = _T("m_strTMP");
    CString str_m_strWet = _T("m_strWet");
    CString str_m_fTestRate = _T("m_fTestRate");
    CString str_m_strRemark = _T("m_strRemark");
    CString str_m_strTestMachine = _T("m_strTestMachine");
    CString str_m_strTester = _T("m_strTester");
    CString str_m_strTestDate = _T("m_strTestDate");
    CString str_m_bCustomVol_Aging = _T("m_bCustomVol_Aging");
    CString str_m_bEMC_Test = _T("m_bEMC_Test");
    CString str_m_bHighLowVol_Aging = _T("m_bHighLowVol_Aging");
    CString str_m_bHighTMP_Aging = _T("m_bHighTMP_Aging");
    CString str_m_bNormalTMP_Aging = _T("m_bNormalTMP_Aging");
    CString str_m_bStaVol_Aging = _T("m_bStaVol_Aging");
    CString str_m_bSwitch_Aging = _T("m_bSwitch_Aging");

    CString strTemp;
    AfxGetApp()->WriteProfileString(strSection, str_m_strLampName, m_strLampName);
    AfxGetApp()->WriteProfileString(strSection, str_m_strLampNote, m_strLampNote);
    AfxGetApp()->WriteProfileString(strSection, str_m_strLampNum, m_strLampNum);
    AfxGetApp()->WriteProfileString(strSection, str_m_strLampRule, m_strLampRule);
    strTemp.Format(_T("%g"), m_fStaPow);
    AfxGetApp()->WriteProfileString(strSection, str_m_fStaPow, strTemp);
    strTemp.Format(_T("%g"), m_fStaFlux);
    AfxGetApp()->WriteProfileString(strSection, str_m_fStaFlux, strTemp);
    strTemp.Format(_T("%g"), m_fStaTc);
    AfxGetApp()->WriteProfileString(strSection, str_m_fStaTc, strTemp);
    strTemp.Format(_T("%g"), m_fStaVol);
    AfxGetApp()->WriteProfileString(strSection, str_m_fStaVol, strTemp);
    AfxGetApp()->WriteProfileString(strSection, str_m_strComboInerface, m_strComboInerface);
    AfxGetApp()->WriteProfileString(strSection, str_m_strFactory, m_strFactory);
    AfxGetApp()->WriteProfileString(strSection, str_m_strLampModel, m_strLampModel);
    AfxGetApp()->WriteProfileString(strSection, str_m_strTMP, m_strTMP);
    AfxGetApp()->WriteProfileString(strSection, str_m_strWet, m_strWet);
    strTemp.Format(_T("%g"), m_fTestRate);
    AfxGetApp()->WriteProfileString(strSection, str_m_fTestRate, strTemp);
    AfxGetApp()->WriteProfileString(strSection, str_m_strRemark, m_strRemark);
    AfxGetApp()->WriteProfileString(strSection, str_m_strTestMachine, m_strTestMachine);
    AfxGetApp()->WriteProfileString(strSection, str_m_strTester, m_strTester);
    AfxGetApp()->WriteProfileString(strSection, str_m_strTestDate, m_strTestDate);
    AfxGetApp()->WriteProfileInt(strSection, str_m_bCustomVol_Aging, m_bCustomVol_Aging);
    AfxGetApp()->WriteProfileInt(strSection, str_m_bEMC_Test, m_bEMC_Test);
    AfxGetApp()->WriteProfileInt(strSection, str_m_bHighLowVol_Aging, m_bHighLowVol_Aging);
    AfxGetApp()->WriteProfileInt(strSection, str_m_bHighTMP_Aging, m_bHighTMP_Aging);
    AfxGetApp()->WriteProfileInt(strSection, str_m_bNormalTMP_Aging, m_bNormalTMP_Aging);
    AfxGetApp()->WriteProfileInt(strSection, str_m_bStaVol_Aging, m_bStaVol_Aging);
    AfxGetApp()->WriteProfileInt(strSection, str_m_bSwitch_Aging, m_bSwitch_Aging);

    CString str_m_bPrintPageHeadLogo = _T("m_bPrintPageHeadLogo");
    CString str_m_iPageHeadLogoPos = _T("m_iPageHeadLogoPos");
    CString str_m_strPrintCap = _T("m_strPrintCap");
    CString str_m_strPageHeadCap = _T("m_strPageHeadCap");
    CString str_m_strPageHeadCapInfo = _T("m_strPageHeadCapInfo");
    CString str_m_strPrintSubCap = _T("m_strPrintSubCap");
    CString str_m_bPrintSubCap = _T("m_bPrintSubCap");

    AfxGetApp()->WriteProfileInt(strSection, str_m_bPrintPageHeadLogo, m_bPrintPageHeadLogo);
    AfxGetApp()->WriteProfileInt(strSection, str_m_iPageHeadLogoPos, m_iPageHeadLogoPos);
    AfxGetApp()->WriteProfileString(strSection, str_m_strPrintCap, m_strPrintCap);
    AfxGetApp()->WriteProfileString(strSection, str_m_strPageHeadCap, m_strPageHeadCap);
    AfxGetApp()->WriteProfileString(strSection, str_m_strPageHeadCapInfo, m_strPageHeadCapInfo);
    AfxGetApp()->WriteProfileString(strSection, str_m_strPrintSubCap, m_strPrintSubCap);
    AfxGetApp()->WriteProfileInt(strSection, str_m_bPrintSubCap, m_bPrintSubCap);

}