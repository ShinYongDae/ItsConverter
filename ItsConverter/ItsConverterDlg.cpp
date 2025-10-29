
// ItsConverterDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "ItsConverter.h"
#include "ItsConverterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CItsConverterDlg 대화 상자



CItsConverterDlg::CItsConverterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ITSCONVERTER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pDlgSetReelmapSapp = NULL;
	m_pDlgSetItsOrigin = NULL;
}

CItsConverterDlg::~CItsConverterDlg()
{
	if (m_pDlgSetItsOrigin != NULL)
	{
		delete m_pDlgSetItsOrigin;
		m_pDlgSetItsOrigin = NULL;
	}

	if (m_pDlgSetReelmapSapp != NULL)
	{
		delete m_pDlgSetReelmapSapp;
		m_pDlgSetReelmapSapp = NULL;
	}
}

void CItsConverterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
}

BEGIN_MESSAGE_MAP(CItsConverterDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CItsConverterDlg::OnTcnSelchangeTab1)
	ON_WM_SHOWWINDOW()
	ON_WM_MOVE()
END_MESSAGE_MAP()


// CItsConverterDlg 메시지 처리기

BOOL CItsConverterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//GetSystemMenu(FALSE)->EnableMenuItem(SC_CLOSE, MF_GRAYED | MF_BYCOMMAND);
	this->SetWindowText(_T("ITS Data Converter (version: 1.0.0) ;  Update Date(2025,10,21)"));


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CItsConverterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CItsConverterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// About CamMaster
tagStrPcs& CItsConverterDlg::GetAddrStrPcs()
{
	return m_CamMaster.GetAddrStrPcs();
}

// About Reelmap
COLORREF CItsConverterDlg::GetDefColor(int nDefCode)
{
	return m_pReelmap[0]->GetDefColor(nDefCode);
}

CArPcr& CItsConverterDlg::GetAddrArPcr()
{
	return m_pReelmap[0]->GetAddrArPcr();
}

CArPcrMark& CItsConverterDlg::GetAddrArPcrMark()
{
	return m_pReelmap[0]->GetAddrArPcrMark();
}

BOOL CItsConverterDlg::GetMatrix(int nPcsId, int &nR, int &nC)
{
	return m_pReelmap[0]->GetMatrix(nPcsId, nR, nC);
}

// About OpenGL
void CItsConverterDlg::DrawStrPcs()
{
	m_pOpengl->DrawStrPcs(GetAddrStrPcs());
}

void CItsConverterDlg::DrawPnlDefNum(int nSerial)
{
	m_pOpengl->DrawPnlDefNum(nSerial, GetAddrArPcr(), GetAddrStrPcs());
}

void CItsConverterDlg::DrawPnlDef(int nSerial)
{
	m_pOpengl->DrawPnlDef(nSerial, GetAddrArPcr(), GetAddrStrPcs());
}

void CItsConverterDlg::DrawMarkedPcs(int nSerial)
{
	m_pOpengl->DrawMarkedPcs(nSerial, GetAddrArPcrMark(), GetAddrStrPcs());
}

void CItsConverterDlg::StringToChar(CString str, char* pCh) // char* returned must be deleted... 
{
	wchar_t*	wszStr;
	int				nLenth;

	USES_CONVERSION;
	//1. CString to wchar_t* conversion
	wszStr = T2W(str.GetBuffer(str.GetLength()));

	//2. wchar_t* to char* conversion
	nLenth = WideCharToMultiByte(CP_ACP, 0, wszStr, -1, NULL, 0, NULL, NULL); //char* 형에 대한길이를 구함 

	//3. wchar_t* to char* conversion
	WideCharToMultiByte(CP_ACP, 0, wszStr, -1, pCh, nLenth, 0, 0);
	return;
}

void CItsConverterDlg::InitTab()	// Tab Control 초기화
{
	CString sTabCaption[2];
	sTabCaption[0] = _T("Reelmap & SAPP");
	sTabCaption[1] = _T("ITS Origin case");

	// Tab Control의 폰트 변경.
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 15; // point 크기
	lf.lfWeight = FW_EXTRABOLD;
	_tcscpy(lf.lfFaceName, _T("굴림체"));

	m_FontOfTabCtrl.CreateFontIndirect(&lf);
	CTabCtrl* pCtlTab = (CTabCtrl*)GetDlgItem(IDC_TAB1); // 탭 콘트롤	
	pCtlTab->SetFont((CFont*)&m_FontOfTabCtrl, TRUE);

	TC_ITEM item;
	item.mask = TCIF_TEXT;
	//char *tabname;
	//tabname = new char[sTabCaption[0].GetLength() + 1];
	//StringToChar(sTabCaption[0], tabname);
	//item.pszText = tabname;
	//m_TabCtrl.InsertItem(0, &item);
	//delete[] tabname;
	item.pszText = (LPWSTR)(LPCWSTR)sTabCaption[0];
	m_TabCtrl.InsertItem(0, &item);

	item.pszText = (LPWSTR)(LPCWSTR)sTabCaption[1];
	m_TabCtrl.InsertItem(1, &item);

	m_nCurItemID = 0;
	m_TabCtrl.HighlightItem(m_nCurItemID, TRUE);

	ShowDlg(m_nCurItemID);
}

void CItsConverterDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	// 현재 설정된 SUB UNIT의 인덱스값(0기준)을 얻는다.
	m_TabCtrl.HighlightItem(m_nCurItemID, FALSE);

	m_nCurItemID = m_TabCtrl.GetCurSel();
	m_TabCtrl.HighlightItem(m_nCurItemID, TRUE);
	ShowDlg(m_nCurItemID);
}

