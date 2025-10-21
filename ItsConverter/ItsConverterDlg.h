
// ItsConverterDlg.h : ��� ����
//

#pragma once
#include "SimpleCamMaster.h"
#include "SimpleOpengl.h"
#include "SimpleReelmap.h"


// CItsConverterDlg ��ȭ ����
class CItsConverterDlg : public CDialog
{
	CSimpleReelmap* m_pReelmap[3];	// 0: RMapUp, 1: RMapDn, 2: RMapAll
	CSimpleOpengl* m_pOpengl;
	CSimpleCamMaster m_CamMaster;
	
// �����Դϴ�.
public:
	CItsConverterDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ITSCONVERTER_DIALOG };
#endif


public:
	// About CamMaster
	tagStrPcs& GetAddrStrPcs();

	// About Reelmap
	CArPcr& GetAddrArPcr();
	CArPcrMark& GetAddrArPcrMark();
	BOOL GetMatrix(int nPcsId, int &nR, int &nC);
	COLORREF GetDefColor(int nDefCode);

	// About OpenGL
	void DrawStrPcs();
	void DrawPnlDefNum(int nSerial);
	void DrawPnlDef(int nSerial);
	void DrawMarkedPcs(int nSerial);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
