// LED300Data.h: interface for the CLED300Data class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LED300DATA_H__BB5026E1_0290_11DB_949C_00055D02EEF1__INCLUDED_)
#define AFX_LED300DATA_H__BB5026E1_0290_11DB_949C_00055D02EEF1__INCLUDED_

#include "SpectData.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLED300Data : public CObject  
{
public:
	CString GetFormatData();
	void Init();
	void Serialize(CArchive& ar);
	void Copy(const CLED300Data &Data);
	CLED300Data& operator =(const CLED300Data &Data);

	CSpectData m_spData;
	CLED300Data();
	virtual ~CLED300Data();

};

#endif // !defined(AFX_LED300DATA_H__BB5026E1_0290_11DB_949C_00055D02EEF1__INCLUDED_)
