
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

	m_nMachine = -1; m_nModel = -1; m_nLot = -1; m_nLayer = -1;
	m_sModel = _T(""); m_sLot = _T(""); m_sLayerSel = _T(""); 
	m_sLayer[0] = _T(""); m_sLayer[1] = _T(""); m_sProcessCode = _T(""), m_sItsCode = _T("");
	m_nTestMode = MODE_NONE;
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
	ON_CBN_SELCHANGE(IDC_COMBO_MACHINE, &CItsConverterDlg::OnSelchangeComboMachine)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CItsConverterDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_RADIO8, &CItsConverterDlg::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO9, &CItsConverterDlg::OnBnClickedRadio9)
	ON_BN_CLICKED(IDC_RADIO10, &CItsConverterDlg::OnBnClickedRadio10)
	ON_CBN_SELCHANGE(IDC_COMBO_MODEL, &CItsConverterDlg::OnSelchangeComboModel)
	ON_LBN_SELCHANGE(IDC_LIST_LAYER, &CItsConverterDlg::OnSelchangeListLayer)
	ON_LBN_SELCHANGE(IDC_LIST_LOT, &CItsConverterDlg::OnSelchangeListLot)
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
	this->SetWindowText(_T("ITS Data Converter (version: 1.0.0) ;  Update Date(2025,10,29)"));

	Init();

	SetTimer(0, 100, NULL);

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
	int			nLenth;

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
	sTabCaption[0] = _T("Reelmap && SAPP");
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

	m_nCurTab = 0;
	m_TabCtrl.HighlightItem(m_nCurTab, TRUE);

	ShowDlg(m_nCurTab);
}

void CItsConverterDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	// 현재 설정된 SUB UNIT의 인덱스값(0기준)을 얻는다.
	m_TabCtrl.HighlightItem(m_nCurTab, FALSE);

	m_nCurTab = m_TabCtrl.GetCurSel();
	m_TabCtrl.HighlightItem(m_nCurTab, TRUE);
	ShowDlg(m_nCurTab);
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

int CItsConverterDlg::MsgBox(CString sMsg, int nType)
{
	CMsgBox msg(sMsg, nType, this);
	msg.DoModal();
	return msg.GetRtn();
}

BOOL CItsConverterDlg::CheckItsOrigin()
{
	int nItsOriginCase = GetItsOriginCase(m_sModel);
	int nCurrOriginCase = GetCurrOriginCase(m_sModel);
	if (nItsOriginCase != nCurrOriginCase && nItsOriginCase > -1)
	{
		CString sMsg = _T("현재 모델의 ITS파일은 원본 Origin과 다릅니다.\r\n원본 Origin기준으로 ITS파일을 재생성하세요.");
		int nRtn = MsgBox(sMsg, MB_OK);
		//HideAllDlg();
		//AfxMessageBox(sMsg);
		////this->MessageBox(sMsg, _T("주의"), MB_OK | MB_ICONQUESTION);
		//ShowDlg(m_nCurTab);
		return FALSE;
	}

	if (nItsOriginCase < 0 || nCurrOriginCase < 0)
		return FALSE;

	return TRUE;
}

void CItsConverterDlg::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	Refresh();
}

void CItsConverterDlg::SetRadioTestMode(int nIdx)
{
	m_nTestMode = nIdx;

	CButton* Btn[3];
	Btn[0] = (CButton*)GetDlgItem(IDC_RADIO8);
	Btn[1] = (CButton*)GetDlgItem(IDC_RADIO9);
	Btn[2] = (CButton*)GetDlgItem(IDC_RADIO10);

	Btn[0]->SetCheck(FALSE);
	Btn[1]->SetCheck(FALSE);
	Btn[2]->SetCheck(FALSE);

	switch (nIdx)
	{
	case 0:
		Btn[0]->SetCheck(TRUE);
		break;
	case 1:
		Btn[1]->SetCheck(TRUE);
		break;
	case 2:
		Btn[2]->SetCheck(TRUE);
		break;
	default:
		break;
	}
}

void CItsConverterDlg::Init()
{
	LoadInfo();

	InitTestMode();
	InitComboMachine();
	InitComboModel();
	InitListLot();
	InitListLayer();
	InitProcessCode();
	InitItsCode();
}

void CItsConverterDlg::InitTestMode()
{
	if (m_nTestMode < 0) return;
	SetRadioTestMode(m_nTestMode);
}

void CItsConverterDlg::InitComboMachine()
{
	if (!m_stIni.Machine) return;

	int nTot = m_stIni.nTotalMachine;
	if (nTot < 1) return;

	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_MACHINE);
	CString sItem;
	for (int i = 0; i < nTot; i++)
	{
		sItem = m_stIni.Machine[i].sName;
		pCombo->InsertString(i, sItem);
	}

	if (m_nMachine > -1)	pCombo->SetCurSel(m_nMachine);
}

