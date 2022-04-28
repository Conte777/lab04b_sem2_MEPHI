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
	(*t)->arg = 0;
}

int add_e(tree* t, int* key, string* info) {
	if (t == NULL || key == NULL || info == NULL)
		return UN;
	if (t->left == NULL && t->right == NULL) {
		if (t->max_count_of_elements_on_lvl >= t->item->size_arrs + 2) {
			for (int i = 0; i <= t->item->size_arrs; i++) {
				if (t->item->keys[i][t->arg] > key[t->arg]) {
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
				if (compar_keys(t->item->keys[i], key, t->k))
					return DB;
			}
			t->item->size_arrs += 1;
			t->item->keys[t->item->size_arrs] = key;
			t->item->info[t->item->size_arrs] = info;
			return OK;
		}
		else {
			for (int i = 0; i <= t->item->size_arrs; i++)
				if (compar_keys(key, t->item->keys[i], t->k))
					return DB;
			item* item1 = (item*)calloc(1, sizeof(item));
			item* item2 = (item*)calloc(1, sizeof(item));
			if ((t->item->size_arrs + 1) % 2 == 0) {
				item1->size_arrs = (t->item->size_arrs + 1) / 2 - 1;
				item2->size_arrs = (t->item->size_arrs + 1) / 2 - 1;
			}
			else {
				item1->size_arrs = (t->item->size_arrs + 1) / 2 - 1;
				item2->size_arrs = (t->item->size_arrs + 1) / 2;
			}
			item1->info = (string**)calloc(t->max_count_of_elements_on_lvl, sizeof(string*));
			item1->keys = (int**)calloc(t->max_count_of_elements_on_lvl, sizeof(int*));
			item2->info = (string**)calloc(t->max_count_of_elements_on_lvl, sizeof(string*));
			item2->keys = (int**)calloc(t->max_count_of_elements_on_lvl, sizeof(int*));
			for (int i = 0; i <= item1->size_arrs; i++) {
				item1->keys[i] = t->item->keys[i];
				item1->info[i] = t->item->info[i];
			}
			for (int i = 0; i <= item2->size_arrs; i++) {
				item2->keys[i] = t->item->keys[item1->size_arrs + 1 + i];
				item2->info[i] = t->item->info[item1->size_arrs + 1 + i];
			}
			free(t->item->keys);
			free(t->item->info);
			free(t->item);
			t->item = NULL;
			tree* left = (tree*)calloc(1, sizeof(tree));
			tree* right = (tree*)calloc(1, sizeof(tree));
			if (t->arg + 1 < t->k) {
				left->arg = t->arg + 1;
				right->arg = t->arg + 1;
			}
			else {
				left->arg = 0;
				right->arg = 0;
			}
			left->max_count_of_elements_on_lvl = t->max_count_of_elements_on_lvl;
			right->max_count_of_elements_on_lvl = t->max_count_of_elements_on_lvl;
			left->item = item1;
			right->item = item2;
			left->parent = t;
			right->parent = t;
			left->k = t->k;
			right->k = t->k;
			// обращаюсь за границы массива, не вижу где
			t->border = 0;
			t->border += left->item->keys[left->item->size_arrs][t->arg];
			t->border += right->item->keys[0][t->arg];
			t->border /= 2;
			sort_item(item1, left->arg);
			sort_item(item2, right->arg);
			t->left = left;
			t->right = right;
			add_e(t, key, info);
			return OK;
		}
	}
	else {
		if (t->left != NULL)
			if (t->border > key[t->arg])
				return add_e(t->left, key, info);
		if (t->right != NULL)
			if (t->border <= key[t->arg])
				return add_e(t->right, key, info);
	}
	return UN;
}

int sort_item(item* item, int arg) {
	for (int i = 0; i <= item->size_arrs; i++)
		for (int j = i + 1; j <= item->size_arrs; j++) {
			if (item->keys[i][arg] > item->keys[j][arg]) {
				int* buffer_key = item->keys[i];
				string* buffer_info = item->info[i];
				item->keys[i] = item->keys[j];
				item->info[i] = item->info[j];
				item->keys[j] = buffer_key;
				item->info[j] = buffer_info;
			}
		}
	return OK;
}

int compar_keys(int* key1, int* key2, int size) {
	int flag = 1;
	for (int i = 0; i < size; i++)
		if (key1[i] != key2[i])
			flag = 0;
	if (flag)
		return 1;
	return 0;
}

int scan(tree* t, int* key, string** data) {
	if (t == NULL || key == NULL)
		return UN;
	if (t->right == NULL && t->left == NULL) {
		for (int i = 0; i <= t->item->size_arrs; i++)
			if (compar_keys(key, t->item->keys[i], t->k)) {
				*data = t->item->info[i];
				return OK;
			}
	}
	if (t->left != NULL)
		if (t->border >= key[t->arg])
			return scan(t->left, key, data);
	if (t->right != NULL)
		if (t->border < key[t->arg])
			return scan(t->right, key, data);
	return UN;
}

int scan_max(tree* t, int** key_data, string** info_data) {
	if (t == NULL)
		return UN;
	tree* ptr = t;
	while (ptr->right != NULL)
		ptr = ptr->right;
	*key_data = ptr->item->keys[ptr->item->size_arrs];
	*info_data = ptr->item->info[ptr->item->size_arrs];
	return OK;
}

int del_e(tree* t, int* key) {
	if (t == NULL || key == NULL)
		return UN;
	if (t->left != NULL)
		if (t->border >= key[t->arg])
			return del_e(t->left, key);
	if (t->right != NULL)
		if (t->border < key[t->arg])
			return del_e(t->right, key);
	if (t->left == NULL && t->right == NULL) {
		if (t->item->size_arrs < 0)
			return UN;
		for (int i = 0; i <= t->item->size_arrs; i++) {
			if (compar_keys(key, t->item->keys[i], t->k)) {
				free(t->item->keys[i]);
				free_s(&t->item->info[i]);
				if (i != t->item->size_arrs) {
					for (int j = i; j <= t->item->size_arrs; j++) {
						t->item->keys[j] = t->item->keys[j + 1];
						t->item->info[j] = t->item->info[j + 1];
					}
					t->item->keys[t->item->size_arrs + 1] = NULL;
					t->item->info[t->item->size_arrs + 1] = NULL;
				}
				t->item->size_arrs--;
				return OK;
			}
		}
	}
	return UN;
}

int print_tree(tree* t) {
	if (t == NULL)
		return UN;
	if (t->left != NULL)
		print_tree(t->left);
	if (t->left == NULL && t->right == NULL) {
		for (int i = 0; i <= t->item->size_arrs; i++) {
			for (int j = 0; j < t->k; j++)
				printf("%d ", t->item->keys[i][j]);
			print_string(t->item->info[i]);
			printf("\n");
		}
	}
	if (t->right != NULL)
		print_tree(t->right);
	return OK;
}

void free_tree(tree* t) {
	if (t != NULL) {
		free_tree(t->left);
		free_tree(t->right);
		if (t->item != NULL) {
			for (int i = 0; i <= t->item->size_arrs; i++) {
				if (t->item->info[i] != NULL)
					free_s(&t->item->info[i]);
				if (t->item->keys[i] != NULL)
					free(t->item->keys[i]);
			}
			free(t->item->keys);
			free(t->item->info);
			free(t->item);
		}
		free(t);
	}
}
