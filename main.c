#include "tree_b.h"

int main() {
	tree* t = NULL;
	string* s, * data = NULL;
	int* key5;
	create_tree(&t, 3, 2);
	get_s(&s);
	int* key1 = (int*)calloc(2, sizeof(int));
	int* key2 = (int*)calloc(2, sizeof(int));
	int* key3 = (int*)calloc(2, sizeof(int));
	int* key4 = (int*)calloc(2, sizeof(int));
	key1[0] = 1;
	key1[1] = 2;
	key2[0] = 0;
	key2[1] = 0;
	key3[0] = 3;
	key3[1] = 3;
	key4[0] = 4;
	key4[1] = 4;
	add_e(t, key1, s);
	get_s(&s);
	add_e(t, key2, s);
	get_s(&s);
	add_e(t, key3, s);
	get_s(&s);
	add_e(t, key4, s);
	scan(t, key4, &data);
	print_string(data);
	printf("\n");
	scan_max(t, &key5, &data);
	print_tree(t);
	printf("\n");
	del_e(t, key5);
	print_tree(t);
	free_tree(t);
	return OK;
}
