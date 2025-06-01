#pragma once

#include <string>

#include "Figure.h"

class Text : public Figure
{
private:
    static sf::Font* font;
    std::string text;

public:
    Text(const Box& box);

    void setText(const std::string& text);
    static void setFont(sf::Font& font);

protected:
    void drawFigure(sf::RenderWindow& window, const Box& screen_box) override;
};