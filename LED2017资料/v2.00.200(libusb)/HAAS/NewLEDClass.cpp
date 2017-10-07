// NewLEDClass.cpp: implementation of the CNewLEDClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "NewLEDClass.h"
#include "DlgLEDClassSetPara.h"
#include "DlgLEDClassDataEdit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern BOOL g_bEnglish;

int CNewLEDClass::m_iTempTypeNum = 0;
int CNewLEDClass::m_iTempType[100];

CNewLEDClass::CNewLEDClass()
{
}

CNewLEDClass::~CNewLEDClass()
{
}

//
// 共有几组分类
//
int CNewLEDClass::GetClassNum()
{
	return m_classData.GetSize();
}

void CNewLEDClass::ListData(CListCtrl &cList)
{	
	cList.DeleteAllItems();
	while(1)
	{
		if(cList.DeleteColumn(0)==FALSE)
			break;
	}
	
	int i,j;
	CString strTemp;
	
	int iN = 0;
	cList.InsertColumn(iN," SN.");
	cList.SetColumnWidth(iN,60);
	iN++;

	if(g_bEnglish)
		strTemp = "Name";
	else
		strTemp = "名称";
	cList.InsertColumn(iN,strTemp);	
	cList.SetColumnWidth(iN,120);
	iN++;

	for(i=0;i<m_iType.GetSize();i++)
	{
		strTemp = CLimitData::Type2NameStr(m_iType[i]);
		cList.InsertColumn(iN,strTemp);	
		cList.SetColumnWidth(iN,100);
		iN++;
	}
	
	for(i=0;i<m_classData.GetSize();i++)
	{
		iN = 0;
		strTemp.Format("%4d",i+1);
		cList.InsertItem(i,strTemp,2);
		iN++;

		strTemp = m_classData[i]->m_strName;
		cList.SetItemText(i,iN,strTemp);
		iN++;
	
		for(j=0;j<m_iType.GetSize();j++)
		{
			strTemp.Format("%g - %g",m_classData[i]->m_fLimit1[j],m_classData[i]->m_fLimit2[j]);
			cList.SetItemText(i,iN,strTemp);
			iN++;
		}
	}
}

BOOL CNewLEDClass::EditDataPara()
{
	// 先清空分类数据
	m_classData.RemoveAll();

	// 再编辑参数类型
	CDlgLEDClassSetPara dlg;
	dlg.m_pClassData  = this;
	dlg.DoModal();

	return TRUE;
}

void CNewLEDClass::ListDataPara(CListBox &list)
{
	list.ResetContent();
	for(int i = 0; i < m_iType.GetSize(); i++)
		list.InsertString(i,CLimitData::Type2NameStr(m_iType[i]));
}

BOOL CNewLEDClass::Add_DataType(int iType)
{
	m_iType.Add(iType);
	return TRUE;
}

