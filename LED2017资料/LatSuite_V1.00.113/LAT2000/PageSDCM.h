#pragma once


// CPageSDCM �Ի���

class CPageSDCM : public CDialogEx
{
	DECLARE_DYNAMIC(CPageSDCM)

public:
	CPageSDCM(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPageSDCM();

// �Ի�������
	enum { IDD = IDD_SDCM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
