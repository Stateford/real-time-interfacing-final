#pragma once

#include "cursor.h"
#include "defenseMissle.h"
#include "shelter.h"
#include "../../templates/container.h"
#include <vector>
#include <memory>

class Player {

private:
	Cursor *_cursor;
    ActorContainer<DefenseMissle*> _missles;
    ActorContainer <Shelter*> _shelters;

    const unsigned int MAX_HEALTH = 10;
    unsigned int health = MAX_HEALTH;

public:
	Player();
	~Player();

	void up(float);
	void down(float);
	void right(float);
	void left(float);

	void shoot();

	void draw(float);
    bool collision(const sf::Vector2f&) const;
};