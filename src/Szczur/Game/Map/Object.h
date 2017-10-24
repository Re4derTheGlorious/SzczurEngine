#pragma once

#include <cstdio>
#include <ctime>
#include <cmath>

#include <SFML/Graphics.hpp>

#include <Szczur/Core/Canvas.h>

namespace rat {
	class Object {
	private:

		Canvas& _canvas;
		sf::Vector2f _pos;
		sf::Color _color;

	public:

		Object(Canvas& canvas) :
			_canvas(canvas) {
			_pos.x = rand() % static_cast<int>(_canvas.getLayersSize().x);
			_pos.y = rand() % static_cast<int>(_canvas.getLayersSize().y);
			float r = std::abs(std::sin(_pos.x / 300.0f)) * 255.0f;
			float g = std::abs(std::sin(_pos.y / 300.0f)) * 255.0f;
			float b = std::abs(std::sin((_pos.x + _pos.y) / 300.0f)) * 255.f;
			_color = sf::Color(r, g, b);
		}

		void update(float deltaTime) {
			(void)deltaTime;
		}

		void render() {
			sf::CircleShape shape(30.f);
			shape.setFillColor(_color);
			shape.setOrigin({ 30.0f, 30.0f });
			shape.setPosition(_pos);

			_canvas.render(shape, rat::fnv1a_32("GAME"));
		}
	};
}
