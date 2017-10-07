// LimitData.h: interface for the CLimitData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIMITDATA_H__62D6FC82_37D1_11DA_ABAD_00055D02EEF1__INCLUDED_)
#define AFX_LIMITDATA_H__62D6FC82_37D1_11DA_ABAD_00055D02EEF1__INCLUDED_

#include <afxtempl.h>

// 参数类型
#define   TD_VF       0    //V
#define   TD_IF       1    //mA
#define   TD_P        2    //mW
#define   TD_VR       3    //V
#define   TD_IR       4    //uA
#define   TD_F        5    //lm
#define   TD_I        6    //cd
#define   TD_L        7    //cd/m2
#define   TD_Fe       8    //W
#define   TD_Ie       9    //W/Sr
#define   TD_Le       10   //W/m2/Sr
#define   TD_X        11
#define   TD_Y        12
#define   TD_U        13   
#define   TD_V        14
#define   TD_CCT      15    //色温
#define   TD_LD       16    //主波长 lambda d
#define   TD_LP       17   //峰波长 lambda p
#define   TD_PUR      18   //色纯度
#define   TD_RA       19   //显色性指数
#define   TD_EFF      20   //Eff
#define   TD_dC       21   //dC

#define   TD_E        22   // E
#define   TD_Ee       23   // Ee

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLimitData : public CObject  
{
public:
	static CString Type2NameStr(int iDataType);
	static void GetName(CArray<CString,CString> &strName,CArray<int,int> &iType);
	void FastLevel();
	CString GetTypeName();

	void Copy(const CLimitData &limitData);
	CLimitData& operator =(const CLimitData &limitData);

	void Serialize(CArchive &ar);
	void Init();
	//参数类型
	int m_iDataType;

	//参数分级点
	int   m_iN;
	float m_fLevel1[10];
	float m_fLevel2[10];

	CLimitData();
	virtual ~CLimitData();

};

#endif // !defined(AFX_LIMITDATA_H__62D6FC82_37D1_11DA_ABAD_00055D02EEF1__INCLUDED_)
