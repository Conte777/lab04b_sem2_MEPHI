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
	int** keys; //массив ключей
	int size_arrs; // идекс последниего элемента в массивах
}item;


typedef struct tree {
	item* item; // если элемент дерева не лист == NULL, иначе там хранятся ключи + информация
	struct tree* left, * right;
	int border; // граница на текущем уровне, по которой определяем куда кинуть элемент
	int max_count_of_elements_on_lvl; // максимальное количество элементов в листе
	int k; // размерность дерева
	int arg; // элемент по которому сравнивается куда распределить элемент
}tree;

void create_tree(tree** t, int max_count_of_elements_on_lvl, int k);

int add_e(tree* t, int* key, string* info);

int scan(tree* t, int* key, string** data);

int scan_neighbor(tree* t, int* key, int* distance, int** key_data, string** info_data);

int scan_max(tree* t, int** key_data, string** info_data);

int del_e(tree* t, int* key);

int sort_item(item* item, int arg);

int print_tree(tree* t);

int compar_keys(int* key1, int* key2, int size);

int add_e_from_file(tree* t, FILE* file);

void free_tree(tree* t);
