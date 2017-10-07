// DockPaneDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "EditLimitDlg.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"
#include "MainFrm.h"
#include "ExWYDll.h"
#include "BurnInSettingsDlg.h"
#include "RectificationTestDlg.h"
#include "AlarmSettingsDlg.h"
#include "InputPasswordDlg.h"
#include "math.h"
#include "DlgMyLastSet.h"
#include "DlgSaftSetup.h"

class CMainFrame;

extern CMyDockablePaneData g_myDockablePaneData;
// CEditLimitDlg 对话框

IMPLEMENT_DYNAMIC(CEditLimitDlg, CDialogEx)

CEditLimitDlg::CEditLimitDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEditLimitDlg::IDD, pParent)
	, m_bTestMyLast(FALSE)
	, m_bTestSaft(FALSE)
	, m_bTestAutoHand(FALSE)
{
    m_bAutoIntegral = FALSE;
    m_strCurrentFileName = "";
    m_fLimitFlux = 0.0f;
    m_fOffsetFlux = 0.0f;
    m_fLimitHW = 0.0f;
    m_fOffsetHW = 0.0f;
    m_fIntegralTime = 0.0f;
    m_fLimitLd = 0.0f;
    m_fOffsetLd = 0.0f;
    m_fLimitLp = 0.0f;
    m_fOffsetLp = 0.0f;
    m_fLimitPI = 0.0f;
    m_fOffsetPI = 0.0f;
    m_fLimitPur = 0.0f;
    m_fOffsetPur = 0.0f;
    m_fLimitPV = 0.0f;
    m_fOffsetPV = 0.0f;
    m_fLimitRa = 0.0f;
    m_fOffsetRa = 0.0f;
    m_fLimitTC = 0.0f;
    m_fOffsetTc = 0.0f;
    m_fLimitu = 0.0f;
    m_fOffsetu = 0.0f;
    m_fLimitv = 0.0f;
    m_fOffsetv = 0.0f;
    m_fLimitx = 0.0f;
    m_fOffsetx = 0.0f;
    m_fLimity = 0.0f;
    m_fOffsety = 0.0f;
    m_strDateTime = _T("");
    m_strLedModel = _T("");
    m_strPersonName = _T("");
    m_strRemarks = _T("");
    m_fLEDWarmUPTimemsec = 100.0f;
    m_fTestVoltage = 0.0f;
    m_fTestFrequency = 0.0f;
    m_fK1 = 0.0f;
    m_fK10 = 0.0f;
    m_fK2 = 0.0f;
    m_fK3 = 0.0f;
    m_fK4 = 0.0f;
    m_fK5 = 0.0f;
    m_fK6 = 0.0f;
    m_fK7 = 0.0f;
    m_fK8 = 0.0f;
    m_fK9 = 0.0f;
    m_fOffsetFlux_ = 0.0f;
    m_fOffsetHW_ = 0.0f;
    m_fOffsetLd_ = 0.0f;
    m_fOffsetLp_ = 0.0f;
    m_fOffsetPI_ = 0.0f;
    m_fOffsetPur_ = 0.0f;
    m_fOffsetPV_ = 0.0f;
    m_fOffsetRa_ = 0.0f;
    m_fOffsetTc_ = 0.0f;
    m_fOffsetu_ = 0.0f;
    m_fOffsetv_ = 0.0f;
    m_fOffsetx_ = 0.0f;
    m_fOffsety_ = 0.0f;
    m_iRangeCF = 0;
    m_iRangeI = 0;
    m_iRangeU = 0;
    m_fLimitLuminousPower = 0.0f;
    m_fOffsetLuminousPower = 0.0f;
    m_fOffsetLuminousPower_ = 0.0f;
    m_fBallHigh = 0.0f;


    for (int i = 0; i < DATA_CAHNNEL_NUM; i++)
    {
        m_fStdFlux[i] = 0;
        m_fTestFlux[i] = 0;
    }

    m_bCheckP = 0;
    m_bCheckPF = 0;
    m_bCheckFre = 0;
    m_fLimitP = 0.0f;
    m_fOffsetP = 0.0f;   
    m_fLimitPF = 0.0f;
    m_fOffsetPF = 0.0f;
    m_fLimitFre = 0.0f;
    m_fOffsetFre = 0.0f;
    m_fOffsetP_ = 0.0f;
    m_fOffsetPF_ = 0.0f;
    m_fOffsetFre_ = 0.0f;

    m_fLimitVal = 50.0f;
    m_fLimitVal_Offset1 = 5.0f;
    m_fLimitVal_Offset2 = 5.0f;
    m_iListSel = -1;
    m_iCurParaLimit = 0;
    m_bLowELorDisOnly = FALSE;
    m_bStatistic = FALSE;
    m_bLoadFile_WhenStart = FALSE;
}

CEditLimitDlg::~CEditLimitDlg()
{

}

void CEditLimitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_FLUX_, m_bCheckFlux);
	DDX_Check(pDX, IDC_CHECK_HW_, m_bCheckHW);
	DDX_Check(pDX, IDC_CHECK_LD_, m_bCheckLd);
	DDX_Check(pDX, IDC_CHECK_LP_, m_bCheckLp);
	DDX_Check(pDX, IDC_CHECK_PI_, m_bCheckPI);
	DDX_Check(pDX, IDC_CHECK_PV_, m_bCheckPV);

	DDX_Check(pDX, IDC_CHECK_P_, m_bCheckP);
	DDX_Check(pDX, IDC_CHECK_PF_, m_bCheckPF);
	DDX_Check(pDX, IDC_CHECK_FRE, m_bCheckFre);


	DDX_Check(pDX, IDC_CHECK_RA_, m_bCheckRa);
	DDX_Check(pDX, IDC_CHECK_TC_, m_bCheckTc);
	DDX_Check(pDX, IDC_CHECK_U_, m_bChecku);
	DDX_Check(pDX, IDC_CHECK_V_, m_bCheckv);
	DDX_Check(pDX, IDC_CHECK_X_, m_bCheckx);
	DDX_Check(pDX, IDC_CHECK_Y_, m_bChecky);
	DDX_Check(pDX, IDC_CHECK_PUR_, m_bCheckPur);
	DDX_Text(pDX, IDC_EDIT_FLUX, m_fLimitFlux);
	DDX_Text(pDX, IDC_EDIT_FLUX_, m_fOffsetFlux);
	DDX_Text(pDX, IDC_EDIT_HW, m_fLimitHW);
	DDX_Text(pDX, IDC_EDIT_HW_, m_fOffsetHW);
	DDX_Text(pDX, IDC_EDIT_INTEGRAL_TIME, m_fIntegralTime);
	DDV_MinMaxFloat(pDX, m_fIntegralTime, 0.1f, 60000.0f);
	DDX_Text(pDX, IDC_EDIT_LD, m_fLimitLd);
	DDX_Text(pDX, IDC_EDIT_LD_, m_fOffsetLd);
	DDX_Text(pDX, IDC_EDIT_LP, m_fLimitLp);
	DDX_Text(pDX, IDC_EDIT_LP_, m_fOffsetLp);
	DDX_Text(pDX, IDC_EDIT_PI, m_fLimitPI);
	DDX_Text(pDX, IDC_EDIT_PI_, m_fOffsetPI);
	DDX_Text(pDX, IDC_EDIT_PUR, m_fLimitPur);
	DDX_Text(pDX, IDC_EDIT_PUR_, m_fOffsetPur);
	DDX_Text(pDX, IDC_EDIT_PV, m_fLimitPV);
	DDX_Text(pDX, IDC_EDIT_PV_, m_fOffsetPV);

	DDX_Text(pDX, IDC_EDIT_P, m_fLimitP);
	DDX_Text(pDX, IDC_EDIT_P_, m_fOffsetP);
	DDX_Text(pDX, IDC_EDIT_PF, m_fLimitPF);
	DDX_Text(pDX, IDC_EDIT_PF_, m_fOffsetPF);
	DDX_Text(pDX, IDC_EDIT_FRE, m_fLimitFre);
	DDX_Text(pDX, IDC_EDIT_FRE_, m_fOffsetFre);

	DDX_Text(pDX, IDC_EDIT_RA, m_fLimitRa);
	DDX_Text(pDX, IDC_EDIT_RA_, m_fOffsetRa);
	DDX_Text(pDX, IDC_EDIT_TC, m_fLimitTC);
	DDX_Text(pDX, IDC_EDIT_TC_, m_fOffsetTc);
	DDX_Text(pDX, IDC_EDIT_U, m_fLimitu);
	DDX_Text(pDX, IDC_EDIT_U_, m_fOffsetu);
	DDX_Text(pDX, IDC_EDIT_V, m_fLimitv);
	DDX_Text(pDX, IDC_EDIT_V_, m_fOffsetv);
	DDX_Text(pDX, IDC_EDIT_X, m_fLimitx);
	DDX_Text(pDX, IDC_EDIT_X_, m_fOffsetx);
	DDX_Text(pDX, IDC_EDIT_Y, m_fLimity);
	DDX_Text(pDX, IDC_EDIT_Y_, m_fOffsety);
	DDX_Text(pDX, IDC_EDIT_DATE, m_strDateTime);
	DDX_Text(pDX, IDC_EDIT_LED_MODEL, m_strLedModel);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strPersonName);
	DDX_Text(pDX, IDC_EDIT_REMARKS, m_strRemarks);
	DDX_Text(pDX, IDC_EDIT_LED_WARMUP_TIME, m_fLEDWarmUPTimemsec);
	DDV_MinMaxFloat(pDX, m_fLEDWarmUPTimemsec, 0.1f, 60000.0f);
	DDX_Text(pDX, IDC_EDIT_TEST_VOLTAGE, m_fTestVoltage);
	DDV_MinMaxFloat(pDX, m_fTestVoltage, 1.0f, 230.0f);
	DDX_Text(pDX, IDC_EDIT_TEST_FREQUENCY, m_fTestFrequency);
	DDV_MinMaxFloat(pDX, m_fTestFrequency, 45.0f, 65.0f);
	DDX_Check(pDX, IDC_CHECK_CH1, m_bTestCh1);
	DDX_Check(pDX, IDC_CHECK_CH10, m_bTestCh10);
	DDX_Check(pDX, IDC_CHECK_CH2, m_bTestCh2);
	DDX_Check(pDX, IDC_CHECK_CH3, m_bTestCh3);
	DDX_Check(pDX, IDC_CHECK_CH4, m_bTestCh4);
	DDX_Check(pDX, IDC_CHECK_CH5, m_bTestCh5);
	DDX_Check(pDX, IDC_CHECK_CH6, m_bTestCh6);
	DDX_Check(pDX, IDC_CHECK_CH7, m_bTestCh7);
	DDX_Check(pDX, IDC_CHECK_CH8, m_bTestCh8);
	DDX_Check(pDX, IDC_CHECK_CH9, m_bTestCh9);
	DDX_Text(pDX, IDC_EDIT_FLUX_2, m_fOffsetFlux_);
	DDX_Text(pDX, IDC_EDIT_HW_2, m_fOffsetHW_);
	DDX_Text(pDX, IDC_EDIT_LD_2, m_fOffsetLd_);
	DDX_Text(pDX, IDC_EDIT_LP_2, m_fOffsetLp_);
	DDX_Text(pDX, IDC_EDIT_PI_2, m_fOffsetPI_);
	DDX_Text(pDX, IDC_EDIT_PUR_2, m_fOffsetPur_);
	DDX_Text(pDX, IDC_EDIT_PV_2, m_fOffsetPV_);

	DDX_Text(pDX, IDC_EDIT_P_2, m_fOffsetP_);
	DDX_Text(pDX, IDC_EDIT_PF_2, m_fOffsetPF_);
	DDX_Text(pDX, IDC_EDIT_FRE_2, m_fOffsetFre_);

	DDX_Text(pDX, IDC_EDIT_RA_2, m_fOffsetRa_);
	DDX_Text(pDX, IDC_EDIT_TC_2, m_fOffsetTc_);
	DDX_Text(pDX, IDC_EDIT_U_2, m_fOffsetu_);
	DDX_Text(pDX, IDC_EDIT_V_2, m_fOffsetv_);
	DDX_Text(pDX, IDC_EDIT_X_2, m_fOffsetx_);
	DDX_Text(pDX, IDC_EDIT_Y_2, m_fOffsety_);
	DDX_CBIndex(pDX, IDC_COMBO_CF, m_iRangeCF);
	DDX_CBIndex(pDX, IDC_COMBO_RANGE_I, m_iRangeI);
	DDX_CBIndex(pDX, IDC_COMBO_RANGE_U, m_iRangeU);
	DDX_Check(pDX, IDC_CHECK_LPOWER, m_bCheckLuminousPower);
	DDX_Text(pDX, IDC_EDIT_LPOWER, m_fLimitLuminousPower);
	DDX_Text(pDX, IDC_EDIT_LPOWER_, m_fOffsetLuminousPower);
	DDX_Text(pDX, IDC_EDIT_LPOWER_2, m_fOffsetLuminousPower_);
	DDX_Check(pDX, IDC_CHECK_CH11, m_bThunderChannel1);
	DDX_Check(pDX, IDC_CHECK_CH12, m_bThunderChannel2);
	DDX_Check(pDX, IDC_CHECK_CH13, m_bThunderChannel3);
	DDX_Check(pDX, IDC_CHECK_CH14, m_bThunderChannel4);
	DDX_Check(pDX, IDC_CHECK_CH15, m_bThunderChannel5);
	DDX_Check(pDX, IDC_CHECK_CH16, m_bThunderChannel6);
	DDX_Check(pDX, IDC_CHECK_CH17, m_bThunderChannel7);
	DDX_Check(pDX, IDC_CHECK_CH18, m_bThunderChannel8);
	DDX_Check(pDX, IDC_CHECK_CH19, m_bThunderChannel9);
	DDX_Check(pDX, IDC_CHECK_CH20, m_bThunderChannel10);
	DDX_Control(pDX, IDC_COMBO_RANGE_U, m_cRangeV);
	DDX_Control(pDX, IDC_COMBO_RANGE_I, m_cRangeI);

	DDX_Check(pDX, IDC_CHECK_DIRECTION_OPPOSITE, m_bTestDirectionOpposite);
	DDX_Check(pDX, IDC_CHECK_LIGHTNING, m_bTestLightning);
	DDX_Check(pDX, IDC_CHECK_VOLTAGE_UP_AND_DIPS, m_bTestVoltageUpAndDips);
	DDX_Check(pDX, IDC_CHECK_BURN_IN, m_bTestBurnIn);
	DDX_Text(pDX, IDC_EDIT_MIN_SECONDS, m_iTestMinSeconds);

	DDX_Check(pDX, IDC_CHECK_R9, m_bCheckR9);
	DDX_Text(pDX, IDC_EDIT_R9, m_fLimitR9);
	DDX_Text(pDX, IDC_EDIT_R9_, m_fOffsetR9);
	DDX_Text(pDX, IDC_EDIT_R9_2, m_fOffsetR9_);
	DDX_Control(pDX, IDC_LIST_LIMIT, m_cList);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_btAdd);
	DDX_Control(pDX, IDC_BUTTON_MOD, m_btMod);
	DDX_Control(pDX, IDC_BUTTON_DEL, m_btDel);
	DDX_Text(pDX, IDC_EDIT_LIMIT_V, m_fLimitVal);
	DDX_Text(pDX, IDC_EDIT_LIMIT_V_OFFSET1, m_fLimitVal_Offset1);
	DDX_Text(pDX, IDC_EDIT_LIMIT_V_OFFSET2, m_fLimitVal_Offset2);
	DDX_Check(pDX, IDC_CHECK_JUDGE, m_bCheckJudge);
	DDX_Control(pDX, IDC_COMBO_LIMITPARA_NAME, m_comboLimitParaName);
	DDX_Control(pDX, IDC_EDIT_LIMIT_V, m_cLimitVal);
	DDX_Control(pDX, IDC_EDIT_LIMIT_V_OFFSET1, m_cLimitVal_Offset1);
	DDX_Control(pDX, IDC_EDIT_LIMIT_V_OFFSET2, m_cLimitVal_Offset2);
	DDX_CBIndex(pDX, IDC_COMBO_LIMITPARA_NAME, m_iCurParaLimit);
	DDX_Text(pDX, IDC_EDIT_STA_POW, m_fStaPow);
	DDX_Text(pDX, IDC_EDIT_STA_FLUX, m_fStaFlux);
	DDX_Text(pDX, IDC_EDIT_STA_TC, m_fStaTc);
	DDX_Text(pDX, IDC_EDIT_STA_VOL, m_fStaVol);
	DDX_Text(pDX, IDC_EDIT_LED_UNON_POW, m_fLEDUnOnPow);
	DDX_Text(pDX, IDC_EDIT_LED_UNON_FLUX, m_fLEDUnOnFlux);
	DDX_Check(pDX, IDC_CHECK_MY_LAST, m_bTestMyLast);
	DDX_Check(pDX, IDC_CHECK_SAFT, m_bTestSaft);
	DDX_Check(pDX, IDC_CHECK_AUTO_LAMP, m_bTestAutoHand);
}


