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

/*int add_e(tree* t, int* key, string* info, int arg) {
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
}*/

int add_e(tree* t, int* key, string* info) {
	if (t == NULL || key == NULL || info == NULL)
		return UN;
	if (t->left == NULL && t->right == NULL) {
		if (t->max_count_of_elements_on_lvl >= t->item->size_arrs + 2) {
			for (int i = 0; i <= t->item->size_arrs; i++) {
				if (t->item->keys[i][t->arg] < key[t->arg]) {
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
				item1->size_arrs = t->item->size_arrs / 2;
				item2->size_arrs = t->item->size_arrs / 2;
			}
			else {
				item1->size_arrs = t->item->size_arrs / 2 - 1;
				item2->size_arrs = t->item->size_arrs / 2;
			}
			item1->info = (string**)calloc(item1->size_arrs + 1, sizeof(string*));
			item1->keys = (int**)calloc(item1->size_arrs + 1, sizeof(int*));
			item2->info = (string**)calloc(item2->size_arrs + 1, sizeof(string*));
			item2->keys = (int**)calloc(item2->size_arrs + 1, sizeof(int*));
			for (int i = 0; i <= item1->size_arrs; i++) {
				item1->keys[i] = t->item->keys[i];
				item1->info[i] = t->item->info[i];
			}
			for (int i = 1; i <= item2->size_arrs; i++) {
				item2->keys[i] = t->item->keys[item1->size_arrs + i];
				item2->info[i] = t->item->info[item1->size_arrs + i];
			}
			free(t->item);
			t->item = NULL;
			// должна быть сортировка по arg+1 item1 item2
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
			t->border = (left->item->keys[left->item->size_arrs][t->arg] + right->item->keys[0][t->arg]) / 2;
			sort_item(item1, left->arg);
			sort_item(item2, right->arg);
			t->left = left;
			t->right = right;
			add_e(t, key, info);
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
	//if (key1 == NULL || key2 == NULL)
	//	return -1;
	for (int i = 0; i < size; i++)
		if (key1[i] == key2[i])
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
		if (t->border > key[t->arg])
			return scan(t->left, key, data);
	if (t->right != NULL)
		if (t->border <= key[t->arg])
			return scan(t->right, key, data);
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
}

void free_tree(tree* t) {
	if (t != NULL) {
		free_tree(t->left);
		free_tree(t->right);
		for (int i = 0; i < t->item->size_arrs; i++) {
			if (t->item->info[i] != NULL)
				free(t->item->info[i]);
			if (t->item->keys[i] != NULL)
				free(t->item->keys[i]);
		}
		free(t->item->keys);
		free(t->item->info);
	}
}
