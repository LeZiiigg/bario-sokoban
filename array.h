#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stddef.h>

void* createArray(size_t length, size_t size, void* zero);

void fillArray(void* array, size_t length, size_t size, void* value);

void copyArray(void* src_array, size_t src_length, void* dst_array, size_t size, size_t dst_length);

void clearArray(void* array, size_t length, size_t size, void (*destruct)(void*));

void getIntoArray(void* src_array, size_t src_length, void* dst_array, size_t dst_length, size_t size, void* zero, void (*destruct)(void*));

int resizeArray(void* array, size_t length, size_t new_length, size_t size, void* zero, void (*destruct)(void*));

void destroyArray(void* array, size_t length, size_t size, void (*destruct)(void*));

#endif /* __ARRAY_H__ */
