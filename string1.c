#include "string1.h"

int get_s(string** s) {
	*s = (string*)calloc(1, sizeof(string));
	(*s)->size = -1;
	char a = 0;
	char* p = NULL;
	int b = scanf("%c", &a);
	if (b < 0)
		return CZ1;
	while (a == '\n' || a == ' ')
		scanf("%c", &a);
	while (a != ' ' && a != '\n' && b > 0) {
		(*s)->size++;
		if ((*s)->string == NULL)
			(*s)->string = (char*)malloc(sizeof(char));
		else {
			p = (*s)->string;
			(*s)->string = (char*)realloc((*s)->string, ((*s)->size + 1) * sizeof(char));
		}
		if ((*s)->string == NULL) {
			free(p);
			return OF1;
		}
		(*s)->string[(*s)->size] = a;
		b = scanf("%c", &a);
		if (b < 0)
			return CZ1;
	}
	(*s)->string = (char*)realloc((*s)->string, ((*s)->size + 2) * sizeof(char));
	(*s)->string[(*s)->size + 1] = '\0';
	return OK1;
}

int compar(string* s1, string* s2) {
	if (s1 == NULL || s2 == NULL)
		return 0;
	if (s1->string == NULL || s2->string == NULL)
		return 0;
	if (s1->size != s2->size)
		return 0;
	else
		for (int i = 0; i <= s1->size; i++)
			if (s1->string[i] != s2->string[i])
				return 0;
	return 1;
}

void free_s(string** s) {
	if (*s != NULL) {
		if ((*s)->string != NULL) {
			free((*s)->string);
			(*s)->string = NULL;
			(*s)->size = -2;
		}
		free(*s);
		*s = NULL;
	}
}

int strcp(string* s1, string** s2) {
	if (s1 == NULL)
		return UN1;
	*s2 = (string*)calloc(1, sizeof(string));
	(*s2)->string = (char*)calloc(s1->size + 1, sizeof(char));
	(*s2)->size = s1->size;
	for (int i = 0; i <= s1->size; i++) {
		(*s2)->string[i] = s1->string[i];
	}
	return OK1;
}

int get_f(string** s, FILE* file) {
	char buffer = ' ';
	int a;
	*s = (string*)calloc(1, sizeof(string));
	(*s)->size = -1;
	(*s)->string = (char*)calloc(1, sizeof(char));
	a = fread(&buffer, sizeof(char), 1, file);
	while (a >= 1 && buffer != '\n' && buffer != ' ') {
		(*s)->size += 1;
		(*s)->string = (char*)realloc((*s)->string, ((*s)->size + 2) * sizeof(char));
		(*s)->string[(*s)->size] = buffer;
		a = fread(&buffer, sizeof(char), 1, file);
	}
	if (a <= 0 && (*s)->size >= 0)
		return OF1;
	if ((*s)->size == -1) {
		free_s(s);
		return UN1;
	}
	(*s)->string[(*s)->size + 1] = '\0';
	return OK1;
}

int create_random_string(string** s, int size) {
	if (size < 0)
		return UN1;
	*s = (string*)calloc(1, sizeof(string));
	if (*s == NULL)
		return OF1;
	(*s)->size = size;
	(*s)->string = (char*)calloc((*s)->size + 2, sizeof(char));
	if ((*s)->string == NULL) {
		free(*s);
		return OF1;
	}
	for (int i = 0; i <= (*s)->size; i++)
		(*s)->string[i] = 'a' + rand() % 26;
	(*s)->string[(*s)->size + 1] = '\0';
	return OK1;
}

int create_random_arr_of_string(string*** arr_s, int arr_size, int el_size) {
	if (arr_size < 1 || el_size < 0)
		return UN1;
	*arr_s = (string**)calloc(arr_size, sizeof(string*));
	if (*arr_s == NULL)
		return OF1;
	int error;
	for (int i = 0; i < arr_size; i++) {
		error = create_random_string(&(*arr_s)[i], el_size);
		if (error) {
			for (int j = 0; j < i; j++)
				free_s(&(*arr_s)[i]);
			free(*arr_s);
			return error;
		}
	}
	return OK1;
}

void print_string(string* s) {
	if (s != NULL)
		if (s->string != NULL)
			for (int i = 0; i <= s->size; i++)
				printf("%c", s->string[i]);
}
