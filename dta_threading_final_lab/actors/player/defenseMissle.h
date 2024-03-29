#pragma once

#include <SFML/Graphics.hpp>
#include "../actor.h"

class DefenseMissle : public Actor
{
private:
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
	DefenseMissle(const sf::Vector2f&);
	~DefenseMissle();

	DefenseMissle(const DefenseMissle&);
	DefenseMissle(DefenseMissle&&) noexcept;

	DefenseMissle& operator=(const DefenseMissle&);
	DefenseMissle& operator=(DefenseMissle&&) noexcept;

	void setPosition(const sf::Vector2f& position) { _shape->setPosition(position); }
	sf::Vector2f getPosition() { return _shape->getPosition(); }
	bool finished() const override { return _finished; }

    // Virtual overrides
	void draw(float) override;
    bool collision(const Actor& actor) const override;
    sf::Shape* getShape() const override { return _shape; };
};