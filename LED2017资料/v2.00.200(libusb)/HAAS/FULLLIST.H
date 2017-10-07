#if !defined(AFX_FULLLIST_H__A6DF87D5_F235_11D0_BC98_00400526DBEA__INCLUDED_)
#define AFX_FULLLIST_H__A6DF87D5_F235_11D0_BC98_00400526DBEA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FullList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFullList window

class CFullList : public CListCtrl
{
// Construction
public:
        CFullList();

// Attributes
public:

// Operations
public:

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CFullList)
        //}}AFX_VIRTUAL

// Implementation
public:
        virtual ~CFullList();

        // Generated message map functions
protected:
        void GoMargin(UINT &nFlags,CPoint &point);
        //{{AFX_MSG(CFullList)
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
        afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
        afx_msg void OnPaint();
        //}}AFX_MSG

        DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FULLLIST_H__A6DF87D5_F235_11D0_BC98_00400526DBEA__INCLUDED_)
