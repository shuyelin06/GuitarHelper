#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

struct Box {
    float x, y, w, h;
    
    Box();
    Box(float x, float y, float w, float h);
};

// Figure Class:
// Represents a base class for rendering to select
// boxes on the screen.
class Figure
{
private:
    // Local x, y, width, height within [0,1].
    Box box;
    // Children
    std::vector<Figure*> children;

public:
    Figure(const Box& box);

    void draw(sf::RenderWindow& window, const Box& target);
    void addChild(Figure& figure);
    
protected:
    virtual void drawFigure(sf::RenderWindow& window, const Box& screen_box);
};