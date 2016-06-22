#include <stdio.h>
#include <stdlib.h>

#include "Map.h"
#include "containers/array.h"
#include "containers/matrix.h"

static void freeTileStack(void* tile)
{
	free(((TileStack*)tile)->stack);
}

Map* createMap()
{
	Map* map = malloc(sizeof(Map));
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
	TileStack empty =
	{
		.stack = NULL,
		.altitude = 0
	};
	if (matrix_resize(&map->tiles, map->width, map->height, width, height, sizeof(TileStack), &empty, &freeTileStack))
	{
		map->width = width;
		map->height = height;
		return 1;
	}
	return 0;
}

int setMapTile(Map* map, int x, int y, int z, Tile* tile)
{
	if (isInsideMap(map, x, y) && z >= 0 && tile != NULL)
	{
		if (z >= map->tiles[x][y].altitude)
		{
			if (!setMapTileAltitude(map, x, y, z + 1))
				return 0;
		}
		map->tiles[x][y].stack[z] = *tile;
		return 1;
	}
	return 0;
}

int setMapTileAltitude(Map* map, int x, int y, int altitude)
{
	Tile empty =
	{
		.geometry = TILE_EMPTY,
		.orientation = TILE_NONE,
		.view = NULL
	};
	if (isInsideMap(map, x, y))
	{
		if (array_resize(&map->tiles[x][y].stack, map->tiles[x][y].altitude, altitude, sizeof(Tile), &empty, NULL))
		{
			map->tiles[x][y].altitude = altitude;
			return 1;
		}
	}
	return 0;
}

Tile* getMapTile(const Map* map, int x, int y, int z)
{
	if (isInsideMap(map, x, y))
	{
		if (z >= 0 && z < map->tiles[x][y].altitude)
		{
			return &map->tiles[x][y].stack[z];
		}
	}
	return NULL;
}

int isInsideMap(const Map* map, int x, int y)
{
	if (map != NULL)
	{
		return (x >= 0 && x < map->width && y >= 0 && y < map->height);
	}
	return 0;
}

void clearMap(Map* map)
{
	matrix_destroy(map->tiles, map->width, map->height, sizeof(TileStack), &freeTileStack);
}

void destroyMap(Map* map)
{
	clearMap(map);
	free(map);
}
