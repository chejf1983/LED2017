// SelfCorrectData.h: interface for the CSelfCorrectData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SELFCORRECTDATA_H__312D8F51_2C80_42C8_846D_75E52F679866__INCLUDED_)
#define AFX_SELFCORRECTDATA_H__312D8F51_2C80_42C8_846D_75E52F679866__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSelfCorrectData : public CObject  
{
public:
	BOOL Open(CString strPathName);
	BOOL Save(CString strPathName);

	void Serialize(CArchive &ar);
	CSelfCorrectData();
	virtual ~CSelfCorrectData();

	int m_iType;

	int m_iSaveTestNum;
	float m_fSave_TestWL[4001];
	float m_fSave_TestPL[4001];

	int m_iSaveRefNum;
	float m_fSave_RefWL[4001];
	float m_fSave_RefPL[4001];
};

#endif // !defined(AFX_SELFCORRECTDATA_H__312D8F51_2C80_42C8_846D_75E52F679866__INCLUDED_)
