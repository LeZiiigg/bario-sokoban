#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

/*	To compile it with gcc use:
*		gcc main.c -o bario-sokoban -lSDL2
*/ 

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Bario Sokoban", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 560, 420, SDL_WINDOW_SHOWN);
	
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

	SDL_Quit();
	return 0;
}
