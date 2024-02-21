
// English_dictionary.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once
#define MAX_WORD 50
#define START_COUNT 0


#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif
#include "resource.h"		// �� ��ȣ�Դϴ�.
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
// �� Ŭ������ ������ ���ؼ��� English_dictionary.cpp�� �����Ͻʽÿ�.
//

class CEnglish_dictionaryApp : public CWinApp
{
public:
	CEnglish_dictionaryApp();
	treenode *tree;
	int answer;
	int wrong;
// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CEnglish_dictionaryApp theApp;