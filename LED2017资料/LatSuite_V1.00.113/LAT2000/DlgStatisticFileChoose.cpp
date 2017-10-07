// DlgStatisticFileChoose.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DlgStatisticFileChoose.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"
#include "EditLimitDlg.h"
// CDlgStatisticFileChoose 对话框

IMPLEMENT_DYNAMIC(CDlgStatisticFileChoose, CDialogEx)

CDlgStatisticFileChoose::CDlgStatisticFileChoose(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgStatisticFileChoose::IDD, pParent)
{
    m_strFilePathArray.RemoveAll();
    m_strFileNameArray.RemoveAll();
    m_dataContainerArray.RemoveAll();
    CString strSection = "DlgStatisticFileChoose";
    CString str_m_strFolderPath = _T("m_strFolderPath");

    m_strFolderPath = AfxGetApp()->GetProfileString(strSection, str_m_strFolderPath, _T("LAT-2000"));
    m_iStatisticMode = 0;

}

CDlgStatisticFileChoose::~CDlgStatisticFileChoose()
{
    CString strSection = "DlgStatisticFileChoose";
    CString str_m_strFolderPath = _T("m_strFolderPath");

    AfxGetApp()->WriteProfileString(strSection, str_m_strFolderPath, m_strFolderPath);

    m_strFilePathArray.RemoveAll();
    m_strFileNameArray.RemoveAll();
    m_dataContainerArray.RemoveAll();
}

void CDlgStatisticFileChoose::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_STATISTIC_FILE, m_cList);
    DDX_Control(pDX, IDC_BUTTON_DEL, m_cDel);
    DDX_Control(pDX, IDC_BUTTON_CLEAR, m_cClear);
    DDX_Radio(pDX, IDC_RADIO_LED_ON_ALL, m_iStatisticMode);
}


BEGIN_MESSAGE_MAP(CDlgStatisticFileChoose, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_LOAD, &CDlgStatisticFileChoose::OnBnClickedButtonLoad)
    ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CDlgStatisticFileChoose::OnBnClickedButtonClear)
    ON_BN_CLICKED(IDOK, &CDlgStatisticFileChoose::OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_DEL, &CDlgStatisticFileChoose::OnBnClickedButtonDel)
    ON_BN_CLICKED(IDC_BUTTON_LOAD_TESTSETDATA, &CDlgStatisticFileChoose::OnBnClickedButtonLoadTestsetdata)
END_MESSAGE_MAP()


// CDlgStatisticFileChoose 消息处理程序


