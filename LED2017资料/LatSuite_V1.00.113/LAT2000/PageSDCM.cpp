// PageSDCM.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "PageSDCM.h"
#include "afxdialogex.h"
#include "Ex_SDCM_DLL.h"

// CPageSDCM 对话框

IMPLEMENT_DYNAMIC(CPageSDCM, CDialogEx)

CPageSDCM::CPageSDCM(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPageSDCM::IDD, pParent)
{
    m_brush.CreateSolidBrush(RGB(255,255,255));
    m_fCIE_x = 0.45f;
    m_fCIE_y = 0.45f;
}

CPageSDCM::~CPageSDCM()
{
}

void CPageSDCM::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageSDCM, CDialogEx)
    ON_WM_PAINT()
    ON_WM_SIZE()
    ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CPageSDCM 消息处理程序


void CPageSDCM::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: 在此处添加消息处理程序代码
    // 不为绘图消息调用 CDialogEx::OnPaint()
    CRect rect, dRect;
    GetClientRect(&rect);
    dRect = rect;

    CBrush *pOldBrush;
    pOldBrush = dc.SelectObject(&m_brush);
    dc.Rectangle(rect);
    SDCM_DLL_DrawSDCM_OneGra(dc.m_hDC, dRect, m_fCIE_x, m_fCIE_y,
        FALSE,FALSE);
    dc.SelectObject(pOldBrush);
}


void CPageSDCM::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码
    Invalidate();
}


void CPageSDCM::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    CDialogEx::OnLButtonDblClk(nFlags, point); 
    AfxGetMainWnd()->SendMessage(WM_COMMAND,ID_MAKE_REGION);
}


void CPageSDCM::ReDraw(float fCIE_x, float fCIE_y)
{
    m_fCIE_x = fCIE_x;
    m_fCIE_y = fCIE_y;
    Invalidate();
}


BOOL CPageSDCM::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
   
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}
