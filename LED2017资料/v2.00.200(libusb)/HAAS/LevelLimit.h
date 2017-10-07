// LevelLimit.h: interface for the CLevelLimit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEVELLIMIT_H__62D6FC81_37D1_11DA_ABAD_00055D02EEF1__INCLUDED_)
#define AFX_LEVELLIMIT_H__62D6FC81_37D1_11DA_ABAD_00055D02EEF1__INCLUDED_

#include "LimitData.h"
#include "LED300Data.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLevelLimit : public CObject  
{
public:
	static BOOL GetData(int iDataType,CLED300Data &data,int iPhType,float &fData);
	BOOL Open(CString sPathName);
	BOOL Save(CString sPathName);
	CString GetLevel(CLED300Data &data,int iPhType);
	int SelePara();
	BOOL AddLimitPara();
	BOOL DelLimitPara(int iSele=-1);
	BOOL EditLimitPara(int iSele=-1);

	void Copy(const CLevelLimit &levelData);
	CLevelLimit& operator =(const CLevelLimit &levelData);

	//各参数的上下限
	CTypedPtrArray<CObArray,CLimitData*>  m_arraLevelLimit;

	void Init();
	void Serialize(CArchive& ar);
	CLevelLimit();
	virtual ~CLevelLimit();

};

#endif // !defined(AFX_LEVELLIMIT_H__62D6FC81_37D1_11DA_ABAD_00055D02EEF1__INCLUDED_)
