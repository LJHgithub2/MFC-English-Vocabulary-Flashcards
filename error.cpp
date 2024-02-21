// error.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "English_dictionary.h"
#include "error.h"
#include "afxdialogex.h"


// error 대화 상자입니다.

IMPLEMENT_DYNAMIC(error, CDialogEx)

error::error(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

error::~error()
{
}

void error::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(error, CDialogEx)
END_MESSAGE_MAP()


// error 메시지 처리기입니다.
