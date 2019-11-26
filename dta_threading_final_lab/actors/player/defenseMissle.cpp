#include "defenseMissle.h"

DefenseMissle::DefenseMissle(sf::RenderWindow *window, const sf::Vector2f &position)
{
	_window = window;
	_shape = new sf::CircleShape(this->_radius);
	_shape->setFillColor(this->_colors[0]);
    _shape->setOrigin(_shape->getRadius(), _shape->getRadius());
    _shape->setPosition(position);
}

DefenseMissle::~DefenseMissle()
{
	if (_shape != nullptr)
	{
		delete _shape;
		_shape = nullptr;
	}
}

DefenseMissle::DefenseMissle(const DefenseMissle& other)
{
	_window = other._window;
	_totalTime = other._totalTime;
    if (other._shape)
    {
        _shape = new sf::CircleShape();
        *_shape = *other._shape;
    }
    else
        _shape = nullptr;
}

DefenseMissle::DefenseMissle(DefenseMissle&& other)
{
	_window = other._window;
	other._window = nullptr;
	_totalTime = other._totalTime;
	_shape = other._shape;
	other._shape = nullptr;
}

DefenseMissle& DefenseMissle::operator=(const DefenseMissle& other)
{
	if (this == &other)
		return *this;

	_window = other._window;
	_totalTime = other._totalTime;
	*_shape = *other._shape;

	return *this;
}

DefenseMissle& DefenseMissle::operator=(DefenseMissle&& other)
{
	if (this == &other)
		return *this;

	_window = other._window;
	other._window = nullptr;
	_totalTime = other._totalTime;
	_shape = other._shape;
	other._shape = nullptr;
	return *this;
}

void DefenseMissle::_animation()
{
	const int value = _totalTime / _animationTime;
	sf::Color color = _colors[value];
	_shape->setFillColor(color);
}

void DefenseMissle::draw(float deltaTime)
{
	_totalTime += deltaTime;
	_animation();
	if (_totalTime <= _ttl)
		_window->draw(*_shape);
	else
		_finished = true;
}