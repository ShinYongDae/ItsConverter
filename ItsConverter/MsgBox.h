#pragma once


// CMsgBox ��ȭ �����Դϴ�.

class CMsgBox : public CDialog
{
	DECLARE_DYNAMIC(CMsgBox)

	CString m_sMsg;
	CWnd* m_pParent;

public:
	CMsgBox(CString sMsg, CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMsgBox();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MSGBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
