// StaticOtherInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "StaticOtherInfo.h"

#include "LAT2000Doc.h"


// CStaticOtherInfo


IMPLEMENT_DYNAMIC(CStaticOtherInfo, CStatic)

extern CLAT2000Doc * g_pDoc;

CStaticOtherInfo::CStaticOtherInfo()
{
	m_font.CreateFont(-16, 0, 0, 0, 500, FALSE, FALSE, 0,
		GB2312_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_MODERN,"宋体");

	m_iWaitRemainSecond = 0;
}

CStaticOtherInfo::~CStaticOtherInfo()
{
}


BEGIN_MESSAGE_MAP(CStaticOtherInfo, CStatic)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CStaticOtherInfo 消息处理程序




void CStaticOtherInfo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()
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
	int iX = sizeText.cx, iY = sizeText.cy, iYStep = sizeText.cy;
	memDC.TextOutA(iX, iY, "【产线状态】");
	iX += memDC.GetOutputTextExtent("【产线状态】").cx;
	if (ManulStopped == m_lineState || NotConnected == m_lineState || LampTooHigh == m_lineState)
	{
		memDC.SetTextColor(RGB(255, 0, 0));
		memDC.TextOutA(iX, iY, m_strLineState);
	}
	if (Testing == m_lineState || WaitTime == m_lineState)
	{
		memDC.SetTextColor(RGB(5, 165, 90));
		memDC.TextOutA(iX, iY, m_strLineState + m_strDot);
	}
	if (Stepping == m_lineState || Free == m_lineState || WaitTime == m_strLineState)
	{
		memDC.SetTextColor(RGB(0, 0, 255));
		memDC.TextOutA(iX, iY, m_strLineState + m_strDot);
	}

    if (Olding == m_lineState)
    {
        memDC.SetTextColor(RGB(0, 0, 255));
        memDC.TextOutA(iX, iY, m_strLineState + m_strDot);
    }
	// Burn in information
	iX = sizeText.cx;
	iY += iYStep * 2;
	memDC.SetTextColor(RGB(0, 0 , 0));
	memDC.TextOutA(iX, iY, "【老炼状态】");
	iX += memDC.GetOutputTextExtent("【老炼状态】").cx;
	memDC.SetTextColor(RGB(0, 0 , 255));
	memDC.TextOutA(iX, iY, m_strBurnInInfo);
	
	// EMS61000-5A
	iX = sizeText.cx;
	iY += iYStep * 2;
	memDC.SetTextColor(RGB(0, 0 , 0));
	memDC.TextOutA(iX, iY, "【雷击试验】");
	iX += memDC.GetOutputTextExtent("【雷击试验】").cx;
	memDC.SetTextColor(RGB(0, 0 , 255));
	memDC.TextOutA(iX, iY, m_str5AInfo);
	
	// EMS61000-11K
	iX = sizeText.cx;
	iY += iYStep * 2;
	memDC.SetTextColor(RGB(0, 0 , 0));
	memDC.TextOutA(iX, iY, "【周波跌落】");
	iX += memDC.GetOutputTextExtent("【周波跌落】").cx;
	memDC.SetTextColor(RGB(0, 0 , 255));
	memDC.TextOutA(iX, iY, m_str11KInfo);
	
	// Statistics information
	iX = sizeText.cx;
	iY += iYStep * 2;
	memDC.SetTextColor(RGB(0, 0 , 0));
	memDC.TextOutA(iX, iY, "【统计信息】");
	iX += memDC.GetOutputTextExtent("【统计信息】").cx;
	memDC.SetTextColor(RGB(0, 0 , 255));
	CString strTemp;
	int i;
	for ( i = 0; i < m_strStatisticInfo.GetLength(); i++)
	{
		if (m_strStatisticInfo.GetAt(i) == '\n')
		{
			strTemp = m_strStatisticInfo.Left(i);
			break;
		}
	}
	memDC.TextOutA(iX, iY, strTemp);

	iX = sizeText.cx;
	iY += iYStep * 2;
	iX += memDC.GetOutputTextExtent("【统计信息】").cx;
	memDC.SetTextColor(RGB(0, 0 , 255));
	strTemp = m_strStatisticInfo.Right(m_strStatisticInfo.GetLength() - i);
	memDC.TextOutA(iX, iY, strTemp);

	memDC.SelectObject(hOld);

	dc.BitBlt(0, 0, rectClient.Width(), rectClient.Height(), &memDC, 0, 0, SRCCOPY);
	MemBitmap.DeleteObject();
	memDC.DeleteDC();
}


void CStaticOtherInfo::SetWaitRemainSeconds(int iTime)
{
	if (iTime < 0)
	{
		return;
	}
	m_iWaitRemainSecond = iTime;
}

void CStaticOtherInfo::SetOldTimeSeconds(float fTime)
{
    m_fOldTime = fTime;
}

