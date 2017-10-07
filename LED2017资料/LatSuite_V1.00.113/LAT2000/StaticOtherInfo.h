#pragma once

enum LineState
{
	NotConnected	= 0,
	Free			= 1,
	Testing			= 2,
	Stepping		= 3,
	ManulStopped	= 4,
	LampTooHigh		= 5,
	WaitTime		= 6,
    Olding			= 7,
};
// CStaticOtherInfo

class CStaticOtherInfo : public CStatic
{
	DECLARE_DYNAMIC(CStaticOtherInfo)

public:
	CStaticOtherInfo();
	virtual ~CStaticOtherInfo();

public:
	void SetLineState(LineState state);
	void SetBurnInInfo(int iONSeconds, int iOFFSeconds);
	void SetBurnInInfo(CString strInfo);
	void Set5AInfo(CString strInfo);
	void Set11KInfo(CString strInfo);
	void SetStatisticInfo(CString strStatisticInfo);
	void SetWaitRemainSeconds(int iTime);
    void SetOldTimeSeconds(float fTime);

private:
	CFont m_font;
	LineState m_lineState;
	CString m_strLineState;
	CString m_strDot;
	CString m_strBurnInInfo;
	CString m_str11KInfo;
	CString m_str5AInfo;
	CString m_strStatisticInfo;
	int m_iWaitRemainSecond;
    float m_fOldTime;
	CCriticalSection m_criticalSection;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


