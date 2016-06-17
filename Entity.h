#ifndef __ENTITY_H__
#define __ENTITY_H__

typedef struct
{
	/* Model properties */
	float x;
	float y;
	float z;

	/* View properties */
	void* view;
} Entity;

#endif /* __ENTITY_H__ */
