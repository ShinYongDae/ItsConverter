
// ItsConverter.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CItsConverterApp:
// �� Ŭ������ ������ ���ؼ��� ItsConverter.cpp�� �����Ͻʽÿ�.
//

class CItsConverterApp : public CWinApp
{
public:
	CItsConverterApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CItsConverterApp theApp;