BEGIN_MESSAGE_MAP(CEditLimitDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CEditLimitDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CEditLimitDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_AS, &CEditLimitDlg::OnBnClickedButtonSaveAs)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &CEditLimitDlg::OnBnClickedButtonQuit)
	ON_BN_CLICKED(IDC_CHECK_FLUX_, &CEditLimitDlg::OnBnClickedCheckFlux)
	ON_BN_CLICKED(IDC_CHECK_TC_, &CEditLimitDlg::OnBnClickedCheckTc)
	ON_BN_CLICKED(IDC_CHECK_X_, &CEditLimitDlg::OnBnClickedCheckX)
	ON_BN_CLICKED(IDC_CHECK_Y_, &CEditLimitDlg::OnBnClickedCheckY)
	ON_BN_CLICKED(IDC_CHECK_U_, &CEditLimitDlg::OnBnClickedCheckU)
	ON_BN_CLICKED(IDC_CHECK_V_, &CEditLimitDlg::OnBnClickedCheckV)
	ON_BN_CLICKED(IDC_CHECK_LD_, &CEditLimitDlg::OnBnClickedCheckLd)
	ON_BN_CLICKED(IDC_CHECK_LP_, &CEditLimitDlg::OnBnClickedCheckLp)
	ON_BN_CLICKED(IDC_CHECK_PUR_, &CEditLimitDlg::OnBnClickedCheckPur)
	ON_BN_CLICKED(IDC_CHECK_HW_, &CEditLimitDlg::OnBnClickedCheckHw)
	ON_BN_CLICKED(IDC_CHECK_PV_, &CEditLimitDlg::OnBnClickedCheckPv)
	ON_BN_CLICKED(IDC_CHECK_NV_, &CEditLimitDlg::OnBnClickedCheckNv)
	ON_BN_CLICKED(IDC_CHECK_PI_, &CEditLimitDlg::OnBnClickedCheckPi)
	ON_BN_CLICKED(IDC_CHECK_NI_, &CEditLimitDlg::OnBnClickedCheckNi)
	ON_BN_CLICKED(IDC_CHECK_RA_, &CEditLimitDlg::OnBnClickedCheckRa)
	ON_BN_CLICKED(IDC_CHECK_TEST_REVERSE, &CEditLimitDlg::OnBnClickedCheckTestReverse)
	ON_BN_CLICKED(IDC_BUTTON_AUTO_INTEGRAL, &CEditLimitDlg::OnBnClickedButtonAutoIntegral)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_LIGHTNING, &CEditLimitDlg::OnBnClickedButtonLightning)
	ON_BN_CLICKED(IDC_BUTTON_UPANDDIPS, &CEditLimitDlg::OnBnClickedButtonUpanddips)
	ON_BN_CLICKED(IDC_BUTTON_BURN_IN, &CEditLimitDlg::OnBnClickedButtonBurnIn)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CEditLimitDlg::OnBnClickedButtonTest)
	ON_BN_CLICKED(IDC_CHECK_LPOWER, &CEditLimitDlg::OnBnClickedCheckLpower)
	ON_BN_CLICKED(IDC_BUTTON_ALARM, &CEditLimitDlg::OnBnClickedButtonAlarm)
    ON_CBN_SELCHANGE(IDC_COMBO_CF, &CEditLimitDlg::OnCbnSelchangeComboCf)
    ON_BN_CLICKED(IDC_CHECK_PF_, &CEditLimitDlg::OnBnClickedCheckPf)
    ON_BN_CLICKED(IDC_CHECK_P_, &CEditLimitDlg::OnBnClickedCheckP)
    ON_BN_CLICKED(IDC_CHECK_FRE, &CEditLimitDlg::OnBnClickedCheckFre)
    ON_BN_CLICKED(IDC_CHECK_JUDGE, &CEditLimitDlg::OnBnClickedCheckJudge)
    ON_BN_CLICKED(IDC_BUTTON_ADD, &CEditLimitDlg::OnBnClickedButtonAdd)
    ON_BN_CLICKED(IDC_BUTTON_MOD, &CEditLimitDlg::OnBnClickedButtonMod)
    ON_BN_CLICKED(IDC_BUTTON_DEL, &CEditLimitDlg::OnBnClickedButtonDel)
    ON_NOTIFY(NM_CLICK, IDC_LIST_LIMIT, &CEditLimitDlg::OnNMClickListLimit)
    ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MY, &CEditLimitDlg::OnBnClickedButtonMy)
	ON_BN_CLICKED(IDC_BUTTON5, &CEditLimitDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_SDCM, &CEditLimitDlg::OnBnClickedButtonSdcm)
END_MESSAGE_MAP()


// CEditLimitDlg 消息处理程序

void CEditLimitDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	return;

	CDialogEx::OnOK();
}


void CEditLimitDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	if (m_bAutoIntegral)
	{
		AfxMessageBox("自动积分进行中，请等待积分结束后再退出！");
		return;
	}

	CDialogEx::OnCancel();
}


void CEditLimitDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	if (FALSE == UpdateData(TRUE))
	{
		return;
	}
	//文件名去除特殊字符
	m_strLedModel.Replace("\\","");
	m_strLedModel.Replace("/","");
	m_strLedModel.Replace(":","");
	m_strLedModel.Replace("*","");
	m_strLedModel.Replace("?","");
	m_strLedModel.Replace("<","");
	m_strLedModel.Replace(">","");
	m_strLedModel.Replace("|","");

    if (!m_bStatistic)
    {
	    if (!IsInputModelAndBulbHigh())
	    {
		    return;
	    }
        CString strTemp;
        strTemp.Format("请确认灯型号是否为%s！\n请确认是否修改原有设置并保存到%s文件中！", 
            m_strLedModel, g_strTestSettingFileName);
        if (IDCANCEL == MessageBox(strTemp, "Warning", MB_OKCANCEL))
        {
            return;
        }
    }
	GetData(m_LimitData);



	CDialogEx::OnOK();
}

