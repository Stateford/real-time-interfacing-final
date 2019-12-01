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
    sf::CircleShape *_endpoint;

    sf::Vector2f _startPoint;
    bool _finished = false;
public:
    AttackMissle(const sf::Vector2f &startPoint);
    ~AttackMissle();

    AttackMissle(const AttackMissle&);
    AttackMissle(AttackMissle&&) noexcept;

    AttackMissle& operator=(const AttackMissle&);
    AttackMissle& operator=(AttackMissle&&) noexcept;

    void defendHit() { _finished = true; }

    bool checkScreenBounds() const;

    // Actor overrides
    bool finished() const override { return _finished; }
    void draw(float) override;
    //bool collision(const Actor& actor) const override;
    sf::Shape* getShape() const override { return _endpoint; };
};