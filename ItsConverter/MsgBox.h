#pragma once


// CMsgBox ��ȭ �����Դϴ�.

class CMsgBox : public CDialog
{
	DECLARE_DYNAMIC(CMsgBox)

	CString m_sMsg;
	int m_nType;
	CWnd* m_pParent;
	int m_nRtn;

public:
	CMsgBox(CString sMsg, int nType = MB_OK, CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMsgBox();

public:
	int GetRtn();

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
