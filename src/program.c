/* A desk calculator implemented in SDL2. */

/*
	TODO
	* Handle key press events.
	* Handle mouse click events.
	* Render output to text area.
*/

#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>

const char *IMAGE_PATH = "../assets/calculator.bmp";
const int WINDOW_HEIGHT = 600, WINDOW_WIDTH = 500;

int init(SDL_Window **, SDL_Surface **);
int loadMedia(SDL_Surface *);
void close(SDL_Window *, SDL_Surface *);

int main(int argc, char **argv)
{
	int status = 0;
	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL, *dcSurface = NULL;
	bool quit = false;
	SDL_Event e;

	status = init(&window, &screenSurface);

	if (status == 0)
	{
		status = loadMedia(&dcSurface);
	}

	if (status == 0)
	{
		while (!quit)
		{
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (e.type == SDL_KEYDOWN)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_KP_0:
					case SDLK_KP_1:
					case SDLK_KP_2:
					case SDLK_KP_3:
					case SDLK_KP_4:
					case SDLK_KP_5:
					case SDLK_KP_6:
					case SDLK_KP_7:
					case SDLK_KP_8:
					case SDLK_KP_9:
					case SDLK_KP_DIVIDE:
					case SDLK_KP_MULTIPLY:
					case SDLK_KP_MINUS:
					case SDLK_KP_PLUS:
					case SDLK_KP_PERIOD:
					case SDLK_KP_ENTER:
						printf("A key was pressed.\n");
						break;
					default:
						break;
					}
				}
			}

			SDL_BlitSurface(dcSurface, NULL, screenSurface, NULL);
			SDL_UpdateWindowSurface(window);
		}
	}

	close(window, screenSurface);

	return 0;
}

int init(SDL_Window **window, SDL_Surface **screenSurface)
{
	int status = SDL_Init(SDL_INIT_VIDEO);
	
	if (status < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return status;
	}

	*window = SDL_CreateWindow(
		"SDL Desk Calculator",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (*window == NULL)
	{
		printf("SDL window could not be created! SDL Error: %s\n", SDL_GetError());
		return -1;
	}

	*screenSurface = SDL_GetWindowSurface(*window);

	return status;
}

int loadMedia(SDL_Surface **dcSurface)
{
	*dcSurface = SDL_LoadBMP(IMAGE_PATH);
	if (*dcSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", IMAGE_PATH, SDL_GetError());
		return -1;
	}

	return 0;
}

void close(SDL_Window *window, SDL_Surface *screenSurface)
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}