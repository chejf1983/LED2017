#pragma once
#include "afxwin.h"


// CCurrentLEDID_Dlg 对话框

class CCurrentLEDID_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCurrentLEDID_Dlg)

public:
	CCurrentLEDID_Dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCurrentLEDID_Dlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_LED_CURRENT_INDEX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    int m_iCurrentLEDID;
};
