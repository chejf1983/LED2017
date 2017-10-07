// DataListViewSelectShow.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DataListViewSelectShow.h"
#include "afxdialogex.h"


// CDataListViewSelectShow 对话框

IMPLEMENT_DYNAMIC(CDataListViewSelectShow, CDialogEx)

CDataListViewSelectShow::CDataListViewSelectShow(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDataListViewSelectShow::IDD, pParent)
{

}

CDataListViewSelectShow::~CDataListViewSelectShow()
{
}

void CDataListViewSelectShow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_FLUX, m_bFlux);
	DDX_Check(pDX, IDC_CHECK_HW, m_bHw);
	DDX_Check(pDX, IDC_CHECK_IF, m_bIF);
	DDX_Check(pDX, IDC_CHECK_IP, m_bIp);
	DDX_Check(pDX, IDC_CHECK_IR, m_bIR);
	DDX_Check(pDX, IDC_CHECK_LD, m_bLd);
	DDX_Check(pDX, IDC_CHECK_LP, m_bLp);
	DDX_Check(pDX, IDC_CHECK_PUR, m_bPur);
	DDX_Check(pDX, IDC_CHECK_RA, m_bRa);
	DDX_Check(pDX, IDC_CHECK_TC, m_bTc);
	DDX_Check(pDX, IDC_CHECK_U, m_bU);
	DDX_Check(pDX, IDC_CHECK_V, m_bV);
	DDX_Check(pDX, IDC_CHECK_VF, m_bVF);
	DDX_Check(pDX, IDC_CHECK_VR, m_bVR);
	DDX_Check(pDX, IDC_CHECK_X, m_bX);
	DDX_Check(pDX, IDC_CHECK_Y, m_bY);
	DDX_Check(pDX, IDC_CHECK_EFF, m_bEff);
}


BEGIN_MESSAGE_MAP(CDataListViewSelectShow, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDataListViewSelectShow::OnBnClickedOk)
END_MESSAGE_MAP()


// CDataListViewSelectShow 消息处理程序


void CDataListViewSelectShow::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CDialogEx::OnOK();
}
