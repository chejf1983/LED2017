// Chip3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "Chip3Dlg.h"
#include "Functions.h"
#include "SetParameter.h"
#include "ChipsHandle.h"

#include "SpectraArsenalEmissionAPI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChip3Dlg dialog
extern int setting_wl[128];

CChip3Dlg::CChip3Dlg(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CChip3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChip3Dlg)
	//}}AFX_DATA_INIT
}


void CChip3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChip3Dlg)
	DDX_Control(pDX, IDC_Test_VZ, m_tVZ);
	DDX_Control(pDX, IDC_Test_LV, m_tLV);
	DDX_Control(pDX, IDC_Test_LE, m_tLE);
	DDX_Control(pDX, IDC_Test_IE, m_tIE);
	DDX_Control(pDX, IDC_CalItemList, m_calItemList);
	DDX_Control(pDX, IDC_ClearDark3, m_clearDark);
	DDX_Control(pDX, IDC_AutoGetOpticGain3, m_getGain);
	DDX_Control(pDX, IDC_AddDark3, m_addDark);
	DDX_Control(pDX, IDC_ClearCalibration, m_clearCal);
	DDX_Control(pDX, IDC_GetCalibration, m_getCal);
	DDX_Control(pDX, IDC_CalibrationTest3, m_caltest);
	DDX_Control(pDX, IDC_AutoSetInteTime3, m_autosetTime);
	DDX_Control(pDX, IDC_shootset3, m_shootset3);
	DDX_Control(pDX, IDC_XYList, m_xylist);
	DDX_Control(pDX, IDC_cbOpticGain3, m_cbOpticGain3);
	DDX_Control(pDX, IDC_cbWLSteptype3, m_cbWLSteptype3);
	DDX_Control(pDX, IDC_Test_XYZ, m_tXYZ);
	DDX_Control(pDX, IDC_Test_WL, m_tWL);
	DDX_Control(pDX, IDC_Test_VR, m_tVR);
	DDX_Control(pDX, IDC_Test_VF, m_tVF);
	DDX_Control(pDX, IDC_Test_THY, m_tTHY);
	DDX_Control(pDX, IDC_Test_PWL, m_tPWL);
	DDX_Control(pDX, IDC_Test_PUR, m_tPUR);
	DDX_Control(pDX, IDC_Test_IV, m_tIV);
	DDX_Control(pDX, IDC_Test_IR, m_tIR);
	DDX_Control(pDX, IDC_Test_IF, m_tIF);
	DDX_Control(pDX, IDC_Test_DVF, m_tDVF);
	DDX_Control(pDX, IDC_Test_DeltaWL, m_tDeltaWL);
	DDX_Control(pDX, IDC_Test_CRI, m_tCRI);
	DDX_Control(pDX, IDC_Test_CCT, m_tCCT);
	DDX_Control(pDX, IDC_SetChipList3, m_chipList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChip3Dlg, CResizingDialog)
	//{{AFX_MSG_MAP(CChip3Dlg)
/*	ON_BN_CLICKED(IDC_Test_IF, OnTestIF)
	ON_BN_CLICKED(IDC_Test_IR, OnTestIR)
	ON_BN_CLICKED(IDC_Test_VF, OnTestVF)
	ON_BN_CLICKED(IDC_Test_VR, OnTestVR)
	ON_BN_CLICKED(IDC_Test_DVF, OnTestDVF)
	ON_BN_CLICKED(IDC_Test_THY, OnTestTHY)
	ON_BN_CLICKED(IDC_Test_IV, OnTestIV)
	ON_BN_CLICKED(IDC_Test_XYZ, OnTestXYZ)
	ON_BN_CLICKED(IDC_Test_WL, OnTestWL)
	ON_BN_CLICKED(IDC_Test_PWL, OnTestPWL)
	ON_BN_CLICKED(IDC_Test_DeltaWL, OnTestDeltaWL)
	ON_BN_CLICKED(IDC_Test_PUR, OnTestPUR)
	ON_BN_CLICKED(IDC_Test_CCT, OnTestCCT)
	ON_BN_CLICKED(IDC_Test_CRI, OnTestCRI)*/
	ON_BN_CLICKED(IDC_shootset3, Onshootset3)
	ON_BN_CLICKED(IDC_ClearDark3, OnClearDark3)
	ON_BN_CLICKED(IDC_AddDark3, OnAddDark3)
	ON_BN_CLICKED(IDC_CalibrationTest3, OnCalibrationTest3)
	ON_BN_CLICKED(IDC_AutoSetInteTime3, OnAutoSetInteTime3)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_ClearCalibration, OnClearCalibration)
	ON_BN_CLICKED(IDC_GetCalibration, OnGetCalibration)
	ON_BN_CLICKED(IDC_AutoGetOpticGain3, OnAutoGetOpticGain3)
	ON_EN_CHANGE(IDC_KLV, OnChangeKlv)
	ON_EN_CHANGE(IDC_KLI, OnChangeKli)
	ON_BN_CLICKED(IDC_AddItem, OnAddItem)
	ON_BN_CLICKED(IDC_delItem, OndelItem)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SET_ITEMS, PopulateComboList)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChip3Dlg message handlers
extern int intMixLight;
extern int intVfAverage;
extern int testItemChip[3];
extern int c[3];
extern TESTTYPE CHIP[3][18];
extern int intWLSteps[3];
extern int intOpticGain[3];   
extern double intIntegrationTime[3];
extern int DeadLed;
extern int DeadLedBin[3];
extern bool usespectrum[3];
extern bool testXYZ[3];
extern int polfalsenum[3];  //反向测试项目的个数  IR VR
extern LightParam KeepLight[3];
extern LightParam PolParam[3];
//extern Wrapper wrapper;
extern double sngCurrentDark[3][PIXELNUM];
extern bool engineer;
extern bool Operator;

extern double setting_spectrum[PIXELNUM];
extern int tempchiptype;
extern int intMixLight;
extern double tempV3, tempI3;
extern bool updateRect;
extern double staMaxPower;
extern SystemSet systemset;

extern double recommended;
extern double gettime;
extern double lastpower;

extern CList<CString, CString> tempItemforlevel[3];

extern int calsta_average;
extern int calsta_boxcar;

BOOL CChip3Dlg::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	chip = 2;
	m_cbWLSteptype3.InsertString(0, "1nm");
	m_cbWLSteptype3.InsertString(1, "5nm");

	m_cbOpticGain3.InsertString(0, "低亮LED");
	m_cbOpticGain3.InsertString(1, "普亮LED");
	m_cbOpticGain3.InsertString(2, "高亮LED");
	m_cbOpticGain3.InsertString(3, "超高亮LED");

	testItemChip[chip] = 0;

	m_chipList.Init();
	m_calItemList.Init();
	m_xylist.Init();
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 20;
	strcpy(lf.lfFaceName, "Verdana");
	font.CreateFontIndirect(&lf);
	m_chipList.SetFont(&font, TRUE);
	m_xylist.SetFont(&font, TRUE);

	m_chipList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_calItemList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_xylist.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	CString strValidChars = "0123456789.-";
	m_chipList.SetValidEditCtrlCharacters(strValidChars);
	m_calItemList.SetValidEditCtrlCharacters(strValidChars);
	m_xylist.SetValidEditCtrlCharacters(strValidChars);

	initdlg();
	SetDialogFace();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CChip3Dlg::PopulateComboList(WPARAM wParam, LPARAM lParam)
{
	CComboBox *pCombo1 = static_cast<CComboBox*>(GetFocus());
	CComboBox *pCombo2 = static_cast<CComboBox*>(GetFocus());
	CComboBox *pCombo3 = static_cast<CComboBox*>(GetFocus());

	CRect rect1, rect2, rect3;
	pCombo1->GetWindowRect(&rect1);
	pCombo2->GetWindowRect(&rect2);
	pCombo2->GetWindowRect(&rect3);

	CPoint comboTopLeft1(rect1.TopLeft());
	CPoint comboTopLeft2(rect2.TopLeft());
	CPoint comboTopLeft3(rect3.TopLeft());

	m_chipList.GetWindowRect(&rect1);
	m_xylist.GetWindowRect(&rect2);
	m_calItemList.GetWindowRect(&rect3);

	int iColIndex = wParam;

	CStringList* pComboList = reinterpret_cast<CStringList*>(lParam);
	pComboList->RemoveAll();

	if(rect1.PtInRect(comboTopLeft1))
	{
		if(8 == iColIndex)
		{
			pComboList->AddTail("True");
			pComboList->AddTail("False");
		}
	}

	if(rect2.PtInRect(comboTopLeft2))
	{
		if(4 == iColIndex)
		{
			pComboList->AddTail("+");
			pComboList->AddTail("*");
			pComboList->AddTail("* +");
		}
	}

	if(rect3.PtInRect(comboTopLeft3))
	{
		if(5 == iColIndex)
		{
			pComboList->AddTail("+");
			pComboList->AddTail("*");
			pComboList->AddTail("* +");
		}
		if(8 == iColIndex)
		{
			pComboList->AddTail("Yes");
			pComboList->AddTail("No");
		}
	}

	return true;
}

