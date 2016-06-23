#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stddef.h>

void* array_create(size_t length, size_t size, const void* zero);

void array_fill(void* array, size_t length, size_t size, const void* value);

void array_copy(void* src_array, size_t src_length, void* dst_array, size_t size, size_t dst_length);

void array_clear(void* array, size_t length, size_t size, void (*destruct)(void*));

void array_get_into(void* src_array, size_t src_length, void* dst_array, size_t dst_length, size_t size, const void* zero, void (*destruct)(void*));

int array_resize(void* array, size_t length, size_t new_length, size_t size, const void* zero, void (*destruct)(void*));

void array_destroy(void* array, size_t length, size_t size, void (*destruct)(void*));

#endif /* __ARRAY_H__ */
