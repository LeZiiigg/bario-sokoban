#include <stdio.h>
#include <stdlib.h>

#include "GamePackage.h"
#include "containers/list.h"
#include "tmx/tmx.h"

static int loadGameEntities(GamePackage* package, tmx_map* map)
{
	return 1;
}

GamePackage* loadGamePackage(const char* filename)
{
	GamePackage* package = NULL;
	tmx_map* map = tmx_load(filename);
	if (map != NULL)
	{
		package = malloc(sizeof(GamePackage));
		if (package != NULL)
		{
			package->map = loadMapFromTMX(map);
			package->entities = NULL;
			if (!loadGameEntities(package, map))
			{
				destroyGamePackage(package);
				package = NULL;
			}
		}
		tmx_map_free(map);
	}
	else
		tmx_perror("loadGamePackage");
	return package;
}

void destroyGamePackage(GamePackage* package)
{
	size_t next, prev;
	if (package != NULL)
	{
		destroyMap(package->map);

		next = list_get_member_offset(package->entities, next);
		prev = list_get_member_offset(package->entities, prev);
		list_clear(&package->entities, NULL, next, prev, &free);
	}
}
