
// ItsConverterDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"

#include "SimpleCamMaster.h"
#include "SimpleOpengl.h"
#include "SimpleReelmap.h"
#include "DlgSetReelmapSapp.h"
#include "DlgSetItsOrigin.h"
#include "MsgBox.h"

#define INI_PATH _T("C:\\R2RSet\\ItsConverter.ini")

struct stLastJob
{
	int nMachine;
	CString sProcessNum, sItsCode;
	CString sModel, sLot, sLayerUp, sLayerDn;
	int nTestMode;

	stLastJob()
	{
		nMachine = -1;
		sProcessNum = _T("");	sItsCode = _T("");
		sModel = _T("");	sLot = _T("");	sLayerUp = _T("");	sLayerDn = _T("");
		nTestMode = -1;
	}
};

struct stMachine
{
	CString sName, sPath;

	stMachine()
	{
		sName = _T("");	sPath = _T("");
	}
};

struct stIni
{
	CString sPathCamSpecDir, sPathItsOriginList;
	stLastJob LastJob;
	int nTotalMachine;
	stMachine* Machine;

	int i;
	TCHAR szData[MAX_PATH];
	TCHAR sep[6]; // _T(",/;\r\n\t");
	TCHAR *token;
	CString sItem, sData;

	stIni()
	{
		sPathCamSpecDir = _T("");
		sPathItsOriginList = _T("");
		nTotalMachine = 0;
		Machine = NULL;

		sep[0] = _T(',');
		sep[1] = _T('/');
		sep[2] = _T(';');
		sep[3] = _T('\r');
		sep[4] = _T('\n');
		sep[5] = _T('\t');
		token = NULL;
		sItem = _T("");

		LoadIni();
	}

	~stIni()
	{
		if (Machine)
		{
			delete [] Machine;
			Machine = NULL;
		}
	}

	void LoadIni()
	{
		if (0 < ::GetPrivateProfileString(_T("Info"), _T("CamSpecDir"), NULL, szData, sizeof(szData), INI_PATH))
			sPathCamSpecDir = CString(szData);
		else
			sPathCamSpecDir = _T("");

		if (0 < ::GetPrivateProfileString(_T("Info"), _T("ItsOriginList"), NULL, szData, sizeof(szData), INI_PATH))
			sPathItsOriginList = CString(szData);
		else
			sPathItsOriginList = _T("");

		if (0 < ::GetPrivateProfileString(_T("Machine Info"), _T("Total"), NULL, szData, sizeof(szData), INI_PATH))
			nTotalMachine = _ttoi(szData);
		else
			nTotalMachine = 0;

		if (nTotalMachine > 0)
		{
			if (Machine)
				delete[] Machine;

			Machine = new stMachine[nTotalMachine];

			for (i = 0; i < nTotalMachine; i++)
			{
				sItem.Format(_T("Machine_%d"), i);
				if (0 < ::GetPrivateProfileString(sItem, _T("Name"), NULL, szData, sizeof(szData), INI_PATH))
					Machine[i].sName = CString(szData);
				else
					Machine[i].sName = _T("");
				if (0 < ::GetPrivateProfileString(sItem, _T("Address"), NULL, szData, sizeof(szData), INI_PATH))
					Machine[i].sPath = CString(szData);
				else
					Machine[i].sPath = _T("");
			}
		}

		if (0 < ::GetPrivateProfileString(_T("Last Job"), _T("Machine No"), NULL, szData, sizeof(szData), INI_PATH))
			LastJob.nMachine = _ttoi(szData);
		else
			LastJob.nMachine = -1;

		if (0 < ::GetPrivateProfileString(_T("Last Job"), _T("Model Name"), NULL, szData, sizeof(szData), INI_PATH))
			LastJob.sModel = CString(szData);
		else
			LastJob.sModel = _T("");

		if (0 < ::GetPrivateProfileString(_T("Last Job"), _T("Lot No"), NULL, szData, sizeof(szData), INI_PATH))
			LastJob.sLot = CString(szData);
		else
			LastJob.sLot = _T("");

		if (0 < ::GetPrivateProfileString(_T("Last Job"), _T("LayerUp Name"), NULL, szData, sizeof(szData), INI_PATH))
			LastJob.sLayerUp = CString(szData);
		else
			LastJob.sLayerUp = _T("");

		if (0 < ::GetPrivateProfileString(_T("Last Job"), _T("LayerDn Name"), NULL, szData, sizeof(szData), INI_PATH))
			LastJob.sLayerDn = CString(szData);
		else
			LastJob.sLayerDn = _T("");

		if (0 < ::GetPrivateProfileString(_T("Last Job"), _T("Process_Code"), NULL, szData, sizeof(szData), INI_PATH))
			LastJob.sProcessNum = CString(szData);
		else
			LastJob.sProcessNum = _T("");

		if (0 < ::GetPrivateProfileString(_T("Last Job"), _T("Its_Code"), NULL, szData, sizeof(szData), INI_PATH))
			LastJob.sItsCode = CString(szData);
		else
			LastJob.sItsCode = _T("");

		if (0 < ::GetPrivateProfileString(_T("Last Job"), _T("TEST_MODE"), NULL, szData, sizeof(szData), INI_PATH))
			LastJob.nTestMode = _ttoi(szData);
		else
			LastJob.nTestMode = -1;
	}