BOOL CEditLimitDlg::GetData(CTestSettingsData & data)
{
    CString strTemp;
    GetDlgItemText(IDC_EDIT_BALL_HIGH, strTemp);
    m_fBallHigh = (float)atof(strTemp);

	data.m_AlarmSettingsData = m_AlarmSettingsData;
	data.m_iEMC5ASelectIndex = m_iEMC5ASelectIndex;
	data.m_iEMC11KSelectIndex = m_iEMC11KSelectIndex;
	
	data.m_iBurnInONSeconds = m_iBurnInONSeconds;
	data.m_iBurnInOFFSeconds = m_iBurnInOFFSeconds;

	data.m_fIntegralTimems = m_fIntegralTime;
	data.m_fTestFrquencyHz = m_fTestFrequency;
	data.m_fTestVoltageV = m_fTestVoltage;
	data.m_fWarmUpTimems = m_fLEDWarmUPTimemsec;
	data.m_iRangeCF = m_iRangeCF;
	data.m_iRangeI = m_iRangeI;
	data.m_iRangeU = m_iRangeU;

	data.m_fLimitFlux = m_fLimitFlux;
	data.m_fLimitHW = m_fLimitHW;
	data.m_fLimitLd = m_fLimitLd;
	data.m_fLimitLp = m_fLimitLp;
	data.m_fLimitPositiveCurrent = m_fLimitPI;
	data.m_fLimitPositiveVoltage = m_fLimitPV;
	data.m_fLimitPur = m_fLimitPur;
	data.m_fLimitRa = m_fLimitRa;
	data.m_fLimitTc = m_fLimitTC;
	data.m_fLimitU = m_fLimitu;
	data.m_fLimitV = m_fLimitv;
	data.m_fLimitX = m_fLimitx;
	data.m_fLimitY = m_fLimity;
	data.m_fLimitLuminousPower = m_fLimitLuminousPower;

   
    data.m_fLimitPow = m_fLimitP;
    data.m_fOffsetPow = m_fOffsetP;
    data.m_fOffsetPow_ = m_fOffsetP_;

    data.m_fLimitPowFactor = m_fLimitPF;
    data.m_fOffsetPowFactor = m_fOffsetPF;
    data.m_fOffsetPowFactor_ = m_fOffsetPF_;

    data.m_fLimitFre = m_fLimitFre;
    data.m_fOffsetFre = m_fOffsetFre;
    data.m_fOffsetFre_ = m_fOffsetFre_;

	data.m_fOffsetFlux = m_fOffsetFlux;
	data.m_fOffsetHW = m_fOffsetHW;
	data.m_fOffsetLd = m_fOffsetLd;
	data.m_fOffsetLp = m_fOffsetLp;
	data.m_fOffsetPositiveVoltage = m_fOffsetPV;
	data.m_fOffsetPositveCurrent = m_fOffsetPI;
	data.m_fOffsetPur = m_fOffsetPur;
	data.m_fOffsetRa = m_fOffsetRa;
	data.m_fOffsetTc = m_fOffsetTc;
	data.m_fOffsetU = m_fOffsetu;
	data.m_fOffsetV = m_fOffsetv;
	data.m_fOffsetX = m_fOffsetx;
	data.m_fOffsetY = m_fOffsety;
	data.m_fOffsetLuminousPower = m_fOffsetLuminousPower;

	data.m_fOffsetFlux_ = m_fOffsetFlux_;
	data.m_fOffsetHW_ = m_fOffsetHW_;
	data.m_fOffsetLd_ = m_fOffsetLd_;
	data.m_fOffsetLp_ = m_fOffsetLp_;
	data.m_fOffsetPositiveVoltage_ = m_fOffsetPV_;
	data.m_fOffsetPositveCurrent_ = m_fOffsetPI_;
	data.m_fOffsetPur_ = m_fOffsetPur_;
	data.m_fOffsetRa_ = m_fOffsetRa_;
	data.m_fOffsetTc_ = m_fOffsetTc_;
	data.m_fOffsetU_ = m_fOffsetu_;
	data.m_fOffsetV_ = m_fOffsetv_;
	data.m_fOffsetX_ = m_fOffsetx_;
	data.m_fOffsetY_ = m_fOffsety_;
	data.m_fOffsetLuminousPower_ = m_fOffsetLuminousPower_;

	data.m_fBallHigh = m_fBallHigh;
	data.m_strDateTime = m_strDateTime;
	data.m_strLedModel = m_strLedModel;
	data.m_strPersonName = m_strPersonName;
	data.m_strRemarks = m_strRemarks;

	data.m_pfLuminosityK[0] = m_fK1;
	data.m_pfLuminosityK[1] = m_fK2;
	data.m_pfLuminosityK[2] = m_fK3;
	data.m_pfLuminosityK[3] = m_fK4;
	data.m_pfLuminosityK[4] = m_fK5;
	data.m_pfLuminosityK[5] = m_fK6;
	data.m_pfLuminosityK[6] = m_fK7;
	data.m_pfLuminosityK[7] = m_fK8;
	data.m_pfLuminosityK[8] = m_fK9;
	data.m_pfLuminosityK[9] = m_fK10;

	data.m_pbTestChannel[0] = m_bTestCh1;
	data.m_pbTestChannel[1] = m_bTestCh2;
	data.m_pbTestChannel[2] = m_bTestCh3;
	data.m_pbTestChannel[3] = m_bTestCh4;
	data.m_pbTestChannel[4] = m_bTestCh5;
	data.m_pbTestChannel[5] = m_bTestCh6;
	data.m_pbTestChannel[6] = m_bTestCh7;
	data.m_pbTestChannel[7] = m_bTestCh8;
	data.m_pbTestChannel[8] = m_bTestCh9;
	data.m_pbTestChannel[9] = m_bTestCh10;

	data.m_pbThunderChannel[0] = m_bThunderChannel1;
	data.m_pbThunderChannel[1] = m_bThunderChannel2;
	data.m_pbThunderChannel[2] = m_bThunderChannel3;
	data.m_pbThunderChannel[3] = m_bThunderChannel4;
	data.m_pbThunderChannel[4] = m_bThunderChannel5;
	data.m_pbThunderChannel[5] = m_bThunderChannel6;
	data.m_pbThunderChannel[6] = m_bThunderChannel7;
	data.m_pbThunderChannel[7] = m_bThunderChannel8;
	data.m_pbThunderChannel[8] = m_bThunderChannel9;
	data.m_pbThunderChannel[9] = m_bThunderChannel10;

    data.m_fOffsetR9 = m_fOffsetR9;
    data.m_fOffsetR9_ = m_fOffsetR9_;
    data.m_fLimitR9 = m_fLimitR9;

	for (int i = 0; i < DATA_CAHNNEL_NUM; i++)
	{
		data.m_pfStandardFlux[i] = m_fStdFlux[i];
		data.m_pfTestFlux[i] = m_fTestFlux[i];
		data.m_pfTestFlux2[i] = m_pfTestFlux2[i];
	}

	UINT32 ui32Flag = 0;
	if (m_bCheckFlux)
	{
		ui32Flag |= CTestSettingsData::CHECK_FLUX;
	}
	if (m_bCheckHW)
	{
		ui32Flag |= CTestSettingsData::CHECK_HW;
	}
	if (m_bCheckLd)
	{
		ui32Flag |= CTestSettingsData::CHECK_LD;
	}
	if (m_bCheckLp)
	{
		ui32Flag |= CTestSettingsData::CHECK_LP;
	}
	if (m_bCheckPI)
	{
		ui32Flag |= CTestSettingsData::CHECK_POSITIVECURRENT;
	}
	if (m_bCheckPV)
	{
		ui32Flag |= CTestSettingsData::CHECK_POSITIVEVOLTAGE;
	}
	if (m_bCheckPur)
	{
		ui32Flag |= CTestSettingsData::CHECK_POSITIVEVOLTAGE;
	}
	if (m_bCheckRa)
	{
		ui32Flag |= CTestSettingsData::CHECK_RA;
	}
	if (m_bCheckTc)
	{
		ui32Flag |= CTestSettingsData::CHECK_TC;
	}
	if (m_bChecku)
	{
		ui32Flag |= CTestSettingsData::CHECK_U;
	}
	if (m_bCheckv)
	{
		ui32Flag |= CTestSettingsData::CHECK_V;
	}
	if (m_bCheckx)
	{
		ui32Flag |= CTestSettingsData::CHECK_X;
	}
	if (m_bChecky)
	{
		ui32Flag |= CTestSettingsData::CHECK_Y;
	}
	if (m_bCheckPur)
	{
		ui32Flag |= CTestSettingsData::CHECK_PUR;
	}
	if (m_bCheckLuminousPower)
	{
		ui32Flag |= CTestSettingsData::CHECK_LUMINOUS_POWER;
	}
    if (m_bCheckP)
    {
        ui32Flag |= CTestSettingsData::CHECK_P;
    }
    if (m_bCheckPF)
    {
        ui32Flag |= CTestSettingsData::CHECK_PF;
    }
    if (m_bCheckFre)
    {
        ui32Flag |= CTestSettingsData::CHECK_FRE;
    }
    if (m_bCheckR9)
    {
        ui32Flag |= CTestSettingsData::CHECK_R9;
    }
	m_LimitData.m_ui32Flag = ui32Flag;

    data.m_bTestLightning	= m_bTestLightning;
    data.m_bTestVoltageUpAndDips = m_bTestVoltageUpAndDips;
    data.m_bTestBurnIn		= m_bTestBurnIn;
    data.m_iTestMinSeconds	= m_iTestMinSeconds;
    data.m_bTestDirectionOpposite = m_bTestDirectionOpposite;

	data.m_bTestSaft	= m_bTestSaft;
	data.m_bTestMyLast	= m_bTestMyLast;
	data.m_bTestAutoHand= m_bTestAutoHand;

    m_LimitData = m_LimitData.LimitEqual(m_LimitDataTemp);    

    data.m_fStaPow = m_fStaPow;
    data.m_fStaFlux = m_fStaFlux;
    data.m_fStaTc = m_fStaTc;
    data.m_fStaVol = m_fStaVol;
    data.m_fLEDUnOnFlux = m_fLEDUnOnFlux;
    data.m_fLEDUnOnPow = m_fLEDUnOnPow;
	g_fUnOnPowLimit = m_fLEDUnOnPow;

	return TRUE;
}

