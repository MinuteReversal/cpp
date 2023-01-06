#pragma once
#include <iostream>
#include <SDL.h>
#include "stick_figure.h"

class Application {
	public:
		Application();
		~Application();

		void loop();
		void update(double delta_time);
		void draw();

		SDL_Surface* load_surface(char const* path);

	private:
		StickFigure m_stick_figure;

		SDL_Window* m_window;
		SDL_Surface* m_window_surface;
		SDL_Event m_window_event;
};
