#include "enemyController.h"
#include "../../renderer.h"

EnemyController::EnemyController(sf::RenderWindow *window)
{
    _window = window;
}

void EnemyController::spawn()
{
    const unsigned int windowWidth = Renderer::getWindowSize().x;

    std::uniform_int_distribution<int> distribution(0, windowWidth);
    const unsigned int spawnPoint = distribution(_generator);  // generates number in the range 1..6 
    _missles.push(new AttackMissle(_window, { static_cast<float>(spawnPoint), 0.0f }));
}

void EnemyController::draw(float deltaTime)
{
    _totalTime += deltaTime;

    if (_totalTime >= _spawnTime)
    {
        spawn();
        _totalTime = 0.0f;
    }

    _missles.draw(deltaTime);
}