	void SaveIni()
	{
		sData.Format(_T("%d"), LastJob.nMachine);
		::WritePrivateProfileString(_T("Last Job"), _T("Machine No"), sData, INI_PATH);

		sData = LastJob.sModel;
		::WritePrivateProfileString(_T("Last Job"), _T("Model Name"), sData, INI_PATH);

		sData = LastJob.sLot;
		::WritePrivateProfileString(_T("Last Job"), _T("Lot No"), sData, INI_PATH);

		sData = LastJob.sLayerUp;
		::WritePrivateProfileString(_T("Last Job"), _T("LayerUp Name"), sData, INI_PATH);

		sData = LastJob.sLayerDn;
		::WritePrivateProfileString(_T("Last Job"), _T("LayerDn Name"), sData, INI_PATH);

		sData = LastJob.sProcessNum;
		::WritePrivateProfileString(_T("Last Job"), _T("Process_Code"), sData, INI_PATH);

		sData = LastJob.sItsCode;
		::WritePrivateProfileString(_T("Last Job"), _T("Its_Code"), sData, INI_PATH);

		sData.Format(_T("%d"), LastJob.nTestMode);
		::WritePrivateProfileString(_T("Last Job"), _T("TEST_MODE"), sData, INI_PATH);
	}
};

// CItsConverterDlg 대화 상자
class CItsConverterDlg : public CDialog
{
	CSimpleReelmap* m_pReelmap[3];	// 0: RMapUp, 1: RMapDn, 2: RMapAll
	CSimpleOpengl* m_pOpengl;
	CSimpleCamMaster m_CamMaster;
	stIni m_stIni;

	int m_nCurTab;
	CFont m_FontOfTabCtrl;

	void InitTab();
	void ShowDlg(int nId);
	void HideAllDlg();

	CDlgSetReelmapSapp* m_pDlgSetReelmapSapp;
	CDlgSetItsOrigin* m_pDlgSetItsOrigin;

	void StringToChar(CString str, char* pCh); // char* returned must be deleted... 
	void Refresh();
	void RefreshDlg();
	void SetRadioTestMode(int nIdx);

	int m_nMachine;
	CString m_sModel, m_sLot, m_sLayer[2], m_sProcessCode, m_sItsCode;
	int m_nTestMode;

	void Init();
	void InitModel();
	void InitTestMode();
	void InitComboMachine();
	void ModifyModel();

	BOOL CheckItsOrigin();
	int GetItsOriginCase(CString sModel);
	int GetCurrOriginCase(CString sModel);

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

	int GetCurTab();
	CWnd* GetCurDlg();

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
	afx_msg void OnSelchangeComboMachine();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
