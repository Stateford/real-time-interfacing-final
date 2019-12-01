#include "player.h"
#include "../../renderer.h"


Player::Player()
{
	_cursor = new Cursor({ 50, 100 });

    const auto windowSize = Renderer::window->getSize();
    const auto divisor = windowSize.x / 3.0f;
    const auto baseLine = windowSize.y / 8.0f;


    for (unsigned int i = 0; i < 3; i++)
        _shelters.push(new Shelter({ ((divisor * i) + (divisor / 2.0f) - 1.0f), windowSize.y - baseLine}));
}

Player::~Player()
{
	delete _cursor;
	_cursor = nullptr;
}

void Player::up(float deltaTime)
{
	if (_cursor->getPosition().y > 0.0f)
		this->_cursor->up(deltaTime);
}

void Player::down(float deltaTime)
{
	if (_cursor->getPosition().y < Renderer::window->getSize().y)
		this->_cursor->down(deltaTime);
}

void Player::left(float deltaTime)
{
	if (_cursor->getPosition().x > 0.0f)
		this->_cursor->left(deltaTime);
}

void Player::right(float deltaTime)
{
	if (_cursor->getPosition().x < Renderer::window->getSize().x)
		this->_cursor->right(deltaTime);
}

void Player::draw(float deltaTime)
{
    _missles.draw(deltaTime);
    _shelters.draw(deltaTime);
	this->_cursor->draw(deltaTime);
}

void Player::shoot()
{
	_missles.push(new DefenseMissle(_cursor->getPosition()));
}