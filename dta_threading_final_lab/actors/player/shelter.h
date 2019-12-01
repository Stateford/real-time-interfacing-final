#pragma once

#include "../actor.h"
#include <SFML/Graphics.hpp>


class Shelter : public Actor
{
private:
    const sf::Vector2f RECT_SIZE = {50, 25};
    sf::RectangleShape _base;

    unsigned int _health = 3;

    bool _visible = true;

public:
    Shelter(const sf::Vector2f&);
    ~Shelter();

    void hit();

    // Actor Overrides
    void draw(float) override;
    //bool collision(const Actor& actor) const override;
};