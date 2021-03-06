#if !defined(AFX__COLUMN_H__917A22CB_89FA_4825_BD9B_4E366FF6552D__INCLUDED_)
#define AFX__COLUMN_H__917A22CB_89FA_4825_BD9B_4E366FF6552D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// C_Column wrapper class

class C_Column : public COleDispatchDriver
{
public:
	C_Column() {}		// Calls COleDispatchDriver default constructor
	C_Column(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	C_Column(const C_Column& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetAlignment();
	void SetAlignment(long nNewValue);
	short GetDecimalLength();
	void SetDecimalLength(short nNewValue);
	BOOL GetLocked();
	void SetLocked(BOOL bNewValue);
	long GetMask();
	void SetMask(long nNewValue);
	long GetSearchMethod();
	void SetSearchMethod(long nNewValue);
	short GetMaxLength();
	void SetMaxLength(short nNewValue);
	long GetCellType();
	void SetCellType(long nNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	CString GetFormatString();
	void SetFormatString(LPCTSTR lpszNewValue);
	long GetUserSortIndicator();
	void SetUserSortIndicator(long nNewValue);
	void SetPosition(long nNewValue);
	void Sort(long Order);
	void AutoFit();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX__COLUMN_H__917A22CB_89FA_4825_BD9B_4E366FF6552D__INCLUDED_)
