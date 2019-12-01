#pragma once

#include "cursor.h"
#include "defenseMissle.h"
#include "shelter.h"
#include "statusBar.h"
#include "../../templates/container.h"
#include "../enemy/enemyController.h"
#include <vector>
#include <memory>

class Player {

private:
	Cursor* _cursor;
    ActorContainer<DefenseMissle*> _missles;
    ActorContainer <Shelter*> _shelters;
    StatusBar* _statusBar;

    const unsigned int MAX_HEALTH = 10;
    unsigned int health = MAX_HEALTH;

    friend class EnemeyController;
public:
	Player();
	~Player();

	void up(float);
	void down(float);
	void right(float);
	void left(float);

    void move(float, float, float);

	void shoot();

	void draw(float);
    void collisionCheck(EnemyController&);
};