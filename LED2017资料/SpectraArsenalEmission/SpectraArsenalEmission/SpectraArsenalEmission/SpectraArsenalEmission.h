// SpectraArsenalEmission.h : SpectraArsenalEmission DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSpectraArsenalEmissionApp
// �йش���ʵ�ֵ���Ϣ������� SpectraArsenalEmission.cpp
//

class CSpectraArsenalEmissionApp : public CWinApp
{
public:
	CSpectraArsenalEmissionApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
