#pragma once


// CCurrentBoardID_Dlg 对话框

class CCurrentBoardID_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCurrentBoardID_Dlg)

public:
	CCurrentBoardID_Dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCurrentBoardID_Dlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_CURRENT_BOARD_INDEX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    UINT m_iCurrentBoardID;
	int m_iLEDOnPos;
	int m_iTestHaveScanedMode;
};
