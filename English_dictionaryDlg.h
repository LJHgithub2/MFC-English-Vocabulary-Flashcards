
// English_dictionaryDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CEnglish_dictionaryDlg 대화 상자
class CEnglish_dictionaryDlg : public CDialogEx
{
// 생성입니다.
public:
	CEnglish_dictionaryDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ENGLISH_DICTIONARY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedInputWord();
	// 단어입력시 사용되는 입력창
	CString IDP_word_input;
	CString IDP_mean_input;
	afx_msg void OnClickedDeleteWord();
	afx_msg void OnClickedWordPrint();
//	CListCtrl list_word;
//	afx_msg void OnDropdownWordPrint(NMHDR *pNMHDR, LRESULT *pResult);
	CListBox list_word;
	afx_msg void OnSelchangeListWord();
	CString select_mean;
//	afx_msg void OnClickedFavoriteSet();
//	int favorite_add;
//	afx_msg void OnClickedFileWord();
	int wordbook;
	CString wordbook_mean;
	afx_msg void OnClickedWordModify();
	afx_msg void OnClickedWordbook1(UINT uid);
	afx_msg void OnClickedWordbook1();
	BOOL favorite_val;
	afx_msg void OnClickedFavorite();
	afx_msg void OnClickedTestWord();
//	afx_msg void OnClickedFileUpload();
	afx_msg void OnBnClickedCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
