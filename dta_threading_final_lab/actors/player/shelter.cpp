#include "shelter.h"
#include "../../renderer.h"

Shelter::Shelter(const sf::Vector2f &position)
{
    _base = new sf::RectangleShape(RECT_SIZE);
    _base->setOrigin({RECT_SIZE.x / 2.0f, RECT_SIZE.y / 2.0f});
    _base->setPosition(position);
    _base->setFillColor(sf::Color::Cyan);
    const auto windowSize = Renderer::getWindowSize();
    const sf::Vector2f healthBarSize = { 10.0f, 20.0f };

    for (unsigned int i = 0; i < _health; i++)
    {
        auto healthBar = sf::RectangleShape(healthBarSize);
        healthBar.setFillColor(sf::Color::Red);
        healthBar.setOrigin(0.0f, (healthBarSize.y / 2.0f));
        float xPos = _base->getSize().x / static_cast<float>(_health);
        healthBar.setPosition(((_base->getPosition().x - (RECT_SIZE.x / 2.0f)) + (xPos * i)) + 10.0f, _base->getPosition().y);
        _healthBars.push_back(healthBar);
    }
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
    _healthBars = other._healthBars;
}

Shelter::Shelter(Shelter&& other) noexcept
{
    _base = other._base;
    other._base = nullptr;

    _health = other._health;
    _visible = other._visible;
    _healthBars = other._healthBars;
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
    _healthBars = other._healthBars;

    return *this;
}

Shelter& Shelter::operator=(Shelter&& other) noexcept
{
    if (this == &other)
        return *this;

    _base = other._base;
    other._base = nullptr;

    _health = other._health;
    _healthBars = other._healthBars;
    _visible = other._visible;

    return *this;
}

void Shelter::draw(float deltaTime)
{
    if (_visible)
    {
        Renderer::window->draw(*_base);
        for (unsigned int i = 0; i < _health; i++)
            Renderer::window->draw(_healthBars[i]);
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