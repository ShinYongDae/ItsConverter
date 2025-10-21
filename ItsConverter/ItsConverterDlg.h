
// ItsConverterDlg.h : 헤더 파일
//

#pragma once
#include "SimpleCamMaster.h"
#include "SimpleOpengl.h"
#include "SimpleReelmap.h"


// CItsConverterDlg 대화 상자
class CItsConverterDlg : public CDialog
{
	CSimpleReelmap* m_pReelmap[3];	// 0: RMapUp, 1: RMapDn, 2: RMapAll
	CSimpleOpengl* m_pOpengl;
	CSimpleCamMaster m_CamMaster;
	
// 생성입니다.
public:
	CItsConverterDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

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
};
