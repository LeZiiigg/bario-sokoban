#include <stdio.h>
#include <stdlib.h>

#include "containers/array.h"
#include "containers/matrix.h"
#include "containers/list.h"

struct int_node
{
	int integer;
	struct int_node* next;
	struct int_node* prev;
};

void print_int_array(int* array, int length);

void print_int_matrix(int** matrix, int width, int height);

void print_int_list(struct int_node* head);

void free_int(void* integer);

void free_int_node(void* node);

int main(int argc, char* argv[])
{
	int *array, **matrix;
	int none = -1;
	int i;

	printf("Array tests\n\n");

	array = array_create(10, sizeof(int), &none);
	print_int_array(array, 10);

	for (i = 0; i < 10; i++)
		array[i] = i;
	print_int_array(array, 10);

	array_resize(&array, 10, 6, sizeof(int), &none, &free_int);
	print_int_array(array, 6);

	array_resize(&array, 6, 10, sizeof(int), NULL, &free_int);
	print_int_array(array, 10);

	printf("\nMatrix tests\n\n");

	matrix = matrix_create(4, 4, sizeof(int), &none);
	print_int_matrix(matrix, 4, 4);

	for (i = 0; i < 16; i++)
		matrix[i%4][i/4] = i;
	print_int_matrix(matrix, 4, 4);

	matrix_resize(&matrix, 4, 4, 6, 3, sizeof(int), &none, free_int);
	print_int_matrix(matrix, 6, 3);

	matrix_resize(&matrix, 6, 3, 2, 5, sizeof(int), NULL, free_int);
	print_int_matrix(matrix, 2, 5);

	array_destroy(array, 10, sizeof(int), NULL);
	matrix_destroy(matrix, 2, 5, sizeof(int), NULL);

	return 0;
}

void print_int_array(int* array, int length)
{
	int i;
	printf("%p\t{", array);
	for (i = 0; i < length; i++)
	{
		printf("%d", array[i]);
		if (i < length - 1)
			printf(", ");
	}
	printf("}\n");
}

void print_int_matrix(int** matrix, int width, int height)
{
	int i, j;
	printf("%p\n", matrix);
	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
}

void print_int_list(struct int_node* head)
{
	struct int_node* it;
	printf("%p\t{", head);
	for (it = head; it != NULL; it = it->next)
	{
		printf("%d", it->integer);
		if (it->next != NULL)
			printf("->");
	}
	printf("}\n");
}

void free_int(void* integer)
{
	printf("free(%d)\n", *((int*)integer));
}

void free_int_node(void* node)
{
	printf("free(%d)\n", ((struct int_node*)node)->integer);
	free(node);
}
