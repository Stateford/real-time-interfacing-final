#pragma once

#include "../actor.h"
#include <SFML/Graphics.hpp>


class Shelter : public Actor
{
private:
    const sf::Vector2f RECT_SIZE = {75, 40};
    sf::RectangleShape *_base;
    std::vector<sf::RectangleShape> _healthBars;
    
    unsigned int _health = 3;

    bool _visible = true;

public:
    Shelter(const sf::Vector2f&);
    ~Shelter();

    Shelter(const Shelter&);
    Shelter(Shelter&&) noexcept;

    Shelter& operator=(const Shelter&);
    Shelter& operator=(Shelter&&) noexcept;

    void hit();
    unsigned int getHealth() const { return _health; }

    // Actor Overrides
    void draw(float) override;
    sf::Shape* getShape() const override { return _base; };
    bool collision(const Actor& actor) const override;
};