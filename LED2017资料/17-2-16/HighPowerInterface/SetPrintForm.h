#if !defined(AFX_SETPRINTFORM_H__EC602110_5E99_495D_9406_47887B8D78FC__INCLUDED_)
#define AFX_SETPRINTFORM_H__EC602110_5E99_495D_9406_47887B8D78FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPrintForm.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\Barcode\Barcode.h"
/////////////////////////////////////////////////////////////////////////////
// CSetPrintForm dialog

class CSetPrintForm : public CResizingDialog
{
// Construction
public:
	CSetPrintForm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetPrintForm)
	enum { IDD = IDD_SetPrintForm };
	CEdit	m_posY9;
	CEdit	m_posY8;
	CEdit	m_posY7;
	CEdit	m_posY6;
	CEdit	m_posY5;
	CEdit	m_posY4;
	CEdit	m_posY3;
	CEdit	m_posY2;
	CEdit	m_posY10;
	CEdit	m_posY1;
	CEdit	m_posX9;
	CEdit	m_posX8;
	CEdit	m_posX7;
	CEdit	m_posX6;
	CEdit	m_posX5;
	CEdit	m_posX4;
	CEdit	m_posX3;
	CEdit	m_posX2;
	CEdit	m_posX10;
	CEdit	m_posX1;
	CButton	m_itemCheck9;
	CButton	m_namecode9;
	CButton	m_namecode8;
	CButton	m_namecode7;
	CButton	m_namecode6;
	CButton	m_namecode5;
	CButton	m_namecode4;
	CButton	m_namecode3;
	CButton	m_namecode2;
	CButton	m_namecode10;
	CButton	m_namecode1;
	CEdit	m_name9;
	CEdit	m_name8;
	CEdit	m_name7;
	CEdit	m_name6;
	CEdit	m_name5;
	CEdit	m_name4;
	CEdit	m_name3;
	CEdit	m_name2;
	CEdit	m_name10;
	CEdit	m_name1;
	CButton	m_itemCheck8;
	CButton	m_itemCheck7;
	CButton	m_itemCheck6;
	CButton	m_itemCheck5;
	CButton	m_itemCheck4;
	CButton	m_itemCheck3;
	CButton	m_itemCheck2;
	CButton	m_itemCheck10;
	CButton	m_itemCheck1;
	CButton	m_datacode9;
	CButton	m_datacode8;
	CButton	m_datacode7;
	CButton	m_datacode6;
	CButton	m_datacode5;
	CButton	m_datacode4;
	CButton	m_datacode3;
	CButton	m_datacode2;
	CButton	m_datacode10;
	CButton	m_datacode1;
	CComboBox	m_data9;
	CComboBox	m_data8;
	CComboBox	m_data7;
	CComboBox	m_data6;
	CComboBox	m_data5;
	CComboBox	m_data4;
	CComboBox	m_data3;
	CComboBox	m_data2;
	CComboBox	m_data10;
	CComboBox	m_data1;
	CComboBox	cmb_Style;
	//}}AFX_DATA

	CWnd *pWnd_picture; 
	CDC *pDC_picture;
	RECT rect; 
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetPrintForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetPrintForm)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnprintPreview();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void P_DrawBarCode(CDC*pDC,const BOOL bPrint);
	bool InitCombo(CComboBox *combo);
	bool InitControls();
	bool getPrintSet();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETPRINTFORM_H__EC602110_5E99_495D_9406_47887B8D78FC__INCLUDED_)