void CStaticOtherInfo::SetLineState(LineState state)
{
	if (!IsWindow(m_hWnd))
	{
		return;
	}
	if (!m_criticalSection.Lock())
	{
		return;
	}

	switch(state)
	{
	case NotConnected:
		m_strLineState = "连接失败!";
		break;

	case ManulStopped:
		m_strLineState = "强制停止!";
		break;

	case Testing:
		if (g_pDoc->m_dataContainer.GetTestSettingData().m_bTestAutoHand)
		{
			if(g_pDoc->m_iHaveInLampBroadNum < (atoi(g_pDoc->m_CommSettingsData.m_strHandAutoRange1)))
				m_strLineState.Format("上灯中当前上灯板号%d已上灯板数%d个",
				g_pDoc->m_iCurrentInLampBroad,
				g_pDoc->m_iHaveInLampBroadNum);
			else
			{
				int iTestBroad;
				int iTolBroad = g_pDoc->m_CommSettingsData.m_iTotalBoard;
				iTestBroad = (g_pDoc->m_iHaveInLampBroadNum - (atoi(g_pDoc->m_CommSettingsData.m_strHandAutoRange1)) - 1 + g_pDoc->m_iStartInLampBroad)%iTolBroad;

				m_strLineState.Format("测试中 测试位%d (当前上灯板号位%d已上灯板数%d个)",
					iTestBroad,
					g_pDoc->m_iCurrentInLampBroad,
					g_pDoc->m_iHaveInLampBroadNum);
			}
		}
		else if(g_pDoc->m_CommSettingsData.m_bHaveScaner)
		{
			if(!g_pDoc->m_TestContainer.CurrentTestRowIsScaned())
				m_strLineState.Format("扫码中当前扫码位%d已扫%d个",
				g_pDoc->m_TestContainer.GetCurrentScanBoard(),
				g_pDoc->m_TestContainer.GetCurrentScanIDNum());
			else
				m_strLineState.Format("测试中 测试位%d (当前扫码位%d已扫%d个)",
				g_pDoc->m_TestContainer.GetCurrentTestBoard(),
				g_pDoc->m_TestContainer.GetCurrentScanBoard(),
				g_pDoc->m_TestContainer.GetCurrentScanIDNum());
		}
		else
		{
			if(g_pDoc->m_dataContainer.GetTestSettingData().m_bTestSaft && g_pDoc->m_iHaveBoradSaftR < g_pDoc->m_CommSettingsData.m_iJydzLedTestRange)
			{
				m_strLineState.Format("安规测试中(%d/%d)",g_pDoc->m_iHaveBoradSaftR,g_pDoc->m_CommSettingsData.m_iJydzLedTestRange);
			}
			else
			{
				m_strLineState = "测试中";
			}
		}
		break;

	case Stepping:
		m_strLineState = "移动中";
		break;

	case Free:
		m_strLineState = "空闲中";
		break;
	
	case LampTooHigh:
		m_strLineState = "产线灯过高！";
		break;

	case WaitTime:
		m_strLineState.Format("测试完成，等待 %d 秒后继续",
			m_iWaitRemainSecond);
		break;
    case Olding:
        m_strLineState.Format("正在老化，当前老化节拍周期 %g 秒",
            m_fOldTime);
        break;
	default:
		break;
	}

	m_lineState = state;
	Invalidate(TRUE);
	
	m_criticalSection.Unlock();
}


void CStaticOtherInfo::SetBurnInInfo(int iONSeconds, int iOFFSeconds)
{
	if (!IsWindow(m_hWnd))
	{
		return;
	}

	if (!m_criticalSection.Lock())
	{
		return;
	}

	m_strBurnInInfo.Format("开(%d秒)   关(%d秒)", 
		iONSeconds, iOFFSeconds);
	Invalidate(TRUE);
	
	m_criticalSection.Unlock();
}


void CStaticOtherInfo::SetBurnInInfo(CString strInfo)
{
	if (!IsWindow(m_hWnd))
	{
		return;
	}

	if (!m_criticalSection.Lock())
	{
		return;
	}

	m_strBurnInInfo = strInfo;
	Invalidate(TRUE);
	
	m_criticalSection.Unlock();
}


void CStaticOtherInfo::Set5AInfo(CString strInfo)
{
	if (!IsWindow(m_hWnd))
	{
		return;
	}

	if (!m_criticalSection.Lock())
	{
		return;
	}

	m_str5AInfo = strInfo;
	Invalidate();
	
	m_criticalSection.Unlock();
}


void CStaticOtherInfo::Set11KInfo(CString strInfo)
{
	if (!IsWindow(m_hWnd))
	{
		return;
	}

	if (!m_criticalSection.Lock())
	{
		return;
	}
	
	m_str11KInfo = strInfo;
	Invalidate();
	
	m_criticalSection.Unlock();
}


void CStaticOtherInfo::SetStatisticInfo(CString strStatisticInfo)
{
	if (!IsWindow(m_hWnd))
	{
		return;
	}

	if (!m_criticalSection.Lock())
	{
		return;
	}
	
	m_strStatisticInfo = strStatisticInfo;
	Invalidate();
	
	m_criticalSection.Unlock();
}


int CStaticOtherInfo::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetTimer(1, 1000, NULL);

	return 0;
}


void CStaticOtherInfo::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!m_criticalSection.Lock())
	{
		return;
	}

	if (m_strDot.GetLength() < 5)
	{
		m_strDot += ".";
	}
	else
	{
		m_strDot = ".";
	}
	Invalidate();

	CStatic::OnTimer(nIDEvent);

	m_criticalSection.Unlock();
}


BOOL CStaticOtherInfo::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//return CStatic::OnEraseBkgnd(pDC);
	return FALSE;
}