BOOL CEditLimitDlg::SetData(CTestSettingsData & data)
{
	m_AlarmSettingsData		= data.m_AlarmSettingsData;
	m_iEMC5ASelectIndex		= data.m_iEMC5ASelectIndex;
	m_iEMC11KSelectIndex	= data.m_iEMC11KSelectIndex;
	
	m_iBurnInONSeconds		= data.m_iBurnInONSeconds;
	m_iBurnInOFFSeconds		= data.m_iBurnInOFFSeconds;

	m_fIntegralTime			= data.m_fIntegralTimems;
	m_fTestFrequency		= data.m_fTestFrquencyHz;
	m_fTestVoltage			= data.m_fTestVoltageV;
	m_fLEDWarmUPTimemsec	= data.m_fWarmUpTimems;
	m_iRangeCF				= data.m_iRangeCF;
	m_iRangeI				= data.m_iRangeI;
	m_iRangeU				= data.m_iRangeU;

	m_fLimitFlux = data.m_fLimitFlux;
	m_fLimitHW = data.m_fLimitHW;
	m_fLimitLd = data.m_fLimitLd;
	m_fLimitLp = data.m_fLimitLp;
	m_fLimitPI = data.m_fLimitPositiveCurrent;
	m_fLimitPV = data.m_fLimitPositiveVoltage;
	m_fLimitPur = data.m_fLimitPur;
	m_fLimitRa = data.m_fLimitRa;
	m_fLimitTC = data.m_fLimitTc;
	m_fLimitu = data.m_fLimitU;
	m_fLimitv = data.m_fLimitV;
	m_fLimitx = data.m_fLimitX;
	m_fLimity = data.m_fLimitY;
	m_fLimitLuminousPower = data.m_fLimitLuminousPower;

    m_fLimitP = data.m_fLimitPow;
    m_fOffsetP = data.m_fOffsetPow;
    m_fOffsetP_ = data.m_fOffsetPow_;

    m_fLimitPF = data.m_fLimitPowFactor;
    m_fOffsetPF = data.m_fOffsetPowFactor;
    m_fOffsetPF_ = data.m_fOffsetPowFactor_;

    m_fLimitFre = data.m_fLimitFre;
    m_fOffsetFre = data.m_fOffsetFre;
    m_fOffsetFre_ = data.m_fOffsetFre_;


	m_fOffsetFlux = data.m_fOffsetFlux;
	m_fOffsetHW = data.m_fOffsetHW;
	m_fOffsetLd = data.m_fOffsetLd;
	m_fOffsetLp = data.m_fOffsetLp;
	m_fOffsetPV = data.m_fOffsetPositiveVoltage;
	m_fOffsetPI = data.m_fOffsetPositveCurrent;
	m_fOffsetPur = data.m_fOffsetPur;
	m_fOffsetRa = data.m_fOffsetRa;
	m_fOffsetTc = data.m_fOffsetTc;
	m_fOffsetu = data.m_fOffsetU;
	m_fOffsetv = data.m_fOffsetV;
	m_fOffsetx = data.m_fOffsetX;
	m_fOffsety = data.m_fOffsetY;
	m_fOffsetLuminousPower = data.m_fOffsetLuminousPower;

	m_fOffsetFlux_ = data.m_fOffsetFlux_;
	m_fOffsetHW_ = data.m_fOffsetHW_;
	m_fOffsetLd_ = data.m_fOffsetLd_;
	m_fOffsetLp_ = data.m_fOffsetLp_;
	m_fOffsetPV_ = data.m_fOffsetPositiveVoltage_;
	m_fOffsetPI_ = data.m_fOffsetPositveCurrent_;
	m_fOffsetPur_ = data.m_fOffsetPur_;
	m_fOffsetRa_ = data.m_fOffsetRa_;
	m_fOffsetTc_ = data.m_fOffsetTc_;
	m_fOffsetu_ = data.m_fOffsetU_;
	m_fOffsetv_ = data.m_fOffsetV_;
	m_fOffsetx_ = data.m_fOffsetX_;
	m_fOffsety_ = data.m_fOffsetY_;
	m_fOffsetLuminousPower_ = data.m_fOffsetLuminousPower_;

	m_fBallHigh		= data.m_fBallHigh;
	m_strDateTime	= data.m_strDateTime;
	m_strLedModel	= data.m_strLedModel;
	m_strPersonName = data.m_strPersonName;
	m_strRemarks	= data.m_strRemarks;
	
	m_fK1 = data.m_pfLuminosityK[0];
	m_fK2 = data.m_pfLuminosityK[1];
	m_fK3 = data.m_pfLuminosityK[2];
	m_fK4 = data.m_pfLuminosityK[3];
	m_fK5 = data.m_pfLuminosityK[4];
	m_fK6 = data.m_pfLuminosityK[5];
	m_fK7 = data.m_pfLuminosityK[6];
	m_fK8 = data.m_pfLuminosityK[7];
	m_fK9 = data.m_pfLuminosityK[8];
	m_fK10 = data.m_pfLuminosityK[9];

	m_bTestCh1 = data.m_pbTestChannel[0];
	m_bTestCh2 = data.m_pbTestChannel[1];
	m_bTestCh3 = data.m_pbTestChannel[2];
	m_bTestCh4 = data.m_pbTestChannel[3];
	m_bTestCh5 = data.m_pbTestChannel[4];
	m_bTestCh6 = data.m_pbTestChannel[5];
	m_bTestCh7 = data.m_pbTestChannel[6];
	m_bTestCh8 = data.m_pbTestChannel[7];
	m_bTestCh9 = data.m_pbTestChannel[8];
	m_bTestCh10 = data.m_pbTestChannel[9];

	m_bThunderChannel1 = data.m_pbThunderChannel[0];
	m_bThunderChannel2 = data.m_pbThunderChannel[1];
	m_bThunderChannel3 = data.m_pbThunderChannel[2];
	m_bThunderChannel4 = data.m_pbThunderChannel[3];
	m_bThunderChannel5 = data.m_pbThunderChannel[4];
	m_bThunderChannel6 = data.m_pbThunderChannel[5];
	m_bThunderChannel7 = data.m_pbThunderChannel[6];
	m_bThunderChannel8 = data.m_pbThunderChannel[7];
	m_bThunderChannel9 = data.m_pbThunderChannel[8];
	m_bThunderChannel10 = data.m_pbThunderChannel[9];

    m_fOffsetR9		= data.m_fOffsetR9;
    m_fOffsetR9_	= data.m_fOffsetR9_;
    m_fLimitR9		= data.m_fLimitR9;
	
	for (int i = 0; i < DATA_CAHNNEL_NUM; i++)
	{
		m_fStdFlux[i] = data.m_pfStandardFlux[i];
		m_fTestFlux[i] = data.m_pfTestFlux[i];
		m_pfTestFlux2[i] = data.m_pfTestFlux2[i];
	}
	
	UINT32 ui32Flag = data.m_ui32Flag;
	m_bCheckFlux = (ui32Flag & CTestSettingsData::CHECK_FLUX) != 0 ? 1 : 0;
	m_bCheckHW = (ui32Flag & CTestSettingsData::CHECK_HW) != 0 ? 1 : 0;
	m_bCheckLd = (ui32Flag & CTestSettingsData::CHECK_LD) != 0 ? 1 : 0;
	m_bCheckLp = (ui32Flag & CTestSettingsData::CHECK_LP) != 0 ? 1 : 0;
	m_bCheckPI = (ui32Flag & CTestSettingsData::CHECK_POSITIVECURRENT) != 0 ? 1 : 0;
	m_bCheckPV = (ui32Flag & CTestSettingsData::CHECK_POSITIVEVOLTAGE) != 0 ? 1 : 0;
	m_bCheckPur = (ui32Flag & CTestSettingsData::CHECK_PUR) != 0 ? 1 : 0;
	m_bCheckRa = (ui32Flag & CTestSettingsData::CHECK_RA) != 0 ? 1 : 0;
	m_bCheckTc = (ui32Flag & CTestSettingsData::CHECK_TC) != 0 ? 1 : 0;
	m_bChecku = (ui32Flag & CTestSettingsData::CHECK_U) != 0 ? 1 : 0;
	m_bCheckv = (ui32Flag & CTestSettingsData::CHECK_V) != 0 ? 1 : 0;
	m_bCheckx = (ui32Flag & CTestSettingsData::CHECK_X) != 0 ? 1 : 0;
	m_bChecky = (ui32Flag & CTestSettingsData::CHECK_Y) != 0 ? 1 : 0;
	m_bCheckLuminousPower = (ui32Flag & CTestSettingsData::CHECK_LUMINOUS_POWER) != 0 ? 1 : 0;
    m_bCheckP = (ui32Flag & CTestSettingsData::CHECK_P) != 0 ? 1 : 0;  
    m_bCheckPF = (ui32Flag & CTestSettingsData::CHECK_PF) != 0 ? 1 : 0;  
    m_bCheckFre = (ui32Flag & CTestSettingsData::CHECK_FRE) != 0 ? 1 : 0;  
    m_bCheckR9 = (ui32Flag & CTestSettingsData::CHECK_R9) != 0 ? 1 : 0;  


    m_bTestLightning		= data.m_bTestLightning;
    m_bTestVoltageUpAndDips = data.m_bTestVoltageUpAndDips;
    m_bTestBurnIn			= data.m_bTestBurnIn;
    m_iTestMinSeconds		= data.m_iTestMinSeconds;
    m_bTestDirectionOpposite= data.m_bTestDirectionOpposite;

	m_bTestMyLast			= data.m_bTestMyLast;
	m_bTestSaft				= data.m_bTestSaft;
	m_bTestAutoHand			= data.m_bTestAutoHand;

    m_LimitDataTemp			= m_LimitDataTemp.LimitEqual(m_LimitData); 
    CString strTemp;
    strTemp.Format("%g", m_fBallHigh);
    SetDlgItemText(IDC_EDIT_BALL_HIGH, strTemp);

    m_fStaPow		= data.m_fStaPow;
    m_fStaFlux		= data.m_fStaFlux;
    m_fStaTc		= data.m_fStaTc;
    m_fStaVol		= data.m_fStaVol;
    m_fLEDUnOnFlux	= data.m_fLEDUnOnFlux;
    m_fLEDUnOnPow	= data.m_fLEDUnOnPow;

	if(!g_pDoc->m_CommSettingsData.m_bHaveEMS61000_5A)
	{
		m_bTestLightning = FALSE;
	}
	if(!g_pDoc->m_CommSettingsData.m_bHaveEMS61000_11K)
	{
		m_bTestVoltageUpAndDips = FALSE;
	}
	UpdateData(FALSE);

	return TRUE;
}

