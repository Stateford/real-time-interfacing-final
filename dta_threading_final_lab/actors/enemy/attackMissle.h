#pragma once

#include "../../templates/container.h"
#include "../actor.h"
#include <SFML/Graphics.hpp>


class AttackMissle : public Actor
{
private:
    const float _animationTime = 0.0f;
    const float _endpointRadius = 2.0f;
    float _totalTime = 0.0f;
    float _speed = 50.0f;

    const unsigned int _missleLineSize = 2;
    sf::Vertex _missleLine[2];
    sf::CircleShape _endpoint;

    sf::Vector2f _startPoint;
    sf::RenderWindow *_window;
    bool _finished = false;
public:
    AttackMissle(sf::RenderWindow *window, sf::Vector2f startPoint);
    ~AttackMissle();

    void draw(float) override;
};