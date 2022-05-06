#include "tree_b.h"

void create_tree(tree** t, int max_count_of_elements_on_lvl, int k) {
	*t = (tree*)calloc(1, sizeof(tree));
	(*t)->max_count_of_elements_on_lvl = max_count_of_elements_on_lvl;
	(*t)->k = k;
	(*t)->right = NULL;
	(*t)->left = NULL;
	(*t)->item = (item*)calloc(1, sizeof(item));
	(*t)->item->size_arrs = -1;
	(*t)->item->info = (string**)calloc((*t)->max_count_of_elements_on_lvl, sizeof(string*));
	(*t)->item->keys = (int**)calloc((*t)->max_count_of_elements_on_lvl, sizeof(int*));
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
			left->k = t->k;
			right->k = t->k;
			t->border = (float)left->item->keys[left->item->size_arrs][t->arg];
			t->border += (float)right->item->keys[0][t->arg];
			t->border /= 2.0;
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
	if (t->left != NULL && t->right != NULL) {
		if (t->border > key[t->arg])
			return scan(t->left, key, data);
		if (t->border < key[t->arg])
			return scan(t->right, key, data);
		if (t->border == key[t->arg]) {
			int error1, error2;
			error1 = scan(t->left, key, data);
			error2 = scan(t->right, key, data);
			if (!error1 || !error2)
				return OK;
			return UN;
		}
	}
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

int scan_neighbor(tree* t, int* key, int* distance, int** key_data, string** info_data) {
	if (t == NULL || key == NULL)
		return UN;
	if (t->left != NULL && t->right != NULL) {
		if (key[t->arg] != t->border) {
			if (key[t->arg] < t->border)
				scan_neighbor(t->left, key, distance, key_data, info_data);
			if (key[t->arg] > t->border)
				scan_neighbor(t->right, key, distance, key_data, info_data);
			int distance_to_box = t->border - key[t->arg];
			distance_to_box *= distance_to_box;
			int buffer_distance, * buffer_key = NULL;
			string* buffer_info = NULL;
			if (distance_to_box <= *distance) {
				if (key[t->arg] < t->border)
					scan_neighbor(t->right, key, &buffer_distance, &buffer_key, &buffer_info);
				if (key[t->arg] >= t->border)
					scan_neighbor(t->left, key, &buffer_distance, &buffer_key, &buffer_info);
				if (buffer_distance < *distance) {
					*distance = buffer_distance;
					*key_data = buffer_key;
					*info_data = buffer_info;
				}
			}
		}
		else {
			int* buffer_key1, * buffer_key2, buffer_distance1, buffer_distance2;
			string* buffer_info1, * buffer_info2;
			scan_neighbor(t->left, key, &buffer_distance1, &buffer_key1, &buffer_info1);
			scan_neighbor(t->right, key, &buffer_distance2, &buffer_key2, &buffer_info2);
			if (buffer_distance1 < buffer_distance2) {
				*key_data = buffer_key1;
				*info_data = buffer_info1;
				*distance = buffer_distance1;
			}
			else {
				*key_data = buffer_key2;
				*info_data = buffer_info2;
				*distance = buffer_distance2;
			}
		}
		return OK;
	}
	if (t->left == NULL && t->right == NULL) {
		int min_distance = 0, buffer_distance = 0, index = 0;
		for (int i = 0; i < t->k; i++)
			min_distance += (key[i] - t->item->keys[0][i]) * (key[i] - t->item->keys[0][i]);
		for (int i = 1; i <= t->item->size_arrs; i++) {
			for (int j = 0; j < t->k; j++)
				buffer_distance += (key[j] - t->item->keys[i][j]) * (key[j] - t->item->keys[i][j]);
			if (buffer_distance < min_distance) {
				min_distance = buffer_distance;
				index = i;
			}
		}
		*distance = min_distance;
		*key_data = t->item->keys[index];
		*info_data = t->item->info[index];
		return OK;
	}
	return UN;
}

int del_e(tree* t, int* key) {
	if (t == NULL || key == NULL)
		return UN;
	if (t->left != NULL && t->right != NULL) {
		int error = -1, flag = 0;
		if (t->left->item != NULL || t->right->item != NULL)
			flag = 1;
		if (t->border > key[t->arg])
			error = del_e(t->left, key);
		if (t->border < key[t->arg])
			error = del_e(t->right, key);
		if (t->border == key[t->arg]) {
			if (!del_e(t->left, key))
				error = OK;
			if (!del_e(t->right, key))
				error = OK;
		}
		if (flag && !error) {
			if (t->left->item->size_arrs + t->right->item->size_arrs + 2 <= t->max_count_of_elements_on_lvl) {
				t->item = (item*)calloc(1, sizeof(item));
				t->item->info = (string**)calloc(t->max_count_of_elements_on_lvl, sizeof(string*));
				t->item->keys = (int**)calloc(t->max_count_of_elements_on_lvl, sizeof(int*));
				t->item->size_arrs = -1;
				for (int i = 0; i <= t->left->item->size_arrs; i++) {
					t->item->keys[i] = t->left->item->keys[i];
					t->item->info[i] = t->left->item->info[i];
					t->item->size_arrs++;
				}
				for (int i = 0; i <= t->right->item->size_arrs; i++) {
					t->item->keys[i + 1 + t->left->item->size_arrs] = t->right->item->keys[i];
					t->item->info[i + 1 + t->left->item->size_arrs] = t->right->item->info[i];
					t->item->size_arrs++;
				}
				free(t->left->item->info);
				free(t->left->item->keys);
				free(t->left->item);
				free(t->left);
				free(t->right->item->info);
				free(t->right->item->keys);
				free(t->right->item);
				free(t->right);
				t->left = NULL;
				t->right = NULL;
				t->border = 0;
			}
			return OK;
		}
	}
	if (t->left == NULL && t->right == NULL) {
		if (t->item->size_arrs < 0)
			return UN;
		for (int i = 0; i <= t->item->size_arrs; i++) {
			if (compar_keys(key, t->item->keys[i], t->k)) {
				free(t->item->keys[i]);
				free_s(&t->item->info[i]);
				if (i != t->item->size_arrs) {
					for (int j = i; j < t->item->size_arrs; j++) {
						t->item->keys[j] = t->item->keys[j + 1];
						t->item->info[j] = t->item->info[j + 1];
					}
					t->item->keys[t->item->size_arrs] = NULL;
					t->item->info[t->item->size_arrs] = NULL;
				}
				t->item->size_arrs--;
				return OK;
			}
		}
	}
	return UN;
}

int print_tree(tree* t, int shift) {
	if (t == NULL)
		return UN;
	if (t->left != NULL) {
		printf("[%d: %f] - left ", t->arg, t->border);
		print_tree(t->left, shift + 1);
	}
	if (t->left == NULL && t->right == NULL) {
		for (int i = 0; i <= t->item->size_arrs; i++) {
			printf("(");
			for (int j = 0; j < t->k; j++)
				if (j != t->k - 1)
					printf("%d, ", t->item->keys[i][j]);
				else
					printf("%d", t->item->keys[i][j]);
			printf(") ");
			print_string(t->item->info[i]);
			printf("  ");
		}
		if (t->item->size_arrs >= 0)
			printf("\n");
	}
	if (t->right != NULL) {
		for (int i = 0; i < shift; i++)
			printf("\t\t\t");
		printf("\t      \\ right ");
		print_tree(t->right, shift + 1);
	}
	return OK;
}

int add_e_from_file(tree* t, FILE* file) {
	if (t == NULL || file == NULL)
		return UN;
	int* key = (int*)calloc(t->k, sizeof(int));
	string* info;
	for (int i = 0; i < t->k; i++)
		if (fscanf(file, "%d ", &key[i]) <= 0)
			return UN;
	int error = get_f(&info, file);
	switch (error) {
	case OK:
		add_e(t, key, info);
		add_e_from_file(t, file);
		break;
	case UN:
		break;
	case OF:
		add_e(t, key, info);
		break;
	}
	return OK;
}

int create_random_key(int** key, int k) {
	*key = (int*)calloc(k, sizeof(int));
	if (*key == NULL)
		return UN;
	for (int i = 0; i < k; i++)
		(*key)[i] = rand();
	return OK;
}

int create_random_arr_of_keys(int*** keys, int k, int size_of_array) {
	*keys = (int**)calloc(size_of_array, sizeof(int*));
	for (int i = 0; i < size_of_array; i++)
		if (create_random_key(&(*keys)[i], k))
			return OF;
	return OK;
}

int add_random_items_to_tree(tree* t, int count_of_elements) {
	for (int i = 0; i < count_of_elements; i++) {
		int* buffer_key;
		string* buffer_info;
		if (create_random_string(&buffer_info, 0))
			return UN;
		if (create_random_key(&buffer_key, t->k))
			return UN;
		if (add_e(t, buffer_key, buffer_info)) {
			free(buffer_key);
			free_s(&buffer_info);
			i--;
		}
	}
	return OK;
}

int test_scan_del_scan_neighbor(int k, int n, int start_pos, int step, int count_of_steps, int count_of_tests, int size_of_arr_for_test) {
	tree* t;
	srand(time(NULL));
	float* time_scan = (float*)calloc(count_of_steps + 1, sizeof(float));
	float* time_del = (float*)calloc(count_of_steps + 1, sizeof(float));
	float* time_scan_neighbor = (float*)calloc(count_of_steps + 1, sizeof(float));
	for (int i = 0; i < count_of_tests; i++) {
		create_tree(&t, n, k);
		printf("Test #%d\n", i + 1);
		int** key_array_for_test, start, end;
		create_random_arr_of_keys(&key_array_for_test, k, size_of_arr_for_test);
		for (int j = 0; j < count_of_steps; j++) {
			if (j == 0)
				add_random_items_to_tree(t, start_pos);
			else
				add_random_items_to_tree(t, step);
			int* buffer_key, buffer_distace, count_of_del = 0;
			string* buffer_data;
			start = clock();
			for (int l = 0; l < size_of_arr_for_test; l++)
				scan(t, key_array_for_test[l], &buffer_data);
			end = clock();
			time_scan[j] = (float)(end - start) / (float)CLOCKS_PER_SEC;
			start = clock();
			for (int l = 0; l < size_of_arr_for_test; l++)
				scan_neighbor(t, key_array_for_test[l], &buffer_distace, &buffer_key, &buffer_data);
			end = clock();
			time_scan_neighbor[j] = (float)(end - start) / (float)CLOCKS_PER_SEC;
			start = clock();
			for (int l = 0; l < size_of_arr_for_test; l++)
				if (del_e(t, key_array_for_test[l]))
					count_of_del++;
			end = clock();
			time_del[j] = (float)(end - start) / (float)CLOCKS_PER_SEC;
			add_random_items_to_tree(t, count_of_del);
		}
		for (int j = 0; j < size_of_arr_for_test; j++)
			free(key_array_for_test[j]);
		free(key_array_for_test);
		free_tree(t);
	}
	for (int i = 0; i < count_of_steps; i++)
		printf("%f %f %f\n", time_scan[i] / (float)count_of_tests, time_scan_neighbor[i] / (float)count_of_tests, time_del[i] / (float)count_of_tests);
	free(time_scan);
	free(time_del);
	free(time_scan_neighbor);
	return OK;
}

int test_add(int k, int n, int start_pos, int step, int count_of_steps, int count_of_tests, int size_of_arr_for_test) {
	tree* t;
	srand(time(NULL));
	float* time_add = (float*)calloc(count_of_steps + 1, sizeof(float));
	string** string_array_for_test;
	if (create_random_arr_of_string(&string_array_for_test, size_of_arr_for_test, 0))
		return OF;
	for (int i = 0; i < count_of_tests; i++) {
		create_tree(&t, n, k);
		printf("Test #%d\n", i + 1);
		int** key_array_for_test, start, end;
		for (int j = 0; j < count_of_steps; j++) {
			if (create_random_arr_of_keys(&key_array_for_test, k, size_of_arr_for_test))
				return OF;
			if (j == 0) {
				if (add_random_items_to_tree(t, start_pos))
					return OF;
			}
			else
				if (add_random_items_to_tree(t, step - size_of_arr_for_test))
					return OF;
			start = clock();
			for (int l = 0; l < size_of_arr_for_test; l++)
				if (add_e(t, key_array_for_test[l], string_array_for_test[l]) == DB)
					free(key_array_for_test[l]);
			end = clock();
			free(key_array_for_test);
			time_add[j] = (float)(end - start) / (float)CLOCKS_PER_SEC;
		}
		free(string_array_for_test);
		free_tree(t);
	}
	for (int i = 0; i < count_of_steps; i++)
		printf("%f\n", time_add[i] / (float)count_of_tests);
	free(time_add);
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
