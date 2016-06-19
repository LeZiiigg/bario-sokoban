#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "Map.h"

void printMap(Map* map);

void printIntArray(int* array, int length)
{
	int i;
	printf("{");
	for (i = 0; i < length; i++)
	{
		printf("%d%s", array[i], (i < length - 1) ? ", " : "}\n");
	}
}

void freeInt(void* elem)
{
	printf("free(%d)\n", *((int*)elem));
}

int main(int argc, char* argv[])
{
	int none = -1;
	int* array = createArray(10, sizeof(int), &none);

	printIntArray(array, 10);

	int i;
	for (i = 0; i < 10; i++)
		array[i] = i;

	printIntArray(array, 10);

	resizeArray(&array, 10, 6, sizeof(int), &none, &freeInt);

	printIntArray(array, 6);

	resizeArray(&array, 6, 10, sizeof(int), NULL, &freeInt);

	printIntArray(array, 10);

	/*
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
	printMap(m);*/
	return 0;
}

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