bool CChip3Dlg::setParameter(int i)
{
	CString s, str;

	s.Format("%d", testItemChip[chip]+1);
	m_chipList.InsertItem(testItemChip[chip], s);
	m_calItemList.InsertItem(testItemChip[chip], s);

	m_chipList.SetItemText(testItemChip[chip], 1, CHIP[chip][i].TestItem);
	m_calItemList.SetItemText(testItemChip[chip], 1, CHIP[chip][i].TestItem);

	s.Format("%d", CHIP[chip][i].Delay);
	m_chipList.SetItemText(testItemChip[chip], 2, s);
	s.Format("%f", CHIP[chip][i].VCom);
	m_chipList.SetItemText(testItemChip[chip], 3, ReformatString(s));
	s.Format("%f", CHIP[chip][i].ICom); 
	m_chipList.SetItemText(testItemChip[chip], 4, ReformatString(s));

	sscanf(CHIP[chip][i].TestItem, "%[^(]", str);
	if(0 == strcmp(str, "XYZ"))
	{
		m_chipList.SetItemText(testItemChip[chip], 2, "disable");
		m_chipList.SetItemText(testItemChip[chip], 3, "disable");
		m_chipList.SetItemText(testItemChip[chip], 4, "disable");
		m_chipList.SetItemText(testItemChip[chip], 5, "disable");
		m_chipList.SetItemText(testItemChip[chip], 6, "disable");
		
		m_calItemList.SetItemText(testItemChip[chip], 2, "disable");
		m_calItemList.SetItemText(testItemChip[chip], 3, "disable");
		m_calItemList.SetItemText(testItemChip[chip], 4, "disable");
		m_calItemList.SetItemText(testItemChip[chip], 8, "No");
		
		s.Format("%f", CHIP[chip][i].stavalue1);
		m_xylist.SetItemText(0, 1, ReformatString(s));
		s.Format("%f", CHIP[chip][i].stavalue2);
		m_xylist.SetItemText(1, 1, ReformatString(s));
		
		if(0 == CHIP[chip][i].Calway)
		{
			m_xylist.SetItemText(0, 4, "+");
			m_xylist.SetItemText(1, 4, "+");
			
			m_xylist.SetItemText(0, 5, "1");
			m_xylist.SetItemText(1, 5, "1");
			s.Format("%f", CHIP[chip][i].CalParam2X);
			m_xylist.SetItemText(0, 6, ReformatString(s));
			s.Format("%f", CHIP[chip][i].CalParam2Y);
			m_xylist.SetItemText(1, 6, ReformatString(s));
		}
		else if(1 == CHIP[chip][i].Calway)
		{
			m_xylist.SetItemText(0, 4, "*");
			m_xylist.SetItemText(1, 4, "*");
			
			s.Format("%f", CHIP[chip][i].CalParam1X);
			m_xylist.SetItemText(0, 5, ReformatString(s));
			s.Format("%f", CHIP[chip][i].CalParam1Y);
			m_xylist.SetItemText(1, 5, ReformatString(s));
			m_xylist.SetItemText(0, 6, "0");
			m_xylist.SetItemText(1, 6, "0");
		}
		else
		{
			m_xylist.SetItemText(0, 4, "* +");
			m_xylist.SetItemText(1, 4, "* +");
			
			s.Format("%f", CHIP[chip][i].CalParam1X);
			m_xylist.SetItemText(0, 5, ReformatString(s));
			s.Format("%f", CHIP[chip][i].CalParam1Y);
			m_xylist.SetItemText(1, 5, ReformatString(s));
			
			s.Format("%f", CHIP[chip][i].CalParam2X);
			m_xylist.SetItemText(0, 6, ReformatString(s));
			s.Format("%f", CHIP[chip][i].CalParam2Y);
			m_xylist.SetItemText(1, 6, ReformatString(s));
		}		
	}
	else
	{
		s.Format("%f", CHIP[chip][i].Lower);
		m_chipList.SetItemText(testItemChip[chip], 5, ReformatString(s));
		s.Format("%f", CHIP[chip][i].Upper);
		m_chipList.SetItemText(testItemChip[chip], 6, ReformatString(s));
		
		s.Format("%f", CHIP[chip][i].stavalue1);
		m_calItemList.SetItemText(testItemChip[chip], 2, ReformatString(s));
		m_calItemList.SetItemText(testItemChip[chip], 8, "No");
		
		if(0 == CHIP[chip][i].Calway)
		{
			m_calItemList.SetItemText(testItemChip[chip], 5, "+");
			
			m_calItemList.SetItemText(testItemChip[chip], 6, "1");
			s.Format("%f", CHIP[chip][i].CalParam2);
			m_calItemList.SetItemText(testItemChip[chip], 7, ReformatString(s));
			
		}
		else if(1 == CHIP[chip][i].Calway)
		{
			m_calItemList.SetItemText(testItemChip[chip], 5, "*");
			
			s.Format("%f", CHIP[chip][i].CalParam1);
			m_calItemList.SetItemText(testItemChip[chip], 6, ReformatString(s));
			m_calItemList.SetItemText(testItemChip[chip], 7, "0");
		}
		else
		{
			m_calItemList.SetItemText(testItemChip[chip], 5, "* +");
			
			s.Format("%f", CHIP[chip][i].CalParam1);
			m_calItemList.SetItemText(testItemChip[chip], 6, ReformatString(s));
			s.Format("%f", CHIP[chip][i].CalParam2);
			m_calItemList.SetItemText(testItemChip[chip], 7, ReformatString(s));
		}		
	}
	
	if((str == "WL") || (str == "PWL") || (str == "DeltaWL") 
		|| (str == "PUR") || (str == "CCT") || (str == "CRI"))
	{
		m_chipList.SetItemText(testItemChip[chip], 2, "disable");
		m_chipList.SetItemText(testItemChip[chip], 3, "disable");
		m_chipList.SetItemText(testItemChip[chip], 4, "disable");
	}

	s.Format("%d", CHIP[chip][i].Fail);
	m_chipList.SetItemText(testItemChip[chip], 7, s);
	if(0 == CHIP[chip][i].Continue)
	{
		m_chipList.SetItemText(testItemChip[chip], 8, "False");
	}
	else
	{
		m_chipList.SetItemText(testItemChip[chip], 8, "True");
	}
		
	testItemChip[chip]++;
	return true;
}

bool CChip3Dlg::initdlg()
{
	CString str;

	m_xylist.InsertColumn(0, "", LVCFMT_CENTER, 20);
	m_xylist.InsertColumn(1, "标准值", LVCFMT_CENTER, 70);
	m_xylist.InsertColumn(2, "实际值", LVCFMT_CENTER, 70);
	m_xylist.InsertColumn(3, "校正后值", LVCFMT_CENTER, 80);
	m_xylist.InsertColumn(4, "方式", LVCFMT_CENTER, 65);
	m_xylist.InsertColumn(5, "校正参数*", LVCFMT_CENTER, 80);
	m_xylist.InsertColumn(6, "校正参数+", LVCFMT_CENTER, 80);
	m_xylist.InsertItem(0, "X");
	m_xylist.InsertItem(1, "Y");
	m_xylist.SetReadOnlyColumns(0);
	m_xylist.SetReadOnlyColumns(2);
	m_xylist.SetReadOnlyColumns(3);
	m_xylist.SetComboColumns(4);

	m_chipList.InsertColumn(0, "", LVCFMT_CENTER, 25);
	m_chipList.InsertColumn(1, "项目", LVCFMT_CENTER, 70);
	m_chipList.InsertColumn(2, "Delay(ms)", LVCFMT_CENTER, 80);
	m_chipList.InsertColumn(3, "V(V)", LVCFMT_CENTER, 70);
	m_chipList.InsertColumn(4, "I(mA)", LVCFMT_CENTER, 70);
	m_chipList.InsertColumn(5, "Min", LVCFMT_CENTER, 70);
	m_chipList.InsertColumn(6, "Max", LVCFMT_CENTER, 70);
	m_chipList.InsertColumn(7, "FailBin", LVCFMT_CENTER, 60);
	m_chipList.InsertColumn(8, "继续?", LVCFMT_CENTER, 60);
	m_chipList.SetReadOnlyColumns(0);
	m_chipList.SetReadOnlyColumns(1);
	m_chipList.SetComboColumns(8);

	m_calItemList.InsertColumn(0, "", LVCFMT_CENTER, 25);
	m_calItemList.InsertColumn(1, "项目", LVCFMT_CENTER, 70);
	m_calItemList.InsertColumn(2, "标准值", LVCFMT_CENTER, 70);
	m_calItemList.InsertColumn(3, "实际值", LVCFMT_CENTER, 70);
	m_calItemList.InsertColumn(4, "校正后值", LVCFMT_CENTER, 70);
	m_calItemList.InsertColumn(5, "方式", LVCFMT_CENTER, 50);
	m_calItemList.InsertColumn(6, "校正参数*", LVCFMT_CENTER, 80);
	m_calItemList.InsertColumn(7, "校正参数+", LVCFMT_CENTER, 80);
	m_calItemList.InsertColumn(8, "校正？", LVCFMT_CENTER, 60);
	m_calItemList.SetReadOnlyColumns(0);
	m_calItemList.SetReadOnlyColumns(1);
	m_calItemList.SetReadOnlyColumns(3);
	m_calItemList.SetReadOnlyColumns(4);
	m_calItemList.SetComboColumns(5);
	m_calItemList.SetComboColumns(8);

	if(engineer || Operator)
	{
		m_caltest.EnableWindow(true);
		m_getCal.EnableWindow(true);
		m_clearCal.EnableWindow(true);
	}

	str.Format("%f", PolParam[chip].Voltage);
	SetDlgItemText(IDC_POLV, ReformatString(str));
	str.Format("%f", PolParam[chip].Current);
	SetDlgItemText(IDC_POLI, ReformatString(str));
	str.Format("%d", PolParam[chip].Delay);
	SetDlgItemText(IDC_POLDelay, str);
	if(1 == DeadLed)
	{
		GetDlgItem(IDC_DLedBin)->EnableWindow(true);
		str.Format("%d", DeadLedBin[chip]);
		SetDlgItemText(IDC_DLedBin, str);
	}
	else
	{
		GetDlgItem(IDC_DLedBin)->EnableWindow(false);
	}


	m_cbWLSteptype3.SetCurSel(intWLSteps[chip]);
	m_cbOpticGain3.SetCurSel(intOpticGain[chip]);

	str.Format("%0.1f", intIntegrationTime[chip]);
	SetDlgItemText(IDC_IntegrationTime3, str);

	str.Format("%f", KeepLight[chip].Voltage);
	SetDlgItemText(IDC_KLV, ReformatString(str));
	str.Format("%f", KeepLight[chip].Current);
	SetDlgItemText(IDC_KLI, ReformatString(str));
	str.Format("%d", KeepLight[chip].Delay);
	SetDlgItemText(IDC_KLDelay, str);

	for(int i=0; i<c[chip]; i++)
	{
		setParameter(i);
	}

	if(1 == intMixLight)
	{
		SetMixLightParam(false);

		if(1 == intVfAverage)
		{
			SetVFaverage(false);
		}
	}
	return true;
}

