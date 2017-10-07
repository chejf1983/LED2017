#pragma once


// CDlgListParaChoose 对话框

class CDlgListParaChoose : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgListParaChoose)

public:
	CDlgListParaChoose(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgListParaChoose();

// 对话框数据
	enum { IDD = IDD_LIST_PARA_CHOOSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
    int m_iNotSN[PARA_NUM];
    BOOL m_bNotSNSel[PARA_NUM];
    int m_iNotNum;

    int m_iYesSN[PARA_NUM];
    BOOL m_bYesSNSel[PARA_NUM];
    int m_iYesNum;
    void RelistNot();
    void RelistYes();

    CButton m_cAdd;
    CButton m_cRemove;
    CListBox m_cListNot;
    CListBox m_cListYes;
    void EnableButton(void);
    afx_msg void OnBnClickedAdd();
    afx_msg void OnBnClickedRemove();
    afx_msg void OnLbnSelchangeListNot();
    afx_msg void OnLbnSelchangeListYes();
public:
    virtual BOOL OnInitDialog();

    afx_msg void OnBnClickedButtonAll();
    afx_msg void OnBnClickedButtonNot();

};
