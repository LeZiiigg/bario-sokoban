#ifndef __MAP_H__
#define __MAP_H__

typedef enum {TILE_EMPTY, TILE_FLOOR, TILE_WALL, TILE_SLOPE} TileGeometry;
typedef enum {TILE_NONE, TILE_NORTH, TILE_SOUTH, TILE_EAST, TILE_WEST} TileOrientation;

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

int setMapTile(Map* map, int x, int y, int z, const Tile* tile);

int setMapTileAltitude(Map* map, int x, int y, int size);

const Tile* getMapTile(const Map* map, int x, int y, int z);

int isInsideMap(const Map* map, int x, int y);

void clearMap(Map* map);

void destroyMap(Map* map);

#endif /* __MAP_H__ */
