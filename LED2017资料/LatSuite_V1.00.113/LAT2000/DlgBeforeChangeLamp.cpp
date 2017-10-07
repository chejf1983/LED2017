// DlgBeforeChangeLamp.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DlgBeforeChangeLamp.h"
#include "afxdialogex.h"
#include "EditLimitDlg.h"
#include "LAT2000Doc.h"
#include "MySheet.h"
#include "TestInfoPage_LampInfoPage.h"
#include "TestInfoPage_TestConditionPage.h"   
#include "TestInfoPage_PrintOpinionPage.h"


// CDlgBeforeChangeLamp 对话框

IMPLEMENT_DYNAMIC(CDlgBeforeChangeLamp, CDialogEx)

CDlgBeforeChangeLamp::CDlgBeforeChangeLamp(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgBeforeChangeLamp::IDD, pParent)
{

}

CDlgBeforeChangeLamp::~CDlgBeforeChangeLamp()
{
}

void CDlgBeforeChangeLamp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FILE_NAME, m_strFileName);
	DDX_Radio(pDX, IDC_RADIO_AUTO_SAVE1, m_bAutoSave);
	DDX_Text(pDX, IDC_EDIT_FILE_PATH, m_strFilePath);
	DDX_CBString(pDX, IDC_COMBO_FILE_DATA_NUM, m_strFileDataNum);
    DDX_Radio(pDX, IDC_RADIO_NUM, m_iSaveType);
    DDX_Radio(pDX, IDC_RADIO_MANU_INPUT, m_iPrefixInputMode);
}


BEGIN_MESSAGE_MAP(CDlgBeforeChangeLamp, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PARA_SET, &CDlgBeforeChangeLamp::OnBnClickedButtonParaSet)
	ON_BN_CLICKED(IDC_BUTTON_SCAN2, &CDlgBeforeChangeLamp::OnBnClickedButtonScan2)
	ON_BN_CLICKED(IDC_RADIO_AUTO_SAVE1, &CDlgBeforeChangeLamp::OnBnClickedRadioAutoSave1)
	ON_BN_CLICKED(IDC_RADIO_AUTO_SAVE2, &CDlgBeforeChangeLamp::OnBnClickedRadioAutoSave2)
	ON_BN_CLICKED(IDC_BUTTON_TESTINFO, &CDlgBeforeChangeLamp::OnBnClickedButtonTestinfo)
    ON_BN_CLICKED(IDC_RADIO_NUM, &CDlgBeforeChangeLamp::OnBnClickedRadioNum)
    ON_BN_CLICKED(IDC_RADIO_DAY, &CDlgBeforeChangeLamp::OnBnClickedRadioDay)
    ON_BN_CLICKED(IDC_RADIO_MANU_INPUT, &CDlgBeforeChangeLamp::OnBnClickedRadioManuInput)
    ON_BN_CLICKED(IDC_RADIO_MANU_INPUT2, &CDlgBeforeChangeLamp::OnBnClickedRadioManuInput2)
END_MESSAGE_MAP()


// CDlgBeforeChangeLamp 消息处理程序


BOOL CDlgBeforeChangeLamp::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
    GetDlgItem(IDC_COMBO_FILE_DATA_NUM)->EnableWindow(!m_iSaveType && m_bAutoSave);
    GetDlgItem(IDC_EDIT_FILE_NAME)->EnableWindow(!m_iPrefixInputMode && m_bAutoSave);
    GetDlgItem(IDC_RADIO_NUM)->EnableWindow(m_bAutoSave);
    GetDlgItem(IDC_RADIO_DAY)->EnableWindow(m_bAutoSave);
    GetDlgItem(IDC_RADIO_MANU_INPUT)->EnableWindow(m_bAutoSave);
    GetDlgItem(IDC_RADIO_MANU_INPUT2)->EnableWindow(m_bAutoSave);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgBeforeChangeLamp::OnBnClickedButtonParaSet()
{
	// TODO: 在此添加控件通知处理程序代码
	CEditLimitDlg dlg;
	g_bDisplayLimitOnly = FALSE;
    dlg.m_bLoadFile_WhenStart = TRUE;
	dlg.m_LimitData = m_TestSettingsData;

	if (IDCANCEL == dlg.DoModal())
	{
		return;
	}
	m_TestSettingsData = dlg.m_LimitData; 
}


