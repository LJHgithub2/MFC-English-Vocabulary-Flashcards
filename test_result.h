#pragma once


// test_result 대화 상자입니다.

class test_result : public CDialog
{
	DECLARE_DYNAMIC(test_result)

public:
	test_result(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~test_result();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double result_wrong;
	double result_answer;
	int result_answer_rate;
	virtual BOOL OnInitDialog();
};
