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
	int i, i_max;

	if (array == NULL)
		goto exception_array_null;

	new_array = malloc(new_length * size);
	if (new_array == NULL)
		goto exception_new_array_bad_alloc;

	i_max = ((new_length > length && zero != NULL) || (new_length < length && destruct == NULL)) ? new_length : length;
	for (i = 0; i < i_max; i++)
	{
		if (i < new_length && i < length)
			memcpy((char*)new_array + i * size, *((char**)array) + i * size, size);
		else if (i >= length)
			memcpy((char*)new_array + i * size, zero, size);
		else if (i >= new_length)
			(*destruct)(*((char**)array) + i * size);
	}
	*((void**)array) = new_array;
	return 1;

exception_new_array_bad_alloc:
exception_array_null:
	return 0;
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