void CItsConverterDlg::InitComboModel()
{
	ModifyModel();
	m_nModel = GetIdxComboModel(m_sModel);
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_MODEL);
	pCombo->SetCurSel(m_nModel);
}

void CItsConverterDlg::InitListLot()
{
	GetDlgItem(IDC_EDIT_LOT)->SetWindowText(m_sLot);

	ModifyLot();
	m_nLot = GetIdxListLot(m_sLot);
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_LOT);
	if (m_nLot > -1)	pList->SetCurSel(m_nLot);
}

void CItsConverterDlg::InitListLayer()
{
	ModifyLayer();
	m_nLayer = GetIdxListLayer(m_sLayerSel);
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_LAYER);
	if (m_nLayer > -1)	pList->SetCurSel(m_nLayer);
}

void CItsConverterDlg::InitProcessCode()
{
	GetDlgItem(IDC_EDIT_PROC)->SetWindowText(m_sProcessCode);
}

void CItsConverterDlg::InitItsCode()
{
	GetDlgItem(IDC_EDIT_ITS)->SetWindowText(m_sItsCode);
}

int CItsConverterDlg::GetIdxComboModel(CString sModel)
{
	int nIdx = -1;
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_MODEL);
	int nCount = pCombo->GetCount();
	CString sLine = _T("");
	for (int i = 0; i < nCount; i++)
	{
		pCombo->GetLBText(i, sLine);
		if (sLine == sModel)
			return i;
	}
	return nIdx;
}

int CItsConverterDlg::GetIdxListLot(CString sLot)
{
	int nIdx = -1;
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_LOT);
	int nCount = pList->GetCount();
	CString sLine = _T("");
	for (int i = 0; i < nCount; i++)
	{
		pList->GetText(i, sLine);
		if (sLine == sLot)
			return i;	
	}
	return nIdx;
}

int CItsConverterDlg::GetIdxListLayer(CString sLayer)
{
	int nIdx = -1;
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_LAYER);
	int nCount = pList->GetCount();
	CString sLine = _T("");
	for (int i = 0; i < nCount; i++)
	{
		pList->GetText(i, sLine);
		if (sLine == sLayer)
			return i;
	}
	return nIdx;
}

void CItsConverterDlg::SetEmptyModel()
{
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_MODEL);
	pCombo->ResetContent();
	m_nModel = -1;
	m_sModel = _T("");

	SetEmptyLot();
	SetEmptyLayer();
}

void CItsConverterDlg::SetEmptyLot()
{
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_LOT);
	pList->ResetContent();
	m_nLot = -1;
	m_sLot = _T("");

	SetEmptyLayer();
}

void CItsConverterDlg::SetEmptyLayer()
{
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_LAYER);
	pList->ResetContent();
	m_nLayer = -1;
	m_sLayerSel = _T("");
	m_sLayer[0] = _T("");
	m_sLayer[1] = _T("");
}

void CItsConverterDlg::ModifyModel()
{
	if (m_nMachine < 0) 
	{
		SetEmptyModel();
		return;
	}

	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_MODEL);
	pCombo->ResetContent();

	CString Dir, sName;
	Dir = m_stIni.Machine[m_nMachine].sPath + _T("MarkedFile");

	TCHAR FN[100];
	_stprintf(FN, _T("%s\\*.*"), Dir);
	pCombo->Dir(0x8010, FN);

	//"[..]"를 제거 
	int nIndex = pCombo->FindStringExact(-1, _T("[..]"));
	if (nIndex > -1)	pCombo->DeleteString(nIndex);
	int nCount = pCombo->GetCount();

	CString strBuf, strBuf2;
	int i;
	for (i = nCount; i > 0; i--)
	{
		int nCurr = i - 1;
		pCombo->GetLBText(nCurr, strBuf);
		if (strBuf.GetLength() < 3)
		{
			pCombo->DeleteString(nCurr);
			continue;
		}

		// 기종이름에서 "[]"를 제거 
		strBuf2 = strBuf.Mid(1, strBuf.GetLength() - 2);
		pCombo->DeleteString(nCurr);
		pCombo->InsertString(nCurr, strBuf2);
	}
}

