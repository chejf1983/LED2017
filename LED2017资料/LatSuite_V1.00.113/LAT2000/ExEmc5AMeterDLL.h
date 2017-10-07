////ExEmc5AMeterDLL.h
//��Ȩ���� 2013 ����Զ�������Ϣ�ɷ����޹�˾(EVERFINE)

#ifndef _EXEMC5AMETERDLL_H_
#define _EXMC5AMETERDLL_H_

typedef struct tag_set_5A_Data
{
	BOOL	m_bDLPE;
	BOOL	m_bDNPE;
	BOOL	m_bLN;
	BOOL	m_bLNPE;
	BOOL	m_bLPE;
	BOOL	m_bNPE;
	int		m_iAlternate;
	int		m_iPhaseSyn;
	int		m_iComm;
	int		m_iDeg1EN;
	int		m_iDeg2EN;
	int		m_iDeg3EN;
	int		m_iDeg4EN;
	int		m_iLevel;
	int		m_iPowerSyn;
	int		m_iTriggerMode;
	int		m_iVPol;
	int		m_iVHL_En;
	int		m_iVLL_En;
	int		m_iWaveForm;
	int		m_iCount;
	int		m_iDeg1;
	int		m_iDeg2;
	int		m_iDeg3;
	int		m_iDeg4;
	int		m_iIHL;
	int		m_iILL;
	int		m_iIHL_En;
	int		m_iILL_En;
	float	m_fRepetTime;
	int		m_iVHL;
	int		m_iVLL;
	int		m_iVPeak;
	int		m_iEut;
	int		m_iSurgePort;
}EMC5ASetData;

typedef struct tag_RE_5A_Data
{
	char strRe[256];
	int   m_iResult;
	float m_fTime;
}EMC5AREData;

//��ʼ�� ��ȡ�ļ�·��
extern BOOL __stdcall EMC_InitEMC5A(char strPathName[], int iCOM);
//��ʾ���öԻ���
extern void __stdcall EMC_ShowEmc5ASetDlg(EMC5ASetData &setData,int &iSeleCur);
//������
extern BOOL __stdcall EMC_EMC5AStart(EMC5ASetData &setData, int iSeleCur);
//��ȡ״̬ �Ƿ������
//-1 ������
//0 �������
//1ʧ��
//2��λ
//3��λ
extern int __stdcall EMC_EMC5ARead(EMC5AREData &ReData);
//��λ����
extern BOOL __stdcall EMC_EMC5AReset();

extern BOOL __stdcall EMC_EMC5ASet();

extern BOOL __stdcall EMC_EMC5ASetEUT(BOOL bON);


class CEMS61000_5AComm
{
public:
	CEMS61000_5AComm()
	{
		InitializeCriticalSection(&m_critical);			
	}
	inline BOOL Initialize(CString strPath, CString strCOM)
	{
		int iCOM;
		strCOM.MakeUpper();
		strCOM.Trim();
		sscanf_s(strCOM, "COM%d", &iCOM);
		EnterCriticalSection(&m_critical);
		BOOL bR = EMC_InitEMC5A(strPath.GetBuffer(), iCOM);
		LeaveCriticalSection(&m_critical);
		return bR;
	}

	inline void ShowSettingsDialog(EMC5ASetData &setData, int & iCurSele ,BOOL bReadOnly)
	{
		EMC_ShowEmc5ASetDlg(setData, iCurSele);
	}

	inline BOOL Start(EMC5ASetData &setData, int iCurSele)
	{
		EnterCriticalSection(&m_critical);
		BOOL bR = EMC_EMC5AStart(setData, iCurSele);
		LeaveCriticalSection(&m_critical);
		return bR;
	}

	inline int Read(EMC5AREData &ReData)
	{
		EnterCriticalSection(&m_critical);
		BOOL bR = EMC_EMC5ARead(ReData);
		LeaveCriticalSection(&m_critical);
		return bR;
	}

	
private:
	CRITICAL_SECTION m_critical;
};

#endif
