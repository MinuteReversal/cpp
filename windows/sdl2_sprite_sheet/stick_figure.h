#pragma once
#include "SDL.h"
#include "spritesheet.h"

enum class Direction { NONE, UP, DOWN, LEFT, RIGHT };

class StickFigure {
	public:
		StickFigure();
		~StickFigure() = default;

		void update(double delta_time);
		void draw(SDL_Surface* window_surface);
		void handle_events(SDL_Event const& event);

	private:
		SpriteSheet m_spritesheet;
		int m_spritesheet_column = 0;
		int const SPRITESHEET_UP = 0;
		int const SPRITESHEET_LEFT = 1;
		int const SPRITESHEET_RIGHT = 2;
		int const SPRITESHEET_DOWN = 3;
		SDL_Rect m_positon;
		double m_x;
		double m_y;
		Direction m_direction;
};