#include <stdio.h>
#include <stdlib.h>

#include "GamePackage.h"
#include "containers/list.h"
#include "tmx/tmx.h"

static int loadGameMap(GamePackage* package, tmx_map* map)
{
	int x, y, z;
	tmx_layer* layer;

	package->map = createMap();
	if (setMapSize(package->map, map->width, map->height))
	{
		for (layer = map->ly_head, z = 0; layer != NULL && layer->type == L_LAYER; layer = layer->next, z++)
		{
			for (x = 0; x < map->width; x++)
			{
				for (y = 0; y < map->height; y++)
				{
					const unsigned int gid = layer->content.gids[x + y * map->width];
					const tmx_tile* tile = tmx_get_tile(map, gid);
					if (tile != NULL)
					{
						/* TODO: setMapTile(map, x, y, z, ...) */
					}
				}
			}
		}
		return 1;
	}
	return 0;
}

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
			package->map = NULL;
			package->entities = NULL;
			if (!loadGameMap(package, map) || !loadGameEntities(package, map))
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
