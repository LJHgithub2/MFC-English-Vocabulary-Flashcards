// test_result.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "English_dictionary.h"
#include "test_result.h"
#include "afxdialogex.h"
#include "English_word.h"


// test_result ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(test_result, CDialog)

test_result::test_result(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ABOUTBOX, pParent)
	, result_wrong(0)
	, result_answer(0)
	, result_answer_rate(0)
{

}

test_result::~test_result()
{
}

void test_result::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_result_wrong, result_wrong);
	DDX_Text(pDX, IDC_result_answer, result_answer);
	DDX_Text(pDX, IDC_result_answer_rate, result_answer_rate);
	DDV_MinMaxInt(pDX, result_answer_rate, 0, 100);
}


BEGIN_MESSAGE_MAP(test_result, CDialog)
END_MESSAGE_MAP()


// test_result �޽��� ó�����Դϴ�.


BOOL test_result::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	result_wrong=theApp.wrong;
	result_answer = theApp.answer;
	if (result_answer == 0 && result_wrong == 0) {
		result_answer_rate = 0;
	}
	else if (result_wrong == 0) result_answer_rate = 100;
	else result_answer_rate = (double)result_answer / (double)(result_wrong + result_answer) * 100;

	
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
