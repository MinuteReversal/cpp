#include <iostream>
#include <SDL.h>

#define SDL_MAIN_HANDLED

int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Failed to initialize the SDL2 library" << std::endl;
		return -1;
	}

	SDL_Window* window = SDL_CreateWindow("Learn SDL2", SDL_WINDOWPOS_CENTERED,
										  SDL_WINDOWPOS_CENTERED, 680, 480, 0);

	if (!window) {
		std::cout << "Failed to create window" << std::endl;
		return -1;
	}

	SDL_Surface* window_surface = SDL_GetWindowSurface(window);

	if (!window_surface) {
		std::cout << "Failed to get the surface from the window" << std::endl;
		std::cout << "SDL2 Error:" << SDL_GetError() << std::endl;
		return -1;
	}

	bool keep_window_open = true;
	while (keep_window_open) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_QUIT:
					keep_window_open = false;
					break;
			}
			SDL_UpdateWindowSurface(window);
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}