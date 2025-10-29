#pragma once


// CDlgSetReelmapSapp 대화 상자입니다.

class CDlgSetReelmapSapp : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetReelmapSapp)

public:
	CDlgSetReelmapSapp(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgSetReelmapSapp();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SET_REELMAP_SAPP };
#else
	enum { IDD = IDD_DLG_SET_REELMAP_SAPP };
#endif

public:
	BOOL Create();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
