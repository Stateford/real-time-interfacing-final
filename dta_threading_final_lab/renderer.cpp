#include "renderer.h"

#include <thread>
#include <chrono>

#if _DEBUG
#include <iostream>
#endif

std::unique_ptr<sf::RenderWindow> Renderer::window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "WINDOWNAME");

Renderer::Renderer()
{
	window->setVerticalSyncEnabled(false);
	window->setFramerateLimit(300);
	_view = new sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));

	_running.store(true);

    _enemy = new EnemyController();
	_player = new Player();

	this->init();
}

Renderer::~Renderer()
{
	_running.store(false);
	_renderThread.join();
	_hotkeyThread.join();
	delete _view;
	_view = nullptr;
    delete _enemy;
    _enemy = nullptr;
	delete _player;
	_player = nullptr;
}

void Renderer::init()
{
	auto windowSize = window->getSize();
}

void Renderer::render()
{
	sf::Clock clock;
	window->setActive(true);

	while (window->isOpen() || this->_running.load())
	{
		deltaTime = clock.restart().asSeconds();
		{
			window->clear();
            {
			    std::lock_guard<std::shared_mutex> mutex(_mutex);
			    // draw the player object
			    _player->draw(deltaTime);
                _enemy->draw(deltaTime);
            }

			window->display();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void Renderer::loop()
{
	window->setActive(false);

	_renderThread = std::thread([this]() {
		render();
	});

	_hotkeyThread = std::thread([this]() {
		hotkeyListener();
	});

	while (window->isOpen())
	{
		eventLoop();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void Renderer::eventLoop()
{
	sf::Event evnt;

	while (window->pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case sf::Event::Resized:
			resizeView();
			break;
		case evnt.Closed:
			_running = false;
			window->close();
			break;
		default:
			break;
		}
		std::this_thread::sleep_for(std::chrono::nanoseconds(1));
	}
}

void Renderer::hotkeyListener()
{
    static bool is_pressed = false;
	while (_running.load())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			std::lock_guard<std::shared_mutex> mutex(_mutex);
			_player->up(deltaTime);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			std::lock_guard<std::shared_mutex> mutex(_mutex);
			_player->down(deltaTime);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			std::lock_guard<std::shared_mutex> mutex(_mutex);
			_player->left(deltaTime);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			std::lock_guard<std::shared_mutex> mutex(_mutex);
			_player->right(deltaTime);
		}

		if (!is_pressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
            is_pressed = true;
			_player->shoot();
		}

        if (is_pressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            is_pressed = false;
        }
	}
}

void Renderer::resizeView()
{
	float aspectRatio = float(window->getSize().x / window->getSize().y);
	_view->setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

void Renderer::start()
{
	this->loop();
}
