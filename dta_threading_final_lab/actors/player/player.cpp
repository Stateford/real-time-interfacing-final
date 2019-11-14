#include "player.h"

Player::Player(sf::RenderWindow *window)
{
	_window = window;
	_cursor = new Cursor({ 50, 100 });
}

Player::~Player()
{
	delete _cursor;
	_cursor = nullptr;
	_window = nullptr;
}

void Player::up(float deltaTime)
{
	if (_cursor->getPosition().y > 0.0f)
		this->_cursor->up(deltaTime);
}

void Player::down(float deltaTime)
{
	if (_cursor->getPosition().y < _window->getSize().y)
		this->_cursor->down(deltaTime);
}

void Player::left(float deltaTime)
{
	if (_cursor->getPosition().x > 0.0f)
		this->_cursor->left(deltaTime);
}

void Player::right(float deltaTime)
{
	if (_cursor->getPosition().x < _window->getSize().x)
		this->_cursor->right(deltaTime);
}

void Player::draw(float deltaTime)
{
	this->_cursor->draw(this->_window);
	for (auto &p : _missles)
		p.draw(deltaTime);
}

void Player::shoot()
{
	_missles.emplace_back(DefenseMissle(_window));
}