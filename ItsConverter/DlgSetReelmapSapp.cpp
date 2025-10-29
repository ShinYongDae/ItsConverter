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
