#include "SDL_surface.h"
#include "SDL_video.h"
#include <iostream>
#define SDL_MAIN_HANDLED
#ifdef _WIN32
#include <SDL.h> /* Windows-specific SDL2 library */
#else
#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#endif

/**https://dev.to/noah11012/using-sdl2-opening-a-window-79c*/
int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "Failed to initialize the SDL2 library\n";
		return -1;
	}
	SDL_Window* window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED,
										  SDL_WINDOWPOS_CENTERED, 680, 480, 0);

	if (!window) {
		std::cout << "Failed to create window\n";
		return -1;
	}

	SDL_Surface* window_surface = SDL_GetWindowSurface(window);

	if (!window_surface) {
		std::cout << "Failed to get the surface from the window\n";
		std::cout << "SDL2 Error:" << SDL_GetError() << "\n";
		return -1;
	}

	SDL_Surface* image = SDL_LoadBMP("image.bmp");

	if (!image) {
		std::cout << "Failed to load image\n";
		std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
		return -1;
	}

	bool keep_window_open = true;
	while (keep_window_open) {
		SDL_Event e;
		while (SDL_PollEvent(&e) > 0) {
			switch (e.type) {
				case SDL_QUIT:
					keep_window_open = false;
					break;
			}
			SDL_BlitSurface(image, NULL, window_surface, NULL);
			SDL_UpdateWindowSurface(window);
		}
	}

	return 0;
}