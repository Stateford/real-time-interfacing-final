#include "attackMissle.h"
#include "../../renderer.h"

AttackMissle::AttackMissle(const sf::Vector2f &startPoint)
{
    _endpoint = new sf::CircleShape(_endpointRadius);
    _startPoint = startPoint;
    _missleLine[0].position = startPoint;
    _missleLine[0].color = sf::Color::Red;

    _missleLine[1].position = startPoint;
    _missleLine[1].color = sf::Color::Red;

    const sf::Vector2f endPosition = { 0.0f, 0.0f };
    
    _endpoint->setFillColor(sf::Color::Yellow);
    _endpoint->setOrigin(_endpoint->getRadius(), _endpoint->getRadius());
    _endpoint->setPosition(startPoint);
}

AttackMissle::~AttackMissle()
{
    if (_endpoint)
    {
        delete _endpoint;
        _endpoint = nullptr;
    }
}

AttackMissle::AttackMissle(const AttackMissle& other)
{
    if (other._endpoint)
    {
        _endpoint = new sf::CircleShape();
        *_endpoint = *other._endpoint;
    }
    else
        _endpoint = nullptr;

    _totalTime = other._totalTime;
}

AttackMissle::AttackMissle(AttackMissle&& other) noexcept
{
    _endpoint = other._endpoint;
    other._endpoint = nullptr;

    _totalTime = other._totalTime;
}

AttackMissle& AttackMissle::operator=(const AttackMissle& other)
{
    if (this == &other)
        return *this;

    if (other._endpoint)
    {
        _endpoint = new sf::CircleShape();
        *_endpoint = *other._endpoint;
    }
    else
        _endpoint = nullptr;

    _totalTime = other._totalTime;

    return *this;
}

AttackMissle& AttackMissle::operator=(AttackMissle&& other) noexcept
{
    if (this == &other)
        return *this;

    _endpoint = other._endpoint;
    other._endpoint = nullptr;

    _totalTime = other._totalTime;

    return *this;
}

bool AttackMissle::checkScreenBounds() const
{
    sf::Vector2u windowSize = Renderer::getWindowSize();

    return ((_endpoint->getPosition().x < windowSize.x) && (_endpoint->getPosition().y < windowSize.y));
}

void AttackMissle::draw(float deltaTime)
{
    _totalTime += deltaTime;
    _missleLine[1].position.y += _speed * deltaTime;
    _endpoint->setPosition({ _missleLine[1].position.x, _missleLine[1].position.y });
    Renderer::window->draw(_missleLine, _missleLineSize, sf::LineStrip);
    Renderer::window->draw(*_endpoint);
}