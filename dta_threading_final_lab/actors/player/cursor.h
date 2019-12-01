#pragma once

#include "../actor.h"
#include <SFML/Graphics.hpp>

class Cursor : public Actor
{
private:
	sf::RectangleShape _horizontal;
	sf::RectangleShape _vertical;

	sf::Vector2f _position;
	sf::Vector2f _windowSize;

	float _speed = 1.5f;

	void _setPosition(const sf::Vector2f&);
public:
	Cursor(const sf::Vector2f&);

	void up(float);
	void down(float);
	void right(float);
	void left(float);

    void move(float, float, float);

	sf::Vector2f getPosition() { return _position; }

	void draw(float) override;
    sf::Shape* getShape() const override { return nullptr; };
};