void CDlgStatisticFileChoose::OnBnClickedButtonLoad()
{
    // TODO: 在此添加控件通知处理程序代码
    CFileDialog dlg(TRUE, "lat2000-everfine", m_strFolderPath,
        OFN_EXPLORER | OFN_ENABLEHOOK | OFN_ALLOWMULTISELECT, "nLAT2000 Files(*.lat2000-everfine)|*.lat2000-everfine|");
    CString fileName;
    const int c_cMaxFiles = 4000;
    const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
    dlg.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
    dlg.GetOFN().nMaxFile = c_cMaxFiles;

    if (IDCANCEL == dlg.DoModal())
    {    
        return;
    }
    POSITION pos = dlg.GetStartPosition();
    CString strTemp;
    CArray<CString, CString> strFileNameArray;
    CArray<CString, CString> strFilePathArray;
beg:     while(pos)
    {
        strTemp = dlg.GetNextPathName(pos);
        for (int i = 0; i < m_strFilePathArray.GetSize(); i ++)
        {
            if (strTemp == m_strFilePathArray.GetAt(i))
            {
                goto beg;
            }
        }
        strFilePathArray.Add(strTemp);
        m_strFolderPath = strTemp;
        for (int i = strTemp.GetLength(); i > 0; i --)
        {
            if (strTemp.GetAt(i) == '\\')
            {
                strTemp = strTemp.Right(strTemp.GetLength() - i - 1); 
                strFileNameArray.Add(strTemp);
                break;
            }
        }

    }
    CArray<int, int>m_iExpect;
    m_iExpect.SetSize(strFileNameArray.GetSize());
    int iExpectNum = 0;
    int iModelUnExpect1Num = 0;
    int iStaValUnExpect1Num = 0;
    for (int i = 0; i < strFileNameArray.GetSize(); i ++)
    {
        m_iExpect[i] = 0;
        CLEDDataContainer *pTemp = new CLEDDataContainer;
        pTemp->LoadFile(strFilePathArray.GetAt(i));
        if (pTemp->GetTestSettingData().m_strLedModel 
            != g_pDoc->m_StatisticLedDataContainer.GetTestSettingData().m_strLedModel)
        {
            iModelUnExpect1Num ++;
            m_iExpect[i] = 1;
            continue;
        }

        if (pTemp->GetTestSettingData().m_fStaFlux 
            != g_pDoc->m_StatisticLedDataContainer.GetTestSettingData().m_fStaFlux
            ||pTemp->GetTestSettingData().m_fStaPow 
            != g_pDoc->m_StatisticLedDataContainer.GetTestSettingData().m_fStaPow
            ||pTemp->GetTestSettingData().m_fStaTc 
            != g_pDoc->m_StatisticLedDataContainer.GetTestSettingData().m_fStaTc
            ||pTemp->GetTestSettingData().m_fStaVol 
            != g_pDoc->m_StatisticLedDataContainer.GetTestSettingData().m_fStaVol)
        {
            iStaValUnExpect1Num ++;
            m_iExpect[i] = 2;
            continue;
        }

        m_strFilePathArray.Add(strFilePathArray.GetAt(i));
        m_strFileNameArray.Add(strFileNameArray.GetAt(i));
        m_dataContainerArray.Add(*pTemp);
        iExpectNum ++;
    }

    if (iStaValUnExpect1Num)
    {
        strTemp.Format("灯型号相同但标称值不同的文件数有%d个，是否添加到统计文件列表并进行参数统计?", iStaValUnExpect1Num);
        if (IDOK == MessageBox(strTemp, "Warning", MB_OKCANCEL))
        {
            for (int i = 0; i < strFileNameArray.GetSize(); i ++)
            {
                if (2 == m_iExpect[i])
                {
                    CLEDDataContainer *pTemp = new CLEDDataContainer;
                    pTemp->LoadFile(strFilePathArray.GetAt(i));
                    m_strFilePathArray.Add(strFilePathArray.GetAt(i));
                    m_strFileNameArray.Add(strFileNameArray.GetAt(i));
                    m_dataContainerArray.Add(*pTemp);
                }
            }
        }
    }

    if (iModelUnExpect1Num)
    {
        strTemp.Format("灯型号不相同文件数有%d个，是否添加到统计文件列表并进行参数统计?", iModelUnExpect1Num);
        if (IDOK == MessageBox(strTemp, "Warning", MB_OKCANCEL))
        {
            for (int i = 0; i < strFileNameArray.GetSize(); i ++)
            {
                if (1 == m_iExpect[i])
                {
                    CLEDDataContainer *pTemp = new CLEDDataContainer;
                    pTemp->LoadFile(strFilePathArray.GetAt(i));
                    m_strFilePathArray.Add(strFilePathArray.GetAt(i));
                    m_strFileNameArray.Add(strFileNameArray.GetAt(i));
                    m_dataContainerArray.Add(*pTemp);
                }
            }
        }
    }

 
    m_cDel.EnableWindow(m_dataContainerArray.GetSize());
    m_cClear.EnableWindow(m_dataContainerArray.GetSize());
    Relist();
}


void CDlgStatisticFileChoose::OnBnClickedButtonClear()
{
    // TODO: 在此添加控件通知处理程序代码
    m_dataContainerArray.RemoveAll();
    m_strFileNameArray.RemoveAll();
    m_strFilePathArray.RemoveAll();    
    m_cDel.EnableWindow(m_dataContainerArray.GetSize());
    m_cClear.EnableWindow(m_dataContainerArray.GetSize());
    Relist();
}