BOOL CEditLimitDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

    m_bLowELorDisOnly = (LOW_EXECUTION_LEVEL == g_iExecutionLevel || TRUE == g_bDisplayLimitOnly);
    if (!m_bStatistic)
    {
        CTestSettingsData Temp;
        if(Temp.Load(g_strTestSettingFileName))
        {
            SetWindowText("参数设置 - " + g_strTestSettingFileName);
        }
    }
    else
    {
        if (LOW_EXECUTION_LEVEL != g_iExecutionLevel)
        {
            SetDlgItemText(IDC_BUTTON_SAVE, "确定");
            SetDlgItemText(IDC_BUTTON_QUIT, "取消");
        }
    }
    if (g_bUnOnPopedom)
    {
        CEdit *pEdit;
        pEdit = (CEdit*)GetDlgItem(IDC_EDIT_LED_UNON_POW);
        pEdit->SetReadOnly(FALSE);
        pEdit = (CEdit*)GetDlgItem(IDC_EDIT_LED_UNON_FLUX);
        pEdit->SetReadOnly(FALSE);
    }
	SetData(m_LimitData);

	if(!g_pDoc->m_CommSettingsData.m_bHaveEMS61000_5A)
	{
		m_bTestLightning = FALSE;
	}
	if(!g_pDoc->m_CommSettingsData.m_bHaveEMS61000_11K)
	{
		m_bTestVoltageUpAndDips = FALSE;
	}
	UpdateData(FALSE);
	
	GetDlgItem(IDC_CHECK_BURN_IN)->EnableWindow(!m_bLowELorDisOnly);
	GetDlgItem(IDC_BUTTON_BURN_IN)->EnableWindow(!m_bLowELorDisOnly);
	GetDlgItem(IDC_BUTTON_LIGHTNING)->EnableWindow(g_pDoc->m_CommSettingsData.m_bHaveEMS61000_5A);
	GetDlgItem(IDC_BUTTON_UPANDDIPS)->EnableWindow(g_pDoc->m_CommSettingsData.m_bHaveEMS61000_11K);
	GetDlgItem(IDC_CHECK_LIGHTNING)->EnableWindow(g_pDoc->m_CommSettingsData.m_bHaveEMS61000_5A);
	GetDlgItem(IDC_CHECK_VOLTAGE_UP_AND_DIPS)->EnableWindow(g_pDoc->m_CommSettingsData.m_bHaveEMS61000_11K);
	
	GetDlgItem(IDC_CHECK_AUTO_LAMP)->EnableWindow(!m_bLowELorDisOnly);
	GetDlgItem(IDC_CHECK_MY_LAST)->EnableWindow(!m_bLowELorDisOnly);
	GetDlgItem(IDC_BUTTON_MY)->EnableWindow(!m_bLowELorDisOnly);
	GetDlgItem(IDC_CHECK_SAFT)->EnableWindow(!m_bLowELorDisOnly);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(!m_bLowELorDisOnly);

	GetDlgItem(IDC_BUTTON_TEST)->EnableWindow(!m_bLowELorDisOnly);
	GetDlgItem(IDC_BUTTON_ALARM)->EnableWindow(!m_bLowELorDisOnly);

	GetDlgItem(IDC_CHECK_MY_LAST)->ShowWindow(g_pDoc->m_CommSettingsData.m_bHaveMyLast);
	GetDlgItem(IDC_BUTTON_MY)->ShowWindow(g_pDoc->m_CommSettingsData.m_bHaveMyLast);
	GetDlgItem(IDC_CHECK_SAFT)->ShowWindow(g_pDoc->m_CommSettingsData.m_bHaveSaft_NYY || g_pDoc->m_CommSettingsData.m_bHaveSaft_JYDZ || g_pDoc->m_CommSettingsData.m_bHaveSaft_XLDL);
	GetDlgItem(IDC_BUTTON5)->ShowWindow(g_pDoc->m_CommSettingsData.m_bHaveSaft_NYY || g_pDoc->m_CommSettingsData.m_bHaveSaft_JYDZ || g_pDoc->m_CommSettingsData.m_bHaveSaft_XLDL);

	SetEnable();

	g_PowerMeterComm.Initialize(g_pDoc->m_CommSettingsData.m_strCOMPF2010A ,
								g_pDoc->m_CommSettingsData.m_iPFType, 
								m_iRangeCF);
    CString strTemp;
    m_cRangeI.ResetContent();
    m_cRangeV.ResetContent();
    for (int i = 0; i < g_PowerMeterComm.GetVolRangeNum(); i ++)
    {
        strTemp.Format("%g", g_PowerMeterComm.GetVolRange(i));
        m_cRangeV.AddString(strTemp);
    }

    for (int i = 0; i < g_PowerMeterComm.GetCurRangeNum(); i ++)
    {
        strTemp.Format("%g", g_PowerMeterComm.GetCurRange(i));
        m_cRangeI.AddString(strTemp);
    }
    Enable_bDisor_LowExecu();
    UpdateData(FALSE);
	for (int i = 0; i < DATA_CAHNNEL_NUM; i ++)
	{
		if (i >= g_iColomnNum)
		{
			GetDlgItem(IDC_CHECK_CH11 + i)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECK_CH1 + i)->ShowWindow(SW_HIDE);
		}
	}

    for (int i = 0; i < PARA_NUM - 1; i ++)
    {
        m_comboLimitParaName.AddString(g_strListParaName[i]);
    }
    m_cLimitVal.EnableWindow(m_bCheckJudge);
    m_cLimitVal_Offset1.EnableWindow(m_bCheckJudge);
    m_cLimitVal_Offset2.EnableWindow(m_bCheckJudge);

    m_cList.ModifyStyle(0,LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS|LVS_NOSORTHEADER);
    m_bLowELorDisOnly?
        m_cList.SetExtendedStyle(m_cList.GetExtendedStyle()  | 
        LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES| LVS_EX_HEADERDRAGDROP)
        :
        m_cList.SetExtendedStyle(m_cList.GetExtendedStyle()  | 
        LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES| LVS_EX_HEADERDRAGDROP|LVS_EX_CHECKBOXES);
   
    m_cList.SetBkColor(RGB(232, 255, 255));
    m_cList.SetTextColor(RGB(128, 0, 64));
    m_cList.SetTextBkColor(RGB(232, 255, 255));

    m_LimitDataTemp.Relist(m_cList, !m_bLowELorDisOnly);
    m_cList.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
    m_cList.EnsureVisible(0, FALSE);
    m_iListSel = 0;    
    SetTimer(1, 100, NULL);

    m_bLowELorDisOnly
        ?m_btDel.EnableWindow(FALSE):m_btDel.EnableWindow(m_LimitDataTemp.m_Limit.GetSize());
    m_bLowELorDisOnly
        ?m_btMod.EnableWindow(FALSE):m_btMod.EnableWindow(m_LimitDataTemp.m_Limit.GetSize());
    if (m_bLoadFile_WhenStart)
    {
        SetTimer(2, 100, NULL);
    }
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CEditLimitDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE,"dat", "Limit1", 6UL, "Limit File(*.dat)|*.dat|", this);
	dlg.m_ofn.lpstrInitialDir = g_strLimitDataPath;
	if (IDOK == dlg.DoModal())
	{
		g_strTestSettingFileName = dlg.GetPathName();
		if (m_LimitData.Load(g_strTestSettingFileName))
		{
            g_strTestSettingFileName = dlg.GetPathName();
			SetWindowText("参数设置 - " + g_strTestSettingFileName);
			SetData(m_LimitData);
			UpdateData(FALSE);
			SetEnable();

			CString strTemp;
            strTemp.Format("请确认标尺高度是否为%.1f！\n请确认测试电压是否为%gV！", 
                m_LimitData.m_fBallHigh, m_LimitData.m_fTestVoltageV);
			AfxMessageBox(strTemp);

            m_LimitDataTemp.Relist(m_cList, !m_bLowELorDisOnly);

            m_bLowELorDisOnly
                ?m_btDel.EnableWindow(FALSE):m_btDel.EnableWindow(m_LimitDataTemp.m_Limit.GetSize());
            m_bLowELorDisOnly
                ?m_btMod.EnableWindow(FALSE):m_btMod.EnableWindow(m_LimitDataTemp.m_Limit.GetSize());
		}
		else
		{
			AfxMessageBox("读取数据失败！");
		}
     
	}
}


void CEditLimitDlg::OnBnClickedButtonSaveAs()
{
	// TODO: 在此添加控件通知处理程序代码
  
	if (!UpdateData(TRUE))
	{
		return;
	}
	
	if (!IsInputModelAndBulbHigh())
	{
		return;
	}

	CFileDialog dlg(FALSE, "dat", "Unnamed1", 6UL, "Limit File(*.dat)|*.dat|");
	dlg.m_ofn.lpstrInitialDir = g_strLimitDataPath;
	if (IDOK == dlg.DoModal())
	{
		GetData(m_LimitData);
		if (m_LimitData.Store(dlg.GetPathName()))
		{
            g_strTestSettingFileName = dlg.GetPathName();
			SetWindowText("参数设置 - " + g_strTestSettingFileName);
			UpdateData(FALSE);
			AfxMessageBox("保存成功!");
		}
		else
		{
			AfxMessageBox("保存失败！");
		}
	}
}


void CEditLimitDlg::OnBnClickedButtonQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void CEditLimitDlg::OnBnClickedCheckFlux()
{
	// TODO: 在此添加控件通知处理程序代码
	SetEnable();
}

void CEditLimitDlg::SetEnable()
{
	UpdateData(TRUE);
	
	GetDlgItem(IDC_EDIT_FLUX)->EnableWindow(m_bCheckFlux);
	GetDlgItem(IDC_EDIT_FLUX_)->EnableWindow(m_bCheckFlux);
	GetDlgItem(IDC_EDIT_FLUX_2)->EnableWindow(m_bCheckFlux);

	GetDlgItem(IDC_EDIT_HW)->EnableWindow(m_bCheckHW);
	GetDlgItem(IDC_EDIT_HW_)->EnableWindow(m_bCheckHW);
	GetDlgItem(IDC_EDIT_HW_2)->EnableWindow(m_bCheckHW);

	GetDlgItem(IDC_EDIT_LD)->EnableWindow(m_bCheckLd);
	GetDlgItem(IDC_EDIT_LD_)->EnableWindow(m_bCheckLd);
	GetDlgItem(IDC_EDIT_LD_2)->EnableWindow(m_bCheckLd);

	GetDlgItem(IDC_EDIT_LP)->EnableWindow(m_bCheckLp);
	GetDlgItem(IDC_EDIT_LP_)->EnableWindow(m_bCheckLp);
	GetDlgItem(IDC_EDIT_LP_2)->EnableWindow(m_bCheckLp);

	GetDlgItem(IDC_EDIT_PI)->EnableWindow(m_bCheckPI);
	GetDlgItem(IDC_EDIT_PI_)->EnableWindow(m_bCheckPI);
	GetDlgItem(IDC_EDIT_PI_2)->EnableWindow(m_bCheckPI);

	GetDlgItem(IDC_EDIT_PUR)->EnableWindow(m_bCheckPur);
	GetDlgItem(IDC_EDIT_PUR_)->EnableWindow(m_bCheckPur);
	GetDlgItem(IDC_EDIT_PUR_2)->EnableWindow(m_bCheckPur);

	GetDlgItem(IDC_EDIT_PV)->EnableWindow(m_bCheckPV);
	GetDlgItem(IDC_EDIT_PV_)->EnableWindow(m_bCheckPV);
	GetDlgItem(IDC_EDIT_PV_2)->EnableWindow(m_bCheckPV);

	GetDlgItem(IDC_EDIT_RA)->EnableWindow(m_bCheckRa);
	GetDlgItem(IDC_EDIT_RA_)->EnableWindow(m_bCheckRa);
	GetDlgItem(IDC_EDIT_RA_2)->EnableWindow(m_bCheckRa);

	GetDlgItem(IDC_EDIT_TC)->EnableWindow(m_bCheckTc);
	GetDlgItem(IDC_EDIT_TC_)->EnableWindow(m_bCheckTc);
	GetDlgItem(IDC_EDIT_TC_2)->EnableWindow(m_bCheckTc);

	GetDlgItem(IDC_EDIT_U)->EnableWindow(m_bChecku);
	GetDlgItem(IDC_EDIT_U_)->EnableWindow(m_bChecku);
	GetDlgItem(IDC_EDIT_U_2)->EnableWindow(m_bChecku);

	GetDlgItem(IDC_EDIT_V)->EnableWindow(m_bCheckv);
	GetDlgItem(IDC_EDIT_V_)->EnableWindow(m_bCheckv);
	GetDlgItem(IDC_EDIT_V_2)->EnableWindow(m_bCheckv);

	GetDlgItem(IDC_EDIT_X)->EnableWindow(m_bCheckx);
	GetDlgItem(IDC_EDIT_X_)->EnableWindow(m_bCheckx);
	GetDlgItem(IDC_EDIT_X_2)->EnableWindow(m_bCheckx);

	GetDlgItem(IDC_EDIT_Y)->EnableWindow(m_bChecky);
	GetDlgItem(IDC_EDIT_Y_)->EnableWindow(m_bChecky);
	GetDlgItem(IDC_EDIT_Y_2)->EnableWindow(m_bChecky);
	
    GetDlgItem(IDC_EDIT_LPOWER)->EnableWindow(m_bCheckLuminousPower);
    GetDlgItem(IDC_EDIT_LPOWER_)->EnableWindow(m_bCheckLuminousPower);
    GetDlgItem(IDC_EDIT_LPOWER_2)->EnableWindow(m_bCheckLuminousPower);

    GetDlgItem(IDC_EDIT_P)->EnableWindow(m_bCheckP);
    GetDlgItem(IDC_EDIT_P_)->EnableWindow(m_bCheckP);
    GetDlgItem(IDC_EDIT_P_2)->EnableWindow(m_bCheckP);

    GetDlgItem(IDC_EDIT_PF)->EnableWindow(m_bCheckPF);
    GetDlgItem(IDC_EDIT_PF_)->EnableWindow(m_bCheckPF);
    GetDlgItem(IDC_EDIT_PF_2)->EnableWindow(m_bCheckPF);    

    GetDlgItem(IDC_EDIT_FRE)->EnableWindow(m_bCheckFre);
    GetDlgItem(IDC_EDIT_FRE_)->EnableWindow(m_bCheckFre);
    GetDlgItem(IDC_EDIT_FRE_2)->EnableWindow(m_bCheckFre);
}


void CEditLimitDlg::OnBnClickedCheckTc()
{
	// TODO: 在此添加控件通知处理程序代码
	SetEnable();
}


void CEditLimitDlg::OnBnClickedCheckX()
{
	// TODO: 在此添加控件通知处理程序代码
	SetEnable();
}


void CEditLimitDlg::OnBnClickedCheckY()
{
	// TODO: 在此添加控件通知处理程序代码
	SetEnable();
}


void CEditLimitDlg::OnBnClickedCheckU()
{
	// TODO: 在此添加控件通知处理程序代码
	SetEnable();
}


void CEditLimitDlg::OnBnClickedCheckV()
{
	// TODO: 在此添加控件通知处理程序代码
	SetEnable();
}


