#pragma once

#include "attackMissle.h"
#include "../player/player.h"
#include "../../templates/container.h"
#include <sfml/Graphics.hpp>
#include <random>

class EnemyController
{
private:
    sf::RenderWindow *_window;
    unsigned int _level = 1;
    float _spawnTime = 6.0f;
    float _totalTime = 0.0f;
    ActorContainer<AttackMissle*> _missles;
    std::default_random_engine _generator;
public:
    EnemyController(sf::RenderWindow*);
    ~EnemyController() = default;
    void nextLevel() { _level += 1; }
    void spawn();

    void collisionCheck(const Player&);

    void draw(float);
};