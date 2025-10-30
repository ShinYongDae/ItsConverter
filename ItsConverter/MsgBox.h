#pragma once


// CMsgBox 대화 상자입니다.

class CMsgBox : public CDialog
{
	DECLARE_DYNAMIC(CMsgBox)

	CString m_sMsg;
	int m_nType;
	CWnd* m_pParent;
	int m_nRtn;

public:
	CMsgBox(CString sMsg, int nType = MB_OK, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMsgBox();

public:
	int GetRtn();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MSGBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
