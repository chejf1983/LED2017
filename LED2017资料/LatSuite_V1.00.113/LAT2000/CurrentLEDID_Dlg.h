#pragma once
#include "afxwin.h"


// CCurrentLEDID_Dlg �Ի���

class CCurrentLEDID_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCurrentLEDID_Dlg)

public:
	CCurrentLEDID_Dlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCurrentLEDID_Dlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_LED_CURRENT_INDEX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    int m_iCurrentLEDID;
};