void CItsConverterDlg::ModifyLot()
{
	if (m_nMachine < 0 || m_sModel.IsEmpty())
	{
		SetEmptyLot();
		return;
	}

	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_LOT);
	pList->ResetContent();

	CString Dir, strFileName;
	Dir = m_stIni.Machine[m_nMachine].sPath + _T("MarkedFile\\") + m_sModel;

	TCHAR FN[100];
	_stprintf(FN, _T("%s\\*.*"), Dir);
	pList->Dir(0x8010, FN);

	//"[..]"를 제거 
	pList->DeleteString(0);
	int nIndex = pList->FindStringExact(-1, _T("[..]"));
	if (nIndex > -1)	pList->DeleteString(nIndex);
	int nCount = pList->GetCount();

	CString strBuf, strBuf2;
	int i;
	for (i = nCount; i > 0; i--)
	{
		int nCurr = i - 1;
		pList->GetText(nCurr, strBuf);

		if (strBuf.GetLength() < 3)
		{
			pList->DeleteString(nCurr);
			continue;
		}

		// 기종이름에서 "[]"를 제거 
		CString strBuf2 = strBuf.Mid(1, strBuf.GetLength() - 2);
		pList->DeleteString(nCurr);
		pList->InsertString(nCurr, strBuf2);
	}
}

void CItsConverterDlg::ModifyLayer()
{
	if (m_nMachine < 0 || m_sModel.IsEmpty() || m_sLot.IsEmpty())
	{
		SetEmptyLayer();
		return;
	}

	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_LAYER);
	pList->ResetContent();

	CString Dir, strFileName;
	Dir = m_stIni.Machine[m_nMachine].sPath + _T("MarkedFile\\") + m_sModel + _T("\\") + m_sLot;

	TCHAR FN[100];
	_stprintf(FN, _T("%s\\*.*"), Dir);
	pList->Dir(0x8010, FN);

	//"[..]"를 제거 
	pList->DeleteString(0);
	int nIndex = pList->FindStringExact(-1, _T("[..]"));
	if (nIndex > -1)	pList->DeleteString(nIndex);
	int nCount = pList->GetCount();

	CString strBuf, strBuf2;
	int i;
	for (i = nCount; i > 0; i--)
	{
		int nCurr = i - 1;
		pList->GetText(nCurr, strBuf);

		if (strBuf.GetLength() < 3)
		{
			pList->DeleteString(nCurr);
			continue;
		}

		// 기종이름에서 "[]"를 제거 
		CString strBuf2 = strBuf.Mid(1, strBuf.GetLength() - 2);
		pList->DeleteString(nCurr);
		pList->InsertString(nCurr, strBuf2);
	}
}

int CItsConverterDlg::GetCurrOriginCase(CString sModel)
{
	CString sPathItsInfoFile;
	sPathItsInfoFile.Format(_T("%sMarkedFile\\%s\\ItsInfo.ini"), m_stIni.Machine[m_nMachine].sPath, sModel);

	int nDataOrigin = -1; // Not Found
	TCHAR szData[MAX_PATH];
	if (0 < ::GetPrivateProfileString(_T("Info"), _T("DataOrigin"), NULL, szData, sizeof(szData), sPathItsInfoFile))
		nDataOrigin = _ttoi(szData);

	return nDataOrigin;
}

int CItsConverterDlg::GetItsOriginCase(CString sModel)
{
	CString sPathItsOriginList = m_stIni.sPathItsOriginList;
	CString sListModel = _T("");
	int nCase = 0;

	TCHAR szData[MAX_PATH];
	TCHAR *token;
	TCHAR sep[] = { _T(",;\r\n\t") };

	int nModelIdx, nTotalModel;
	CString sModelIdx = _T("");

	if (0 < ::GetPrivateProfileString(_T("Info"), _T("Total_Models"), NULL, szData, sizeof(szData), sPathItsOriginList))
		nTotalModel = _ttoi(szData);
	else
		nTotalModel = 0;

	for (nModelIdx = 0; nModelIdx < nTotalModel; nModelIdx++)
	{
		sModelIdx.Format(_T("%d"), nModelIdx);

		if (0 < ::GetPrivateProfileString(_T("Model"), sModelIdx, NULL, szData, sizeof(szData), sPathItsOriginList))
		{
			token = _tcstok(szData, sep);
			sListModel = CString(token);
			token = _tcstok(NULL, sep);
			nCase = _ttoi(token);
		}
		else
			sListModel = _T("");

		if (sListModel == sModel)
			return nCase;
	}

	return -1; // Not Found
}

void CItsConverterDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	KillTimer(nIDEvent);
	switch (nIDEvent)
	{
	case 0:
		CheckItsOrigin();
		break;
	default:
		break;
	}

	CDialog::OnTimer(nIDEvent);
}

BOOL CItsConverterDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

int CItsConverterDlg::GetCurTab()
{
	return m_nCurTab;
}

