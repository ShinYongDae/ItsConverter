// DlgSetReelmapSapp.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ItsConverter.h"
#include "DlgSetReelmapSapp.h"
#include "afxdialogex.h"


// CDlgSetReelmapSapp ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgSetReelmapSapp, CDialog)

CDlgSetReelmapSapp::CDlgSetReelmapSapp(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DLG_SET_REELMAP_SAPP, pParent)
{

}

CDlgSetReelmapSapp::~CDlgSetReelmapSapp()
{
}

void CDlgSetReelmapSapp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSetReelmapSapp, CDialog)
END_MESSAGE_MAP()


// CDlgSetReelmapSapp �޽��� ó�����Դϴ�.

BOOL CDlgSetReelmapSapp::Create()
{
	return CDialog::Create(CDlgSetReelmapSapp::IDD);
}


BOOL CDlgSetReelmapSapp::PreTranslateMessage(MSG* pMsg)
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
