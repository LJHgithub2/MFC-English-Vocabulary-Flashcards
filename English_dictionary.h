
// English_dictionary.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once
#define MAX_WORD 50
#define START_COUNT 0


#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif
#include "resource.h"		// 주 기호입니다.
typedef struct element {
	char word[MAX_WORD];
	char mean[MAX_WORD];
	int wrong;
	int favorite;
}element;
typedef struct treenode {
	element word;
	struct treenode *left, *right;
}treenode;

// CEnglish_dictionaryApp:
// 이 클래스의 구현에 대해서는 English_dictionary.cpp을 참조하십시오.
//

class CEnglish_dictionaryApp : public CWinApp
{
public:
	CEnglish_dictionaryApp();
	treenode *tree;
	int answer;
	int wrong;
// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.

	DECLARE_MESSAGE_MAP()
};

extern CEnglish_dictionaryApp theApp;