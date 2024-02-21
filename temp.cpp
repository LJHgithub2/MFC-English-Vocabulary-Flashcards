// temp.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "English_dictionary.h"
#include "English_word.h"
#include "temp.h"
#include "afxdialogex.h"
#include "test_result.h"


// temp 대화 상자입니다.

IMPLEMENT_DYNAMIC(temp, CDialog)

temp::temp(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG2, pParent)
	, answer_input(_T(""))
	, answer_int(0)
	, detail_question(_T("스펠링/뜻을 입력해주세요."))
	, question(_T("질문"))
	, timer_sec(0)
	, wrong_int(0)
	, pub_sort(flag)
	, answer_rate(0)
{

}

temp::~temp()
{
}

void temp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_answer_input, answer_input);
	DDV_MaxChars(pDX, answer_input, 50);
	DDX_Text(pDX, IDC_answer_int, answer_int);
	//  DDX_Text(pDX, IDC_answer_rate, answer_rate);
	DDX_Text(pDX, IDC_detail_question, detail_question);
	DDX_Text(pDX, IDC_question, question);
	DDV_MaxChars(pDX, question, 50);
	DDX_Text(pDX, IDC_sec, timer_sec);
	DDX_Text(pDX, IDC_wrong_int, wrong_int);
	DDX_Control(pDX, IDC_PROGRESS1, progress);
	DDX_Text(pDX, IDC_answer_rate, answer_rate);
	DDV_MinMaxInt(pDX, answer_rate, 0, 100);
}




BEGIN_MESSAGE_MAP(temp, CDialog)
	//ON_BN_CLICKED(IDC_test_start, &temp::OnClickedTestStart)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_submit, &temp::OnClickedSubmit)
	ON_BN_CLICKED(IDCANCEL, &temp::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &temp::OnBnClickedOk)
	ON_BN_CLICKED(IDC_test_exit, &temp::OnClickedTestExit)
END_MESSAGE_MAP()


// temp 메시지 처리기입니다.

void temp::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 1) {
		int pos = progress.GetPos();
		if (pos > 0) progress.SetPos(pos - 1);
		else progress.SetPos(10);
		if (pos == 0) {
			OnClickedSubmit();
		}
		else timer_sec = --pos;
		CDataExchange dx(this, FALSE);
		DDX_Text(&dx, IDC_sec, timer_sec);
	}
	if (nIDEvent == 2) {
		
	}
	CDialog::OnTimer(nIDEvent);
}

void temp::OnClickedTestStart()
{
	//여기선 화면에 데이터들 입력하고 질문만하고 버튼에서 모든처리를하고 타이머 함수돌때 버튼 함수콜해서 틀린거 처리 여기는 마지막에 index++해주면됌
	if(pub_sort.word_flag){
	question=pub_sort.arr_word[pub_sort.index].word;
	detail_question = "단어 뜻을 입력하세요.";
	UpdateData(false);
	}
	else {
		question = pub_sort.arr_word[pub_sort.index].mean;
		detail_question = "단어 스펠링을 입력하세요.";
		UpdateData(false);
	}
	SetTimer(1, 1000 , NULL);
	
}

BOOL temp::OnInitDialog()
{
	srand((unsigned int)time(NULL));
	CDialog::OnInitDialog();
	pub_sort.flag=flag;
	pub_sort.input_data(theApp.tree);
	pub_sort.mix_array();
	pub_sort.word_flag=pub_sort.word_flag_set();
	pub_sort.index=0;


	progress.SetRange(0, 10);
	progress.SetPos(10);
	timer_sec = 10;
	UpdateData(false);
	OnClickedTestStart();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void temp::OnClickedSubmit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	KillTimer(1);
	progress.SetPos(10);
	UpdateData(true);
	timer_sec = 10;
	CString temp= answer_input;
	char word[MAX_WORD];
	int len = temp.GetLength();
	int n = WideCharToMultiByte(CP_ACP, 0, temp, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, temp, -1, word, n, NULL, NULL);
	element *wrong_word = search(theApp.tree, pub_sort.arr_word[pub_sort.index].word);
	if (pub_sort.word_flag) {
		if (strcmp(word, pub_sort.arr_word[pub_sort.index].mean) == 0) {
			answer_int++;
			if (pub_sort.flag == 1) {
				wrong_word->wrong = 0;
			}
		}
		else {
			wrong_int++;
			if (pub_sort.flag == 0 || pub_sort.flag == 2) {
				wrong_word->wrong = 1;
			}
		}
	}
	else {
		if(strcmp(word, pub_sort.arr_word[pub_sort.index].word) == 0) {
			answer_int++;
			if (pub_sort.flag == 1) {
				wrong_word->wrong = 0;
			}
		}
		else {
			wrong_int++;
			if (pub_sort.flag == 0 || pub_sort.flag == 2) {
				wrong_word->wrong = 1;
			}
		}
	}
	answer_input.SetString(_T(""));
	if (answer_int == 0 && wrong_int == 0) {
		answer_rate = 0;
	}
	else if (wrong_int == 0) answer_rate = 100;
	else answer_rate = (double)answer_int / (double)(wrong_int+ answer_int) * 100;
	UpdateData(false);
	pub_sort.index++;
	pub_sort.word_flag = pub_sort.word_flag_set();
	if (pub_sort.index == pub_sort.count) {
		theApp.answer = answer_int;
		theApp.wrong = wrong_int;
		test_result dlg;
		dlg.DoModal();
		CDialog::OnCancel();
	}
	OnClickedTestStart();
	
}


void temp::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void temp::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnClickedSubmit();
}


void temp::OnClickedTestExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	theApp.answer = answer_int;
	theApp.wrong = wrong_int;
	test_result dlg;
	dlg.DoModal();
	CDialog::OnCancel();
}
