#pragma once


// CDlgSetItsOrigin ��ȭ �����Դϴ�.

class CDlgSetItsOrigin : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetItsOrigin)

public:
	CDlgSetItsOrigin(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgSetItsOrigin();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SET_ITS_ORIGIN };
#else
	enum { IDD = IDD_DLG_SET_ITS_ORIGIN };
#endif

public:
	BOOL Create();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