void CChip3Dlg::initAuthorityItem()
{
	CString strItem, str;
	m_caltest.EnableWindow(true);
	m_getCal.EnableWindow(true);
	m_clearCal.EnableWindow(true);
/*	m_calItemList.InsertColumn(2, "标准值", LVCFMT_CENTER, 100);
	m_calItemList.InsertColumn(3, "实际值", LVCFMT_CENTER, 100);
	m_calItemList.InsertColumn(4, "校正后值", LVCFMT_CENTER, 100);
	m_calItemList.InsertColumn(5, "校正方式", LVCFMT_CENTER, 70);
	m_calItemList.InsertColumn(6, "校正参数*", LVCFMT_CENTER, 120);
	m_calItemList.InsertColumn(7, "校正参数+", LVCFMT_CENTER, 120);
	m_calItemList.SetReadOnlyColumns(3);
	m_calItemList.SetReadOnlyColumns(4);
	m_calItemList.SetComboColumns(5);*/

	for(int i=0; i<testItemChip[chip]; i++)
	{
		strItem = m_chipList.GetItemText(i, 1);

		for(int j=0; j<c[chip]; j++)
		{
			if(0 == strcmp(CHIP[chip][j].TestItem, strItem))
			{	
				if(strItem == "XYZ")
				{
					m_calItemList.SetItemText(i, 2, "disable");
					m_calItemList.SetItemText(i, 3, "disable");
					m_calItemList.SetItemText(i, 4, "disable");
					m_calItemList.SetItemText(i, 8, "No");
					
					str.Format("%f", CHIP[chip][i].stavalue1);
					m_xylist.SetItemText(0, 1, ReformatString(str));
					str.Format("%f", CHIP[chip][i].stavalue2);
					m_xylist.SetItemText(1, 1, ReformatString(str));
					
					if(0 == CHIP[chip][j].Calway)
					{
						m_xylist.SetItemText(0, 4, "+");
						m_xylist.SetItemText(1, 4, "+");
						
						m_xylist.SetItemText(0, 5, "1");
						m_xylist.SetItemText(1, 5, "1");
						
						str.Format("%f", CHIP[chip][i].CalParam2X);
						m_xylist.SetItemText(0, 6, ReformatString(str));	
						str.Format("%f", CHIP[chip][i].CalParam2Y);
						m_xylist.SetItemText(1, 6, ReformatString(str));
					}
					else if(1 == CHIP[chip][j].Calway)
					{
						m_xylist.SetItemText(0, 4, "*");
						m_xylist.SetItemText(1, 4, "*");
						
						str.Format("%f", CHIP[chip][i].CalParam1X);
						m_xylist.SetItemText(0, 5, ReformatString(str));
						str.Format("%f", CHIP[chip][i].CalParam1Y);
						m_xylist.SetItemText(1, 5, ReformatString(str));
						
						m_xylist.SetItemText(0, 6, "0");
						m_xylist.SetItemText(1, 6, "0");
					}
					else
					{
						m_xylist.SetItemText(0, 4, "* +");
						m_xylist.SetItemText(1, 4, "* +");
						
						str.Format("%f", CHIP[chip][i].CalParam1X);
						m_xylist.SetItemText(0, 5, ReformatString(str));
						str.Format("%f", CHIP[chip][i].CalParam1Y);
						m_xylist.SetItemText(1, 5, ReformatString(str));
						str.Format("%f", CHIP[chip][i].CalParam2X);
						m_xylist.SetItemText(0, 6, ReformatString(str));
						str.Format("%f", CHIP[chip][i].CalParam2Y);
						m_xylist.SetItemText(1, 6, ReformatString(str));
					}
				}
				else
				{
					str.Format("%f", CHIP[chip][i].stavalue1);
					m_calItemList.SetItemText(i, 2, ReformatString(str));
					m_calItemList.SetItemText(i, 8, "No");
					
					if(0 == CHIP[chip][j].Calway)
					{
						m_calItemList.SetItemText(i, 5, "+");

						m_calItemList.SetItemText(i, 6, "1");
						str.Format("%f", CHIP[chip][j].CalParam2);
						m_calItemList.SetItemText(i, 7, ReformatString(str));
					}
					else if(1 == CHIP[chip][j].Calway)
					{
						m_calItemList.SetItemText(i, 5, "*");

						str.Format("%f", CHIP[chip][j].CalParam1);
						m_calItemList.SetItemText(i, 6, ReformatString(str));
						m_calItemList.SetItemText(i, 7, "0");
					}
					else
					{
						m_calItemList.SetItemText(i, 5, "* +");

						str.Format("%f", CHIP[chip][j].CalParam1);
						m_calItemList.SetItemText(i, 6, ReformatString(str));
						str.Format("%f", CHIP[chip][j].CalParam2);
						m_calItemList.SetItemText(i, 7, ReformatString(str));
					}					
				}
			}
		}
	}
}

void CChip3Dlg::hideAuthorityItem()
{
	m_caltest.EnableWindow(false);
	m_getCal.EnableWindow(false);
	m_clearCal.EnableWindow(false);
/*	m_chipList.DeleteColumn(15);
	m_chipList.DeleteColumn(14);
	m_chipList.DeleteColumn(13);
	m_chipList.DeleteColumn(12);
	m_chipList.DeleteColumn(11);
	m_chipList.DeleteColumn(10);
	m_chipList.DeleteColumn(9);*/

	for(int i=1; i<7; i++)
	{
		m_xylist.SetItemText(0, i, "");
		m_xylist.SetItemText(1, i, "");
	}
}

int CChip3Dlg::searchItem(CString str)
{
	CString str_item, str_item2;
	int itemnum = 1;
	int count = m_chipList.GetItemCount();

	for(int i=0; i<count; i++)
	{
		str_item = m_chipList.GetItemText(i, 1);
		sscanf(str_item, "%[^(]", str_item2);
		if(str_item2 == str)
		{
			itemnum++;
		}
	}

	return itemnum;
}