void CItsConverterDlg::ShowDlg(int nId)
{
	CRect rtForm, rtTab, rtDlg;
	CRect rtDlg0, rtDlg1;
	this->GetWindowRect(&rtForm);
	int nHeithtSystemBar = GetSystemMetrics(SM_CYCAPTION);
	GetDlgItem(IDC_STATIC_TAB1)->GetWindowRect(&rtTab);
	ScreenToClient(&rtTab);
	//ClientToScreen(&rtTab);

	HideAllDlg();
	switch (nId)
	{
	case 0:
		if (!m_pDlgSetReelmapSapp)
		{
			m_pDlgSetReelmapSapp = new CDlgSetReelmapSapp(this);
			if (m_pDlgSetReelmapSapp->GetSafeHwnd() == 0)
			{
				m_pDlgSetReelmapSapp->Create();
				m_pDlgSetReelmapSapp->ShowWindow(SW_SHOW);

				m_pDlgSetReelmapSapp->GetClientRect(rtDlg0);
				rtDlg.left = rtForm.left + rtTab.left;
				rtDlg.top = rtForm.top + nHeithtSystemBar + rtTab.top;
				m_pDlgSetReelmapSapp->SetWindowPos(NULL, rtDlg.left, rtDlg.top, rtDlg0.Width(), rtDlg0.Height(), SWP_NOZORDER | SWP_NOACTIVATE);
			}
		}
		else
		{
			RefreshDlg();
			m_pDlgSetReelmapSapp->ShowWindow(SW_SHOW);
		}
		break;
	case 1:
		if (!m_pDlgSetItsOrigin)
		{
			m_pDlgSetItsOrigin = new CDlgSetItsOrigin(this);
			if (m_pDlgSetItsOrigin->GetSafeHwnd() == 0)
			{
				m_pDlgSetItsOrigin->Create();
				m_pDlgSetItsOrigin->ShowWindow(SW_SHOW);

				m_pDlgSetItsOrigin->GetClientRect(rtDlg1);
				rtDlg.left = rtForm.left + rtTab.left;
				rtDlg.top = rtForm.top + nHeithtSystemBar + rtTab.top;
				m_pDlgSetItsOrigin->SetWindowPos(NULL, rtDlg.left, rtDlg.top, rtDlg1.Width(), rtDlg1.Height(), SWP_NOZORDER | SWP_NOACTIVATE);
			}
		}
		else
		{
			RefreshDlg();
			m_pDlgSetItsOrigin->ShowWindow(SW_SHOW);
		}
		break;
	}
}

void CItsConverterDlg::HideAllDlg()
{
	if (m_pDlgSetReelmapSapp && m_pDlgSetReelmapSapp->GetSafeHwnd())
	{
		if (m_pDlgSetReelmapSapp->IsWindowVisible())
			m_pDlgSetReelmapSapp->ShowWindow(SW_HIDE);
	}

	if (m_pDlgSetItsOrigin && m_pDlgSetItsOrigin->GetSafeHwnd())
	{
		if (m_pDlgSetItsOrigin->IsWindowVisible())
			m_pDlgSetItsOrigin->ShowWindow(SW_HIDE);
	}
}

void CItsConverterDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow)
	{
		InitTab();
	}
}

void CItsConverterDlg::Refresh()
{
	if (m_pDlgSetReelmapSapp && m_pDlgSetReelmapSapp->GetSafeHwnd())
	{
		RefreshDlg();
	}
	else if (m_pDlgSetItsOrigin && m_pDlgSetItsOrigin->GetSafeHwnd())
	{
		RefreshDlg();
	}
}

void CItsConverterDlg::RefreshDlg()
{
	CRect rtForm, rtTab, rtDlg;
	CRect rtDlg0, rtDlg1;
	this->GetWindowRect(&rtForm);
	int nHeithtSystemBar = GetSystemMetrics(SM_CYCAPTION);
	GetDlgItem(IDC_STATIC_TAB1)->GetWindowRect(&rtTab);
	ScreenToClient(&rtTab);

	if (m_pDlgSetReelmapSapp && m_pDlgSetReelmapSapp->GetSafeHwnd())
	{
		//if (m_pDlgSetReelmapSapp->IsWindowVisible())
		{
			m_pDlgSetReelmapSapp->GetClientRect(rtDlg0);
			rtDlg.left = rtForm.left + rtTab.left;
			rtDlg.top = rtForm.top + nHeithtSystemBar + rtTab.top;
			m_pDlgSetReelmapSapp->SetWindowPos(NULL, rtDlg.left, rtDlg.top, rtDlg0.Width(), rtDlg0.Height(), SWP_NOZORDER | SWP_NOACTIVATE);
		}
	}
	if (m_pDlgSetItsOrigin && m_pDlgSetItsOrigin->GetSafeHwnd())
	{
		//if (m_pDlgSetItsOrigin->IsWindowVisible())
		{
			m_pDlgSetItsOrigin->GetClientRect(rtDlg1);
			rtDlg.left = rtForm.left + rtTab.left;
			rtDlg.top = rtForm.top + nHeithtSystemBar + rtTab.top;
			m_pDlgSetItsOrigin->SetWindowPos(NULL, rtDlg.left, rtDlg.top, rtDlg1.Width(), rtDlg1.Height(), SWP_NOZORDER | SWP_NOACTIVATE);
		}
	}
}


void CItsConverterDlg::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	Refresh();
}
