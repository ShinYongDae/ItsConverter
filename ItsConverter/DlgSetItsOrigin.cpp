// DlgSetItsOrigin.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ItsConverter.h"
#include "DlgSetItsOrigin.h"
#include "afxdialogex.h"


// CDlgSetItsOrigin 대화 상자입니다.

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


// CDlgSetItsOrigin 메시지 처리기입니다.

BOOL CDlgSetItsOrigin::Create()
{
	return CDialog::Create(CDlgSetItsOrigin::IDD);
}
