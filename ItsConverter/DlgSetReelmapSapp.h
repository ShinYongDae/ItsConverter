#pragma once


// CDlgSetReelmapSapp ��ȭ �����Դϴ�.

class CDlgSetReelmapSapp : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetReelmapSapp)

public:
	CDlgSetReelmapSapp(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgSetReelmapSapp();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SET_REELMAP_SAPP };
#else
	enum { IDD = IDD_DLG_SET_REELMAP_SAPP };
#endif

public:
	BOOL Create();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
