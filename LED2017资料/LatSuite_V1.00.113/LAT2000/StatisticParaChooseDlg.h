#pragma once


// CStatisticParaChooseDlg �Ի���

class CStatisticParaChooseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStatisticParaChooseDlg)

public:
	CStatisticParaChooseDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStatisticParaChooseDlg();

// �Ի�������
	enum { IDD = IDD_STATISTIC_PARA_CHOOSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    CButton m_cAdd;
    CButton m_cRemove;
    CListBox m_cListNot;
    CListBox m_cListYes;
    void RelistNot();
    void RelistYes();
    afx_msg void OnBnClickedAdd();
    afx_msg void OnBnClickedRemove();
    afx_msg void OnLbnSelchangeListNot();
    afx_msg void OnLbnSelchangeListYes();
private:
    int m_iNotSN[50];
    BOOL m_bNotSNSel[50];
    int m_iNotNum;

    int m_iYesSN[50];
    BOOL m_bYesSNSel[50];
    int m_iYesNum;
public:
    void EnableButton(void);
	afx_msg void OnBnClickedButtonAll();
	afx_msg void OnBnClickedButtonNot();
};
