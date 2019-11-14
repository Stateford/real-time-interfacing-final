#pragma once

#include "cursor.h"
#include "defenseMissle.h"
#include <vector>

class Player {

private:
	Cursor *_cursor;
	sf::RenderWindow *_window;
	std::vector<DefenseMissle> _missles;

public:
	Player(sf::RenderWindow*);
	~Player();

	void up(float);
	void down(float);
	void right(float);
	void left(float);

	void shoot();

	void draw(float);
};