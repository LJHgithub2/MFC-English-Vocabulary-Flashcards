#pragma once


// test_result ��ȭ �����Դϴ�.

class test_result : public CDialog
{
	DECLARE_DYNAMIC(test_result)

public:
	test_result(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~test_result();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	double result_wrong;
	double result_answer;
	int result_answer_rate;
	virtual BOOL OnInitDialog();
};
