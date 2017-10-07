// DlgShowOtherNote.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DlgShowOtherNote.h"
#include "afxdialogex.h"


// CDlgShowOtherNote 对话框

IMPLEMENT_DYNAMIC(CDlgShowOtherNote, CDialogEx)

CDlgShowOtherNote::CDlgShowOtherNote(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgShowOtherNote::IDD, pParent)
{
	m_font.CreateFont(-16, 0, 0, 0, 500, FALSE, FALSE, 0,
		GB2312_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_MODERN,"宋体");
	m_strDot = "";
	m_iTimems = - 1;
}

CDlgShowOtherNote::~CDlgShowOtherNote()
{
}

void CDlgShowOtherNote::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgShowOtherNote, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgShowOtherNote 消息处理程序


void CDlgShowOtherNote::OnPaint()
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
	CSize sizeTextNote = memDC.GetOutputTextExtent(m_strNote);
	int iX = rectClient.Width() /2 - sizeTextNote.cx / 2 - sizeText.cx,  iY = rectClient.top + rectClient.Height() / 2 - sizeText.cy / 2, iYStep = sizeText.cy;
	memDC.SetTextColor(RGB(0, 0, 255));
	memDC.TextOutA(iX, iY, m_strNote + m_strDot);
	memDC.SelectObject(hOld);

	dc.BitBlt(0, 0, rectClient.Width(), rectClient.Height(), &memDC, 0, 0, SRCCOPY);
	MemBitmap.DeleteObject();
	memDC.DeleteDC();
}


void CDlgShowOtherNote::OnTimer(UINT_PTR nIDEvent)
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
	if((int)::GetCurrentTime() - m_iStartTimes > m_iTimems)
	{
		SendMessage(WM_CLOSE);
	}
	Invalidate();
	CDialogEx::OnTimer(nIDEvent);
}


void CDlgShowOtherNote::SetNote(CString strNote, int iTimes)
{
	m_strNote = strNote;
	m_iTimems = iTimes * 1000;
	m_iStartTimes = (DWORD)GetCurrentTime();
}


BOOL CDlgShowOtherNote::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetTimer(1, 1000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
