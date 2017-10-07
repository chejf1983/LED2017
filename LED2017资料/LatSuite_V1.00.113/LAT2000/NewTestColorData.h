// NewTestColorData.h: interface for the CNewTestColorData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEWTESTCOLORDATA_H__72F7C395_26E3_4F0F_A03A_ECAD69A70DFF__INCLUDED_)
#define AFX_NEWTESTCOLORDATA_H__72F7C395_26E3_4F0F_A03A_ECAD69A70DFF__INCLUDED_

#include <afxtempl.h>
//#include "Definition.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class __declspec(dllexport) CNewTestColorData : public CObject  
{
public:
	CNewTestColorData();
//	CNewTestColorData(NewTestColorData & data);
	virtual ~CNewTestColorData();

	CNewTestColorData & operator=(CNewTestColorData & data);
//	void GetData(NewTestColorData & data);

	BOOL m_bHaveColorData;

	float m_fPh;
	float m_fPh_e;

	float m_fCIEx;
	float m_fCIEy;
	float m_fCIEu_;
	float m_fCIEv_;
	float m_fTc;
	float m_fduv;
	float m_fLp;
	float m_fHW;
	float m_fLd;
	float m_fLav;
	float m_fPur;
	float m_fRR;
	float m_fGR;
	float m_fBR;
	float m_fRa;
	float m_fRi[15];

	float m_fWL1;
	float m_fWL2;
	float m_fIntervalWL;

	float m_fAbsPL_K;
	float m_fIntTime;
	float m_fIp;
	float m_fIp_removeDark;

	float m_fPL[4096];
	int	  m_iPLLength;
};

#endif // !defined(AFX_NEWTESTCOLORDATA_H__72F7C395_26E3_4F0F_A03A_ECAD69A70DFF__INCLUDED_)
