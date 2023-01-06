#include "stick_figure.h"

StickFigure::StickFigure() : m_spritesheet("stick_figure.bmp", 1, 2) {
	m_positon.x = 0;
	m_positon.y = 0;
	m_positon.w = 22;
	m_positon.h = 43;

	m_x = 0.0;
	m_y = 0.0;

	m_spritesheet.select_sprite(0, 0);
}

void StickFigure::update(double delta_time) {
	switch (m_direction) {
		case Direction::NONE:
			m_x += 0.0;
			m_y += 0.0;
			break;
		case Direction::UP:
			m_y = m_y - (5.0 * delta_time);
			break;
		case Direction::DOWN:
			m_y = m_y + (5.0 * delta_time);
			break;
		case Direction::LEFT:
			m_x = m_x - (5.0 * delta_time);
			break;
		case Direction::RIGHT:
			m_x = m_x + (5.0 * delta_time);
			break;
	}

	m_positon.x = m_x;
	m_positon.y = m_y;

	m_spritesheet_column++;

	if (m_spritesheet_column > 1)
		m_spritesheet_column = 0;
	m_spritesheet.select_sprite(m_spritesheet_column, 0);
}

void StickFigure::draw(SDL_Surface* window_surface) {
	m_spritesheet.draw_selected_sprite(window_surface, &m_positon);
}

void StickFigure::handle_events(const SDL_Event& event) {
	switch (event.type) {
		case SDL_KEYDOWN: {
			Uint8 const* keys = SDL_GetKeyboardState(nullptr);
			if (keys[SDL_SCANCODE_W] == 1)
				m_direction = Direction::UP;
			else if (keys[SDL_SCANCODE_S] == 1)
				m_direction = Direction::DOWN;
			else if (keys[SDL_SCANCODE_A] == 1)
				m_direction = Direction::LEFT;
			else if (keys[SDL_SCANCODE_D] == 1)
				m_direction = Direction::RIGHT;
			break;
		}
		case SDL_KEYUP:
			m_direction = Direction::NONE;
			break;
	}
}