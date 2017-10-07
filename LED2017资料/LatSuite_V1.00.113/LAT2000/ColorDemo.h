#pragma once


// CColorDemo



class CColorDemo : public CStatic
{
	DECLARE_DYNAMIC(CColorDemo)

public:
	CColorDemo();
	virtual ~CColorDemo();

protected:
	DECLARE_MESSAGE_MAP()
	CFont m_newFont;

public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


