// MusterType.h: interface for the CMusterType class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUSTERTYPE_H__A735D941_2F9C_11DC_B6B8_000D87C8DDE3__INCLUDED_)
#define AFX_MUSTERTYPE_H__A735D941_2F9C_11DC_B6B8_000D87C8DDE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMusterType : public CObject  //当前测试的典型数据
{
public:
	CMusterType& operator =(const CMusterType &MtData);
	void Copy(const CMusterType &MtData);
	void Serialize(CArchive &ar);

	void Init();

	CString m_strName;
	CArray<float,float> m_fRefS;
	CArray<float,float> m_fRefQ;

	CMusterType();
	virtual ~CMusterType();

};

#endif // !defined(AFX_MUSTERTYPE_H__A735D941_2F9C_11DC_B6B8_000D87C8DDE3__INCLUDED_)
