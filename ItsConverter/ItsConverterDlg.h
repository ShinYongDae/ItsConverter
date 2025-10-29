
// ItsConverterDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"

#include "SimpleCamMaster.h"
#include "SimpleOpengl.h"
#include "SimpleReelmap.h"
#include "DlgSetReelmapSapp.h"
#include "DlgSetItsOrigin.h"


// CItsConverterDlg 대화 상자
class CItsConverterDlg : public CDialog
{
	CSimpleReelmap* m_pReelmap[3];	// 0: RMapUp, 1: RMapDn, 2: RMapAll
	CSimpleOpengl* m_pOpengl;
	CSimpleCamMaster m_CamMaster;
	
	int m_nCurItemID;
	CFont m_FontOfTabCtrl;

	void InitTab();
	void ShowDlg(int nId);
	void HideAllDlg();

	CDlgSetReelmapSapp* m_pDlgSetReelmapSapp;
	CDlgSetItsOrigin* m_pDlgSetItsOrigin;

	void StringToChar(CString str, char* pCh); // char* returned must be deleted... 
	void Refresh();
	void RefreshDlg();

// 생성입니다.
public:
	CItsConverterDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	~CItsConverterDlg();

// 대화 상자 데이터입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_TabCtrl;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnMove(int x, int y);
};
