#pragma once

#include <SFML/Graphics.hpp>

class Cursor
{
private:
	sf::RectangleShape _horizontal;
	sf::RectangleShape _vertical;

	sf::Vector2f _position;

	float _speed = 2.0f;

	void _setPosition(const sf::Vector2f&);
public:
	Cursor(const sf::Vector2f&);

	void up(float);
	void down(float);
	void right(float);
	void left(float);

	void draw(sf::RenderWindow*);
};