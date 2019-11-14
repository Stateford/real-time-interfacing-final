#pragma once

#include <SFML/Graphics.hpp>

class DefenseMissle
{
private:
	sf::RenderWindow *_window;
	const float _ttl = 1.0f;
	const float _animationTime = 0.2f;
	const float _radius = 5.0f;
	const sf::Color _colors[4] = { sf::Color::Red, sf::Color::Transparent, sf::Color::Color(255, 0, 50, 0), sf::Color::Transparent };
	float _totalTime = 0.0f;
	sf::CircleShape *_shape;

	bool _finished = false;
	void _animation();
public:
	DefenseMissle(sf::RenderWindow*);
	~DefenseMissle();

	DefenseMissle(const DefenseMissle&);
	DefenseMissle(DefenseMissle&&);

	DefenseMissle& operator=(const DefenseMissle&);
	DefenseMissle& operator=(DefenseMissle&&);

	void setPosition(const sf::Vector2f& position) { _shape->setPosition(position); }
	sf::Vector2f getPosition() { return _shape->getPosition(); }
	bool finished() { return _finished; }

	void draw(float);
};