void CChip3Dlg::HandleCheck(CString str, CButton *m_check)
{
	CString s, str_item, str_item2;
	int existnum = 0;
	int i;

	if(1 == m_check->GetCheck())
	{	
		existnum = searchItem(str);

		m_check->SetCheck(0);
		s.Format("%d", testItemChip[chip]+1);
		m_chipList.InsertItem(testItemChip[chip], s);

		if(existnum > 1)
		{
			str_item.Format("%s(%d)", str, existnum);
			m_chipList.SetItemText(testItemChip[chip], 1, str_item);
			str_item2.Format("C%d-%s", chip+1, str_item);
		}
		else
		{
			m_chipList.SetItemText(testItemChip[chip], 1, str);
			str_item2.Format("C%d-%s", chip+1, str);
		}

		m_chipList.SetItemText(testItemChip[chip], 2, "0");
		m_chipList.SetItemText(testItemChip[chip], 3, "5");
		m_chipList.SetItemText(testItemChip[chip], 4, "20");	
		m_chipList.SetItemText(testItemChip[chip], 5, "0");
		m_chipList.SetItemText(testItemChip[chip], 6, "10000");	
		m_chipList.SetItemText(testItemChip[chip], 7, "1");
		m_chipList.SetItemText(testItemChip[chip], 8, "False");

		if(str != "XYZ")
		{
			m_calItemList.InsertItem(testItemChip[chip], s);
				
			if(existnum > 1)
			{
				m_calItemList.SetItemText(testItemChip[chip], 1, str_item);
			}
			else
			{
				m_calItemList.SetItemText(testItemChip[chip], 1, str);
			}
			
			if((str == "IV") || (str == "IE") || (str == "LE") || (str == "LV"))
			{
				m_calItemList.SetItemText(testItemChip[chip], 5, "*");
			}
			else
			{
				m_calItemList.SetItemText(testItemChip[chip], 5, "+");
			}

			m_calItemList.SetItemText(testItemChip[chip], 6, "1");
			m_calItemList.SetItemText(testItemChip[chip], 7, "0");
			m_calItemList.SetItemText(testItemChip[chip], 8, "No");
		}

		if((str == "IR") || (str == "VR"))
		{
			m_chipList.SetItemText(testItemChip[chip], 4, "0.1");
		}	
		else if((str == "WL") || (str == "PWL") || (str == "DeltaWL") 
			|| (str == "PUR") || (str == "CCT") || (str == "CRI"))
		{
			m_chipList.SetItemText(testItemChip[chip], 2, "disable");
			m_chipList.SetItemText(testItemChip[chip], 3, "disable");
			m_chipList.SetItemText(testItemChip[chip], 4, "disable");
		}
		else if(str == "XYZ")
		{
			m_chipList.SetItemText(testItemChip[chip], 2, "disable");
			m_chipList.SetItemText(testItemChip[chip], 3, "disable");
			m_chipList.SetItemText(testItemChip[chip], 4, "disable");
			m_chipList.SetItemText(testItemChip[chip], 5, "disable");
			m_chipList.SetItemText(testItemChip[chip], 6, "disable");
			
			m_calItemList.InsertItem(testItemChip[chip], s);
			m_calItemList.SetItemText(testItemChip[chip], 1, str);
			m_calItemList.SetItemText(testItemChip[chip], 2, "disable");
			m_calItemList.SetItemText(testItemChip[chip], 3, "disable");
			m_calItemList.SetItemText(testItemChip[chip], 4, "disable");
			m_calItemList.SetItemText(testItemChip[chip], 8, "No");
			
			m_xylist.SetItemText(0, 1, "0");
			m_xylist.SetItemText(0, 4, "+");
			m_xylist.SetItemText(0, 5, "1");
			m_xylist.SetItemText(0, 6, "0");
			
			m_xylist.SetItemText(1, 1, "0");
			m_xylist.SetItemText(1, 4, "+");
			m_xylist.SetItemText(1, 5, "1");
			m_xylist.SetItemText(1, 6, "0");	
		}
		testItemChip[chip]++;
	}
	else
	{
		for(i=0; i<(testItemChip[chip]+1); i++)
		{
			s = m_chipList.GetItemText(i, 1);
			if(s == str)
			{
				m_chipList.DeleteItem(i);
				m_calItemList.DeleteItem(i);

				if(i != testItemChip[chip])
				{
					for(int j=i; j<testItemChip[chip]; j++)
					{
						s.Format("%d", j+1);
						m_chipList.SetItemText(j, 0, s);
						m_calItemList.SetItemText(j, 0, s);
					}
				}
				testItemChip[chip]--;
				i = testItemChip[chip] + 1;
				
				if(str == "XYZ")
				{
					for(int i=1; i<7; i++)
					{
						m_xylist.SetItemText(0, i, "");
						m_xylist.SetItemText(1, i, "");
					}
				}
			}
		}
	}
}

void CChip3Dlg::OnAddItem() 
{
	// TODO: Add your control notification handler code here
	CButton *m_check[18] = {&m_tIF, &m_tIR, &m_tVF, &m_tVR, &m_tVZ, 
		                    &m_tDVF, &m_tTHY, &m_tIV, &m_tIE, &m_tLE, &m_tLV,
                    &m_tXYZ, &m_tWL, &m_tPWL, &m_tDeltaWL, &m_tPUR, &m_tCCT, &m_tCRI};

	CString str[18] = {"IF", "IR", "VF", "VR", "VZ", "DVF", "THY", "IV", "IE", "LE", "LV",
	                	"XYZ", "WL", "PWL", "DeltaWL", "PUR","CCT", "CRI"};
	for(int i=0; i<18; i++)
	{
		if(1 == m_check[i]->GetCheck())
		{
			HandleCheck(str[i], m_check[i]);
			m_check[i]->SetCheck(0);
		}
	}

	updateItemforlevel();
}

void CChip3Dlg::OndelItem() 
{
	// TODO: Add your control notification handler code here
	CString str, str2;
	int num = 0;

	POSITION pos=m_chipList.GetFirstSelectedItemPosition();
	if(pos==NULL)
	{
		MessageBox("请选择要删除行!");
		return;
	}

	num = (int)m_chipList.GetNextSelectedItem(pos);

	str = m_chipList.GetItemText(num, 1);
	HandleCheck(str, &m_tIF);

	CString str_item, str_item2, str_change;
	int itemnum = 1, itemnum2 = 1;
	int count = m_chipList.GetItemCount();

	str_item = "NULL";
	sscanf(str, "%[^(](%d", str_item, &itemnum);
	for(int i=num; i<count; i++)
	{
		str2 = "NULL";
		str_item2 = "NULL";
		str2 = m_chipList.GetItemText(i, 1);
		sscanf(str2, "%[^(](%d", str_item2, &itemnum2);
		if((str_item == str_item2) && (itemnum < itemnum2))
		{
			str_change = "NULL";
			if(itemnum2 < 3)
			{
				str_change.Format("%s", str_item2);
			}
			else
			{
				str_change.Format("%s(%d)", str_item2, itemnum2-1);
			}
			
			m_chipList.SetItemText(i, 1, str_change);
			m_calItemList.SetItemText(i, 1, str_change);
		}
	}

	updateItemforlevel();
}

bool CChip3Dlg::updateItemforlevel()
{
	CString str, str_item;

	tempItemforlevel[chip].RemoveAll();
	int itemnum = m_chipList.GetItemCount();

	for(int i=0; i<itemnum; i++)
	{
		str = m_chipList.GetItemText(i, 1);
		str_item.Format("C%d-%s", chip+1, str);
		tempItemforlevel[chip].AddTail(str_item);
	}

	return true;
}
/*
void CChip3Dlg::OnTestIF() 
{
	// TODO: Add your control notification handler code here
	HandleCheck("IF", &m_tIF);
}

void CChip3Dlg::OnTestIR() 
{
	// TODO: Add your control notification handler code here
	HandleCheck("IR", &m_tIR);
}

void CChip3Dlg::OnTestVF() 
{
	// TODO: Add your control notification handler code here
	HandleCheck("VF", &m_tVF);
}

void CChip3Dlg::OnTestVR() 
{
	// TODO: Add your control notification handler code here
	HandleCheck("VR", &m_tVR);
}

void CChip3Dlg::OnTestDVF() 
{
	// TODO: Add your control notification handler code here
	HandleCheck("DVF", &m_tDVF);
}

void CChip3Dlg::OnTestTHY() 
{
	// TODO: Add your control notification handler code here
	HandleCheck("THY", &m_tTHY);
}

void CChip3Dlg::OnTestIV() 
{
	// TODO: Add your control notification handler code here
	HandleCheck("IV", &m_tIV);
}

void CChip3Dlg::OnTestXYZ() 
{
	// TODO: Add your control notification handler code here
	HandleCheck("XYZ", &m_tXYZ);
	if(1 == m_tXYZ.GetCheck())
	{
		m_shootset3.EnableWindow(true);
	}
	else
	{
		m_shootset3.EnableWindow(false);
	}
}

void CChip3Dlg::OnTestWL() 
{
	// TODO: Add your control notification handler code here
	HandleCheck("WL", &m_tWL);
}

void CChip3Dlg::OnTestPWL() 
{
	// TODO: Add your control notification handler code here
	HandleCheck("PWL", &m_tPWL);
}

void CChip3Dlg::OnTestDeltaWL() 
{
	// TODO: Add your control notification handler code here
	HandleCheck("DeltaWL", &m_tDeltaWL);
}

void CChip3Dlg::OnTestPUR() 
{
	// TODO: Add your control notification handler code here
	HandleCheck("PUR", &m_tPUR);
}

void CChip3Dlg::OnTestCCT() 
{
	// TODO: Add your control notification handler code here
	HandleCheck("CCT", &m_tCCT);
}

void CChip3Dlg::OnTestCRI() 
{
	// TODO: Add your control notification handler code here
	HandleCheck("CRI", &m_tCRI);
}
*/
void CChip3Dlg::SetMixLightParam(bool enable)
{
	int i = 0;
	CButton *m_check[2] = {&m_tIV, &m_tXYZ};
	if(!enable)
	{	
		CString str[2] = {"IV", "XYZ"};
		
		for(i=0; i<2; i++)
		{
			if(1 == m_check[i]->GetCheck())
			{
				m_check[i]->SetCheck(0);
				HandleCheck(str[i], m_check[i]);
			}
		}
	}
	
	for(i=0; i<2; i++)
	{
		m_check[i]->EnableWindow(enable);
	}
}

