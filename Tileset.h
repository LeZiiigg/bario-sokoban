#ifndef __TILESET_H__
#define __TILESET_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct
{
    SDL_Texture* image;
    SDL_Rect* tiles;
} Tileset;

#endif /* __TILESET_H__ */
