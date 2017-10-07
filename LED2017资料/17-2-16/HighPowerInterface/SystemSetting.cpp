// SystemSetting.cpp : implementation file
//

#include "stdafx.h"
#include "HighPowerInterface.h"
#include "SystemSetting.h"

#include "Functions.h"
#include "Login.h"
#include "highpower.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSystemSetting dialog


CSystemSetting::CSystemSetting(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CSystemSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSystemSetting)
	//}}AFX_DATA_INIT
}


void CSystemSetting::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSystemSetting)
	DDX_Control(pDX, IDC_Exit, m_exit);
	DDX_Control(pDX, IDC_CheckHardware, m_ElecTest);
	DDX_Control(pDX, IDC_OOIConfig, m_OOIConfig);
	DDX_Control(pDX, IDC_SystemSave, m_systemsave);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSystemSetting, CResizingDialog)
	//{{AFX_MSG_MAP(CSystemSetting)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_Exit, OnExit)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_SystemSave, OnSystemSave)
	ON_BN_CLICKED(IDC_CheckHardware, OnCheckHardware)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_OOIConfig, OnOOIConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSystemSetting message handlers
extern SystemSet systemset;
extern bool Operator;
extern bool engineer;
extern CString mainpath;

BOOL CSystemSetting::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	MoveWindow(200, 200, 335, 280);
	CRgn rgn;
	rgn.CreateRoundRectRgn(0, 0, 335, 280, 15, 15);
	SetWindowRgn(rgn, true);
	
	CString str;

	str.Format("%d", systemset.intMachineType);
	SetDlgItemText(IDC_machineType, str);

	str.Format("%0.3f", systemset.VRoffset[0]);
	SetDlgItemText(IDC_VRoffset, str);

	str.Format("%0.3f", systemset.VRoffset[1]);
	SetDlgItemText(IDC_VRoffset2, str);

	str.Format("%0.3f", systemset.VRoffset[2]);
	SetDlgItemText(IDC_VRoffset3, str);

	str.Format("%d", systemset.checkCount);
	SetDlgItemText(IDC_checkTimes, str);
		
	str.Format("%d", systemset.validCount);
	SetDlgItemText(IDC_validTimes, str);
			
    str.Format("%d", systemset.sentBinDelay);
	SetDlgItemText(IDC_sendBinDelay, str);
		
	str.Format("%d", systemset.mintesttime);		
	SetDlgItemText(IDC_minTestTime, str);

	if(engineer || Operator)
	{
		m_systemsave.EnableWindow(true);
	}
	else
	{
		m_systemsave.EnableWindow(false);
	}

	SetDialogFace();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSystemSetting::OnCheckHardware() 
{
	// TODO: Add your control notification handler code here
	SetDlgItemText(IDC_CheckHardware, "正在检测...");
	double hardware = 0;
	hardware = initializeHardware();
	if(hardware != 0)
	{
		if(hardware <= 10)
		{
			MessageBox("反向电压校验出错");
		}
		else if((hardware > 10) && (hardware < 14))
		{
			MessageBox("电流500uA校验出错");
		}
		else if((hardware > 20) && (hardware < 24))
		{
			MessageBox("电流20mA校验出错");
		}
		else if((hardware > 30) && (hardware < 34))
		{
			MessageBox("电流200mA校验出错");
		}
		else if((hardware > 40) && (hardware < 44))
		{
			MessageBox("电流2000mA校验出错");
		}
		else 
		{
			MessageBox("电压线性校验出错!");
		}
	}
	else
	{
		MessageBox("电气测试通过!");
	}
	SetDlgItemText(IDC_CheckHardware, "手 动 电 气 检 测");
}

void CSystemSetting::OnOOIConfig() 
{
	// TODO: Add your control notification handler code here
//	OOI_Config(0, 0, 0, 0);
}

bool CSystemSetting::OnSystemSave() 
{
	// TODO: Add your control notification handler code here
	CString str_parameter;
	int i=1;

	GetDlgItemText(IDC_machineType, str_parameter);
	while(str_parameter != "")
	{
		switch(i)
		{
		case 1:
			systemset.intMachineType = atoi(str_parameter);
			if(systemset.intMachineType > MAXBIN)
			{
				MessageBox("所填BIN数超过系统允许最大BIN数!");
				return false;
			}
			GetDlgItemText(IDC_VRoffset, str_parameter);
			break;
		case 2:
			systemset.VRoffset[0] = atof(str_parameter);
			GetDlgItemText(IDC_VRoffset2, str_parameter);
			break;
		case 3:
			systemset.VRoffset[1] = atof(str_parameter);
			GetDlgItemText(IDC_VRoffset3, str_parameter);
			break;
		case 4:
			systemset.VRoffset[2] = atof(str_parameter);
			GetDlgItemText(IDC_checkTimes, str_parameter);
			break;
		case 5:
			systemset.checkCount = atoi(str_parameter);
			GetDlgItemText(IDC_validTimes, str_parameter);
			break;
		case 6:
			systemset.validCount = atoi(str_parameter);
			GetDlgItemText(IDC_sendBinDelay, str_parameter);
			break;
		case 7:	
			systemset.sentBinDelay = atoi(str_parameter);
			GetDlgItemText(IDC_minTestTime, str_parameter);
			break;
		case 8:
			systemset.mintesttime = atoi(str_parameter);
			str_parameter = "";
			break;
		default:
			str_parameter = "";
			break;
		}
		i++;
	}
	
	if(9 == i)
	{
		CStdioFile m_file;
		CString filePath;
		CString str_write;
		
		filePath = "\\System\\System.sys";
		CFileException e;
		if(!m_file.Open((LPCTSTR)filePath, CFile::modeReadWrite, &e))
		{
			CString sss;
			sss.Format("%d", e.m_cause);
			MessageBox(sss);
			MessageBox("文件保存失败!");
		}
		else
		{
			WriteSysFile(&m_file);
			m_file.Close();
			OnClose();
		}
	}
	else
	{
		MessageBox("参数填写不完整");
	}

	return true;
}

void CSystemSetting::OnExit() 
{
	// TODO: Add your control notification handler code here
	OnClose();
}

void CSystemSetting::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	CResizingDialog::OnLButtonDown(nFlags, point);
}

void CSystemSetting::SetDialogFace()
{
	m_ElecTest.SetBitmaps(IDB_Button_ElecTestNormal, IDB_Button_ElecTestDown,
		              IDB_Button_ElecTestHigh, IDB_Button_ElecTestDisable);
	m_ElecTest.SizeToContent();

	m_OOIConfig.SetBitmaps(IDB_Button_OOIConfigNormal, IDB_Button_OOIConfigDown,
		              IDB_Button_OOIConfigHigh, IDB_Button_OOIConfigDisable);
	m_OOIConfig.SizeToContent();

	m_systemsave.SetBitmaps(IDB_Button_SaveNormal, IDB_Button_SaveDown,
		              IDB_Button_SaveHigh, IDB_Button_SaveDisable);
	m_systemsave.SizeToContent();

	m_exit.SetBitmaps(IDB_Button_CancelNormal3, IDB_Button_CancelDown3,
		                 IDB_Button_CancelHigh3, IDB_Button_CancelDisable3);
	m_exit.SizeToContent();
}

BOOL CSystemSetting::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return CResizingDialog::DrawBK(pDC, IDB_SetSystemBK, 0);	
//	return CResizingDialog::OnEraseBkgnd(pDC);
}

HBRUSH CSystemSetting::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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


