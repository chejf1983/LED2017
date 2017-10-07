#pragma once


// CPageSDCM 对话框

class CPageSDCM : public CDialogEx
{
	DECLARE_DYNAMIC(CPageSDCM)

public:
	CPageSDCM(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPageSDCM();

// 对话框数据
	enum { IDD = IDD_SDCM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnPaint();
private:
    CBrush m_brush;
    float m_fCIE_x;
    float m_fCIE_y;
public:    
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    void ReDraw(float fCIE_x, float fCIE_y);
    virtual BOOL OnInitDialog();
};
