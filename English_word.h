#pragma once
#define MAX_WORD 50
#define START_COUNT 0
#include "English_dictionary.h"
void insert_word(treenode **x, element word);
void delete_word(treenode **x, char word[]);
void clear(treenode *x);
class sort {
public:
	element arr_word[100];
	int word_flag;
	int index;
	int count;
	int flag;
	sort(int flag) :count(0), flag(flag) {}
	int is_empty_array();
	void swap_element(int index1, int index2);
	void element_copy(element b);
	void input_data(treenode *x);
	void quick_sort();
	void quick_sort(int left, int right);
	int partition(int left, int right);
	void display();
	void mix_array();
	int word_flag_set();
	void fileupload(treenode *x);
};
void change_key(treenode *x, int flag, char *word);
void file_upload(treenode **x);
element *search(treenode *x, char *word);