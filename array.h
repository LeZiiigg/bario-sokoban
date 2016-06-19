#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stddef.h>

void* createArray(size_t array_size, size_t elem_size, void* elem_zero);

int resizeArray(void** array, size_t array_size, size_t new_array_size, size_t elem_size, void* elem_zero, void (*elem_free)(void* elem));

void destroyArray(void* array, size_t array_size, size_t elem_size, void (*elem_free)(void* elem));

#endif /* __ARRAY_H__ */
