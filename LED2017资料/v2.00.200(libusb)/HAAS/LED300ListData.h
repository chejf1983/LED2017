// LED300ListData.h: interface for the CLED300ListData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LED300LISTDATA_H__6AB70801_04EA_11DB_949C_00055D02EEF1__INCLUDED_)
#define AFX_LED300LISTDATA_H__6AB70801_04EA_11DB_949C_00055D02EEF1__INCLUDED_

#include "LED300Data.h"
#include "OPSetupData.h"
#include <afxtempl.h>
#include "WhiteZone.h"
#include "LevelLimit.h"
#include "NewLEDClass.h"

#include "SortListCtrl.h"
#include "FailFlagData.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//class CHaasDatabase;

class CLED300ListData : public CObject  
{
public:
	void ReCalcLeve();
	static CFailFlagData m_failFlagData;

	BOOL Export_CSV_ALL(CString strPathName, float fInterval);
	int m_iPerCur;
	//得到分级字串
	CString GetWhite(int iCur);
	CString GetLevel(int iCur, COLORREF &color);
	//得到表
	static void GetList(int iPhType, BOOL bHaveSpect, int iList[], int &iN);
	//打印LED变化曲线报告
	void printLEDCurve(CDC *pDC,CRect printRect,int iPara[],int iSele);
	//画曲线
	void Draw_LEDCurve(CDC *pDC, CRect mRect,int iPara,int iSele,BOOL bPrint);
	//让所有测试信息一致
	void DoAllTestInfo();
	//文件管理
	BOOL Save(CString strPathName);
	BOOL Open(CString strPathName);
	//列表
	void LIST_Insert(CListCtrl &cList,int iSele);
	void ListHead(CListCtrl &cList);
	//打印数据表格
	void printListTable(CDC *pDC,CRect printRect,int iCurPage,int iMaxPage,int iB,CString strPathName,int PT_N);
	void Serialize(CArchive &ar);
	//导出所有数据Excel
	BOOL Export_CSV(CString strPathName);
	//清空
	void New();

	//光度或辐射度类型
	int   m_iPhType;
	//数据链表
	CTypedPtrArray<CObArray,CLED300Data*> m_listData;
	//选项设置参数
	COPSetupData m_opData;

	//分级依据
	CWhiteZone   m_xyZone;
	CLevelLimit  m_levelLimit;
	CNewLEDClass m_newClassLimit;

	CLED300ListData();
	virtual ~CLED300ListData();

};

#endif // !defined(AFX_LED300LISTDATA_H__6AB70801_04EA_11DB_949C_00055D02EEF1__INCLUDED_)
