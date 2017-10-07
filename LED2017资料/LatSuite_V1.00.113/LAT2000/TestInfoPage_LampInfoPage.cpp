// TestInfoPage_LampInfoPage.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "TestInfoPage_LampInfoPage.h"
#include "afxdialogex.h"


// CTestInfoPage_LampInfoPage 对话框

IMPLEMENT_DYNAMIC(CTestInfoPage_LampInfoPage, CPropertyPage)

CTestInfoPage_LampInfoPage::CTestInfoPage_LampInfoPage()
	: CPropertyPage(CTestInfoPage_LampInfoPage::IDD)
{

    m_strLampName = _T("");
    m_strLampNote = _T("");
    m_strLampNum = _T("");
    m_strLampRule = _T("");
    m_fStaPow = 0.0f;
    m_fStaFlux = 0.0f;
    m_fStaTc = 0.0f;
    m_fStaVol = 0.0f;
    m_strComboInerface = _T("");
    m_strFactory = _T("");
    m_strLampModel = _T("");
}

CTestInfoPage_LampInfoPage::~CTestInfoPage_LampInfoPage()
{
}

void CTestInfoPage_LampInfoPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_NAME, m_strLampName);
    DDX_Text(pDX, IDC_EDIT_NOTE, m_strLampNote);
    DDX_Text(pDX, IDC_EDIT_NUMBER, m_strLampNum);
    DDX_Text(pDX, IDC_EDIT_RULE, m_strLampRule);
    DDX_Text(pDX, IDC_EDIT_STA_POW, m_fStaPow);
    DDX_Text(pDX, IDC_EDIT_STA_FLUX, m_fStaFlux);
    DDX_Text(pDX, IDC_EDIT_STA_TC, m_fStaTc);
    DDX_Text(pDX, IDC_EDIT_STA_VOL, m_fStaVol);
    DDX_CBString(pDX, IDC_COMBO_INTERFACE, m_strComboInerface);
    DDX_Text(pDX, IDC_EDIT_FACTORY, m_strFactory);
    DDX_Text(pDX, IDC_EDIT_MODEL, m_strLampModel);
}


BEGIN_MESSAGE_MAP(CTestInfoPage_LampInfoPage, CPropertyPage)
END_MESSAGE_MAP()


// CTestInfoPage_LampInfoPage 消息处理程序
