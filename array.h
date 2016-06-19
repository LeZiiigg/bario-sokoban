#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stddef.h>

void* createArray(size_t length, size_t size, void* zero);

int resizeArray(void* array, size_t length, size_t new_length, size_t size, void* zero, void (*destruct)(void* elem));

void destroyArray(void* array, size_t length, size_t size, void (*destruct)(void* elem));

#endif /* __ARRAY_H__ */
