#include <iostream>
#include <SDL.h>

int main(int argc, char ** argv) {

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window * window;

	window = SDL_CreateWindow("Project Mercury Black", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 400, SDL_WINDOW_RESIZABLE);

	SDL_Delay(5000);

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}