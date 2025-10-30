// DlgSetReelmapSapp.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ItsConverter.h"
#include "DlgSetReelmapSapp.h"
#include "afxdialogex.h"


// CDlgSetReelmapSapp 대화 상자입니다.

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


// CDlgSetReelmapSapp 메시지 처리기입니다.

BOOL CDlgSetReelmapSapp::Create()
{
	return CDialog::Create(CDlgSetReelmapSapp::IDD);
}


BOOL CDlgSetReelmapSapp::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
