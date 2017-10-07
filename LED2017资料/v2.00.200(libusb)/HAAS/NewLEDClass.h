// NewLEDClass.h: interface for the CNewLEDClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEWLEDCLASS_H__62ABE225_F321_4B0B_982A_6FB8646A262E__INCLUDED_)
#define AFX_NEWLEDCLASS_H__62ABE225_F321_4B0B_982A_6FB8646A262E__INCLUDED_

#include "afxtempl.h"
#include "NewLEDClassData.h"
// #include "DlgLEDClassSetPara.h"
#include "LevelLimit.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDlgLEDClassSetPara;

class CNewLEDClass : public CObject  
{
public:
	CString GetLevel(CLED300Data &data,int iPhType, COLORREF &color);
	BOOL Export_CSV(CString strPathName);
	BOOL Mod_Class(int iSele);
	BOOL Del_Class(int iSele);
	BOOL Add_Class();
	BOOL Del_DataType(int iSele);
	BOOL Add_DataType(int iType);
	void ListDataPara(CListBox &list);
	BOOL EditDataPara();
	friend class CDlgLEDClassSetPara;

	void Serialize(CArchive &ar);

	BOOL NC_Load(CString strPathName);
	BOOL NC_Save(CString strPathName);

	void ListData(CListCtrl &list);
	int GetClassNum();
	CNewLEDClass();
	virtual ~CNewLEDClass();

	static int m_iTempTypeNum;
	static int m_iTempType[100];

private:
	CTypedPtrArray<CObArray,CNewLEDClassData*>  m_classData;
	CArray<int,int> m_iType;

};

#endif // !defined(AFX_NEWLEDCLASS_H__62ABE225_F321_4B0B_982A_6FB8646A262E__INCLUDED_)
