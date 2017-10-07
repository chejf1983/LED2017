// AlarmRingEditDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "AlarmRingEditDlg.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"


extern CString g_strCurrentPath;
// CAlarmRingEditDlg �Ի���

IMPLEMENT_DYNAMIC(CAlarmRingEditDlg, CDialogEx)

CAlarmRingEditDlg::CAlarmRingEditDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAlarmRingEditDlg::IDD, pParent)
{

	m_iOFFTimems = 0;
	m_iRingONTimems = 0;
	m_iRingNumber = 0;
	m_strName = _T("");
}

CAlarmRingEditDlg::~CAlarmRingEditDlg()
{
}

void CAlarmRingEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_OFF_TIME, m_iOFFTimems);
	DDX_Text(pDX, IDC_EDIT_ON_TIME, m_iRingONTimems);
	DDX_Text(pDX, IDC_EDIT_RING_NUMBER, m_iRingNumber);
	DDX_Control(pDX, IDC_LIST_RING, m_cRingListBox);
	DDX_Text(pDX, IDC_EDIT_RING_NAME, m_strName);
}


BEGIN_MESSAGE_MAP(CAlarmRingEditDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CAlarmRingEditDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CAlarmRingEditDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CAlarmRingEditDlg::OnBnClickedButtonModify)
	ON_BN_CLICKED(IDOK, &CAlarmRingEditDlg::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST_RING, &CAlarmRingEditDlg::OnLbnSelchangeListRing)
END_MESSAGE_MAP()


// CAlarmRingEditDlg ��Ϣ�������


void CAlarmRingEditDlg::OnBnClickedButtonAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!UpdateData(TRUE))
	{
		return;
	}

	if (NULL == g_pDoc)
	{
		return;
	}
	if (-1 != g_pDoc->m_AlarmRingData.FindRing(m_strName))
	{
		AfxMessageBox("�������Ѿ����ڣ����޸����ƺ�����ӣ�");
		return;
	}

	RingData data;
	data.strRingName = m_strName;
	data.iRingNumber = m_iRingNumber;
	data.iRingOFFTimems = m_iOFFTimems;
	data.iRingONTimems = m_iRingONTimems;

	g_pDoc->m_AlarmRingData.AddRing(data);
	RelistRing();
}


void CAlarmRingEditDlg::RelistRing()
{
	if (NULL != g_pDoc)
	{
		m_cRingListBox.ResetContent();
		for (int i = 0; i < g_pDoc->m_AlarmRingData.GetRingCount(); i++)
		{
			m_cRingListBox.InsertString(i, g_pDoc->m_AlarmRingData.GetRingInfoString(i));
		}
	}
}


void CAlarmRingEditDlg::OnBnClickedButtonDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if (NULL != g_pDoc)
	{
		if (g_pDoc->m_AlarmRingData.DeleteRingData(m_strName))
		{
			RelistRing();
			m_cRingListBox.SetCurSel(0);
			AfxMessageBox("ɾ���ɹ���");
		}
		else
		{
			AfxMessageBox("ɾ��ʧ�ܣ�");
		}
	}
}


void CAlarmRingEditDlg::OnBnClickedButtonModify()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (NULL != g_pDoc)
	{
		int iCurSel = m_cRingListBox.GetCurSel();
		if (-1 == iCurSel)
		{
			AfxMessageBox("����ѡ��һ����ʾ����");
			return;
		}

		RingData Data = g_pDoc->m_AlarmRingData.GetRingData(iCurSel);
		Data.strRingName = m_strName;
		Data.iRingOFFTimems = m_iOFFTimems;
		Data.iRingNumber = m_iRingNumber;
		Data.iRingONTimems = m_iRingONTimems;
		
		RelistRing();
		AfxMessageBox("���³ɹ���");
	}
}


BOOL CAlarmRingEditDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	RelistRing();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CAlarmRingEditDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CAlarmRingEditDlg::OnLbnSelchangeListRing()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int iIndex = m_cRingListBox.GetCurSel();
	if (-1 == iIndex)
	{
		AfxMessageBox("����ѡ��һ����ʾ����");
		return;
	}
	if (NULL != g_pDoc)
	{
		RingData Data = g_pDoc->m_AlarmRingData.GetRingData(iIndex);
		m_strName = Data.strRingName;
		m_iOFFTimems = Data.iRingOFFTimems;
		m_iRingNumber = Data.iRingNumber;
		m_iRingONTimems = Data.iRingONTimems;

		UpdateData(FALSE);
	}
}
