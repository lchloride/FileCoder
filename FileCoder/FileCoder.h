
// FileCoder.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFileCoderApp: 
// �йش����ʵ�֣������ FileCoder.cpp
//

class CFileCoderApp : public CWinApp
{
public:
	CFileCoderApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFileCoderApp theApp;