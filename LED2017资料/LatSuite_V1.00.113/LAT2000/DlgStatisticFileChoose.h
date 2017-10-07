#pragma once
#include "LEDDataContainer.h"
#include "afxwin.h"

// CDlgStatisticFileChoose 对话框

class CDlgStatisticFileChoose : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgStatisticFileChoose)

public:
	CDlgStatisticFileChoose(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgStatisticFileChoose();

// 对话框数据
	enum { IDD = IDD_STATISTIC_FILE_CHOOSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonLoad();
    afx_msg void OnBnClickedButtonClear();
    CArray<CLEDDataContainer, CLEDDataContainer&>m_dataContainerArray;
    afx_msg void OnBnClickedOk();
    CArray<CString, CString>m_strFilePathArray;
    CString m_strFolderPath;
    CArray<CString, CString> m_strFileNameArray;
    void Relist();
    CListCtrl m_cList;
    CButton m_cDel;
    CButton m_cClear;
    afx_msg void OnBnClickedButtonDel();
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedButtonLoadTestsetdata();
    int m_iStatisticMode;
};
