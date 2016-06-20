#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "matrix.h"
#include "Map.h"

void printMap(Map* map);

void print_int_array(int* array, int length);

void print_int_matrix(int** matrix, int width, int height);

void free_int(void* elem);

int main(int argc, char* argv[])
{
	int *array, **matrix;
	int none = -1;
	int i;

	printf("Array tests\n\n");

	array = array_create(10, sizeof(int), &none);
	print_int_array(array, 10);

	for (i = 0; i < 10; i++)
		array[i] = i;
	print_int_array(array, 10);

	array_resize(&array, 10, 6, sizeof(int), &none, &free_int);
	print_int_array(array, 6);

	array_resize(&array, 6, 10, sizeof(int), NULL, &free_int);
	print_int_array(array, 10);

	printf("\nMatrix tests\n\n");

	matrix = matrix_create(4, 4, sizeof(int), &none);
	print_int_matrix(matrix, 4, 4);

	for (i = 0; i < 16; i++)
		matrix[i%4][i/4] = i;
	print_int_matrix(matrix, 4, 4);

	matrix_resize(&matrix, 4, 4, 6, 3, sizeof(int), &none, free_int);
	print_int_matrix(matrix, 6, 3);

	matrix_resize(&matrix, 6, 3, 2, 5, sizeof(int), NULL, free_int);
	print_int_matrix(matrix, 2, 5);

	array_destroy(array, 10, sizeof(int), NULL);
	matrix_destroy(matrix, 2, 5, sizeof(int), NULL);

	printf("\nMap tests\n\n");

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

	destroyMap(m);
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

void print_int_array(int* array, int length)
{
	int i;
	printf("%p\t{", array);
	for (i = 0; i < length; i++)
	{
		printf("%d", array[i]);
		if (i < length - 1)
			printf(", ");
	}
	printf("}\n");
}

void print_int_matrix(int** matrix, int width, int height)
{
	int i, j;
	printf("%p\n", matrix);
	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
}

void free_int(void* integer)
{
	printf("free(%d)\n", *((int*)integer));
}