void CEditLimitDlg::OnBnClickedCheckLd()
{
	// TODO: 在此添加控件通知处理程序代码
	SetEnable();
}


void CEditLimitDlg::OnBnClickedCheckLp()
{
	// TODO: 在此添加控件通知处理程序代码
	SetEnable();
}


void CEditLimitDlg::OnBnClickedCheckPur()
{
	// TODO: 在此添加控件通知处理程序代码
	SetEnable();
}


void CEditLimitDlg::OnBnClickedCheckHw()
{
	// TODO: 在此添加控件通知处理程序代码
	SetEnable();
}


void CEditLimitDlg::OnBnClickedCheckPv()
{
	// TODO: 在此添加控件通知处理程序代码
	SetEnable();
}


void CEditLimitDlg::OnBnClickedCheckNv()
{
	// TODO: 在此添加控件通知处理程序代码
	SetEnable();
}


void CEditLimitDlg::OnBnClickedCheckPi()
{
	// TODO: 在此添加控件通知处理程序代码
	SetEnable();
}


void CEditLimitDlg::OnBnClickedCheckNi()
{
	// TODO: 在此添加控件通知处理程序代码
	SetEnable();
}


void CEditLimitDlg::OnBnClickedCheckRa()
{
	// TODO: 在此添加控件通知处理程序代码
	SetEnable();
}


void CEditLimitDlg::OnBnClickedCheckTestReverse()
{
	// TODO: 在此添加控件通知处理程序代码
	if (FALSE == UpdateData(TRUE))
	{
		return;
	}
}


void CEditLimitDlg::OnBnClickedButtonAutoIntegral()
{
	// TODO: 在此添加控件通知处理程序代码
	if (FALSE == UpdateData(TRUE))
	{
		return;
	}
	BOOL bR;
	if (g_DPSComm.IsRunning())
	{
		RealTimeData data;
		bR = g_DPSComm.GetRealTimeData(data);
		float fVoltage = m_fTestVoltage, 
			fFrequency = m_fTestFrequency;
		if (fabs(data.fVoltageValue - fVoltage) > fVoltage / 100 || fabs(data.fFrequence - fFrequency) > fFrequency / 100)
		{
			bR = g_DPSComm.SetParameterRunning(m_fTestVoltage, m_fTestVoltage,
				g_DPSComm.GetLimitData().LimitCurrentRange2.fUpper, g_DPSComm.GetLimitData().LimitPower.fUpper);
		}
	}
	else
	{
		bR = g_DPSComm.StopOutput();
		bR = g_DPSComm.FastRun(m_fTestVoltage, m_fTestVoltage);
	}
	if (!bR)
	{
		AfxMessageBox("输出电源控制失败!");
		return;
	}
	AfxBeginThread(ThreadAutoIntegral, this);
}


UINT CEditLimitDlg::ThreadAutoIntegral(LPVOID pPar)
{
	CEditLimitDlg * pDlg = (CEditLimitDlg *)pPar;

    float fIntegralTimems[2] = {0, 0};
    float fMinIntegralTimems;
	int iMaxLumPosNum;
	if (g_iColomnNum % 2 == 0)
	{
		iMaxLumPosNum = 2;
	}
	else
	{
		iMaxLumPosNum = 1;		
	}
	int *iMaxLumPos = new int[iMaxLumPosNum];
	for (int i = 0; i < iMaxLumPosNum; i ++)
	{
		iMaxLumPos[i] = g_iColomnNum / 2 + i;
	}
	pDlg->m_bAutoIntegral = TRUE;
	pDlg->GetDlgItem(IDC_BUTTON_AUTO_INTEGRAL)->EnableWindow(FALSE);
    for (int i = 0; i < iMaxLumPosNum; i ++)
    {
        BOOL bR = FALSE;
		if (g_pDoc->m_CommSettingsData.m_iTestChannelControlerType == 1)
		{
			bR = g_SC1000Comm.SwitchChannel(iMaxLumPos[i]);
		}
		else
		{
			bR = g_TestChannelControlComm.SwitchOneChannel(iMaxLumPos[i], TRUE);
		}
		if (!bR)
		{
			pDlg->GetDlgItem(IDC_BUTTON_AUTO_INTEGRAL)->EnableWindow(TRUE);
			AfxMessageBox("开灯失败！");

			pDlg->m_bAutoIntegral = FALSE;
			return 1;
		}
        bR = g_Hass1200Meter.AutoIntegralTime(fIntegralTimems[i], 10000, 40000);
        if (!bR)
        {
			if (g_pDoc->m_CommSettingsData.m_iTestChannelControlerType == 1)
			{
				bR = g_SC1000Comm.SwitchAllLamp(FALSE);
			}
			else
			{
				bR = g_TestChannelControlComm.SwitchAllChannel(FALSE);
			}

            pDlg->GetDlgItem(IDC_BUTTON_AUTO_INTEGRAL)->EnableWindow(TRUE);
            AfxMessageBox("测试失败！");

            pDlg->m_bAutoIntegral = FALSE;
            return 3;
        }

        Sleep(100);
		if (g_pDoc->m_CommSettingsData.m_iTestChannelControlerType == 1)
		{
			bR = g_SC1000Comm.SwitchAllLamp(FALSE);
		}
		else
		{
			bR = g_TestChannelControlComm.SwitchAllChannel(FALSE);
		}
        if (!bR)
        {
            AfxMessageBox("关灯失败！");
            break;
        }
    }
	delete []iMaxLumPos;
	for (int i = 0; i < iMaxLumPosNum; i ++)
	{
        if (i == 0)
        {
            fMinIntegralTimems = fIntegralTimems[i];
        }
        else
        {
            if (fIntegralTimems[i] < fMinIntegralTimems)
            {
                fMinIntegralTimems = fIntegralTimems[i];
            }
        }
	}
	pDlg->GetDlgItem(IDC_BUTTON_AUTO_INTEGRAL)->EnableWindow(TRUE);

	CString strTemp;
	strTemp.Format("%.1f", fMinIntegralTimems);
	pDlg->GetDlgItem(IDC_EDIT_INTEGRAL_TIME)->SetWindowText(strTemp);
//	AfxMessageBox(strTemp);

	pDlg->m_bAutoIntegral = FALSE;
	return 0;
}


float CEditLimitDlg::GetIp(float * fAD, int nNum)
{
	if (NULL == fAD)
	{
		return 0.0f;
	}

	float fMax = 0;
	for (int i = 0; i < nNum; i++)
	{
		if (fAD[i] > fMax)
		{
			fMax = fAD[i];
		}
	}

	return fMax;
}

void CEditLimitDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bAutoIntegral)
	{
		AfxMessageBox("自动积分进行中，请等待积分结束后再退出！");
		return;
	}

	CDialogEx::OnClose();
}


BOOL CEditLimitDlg::IsInputModelAndBulbHigh()
{
    BOOL bInputModel = FALSE, InputBulbHigh = FALSE;
	CString strUnExpe;
    if ("" != m_strLedModel)
	{
        bInputModel = TRUE;
	}
    CString strTemp;
    GetDlgItemText(IDC_EDIT_BALL_HIGH, strTemp);
    m_fBallHigh = (float)atof(strTemp);
    if (m_fBallHigh > 0 && m_fBallHigh < 500)
    {
        InputBulbHigh = TRUE;
    }
    if (bInputModel && m_fBallHigh)
    {
        return TRUE;
    }
    if (!bInputModel)
    {
        strUnExpe += "请填写灯型号!\n";
    }
    if (!InputBulbHigh)
    {
        strUnExpe += "请填标尺刻度!";
    }
    AfxMessageBox(strUnExpe);
    if (!bInputModel)
    {
        GetDlgItem(IDC_EDIT_LED_MODEL)->SetFocus();
    }
    if (!InputBulbHigh)
    {
        GetDlgItem(IDC_EDIT_BALL_HIGH)->SetFocus();
    }
    return FALSE;
}


void CEditLimitDlg::OnBnClickedButtonSetK1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	m_fK1 = 1;
	m_fK2 = 1;
	m_fK3 = 1;
	m_fK4 = 1;
	m_fK5 = 1;

	m_fK6 = 1;
	m_fK7 = 1;
	m_fK8 = 1;
	m_fK9 = 1;
	m_fK10 = 1;

	UpdateData(FALSE);
}


void CEditLimitDlg::OnBnClickedButtonLightning()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	EMC5ASetData data;
	g_EMS61000_5AComm.ShowSettingsDialog(data, m_iEMC5ASelectIndex, g_bDisplayLimitOnly ||
		LOW_EXECUTION_LEVEL == g_iExecutionLevel);
}


void CEditLimitDlg::OnBnClickedButtonUpanddips()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	g_EMS61000_11KComm.ShowSettingsDialog(m_iEMC11KSelectIndex, g_bDisplayLimitOnly||
		LOW_EXECUTION_LEVEL == g_iExecutionLevel);
}


void CEditLimitDlg::OnBnClickedButtonBurnIn()
{
	// TODO: 在此添加控件通知处理程序代码
	CBurnInSettingsDlg dlg;
	dlg.m_iOFFSeconds = m_iBurnInOFFSeconds;
	dlg.m_iONSeconds = m_iBurnInONSeconds;
	if (IDOK == dlg.DoModal())
	{
		m_iBurnInOFFSeconds = dlg.m_iOFFSeconds;
		m_iBurnInONSeconds = dlg.m_iONSeconds;
	}
}


void CEditLimitDlg::OnBnClickedButtonTest()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	CRectificationTestDlg dlg;
	dlg.m_fFrequency		= m_fTestFrequency;
	dlg.m_fVoltage			= m_fTestVoltage;
	dlg.m_fIntegralTimems	= m_fIntegralTime;
	dlg.m_iElectricalHeatingmsec = (int)m_fLEDWarmUPTimemsec;
	dlg.m_pbTestChannel[0]	= m_bTestCh1;
	dlg.m_pbTestChannel[1]	= m_bTestCh2;
	dlg.m_pbTestChannel[2]	= m_bTestCh3;
	dlg.m_pbTestChannel[3]	= m_bTestCh4;
	dlg.m_pbTestChannel[4]	= m_bTestCh5;

	dlg.m_pbTestChannel[5] = m_bTestCh6;
	dlg.m_pbTestChannel[6] = m_bTestCh7;
	dlg.m_pbTestChannel[7] = m_bTestCh8;
	dlg.m_pbTestChannel[8] = m_bTestCh9;
	dlg.m_pbTestChannel[9] = m_bTestCh10;

	dlg.m_iRangeCF = m_iRangeCF;
	dlg.m_iRangeI = m_iRangeI;
	dlg.m_iRangeU = m_iRangeU;
	for (int i = 0; i < DATA_CAHNNEL_NUM; i++)
	{
		dlg.m_fStdValue[i] = m_fStdFlux[i];
		dlg.m_fTestValue1[i] = m_fTestFlux[i] ;
		dlg.m_fTestValue2[i] = m_pfTestFlux2[i];
	}
	dlg.m_fShowValue[0] = m_pfTestFlux2[0] * m_fK1;
	dlg.m_fShowValue[1] = m_pfTestFlux2[1] * m_fK2;
	dlg.m_fShowValue[2] = m_pfTestFlux2[2] * m_fK3;
	dlg.m_fShowValue[3] = m_pfTestFlux2[3] * m_fK4;
	dlg.m_fShowValue[4] = m_pfTestFlux2[4] * m_fK5;
	dlg.m_fShowValue[5] = m_pfTestFlux2[5] * m_fK6;
	dlg.m_fShowValue[6] = m_pfTestFlux2[6] * m_fK7;
	dlg.m_fShowValue[7] = m_pfTestFlux2[7] * m_fK8;
	dlg.m_fShowValue[8] = m_pfTestFlux2[8] * m_fK9;
	dlg.m_fShowValue[9] = m_pfTestFlux2[9] * m_fK10;

    dlg.m_fSetFrequency = m_fTestFrequency;
    dlg.m_fSetVoltage = m_fTestVoltage;


	if (IDOK == dlg.DoModal())
	{
		for (int i = 0; i < DATA_CAHNNEL_NUM; i++)
		{
			m_fTestFlux[i] = dlg.m_fTestValue1[i];
			m_fStdFlux[i] = dlg.m_fStdValue[i];
			m_pfTestFlux2[i] = dlg.m_fTestValue2[i];
		}
		m_fK1 = m_fStdFlux[0] / (m_fTestFlux[0] > 1 ? m_fTestFlux[0] : 1);
		m_fK2 = m_fStdFlux[1] / (m_fTestFlux[1] > 1 ? m_fTestFlux[1] : 1);
		m_fK3 = m_fStdFlux[2] / (m_fTestFlux[2] > 1 ? m_fTestFlux[2] : 1);
		m_fK4 = m_fStdFlux[3] / (m_fTestFlux[3] > 1 ? m_fTestFlux[3] : 1);
		m_fK5 = m_fStdFlux[4] / (m_fTestFlux[4] > 1 ? m_fTestFlux[4] : 1);
	
		m_fK6 = m_fStdFlux[5] / (m_fTestFlux[5] > 1 ? m_fTestFlux[5] : 1);
		m_fK7 = m_fStdFlux[6] / (m_fTestFlux[6] > 1 ? m_fTestFlux[6] : 1);
		m_fK8 = m_fStdFlux[7] / (m_fTestFlux[7] > 1 ? m_fTestFlux[7] : 1);
		m_fK9 = m_fStdFlux[8] / (m_fTestFlux[8] > 1 ? m_fTestFlux[8] : 1);
		m_fK10 = m_fStdFlux[9] / (m_fTestFlux[9] > 1 ? m_fTestFlux[9] : 1);
	}

	m_iRangeCF = dlg.m_iRangeCF;
	m_iRangeI = dlg.m_iRangeI;
	m_iRangeU = dlg.m_iRangeU;

	CString strTemp;
	m_cRangeI.ResetContent();
	m_cRangeV.ResetContent();
	for (int i = 0; i < g_PowerMeterComm.GetVolRangeNum(); i ++)
	{
		strTemp.Format("%g", g_PowerMeterComm.GetVolRange(i));
		m_cRangeV.AddString(strTemp);
	}

	for (int i = 0; i < g_PowerMeterComm.GetCurRangeNum(); i ++)
	{
		strTemp.Format("%g", g_PowerMeterComm.GetCurRange(i));
		m_cRangeI.AddString(strTemp);
	}

	UpdateData(FALSE);
}


