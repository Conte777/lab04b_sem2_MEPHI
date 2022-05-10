#include "tree_b.h"

int scanfs(int* a, int b);
int errors_get(int a, string* s);
int choice(tree* t, int a);
void get_key(int** key, int size);
void print_key(int* key, int size);

int errors_get(int a, string* s) {
	switch (a) {
	case CZ:
		return CZ;
	case OF:
		printf("The line is too long! Try again: ");
		errors_get(get_s(&s), s);
	}
	return OK;
}

void get_key(int** key, int size) {
	*key = (int*)calloc(size, sizeof(int));
	for (int i = 0; i < size; i++)
		scanfs(&(*key)[i], 0);
}

void print_key(int* key, int size) {
	for (int i = 0; i < size; i++)
		printf("%d ", key[i]);
}

int choice(tree* t, int a) {
	int* key, * key_data, error, ** range;
	float distace;
	string* info, * info_data;
	FILE* file = NULL;
	switch (a) {
	case 1:
		printf("Enter key: ");
		get_key(&key, t->k);
		printf("Enter info: ");
		get_s(&info);
		error = add_e(t, key, info);
		switch (error) {
		case OK:
			printf("The item was successfully added\n");
			break;
		case UN:
			free(key);
			free_s(&info);
			printf("Tree is empty\n");
			break;
		case DB:
			free(key);
			free_s(&info);
			printf("Duplicate found\n");
			break;
		}
		return OK;
	case 2:
		printf("Enter key: ");
		get_key(&key, t->k);
		if (!scan(t, key, &info_data)) {
			printf("Here's what was found on your key:\nkey: ");
			print_key(key, t->k);
			printf("\ninfo: ");
			print_string(info_data);
			printf("\n");
		}
		else
			printf("An element with such a key was not found\n");
		free(key);
		return OK;
	case 3:
		printf("Enter key: ");
		get_key(&key, t->k);
		if (!del_e(t, key))
			printf("The item was successfully deleted\n");
		else
			printf("An element with such a key was not found\n");
		free(key);
		return OK;
	case 4:
		printf("Maximum element in the tree:\nkey: ");
		if (!scan_max(t, &key_data, &info_data)) {
			print_key(key_data, t->k);
			printf("\ninfo: ");
			print_string(info_data);
			printf("\n");
		}
		else
			printf("Tree is empty\n");
		return OK;
	case 5:
		printf("Enter key: ");
		get_key(&key, t->k);
		if (!scan_neighbor(t, key, &distace, &key_data, &info_data)) {
			printf("Here's what was found on your key:\ndistace: sqrt(%f)\nkey: ", distace);
			print_key(key_data, t->k);
			printf("\ninfo: ");
			print_string(info_data);
			printf("\n");
		}
		else
			printf("Tree is empty\n");
		free(key);
		return OK;
	case 6:
		printf("Enter file name: ");
		get_s(&info);
		file = fopen(info->string, "r");
		if (file != NULL) {
			if (!add_e_from_file(t, file))
				printf("The items was successfully added\n");
			else
				printf("Unable to open the file or something is wrong with the tree\n");
			fclose(file);
		}
		else
			printf("Unable to open the file or something is wrong with the tree\n");
		free_s(&info);
		return OK;
	case 7:
		if (print_tree(t, 0))
			printf("Something is wrong with the tree\n");
		return OK;
	case 8:
		file = fopen("viz.gv", "w+");
		if (file == NULL)
			return UN;
		if (viz_tree(t, file, 1) == OK) {
			fclose(file);
			system("dot -Tpng viz.gv -o viz.png");
			system("start viz.png");
		}
		else {
			printf("Tree is empty.\n");
			fclose(file);
		}
		remove("viz.gv");
		return OK;
	case 9:
		range = (int**)calloc(2, sizeof(int*));
		for (int i = 0; i < 2; i++) {
			printf("Enter key for range: ");
			get_key(&range[i], t->k);
		}
		printf("\nkey info\n");
		if (print_tree_in_range(t, range))
			printf("Tree is empty.\n");
		for (int i = 0; i < 2; i++)
			free(range[i]);
		free(range);
		return OK;
	case 10:
		test_scan_del_scan_neighbor(2, 10, 20000, 10000, 109, 10, 10000);
		return OK;
	case 11:
		test_add(2, 10, 10000, 10000, 110, 10, 9999);
		return OK;
	}
	return CZ;
}

int scanfs(int* a, int b) {
	int c;
	do {
		c = scanf("%d", a);
		if (c < 0)
			return 1;
		if ((b == 1 && *a <= 0) || c == 0) {
			printf("Error, try again: ");
			scanf("%*c");
		}
	} while ((b == 1 && *a <= 0) || c == 0);
	return 0;
}

int main() {
	int flag = 1, a = 0, b = 0, k, n;
	tree* t;
	printf("Enter dimension of the tree: ");
	scanfs(&k, 1);
	while (k < 0) {
		printf("Please enter a positive number: ");
		scanfs(&k, 1);
	}
	printf("Maximum number of elements per level: ");
	scanfs(&n, 1);
	while (n < 0) {
		printf("Please enter a positive number: ");
		scanfs(&k, 1);
	}
	create_tree(&t, n, k);
	while (flag) {
		printf("\nEnter the number of the item to be executed\n0. Exit\n1. Add new element\n2. Scan\n3. Delete\n4. Scaning max\n5. Scan neighbor\n6. Add items from a file\n7. Print tree\n8. Viz tree\n9. Print tree in range\nEnter number: ");
		b = scanf("%d", &a);
		// system("cls");
		if (b > 0 && a > 0 && a <= 12) {
			if (choice(t, a) == CZ)
				flag = 0;
		}
		else {
			if (b == 0) {
				printf("You didn't enter a number, try again: ");
				scanf("%*c");
			}
			else if (a == 0 || b < 0)
				flag = 0;
		}
	}
	free_tree(t);
	return 0;
}