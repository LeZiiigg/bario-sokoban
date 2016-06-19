#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stddef.h>

void* create_array(size_t length, size_t size, void* zero);

void fill_array(void* array, size_t length, size_t size, void* value);

void copy_array(void* src_array, size_t src_length, void* dst_array, size_t size, size_t dst_length);

void clear_array(void* array, size_t length, size_t size, void (*destruct)(void*));

void get_into_array(void* src_array, size_t src_length, void* dst_array, size_t dst_length, size_t size, void* zero, void (*destruct)(void*));

int resize_array(void* array, size_t length, size_t new_length, size_t size, void* zero, void (*destruct)(void*));

void destroy_array(void* array, size_t length, size_t size, void (*destruct)(void*));

#endif /* __ARRAY_H__ */
