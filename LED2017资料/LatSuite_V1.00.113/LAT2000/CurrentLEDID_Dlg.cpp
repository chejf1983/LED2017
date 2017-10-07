// CurrentLEDID_Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "CurrentLEDID_Dlg.h"
#include "afxdialogex.h"


// CCurrentLEDID_Dlg 对话框

IMPLEMENT_DYNAMIC(CCurrentLEDID_Dlg, CDialogEx)

CCurrentLEDID_Dlg::CCurrentLEDID_Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCurrentLEDID_Dlg::IDD, pParent)
{

}

CCurrentLEDID_Dlg::~CCurrentLEDID_Dlg()
{
}

void CCurrentLEDID_Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_CURLEDID, m_iCurrentLEDID);
}


BEGIN_MESSAGE_MAP(CCurrentLEDID_Dlg, CDialogEx)
END_MESSAGE_MAP()


// CCurrentLEDID_Dlg 消息处理程序
