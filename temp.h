#pragma once
#include "resource.h"
#include "afxcmn.h"

// temp ��ȭ �����Դϴ�.

class temp : public CDialog
{
	DECLARE_DYNAMIC(temp)

public:
	temp(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~temp();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString answer_input;
	int answer_int;
//	double answer_rate;
	CString detail_question;
	CString question;
	int timer_sec;
	int wrong_int;
	int flag;
	sort pub_sort;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClickedTestStart();
	CProgressCtrl progress;
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedSubmit();
	int answer_rate;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnClickedTestExit();
};