CWnd* CItsConverterDlg::GetCurDlg()
{
	switch (m_nCurTab)
	{
	case 0:
		return m_pDlgSetReelmapSapp;
	case 1:
		return m_pDlgSetItsOrigin;
	default:
		return NULL;
	}
	
	return NULL;
}

void CItsConverterDlg::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sMsg = _T("현재 모델의 작업 내용을 저장하시겠습니까?");
	int nRtn = MsgBox(sMsg, MB_YESNO);

	if (IDYES == nRtn)
	{
		SaveInfo();
	}
}

void CItsConverterDlg::LoadInfo()
{
	m_nMachine = m_stIni.LastJob.nMachine;
	m_sModel = m_stIni.LastJob.sModel;
	m_sLot = m_stIni.LastJob.sLot;
	m_sLayerSel = m_stIni.LastJob.sLayer;
	m_sLayer[0] = m_stIni.LastJob.sLayerUp;
	m_sLayer[1] = m_stIni.LastJob.sLayerDn;
	m_sProcessCode = m_stIni.LastJob.sProcessNum;
	m_sItsCode = m_stIni.LastJob.sItsCode;
	m_nTestMode = m_stIni.LastJob.nTestMode;
}

void CItsConverterDlg::SaveInfo()
{
	m_stIni.LastJob.nMachine = m_nMachine;
	m_stIni.LastJob.sModel = m_sModel;
	m_stIni.LastJob.sLot = m_sLot;
	m_stIni.LastJob.sLayer = m_sLayerSel;
	m_stIni.LastJob.sLayerUp = m_sLayer[0];
	m_stIni.LastJob.sLayerDn = m_sLayer[1];
	m_stIni.LastJob.sProcessNum = m_sProcessCode;
	m_stIni.LastJob.sItsCode = m_sItsCode;
	m_stIni.LastJob.nTestMode = m_nTestMode;

	m_stIni.SaveIni();
}


void CItsConverterDlg::OnBnClickedRadio8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetRadioTestMode(MODE_DUAL);
}


void CItsConverterDlg::OnBnClickedRadio9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetRadioTestMode(MODE_INNER);
}


void CItsConverterDlg::OnBnClickedRadio10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetRadioTestMode(MODE_OUTER);
}

void CItsConverterDlg::ResetModel()
{
	m_nModel = -1; m_sModel = _T("");
	ModifyModel();
	ResetLot();
	ResetLayer();
	ResetTestMode();
	ResetProcessCode();
	ResetItsCode();
}

void CItsConverterDlg::ResetLot()
{
	m_nLot = -1; m_sLot = _T("");
	GetDlgItem(IDC_EDIT_LOT)->SetWindowText(m_sLot);
	ModifyLot();
	ResetLayer();
	ResetTestMode();
	ResetProcessCode();
	ResetItsCode();
}

void CItsConverterDlg::ResetLayer()
{
	m_nLayer = -1; m_sLayerSel = _T(""); m_sLayer[0] = _T(""); m_sLayer[1] = _T("");
	ModifyLayer();
	ResetTestMode();
	ResetProcessCode();
	ResetItsCode();
}

void CItsConverterDlg::ResetProcessCode()
{
	m_sProcessCode = _T("");
	GetDlgItem(IDC_EDIT_PROC)->SetWindowText(m_sProcessCode);
}

void CItsConverterDlg::ResetItsCode()
{
	m_sItsCode = _T("");
	GetDlgItem(IDC_EDIT_ITS)->SetWindowText(m_sItsCode);
}

void CItsConverterDlg::ResetTestMode()
{
	SetRadioTestMode(MODE_NONE);
}

void CItsConverterDlg::OnSelchangeComboMachine()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_MACHINE);
	int nIndex = pCombo->GetCurSel();
	if (nIndex != LB_ERR)
	{
		m_nMachine = nIndex;
		ResetModel();
	}
}

void CItsConverterDlg::OnSelchangeComboModel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_MODEL);
	int nIndex = pCombo->GetCurSel();
	if (nIndex != LB_ERR)
	{
		m_nModel = nIndex;
		pCombo->GetLBText(m_nModel, m_sModel);
		ResetLot();
	}
}

void CItsConverterDlg::OnSelchangeListLot()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_LOT);
	int nIndex = pList->GetCurSel();
	if (nIndex != LB_ERR)
	{
		m_nLot = nIndex;
		pList->GetText(m_nLot, m_sLot);
		ResetLayer();
	}
}

void CItsConverterDlg::OnSelchangeListLayer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_LAYER);
	int nIndex = pList->GetCurSel();
	if (nIndex != LB_ERR)
	{
		m_nLayer = nIndex;
		pList->GetText(m_nLayer, m_sLayerSel);
		// LoadPcr
	}
}

