// DlgShowOldingTime.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DlgShowOldingTime.h"
#include "afxdialogex.h"


// CDlgShowOldingTime 对话框

IMPLEMENT_DYNAMIC(CDlgShowOldingTime, CDialogEx)

CDlgShowOldingTime::CDlgShowOldingTime(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgShowOldingTime::IDD, pParent)
{
    m_font.CreateFont(-16, 0, 0, 0, 500, FALSE, FALSE, 0,
        GB2312_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_MODERN,"宋体");
}

CDlgShowOldingTime::~CDlgShowOldingTime()
{
}

void CDlgShowOldingTime::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgShowOldingTime, CDialogEx)
    ON_WM_PAINT()
    ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgShowOldingTime 消息处理程序


BOOL CDlgShowOldingTime::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    SetTimer(1, 1000, NULL);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}


void CDlgShowOldingTime::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: 在此处添加消息处理程序代码
    // 不为绘图消息调用 CDialogEx::OnPaint()
    CRect rectClient;
    GetClientRect(&rectClient);

    CDC memDC;
    CBitmap MemBitmap;
    memDC.CreateCompatibleDC(NULL);
    MemBitmap.CreateCompatibleBitmap(&dc, rectClient.Width(), rectClient.Height());
    CBitmap * pOldBit = memDC.SelectObject(&MemBitmap);

    CBrush memBrush;
    memBrush.CreateSolidBrush(::GetSysColor(COLOR_3DFACE));

    HGDIOBJ hOld;
    hOld = memDC.SelectObject(&memBrush);
    memDC.SelectObject(GetStockObject(NULL_PEN));
    memDC.SelectObject(&m_font);
    memDC.Rectangle(&rectClient);
    memDC.DrawEdge(&rectClient, BDR_RAISED, BF_RECT);

    memDC.SetBkMode(TRANSPARENT);
    //memDC.SetTextColor(RGB(0, 0, 255));
    CSize sizeText = memDC.GetOutputTextExtent("aa");
    int iX = sizeText.cx,  iY = rectClient.top + rectClient.Height() / 2 - sizeText.cy, iYStep = sizeText.cy;
    memDC.SetTextColor(RGB(0, 0, 0));
    memDC.TextOutA(iX, iY, "【产线状态】" );
    memDC.SetTextColor(RGB(0, 0, 255));
    iX += memDC.GetOutputTextExtent("【产线状态】").cx;
    memDC.TextOutA(iX, iY,  "正在老化中" +  m_strDot );

    iY = rectClient.top + rectClient.Height() / 2 + sizeText.cy;
    CString strTemp;
    strTemp.Format("当前老化节拍周期 %g 秒, 当前老化总时间 % 0.0f 秒", 
        m_fOldTimes, ((DWORD)GetCurrentTime() - m_iStartTimes) * 1.0f / 1000);
    memDC.TextOutA(iX, iY,  strTemp );

    memDC.SelectObject(hOld);

    dc.BitBlt(0, 0, rectClient.Width(), rectClient.Height(), &memDC, 0, 0, SRCCOPY);
    MemBitmap.DeleteObject();
    memDC.DeleteDC();
}


void CDlgShowOldingTime::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    if (m_strDot.GetLength() < 5)
    {
        m_strDot += ".";
    }
    else
    {
        m_strDot = ".";
    }
    Invalidate();
    CDialogEx::OnTimer(nIDEvent);
}

void CDlgShowOldingTime::Init(float fOldTimes)
{
   m_strDot = "";
   m_iStartTimes = (DWORD)GetCurrentTime();
   m_fOldTimes = fOldTimes;
}
