#include "tree_b.h"

void create_tree(tree** t, int max_count_of_elements_on_lvl, int k) {
	*t = (tree*)calloc(1, sizeof(tree));
	(*t)->max_count_of_elements_on_lvl = max_count_of_elements_on_lvl;
	(*t)->k = k;
	(*t)->parent = NULL;
	(*t)->right = NULL;
	(*t)->left = NULL;
	(*t)->item = (item*)calloc(1, sizeof(item));
	(*t)->item->size_arrs = -1;
	(*t)->item->info = (string**)calloc((*t)->max_count_of_elements_on_lvl, sizeof(string*));
	(*t)->item->keys = (int**)calloc((*t)->max_count_of_elements_on_lvl, sizeof(int));
	(*t)->border = NULL;
}

int add_e(tree* t, int* key, string* info, int arg) {
	if (t == NULL || key == NULL || info == NULL)
		return UN;
	if (t->left == NULL && t->right == NULL) {
		if (t->max_count_of_elements_on_lvl >= t->item->size_arrs + 2) {
			int flag = 1;
			for (int i = 0; i <= t->item->size_arrs + 1; i++) {
				if (i != t->item->size_arrs + 1) {
					if (compar_keys(t->item->keys[i], key, t->k))
						return DB;
					if (t->item->keys[i][arg] < key[arg]) {
						flag = 0;
						string* buffer1_info = t->item->info[i], * buffer2_info = NULL;
						int* buffer1_key = t->item->keys[i], * buffer2_key = NULL;
						for (int j = i; j < t->item->size_arrs + 1; j++) {
							buffer2_key = t->item->keys[j + 1];
							buffer2_info = t->item->info[j + 1];
							t->item->keys[j + 1] = buffer1_key;
							t->item->info[j + 1] = buffer1_info;
							buffer1_key = buffer2_key;
							buffer1_info = buffer2_info;
						}
						t->item->size_arrs += 1;
						t->item->keys[i] = key;
						t->item->info[i] = info;
						return OK;
					}
				}
				if (i == t->item->size_arrs + 1 && flag) {
					return OK;
					t->item->keys[i] = key;
					t->item->info[i] = info;
					t->item->size_arrs += 1;
				}
			}
		}
		else {
			for (int i = 0; i <= t->item->size_arrs; i++)
				if (compar_keys(key, t->item->keys[i], arg))
					return DB;
			item* left_buffer = (item*)calloc(1, sizeof(item)), * right_buffer = (item*)calloc(1, sizeof(item));

			for (int i = 0; i < t->border[arg] / 2; i++) {
				left_buffer->keys
			}
		}
	}
	else {
		if (arg + 1 == t->k)
			arg = -1;
		if (t->border[arg] >= key[arg])
			return add_e(t, key, info, arg + 1);
		if (t->border[arg] < key[arg])
			return add_e(t, key, info, arg + 1);
	}
}

int compar_keys(int* key1, int* key2, int size) {
	//if (key1 == NULL || key2 == NULL)
	//	return -1;
	for (int i = 0; i < size; i++)
		if (key1[i] == key2[i])
			return 1;
	return 0;
}

void free_tree(tree* t) {
	if (t != NULL) {
		free_tree(t->left);
		free_tree(t->right);
		for (int i = 0; i < t->item->size_arrs; i++) {
			if (t->item->info[i] != NULL)
				free(t->item->info[i]);
			free(t->item->info);
			if (t->item->keys[i] != NULL)
				free(t->item->keys[i]);
			free(t->item->keys);
		}
	}
}