void CEditLimitDlg::OnBnClickedCheckLpower()
{
	// TODO: 在此添加控件通知处理程序代码
	SetEnable();
}


void CEditLimitDlg::OnBnClickedButtonAlarm()
{
	// TODO: 在此添加控件通知处理程序代码
	CAlarmSettingsDlg dlg;
	dlg.m_bStopTest = m_AlarmSettingsData.m_bStopTest;

    for (int i = 0; i < g_iGaugeNum; i ++)
    {  
        dlg.m_fCurrentH[i] = m_AlarmSettingsData.m_fCurrentH[i];
        dlg.m_fCurrentL[i] = m_AlarmSettingsData.m_fCurrentL[i];
		dlg.m_fVoltageH[i] = m_AlarmSettingsData.m_fVoltageH[i];
		dlg.m_fVoltageL[i] = m_AlarmSettingsData.m_fVoltageL[i];
        dlg.m_fPowerH[i] = m_AlarmSettingsData.m_fPowerH[i];
        dlg.m_fPowerL[i] = m_AlarmSettingsData.m_fPowerL[i];
        dlg.m_bRegion[i] = m_AlarmSettingsData.m_bRegionAlarm[i];
        dlg.m_iRegionRingIndex[i] = m_AlarmSettingsData.m_iRegionRingIndex[i] + 1;
    }

    for (int i = 0; i < g_iTMPControlNum; i ++)
    {
        dlg.m_fTMPH[i] = m_AlarmSettingsData.m_fTMPH[i];
        dlg.m_fTMPL[i] = m_AlarmSettingsData.m_fTMPL[i];
		dlg.m_fTMPOPEN[i] = m_AlarmSettingsData.m_fTMPOPEN[i];
        dlg.m_bTMP[i] = m_AlarmSettingsData.m_bTMPAlarm[i];
        dlg.m_iTMPRingIndex[i] = m_AlarmSettingsData.m_iTMPRingIndex[i]  + 1;

    }	



	

	// Ring index
	dlg.m_bLampTooHigh = m_AlarmSettingsData.m_bLampTooHighAlarm;
	dlg.m_iLampTooHighRingIndex = m_AlarmSettingsData.m_iLampTooHighRingIndex + 1;
	dlg.m_bManualStop = m_AlarmSettingsData.m_bManualStopAlarm;
	dlg.m_iManualStopRingIndex = m_AlarmSettingsData.m_iManualStopRingIndex + 1;

    dlg.m_bScanerOverTimeAlarm = m_AlarmSettingsData.m_bScanerOverTimeAlarm;
    dlg.m_iScanerOverTimeRingIndex= m_AlarmSettingsData.m_iScanerOverTimeRingIndex + 1;
	if (IDOK == dlg.DoModal())
	{
		m_AlarmSettingsData.m_bStopTest = dlg.m_bStopTest;



        for (int i = 0; i < g_iGaugeNum; i ++)
        {  
            m_AlarmSettingsData.m_fCurrentH[i] = dlg.m_fCurrentH[i];
            m_AlarmSettingsData.m_fCurrentL[i] = dlg.m_fCurrentL[i];
            m_AlarmSettingsData.m_fVoltageH[i] = dlg.m_fVoltageH[i];
            m_AlarmSettingsData.m_fVoltageL[i] = dlg.m_fVoltageL[i];
            m_AlarmSettingsData.m_fPowerH[i] = dlg.m_fPowerH[i];
            m_AlarmSettingsData.m_fPowerL[i] = dlg.m_fPowerL[i];
            m_AlarmSettingsData.m_bRegionAlarm[i] = dlg.m_bRegion[i];
            m_AlarmSettingsData.m_iRegionRingIndex[i] = dlg.m_iRegionRingIndex[i] - 1;
        }

        for (int i = 0; i < g_iTMPControlNum; i ++)
        {
            m_AlarmSettingsData.m_fTMPH[i] = dlg.m_fTMPH[i];
            m_AlarmSettingsData.m_fTMPL[i] = dlg.m_fTMPL[i];
			m_AlarmSettingsData.m_fTMPOPEN[i] = dlg.m_fTMPOPEN[i];
            m_AlarmSettingsData.m_bTMPAlarm[i] = dlg.m_bTMP[i];
            m_AlarmSettingsData.m_iTMPRingIndex[i] = dlg.m_iTMPRingIndex[i] - 1;

        }	

		// Ring index
		m_AlarmSettingsData.m_bLampTooHighAlarm = dlg.m_bLampTooHigh;
		m_AlarmSettingsData.m_iLampTooHighRingIndex = dlg.m_iLampTooHighRingIndex - 1;
		m_AlarmSettingsData.m_bManualStopAlarm = dlg.m_bManualStop;
		m_AlarmSettingsData.m_iManualStopRingIndex = dlg.m_iManualStopRingIndex - 1;

        m_AlarmSettingsData.m_bScanerOverTimeAlarm = dlg.m_bScanerOverTimeAlarm;
        m_AlarmSettingsData.m_iScanerOverTimeRingIndex= dlg.m_iScanerOverTimeRingIndex - 1;
	}
}


void CEditLimitDlg::OnCbnSelchangeComboCf()
{
    // TODO: 在此添加控件通知处理程序代码
  
	UpdateData(TRUE);

	g_PowerMeterComm.Initialize(g_pDoc->m_CommSettingsData.m_strCOMPF2010A ,g_pDoc->m_CommSettingsData.m_iPFType, 
		m_iRangeCF);
	CString strTemp;
	m_cRangeI.ResetContent();
	m_cRangeV.ResetContent();
	for (int i = 0; i < g_PowerMeterComm.GetVolRangeNum(); i ++)
	{
		strTemp.Format("%g", g_PowerMeterComm.GetVolRange(i));
		m_cRangeV.AddString(strTemp);
	}

	for (int i = 0; i < g_PowerMeterComm.GetCurRangeNum(); i ++)
	{
		strTemp.Format("%g", g_PowerMeterComm.GetCurRange(i));
		m_cRangeI.AddString(strTemp);
	}
	m_cRangeV.SetCurSel(0);
	m_cRangeI.SetCurSel(0);

}


void CEditLimitDlg::OnBnClickedCheckPf()
{
    // TODO: 在此添加控件通知处理程序代码
    SetEnable();
}


void CEditLimitDlg::OnBnClickedCheckP()
{
    // TODO: 在此添加控件通知处理程序代码
    SetEnable();
}


void CEditLimitDlg::OnBnClickedCheckFre()
{
    // TODO: 在此添加控件通知处理程序代码
    SetEnable();
}


void CEditLimitDlg::Enable_bDisor_LowExecu(void)
{
    if (LOW_EXECUTION_LEVEL == g_iExecutionLevel)
    {
		GetDlgItem(IDC_BUTTON_SAVE_AS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_SAVE)->ShowWindow(SW_HIDE);
		EnaleControls_bDisor_LowExecu();
	}
	if (TRUE == g_bDisplayLimitOnly)
	{
		GetDlgItem(IDC_BUTTON_SAVE_AS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_SAVE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_OPEN)->ShowWindow(SW_HIDE);
		EnaleControls_bDisor_LowExecu();
	}
}


