// error.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "English_dictionary.h"
#include "error.h"
#include "afxdialogex.h"


// error ��ȭ �����Դϴ�.

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


// error �޽��� ó�����Դϴ�.
