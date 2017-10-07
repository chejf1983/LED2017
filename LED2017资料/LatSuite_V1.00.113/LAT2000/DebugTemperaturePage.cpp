// DebugTemperaturePage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DebugTemperaturePage.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"

// CDebugTemperaturePage �Ի���

IMPLEMENT_DYNAMIC(CDebugTemperaturePage, CPropertyPage)

CDebugTemperaturePage::CDebugTemperaturePage()
	: CPropertyPage(CDebugTemperaturePage::IDD)
{

	m_strBaudrate = _T("9600");
	m_ucAddress = 1;
	m_fTMPRead = 0.0f;
	m_fTMPSet = 0.0f;

	CString strSection = "DebugTemperaturePage";
	m_strCOM = AfxGetApp()->GetProfileStringA(strSection, "m_strCOM", "COM1");
}

CDebugTemperaturePage::~CDebugTemperaturePage()
{
	CString strSection = "DebugTemperaturePage";
	AfxGetApp()->WriteProfileString(strSection, "m_strCOM", m_strCOM);
}

void CDebugTemperaturePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_BAUDRATE, m_strBaudrate);
	DDX_CBString(pDX, IDC_COMBO_COM, m_strCOM);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_ucAddress);
	DDX_Text(pDX, IDC_EDIT_TMP_READ, m_fTMPRead);
	DDX_Text(pDX, IDC_EDIT_TMP_SET, m_fTMPSet);
}


BEGIN_MESSAGE_MAP(CDebugTemperaturePage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CDebugTemperaturePage::OnBnClickedButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CDebugTemperaturePage::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_TMP_STOP, &CDebugTemperaturePage::OnBnClickedButtonTmpStop)
    ON_BN_CLICKED(IDC_BUTTON_SELF_TURNING_MODE, &CDebugTemperaturePage::OnBnClickedButtonSelfTurningMode)
    ON_BN_CLICKED(IDC_BUTTON_CAL_RIGHT_PID, &CDebugTemperaturePage::OnBnClickedButtonCalRightPid)
    ON_BN_CLICKED(IDC_BUTTON_READ_PIDTURNING_MODE, &CDebugTemperaturePage::OnBnClickedButtonReadPidturningMode)
    ON_BN_CLICKED(IDC_BUTTON_READ_PID, &CDebugTemperaturePage::OnBnClickedButtonReadPid)
    ON_BN_CLICKED(IDC_BUTTON_INIT, &CDebugTemperaturePage::OnBnClickedButtonInit)
END_MESSAGE_MAP()


// CDebugTemperaturePage ��Ϣ�������


void CDebugTemperaturePage::OnBnClickedButtonRead()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	BeginWaitCursor();
	g_FujiTMPComm.Initialize(m_strCOM);
	if (g_FujiTMPComm.ReadTemperature(m_ucAddress, m_fTMPRead, m_iAlarm))
	{
		UpdateData(FALSE);
		AfxMessageBox("��ȡ�ɹ���");
	}
	else
	{
		AfxMessageBox("��ȡʧ�ܣ�");
	}
	EndWaitCursor();
}


void CDebugTemperaturePage::OnBnClickedButtonSet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	BeginWaitCursor();
	g_FujiTMPComm.Initialize(m_strCOM);
	if (g_FujiTMPComm.SetTemperature(m_ucAddress, m_fTMPSet,m_fTMPSetL, m_fTMPSetH))
	{
		AfxMessageBox("���óɹ���");
	}
	else
	{
		AfxMessageBox("����ʧ�ܣ�");
	}
	EndWaitCursor();
}


void CDebugTemperaturePage::OnBnClickedButtonTmpStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	BeginWaitCursor();
	g_FujiTMPComm.Initialize(m_strCOM);
	if (g_FujiTMPComm.StopTwo())
	{
		AfxMessageBox("���Ƴɹ���");
	}
	else
	{
		AfxMessageBox("����ʧ�ܣ�");
	}
	EndWaitCursor();
}


void CDebugTemperaturePage::OnBnClickedButtonSelfTurningMode()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);

    BeginWaitCursor();
    g_FujiTMPComm.Initialize(m_strCOM);
    if (g_FujiTMPComm.SetSelfTruningMode(m_ucAddress))
    {
        AfxMessageBox("���óɹ���");
    }
    else
    {
        AfxMessageBox("����ʧ�ܣ�");
    }
    EndWaitCursor();
}


void CDebugTemperaturePage::OnBnClickedButtonCalRightPid()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������


    UpdateData(TRUE);

    BeginWaitCursor();
    g_FujiTMPComm.Initialize(m_strCOM);
    if (g_FujiTMPComm.SetSelfTruningMode(m_ucAddress))
    {
    }
    else
    {
        AfxMessageBox("����ʧ�ܣ�");
        return;
    }
    EndWaitCursor();

    UpdateData(TRUE);

    BeginWaitCursor();
    g_FujiTMPComm.Initialize(m_strCOM);
    if (g_FujiTMPComm.SetPIDTruning(m_ucAddress))
    {
        AfxMessageBox("���Ƴɹ���");
    }
    else
    {
        AfxMessageBox("����ʧ�ܣ�");
        return;
    }
    EndWaitCursor();
}


void CDebugTemperaturePage::OnBnClickedButtonReadPidturningMode()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);

    BeginWaitCursor();
    g_FujiTMPComm.Initialize(m_strCOM);
    int iState;
    if (g_FujiTMPComm.GetPIDTruningState(m_ucAddress, iState))
    {
        if (iState == 0)
        {
            GetDlgItem(IDC_EDIT_PID_TRUNING_STATE)->SetWindowText("���������!");
        }
        else
        {
            GetDlgItem(IDC_EDIT_PID_TRUNING_STATE)->SetWindowText("��������...!");
        }
        AfxMessageBox("��ȡ�ɹ���");
    }
    else
    {
        AfxMessageBox("��ȡʧ�ܣ�");
    }
    EndWaitCursor();
}


void CDebugTemperaturePage::OnBnClickedButtonReadPid()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);

    BeginWaitCursor();
    g_FujiTMPComm.Initialize(m_strCOM);
    float fP, fI, fD;
    if (g_FujiTMPComm.GetPID(m_ucAddress, fP, fI, fD))
    {
        CString strTemp;
        strTemp.Format("P:%.4g, I:%.4g, D:%.4g", fP, fI, fD);
        GetDlgItem(IDC_EDIT_PID)->SetWindowText(strTemp);
        AfxMessageBox("��ȡ�ɹ���");
    }
    else
    {
        AfxMessageBox("��ȡʧ�ܣ�");
    }
    EndWaitCursor();
}


void CDebugTemperaturePage::OnBnClickedButtonInit()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);

    BeginWaitCursor();
    g_FujiTMPComm.Initialize(m_strCOM);
    if (g_FujiTMPComm.SetInitPara(m_ucAddress))
    {
        AfxMessageBox("��ʼ���ɹ���");
    }
    else
    {
        AfxMessageBox("��ʼ��ʧ�ܣ�");
    }
    EndWaitCursor();
}


BOOL CDebugTemperaturePage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_strCOM = g_pDoc->m_CommSettingsData.m_strCOMTemperature;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
