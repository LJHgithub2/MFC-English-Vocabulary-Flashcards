
// English_dictionaryDlg.cpp : 구현 파일
//
#include "stdafx.h"
#include "English_dictionary.h"
#include "English_dictionaryDlg.h"
#include "afxdialogex.h"
#include "English_word.h"
#include "Resource.h"
#include "temp.h"
#include "error.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	int result_answer_rate;
//	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)

{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_result_answer_rate, result_answer_rate);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEnglish_dictionaryDlg 대화 상자



CEnglish_dictionaryDlg::CEnglish_dictionaryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ENGLISH_DICTIONARY_DIALOG, pParent)
	, IDP_word_input(_T(""))
	, IDP_mean_input(_T(""))
	, select_mean(_T(""))
	, wordbook(0)
	, wordbook_mean(_T("    전체"))
	, favorite_val(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEnglish_dictionaryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDP_word, IDP_word);
	DDX_Text(pDX, IDP_word, IDP_word_input);
	DDV_MaxChars(pDX, IDP_word_input, 50);
	DDX_Text(pDX, IDP_mean, IDP_mean_input);
	//  DDX_Control(pDX, IDC_LIST_word, list_word);
	DDX_Control(pDX, IDC_LIST_word, list_word);
	DDX_Text(pDX, IDC_select_mean, select_mean);
	DDV_MaxChars(pDX, select_mean, 50);
	//  DDX_Radio(pDX, IDC_favorite_add, favorite_add);
	DDX_Radio(pDX, IDC_wordbook1, wordbook);
	DDX_Text(pDX, IDC_wordbook_mean, wordbook_mean);
	DDV_MaxChars(pDX, wordbook_mean, 50);
	DDX_Check(pDX, IDC_favorite, favorite_val);
}

BEGIN_MESSAGE_MAP(CEnglish_dictionaryDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_wordbook2, IDC_wordbook3, &CEnglish_dictionaryDlg::OnClickedWordbook1)
	ON_BN_CLICKED(IDC_input_word, &CEnglish_dictionaryDlg::OnClickedInputWord)
	ON_BN_CLICKED(IDC_delete_word, &CEnglish_dictionaryDlg::OnClickedDeleteWord)
	ON_BN_CLICKED(IDC_word_print, &CEnglish_dictionaryDlg::OnClickedWordPrint)
//	ON_NOTIFY(BCN_DROPDOWN, IDC_word_print, &CEnglish_dictionaryDlg::OnDropdownWordPrint)
ON_LBN_SELCHANGE(IDC_LIST_word, &CEnglish_dictionaryDlg::OnSelchangeListWord)
//ON_BN_CLICKED(IDC_favorite_set, &CEnglish_dictionaryDlg::OnClickedFavoriteSet)
//ON_BN_CLICKED(IDC_file_word, &CEnglish_dictionaryDlg::OnClickedFileWord)
ON_BN_CLICKED(IDC_word_modify, &CEnglish_dictionaryDlg::OnClickedWordModify)
ON_BN_CLICKED(IDC_wordbook1, &CEnglish_dictionaryDlg::OnClickedWordbook1)
ON_BN_CLICKED(IDC_favorite, &CEnglish_dictionaryDlg::OnClickedFavorite)
ON_BN_CLICKED(IDC_test_word, &CEnglish_dictionaryDlg::OnClickedTestWord)
//ON_BN_CLICKED(IDC_file_upload, &CEnglish_dictionaryDlg::OnClickedFileUpload)
ON_BN_CLICKED(IDCANCEL, &CEnglish_dictionaryDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CEnglish_dictionaryDlg 메시지 처리기

BOOL CEnglish_dictionaryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	theApp.tree = NULL;
	file_upload(&(theApp.tree));
	OnClickedWordPrint();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CEnglish_dictionaryDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CEnglish_dictionaryDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CEnglish_dictionaryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CEnglish_dictionaryDlg::OnClickedInputWord()
{	
	UpdateData();
	if (IDP_word_input.IsEmpty() || IDP_mean_input.IsEmpty()) {
		return;
	}
	element word;

	int len = IDP_word_input.GetLength();
	int n = WideCharToMultiByte(CP_ACP, 0, IDP_word_input, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, IDP_word_input,-1, word.word, n, NULL, NULL);
	len = IDP_mean_input.GetLength();
	n =WideCharToMultiByte(CP_ACP, 0, IDP_mean_input, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, IDP_mean_input, -1, word.mean, n, NULL, NULL);
	word.favorite = 0;
	word.wrong = 0;
	insert_word(&(theApp.tree), word);

	IDP_word_input.SetString(_T(""));
	IDP_mean_input.SetString(_T(""));
	UpdateData(FALSE);
	OnClickedWordPrint();
	sort sort(0);
	sort.fileupload(theApp.tree);
}


void CEnglish_dictionaryDlg::OnClickedDeleteWord()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString temp;
	if (list_word.GetCurSel() < 0)return;
	list_word.GetText(list_word.GetCurSel(), temp);
	char word[MAX_WORD];
	int len = temp.GetLength();
	int n = WideCharToMultiByte(CP_ACP, 0, temp, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, temp, -1, word, n, NULL, NULL);
	delete_word(&(theApp.tree), word);
	OnClickedWordPrint();

	sort sort(0);
	sort.fileupload(theApp.tree);
}


