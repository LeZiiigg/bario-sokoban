#ifndef __WORLD_H__
#define __WORLD_H__

#include "Entity.h"
#include "Map.h"

typedef struct
{
	/* Model properties */
	Entity* entities;
	Map* map;

	/* View properties */
	void* view;
} World;

#endif /* __WORLD_H__ */
