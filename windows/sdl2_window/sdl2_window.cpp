#include <stdio.h>
#define SDL_MAIN_HANDLED
#ifdef _WIN32
#include <SDL.h> /* Windows-specific SDL2 library */
#else
#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#endif

int main(int argc, char *argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
		return 1;
	}
	auto window = SDL_CreateWindow("Learn SDL2", SDL_WINDOWPOS_UNDEFINED,
								   SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
	SDL_Delay(3000);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}