void CEnglish_dictionaryDlg::OnClickedWordPrint()
{
	UpdateData();
	sort sort(0);
	switch (wordbook) {
	case 0:
		wordbook_mean = _T("    전체");
		break;
	case 1:
		wordbook_mean = _T("    오답");
		sort.flag = 1;
		break;
	case 2:
		wordbook_mean = _T("즐겨찾기");
		sort.flag = 2;
		break;

	}
	list_word.ResetContent();
	sort.input_data(theApp.tree);
	CString temp;
	for (int i = 0; i < sort.count; i++) {
		temp = sort.arr_word[i].word;
		list_word.AddString(temp);
	}
	UpdateData(FALSE);
}




void CEnglish_dictionaryDlg::OnSelchangeListWord()
{
	CString temp;

	if (list_word.GetCurSel() < 0)return;
	list_word.GetText(list_word.GetCurSel(), temp);
	char word[MAX_WORD];
	int len = temp.GetLength();
	int n = WideCharToMultiByte(CP_ACP, 0, temp, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, temp, -1, word, n, NULL, NULL);
	element *mean = search(theApp.tree, word);
	select_mean = mean->mean;
	IDP_mean_input = mean->mean;
	IDP_word_input = mean->word;
	if (mean->favorite == 0) {
		favorite_val = false;
	}
	else
		favorite_val = true;
	UpdateData(FALSE);
}


//void CEnglish_dictionaryDlg::OnClickedFavoriteSet()
//{
//	UpdateData();
//	CString temp;
//	if (list_word.GetCurSel() < 0)return;
//	list_word.GetText(list_word.GetCurSel(), temp);
//	char word[MAX_WORD];
//	int len = temp.GetLength();
//	int n = WideCharToMultiByte(CP_ACP, 0, temp, -1, NULL, 0, NULL, NULL);
//	WideCharToMultiByte(CP_ACP, 0, temp, -1, word, n, NULL, NULL);
//	element *mean = search(theApp.tree, word);
//	if (favorite_add) {
//		mean->favorite = 0;
//	}
//	else {
//		mean->favorite = 1;
//	}
//}


//void CEnglish_dictionaryDlg::OnClickedFileWord()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}


void CEnglish_dictionaryDlg::OnClickedWordModify()
{
	if (list_word.GetCurSel() < 0)return;
	OnClickedDeleteWord();
	OnClickedInputWord();
	OnClickedWordPrint();
	sort sort(0);
	sort.fileupload(theApp.tree);
}
void CEnglish_dictionaryDlg::OnClickedWordbook1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnClickedWordPrint();
}

void CEnglish_dictionaryDlg::OnClickedWordbook1(UINT uid)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnClickedWordPrint();
}


void CEnglish_dictionaryDlg::OnClickedFavorite()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	CString temp;
	if (list_word.GetCurSel() < 0)return;
	list_word.GetText(list_word.GetCurSel(), temp);
	char word[MAX_WORD];
	int len = temp.GetLength();
	int n = WideCharToMultiByte(CP_ACP, 0, temp, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, temp, -1, word, n, NULL, NULL);
	element *mean = search(theApp.tree, word);
	if (favorite_val) {
		mean->favorite = 1;
	}
	else mean->favorite = 0;
	OnClickedWordPrint();
}


void CEnglish_dictionaryDlg::OnClickedTestWord()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	temp dlg;
	int i;
	switch (wordbook) {
	case 0:
		i = 0;
		break;
	case 1:
		i = 1;
		break;
	case 2:
		i = 2;
		break;

	}
	sort sort(i);
	sort.input_data(theApp.tree);
	if (sort.count == 0) {
		error dlg;
		dlg.DoModal();
		return;
	}
	dlg.flag = i;
	if (dlg.DoModal() == IDOK) {
	}

	OnClickedWordPrint();

}


//BOOL CAboutDlg::OnInitDialog()
//{
//	CDialogEx::OnInitDialog();
//
//	// TODO:  여기에 추가 초기화 작업을 추가합니다.
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
//}


//void CEnglish_dictionaryDlg::OnClickedFileUpload()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}


void CEnglish_dictionaryDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


BOOL CEnglish_dictionaryDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
			return TRUE;
		else if (pMsg->wParam == VK_RETURN) {
			OnClickedInputWord();
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
