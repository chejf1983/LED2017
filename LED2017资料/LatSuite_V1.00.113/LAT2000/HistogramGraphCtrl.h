#pragma once

#include "StatisticLedDataContainer.h"

// CHistogramGraphCtrl

class CHistogramGraphCtrl : public CStatic
{
	DECLARE_DYNAMIC(CHistogramGraphCtrl)

public:
	CHistogramGraphCtrl();
	virtual ~CHistogramGraphCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnPaint();
    CFont m_fontHor;
    CFont m_fontTitle;
    CString m_strTitle;
    StatisticPara m_para;
};


