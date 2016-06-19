#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* memcpy */

#include "array.h"

void* createArray(size_t length, size_t size, void* zero)
{
	void* array;
	int i;

	array = malloc(length * size);
	if (array == NULL)
		goto exception_array_bad_alloc;

	if (zero != NULL)
	{
		for (i = 0; i < length; i++)
		{
			memcpy((char*)array + i * size, zero, size);
		}
	}
	return array;

exception_array_bad_alloc:
	return NULL;
}

int resizeArray(void* array, size_t length, size_t new_length, size_t size, void* zero, void (*destruct)(void* elem))
{
	void* new_array;
	if (array == NULL)
		goto exception_array_null;

	new_array = createArray(new_length, size, NULL);
	if (new_array == NULL)
		goto exception_new_array_bad_alloc;

	getIntoArray(*((void**)array), length, new_array, new_length, size, zero, destruct);
	*((void**)array) = new_array;
	return 1;

exception_new_array_bad_alloc:
exception_array_null:
	return 0;
}

void getIntoArray(void* src_array, size_t src_length, void* dst_array, size_t dst_length, size_t size, void* zero, void (*destruct)(void*))
{
	int i, i_max;
	if (dst_length > src_length)
		i_max = (zero != NULL) ? dst_length : src_length;
	else
		i_max = (destruct != NULL) ? src_length : dst_length;
	for (i = 0; i < i_max; i++)
	{
		if (i < src_length && i < dst_length)
			memcpy((char*)dst_array + i * size, (char*)src_array + i * size, size);
		else if (i >= src_length)
			memcpy((char*)dst_array + i * size, zero, size);
		else if (i >= dst_length)
			(*destruct)((char*)src_array + i * size);
	}
	free(*(void**)src_array);
}

void destroyArray(void* array, size_t length, size_t size, void (*destruct)(void* elem))
{
	int i;
	if (array != NULL)
	{
		if (destruct != NULL)
		{
			for (i = 0; i < length; i++)
			{
				(*destruct)((char*)array + i * size);
			}
		}
		free(array);
	}
}
