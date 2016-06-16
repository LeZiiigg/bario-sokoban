#ifndef __MAP_H__
#define __MAP_H__

typedef enum{ FLOOR, WALL, SLOPE } TileGeometry;
typedef enum{ NORTH, SOUTH, EAST, WEST } TileOrientation;

typedef struct
{
	/* Model properties */
	TileGeometry geometry;
	TileOrientation orientation;

	/* View properties */
	void* view;
} Tile;

typedef struct
{
	/* Model properties */
	Tile* stack;
	int altitude;
} TileStack;

typedef struct
{
	/* Model properties */
	TileStack** tiles;
	int width;
	int height;

	/* View properties */
	void* view;
} Map;

Map* createMap();

int setMapSize(Map* map, int width, int height);

int setMapTile(Map* map, int x, int y, int z, Tile tile);

Tile* getMapTile(Map* map, int x, int y, int z);

void destroyMap(Map* map);

#endif /* __MAP_H__ */
