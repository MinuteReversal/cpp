#pragma once
#include <iostream>
#include <SDL.h>

class Application {
	public:
		Application();
		~Application();

		void loop();
		void update(double delta_time);
		void draw();

		SDL_Surface* load_surface(char const* path);

	private:
		SDL_Surface* m_image;
		SDL_Rect m_image_position;
		double m_image_x = 0.0;
		double m_image_y = 0.0;

		SDL_Window* m_window;
		SDL_Surface* m_window_surface;
		SDL_Event m_window_event;
};
