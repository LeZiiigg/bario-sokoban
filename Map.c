#include <stdio.h>
#include <stdlib.h>

#include "Map.h"

Map* createMap()
{
	Map* map;

	map = malloc(sizeof(Map));
	if (map != NULL)
	{
		map->tiles = NULL;
		map->width = 0;
		map->height = 0;
		map->view = NULL;
	}
	return map;
}

int setMapSize(Map* map, int width, int height)
{
	if (map != NULL)
	{

	}
	return 0;
}

int setMapTile(Map* map, int x, int y, int z, Tile tile)
{
	if (map != NULL)
	{

	}
	return 0;
}

Tile* getMapTile(Map* map, int x, int y, int z)
{
	if (isInsideMap(map, x, y))
	{
		if (z >= 0 && z < map->tiles[x][y].altitude)
		{
			return map->tiles[x][y].stack[z];
		}
	}
	return NULL;
}

int isInsideMap(Map* map, int x, int y)
{
	if (map != NULL)
	{
		return (x >= 0 && x < map->width && y >= 0 && y < map->height);
	}
	return 0;
}

void destroyMap(Map* map)
{
	int x, y;

	if (map != NULL)
	{
		for (x = 0; x < map->width; x++)
		{
			for (y = 0; y < map->height; y++)
			{
				free(map->tiles[x][y].stack);
			}
			free(map->tiles[x]);
		}
		free(map->tiles);
	}
}
