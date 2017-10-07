// CurrentBoardID_Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "CurrentBoardID_Dlg.h"
#include "afxdialogex.h"      
#include "LAT2000Doc.h"


// CCurrentBoardID_Dlg 对话框

IMPLEMENT_DYNAMIC(CCurrentBoardID_Dlg, CDialogEx)

CCurrentBoardID_Dlg::CCurrentBoardID_Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCurrentBoardID_Dlg::IDD, pParent)
    , m_iCurrentBoardID(1)
	, m_iLEDOnPos(0)
	, m_iTestHaveScanedMode(0)
{

}

CCurrentBoardID_Dlg::~CCurrentBoardID_Dlg()
{
}

void CCurrentBoardID_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CURRENT_BOARD_INDEX, m_iCurrentBoardID);
	DDV_MinMaxInt(pDX, m_iCurrentBoardID, 1, g_pDoc->m_CommSettingsData.m_iTotalBoard);
	DDX_Radio(pDX, IDC_NOMAL_LEDON_POS, m_iLEDOnPos);
	DDX_Radio(pDX, IDC_RADIO_TESTANDSCAN, m_iTestHaveScanedMode);
}


BEGIN_MESSAGE_MAP(CCurrentBoardID_Dlg, CDialogEx)
END_MESSAGE_MAP()


// CCurrentBoardID_Dlg 消息处理程序
