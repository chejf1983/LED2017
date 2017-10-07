// SystemSettingsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "SystemSettingsDlg.h"
#include "afxdialogex.h"


// CSystemSettingsDlg �Ի���

IMPLEMENT_DYNAMIC(CSystemSettingsDlg, CDialogEx)

CSystemSettingsDlg::CSystemSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSystemSettingsDlg::IDD, pParent)
{

    m_strFileDataNum = _T("");
    m_strFileName = _T("");
    m_strFilePath = _T("");
    m_iSaveType = 0;
    m_iPrefixInputMode = 0;
}

CSystemSettingsDlg::~CSystemSettingsDlg()
{
}

void CSystemSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_FILE_DATA_NUM, m_strFileDataNum);
	DDX_Text(pDX, IDC_EDIT_FILE_NAME, m_strFileName);
	DDX_Radio(pDX, IDC_RADIO_AUTO_SAVE1, m_bAutoSave);
	DDX_Check(pDX, IDC_CHECK_LINE_NOT_MOVE, m_bLineNotMove);
	DDX_Text(pDX, IDC_EDIT_FILE_PATH, m_strFilePath);
	DDX_Radio(pDX, IDC_RADIO_NUM, m_iSaveType);
	DDX_Radio(pDX, IDC_RADIO_MANU_INPUT, m_iPrefixInputMode);
	DDX_Check(pDX, IDC_CHECK_DEMO, m_bDemo);
	DDX_Check(pDX, IDC_CHECK_INPUT_POWER, m_bInputPower);
}


BEGIN_MESSAGE_MAP(CSystemSettingsDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSystemSettingsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_AUTO_SAVE1, &CSystemSettingsDlg::OnBnClickedRadioAutoSave1)
	ON_BN_CLICKED(IDC_RADIO_AUTO_SAVE2, &CSystemSettingsDlg::OnBnClickedRadioAutoSave2)
	ON_BN_CLICKED(IDC_BUTTON_SCAN, &CSystemSettingsDlg::OnBnClickedButtonScan)
    ON_BN_CLICKED(IDC_RADIO_NUM, &CSystemSettingsDlg::OnBnClickedRadioNum)
    ON_BN_CLICKED(IDC_RADIO_DAY, &CSystemSettingsDlg::OnBnClickedRadioDay)
    ON_BN_CLICKED(IDC_RADIO_MANU_INPUT, &CSystemSettingsDlg::OnBnClickedRadioManuInput)
    ON_BN_CLICKED(IDC_RADIO_MANU_INPUT2, &CSystemSettingsDlg::OnBnClickedRadioManuInput2)
END_MESSAGE_MAP()


// CSystemSettingsDlg ��Ϣ�������


void CSystemSettingsDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!UpdateData(TRUE))
	{
		return;
	}

	if (m_bAutoSave)
	{
		if (m_strFilePath.Trim().GetLength() == 0)
		{
			AfxMessageBox("����ѡ��һ��·����");
			return;
		}

		CFileFind m_find;
		if (!m_find.FindFile(m_strFilePath))
		{
			if (0 == CreateDirectory(m_strFilePath, NULL))
			{
				if (GetLastError() == ERROR_PATH_NOT_FOUND)
				{
					AfxMessageBox("·����Ч��������ѡ��");
					return;
				}
			}
		}
	}
	
	CDialogEx::OnOK();
}


BOOL CSystemSettingsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

 

    GetDlgItem(IDC_COMBO_FILE_DATA_NUM)->EnableWindow(!m_iSaveType && m_bAutoSave);
    GetDlgItem(IDC_EDIT_FILE_NAME)->EnableWindow(!m_iPrefixInputMode && m_bAutoSave);
    GetDlgItem(IDC_RADIO_NUM)->EnableWindow(m_bAutoSave);
    GetDlgItem(IDC_RADIO_DAY)->EnableWindow(m_bAutoSave);
    GetDlgItem(IDC_RADIO_MANU_INPUT)->EnableWindow(m_bAutoSave);
    GetDlgItem(IDC_RADIO_MANU_INPUT2)->EnableWindow(m_bAutoSave);
	if (!g_bDebug)
	{
		GetDlgItem(IDC_CHECK_DEMO)->ShowWindow(g_bDebug);
		m_bDemo = FALSE;
		UpdateData(FALSE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSystemSettingsDlg::OnBnClickedRadioAutoSave1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

    GetDlgItem(IDC_COMBO_FILE_DATA_NUM)->EnableWindow(!m_iSaveType && m_bAutoSave);
    GetDlgItem(IDC_EDIT_FILE_NAME)->EnableWindow(!m_iPrefixInputMode && m_bAutoSave);
    GetDlgItem(IDC_RADIO_NUM)->EnableWindow(m_bAutoSave);
    GetDlgItem(IDC_RADIO_DAY)->EnableWindow(m_bAutoSave);
    GetDlgItem(IDC_RADIO_MANU_INPUT)->EnableWindow(m_bAutoSave);
    GetDlgItem(IDC_RADIO_MANU_INPUT2)->EnableWindow(m_bAutoSave);
}


void CSystemSettingsDlg::OnBnClickedRadioAutoSave2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	
    GetDlgItem(IDC_COMBO_FILE_DATA_NUM)->EnableWindow(!m_iSaveType && m_bAutoSave);
    GetDlgItem(IDC_EDIT_FILE_NAME)->EnableWindow(!m_iPrefixInputMode && m_bAutoSave);
    GetDlgItem(IDC_RADIO_NUM)->EnableWindow(m_bAutoSave);
    GetDlgItem(IDC_RADIO_DAY)->EnableWindow(m_bAutoSave);
    GetDlgItem(IDC_RADIO_MANU_INPUT)->EnableWindow(m_bAutoSave);
    GetDlgItem(IDC_RADIO_MANU_INPUT2)->EnableWindow(m_bAutoSave);
}


void CSystemSettingsDlg::OnBnClickedButtonScan()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	
	char szDir[MAX_PATH];
	BROWSEINFO bi;
	ITEMIDLIST * piDl;
	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szDir;
	bi.lpszTitle = "��ѡ��Ŀ¼";
	bi.ulFlags = BIF_STATUSTEXT | BIF_USENEWUI | BIF_RETURNFSANCESTORS;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	piDl = SHBrowseForFolder(&bi);
	if (NULL == piDl)
	{
		return;
	}
	else
	{
		SHGetPathFromIDList(piDl, szDir);
		m_strFilePath = szDir;
	}

	UpdateData(FALSE);
}


void CSystemSettingsDlg::OnBnClickedRadioNum()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);
    GetDlgItem(IDC_COMBO_FILE_DATA_NUM)->EnableWindow(!m_iSaveType);
}


void CSystemSettingsDlg::OnBnClickedRadioDay()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE); 
    GetDlgItem(IDC_COMBO_FILE_DATA_NUM)->EnableWindow(!m_iSaveType);
}


void CSystemSettingsDlg::OnBnClickedRadioManuInput()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);
    GetDlgItem(IDC_EDIT_FILE_NAME)->EnableWindow(!m_iPrefixInputMode);
}


void CSystemSettingsDlg::OnBnClickedRadioManuInput2()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);
    GetDlgItem(IDC_EDIT_FILE_NAME)->EnableWindow(!m_iPrefixInputMode);
}
