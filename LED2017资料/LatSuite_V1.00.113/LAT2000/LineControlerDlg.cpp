// LineControlerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "LineControlerDlg.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"


// CLineControlerDlg 对话框

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


// CLineControlerDlg 消息处理程序


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
			AfxMessageBox("产线控制失败!");
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
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    CDialogEx::OnCancel();
}


void CLineControlerDlg::OnBnClickedButtonContinueMoveOnesetp()
{
    // TODO: 在此添加控件通知处理程序代码
    if (UpdateData(TRUE) == FALSE)
	{
		return;
	}
	if (m_iSleepTimems < 5000)
	{
		AfxMessageBox("节拍时间太短!请重新设定.");
		return;
	}
    
    m_bStopMoveOneStep = FALSE;
    AfxBeginThread(ThreadLineControlerMoveOneStep, this);
}



void CLineControlerDlg::OnBnClickedButtonStopMoveOnesetp()
{
    // TODO: 在此添加控件通知处理程序代码

    m_bStopMoveOneStep = TRUE;
}


void CLineControlerDlg::OnBnClickedButtonContinueMove()
{
    // TODO: 在此添加控件通知处理程序代码
    BeginWaitCursor();
    if (!g_LineControllerComm.MoveLineContinuous())
    {
        AfxMessageBox("产线控制失败!");
    }
    EndWaitCursor();
}


void CLineControlerDlg::OnBnClickedButtonSeopMove()
{
    // TODO: 在此添加控件通知处理程序代码
    BeginWaitCursor();
    if (!g_LineControllerComm.SetLinePause())
    {
        AfxMessageBox("产线控制失败!");
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

    // TODO:  在此添加额外的初始化
    EnableButton();

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}
