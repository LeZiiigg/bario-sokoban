#ifndef __LIST_H__
#define __LIST_H__

#include <stddef.h>

#define list_get_member_offset(element, member) ((size_t)(&(element)->member) - (size_t)(element))

void list_insert_first(void* head, void* tail, void* element, size_t next, size_t prev);

void list_insert_last(void* head, void* tail, void* element, size_t next, size_t prev);

void list_insert(void* head, void* tail, void* position, void* element, size_t next, size_t prev);

void list_remove_first(void* head, void* tail, size_t next, size_t prev);

void list_remove_last(void* head, void* tail, size_t next, size_t prev);

void list_remove(void* head, void* tail, void* element, size_t next, size_t prev);

void list_clear(void* head, void* tail, size_t next, size_t prev, void (*destruct)(void*));

#endif /* __LIST_H__ */

