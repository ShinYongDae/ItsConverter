// MsgBox.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ItsConverter.h"
#include "MsgBox.h"
#include "afxdialogex.h"

#include "ItsConverterDlg.h"
#include "DlgSetReelmapSapp.h"
#include "DlgSetItsOrigin.h"


// CMsgBox ��ȭ �����Դϴ�.

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


// CMsgBox �޽��� ó�����Դϴ�.


BOOL CMsgBox::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	this->ShowWindow(SW_HIDE);
	int nTab = ((CItsConverterDlg*)m_pParent)->GetCurTab();
	CWnd* pWnd = ((CItsConverterDlg*)m_pParent)->GetCurDlg();
	if(pWnd)
		m_nRtn = pWnd->MessageBox(m_sMsg, 0, m_nType);

	OnOK();
	//SetTimer(0, 100, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CMsgBox::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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