BOOL CNewLEDClass::Del_DataType(int iSele)
{
	if(iSele >=0 && iSele < m_iType.GetSize())
	{
		m_iType.RemoveAt(iSele);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CNewLEDClass::Add_Class()
{
	int i;
	CDlgLEDClassDataEdit dlg;
	
	for(i = 0; i < m_iType.GetSize(); i++)
	{
		dlg.m_iListType.Add(m_iType[i]);
		dlg.m_fLimit1.Add(0);
		dlg.m_fLimit2.Add(0);
	}

	if(dlg.DoModal()==IDCANCEL)
		return FALSE;

	CNewLEDClassData *pData = new CNewLEDClassData();
	pData->m_fLimit1.Copy(dlg.m_fLimit1);
	pData->m_fLimit2.Copy(dlg.m_fLimit2);
	pData->m_strName = dlg.m_strName;
	pData->m_color = dlg.m_color;

	m_classData.Add(pData);
	return TRUE;
}

BOOL CNewLEDClass::Del_Class(int iSele)
{
	if(iSele >=0 && iSele < m_classData.GetSize())
	{

		CNewLEDClassData *pData = m_classData.GetAt(iSele);
		m_classData.RemoveAt(iSele);
		delete pData;
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CNewLEDClass::Mod_Class(int iSele)
{
	if(iSele >=0 && iSele < m_classData.GetSize())
	{
		int i;
		CDlgLEDClassDataEdit dlg;
		
		for(i = 0; i < m_iType.GetSize(); i++)
		{
			dlg.m_iListType.Add(m_iType[i]);
			dlg.m_fLimit1.Add(m_classData[iSele]->m_fLimit1[i]);
			dlg.m_fLimit2.Add(m_classData[iSele]->m_fLimit2[i]);
		}
		
		dlg.m_strName = m_classData[iSele]->m_strName;
		dlg.m_color = m_classData[iSele]->m_color;

		if(dlg.DoModal()==IDCANCEL)
			return FALSE;
		
		CNewLEDClassData *pData = m_classData[iSele];
		pData->m_fLimit1.Copy(dlg.m_fLimit1);
		pData->m_fLimit2.Copy(dlg.m_fLimit2);
		pData->m_strName = dlg.m_strName;
		m_classData[iSele]->m_color = dlg.m_color;

		return TRUE;
	}
	else
		return FALSE;
}

BOOL CNewLEDClass::Export_CSV(CString strPathName)
{
	FILE *fp;
	if((fp=fopen(strPathName,"wt"))==0)
		return FALSE;
	else
	{
		int i,j;
		CString strTemp;

		strTemp = "Class Name";
		fprintf(fp,"\"%s\",",strTemp);

		for(i=0;i<m_iType.GetSize();i++)
		{
			strTemp = CLimitData::Type2NameStr(m_iType[i]);
			fprintf(fp,"\"%s\",",strTemp);

			strTemp = "";
			fprintf(fp,"\"%s\",",strTemp);
		}
		fprintf(fp,"\n");
		
		for(i=0;i<m_classData.GetSize();i++)
		{
			strTemp = m_classData[i]->m_strName;
			fprintf(fp,"\"%s\",",strTemp);
			
			for(j=0;j<m_iType.GetSize();j++)
			{
				strTemp.Format("%g",m_classData[i]->m_fLimit1[j]);
				fprintf(fp,"\"%s\",",strTemp);

				strTemp.Format("%g",m_classData[i]->m_fLimit2[j]);
				fprintf(fp,"\"%s\",",strTemp);
			}
			fprintf(fp,"\n");
		}
		fclose(fp);
	}
	return TRUE;
}

void CNewLEDClass::Serialize(CArchive &ar)
{
	CString strVer;
	int i,iN;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		strVer="CNewLEDClass_A";
		ar<<strVer;

		iN = m_iType.GetSize();
		ar<<iN;

		for(i = 0; i < iN; i++)
			ar<<m_iType[i];

		iN = m_classData.GetSize();
		ar<<iN;
		
		for(i = 0; i < iN; i++)
			m_classData[i]->Serialize(ar);
	}
	else
	{
		ar>>strVer;
		if(strVer!="CNewLEDClass_A")
			return;

		ar>>iN;
		m_iType.RemoveAll();
		for(i = 0; i < iN; i++)
		{
			int iType;
			ar>>iType;
			m_iType.Add(iType);
		}

		ar>>iN;
		m_classData.RemoveAll();
		for(i = 0; i < iN; i++)
		{
			CNewLEDClassData *pData = new CNewLEDClassData();
			pData->Serialize(ar);
			m_classData.Add(pData);
		}
	}
}

BOOL CNewLEDClass::NC_Load(CString strPathName)
{
	CFile oFile;
	if(!oFile.Open(strPathName,CFile::modeRead))
	{
		if(g_bEnglish)
			AfxMessageBox("Can not open!\n\n"+strPathName,MB_ICONSTOP);
		else
			AfxMessageBox("不能打开文件!\n\n"+strPathName,MB_ICONSTOP);
		return FALSE;
	}
    CArchive ar(&oFile,CArchive::load);
	Serialize(ar);
	ar.Close();
	oFile.Close();
	
	return TRUE;
	
}

BOOL CNewLEDClass::NC_Save(CString strPathName)
{
	CFile sFile;
	if(!sFile.Open(strPathName,CFile::modeCreate|CFile::modeReadWrite))
	{
		if(g_bEnglish)
			AfxMessageBox("Can not save file!",MB_ICONSTOP);
		else
			AfxMessageBox("不能保存文件!",MB_ICONSTOP);
		return FALSE;
	}
    CArchive ar(&sFile,CArchive::store);
	Serialize(ar);
	ar.Close();
	sFile.Close();
	
	return TRUE;
}

CString CNewLEDClass::GetLevel(CLED300Data &data, int iPhType, COLORREF &color)
{
	m_iTempTypeNum = 0;
	color = RGB(192, 192, 192);
	if(m_iType.GetSize() <= 0)
	{
		return "";
	}

	float fData;
	for(int i = 0; i < m_classData.GetSize(); i++)
	{
		m_iTempTypeNum = 0;

		BOOL bNotHaveAllData = FALSE;
		BOOL bPass = TRUE;
		for(int j = 0; j < m_classData[i]->m_fLimit1.GetSize(); j++)
		{
			if(CLevelLimit::GetData(m_iType[j], data, iPhType, fData) == TRUE)
			{
				if(fData >= m_classData[i]->m_fLimit1[j] && fData <= m_classData[i]->m_fLimit2[j])
				{

				}
				else
				{

					bPass = FALSE;
					m_iTempType[m_iTempTypeNum] = m_iType[j];
					m_iTempTypeNum++;

					// break;
				}
			}
			else
			{
				bNotHaveAllData = TRUE;
				// return "---";
			}
		}

		if(bNotHaveAllData == TRUE)
			return "---";

		if(bPass == TRUE)
		{
			color = m_classData[i]->m_color; 
			return m_classData[i]->m_strName;
		}
	}

	return "OUT";
}