void CChip3Dlg::SetVFaverage(bool enable)
{
	int i = 0;
	CButton *m_check = &m_tVF;
	CString str = "VF";
	if(!enable)
	{		
		if(1 == m_check->GetCheck())
		{
			m_check->SetCheck(0);
			HandleCheck(str, m_check);
		}
	}
	
	m_check->EnableWindow(enable);
}

bool CChip3Dlg::getParameter()
{
	c[chip] = testItemChip[chip];
	CString str, testItem, testItem2;
	CString Items[18] = {"IR", "VR", "VZ", "VF", "IF", "IV", "IE", "LE", "LV",
		"XYZ", "WL", "PWL", "DeltaWL", "PUR", "CCT", "CRI", "DVF", "THY"};
	int i = 0;
	int j, itemsnum;
	bool optictest = false;
	bool XYZtest = false;
	polfalsenum[chip] = 0;

	GetDlgItemText(IDC_POLV, str);
    PolParam[chip].Voltage = atof(str);
	GetDlgItemText(IDC_POLI, str);
    PolParam[chip].Current = atof(str);
	GetDlgItemText(IDC_POLDelay, str);
    PolParam[chip].Delay = atoi(str);
	GetDlgItemText(IDC_DLedBin, str);
	DeadLedBin[chip] = atoi(str);

	GetDlgItemText(IDC_KLV, str);
    KeepLight[chip].Voltage = atof(str);
	GetDlgItemText(IDC_KLI, str);
    KeepLight[chip].Current = atof(str);
	GetDlgItemText(IDC_KLDelay, str);
    KeepLight[chip].Delay = atoi(str);

	for(itemsnum=0; itemsnum<18; itemsnum++)
	{
		for(j=0; j<c[chip]; j++)
		{
			testItem = m_chipList.GetItemText(j, 1);
			testItem2 = "NULL";
			sscanf(testItem, "%[^(]", testItem2);
			if(0 == strcmp(testItem2, Items[itemsnum]))
			{
				strcpy(CHIP[chip][i].TestItem, testItem);
				CHIP[chip][i].Delay = atoi(m_chipList.GetItemText(j, 2)); 
				CHIP[chip][i].VCom = atof(m_chipList.GetItemText(j, 3)); 
				CHIP[chip][i].ICom = atof(m_chipList.GetItemText(j, 4)); 

				if((0 == itemsnum) || (1 == itemsnum) || (2 == itemsnum))
				{
					polfalsenum[chip] ++;
				}
			
				if(itemsnum > 5 && itemsnum < 16)
				{
					optictest = true;	
					CHIP[chip][i].VCom = KeepLight[chip].Voltage; 
					CHIP[chip][i].ICom = KeepLight[chip].Current;
					CHIP[chip][i].Delay = KeepLight[chip].Delay; 
				}
			
				if(9 == itemsnum)
				{
					CHIP[chip][i].Lower = 0; 
					CHIP[chip][i].Upper = 0;
					XYZtest = true;
					
					if(engineer || Operator)
					{
						if(m_xylist.GetItemText(0, 4) == "+")
						{
							CHIP[chip][i].Calway = 0;
							
							CHIP[chip][i].CalParam2X = atof(m_xylist.GetItemText(0, 6));
							CHIP[chip][i].CalParam2Y = atof(m_xylist.GetItemText(1, 6));
						}
						else if(m_xylist.GetItemText(0, 4) == "*")
						{
							CHIP[chip][i].Calway = 1;
							
							CHIP[chip][i].CalParam1X = atof(m_xylist.GetItemText(0, 5));				
							CHIP[chip][i].CalParam1Y = atof(m_xylist.GetItemText(1, 5));
						}
						else
						{
							CHIP[chip][i].Calway = 2;
											
							CHIP[chip][i].CalParam1X = atof(m_xylist.GetItemText(0, 5));				
							CHIP[chip][i].CalParam1Y = atof(m_xylist.GetItemText(1, 5));
							CHIP[chip][i].CalParam2X = atof(m_xylist.GetItemText(0, 6));
							CHIP[chip][i].CalParam2Y = atof(m_xylist.GetItemText(1, 6));
						}
						CHIP[chip][i].stavalue1 = atof(m_xylist.GetItemText(0, 1));
						CHIP[chip][i].stavalue2 = atof(m_xylist.GetItemText(1, 1));
					}
				}
				else
				{
					CHIP[chip][i].Lower = atof(m_chipList.GetItemText(j, 5)); 
					CHIP[chip][i].Upper = atof(m_chipList.GetItemText(j, 6));
				
					if(engineer || Operator)
					{
						CHIP[chip][i].stavalue1 = atof(m_calItemList.GetItemText(j, 2));

						if(m_calItemList.GetItemText(j, 5) == "+")						
						{
							CHIP[chip][i].Calway = 0;
							CHIP[chip][i].CalParam2 = atof(m_calItemList.GetItemText(j, 7));
						}
						else if(m_calItemList.GetItemText(j, 5) == "*")
						{
							CHIP[chip][i].Calway = 1;
							CHIP[chip][i].CalParam1 = atof(m_calItemList.GetItemText(j, 6));
						}
						else
						{
							CHIP[chip][i].Calway = 2;
							
							CHIP[chip][i].CalParam1 = atof(m_calItemList.GetItemText(j, 6));
							CHIP[chip][i].CalParam2 = atof(m_calItemList.GetItemText(j, 7));
						}
					}
				}
				
				CHIP[chip][i].Fail = atoi(m_chipList.GetItemText(j, 7)); 
				if(m_chipList.GetItemText(j, 8) == "True")
				{
					CHIP[chip][i].Continue = 1;
				}
				else
				{
					CHIP[chip][i].Continue = 0;
				}
			
				i++;
			}
		}
	}

	intWLSteps[chip] = m_cbWLSteptype3.GetCurSel();
    intOpticGain[chip] = m_cbOpticGain3.GetCurSel(); 

	GetDlgItemText(IDC_IntegrationTime3, str);
    intIntegrationTime[chip] = atof(str);

	usespectrum[chip] = optictest;
	testXYZ[chip] = XYZtest;

	return true;
}

