// SDCM.h: interface for the SDCM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDCM_H__B8B65E62_886A_11D8_A0D0_00055D02EEF1__INCLUDED_)
#define AFX_SDCM_H__B8B65E62_886A_11D8_A0D0_00055D02EEF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SDCM : public CObject  
{
public:
	CString m_strName;
	float  m_fx,m_fy;              //陏圆中心
	float  m_fxs,m_fys;            //起始x,y作图用
	float  m_fg11,m_fg12,m_fg22;   //陏圆的描述参数

	SDCM();
	virtual ~SDCM();

};

#endif // !defined(AFX_SDCM_H__B8B65E62_886A_11D8_A0D0_00055D02EEF1__INCLUDED_)
