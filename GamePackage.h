#ifndef __GAMEPACKAGE_H__
#define __GAMEPACKAGE_H__

#include "Entity.h"
#include "Map.h"

typedef struct
{
	/* Model properties */
	Entity* entities;
	Map* map;

	Entity* player;

	/* View properties */

	/* Controller properties */
} GamePackage;

GamePackage* loadGamePackage(const char* filename);

void destroyGamePackage(GamePackage* package);

#endif /* __GAMEPACKAGE_H__ */
