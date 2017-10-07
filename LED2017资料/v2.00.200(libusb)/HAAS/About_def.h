// About_def.h
#ifndef _ABOUT_DEF_H_
#define _ABOUT_DEF_H_

// 
//  说明: AboutDialogBoxDLL 用于显示远方标准About对话框功能
//  版本: V1.00 Update 2012.11
//        V1.01 Update 2013.1 修改英文界面的logo为全英文
//

// 字段
#define  ABOUT_NAME          0  // 软件名称
#define  ABOUT_VER           1  // 版本信息
#define  ABOUT_COMPANY       2  // 公司名称
#define  ABOUT_COPYRIGHT     3  // 保留所有权利
#define  ABOUT_ADD_NOTE      4  // 附加信息,可多行

// 语言
#define   LANG_CN             0
#define   LANG_EN             1


// 设置语言
extern BOOL __stdcall AboutDll_SetLang(int iLang);

// 设置各个显示字段 Unicode版本
extern BOOL __stdcall AboutDll_SetStringUnicode(int iType, CString strName);

// 设置各个显示字段 ASCII版本
extern BOOL __stdcall AboutDll_SetString(int iType, char szName[]);

// 显示远方标准About对话框
extern BOOL __stdcall AboutDll_ShowAboutDlg();

#endif
