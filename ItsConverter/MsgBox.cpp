// MsgBox.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ItsConverter.h"
#include "MsgBox.h"
#include "afxdialogex.h"

#include "ItsConverterDlg.h"
#include "DlgSetReelmapSapp.h"
#include "DlgSetItsOrigin.h"


// CMsgBox 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMsgBox, CDialog)

CMsgBox::CMsgBox(CString sMsg, int nType, CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MSGBOX, pParent)
{
	m_sMsg = sMsg;
	m_nType = nType;
	m_pParent = pParent;
	m_nRtn = IDOK;
}

CMsgBox::~CMsgBox()
{
}

void CMsgBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMsgBox, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMsgBox 메시지 처리기입니다.


BOOL CMsgBox::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	this->ShowWindow(SW_HIDE);
	int nTab = ((CItsConverterDlg*)m_pParent)->GetCurTab();
	CWnd* pWnd = ((CItsConverterDlg*)m_pParent)->GetCurDlg();
	if(pWnd)
		m_nRtn = pWnd->MessageBox(m_sMsg, 0, m_nType);

	OnOK();
	//SetTimer(0, 100, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMsgBox::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	KillTimer(nIDEvent);
	switch (nIDEvent)
	{
	case 0:
		OnOK();
		break;
	default:
		break;
	}

	CDialog::OnTimer(nIDEvent);
}

int CMsgBox::GetRtn()
{
	return m_nRtn;
}