// DlgSetItsOrigin.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ItsConverter.h"
#include "DlgSetItsOrigin.h"
#include "afxdialogex.h"


// CDlgSetItsOrigin ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgSetItsOrigin, CDialog)

CDlgSetItsOrigin::CDlgSetItsOrigin(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DLG_SET_ITS_ORIGIN, pParent)
{

}

CDlgSetItsOrigin::~CDlgSetItsOrigin()
{
}

void CDlgSetItsOrigin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSetItsOrigin, CDialog)
END_MESSAGE_MAP()


// CDlgSetItsOrigin �޽��� ó�����Դϴ�.

BOOL CDlgSetItsOrigin::Create()
{
	return CDialog::Create(CDlgSetItsOrigin::IDD);
}


BOOL CDlgSetItsOrigin::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