void CDlgStatisticFileChoose::OnBnClickedButtonDel()
{
    // TODO: 在此添加控件通知处理程序代码
    if (IDCANCEL == MessageBox("是否移除当前统计文件名列表打钩文件？", "Warning", MB_OKCANCEL))
    {
        return;
    }
    for (int i = m_dataContainerArray.GetSize() - 1; i >= 0; i --)
    {
        if (!m_cList.GetCheck(i))
        {
            continue;
        }
        m_dataContainerArray.RemoveAt(i);
        m_strFileNameArray.RemoveAt(i);
        m_strFilePathArray.RemoveAt(i);
    }
    m_cDel.EnableWindow(m_dataContainerArray.GetSize());
    m_cClear.EnableWindow(m_dataContainerArray.GetSize());
    Relist();
}


void CDlgStatisticFileChoose::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
    if (m_dataContainerArray.GetSize() == 0)
    {
        AfxMessageBox("未载入待统计灯具测试文件,请载入待统计灯具测试文件！");
        return;
    }
    for (int i = 0; i < m_dataContainerArray.GetSize(); i ++)
    {
        for (int j = 0; j < m_dataContainerArray.GetAt(i).GetSize(); j ++)
        {
            g_pDoc->m_StatisticLedDataContainer.AddLedData(m_dataContainerArray.GetAt(i).GetAt(j));
        }
    }
    CDialogEx::OnOK();
}


void CDlgStatisticFileChoose::Relist()
{
    m_cList.DeleteAllItems();
    while(1)
    {
        if (m_cList.DeleteColumn(0) == FALSE)
        {
            break;
        }
    }
    CString strTemp;
    strTemp.Format("%-80s %s", "统计文件名", "包含数据个数");
    int iN = 0; 
    strTemp = _T("SN.");
    m_cList.InsertColumn(iN,strTemp);
    m_cList.SetColumnWidth(iN,60);
    iN ++;
    strTemp = _T("统计文件名");
    m_cList.InsertColumn(iN,strTemp);
    m_cList.SetColumnWidth(iN,280); 

    iN ++;
    strTemp = _T("包含数据个数");
    m_cList.InsertColumn(iN,strTemp);
    m_cList.SetColumnWidth(iN,80); 
    for (int i = 0; i < m_dataContainerArray.GetSize(); i ++)
    {   
        iN = 0;
        strTemp.Format(_T("%4d"),i+1);
        m_cList.InsertItem(i,strTemp);
        iN ++;
        strTemp.Format(_T("%s"),m_strFileNameArray.GetAt(i)) ;
        m_cList.SetItemText(i,iN,strTemp);
        iN ++;
        strTemp.Format(_T("%d"),m_dataContainerArray.GetAt(i).GetSize()) ;
        m_cList.SetItemText(i,iN,strTemp);

    }
}




BOOL CDlgStatisticFileChoose::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    Relist();
    m_cDel.EnableWindow(m_dataContainerArray.GetSize());
    m_cClear.EnableWindow(m_dataContainerArray.GetSize());
    m_cList.ModifyStyle(0,LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS|LVS_NOSORTHEADER);
    m_cList.SetExtendedStyle(m_cList.GetExtendedStyle()  | 
        LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES| LVS_EX_HEADERDRAGDROP|LVS_EX_CHECKBOXES);

    m_cList.SetBkColor(RGB(232, 255, 255));
    m_cList.SetTextColor(RGB(128, 0, 64));
    m_cList.SetTextBkColor(RGB(232, 255, 255));
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}




void CDlgStatisticFileChoose::OnBnClickedButtonLoadTestsetdata()
{
    // TODO: 在此添加控件通知处理程序代码
    CEditLimitDlg dlg;
    dlg.m_bStatistic = TRUE;
    dlg.m_bLoadFile_WhenStart = TRUE;
    dlg.m_LimitData = g_pDoc->m_StatisticLedDataContainer.GetTestSettingData();
    dlg.DoModal();
    g_pDoc->m_StatisticLedDataContainer.GetTestSettingData() = dlg.m_LimitData;
}
