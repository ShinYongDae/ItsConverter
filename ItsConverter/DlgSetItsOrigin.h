#pragma once


// CDlgSetItsOrigin 대화 상자입니다.

class CDlgSetItsOrigin : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetItsOrigin)

public:
	CDlgSetItsOrigin(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgSetItsOrigin();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SET_ITS_ORIGIN };
#else
	enum { IDD = IDD_DLG_SET_ITS_ORIGIN };
#endif

public:
	BOOL Create();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
