// LineControlerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "LineControlerDlg.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"


// CLineControlerDlg �Ի���

IMPLEMENT_DYNAMIC(CLineControlerDlg, CDialogEx)

CLineControlerDlg::CLineControlerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLineControlerDlg::IDD, pParent)
{

	//  m_iSleepTimems = 0;

	CString strSection = "LineControlerDlg";
	CString str_m_iSleepTimems = _T("m_iSleepTimems");
	m_iSleepTimems = 0;
	m_iSleepTimems = AfxGetApp()->GetProfileInt(strSection, str_m_iSleepTimems, 5000);
	m_bStopMoveOneStep = TRUE;
	g_LineControllerComm.Initialize(g_pDoc->m_CommSettingsData.m_strLineControllerCOM);

}

CLineControlerDlg::~CLineControlerDlg()
{

    CString strSection = "LineControlerDlg";
    CString str_m_iSleepTimems = _T("m_iSleepTimems");

    AfxGetApp()->WriteProfileInt(strSection, str_m_iSleepTimems, m_iSleepTimems);
}

void CLineControlerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SLEEPTIME, m_iSleepTimems);
}


BEGIN_MESSAGE_MAP(CLineControlerDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_CONTINUE_MOVE_ONESETP, &CLineControlerDlg::OnBnClickedButtonContinueMoveOnesetp)
    ON_BN_CLICKED(IDCANCEL, &CLineControlerDlg::OnBnClickedCancel)
    ON_BN_CLICKED(IDC_BUTTON_STOP_MOVE_ONESETP, &CLineControlerDlg::OnBnClickedButtonStopMoveOnesetp)
    ON_BN_CLICKED(IDC_BUTTON_CONTINUE_MOVE, &CLineControlerDlg::OnBnClickedButtonContinueMove)
    ON_BN_CLICKED(IDC_BUTTON_SEOP_MOVE, &CLineControlerDlg::OnBnClickedButtonSeopMove)
END_MESSAGE_MAP()


// CLineControlerDlg ��Ϣ�������


UINT CLineControlerDlg::ThreadLineControlerMoveOneStep(LPVOID lPar)
{
	CLineControlerDlg *pDlg = (CLineControlerDlg*)lPar;
	pDlg->EnableButton();
	while(1)
	{
		if (pDlg->m_bStopMoveOneStep)
		{
			break;
		}
		if (!g_LineControllerComm.MoveLineOneStep())
		{
			AfxMessageBox("���߿���ʧ��!");
			pDlg->m_bStopMoveOneStep = TRUE;
			break;
		}
		int bInposition, bManualStopped, bLampTooHigh;
		while(g_LineControllerComm.ReadLineState(bInposition, bManualStopped, bLampTooHigh))
		{
			if (bManualStopped)
			{
				pDlg->m_bStopMoveOneStep = TRUE;
				pDlg->EnableButton();
				return 0;
			}
			if (bInposition == 2)
			{
				break;
			}

			Sleep(20);
		}

		Sleep(pDlg->m_iSleepTimems);
	}
	pDlg->EnableButton();
	return 0;
}

void CLineControlerDlg::OnBnClickedCancel()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);
    CDialogEx::OnCancel();
}


void CLineControlerDlg::OnBnClickedButtonContinueMoveOnesetp()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    if (UpdateData(TRUE) == FALSE)
	{
		return;
	}
	if (m_iSleepTimems < 5000)
	{
		AfxMessageBox("����ʱ��̫��!�������趨.");
		return;
	}
    
    m_bStopMoveOneStep = FALSE;
    AfxBeginThread(ThreadLineControlerMoveOneStep, this);
}



void CLineControlerDlg::OnBnClickedButtonStopMoveOnesetp()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������

    m_bStopMoveOneStep = TRUE;
}


void CLineControlerDlg::OnBnClickedButtonContinueMove()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    BeginWaitCursor();
    if (!g_LineControllerComm.MoveLineContinuous())
    {
        AfxMessageBox("���߿���ʧ��!");
    }
    EndWaitCursor();
}


void CLineControlerDlg::OnBnClickedButtonSeopMove()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    BeginWaitCursor();
    if (!g_LineControllerComm.SetLinePause())
    {
        AfxMessageBox("���߿���ʧ��!");
    }
    EndWaitCursor();
}


void CLineControlerDlg::EnableButton()
{
    GetDlgItem(IDC_BUTTON_CONTINUE_MOVE_ONESETP)->EnableWindow(m_bStopMoveOneStep);
    GetDlgItem(IDC_BUTTON_STOP_MOVE_ONESETP)->EnableWindow(!m_bStopMoveOneStep);
    GetDlgItem(IDC_BUTTON_CONTINUE_MOVE)->EnableWindow(m_bStopMoveOneStep);
    GetDlgItem(IDC_BUTTON_SEOP_MOVE)->EnableWindow(m_bStopMoveOneStep);
	GetDlgItem(IDCANCEL)->EnableWindow(m_bStopMoveOneStep);

}


BOOL CLineControlerDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    EnableButton();

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}
