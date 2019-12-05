#pragma once
#include "actors/player/player.h"
#include "actors/enemy/enemyController.h"
#include <SFML\Graphics.hpp>

#include <atomic>
#include <memory>
#include <shared_mutex>

class Renderer
{
private:

	std::shared_mutex _mutex;
	std::atomic<bool> _running;
	std::thread _renderThread;
	std::thread _hotkeyThread;
	sf::View *_view;

    EnemyController *_enemy;
	Player *_player;

	const float VIEW_WIDTH = 800.0f;
	const float VIEW_HEIGHT = 600.0f;

    float deltaTime = 0.0f;

    const unsigned int LEVEL_SCORE_LIMIT = 5000;
    unsigned int _scoreMark = 0;

	void resizeView();
	void init();
	void render();
	void loop();
	void eventLoop();
	void hotkeyListener();
public:
	Renderer();
	~Renderer();

    static std::unique_ptr<sf::RenderWindow> window;
    static const sf::Vector2u getWindowSize() { return window->getSize(); };

	void start();
};