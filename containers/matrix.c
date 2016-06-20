#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "array.h"

void* matrix_create(size_t width, size_t height, size_t size, void* zero)
{
	void* matrix;
	int i;

	matrix = array_create(width, sizeof(void*), NULL);
	if (matrix == NULL)
		goto exception_matrix_bad_alloc;

	for (i = 0; i < width; i++)
	{
		((void**)matrix)[i] = array_create(height, size, zero);
		if (((void**)matrix)[i] == NULL)
			goto exception_matrix_i_bad_alloc;
	}
	return matrix;

exception_matrix_i_bad_alloc:
	for (i--; i >= 0; i--)
		array_destroy(((void**)matrix)[i], height, size, NULL);
	array_destroy(matrix, width, sizeof(void*), NULL);

exception_matrix_bad_alloc:
	return NULL;
}

int matrix_resize(void* matrix, size_t width, size_t height, size_t new_width, size_t new_height, size_t size, void* zero, void (*destruct)(void*))
{
	void* new_matrix;
	int i;

	if (matrix == NULL)
		goto exception_matrix_null;

	new_matrix = matrix_create(new_width, new_height, size, NULL);
	if (new_matrix == NULL)
		goto exception_new_matrix_bad_alloc;

	for (i = 0; (i < new_width && zero != NULL) || i < width; i++)
	{
		if (i < new_width && i < width)
			array_get_into((*(void***)matrix)[i], height, ((void**)new_matrix)[i], new_height, size, zero, destruct);
		else if (i < new_width)
			array_fill(((void**)new_matrix)[i], new_height, size, zero);
		else if (i < width)
			array_destroy((*(void***)matrix)[i], height, size, destruct);
	}
	*((void**)matrix) = new_matrix;
	return 1;

exception_new_matrix_bad_alloc:
exception_matrix_null:
	return 0;
}

void matrix_destroy(void* matrix, size_t width, size_t height, size_t size, void (*destruct)(void*))
{
	int i;
	for (i = 0; i < width; i++)
		array_destroy(((void**)matrix)[i], height, size, destruct);
	array_destroy(matrix, width, sizeof(void*), NULL);
}
