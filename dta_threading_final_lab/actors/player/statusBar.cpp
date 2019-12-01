#include "statusBar.h"
#include "../../utils.h"
#include "../../renderer.h"
#include "../../exceptions.h"
#include <string>


StatusBar::StatusBar()
{
    _score = 0;
    if (!_font.loadFromFile(FONT_STYLE))
    {
        DEBUGPRINT("cannot load font %s\n", FONT_STYLE);
        throw FontException("Could not load font: " + std::string(FONT_STYLE));
    }

    const auto windowSize = Renderer::window->getSize();
    _scoreText.setFont(_font);
    _scoreText.setFillColor(sf::Color::White);
    _scoreText.setCharacterSize(24);
    _writeScore();
}

void StatusBar::draw()
{
    _writeScore();
    Renderer::window->draw(_scoreText);
}

void StatusBar::_writeScore()
{
    std::wstring score = L"Score: ";
    score += std::to_wstring(_score);
    _scoreText.setString(score);
}

void StatusBar::addScore(unsigned int score)
{
    _score += score;
    _writeScore();
}