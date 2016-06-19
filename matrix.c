#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "array.h"

void* create_matrix(size_t width, size_t height, size_t size, void* zero)
{
	void* matrix;
	int i;

	matrix = create_array(width, sizeof(void*), NULL);
	if (matrix == NULL)
		goto exception_matrix_bad_alloc;

	for (i = 0; i < width; i++)
	{
		((void**)matrix)[i] = create_array(height, size, zero);
		if (((void**)matrix)[i] == NULL)
			goto exception_matrix_i_bad_alloc;
	}
	return matrix;

	for (i = width - 1; i >= 0; i++)
	{
		destroy_array(((void**)matrix)[i], height, size, NULL);
exception_matrix_i_bad_alloc:
		;
	}
	destroy_array(matrix, width, sizeof(void*), NULL);

exception_matrix_bad_alloc:
	return NULL;
}

int resize_matrix(void* matrix, size_t width, size_t height, size_t new_width, size_t new_height, size_t size, void* zero, void (*destruct)(void*))
{
	void* new_matrix;
	int i;

	if (matrix == NULL)
		goto exception_matrix_null;

	new_matrix = create_matrix(new_width, new_height, size, NULL);
	if (new_matrix == NULL)
		goto exception_new_matrix_bad_alloc;

	for (i = 0; (i < new_width && zero != NULL) || i < width; i++)
	{
		if (i < new_width && i < width)
			get_into_array((*(void***)matrix)[i], height, ((void**)new_matrix)[i], new_height, size, zero, destruct);
		else if (i >= width)
			fill_array(((void**)new_matrix)[i], new_height, size, zero);
		else if (i >= new_width)
			clear_array((*(void***)matrix)[i], height, size, destruct);
	}
	*((void**)matrix) = new_matrix;
	return 1;

exception_new_matrix_bad_alloc:
exception_matrix_null:
	return 0;
}

void destroy_matrix(void* matrix, size_t width, size_t height, size_t size, void (*destruct)(void*))
{
	int i;
	for (i = 0; i < width; i++)
		destroy_array(((void**)matrix)[i], height, size, destruct);
	destroy_array(matrix, width, sizeof(void*), NULL);
}
