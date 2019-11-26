#include "attackMissle.h"

AttackMissle::AttackMissle(sf::RenderWindow *window, sf::Vector2f startPoint)
    : _endpoint(_endpointRadius)
{
    _window = window;
    _startPoint = startPoint;
    _missleLine[0].position = startPoint;
    _missleLine[0].color = sf::Color::Red;

    _missleLine[1].position = startPoint;
    _missleLine[1].color = sf::Color::Red;

    _endpoint.setFillColor(sf::Color::Yellow);
    _endpoint.setOrigin(_endpoint.getRadius(), _endpoint.getRadius());
    _endpoint.setPosition(startPoint);
}

AttackMissle::~AttackMissle()
{

}

void AttackMissle::draw(float deltaTime)
{
    _totalTime += deltaTime;
    _missleLine[1].position.y += _speed * deltaTime;
    _endpoint.setPosition({ _missleLine[1].position.x, _missleLine[1].position.y });
    _window->draw(_missleLine, _missleLineSize, sf::LineStrip);
    _window->draw(_endpoint);
}