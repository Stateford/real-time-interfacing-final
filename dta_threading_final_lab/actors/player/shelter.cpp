#include "shelter.h"
#include "../../renderer.h"

Shelter::Shelter(const sf::Vector2f &position)
{
    _base = new sf::RectangleShape(RECT_SIZE);
    _base->setOrigin({RECT_SIZE.x / 2.0f, RECT_SIZE.y / 2.0f});
    _base->setPosition(position);
    _base->setFillColor(sf::Color::Cyan);
}

Shelter::~Shelter()
{
    if (_base)
    {
        delete _base;
        _base = nullptr;
    }
}

Shelter::Shelter(const Shelter& other)
{
    if (other._base)
    {
        _base = new sf::RectangleShape();
        *_base = *other._base;
    }
    else
        _base = nullptr;

    _health = other._health;
    _visible = other._visible;
}

Shelter::Shelter(Shelter&& other) noexcept
{
    _base = other._base;
    other._base = nullptr;

    _health = other._health;
    _visible = other._visible;
}

Shelter& Shelter::operator=(const Shelter& other)
{
    if (this == &other)
        return *this;

    if (other._base)
    {
        _base = new sf::RectangleShape();
        *_base = *other._base;
    }
    else
        _base = nullptr;

    _health = other._health;
    _visible = other._visible;

    return *this;
}

Shelter& Shelter::operator=(Shelter&& other) noexcept
{
    if (this == &other)
        return *this;

    _base = other._base;
    other._base = nullptr;

    _health = other._health;
    _visible = other._visible;

    return *this;
}

void Shelter::draw(float deltaTime)
{
    if (_visible)
    {
        Renderer::window->draw(*_base);
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

bool Shelter::collision(const Actor& actor) const
{
    auto shape = static_cast<sf::CircleShape*>(actor.getShape());

    return _base->getGlobalBounds().intersects(shape->getGlobalBounds());
}