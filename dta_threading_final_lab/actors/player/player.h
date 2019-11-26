#pragma once

#include "cursor.h"
#include "defenseMissle.h"
#include "../../templates/container.h"
#include <vector>
#include <memory>

class Player {

private:
	Cursor *_cursor;
    ActorContainer<DefenseMissle*> _missles;

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