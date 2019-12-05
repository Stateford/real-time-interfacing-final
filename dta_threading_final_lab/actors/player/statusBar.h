#pragma once

#include "../actor.h"
#include <SFML/Graphics.hpp>

constexpr const char* const FONT_STYLE = "fonts/BebasNeue-Regular.ttf";

class StatusBar : public Actor
{
private:
    sf::Font _font;
    sf::Text _scoreText;

    unsigned int _score;
    float _baseLine;

    void _writeScore();
public:
    StatusBar();
    ~StatusBar() = default;

    void addScore(unsigned int);
    unsigned int getScore() const { return _score; }


    void draw() override;
    sf::Shape* getShape() const { return nullptr; }
};