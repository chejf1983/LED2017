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
	//�õ��ּ��ִ�
	CString GetWhite(int iCur);
	CString GetLevel(int iCur, COLORREF &color);
	//�õ���
	static void GetList(int iPhType, BOOL bHaveSpect, int iList[], int &iN);
	//��ӡLED�仯���߱���
	void printLEDCurve(CDC *pDC,CRect printRect,int iPara[],int iSele);
	//������
	void Draw_LEDCurve(CDC *pDC, CRect mRect,int iPara,int iSele,BOOL bPrint);
	//�����в�����Ϣһ��
	void DoAllTestInfo();
	//�ļ�����
	BOOL Save(CString strPathName);
	BOOL Open(CString strPathName);
	//�б�
	void LIST_Insert(CListCtrl &cList,int iSele);
	void ListHead(CListCtrl &cList);
	//��ӡ���ݱ��
	void printListTable(CDC *pDC,CRect printRect,int iCurPage,int iMaxPage,int iB,CString strPathName,int PT_N);
	void Serialize(CArchive &ar);
	//������������Excel
	BOOL Export_CSV(CString strPathName);
	//���
	void New();

	//��Ȼ���������
	int   m_iPhType;
	//��������
	CTypedPtrArray<CObArray,CLED300Data*> m_listData;
	//ѡ�����ò���
	COPSetupData m_opData;

	//�ּ�����
	CWhiteZone   m_xyZone;
	CLevelLimit  m_levelLimit;
	CNewLEDClass m_newClassLimit;

	CLED300ListData();
	virtual ~CLED300ListData();

};

#endif // !defined(AFX_LED300LISTDATA_H__6AB70801_04EA_11DB_949C_00055D02EEF1__INCLUDED_)
