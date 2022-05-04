#include <stdio.h>
#include <stdlib.h>

typedef enum {
	OK1 = 0,
	OF1 = 1,
	UN1 = 2,
	DB1 = 3,
	CZ1 = 4
} errors1;

typedef struct string {
	int size;
	char* string;
} string;

int get_s(string** s);

int compar(string* s1, string* s2);

void free_s(string** s);

int strcp(string* s1, string** s2);

int get_f(string** s, FILE* file);

int create_random_string(string** s, int size);

int create_random_arr_of_string(string*** arr_s, int arr_size, int el_size);

void print_string(string* s);
