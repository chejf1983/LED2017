// FailFlagData.h: interface for the CFailFlagData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FAILFLAGDATA_H__D6A8DEA9_BEEC_4BCC_9A9E_D818695D08F9__INCLUDED_)
#define AFX_FAILFLAGDATA_H__D6A8DEA9_BEEC_4BCC_9A9E_D818695D08F9__INCLUDED_

#include "LimitData.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFailFlagData  
{
public:
	int GetListTypeNum();
	const static int NONE_DATA;

	CFailFlagData();
	virtual ~CFailFlagData();

	void ClearAll();

	void AddListPara(int iType);
	void SetDataLineNum(int iDataLineNum);
	void AddLineFailDataType(int iSeleLine, int iType);

	BOOL IsFail(int iSeleLine, int iSeleList) const;

	BOOL m_bModifyLisType;

private:
	CArray<int, int> m_iListDataType;

	// ����������
	int m_iLineNum;
	// ÿһ�в��ϸ�����Ĳ���
	CArray<int, int> *m_pFailData;
};

#endif // !defined(AFX_FAILFLAGDATA_H__D6A8DEA9_BEEC_4BCC_9A9E_D818695D08F9__INCLUDED_)