void CDlgBeforeChangeLamp::OnBnClickedButtonScan2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	char szDir[MAX_PATH];
	BROWSEINFO bi;
	ITEMIDLIST * piDl;
	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szDir;
	bi.lpszTitle = "请选择目录";
	bi.ulFlags = BIF_STATUSTEXT | BIF_USENEWUI | BIF_RETURNFSANCESTORS;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	piDl = SHBrowseForFolder(&bi);
	if (NULL == piDl)
	{
		return;
	}
	else
	{
		SHGetPathFromIDList(piDl, szDir);
		m_strFilePath = szDir;
	}

	UpdateData(FALSE);
}


void CDlgBeforeChangeLamp::OnBnClickedRadioAutoSave1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
    GetDlgItem(IDC_COMBO_FILE_DATA_NUM)->EnableWindow(!m_iSaveType && m_bAutoSave);
    GetDlgItem(IDC_EDIT_FILE_NAME)->EnableWindow(!m_iPrefixInputMode && m_bAutoSave);
    GetDlgItem(IDC_RADIO_NUM)->EnableWindow(m_bAutoSave);
    GetDlgItem(IDC_RADIO_DAY)->EnableWindow(m_bAutoSave);
    GetDlgItem(IDC_RADIO_MANU_INPUT)->EnableWindow(m_bAutoSave);
    GetDlgItem(IDC_RADIO_MANU_INPUT2)->EnableWindow(m_bAutoSave);
}


void CDlgBeforeChangeLamp::OnBnClickedRadioAutoSave2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
    GetDlgItem(IDC_COMBO_FILE_DATA_NUM)->EnableWindow(!m_iSaveType && m_bAutoSave);
    GetDlgItem(IDC_EDIT_FILE_NAME)->EnableWindow(!m_iPrefixInputMode && m_bAutoSave);
    GetDlgItem(IDC_RADIO_NUM)->EnableWindow(m_bAutoSave);
    GetDlgItem(IDC_RADIO_DAY)->EnableWindow(m_bAutoSave);
    GetDlgItem(IDC_RADIO_MANU_INPUT)->EnableWindow(m_bAutoSave);
    GetDlgItem(IDC_RADIO_MANU_INPUT2)->EnableWindow(m_bAutoSave);
	
}


