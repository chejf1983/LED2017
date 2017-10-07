// Configure_OthersPage.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "Configure_OthersPage.h"
#include "afxdialogex.h"


// CConfigure_OthersPage 对话框

IMPLEMENT_DYNAMIC(CConfigure_OthersPage, CPropertyPage)

CConfigure_OthersPage::CConfigure_OthersPage()
	: CPropertyPage(CConfigure_OthersPage::IDD)
	, m_iJydzLedTestRange(0)
	, m_iNyyLedTestRange(0)
	, m_iXldlLedTestRange(0)
{

	m_iLEDTestAndLEDDownRange = 0;
	m_iLEDOnAndLEDTestRange = 0;
	m_iSpectialLEDOnAndLEDTestRange = 0;
}

CConfigure_OthersPage::~CConfigure_OthersPage()
{
}

void CConfigure_OthersPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_CALIBRATION_RANGE, m_strCalibrationRange);
	DDX_Text(pDX, IDC_EDIT_TOTAL_BROAD_NUM, m_iTotalBoard);
	DDX_Text(pDX, IDC_EDIT_LEDTEST_LEDDOWN_RANGE, m_iLEDTestAndLEDDownRange);
	DDX_Text(pDX, IDC_EDIT_LEDON_LEDTEST_RANGE, m_iLEDOnAndLEDTestRange);
	DDX_Text(pDX, IDC_EDIT_SPECTIAL_LEDON_LEDTEST_RANGE, m_iSpectialLEDOnAndLEDTestRange);
	DDX_Text(pDX, IDC_EDIT_JYDZ_LEDTEST_RANGE, m_iJydzLedTestRange);
	DDX_Text(pDX, IDC_EDIT_NYY_LEDTEST_RANGE, m_iNyyLedTestRange);
	DDX_Text(pDX, IDC_EDIT_XLDL_LEDTEST_RANGE, m_iXldlLedTestRange);
}


BEGIN_MESSAGE_MAP(CConfigure_OthersPage, CPropertyPage)
END_MESSAGE_MAP()


// CConfigure_OthersPage 消息处理程序
