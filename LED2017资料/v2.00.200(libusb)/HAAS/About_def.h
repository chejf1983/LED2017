// About_def.h
#ifndef _ABOUT_DEF_H_
#define _ABOUT_DEF_H_

// 
//  ˵��: AboutDialogBoxDLL ������ʾԶ����׼About�Ի�����
//  �汾: V1.00 Update 2012.11
//        V1.01 Update 2013.1 �޸�Ӣ�Ľ����logoΪȫӢ��
//

// �ֶ�
#define  ABOUT_NAME          0  // �������
#define  ABOUT_VER           1  // �汾��Ϣ
#define  ABOUT_COMPANY       2  // ��˾����
#define  ABOUT_COPYRIGHT     3  // ��������Ȩ��
#define  ABOUT_ADD_NOTE      4  // ������Ϣ,�ɶ���

// ����
#define   LANG_CN             0
#define   LANG_EN             1


// ��������
extern BOOL __stdcall AboutDll_SetLang(int iLang);

// ���ø�����ʾ�ֶ� Unicode�汾
extern BOOL __stdcall AboutDll_SetStringUnicode(int iType, CString strName);

// ���ø�����ʾ�ֶ� ASCII�汾
extern BOOL __stdcall AboutDll_SetString(int iType, char szName[]);

// ��ʾԶ����׼About�Ի���
extern BOOL __stdcall AboutDll_ShowAboutDlg();

#endif
