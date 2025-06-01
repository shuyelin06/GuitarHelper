#include "BoxPlot.h"

BoxPlot::BoxPlot(const Box &box) : Figure(box) {}

void BoxPlot::addBar(float height)
{
    bars.push_back(height);
}
void BoxPlot::clear()
{
    bars.clear();
}

void BoxPlot::drawFigure(sf::RenderWindow &window, const Box &screen_box)
{
    // We will first go through and find the max bar height. We will then normalize by this height.
    for (const float &data : bars)
        max_height = std::max(data, max_height);

    const float box_width = screen_box.w / bars.size();

    for (int i = 0; i < bars.size(); i++)
    {
        const float height = (bars[i] / max_height) * screen_box.h;

        const float x = screen_box.x + box_width * i;
        const float y = (screen_box.y + screen_box.h) - height;

        if (height > 0.001f)
        {
            sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(box_width, height));
            rect.setPosition(sf::Vector2f(x, y));
            rect.setFillColor(sf::Color::Blue);
            window.draw(rect);
        }
    }
}