bool CChip3Dlg::getParameterbyhand()
{
	c[chip] = testItemChip[chip];
	CString str, testItem, testItem2;
	CString Items[18] = {"IR", "VR", "VZ", "VF", "IF", "IV", "IE", "LE", "LV",
		"XYZ", "WL", "PWL", "DeltaWL", "PUR", "CCT", "CRI", "DVF", "THY"};
	int i = 0;
	int j, itemsnum;
	bool optictest = false;
	bool XYZtest = false;
	polfalsenum[chip] = 0;

	GetDlgItemText(IDC_POLV, str);
    PolParam[chip].Voltage = atof(str);
	GetDlgItemText(IDC_POLI, str);
    PolParam[chip].Current = atof(str);
	GetDlgItemText(IDC_POLDelay, str);
    PolParam[chip].Delay = atoi(str);
	GetDlgItemText(IDC_DLedBin, str);
	DeadLedBin[chip] = atoi(str);

	GetDlgItemText(IDC_KLV, str);
    KeepLight[chip].Voltage = atof(str);
	GetDlgItemText(IDC_KLI, str);
    KeepLight[chip].Current = atof(str);
	GetDlgItemText(IDC_KLDelay, str);
    KeepLight[chip].Delay = atoi(str);
	
	for(j=0; j<c[chip]; j++)
	{
		for(itemsnum=0; itemsnum<18; itemsnum++)
		{
			testItem = m_chipList.GetItemText(j, 1);
			testItem2 = "NULL";
			sscanf(testItem, "%[^(]", testItem2);
			if(0 == strcmp(testItem2, Items[itemsnum]))
			{
				strcpy(CHIP[chip][i].TestItem, testItem);
				CHIP[chip][i].Delay = atoi(m_chipList.GetItemText(j, 2)); 
				CHIP[chip][i].VCom = atof(m_chipList.GetItemText(j, 3)); 
				CHIP[chip][i].ICom = atof(m_chipList.GetItemText(j, 4)); 
				
				if((0 == itemsnum) || (1 == itemsnum) || (2 == itemsnum))
				{
					polfalsenum[chip] ++;
				}
				
				if(itemsnum > 5 && itemsnum < 16)
				{
					optictest = true;	
					CHIP[chip][i].VCom = KeepLight[chip].Voltage; 
					CHIP[chip][i].ICom = KeepLight[chip].Current;
					CHIP[chip][i].Delay = KeepLight[chip].Delay; 
				}
				
				if(9 == itemsnum)
				{
					CHIP[chip][i].Lower = 0; 
					CHIP[chip][i].Upper = 0;
					XYZtest = true;
					
					if(engineer || Operator)
					{
						if(m_xylist.GetItemText(0, 4) == "+")
						{
							CHIP[chip][i].Calway = 0;		
							CHIP[chip][i].CalParam2X = atof(m_xylist.GetItemText(0, 6));
							CHIP[chip][i].CalParam2Y = atof(m_xylist.GetItemText(1, 6));
						}
						else if(m_xylist.GetItemText(0,4) == "*")
						{
							CHIP[chip][i].Calway = 1;	
							CHIP[chip][i].CalParam1X = atof(m_xylist.GetItemText(0, 5));
							CHIP[chip][i].CalParam1Y = atof(m_xylist.GetItemText(1, 5));
						}
						else
						{
							CHIP[chip][i].Calway = 2;	
							CHIP[chip][i].CalParam1X = atof(m_xylist.GetItemText(0, 5));
							CHIP[chip][i].CalParam1Y = atof(m_xylist.GetItemText(1, 5));
							CHIP[chip][i].CalParam2X = atof(m_xylist.GetItemText(0, 6));
							CHIP[chip][i].CalParam2Y = atof(m_xylist.GetItemText(1, 6));	
						}
						
						CHIP[chip][i].stavalue1 = atof(m_xylist.GetItemText(0, 1));
						CHIP[chip][i].stavalue2 = atof(m_xylist.GetItemText(1, 1));
					}
				}
				else
				{
					CHIP[chip][i].Lower = atof(m_chipList.GetItemText(j, 5)); 
					CHIP[chip][i].Upper = atof(m_chipList.GetItemText(j, 6));
					
					if(engineer || Operator)
					{
						CHIP[chip][i].stavalue1 = atof(m_calItemList.GetItemText(j, 2));

						if(m_calItemList.GetItemText(j, 5) == "+")						
						{
							CHIP[chip][i].Calway = 0;
							CHIP[chip][i].CalParam2 = atof(m_calItemList.GetItemText(j, 7));
						}
						else if(m_calItemList.GetItemText(j, 5) == "*")
						{
							CHIP[chip][i].Calway = 1;
							CHIP[chip][i].CalParam1 = atof(m_calItemList.GetItemText(j, 6));
						}
						else
						{
							CHIP[chip][i].Calway = 2;
							
							CHIP[chip][i].CalParam1 = atof(m_calItemList.GetItemText(j, 6));
							CHIP[chip][i].CalParam2 = atof(m_calItemList.GetItemText(j, 7));
						}
					}
				}
				
				CHIP[chip][i].Fail = atoi(m_chipList.GetItemText(j, 7)); 
				if(m_chipList.GetItemText(j, 8) == "True")
				{
					CHIP[chip][i].Continue = 1;
				}
				else
				{
					CHIP[chip][i].Continue = 0;
				}
				
				i++;
			}
		}
	}
	
	intWLSteps[chip] = m_cbWLSteptype3.GetCurSel();
    intOpticGain[chip] = m_cbOpticGain3.GetCurSel(); 
	
	GetDlgItemText(IDC_IntegrationTime3, str);
    intIntegrationTime[chip] = atof(str);
	
	usespectrum[chip] = optictest;
	testXYZ[chip] = XYZtest;
	
	return true;
}

void CChip3Dlg::Onshootset3() 
{
	// TODO: Add your control notification handler code here
	extern int shootchip;
	shootchip = 2;
	CShootDiagram m_shootdiagram;
	m_shootdiagram.DoModal();
	m_shootdiagram.m_shootchip = 2;
}

void CChip3Dlg::OnAutoSetInteTime3() 
{
	// TODO: Add your control notification handler code here
	CString str;
	double maxpower = 0;
	double time = 0; 
	double max = 100, min = 1;
	gettime = min;
	lastpower = 0;

	if(1)
	{
		recommended = 20000;
	}
	else
	{
		recommended = 1500;
	}

	double VCom = 0, ICom = 0;
	int delay = 0;
	int boxcar = 0; 
	int average = 0;
//	CSetParameter *setparam = (CSetParameter*)GetParent();

	GetDlgItemText(IDC_KLV, str);
	VCom = atof(str);
	GetDlgItemText(IDC_KLI, str);
	ICom = atof(str);
	GetDlgItemText(IDC_KLDelay, str);
	delay = atoi(str);

/*	setparam->GetDlgItemText(IDC_ScanTimes, str);
	average = atoi(str);
	setparam->GetDlgItemText(IDC_Boxcar, str);
	boxcar = atoi(str);*/

	average = calsta_average;
	boxcar = calsta_boxcar;

	OpenLightSet(tempchiptype, chip);
	OpenLight(VCom, ICom);
	Delay(delay * 1000);

	SetDlgItemText(IDC_AutoSetInteTime3, "正在获取");
	
	maxpower = autoGetMaxpower(chip, average, boxcar, min);
	SetDlgItemText(IDC_AutoSetInteTime3, "正在获取 .");
	if(maxpower > (recommended * 1.1))
	{
		MessageBox("光子太强, 无法获得积分时间!");
		SetDlgItemText(IDC_AutoSetInteTime3, "自动调整积分时间");
		m_autosetTime.EnableWindow(true);
		CloseLight(1, 0);
		return;
	}

	maxpower = autoGetMaxpower(chip, average, boxcar, max);
	SetDlgItemText(IDC_AutoSetInteTime3, "正在获取 . .");
	if(maxpower < (recommended * 0.9))
	{
		MessageBox("光子太弱, 无法获得积分时间!");
		SetDlgItemText(IDC_AutoSetInteTime3, "自动调整积分时间");
		m_autosetTime.EnableWindow(true);
		CloseLight(1, 0);
		return;
	}
	
	time = getTime(chip, average, boxcar, max, min);
	str.Format("%0.1f", time);
	SetDlgItemText(IDC_IntegrationTime3, str);
	SetDlgItemText(IDC_AutoSetInteTime3, "自动调整积分时间");

	autoGetMaxpower(chip, average, boxcar, time);
	
	CloseLight(1, 0);

	updateRect = true;
	Delay(1000);
	updateRect = false;
	
	SetDlgItemText(IDC_AutoSetInteTime3, "自动调整积分时间");
	m_autosetTime.EnableWindow(true);
}

void CChip3Dlg::OnClearDark3() 
{
	// TODO: Add your control notification handler code here
	InitCalDarkParam(chip);
}

void CChip3Dlg::OnAddDark3() 
{
	// TODO: Add your control notification handler code here
	int time = 0; 
	CString str;
	GetDlgItemText(IDC_IntegrationTime3, str);
    time = atoi(str);
	setCalDarkParam(chip, time);
}

