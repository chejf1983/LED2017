#pragma once
#include "ToolTipEx.h"

// CMyCheckLED

class CMyCheckLED : public CStatic
{
	DECLARE_DYNAMIC(CMyCheckLED)

public:
	void SetColor(COLORREF color);
	BOOL GetCheck();
	BOOL SetCheck(BOOL bCheck);
	BOOL SetTooltip(CString strTooltipText);
	static CToolTipEx m_cToolTipEx;

public:
	CMyCheckLED();
	virtual ~CMyCheckLED();

private:
	BOOL m_bChecked;
	COLORREF m_color;
	COLORREF m_colorHighLight;
	COLORREF m_colorSelected;
	BOOL m_bMouseIn;
	int m_iCount;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnStnClicked();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


