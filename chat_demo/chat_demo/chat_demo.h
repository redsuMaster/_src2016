
// chat_demo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cchat_demoApp: 
// �йش����ʵ�֣������ chat_demo.cpp
//

class Cchat_demoApp : public CWinApp
{
public:
	Cchat_demoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cchat_demoApp theApp;