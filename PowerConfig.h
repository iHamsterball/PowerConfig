
// PowerConfig.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPowerConfigApp: 
// �йش����ʵ�֣������ PowerConfig.cpp
//

class CPowerConfigApp : public CWinApp
{
public:
	CPowerConfigApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPowerConfigApp theApp;