void CDlgBeforeChangeLamp::OnBnClickedButtonTestinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	CMySheet sheet("测试信息");
	CTestInfoPage_LampInfoPage page1;
	CTestInfoPage_TestConditionPage page2;
	CTestInfoPage_PrintOpinionPage page3;
	page1.m_strLampName = TestInfoData.m_strLampName;
	page1.m_strLampNote = TestInfoData.m_strLampNote;
	page1.m_strLampNum = TestInfoData.m_strLampNum;
	page1.m_strLampRule = TestInfoData.m_strLampRule;
	page1.m_fStaPow = TestInfoData.m_fStaPow;
	page1.m_fStaFlux = TestInfoData.m_fStaFlux;
	page1.m_fStaTc = TestInfoData.m_fStaTc;
	page1.m_fStaVol = TestInfoData.m_fStaVol;
	page1.m_strComboInerface = TestInfoData.m_strComboInerface;
	page1.m_strFactory = TestInfoData.m_strFactory;
	page1.m_strLampModel = TestInfoData.m_strLampModel;

	page2.m_strTMP = TestInfoData.m_strTMP;
	page2.m_strWet = TestInfoData.m_strWet;
	page2.m_fTestRate = TestInfoData.m_fTestRate;
	page2.m_strRemark = TestInfoData.m_strRemark;
	page2.m_strTestMachine = TestInfoData.m_strTestMachine;
	page2.m_strTester = TestInfoData.m_strTester;
	page2.m_strTestDate = TestInfoData.m_strTestDate;
	page2.m_bCustomVol_Aging = TestInfoData.m_bCustomVol_Aging;
	page2.m_bEMC_Test = TestInfoData.m_bEMC_Test;
	page2.m_bHighLowVol_Aging = TestInfoData.m_bHighLowVol_Aging;
	page2.m_bHighTMP_Aging = TestInfoData.m_bHighTMP_Aging;
	page2.m_bNormalTMP_Aging = TestInfoData.m_bNormalTMP_Aging;
	page2.m_bStaVol_Aging = TestInfoData.m_bStaVol_Aging;
	page2.m_bSwitch_Aging = TestInfoData.m_bSwitch_Aging;

	page3.m_bPrintPageHeadLogo = TestInfoData.m_bPrintPageHeadLogo;
	page3.m_iPageHeadLogoPos = TestInfoData.m_iPageHeadLogoPos;
	page3.m_bPrintSubCap = TestInfoData.m_bPrintSubCap;
	page3.m_strPageHeadCap = TestInfoData.m_strPageHeadCap;
	page3.m_strPageHeadCapInfo = TestInfoData.m_strPageHeadCapInfo;
	page3.m_strPrintCap = TestInfoData.m_strPrintCap;
	page3.m_strPrintSubCap = TestInfoData.m_strPrintSubCap;

	sheet.AddPage(&page1);
	sheet.AddPage(&page2);
	sheet.AddPage(&page3);
	if (IDCANCEL == sheet.DoModal())
	{
		return;
	}        

	TestInfoData.m_strLampName = page1.m_strLampName;
	TestInfoData.m_strLampNote = page1.m_strLampNote;
	TestInfoData.m_strLampNum = page1.m_strLampNum;
	TestInfoData.m_strLampRule = page1.m_strLampRule;
	TestInfoData.m_fStaPow = page1.m_fStaPow;
	TestInfoData.m_fStaFlux = page1.m_fStaFlux;
	TestInfoData.m_fStaTc = page1.m_fStaTc;
	TestInfoData.m_fStaVol = page1.m_fStaVol;
	TestInfoData.m_strComboInerface = page1.m_strComboInerface;
	TestInfoData.m_strFactory = page1.m_strFactory;
	TestInfoData.m_strLampModel = page1.m_strLampModel;

	TestInfoData.m_strTMP = page2.m_strTMP;
	TestInfoData.m_strWet = page2.m_strWet;
	TestInfoData.m_fTestRate = page2.m_fTestRate;
	TestInfoData.m_strRemark = page2.m_strRemark;
	TestInfoData.m_strTestMachine = page2.m_strTestMachine;
	TestInfoData.m_strTester = page2.m_strTester;
	TestInfoData.m_strTestDate = page2.m_strTestDate;
	TestInfoData.m_bCustomVol_Aging = page2.m_bCustomVol_Aging;
	TestInfoData.m_bEMC_Test = page2.m_bEMC_Test;
	TestInfoData.m_bHighLowVol_Aging = page2.m_bHighLowVol_Aging;
	TestInfoData.m_bHighTMP_Aging = page2.m_bHighTMP_Aging;
	TestInfoData.m_bNormalTMP_Aging = page2.m_bNormalTMP_Aging;
	TestInfoData.m_bStaVol_Aging = page2.m_bStaVol_Aging;
	TestInfoData.m_bSwitch_Aging = page2.m_bSwitch_Aging;

	TestInfoData.m_bPrintPageHeadLogo = page3.m_bPrintPageHeadLogo;
	TestInfoData.m_iPageHeadLogoPos = page3.m_iPageHeadLogoPos;
	TestInfoData.m_bPrintSubCap = page3.m_bPrintSubCap;
	TestInfoData.m_strPageHeadCap = page3.m_strPageHeadCap;
	TestInfoData.m_strPageHeadCapInfo = page3.m_strPageHeadCapInfo;
	TestInfoData.m_strPrintCap = page3.m_strPrintCap;
	TestInfoData.m_strPrintSubCap = page3.m_strPrintSubCap;
	TestInfoData.SaveTestInfoSection();
}



void CDlgBeforeChangeLamp::OnBnClickedRadioNum()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    GetDlgItem(IDC_COMBO_FILE_DATA_NUM)->EnableWindow(!m_iSaveType);
}


void CDlgBeforeChangeLamp::OnBnClickedRadioDay()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE); 
    GetDlgItem(IDC_COMBO_FILE_DATA_NUM)->EnableWindow(!m_iSaveType);
}


void CDlgBeforeChangeLamp::OnBnClickedRadioManuInput()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    GetDlgItem(IDC_EDIT_FILE_NAME)->EnableWindow(!m_iPrefixInputMode);
}


void CDlgBeforeChangeLamp::OnBnClickedRadioManuInput2()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    GetDlgItem(IDC_EDIT_FILE_NAME)->EnableWindow(!m_iPrefixInputMode);
}