void CEditLimitDlg::EnaleControls_bDisor_LowExecu(void)
{
	if (m_bLowELorDisOnly)
	{
		CEdit *pEdit;
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TEST_VOLTAGE);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TEST_FREQUENCY);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_LED_WARMUP_TIME);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_INTEGRAL_TIME);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_EDIT_INTEGRAL_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_RANGE_I)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_CF)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_RANGE_U)->EnableWindow(FALSE);				
		GetDlgItem(IDC_CHECK_DIRECTION_OPPOSITE)->EnableWindow(FALSE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_MIN_SECONDS);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_CHECK_BURN_IN)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_LIGHTNING)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_VOLTAGE_UP_AND_DIPS)->EnableWindow(FALSE);

		GetDlgItem(IDC_CHECK_CH1)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_CH2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_CH3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_CH4)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_CH5)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_CH6)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_CH7)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_CH8)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_CH9)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_CH10)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_CH11)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_CH12)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_CH13)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_CH14)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_CH15)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_CH16)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_CH17)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_CH18)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_CH19)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_CH20)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_FLUX_)->EnableWindow(FALSE);	
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_FLUX);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_FLUX_);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_FLUX_2);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_CHECK_TC_)->EnableWindow(FALSE);	
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TC);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TC_);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TC_2);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_CHECK_RA_)->EnableWindow(FALSE);	
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_RA);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_RA_);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_RA_2);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_CHECK_X_)->EnableWindow(FALSE);	
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_X);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_X_);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_X_2);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_CHECK_Y_)->EnableWindow(FALSE);	
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Y);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Y_);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Y_2);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_CHECK_PV_)->EnableWindow(FALSE);	
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PV);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PV_);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PV_2);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_CHECK_U_)->EnableWindow(FALSE);	
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_U);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_U_);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_U_2);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_CHECK_V_)->EnableWindow(FALSE);	
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_V);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_V_);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_V_2);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_CHECK_PI_)->EnableWindow(FALSE);	
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PI);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PI_);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PI_2);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_CHECK_LD_)->EnableWindow(FALSE);	
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_LD);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_LD_);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_LD_2);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_CHECK_LP_)->EnableWindow(FALSE);	
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_LP);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_LP_);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_LP_2);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_CHECK_P_)->EnableWindow(FALSE);	
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_P);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_P_);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_P_2);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_CHECK_HW_)->EnableWindow(FALSE);	
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_HW);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_HW_);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_HW_2);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_CHECK_LPOWER)->EnableWindow(FALSE);	
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_LPOWER);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_LPOWER_);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_LPOWER_2);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_CHECK_PF_)->EnableWindow(FALSE);	
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PF);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PF_);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PF_2);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_CHECK_PF_)->EnableWindow(FALSE);	
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PF);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PF_);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PF_2);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_CHECK_PF_)->EnableWindow(FALSE);	
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PF);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PF_);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PF_2);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_CHECK_PUR_)->EnableWindow(FALSE);	
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PUR);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PUR_);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PUR_2);
		pEdit->SetReadOnly(TRUE);	
		GetDlgItem(IDC_CHECK_FRE)->EnableWindow(FALSE);	
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_FRE);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_FRE_);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_FRE_2);
		pEdit->SetReadOnly(TRUE);

		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_BALL_HIGH);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_DATE);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_NAME);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_LED_MODEL);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_REMARKS);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_BUTTON_AUTO_INTEGRAL)->EnableWindow(FALSE);
        m_btAdd.ShowWindow(SW_HIDE);
        m_btMod.ShowWindow(SW_HIDE);
        m_btDel.ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHECK_JUDGE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_LIMITPARA_NAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_LIMIT_PARA_NAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_LIMIT_V)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_PARA_OFFSET_UP)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_PARA_OFFSET_LOW)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_LIMIT_V_OFFSET1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_LIMIT_V_OFFSET2)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_STA_VAL)->ShowWindow(SW_HIDE);

        pEdit = (CEdit*)GetDlgItem(IDC_EDIT_STA_VOL);
        pEdit->SetReadOnly(TRUE);
        pEdit = (CEdit*)GetDlgItem(IDC_EDIT_STA_POW);
        pEdit->SetReadOnly(TRUE);
        pEdit = (CEdit*)GetDlgItem(IDC_EDIT_STA_FLUX);
        pEdit->SetReadOnly(TRUE);
        pEdit = (CEdit*)GetDlgItem(IDC_EDIT_STA_TC);
        pEdit->SetReadOnly(TRUE);

        pEdit = (CEdit*)GetDlgItem(IDC_EDIT_LED_UNON_POW);
        pEdit->SetReadOnly(TRUE);
        pEdit = (CEdit*)GetDlgItem(IDC_EDIT_LED_UNON_FLUX);
        pEdit->SetReadOnly(TRUE);
	}
}


void CEditLimitDlg::OnBnClickedCheckJudge()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_cLimitVal.EnableWindow(m_bCheckJudge);
    m_cLimitVal_Offset1.EnableWindow(m_bCheckJudge);
    m_cLimitVal_Offset2.EnableWindow(m_bCheckJudge);
}


void CEditLimitDlg::OnBnClickedButtonAdd()
{
    // TODO: 在此添加控件通知处理程序代码
    GetLimitFromView();
    int i;
    for (i = 0; i < m_LimitDataTemp.m_Limit.GetSize(); i ++)
    {
        if (m_LimitDataTemp.m_Limit.GetAt(i).m_iCurPara == m_OneParaLimit.m_iCurPara)
        {
            return;
        }
    }

    m_LimitDataTemp.AddtoLimit(m_OneParaLimit);
    m_LimitDataTemp.Relist(m_cList, !m_bLowELorDisOnly);
    m_bLowELorDisOnly
        ?m_btDel.EnableWindow(FALSE):m_btDel.EnableWindow(m_LimitDataTemp.m_Limit.GetSize());
    m_bLowELorDisOnly
        ?m_btMod.EnableWindow(FALSE):m_btMod.EnableWindow(m_LimitDataTemp.m_Limit.GetSize());
}


void CEditLimitDlg::OnBnClickedButtonMod()
{
    // TODO: 在此添加控件通知处理程序代码
    GetLimitFromView();
    if (m_iListSel < 0 || m_iListSel > m_LimitDataTemp.m_Limit.GetSize())
    {     
        AfxMessageBox("未选中需修改参数限值!");
        return;
    }
    if (-1 == m_LimitDataTemp.ModifytoLimit(m_OneParaLimit))
    {
        AfxMessageBox("未选中需修改参数限值!");
    }  
    m_LimitDataTemp.Relist(m_cList, !m_bLowELorDisOnly);
}


void CEditLimitDlg::OnBnClickedButtonDel()
{
    // TODO: 在此添加控件通知处理程序代码
    if (m_iListSel < 0 || m_iListSel > m_LimitDataTemp.m_Limit.GetSize())
    {     
        return;
    }
    m_LimitDataTemp.m_Limit.RemoveAt(m_iListSel);
    m_LimitDataTemp.Relist(m_cList, !m_bLowELorDisOnly);
    m_bLowELorDisOnly
        ?m_btDel.EnableWindow(FALSE):m_btDel.EnableWindow(m_LimitDataTemp.m_Limit.GetSize());
    m_bLowELorDisOnly
        ?m_btMod.EnableWindow(FALSE):m_btMod.EnableWindow(m_LimitDataTemp.m_Limit.GetSize());
}


void  CEditLimitDlg::GetLimitFromView()
{
   UpdateData(TRUE);
   m_OneParaLimit.m_bCheckJudge = m_bCheckJudge;
   m_OneParaLimit.m_iCurPara = m_iCurParaLimit;
   m_OneParaLimit.m_fLimitVal = m_fLimitVal;
   m_OneParaLimit.m_fLimitVal_Offset1 = m_fLimitVal_Offset1;
   m_OneParaLimit.m_fLimitVal_Offset2 = m_fLimitVal_Offset2;
}


void  CEditLimitDlg::SetLimittoView()
{
    m_bCheckJudge = m_OneParaLimit.m_bCheckJudge;
    m_iCurParaLimit = m_OneParaLimit.m_iCurPara;
    m_fLimitVal = m_OneParaLimit.m_fLimitVal;
    m_fLimitVal_Offset1 = m_OneParaLimit.m_fLimitVal_Offset1;
    m_fLimitVal_Offset2 = m_OneParaLimit.m_fLimitVal_Offset2;
    if(m_bLowELorDisOnly)
    {
        m_cLimitVal.EnableWindow(FALSE);
        m_cLimitVal_Offset1.EnableWindow(FALSE);
        m_cLimitVal_Offset2.EnableWindow(FALSE);
    }
    else
    {
        m_cLimitVal.EnableWindow(m_bCheckJudge);
        m_cLimitVal_Offset1.EnableWindow(m_bCheckJudge);
        m_cLimitVal_Offset2.EnableWindow(m_bCheckJudge);
    }
    UpdateData(FALSE);      
}



void CEditLimitDlg::OnNMClickListLimit(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    SetTimer(1, 20, NULL);
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    m_iListSel = pNMListView->iItem;

    *pResult = 0;
}



void CEditLimitDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    if (1 == nIDEvent)
    {
        for (int i = 0; i < m_LimitDataTemp.m_Limit.GetSize(); i ++)
        {
            m_LimitDataTemp.m_Limit.GetAt(i).m_bCheckJudge = m_cList.GetCheck(i);
        }
        if (m_iListSel >= 0 && m_iListSel <= m_LimitDataTemp.m_Limit.GetSize() - 1)
        {
            m_OneParaLimit = m_LimitDataTemp.m_Limit.GetAt(m_iListSel);
            SetLimittoView();
            m_cList.SetItemState(m_iListSel, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
            m_cList.EnsureVisible(m_iListSel, FALSE);	
        }
        KillTimer(1);
    }
    if (2 == nIDEvent)
    {
        KillTimer(2);
        OnBnClickedButtonOpen();
    }
    CDialogEx::OnTimer(nIDEvent);
}


BOOL CEditLimitDlg::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (nCode == 0)
	{
		for (int i = 0; i < DATA_CAHNNEL_NUM; i ++)
		{
			if (IDC_CHECK_CH1 + i == nID )
			{
				UpdateData(TRUE);
			}
			if (IDC_CHECK_CH11 + i == nID)
			{
				UpdateData(TRUE);			
			}
		}
	}
	

	return CDialogEx::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



void CEditLimitDlg::OnBnClickedButtonMy()
{
	// TODO: 在此添加控件通知处理程序代码
	//漫游老炼功能
	int i;
	CDlgMyLastSet dlg;
	
	dlg.m_fVolMyLastList.RemoveAll();
	dlg.m_fFreqMyLastList.RemoveAll();
	dlg.m_iTimeMyLastList.RemoveAll();
	for (i = 0; i < m_LimitData.m_fVolMyLast.GetSize();i++)
	{
		dlg.m_fVolMyLastList.Add(m_LimitData.m_fVolMyLast[i]);
		dlg.m_fFreqMyLastList.Add(m_LimitData.m_fFreqMyLast[i]);
		dlg.m_iTimeMyLastList.Add(m_LimitData.m_iTimeMyLast[i]);
	}

	int iR = dlg.DoModal();
	if(iR == IDCANCEL)
	{
		return;
	}

	m_LimitData.m_fVolMyLast.RemoveAll();
	m_LimitData.m_fFreqMyLast.RemoveAll();
	m_LimitData.m_iTimeMyLast.RemoveAll();
	for (i = 0; i < dlg.m_fVolMyLastList.GetSize();i++)
	{
		m_LimitData.m_fVolMyLast.Add(dlg.m_fVolMyLastList[i]);
		m_LimitData.m_fFreqMyLast.Add(dlg.m_fFreqMyLastList[i]);
		m_LimitData.m_iTimeMyLast.Add(dlg.m_iTimeMyLastList[i]);
	}
}

void CEditLimitDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgSaftSetup dlg;
	dlg.m_iDebugType = 0;
	dlg.m_iTypeNYY		= m_LimitData.m_iTypeNYY;
	dlg.m_fSetVolNYY	= m_LimitData.m_fSetVolNYY;
	dlg.m_fSetTimeNYY	= m_LimitData.m_fSetTimeNYY;
	dlg.m_fNYYLimit		= m_LimitData.m_fNYYLimit;
	dlg.m_fSetVolJYDZ	= m_LimitData.m_fSetVolJYDZ;
	dlg.m_fSetTimeJYDZ	= m_LimitData.m_fSetTimeJYDZ;
	dlg.m_fJYDZLimit	= m_LimitData.m_fJYDZLimit;
	dlg.m_fSetVolXLDL	= m_LimitData.m_fSetVolXLDL;
	dlg.m_fSetTimeXLDL	= m_LimitData.m_fSetTimeXLDL;
	dlg.m_fXLDLLimit	= m_LimitData.m_fXLDLLimit;
	int iR = dlg.DoModal();
	if(iR == IDCANCEL)
		return;

	m_LimitData.m_iTypeNYY		= dlg.m_iTypeNYY;
	m_LimitData.m_fSetVolNYY	= dlg.m_fSetVolNYY;
	m_LimitData.m_fSetTimeNYY	= dlg.m_fSetTimeNYY;
	m_LimitData.m_fNYYLimit		= dlg.m_fNYYLimit;
	m_LimitData.m_fSetVolJYDZ	= dlg.m_fSetVolJYDZ;
	m_LimitData.m_fSetTimeJYDZ	= dlg.m_fSetTimeJYDZ;
	m_LimitData.m_fJYDZLimit	= dlg.m_fJYDZLimit;
	m_LimitData.m_fSetVolXLDL	= dlg.m_fSetVolXLDL;
	m_LimitData.m_fSetTimeXLDL	= dlg.m_fSetTimeXLDL;
	m_LimitData.m_fXLDLLimit	= dlg.m_fXLDLLimit;
	
	SetData(m_LimitData);
}


void CEditLimitDlg::OnBnClickedButtonSdcm()
{
	// TODO: 在此添加控件通知处理程序代码
	SDCM_DLL_Dlg_Domodal();
}
