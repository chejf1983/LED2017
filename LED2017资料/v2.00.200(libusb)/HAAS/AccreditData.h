// AccreditData.h: interface for the CAccreditData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCREDITDATA_H__C533CDEA_25FA_4B39_8B26_4D380109E594__INCLUDED_)
#define AFX_ACCREDITDATA_H__C533CDEA_25FA_4B39_8B26_4D380109E594__INCLUDED_

#include <afxtempl.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAccreditData : public CObject  
{
public:
	CString GetTimeStr() const;
	int GetTimeNum();
	static void Name2NewName(char szName[], char szNewName[]);
	void Serialize(CArchive &ar);
	void SetTimeT12(CTime time1,CTime time2);
	void GetTimeT12(CTime &time1,CTime &time2);

	CAccreditData();
	virtual ~CAccreditData();

	void ClearAllTime();
	void Add(CTime time);
	BOOL CanUse();

	BOOL Open(CString strPathName);
	BOOL Save(CString strPathName);

private:
	CArray<CTime, CTime> m_time;
	CTime m_timeSetT1;
	CTime m_timeSetT2;
};

#endif // !defined(AFX_ACCREDITDATA_H__C533CDEA_25FA_4B39_8B26_4D380109E594__INCLUDED_)
