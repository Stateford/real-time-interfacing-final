#include "player.h"
#include "../../renderer.h"
#include "../../utils.h"
#include <shared_mutex>


Player::Player()
{
	_cursor = new Cursor({ 50, 100 });

    const auto windowSize = Renderer::window->getSize();
    const auto divisor = windowSize.x / 3.0f;
    const auto baseLine = windowSize.y / 8.0f;
    _statusBar = new StatusBar();

    for (unsigned int i = 0; i < 3; i++)
        _shelters.push(new Shelter({ ((divisor * i) + (divisor / 2.0f)), windowSize.y - baseLine}));
}

Player::~Player()
{
	delete _cursor;
	_cursor = nullptr;
    delete _statusBar;
    _statusBar = nullptr;
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
    this->_statusBar->draw();
}

void Player::shoot()
{
	_missles.push(new DefenseMissle(_cursor->getPosition()));
}

void Player::move(float deltaTime, float x, float y)
{
    this->_cursor->move(deltaTime, x, y);
}

void Player::collisionCheck(EnemyController& enemy)
{
    std::shared_mutex mutex;

    for (AttackMissle* atkMissle : enemy._missles)
    {
        if (!atkMissle->checkScreenBounds())
        {
            atkMissle->defendHit();
            continue;
        }

        for (const DefenseMissle* defMissle : _missles)
        {
            if (!atkMissle->finished() && !defMissle->finished() && defMissle->collision(*atkMissle))
            {
                std::lock_guard<std::shared_mutex> guard(mutex);
                atkMissle->defendHit();
                _statusBar->addScore(1000);
                DEBUGPRINT("MISSLE HIT\n");
            }
        }

        for (Shelter* shelter : _shelters)
        {
            if (!atkMissle->finished() && !shelter->finished() && shelter->collision(*atkMissle))
            {
                std::lock_guard<std::shared_mutex> guard(mutex);
                shelter->hit();
                atkMissle->defendHit();
                DEBUGPRINT("SHELTER HIT\n");
            }
        }
    }
}