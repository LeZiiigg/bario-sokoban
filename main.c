#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GamePackage.h"

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	SDL_Window* window = SDL_CreateWindow("Bario Sokoban", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 560, 420, SDL_WINDOW_SHOWN);
	SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	GamePackage* package = loadGamePackage("level.tmx");

	int quit = 0;
	while (!quit)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				quit = 1;
				break;
			}
		}
	}

	destroyGamePackage(package);


	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
	return 0;
}
