
// ipv6source.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cipv6sourceApp:
// �йش����ʵ�֣������ ipv6source.cpp
//

class Cipv6sourceApp : public CWinApp
{
public:
	Cipv6sourceApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cipv6sourceApp theApp;