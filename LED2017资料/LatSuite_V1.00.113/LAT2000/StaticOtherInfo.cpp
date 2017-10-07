// StaticOtherInfo.cpp : ʵ���ļ�
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
		DEFAULT_PITCH | FF_MODERN,"����");

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



// CStaticOtherInfo ��Ϣ�������




void CStaticOtherInfo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CStatic::OnPaint()
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
	memDC.TextOutA(iX, iY, "������״̬��");
	iX += memDC.GetOutputTextExtent("������״̬��").cx;
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
	memDC.TextOutA(iX, iY, "������״̬��");
	iX += memDC.GetOutputTextExtent("������״̬��").cx;
	memDC.SetTextColor(RGB(0, 0 , 255));
	memDC.TextOutA(iX, iY, m_strBurnInInfo);
	
	// EMS61000-5A
	iX = sizeText.cx;
	iY += iYStep * 2;
	memDC.SetTextColor(RGB(0, 0 , 0));
	memDC.TextOutA(iX, iY, "���׻����顿");
	iX += memDC.GetOutputTextExtent("���׻����顿").cx;
	memDC.SetTextColor(RGB(0, 0 , 255));
	memDC.TextOutA(iX, iY, m_str5AInfo);
	
	// EMS61000-11K
	iX = sizeText.cx;
	iY += iYStep * 2;
	memDC.SetTextColor(RGB(0, 0 , 0));
	memDC.TextOutA(iX, iY, "���ܲ����䡿");
	iX += memDC.GetOutputTextExtent("���ܲ����䡿").cx;
	memDC.SetTextColor(RGB(0, 0 , 255));
	memDC.TextOutA(iX, iY, m_str11KInfo);
	
	// Statistics information
	iX = sizeText.cx;
	iY += iYStep * 2;
	memDC.SetTextColor(RGB(0, 0 , 0));
	memDC.TextOutA(iX, iY, "��ͳ����Ϣ��");
	iX += memDC.GetOutputTextExtent("��ͳ����Ϣ��").cx;
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
	iX += memDC.GetOutputTextExtent("��ͳ����Ϣ��").cx;
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
		m_strLineState = "����ʧ��!";
		break;

	case ManulStopped:
		m_strLineState = "ǿ��ֹͣ!";
		break;

	case Testing:
		if (g_pDoc->m_dataContainer.GetTestSettingData().m_bTestAutoHand)
		{
			if(g_pDoc->m_iHaveInLampBroadNum < (atoi(g_pDoc->m_CommSettingsData.m_strHandAutoRange1)))
				m_strLineState.Format("�ϵ��е�ǰ�ϵư��%d���ϵư���%d��",
				g_pDoc->m_iCurrentInLampBroad,
				g_pDoc->m_iHaveInLampBroadNum);
			else
			{
				int iTestBroad;
				int iTolBroad = g_pDoc->m_CommSettingsData.m_iTotalBoard;
				iTestBroad = (g_pDoc->m_iHaveInLampBroadNum - (atoi(g_pDoc->m_CommSettingsData.m_strHandAutoRange1)) - 1 + g_pDoc->m_iStartInLampBroad)%iTolBroad;

				m_strLineState.Format("������ ����λ%d (��ǰ�ϵư��λ%d���ϵư���%d��)",
					iTestBroad,
					g_pDoc->m_iCurrentInLampBroad,
					g_pDoc->m_iHaveInLampBroadNum);
			}
		}
		else if(g_pDoc->m_CommSettingsData.m_bHaveScaner)
		{
			if(!g_pDoc->m_TestContainer.CurrentTestRowIsScaned())
				m_strLineState.Format("ɨ���е�ǰɨ��λ%d��ɨ%d��",
				g_pDoc->m_TestContainer.GetCurrentScanBoard(),
				g_pDoc->m_TestContainer.GetCurrentScanIDNum());
			else
				m_strLineState.Format("������ ����λ%d (��ǰɨ��λ%d��ɨ%d��)",
				g_pDoc->m_TestContainer.GetCurrentTestBoard(),
				g_pDoc->m_TestContainer.GetCurrentScanBoard(),
				g_pDoc->m_TestContainer.GetCurrentScanIDNum());
		}
		else
		{
			if(g_pDoc->m_dataContainer.GetTestSettingData().m_bTestSaft && g_pDoc->m_iHaveBoradSaftR < g_pDoc->m_CommSettingsData.m_iJydzLedTestRange)
			{
				m_strLineState.Format("���������(%d/%d)",g_pDoc->m_iHaveBoradSaftR,g_pDoc->m_CommSettingsData.m_iJydzLedTestRange);
			}
			else
			{
				m_strLineState = "������";
			}
		}
		break;

	case Stepping:
		m_strLineState = "�ƶ���";
		break;

	case Free:
		m_strLineState = "������";
		break;
	
	case LampTooHigh:
		m_strLineState = "���ߵƹ��ߣ�";
		break;

	case WaitTime:
		m_strLineState.Format("������ɣ��ȴ� %d ������",
			m_iWaitRemainSecond);
		break;
    case Olding:
        m_strLineState.Format("�����ϻ�����ǰ�ϻ��������� %g ��",
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

	m_strBurnInInfo.Format("��(%d��)   ��(%d��)", 
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

	// TODO:  �ڴ������ר�õĴ�������
	SetTimer(1, 1000, NULL);

	return 0;
}


void CStaticOtherInfo::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//return CStatic::OnEraseBkgnd(pDC);
	return FALSE;
}
