#include "renderer.h"

#include <thread>
#include <chrono>

#if _DEBUG
#include <iostream>
#endif


Renderer::Renderer()
{
	_window = new sf::RenderWindow(sf::VideoMode(800, 600), "WindowName");
	_window->setVerticalSyncEnabled(false);
	_window->setFramerateLimit(300);
	_view = new sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));

	_running.store(true);

	_cursor = new Cursor(sf::Vector2f{VIEW_WIDTH / 2.0f, VIEW_HEIGHT / 2.0f});

	this->init();
}

Renderer::~Renderer()
{
	_running.store(false);
	_renderThread.join();
	_hotkeyThread.join();
	delete _view;
	_view = nullptr;
	delete _window;
	_window = nullptr;
	delete _cursor;
	_cursor = nullptr;
}

void Renderer::init()
{
	auto windowSize = _window->getSize();
}

void Renderer::render()
{
	sf::Clock clock;
	_window->setActive(true);

	while (_window->isOpen() || this->_running.load())
	{
		{
			deltaTime = clock.restart().asSeconds();
			std::lock_guard<std::shared_mutex> mutex(_mutex);
			_window->clear();

			_cursor->draw(_window);

			_window->display();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void Renderer::loop()
{
	_window->setActive(false);

	_renderThread = std::thread([this]() {
		render();
	});

	_hotkeyThread = std::thread([this]() {
		hotkeyListener();
	});

	while (_window->isOpen())
	{
		eventLoop();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void Renderer::eventLoop()
{
	sf::Event evnt;

	while (_window->pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case sf::Event::Resized:
			resizeView();
			break;
		case evnt.Closed:
			_running = false;
			_window->close();
			break;
		default:
			break;
		}
		std::this_thread::sleep_for(std::chrono::nanoseconds(1));
	}
}

void Renderer::hotkeyListener()
{
	while (_running.load())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			std::lock_guard<std::shared_mutex> mutex(_mutex);
			_cursor->up(deltaTime);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			std::lock_guard<std::shared_mutex> mutex(_mutex);
			_cursor->down(deltaTime);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			std::lock_guard<std::shared_mutex> mutex(_mutex);
			_cursor->left(deltaTime);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			std::lock_guard<std::shared_mutex> mutex(_mutex);
			_cursor->right(deltaTime);
		}
	}
}

void Renderer::resizeView()
{
	float aspectRatio = float(_window->getSize().x / _window->getSize().y);
	_view->setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

void Renderer::start()
{
	this->loop();
}
