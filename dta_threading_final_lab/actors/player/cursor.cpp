#include "cursor.h"

Cursor::Cursor(const sf::Vector2f &position) :
	_horizontal(sf::Vector2f(30.0f, 10.0f)),
	_vertical(sf::Vector2f(10.0f, 30.0f)),
	_position(position)
{
	_horizontal.setOrigin(sf::Vector2f{ _horizontal.getSize().x / 2.0f, _horizontal.getSize().y / 2.0f });
	_vertical.setOrigin(sf::Vector2f{ _vertical.getSize().x / 2.0f, _vertical.getSize().y / 2.0f });

	this->_setPosition(position);
}

void Cursor::up(float deltaTime)
{
	_position.y -= _speed * deltaTime;
	this->_setPosition(_position);
}

void Cursor::down(float deltaTime)
{
	_position.y += _speed * deltaTime;
	this->_setPosition(_position);
}

void Cursor::left(float deltaTime)
{
	_position.x -= _speed * deltaTime;
	this->_setPosition(_position);
}

void Cursor::right(float deltaTime)
{
	_position.x += _speed * deltaTime;
	this->_setPosition(_position);
}

void Cursor::_setPosition(const sf::Vector2f &position)
{
	_position = position;
	_horizontal.setPosition(_position);
	_vertical.setPosition(_position);
}

void Cursor::draw(sf::RenderWindow *window)
{
	window->draw(this->_horizontal);
	window->draw(this->_vertical);
}