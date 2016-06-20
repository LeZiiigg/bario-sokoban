#include <stdio.h>
#include <stdlib.h>

#include "list.h"

#define getm(element, member, type) (*(type*)((char*)(element) + (member)))

void list_insert_first(void* head, void* tail, void* element, size_t next, size_t prev)
{
	if (head != NULL && element != NULL)
	{
		getm(element, prev, void*) = NULL;
		getm(element, next, void*) = *(void**)head;
		if (*(void**)head != NULL)
			getm(*(void**)head, prev, void*) = element;
		else if(tail != NULL)
			*(void**)tail = element;
		*(void**)head = element;
	}
}

void list_insert_last(void* head, void* tail, void* element, size_t next, size_t prev)
{
	list_insert_first(tail, head, element, prev, next);
}

void list_insert(void* head, void* tail, void* position, void* element, size_t next, size_t prev)
{
	if (head != NULL && position == *(void**)head)
		list_insert_first(head, tail, element, next, prev);
	else if (tail != NULL && position == NULL)
		list_insert_last(head, tail, element, next, prev);
	else if (element != NULL)
	{
		getm(element, prev, void*) = getm(position, prev, void*);
		getm(element, next, void*) = position;
		getm(getm(position, prev, void*), next, void*) = element;
		getm(position, prev, void*) = element;
	}
}

void list_remove_first(void* head, void* tail, size_t next, size_t prev)
{
	if (head != NULL && *(void**)head != NULL)
	{
		if (getm(*(void**)head, next, void*) != NULL)
			getm(getm(*(void**)head, next, void*), prev, void*) = NULL;
		else if(tail != NULL)
			*(void**)tail = NULL;
		*(void**)head = getm(*(void**)head, next, void*);
	}
}

void list_remove_last(void* head, void* tail, size_t next, size_t prev)
{
	list_remove_first(tail, head, prev, next);
}

void list_remove(void* head, void* tail, void* element, size_t next, size_t prev)
{
	if (head != NULL && element == *(void**)head)
		list_remove_first(head, tail, next, prev);
	else if (tail != NULL && element == *(void**)tail)
		list_remove_last(head, tail, next, prev);
	else if (element != NULL)
	{
		getm(getm(element, prev, void*), next, void*) = getm(element, next, void*);
		getm(getm(element, next, void*), prev, void*) = getm(element, prev, void*);
	}
}

void list_clear(void* head, void* tail, size_t next, size_t prev, void (*destruct)(void*))
{
	void* temp;
	if (head != NULL)
		while (*(void**)head)
		{
			temp = *(void**)head;
			list_remove_first(head, tail, next, prev);
			if (destruct != NULL)
				(*destruct)(temp);
		}
	else
		list_clear(tail, head, prev, next, destruct);
}
