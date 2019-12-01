#pragma once

#include <SFML/Graphics.hpp>

class Actor
{
protected:
    bool _finished = false;
public:
    virtual bool finished() const { return _finished; }
    virtual void draw() {};
    virtual void draw(float) {};
    virtual bool collision(const Actor& actor) const { return false; };
    virtual sf::Shape* getShape() const = 0;
};