void CChip3Dlg::OnCalibrationTest3() 
{
	// TODO: Add your control notification handler code here
//	DoubleArray sa;
//	OOI_PARAM ooip;
	double *spectrum;
//	double spectrumpc[PIXELNUM];
//	CSetParameter *setparam = (CSetParameter*)GetParent();

	CString str, str_item;
	char testItem[20];
	int delay = 0;
	double VCom = 0, ICom = 0;
	double TestValue = 0, TestValueAft = 0;
	double calparam1 = 1, calparam2 = 0, calparam3 = 1, calparam4 = 0;
	long opticgain = 0;
	double InteTime = 1;
	int wlSteps = 0;
	double x = 0, y = 0;
	int boxcar = 0; 
	int average = 0;

	bool outOfRange = false;

	COLOR_PARA dColorPara;
	ORI_PARA dOriPara;

	average = calsta_average;
	boxcar = calsta_boxcar;

	if(testItemChip[chip] > 0)
	{
		OpenLightSet(tempchiptype, chip);
	}
	for(int i=0; i<testItemChip[chip]; i++)
	{
		str_item = m_chipList.GetItemText(i, 1);
		sscanf(str_item, "%[^(]", testItem);
		delay = atoi(m_chipList.GetItemText(i, 2)); 
		VCom = atof(m_chipList.GetItemText(i, 3)); 
		ICom = atof(m_chipList.GetItemText(i, 4)); 

		if(0 == strcmp(testItem, "IF"))
		{
			TestValue = getIF(VCom, ICom, delay);
		}
		else if(0 == strcmp(testItem, "IR"))
		{
			TestValue = 1000 * fabs(getIR(VCom, ICom, delay));
		}
		else if(0 == strcmp(testItem, "VF"))
		{
			TestValue = getVF(VCom, ICom, delay);
			if(!getBering())
			{
				TestValue += systemset.VRoffset[2];
			}
		}
		else if(0 == strcmp(testItem, "VR"))
		{
			TestValue = getVR(VCom, ICom, delay);
		}
		else if(0 == strcmp(testItem, "DVF"))
		{
			TestValue = getDVF(ICom, delay);
		}
		else if(0 == strcmp(testItem, "THY"))
		{
			TestValue = getTHY(VCom, ICom);
		}
		else if(0 == strcmp(testItem, "IV"))
		{
			opticgain = m_cbOpticGain3.GetCurSel(); 
			TestValue = getYbit(false, opticgain, VCom, ICom, delay, true);
			
			if(TestValue >= 31000)
			{
				outOfRange = true;
			}
		}
		else
		{
			GetDlgItemText(IDC_KLV, str);
			VCom = atof(str);
			GetDlgItemText(IDC_KLI, str);
			ICom = atof(str);
			GetDlgItemText(IDC_KLDelay, str);
			delay = atoi(str);

			GetDlgItemText(IDC_IntegrationTime3, str);
			InteTime = atof(str);
			
			OpenLight(VCom, ICom);
			Delay(delay * 1000);
			if(1)
			{
				JK_Emission_GetData_3LED(chip, (float)InteTime, average, 3, dColorPara,dOriPara);
				int j;
				double dDecAD[2048];
				for (j = 0; j < dOriPara.iPixN; j++)
				{
					dDecAD[j] = dOriPara.fDecPL[j];
				}
				spectrum = &dDecAD[0];
				for (j = 0; j < 128; j++)
				{
					setting_wl[j] = (int)(0.26 * dOriPara.fDecWL[j*16] - 39);
				}
				for(j = 0; j < PIXELNUM; j++)
				{
					setting_spectrum[j] = dOriPara.fDecAD[j];//fDecAD[i];
				}
				setsngCounts(spectrum, sngCurrentDark[chip]);	
			}
			CloseLight(1, 0);

			//getXY();
			x = dColorPara.fx;//getX();
			y = dColorPara.fy;//getY();
			
			if(0 == strcmp(testItem, "WL"))
			{
				wlSteps = m_cbWLSteptype3.GetCurSel();
				
				if(0 == wlSteps)
				{
					TestValue = getWL_New(x, y);
				}	
				else
				{
					TestValue = getWL_5nm_New(x, y);
				}
			}
			else if(0 == strcmp(testItem, "PWL"))
			{
				TestValue = dColorPara.fLp;//getPeakWL(1, false);
			}
			else if(0 == strcmp(testItem, "DeltaWL"))
			{
				TestValue = dColorPara.fLd;//getDeltaWL();
			}
			else if(0 == strcmp(testItem, "PUR"))
			{
				TestValue = dColorPara.fPur;//getPUR(x, y);
			}
			else if(0 == strcmp(testItem, "CCT"))
			{
				TestValue = dColorPara.fCCT;//getCCT(x, y);
			}
			else if(0 == strcmp(testItem, "CRI"))
			{
				TestValue = dColorPara.fRa;//getCRI(x, y);
			}
			else if(0 == strcmp(testItem, "IE"))
			{
				TestValue = getOptics_IV(0, intIntegrationTime[chip]);
			}	
			else if(0 == strcmp(testItem, "LE"))
			{
				TestValue = getOptics_IV(2, intIntegrationTime[chip]);
			}
			else if(0 == strcmp(testItem, "LV"))
			{
				TestValue = getOptics_IV(1, intIntegrationTime[chip]);
			}
		}

		if(m_calItemList.GetItemText(i, 5) == "+")
		{
			calparam2 = atof(m_calItemList.GetItemText(i, 7));
			TestValueAft = TestValue + calparam2;	
		}
		else if(m_chipList.GetItemText(i, 5) == "*")
		{
			calparam1 = atof(m_calItemList.GetItemText(i, 6));
			TestValueAft = TestValue * calparam1;
		}
		else
		{
			calparam1 = atof(m_calItemList.GetItemText(i, 6));
			calparam2 = atof(m_calItemList.GetItemText(i, 7));
			TestValueAft = TestValue * calparam1 + calparam2;
		}
		
		TestValue = fabs(TestValue);
		str.Format("%0.3f", TestValue);
		m_calItemList.SetItemText(i, 3, ReformatString(str));
		str.Format("%0.3f", TestValueAft);
		m_calItemList.SetItemText(i, 4, ReformatString(str));
		
		if(0 == strcmp(testItem, "XYZ"))
		{
			//getXY();
			x = dColorPara.fx;//getX();
			y = dColorPara.fy;//getY();

			double xafter = 0, yafter = 0;
			if(m_xylist.GetItemText(0, 4) == "+")
			{
				calparam2 = atof(m_xylist.GetItemText(0, 6));
				calparam4 = atof(m_xylist.GetItemText(1, 6));
				
				xafter = x + calparam2;
				yafter = y + calparam4;
			}
			else if(m_xylist.GetItemText(0, 4) == "*")
			{
				calparam1 = atof(m_xylist.GetItemText(0, 5));
				calparam3 = atof(m_xylist.GetItemText(1, 5));
				
				xafter = x * calparam1;
				yafter = y * calparam3;
				
				
			}
			else
			{
				calparam1 = atof(m_xylist.GetItemText(0, 5));
				calparam3 = atof(m_xylist.GetItemText(1, 5));
				calparam2 = atof(m_xylist.GetItemText(0, 6));
				calparam4 = atof(m_xylist.GetItemText(1, 6));
				
				xafter = x * calparam1 + calparam2;
				yafter = y * calparam3 + calparam4;
			}
			
			m_calItemList.SetItemText(i, 2, "disable");
			m_calItemList.SetItemText(i, 3, "disable");
			m_calItemList.SetItemText(i, 4, "disable");
			
			str.Format("%0.4f", x);
			m_xylist.SetItemText(0, 2, ReformatString(str));
			str.Format("%0.4f", y);
			m_xylist.SetItemText(1, 2, ReformatString(str));
			str.Format("%0.4f", xafter);
			m_xylist.SetItemText(0, 3, ReformatString(str));
			str.Format("%0.4f", yafter);
			m_xylist.SetItemText(1, 3, ReformatString(str));
		}
	}
	

	updateRect = true;
	Delay(1000);
	updateRect = false;

	if(outOfRange)
	{
		MessageBox("亮度饱和，请选择适当的光强增益!");
	}
}


void CChip3Dlg::OnClearCalibration() 
{
	// TODO: Add your control notification handler code here
	CString testItem, str_item;

	for(int i=0; i<testItemChip[chip]; i++)
	{	
		str_item = m_chipList.GetItemText(i, 1);
		sscanf(str_item, "%[^(]", testItem);
		if(0 == strcmp(testItem, "XYZ"))
		{
			m_xylist.SetItemText(0, 5, "1");
			m_xylist.SetItemText(0, 6, "0");

			m_xylist.SetItemText(1, 5, "1");
			m_xylist.SetItemText(1, 6, "0");
		}
		else
		{
			m_calItemList.SetItemText(i, 6, "1");
			m_calItemList.SetItemText(i, 7, "0");
		}
	}
}

