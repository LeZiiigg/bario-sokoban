#include <stdio.h>
#include <stdlib.h>

#include "Map.h"

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
    int x, y;
    if (map != NULL)
    {
        Map old = *map;
        map->tiles = malloc(width * sizeof(TileStack*));
        map->width = width;
        map->height = height;

        if (map->tiles == NULL)
            goto tiles_bad_alloc;

        for (x = 0; x < width; x++)
        {
            map->tiles[x] = malloc(height * sizeof(TileStack));
            if (map->tiles[x] == NULL)
                goto tiles_x_bad_alloc;

            for (y = 0; y < height; y++)
            {
                if (x < old.width && y < old.height)
                {
                    map->tiles[x][y] = old.tiles[x][y];
                    old.tiles[x][y].stack = NULL;
                }
                else
                {
                    map->tiles[x][y].stack = NULL;
                    map->tiles[x][y].altitude = 0;
                }
            }
        }
        clearMap(&old);
        return 1;

tiles_x_bad_alloc:
        for (x--; x >= 0; x--)
        {
            free(map->tiles[x]);
        }
        free(map->tiles);

tiles_bad_alloc:
        *map = old;
    }
    return 0;
}

int setMapTile(Map* map, int x, int y, int z, Tile* tile)
{
    if (isInsideMap(map, x, y) && z >= 0)
    {
        if (z >= map->tiles[x][y].altitude)
        {
            setMapTileStackSize(map, x, y, z + 1);
        }
        map->tiles[x][y].stack[z] = *tile;
        return 1;
    }
    return 0;
}

int setMapTileStackSize(Map* map, int x, int y, int size)
{
    int z;
	if (map != NULL)
    {
        TileStack old = map->tiles[x][y];
        map->tiles[x][y].stack = malloc(size * sizeof(Tile));
        map->tiles[x][y].altitude = size;

        if (map->tiles[x][y].stack == NULL)
            goto stack_bad_alloc;

        for (z = 0; z < size; z++)
        {
            if (z < old.altitude)
            {
                map->tiles[x][y].stack[z] = old.stack[z];
            }
            else
            {
                map->tiles[x][y].stack[z].geometry = EMPTY;
                map->tiles[x][y].stack[z].orientation = NONE;
                map->tiles[x][y].stack[z].view = NULL;
            }
        }
        free(old.stack);
        return 1;

stack_bad_alloc:
        map->tiles[x][y] = old;
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

void destroyMap(Map* map)
{
    clearMap(map);
    free(map);
}
