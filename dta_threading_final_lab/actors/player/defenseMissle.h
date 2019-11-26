#pragma once

#include <SFML/Graphics.hpp>
#include "../actor.h"

class DefenseMissle : public Actor
{
private:
	sf::RenderWindow *_window;
	const float _ttl = 2.0f;
	const float _animationTime = 1.0f;
	const float _radius = 20.0f;
	const sf::Color _colors[4] = { sf::Color::Red, sf::Color::Color(255, 0, 50, 100), sf::Color::Red, sf::Color::Color(255, 0, 50, 100) };
	float _totalTime = 0.0f;
	sf::CircleShape *_shape;

	bool _finished = false;
	void _animation();
public:
    DefenseMissle() = default;
	DefenseMissle(sf::RenderWindow*, const sf::Vector2f&);
	~DefenseMissle();

	DefenseMissle(const DefenseMissle&);
	DefenseMissle(DefenseMissle&&);

	DefenseMissle& operator=(const DefenseMissle&);
	DefenseMissle& operator=(DefenseMissle&&);

	void setPosition(const sf::Vector2f& position) { _shape->setPosition(position); }
	sf::Vector2f getPosition() { return _shape->getPosition(); }
	bool finished() override { return _finished; }

	void draw(float) override;
};