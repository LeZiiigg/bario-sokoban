#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "GamePackage.h"

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Bario Sokoban", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 560, 420, SDL_WINDOW_SHOWN);

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

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
