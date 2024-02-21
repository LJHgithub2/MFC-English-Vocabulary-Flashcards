#include "stdafx.h"
#include "English_word.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include "English_dictionary.h"
#include <iostream>
#include <CString>
using namespace std;
void insert_word(treenode **x, element word) {
	treenode *newnode = new treenode;
	treenode *f = NULL;
	treenode *p = *x;
	newnode->left = newnode->right = NULL;
	newnode->word = word;
	if (!p) {
		*x = newnode;
		return;
	}
	while (p) {
		f = p;
		if (strcmp(p->word.word, word.word) > 0) {
			p = p->right;
		}
		else if (strcmp(p->word.word, word.word) < 0) {
			p = p->left;
		}
		else {
			return;
		}
	}
	if (strcmp(f->word.word, word.word) == 1) {
		f->right = newnode;
		return;
	}
	else {
		f->left = newnode;
		return;
	}
}

void delete_word(treenode **x, char word[]) {
	treenode *p, *f, *temp, *temp_f;
	p = *x;
	f = NULL;
	while (p && strcmp(word, p->word.word)) {
		f = p;
		if (strcmp(p->word.word, word) > 0) {
			p = p->right;
		}
		else if (strcmp(p->word.word, word) < 0) {
			p = p->left;
		}
	}
	if (!p) {
		return;
	}
	if (!p->left && !p->right) {
		if (f) {
			if (f->right == p) {
				f->right = NULL;
			}
			else {
				f->left = NULL;
			}
			delete p;
		}
		else {
			*x = NULL;
			delete p;
		}
	}
	else if (!p->left || !p->right) {
		temp = (p->right) ? p->right : p->left;
		if (f) {
			if (f->right == p) {
				f->right = temp;
			}
			else {
				f->left = temp;
			}
			delete p;
		}
		else {
			*x = temp;
			delete p;
		}
	}
	else {
		temp_f = p;
		temp = p->left;
		while (temp->right) {
			temp_f = temp;
			temp = temp->right;
		}
		if (temp_f->right == temp) temp_f->right = temp->left;
		else temp_f->left = temp->left;
		p->word = temp->word;
		delete temp;
	}
}
void sort::input_data(treenode *x) {
	treenode *p = x;
	if (p) {
		sort::input_data(p->left);
		sort::input_data(p->right);
		if (flag == 0) {
			element_copy(p->word);
			count++;
		}
		else if (p->word.wrong &&flag == 1) {
			element_copy(p->word);
			count++;
		}
		else if (p->word.favorite && flag == 2) {
			element_copy(p->word);
			count++;
		}
	}
}
void sort::element_copy(element b) {
	strcpy_s(arr_word[count].word, sizeof(char)*MAX_WORD, b.word);
	strcpy_s(arr_word[count].mean, sizeof(char)*MAX_WORD, b.mean);
	arr_word[count].favorite = b.favorite;
	arr_word[count].wrong = b.wrong;
}
element* search(treenode *x, char *word) {
	treenode *p = x;
	while (p) {
		if (strcmp(p->word.word, word) > 0) {
			p = p->right;
		}
		else if (strcmp(p->word.word, word) < 0) {
			p = p->left;
		}
		else {
			return &(p->word);
		}
	}
	return NULL;
}

void clear(treenode *x) {
	treenode *p = x;
	if (p) {
		clear(p->left);
		clear(p->right);
		delete p;
	}
}
void sort::swap_element(int index1, int index2) {
	element temp;
	temp = arr_word[index1];
	arr_word[index1] = arr_word[index2];
	arr_word[index2] = temp;
}
void sort::mix_array() {
	if (count == 1) { return; }
	for (int i = 0; i < count; i++) {
		swap_element(i, rand() % (count - 1));
	}
}

int sort::is_empty_array() {
	if (count > 0)return 0;
	else return 1;
}
int sort::word_flag_set() {
	if (0.5 >= (double)rand() / RAND_MAX) {
		return 1;
	}
	else return 0;
}
void file_upload(treenode **x) {
	int i = 0;
	FILE *fp;
	fopen_s(&fp, "word.txt", "r");
	if (fp) {
		char buffer[200];
		while (!feof(fp)) {
			char *context;
			element word;
			if (feof(fp))return;
			fgets(buffer, sizeof(buffer), fp);
			char *ptr = strtok_s(buffer, ":", &context);
			strcpy_s(word.word, sizeof(char)*MAX_WORD, ptr);
			ptr = strtok_s(NULL, "\n", &context);
			strcpy_s(word.mean, sizeof(char)*MAX_WORD, ptr);
			word.favorite = 0;
			word.wrong = 0;
			if (i >= 1) {
				insert_word(x, word);
			}
			i++;
		}
		fclose(fp);
	}
}
void sort::fileupload(treenode *x) {
	input_data(x);
	int i = 0;
	FILE *fp;
	fopen_s(&fp, "word.txt", "w");
	fprintf_s(fp, "영단어:단어뜻");
	if (fp) {
		for (int i = 0; i < count; i++) {
			fprintf_s(fp, "\n");
			fprintf_s(fp, "%s:%s",arr_word[i].word, arr_word[i].mean);
		}
	}
	fclose(fp);
}


