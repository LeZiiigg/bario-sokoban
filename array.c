#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* memcpy */

#include "array.h"

void* createArray(size_t length, size_t size, void* zero)
{
	void* array;
	array = malloc(length * size);
	if (array == NULL)
		goto exception_array_bad_alloc;

	fillArray(array, length, size, zero);
	return array;

exception_array_bad_alloc:
	return NULL;
}

void fillArray(void* array, size_t length, size_t size, void* value)
{
	int i;
	if (value != NULL)
	{
		for (i = 0; i < length; i++)
		{
			memcpy((char*)array + i * size, value, size);
		}
	}
}

void copyArray(void* src_array, size_t src_length, void* dst_array, size_t dst_length, size_t size)
{
	int i;
	for (i = 0; i < src_length && i < dst_length; i++)
	{
		memcpy((char*)dst_array + i * size, (char*)src_array + i * size, size);
	}
}

void clearArray(void* array, size_t length, size_t size, void (*destruct)(void*))
{
	int i;
	if (destruct != NULL)
	{
		for (i = 0; i < length; i++)
		{
			(*destruct)((char*)array + i * size);
		}
	}
}

void getIntoArray(void* src_array, size_t src_length, void* dst_array, size_t dst_length, size_t size, void* zero, void (*destruct)(void*))
{
	copyArray(src_array, src_length, dst_array, dst_length, size);
	if (dst_length > src_length)
		fillArray((char*)dst_array + src_length * size, dst_length - src_length, size, zero);
	else if (src_length > dst_length)
		clearArray((char*)src_array + dst_length * size, src_length - dst_length, size, destruct);
	free(src_array);
}

int resizeArray(void* array, size_t length, size_t new_length, size_t size, void* zero, void (*destruct)(void* elem))
{
	void* new_array;
	if (array == NULL)
		goto exception_array_null;

	if (new_length != length)
	{
		new_array = createArray(new_length, size, NULL);
		if (new_array == NULL)
			goto exception_new_array_bad_alloc;

		getIntoArray(*((void**)array), length, new_array, new_length, size, zero, destruct);
		*((void**)array) = new_array;
	}
	return 1;

exception_new_array_bad_alloc:
exception_array_null:
	return 0;
}

void destroyArray(void* array, size_t length, size_t size, void (*destruct)(void*))
{
	clearArray(array, length, size, destruct);
	free(array);
}
