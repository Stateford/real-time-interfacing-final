#pragma once
#include "actors/player/player.h"
#include <SFML\Graphics.hpp>

#include <atomic>
#include <shared_mutex>

class Renderer
{
private:
	sf::RenderWindow *_window;
	std::shared_mutex _mutex;
	std::atomic<bool> _running;
	std::thread _renderThread;
	std::thread _hotkeyThread;
	sf::View *_view;

	Player *_player;

	const float VIEW_WIDTH = 800.0f;
	const float VIEW_HEIGHT = 600.0f;

	// NOTE: temp value
	unsigned int testPlotter = 0;
	float deltaTime = 0.0f;

	void resizeView();
	void init();
	void render();
	void loop();
	void eventLoop();
	void hotkeyListener();
public:
	Renderer();
	~Renderer();


	void start();
};