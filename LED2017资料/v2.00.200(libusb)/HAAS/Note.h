#if !defined(AFX_NOTE_H__08DE1897_5E85_11D2_8ABB_D78FD9126220__INCLUDED_)
#define AFX_NOTE_H__08DE1897_5E85_11D2_8ABB_D78FD9126220__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Note.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNote window

class CNote : public CStatic
{
// Construction
public:
	CNote();
	virtual void PostNcDestroy();
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNote)
	//}}AFX_VIRTUAL

// Implementation
public:
	static CNote * c_Note;
	static void Passtext(CString String);
	static void Draw();
	void Hide();
	static void Destroy();
	static void Show(CWnd * pParentWnd=NULL);
	virtual ~CNote();

	// Generated message map functions
protected:
	static CString m_String;
	BOOL Create(CWnd * pParentWnd=NULL);
	//{{AFX_MSG(CNote)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTE_H__08DE1897_5E85_11D2_8ABB_D78FD9126220__INCLUDED_)
