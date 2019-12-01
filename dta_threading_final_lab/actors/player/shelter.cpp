#include "shelter.h"
#include "../../renderer.h"

Shelter::Shelter(const sf::Vector2f &position)
    : _base(RECT_SIZE)
{
    _base.setPosition(position);
    _base.setFillColor(sf::Color::Cyan);
}

Shelter::~Shelter()
{

}

void Shelter::draw(float deltaTime)
{
    if (_visible)
    {
        Renderer::window->draw(_base);
    }
}

void Shelter::hit()
{
    _health--;
    if (_health <= 0)
    {
        _visible = false;
        _finished = true;
    }
}