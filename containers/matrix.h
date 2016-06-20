#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stddef.h>

void* matrix_create(size_t width, size_t height, size_t size, void* zero);

int matrix_resize(void* matrix, size_t width, size_t height, size_t new_width, size_t new_height, size_t size, void* zero, void (*destruct)(void*));

void matrix_destroy(void* matrix, size_t width, size_t height, size_t size, void (*destruct)(void*));

#endif /* __MATRIX_H__ */

