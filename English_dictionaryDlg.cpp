
// English_dictionaryDlg.cpp : ���� ����
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


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CEnglish_dictionaryDlg ��ȭ ����



CEnglish_dictionaryDlg::CEnglish_dictionaryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ENGLISH_DICTIONARY_DIALOG, pParent)
	, IDP_word_input(_T(""))
	, IDP_mean_input(_T(""))
	, select_mean(_T(""))
	, wordbook(0)
	, wordbook_mean(_T("    ��ü"))
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


// CEnglish_dictionaryDlg �޽��� ó����

BOOL CEnglish_dictionaryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	theApp.tree = NULL;
	file_upload(&(theApp.tree));
	OnClickedWordPrint();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CEnglish_dictionaryDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		wordbook_mean = _T("    ��ü");
		break;
	case 1:
		wordbook_mean = _T("    ����");
		sort.flag = 1;
		break;
	case 2:
		wordbook_mean = _T("���ã��");
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
//	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnClickedWordPrint();
}

void CEnglish_dictionaryDlg::OnClickedWordbook1(UINT uid)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnClickedWordPrint();
}


void CEnglish_dictionaryDlg::OnClickedFavorite()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
//	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
//}


//void CEnglish_dictionaryDlg::OnClickedFileUpload()
//{
//	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
//}


void CEnglish_dictionaryDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}


BOOL CEnglish_dictionaryDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
