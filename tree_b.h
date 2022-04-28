#include <stdio.h>
#include <stdlib.h>
#include "string1.h"
#include <string.h>
#include <time.h>

typedef enum {
	OK = 0,
	OF = 1,
	UN = 2,
	DB = 3,
	CZ = 4
} errors;

typedef struct item {
	string** info; // массив строк 
	int** keys, size_arrs; // массив ключей, идекс последниего элемента в массивах
}item;


typedef struct tree {
	item* item; // если элемент дерева не лист == NULL
	struct tree* left, * right, * parent;
	int border, max_count_of_elements_on_lvl, k, arg;
}tree;

void create_tree(tree** t, int max_count_of_elements_on_lvl, int k);

int add_e(tree* t, int* key, string* info);

int scan(tree* t, int* key, string** data);

int sort_item(item* item, int arg);

int print_tree(tree* t);

int compar_keys(int* key1, int* key2, int size);

void free_tree(tree* t);
