#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stddef.h>

void* createMatrix(size_t width, size_t height, size_t size, void* zero);

int resizeMatrix(void* matrix, size_t width, size_t height, size_t new_width, size_t new_height, size_t size, void* zero, void (*destruct)(void*));

void destroyMatrix(void* matrix, size_t width, size_t height, size_t size, void (*destruct)(void*));

#endif /* __MATRIX_H__ */

