#pragma once


// CCurrentBoardID_Dlg �Ի���

class CCurrentBoardID_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCurrentBoardID_Dlg)

public:
	CCurrentBoardID_Dlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCurrentBoardID_Dlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_CURRENT_BOARD_INDEX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    UINT m_iCurrentBoardID;
	int m_iLEDOnPos;
	int m_iTestHaveScanedMode;
};
