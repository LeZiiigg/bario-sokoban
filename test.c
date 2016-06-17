#include <stdio.h>
#include <stdlib.h>

#include "Map.h"

void printMap(Map* map)
{
	int x, y, z;
	for (y = 0; y < map->height; y++)
	{
		for (x = 0; x < map->width; x++)
		{
			char c = '?';
			for (z = 0; z < map->tiles[x][y].altitude; z++)
			{
				Tile* t = getMapTile(map, x, y, z);
				switch (t->geometry)
				{
				case TILE_FLOOR:
					c = '.';
					break;
				case TILE_WALL:
					c = '#';
					break;
				case TILE_SLOPE:
					c = '/';
					break;
				default:
					break;
				}
			}
			printf("%c", c);
		}
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char* argv[])
{
	Map* m = createMap();
	Tile f = {TILE_FLOOR, TILE_NONE}, w = {TILE_WALL, TILE_NONE};
	int x, y;

	setMapSize(m, 4, 4);
	for (x = 0; x < m->width; x++)
	{
		for (y = 0; y < m->height; y++)
		{
			setMapTile(m, x, y, 0, &f);
		}
	}
	setMapTile(m, 2, 2, 0, &w);
	setMapTile(m, 2, 3, 1, &w);
	printMap(m);

	setMapSize(m, 5, 3);
	printMap(m);
	return 0;
}
