#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Map.h"
#include "containers/array.h"
#include "containers/matrix.h"

static const Tile empty =
{
	.geometry = TILE_EMPTY,
	.orientation = TILE_NONE,
	.view = NULL
};

static const Tile floor =
{
	.geometry = TILE_FLOOR,
	.orientation = TILE_NONE,
	.view = NULL
};

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

int setMapTile(Map* map, int x, int y, int z, const Tile* tile)
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

const Tile* getMapTile(const Map* map, int x, int y, int z)
{
	if (isInsideMap(map, x, y))
	{
		if (z >= 0 && z < map->tiles[x][y].altitude)
		{
			return &map->tiles[x][y].stack[z];
		}
	}
	return &empty;
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

static int loadTMXTile(Map* map, int x, int y, int z, tmx_tile* tmx)
{
	Tile tile = empty;
	if (tmx != NULL)
	{
		tmx_property* property;
		for (property = tmx->properties; property != NULL; property = property->next)
		{
			if (strcmp(property->name, "geometry") == 0)
			{
				if (strcmp(property->value, "floor") == 0)
					tile.geometry = TILE_FLOOR;
				else if (strcmp(property->value, "cube") == 0)
					tile.geometry = TILE_WALL;
				else if (strcmp(property->value, "slope") == 0)
					tile.geometry = TILE_SLOPE;
			}
			else if (strcmp(property->name, "orientation") == 0)
			{
				if (strcmp(property->value, "north") == 0)
					tile.orientation = TILE_NORTH;
				else if (strcmp(property->value, "south") == 0)
					tile.orientation = TILE_SOUTH;
				else if (strcmp(property->value, "east") == 0)
					tile.orientation = TILE_EAST;
				else if (strcmp(property->value, "west") == 0)
					tile.orientation = TILE_WEST;
			}
		}
	}
	if (tile.geometry == TILE_WALL)
		setMapTile(map, x, y, z + 1, &floor);
	return setMapTile(map, x, y, z, &tile);
}

static int loadTMXLayer(Map* map, int z, tmx_map* tmx, tmx_layer* layer)
{
	int x, y;
	for (x = 0; x < map->width; x++)
	{
		for (y = 0; y < map->height; y++)
		{
			tmx_tile* tile = tmx_get_tile(tmx, layer->content.gids[x + y * tmx->width]);
			if (tile != NULL)
			{
				if (!loadTMXTile(map, x, y, z, tile))
					return 0;
			}
		}
	}
	return 1;
}

Map* loadMapFromTMX(tmx_map* tmx)
{
	Map* map = createMap();
	if (setMapSize(map, tmx->width, tmx->height))
	{
		tmx_layer* layer;
		int z = 0;
		for (layer = tmx->ly_head; map != NULL && layer != NULL && layer->type == L_LAYER; layer = layer->next)
		{
			if (!loadTMXLayer(map, z, tmx, layer))
			{
				destroyMap(map);
				map = NULL;
			}
			z++;
		}
	}
	return map;
}
