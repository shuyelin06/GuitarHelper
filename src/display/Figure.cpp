#include "Figure.h"

Box::Box() = default;
Box::Box(float _x, float _y, float _w, float _h)
{
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

Figure::Figure(const Box& _box) : children(0) {
    box = _box;
}

void Figure::addChild(Figure& figure) {
    children.push_back(&figure);
}

void Figure::draw(sf::RenderWindow& window, const Box& target) {
    const float x = target.x + box.x * target.w;
    const float y = target.y + box.y * target.h;
    const float w = target.w * box.w;
    const float h = target.h * box.h;

    drawFigure(window, Box(x,y,w,h));

    for (Figure* child : children)
        child->draw(window, Box(x,y,w,h));
}

void Figure::drawFigure(sf::RenderWindow& window, const Box& screen_box) {
    sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(screen_box.w, screen_box.h));
    rect.setPosition(sf::Vector2f(screen_box.x, screen_box.y));
    rect.setFillColor(sf::Color::Red);
    window.draw(rect);
}
