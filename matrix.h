#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stddef.h>

void* create_matrix(size_t width, size_t height, size_t size, void* zero);

int resize_matrix(void* matrix, size_t width, size_t height, size_t new_width, size_t new_height, size_t size, void* zero, void (*destruct)(void*));

void destroy_matrix(void* matrix, size_t width, size_t height, size_t size, void (*destruct)(void*));

#endif /* __MATRIX_H__ */