void CChip3Dlg::OnGetCalibration() 
{
	// TODO: Add your control notification handler code here
//	DoubleArray sa;
//	OOI_PARAM ooip;
	double *spectrum;
//	double spectrumpc[PIXELNUM];
//	CSetParameter *setparam = (CSetParameter*)GetParent();

	CString str, calibrate, str_item;
	char testItem[20];
	int delay = 0;
	double VCom = 0, ICom = 0;
	double staValue = 0, staValue2 = 0;
	double TestValue = 0, TestValueAft = 0;
	double calparam1 = 1, calparam2 = 0, calparam3 = 1, calparam4 = 0;
	long opticgain = 0;
	double InteTime = 1;
	int wlSteps = 0;
	double x = 0, y = 0;
	int boxcar = 0; 
	int average = 0;

	bool outOfRange = false;

/*	setparam->GetDlgItemText(IDC_ScanTimes, str);
	average = atoi(str);
	setparam->GetDlgItemText(IDC_Boxcar, str);
	boxcar = atoi(str);*/
	COLOR_PARA dColorPara;
	ORI_PARA dOriPara;

	average = calsta_average;
	boxcar = calsta_boxcar;

	for(int i=0; i<testItemChip[chip]; i++)
	{
		str_item = m_chipList.GetItemText(i, 1);
		sscanf(str_item, "%[^(]", testItem);
		delay = atoi(m_chipList.GetItemText(i, 2)); 
		VCom = atof(m_chipList.GetItemText(i, 3)); 
		ICom = atof(m_chipList.GetItemText(i, 4)); 
		calibrate = m_calItemList.GetItemText(i, 8);
		
		if(calibrate == "Yes")
		{
			if(testItemChip[chip] > 0)
			{
				OpenLightSet(tempchiptype, chip);
			}

			if(0 == strcmp(testItem, "IF"))
			{
				TestValue = getIF(VCom, ICom, delay);
			}
			else if(0 == strcmp(testItem, "IR"))
			{
				TestValue = 1000 * fabs(getIR(VCom, ICom, delay));
			}
			else if(0 == strcmp(testItem, "VF"))
			{
				TestValue = getVF(VCom, ICom, delay);
				if(!getBering())
				{
					TestValue += systemset.VRoffset[2];
				}
			}
			else if(0 == strcmp(testItem, "VR"))
			{
				TestValue = getVR(VCom, ICom, delay);
			}
			else if(0 == strcmp(testItem, "DVF"))
			{
				TestValue = getDVF(ICom, delay);
			}
			else if(0 == strcmp(testItem, "THY"))
			{
				TestValue = getTHY(VCom, ICom);
			}
			else if(0 == strcmp(testItem, "IV"))
			{
				opticgain = m_cbOpticGain3.GetCurSel(); 
				
				TestValue = getYbit(false, opticgain, VCom, ICom, delay, true);
				
				if(TestValue >= 31000)
				{
					outOfRange = true;
				}
			}
			else
			{
				GetDlgItemText(IDC_KLV, str);
				VCom = atof(str);
				GetDlgItemText(IDC_KLI, str);
				ICom = atof(str);
				GetDlgItemText(IDC_KLDelay, str);
				delay = atoi(str);
				
				GetDlgItemText(IDC_IntegrationTime3, str);
				InteTime = atof(str);
				
				OpenLight(VCom, ICom);
				Delay(delay * 1000);
				if(1)
				{
					JK_Emission_GetData_3LED(chip, (float)InteTime, average, 3, dColorPara,dOriPara);
					int j;
					double dDecAD[2048];
					for (j = 0; j < dOriPara.iPixN; j++)
					{
						dDecAD[j] = dOriPara.fDecAD[j];
					}
					spectrum = &dDecAD[0];

					for(j = 0; j < PIXELNUM; j++)
					{
						setting_spectrum[j] = dOriPara.fDecAD[j];
					}
 					setsngCounts(spectrum, sngCurrentDark[chip]);	
				}
				CloseLight(1, 0);
				
				//getXY();
				x = dColorPara.fx;//getX();
				y = dColorPara.fy;//getY();

				if(0 == strcmp(testItem, "WL"))
				{
					wlSteps = m_cbWLSteptype3.GetCurSel();
					
					if(0 == wlSteps)
					{
						TestValue = getWL_New(x, y);
					}	
					else
					{
						TestValue = getWL_5nm_New(x, y);
					}
				}
				else if(0 == strcmp(testItem, "PWL"))
				{
					TestValue = dColorPara.fLp;//getPeakWL(1, false);
				}
				else if(0 == strcmp(testItem, "DeltaWL"))
				{
					TestValue = dColorPara.fLd;//getDeltaWL();
				}
				else if(0 == strcmp(testItem, "PUR"))
				{
					TestValue = dColorPara.fPur;//getPUR(x, y);
				}
				else if(0 == strcmp(testItem, "CCT"))
				{
					TestValue = dColorPara.fCCT;//getCCT(x, y);
				}
				else if(0 == strcmp(testItem, "CRI"))
				{
					TestValue = dColorPara.fRa;//getCRI(x, y);
				}
				else if(0 == strcmp(testItem, "IE"))
				{
					TestValue = getOptics_IV(0, intIntegrationTime[chip]);
				}	
				else if(0 == strcmp(testItem, "LE"))
				{
					TestValue = getOptics_IV(2, intIntegrationTime[chip]);
				}
				else if(0 == strcmp(testItem, "LV"))
				{
					TestValue = getOptics_IV(1, intIntegrationTime[chip]);
				}
			}
			
			if(0 == strcmp(testItem, "XYZ"))
			{
				staValue = atof(m_xylist.GetItemText(0, 1));
				staValue2 = atof(m_xylist.GetItemText(1, 1));
				
				getXY();
				x = dColorPara.fx;//getX();
				y = dColorPara.fy;//getY();
				
				double xafter = 0, yafter = 0;
				if(m_xylist.GetItemText(0, 4) == "+")
				{
					calparam2 = staValue - x;
					calparam4 = staValue2 - y;
					
					str.Format("%0.4f", calparam2);
					m_xylist.SetItemText(0, 6, ReformatString(str));
					str.Format("%0.4f", calparam4);
					m_xylist.SetItemText(1, 6, ReformatString(str));
					
					m_xylist.SetItemText(0, 5, "1");
					m_xylist.SetItemText(1, 5, "1");
				}
				else if(m_xylist.GetItemText(0, 4) == "*")
				{
					calparam1 = staValue / x;
					calparam3 = staValue2 / y;
					
					str.Format("%0.4f", calparam1);
					m_xylist.SetItemText(0, 5, ReformatString(str));
					str.Format("%0.4f", calparam3);
					m_xylist.SetItemText(1, 5, ReformatString(str));
					
					m_xylist.SetItemText(0, 6, "0");
					m_xylist.SetItemText(1, 6, "0");
				}
				
				m_calItemList.SetItemText(i, 2, "disable");
				m_calItemList.SetItemText(i, 3, "disable");
				m_calItemList.SetItemText(i, 4, "disable");
				
				str.Format("%0.4f", x);
				m_xylist.SetItemText(0, 2, ReformatString(str));
				str.Format("%0.4f", y);
				m_xylist.SetItemText(1, 2, ReformatString(str));
			}
			else
			{
				staValue = atof(m_calItemList.GetItemText(i, 2));
				if(m_calItemList.GetItemText(i, 5) == "+")
				{
					calparam2 = staValue - TestValue;
					str.Format("%0.4f", calparam2);
					m_calItemList.SetItemText(i, 7, ReformatString(str));
					m_calItemList.SetItemText(i, 6, "1");
				}
				else if(m_calItemList.GetItemText(i, 5) == "*")
				{
					calparam1 = staValue / TestValue;
					str.Format("%0.4f", calparam1);
					m_calItemList.SetItemText(i, 6, ReformatString(str));
					m_calItemList.SetItemText(i, 7, "0");
				}
				
				TestValue = fabs(TestValue);
				str.Format("%0.3f", TestValue);
				m_calItemList.SetItemText(i, 3, ReformatString(str));
			}
		}
	}
	
	updateRect = true;
	Delay(1000);
	updateRect = false;

	if(outOfRange)
	{
		MessageBox("亮度饱和，请选择适当的光强增益!");
	}
}

void CChip3Dlg::OnAutoGetOpticGain3() 
{
	// TODO: Add your control notification handler code here
	extern bool tempmixopen;
	double value = 0, tempvalue = 0;
	double voltage = 0, current = 0;
	long delay = 0;
	int i = 0;
	int gain = 0;
	CString str;
	
	OpenLightSet(tempchiptype, chip);
	
	if(!tempmixopen)
	{	
		for(i=0; i<testItemChip[chip]; i++)
		{
			str = m_chipList.GetItemText(i, 1);
			if(str == "IV")
			{
				delay = atoi(m_chipList.GetItemText(i, 2)); 
				voltage = atof(m_chipList.GetItemText(i, 3)); 
				current = atof(m_chipList.GetItemText(i, 4)); 
				
				i = testItemChip[chip];
			}
		}
		
		for(i=0; i<4; i++)
		{
			tempvalue = getYbit(false, i, voltage, current, delay, false);	
			
			if((tempvalue > 0) && fabs((tempvalue - 6) < fabs(value - 6)))
			{
				gain = i;
			}
		}
	}

	m_cbOpticGain3.SetCurSel(gain);
}

void CChip3Dlg::OnChangeKlv() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CResizingDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItemText(IDC_KLV, str);
	tempV3 = atof(str);
}

void CChip3Dlg::OnChangeKli() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CResizingDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItemText(IDC_KLI, str);
	tempI3 = atof(str);
}


void CChip3Dlg::SetDialogFace()
{
	m_getGain.SetBitmaps(IDB_Button_GetGainNormal, IDB_Button_GetGainDown,
		              IDB_Button_GetGainHigh, IDB_Button_GetGainDisable);
	m_getGain.SizeToContent();

	m_autosetTime.SetBitmaps(IDB_Button_InteTimeNormal, IDB_Button_InteTimeDown,
		              IDB_Button_InteTimeHigh, IDB_Button_InteTimeDisable);
	m_autosetTime.SizeToContent();
	m_autosetTime.SetDrawText(true, false)
			.SetFont3D(true, 0, 0, false)
		    .SetFontSize(10, false)
			.SetForceColor(RGB(255, 255, 255), RGB(255, 255, 255), RGB(255, 255, 255), false);


	m_addDark.SetBitmaps(IDB_Button_AddDarkNormal, IDB_Button_AddDarkDown,
		              IDB_Button_AddDarkHigh, IDB_Button_AddDarkDisable);
	m_addDark.SizeToContent();

	m_clearDark.SetBitmaps(IDB_Button_clearDarkNormal, IDB_Button_clearDarkDown,
		              IDB_Button_clearDarkHigh, IDB_Button_clearDarkDisable);
	m_clearDark.SizeToContent();
	
	
	m_caltest.SetBitmaps(IDB_Button_CalTestNormal, IDB_Button_CalTestDown,
		              IDB_Button_CalTestHigh, IDB_Button_CalTestDisable);
	m_caltest.SizeToContent();

	m_getCal.SetBitmaps(IDB_Button_GetCalNormal, IDB_Button_GetCalDown,
		              IDB_Button_GetCalHigh, IDB_Button_GetCalDisable);
	m_getCal.SizeToContent();

	m_clearCal.SetBitmaps(IDB_Button_ClearCalNormal, IDB_Button_ClearCalDown,
		              IDB_Button_ClearCalHigh, IDB_Button_ClearCalDisable);
	m_clearCal.SizeToContent();
}

BOOL CChip3Dlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default	
//	return CResizingDialog::OnEraseBkgnd(pDC);
	return true;
}

HBRUSH CChip3Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CResizingDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr=(HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}



