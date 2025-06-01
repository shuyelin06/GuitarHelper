#include "Text.h"

sf::Font* Text::font = nullptr;

Text::Text(const Box& box) : Figure(box) {
    text = "___";
}

void Text::setText(const std::string& _text) {
    text = _text;
}

void Text::setFont(sf::Font& _font) {
    font = &_font;
}

void Text::drawFigure(sf::RenderWindow& window, const Box& screen_box) {
    sf::Text g_text(*font);
    g_text.setString(text);
    
    // Scale the text so it fits in our box
    unsigned int size = screen_box.h;
    size = std::min(size, (unsigned int) (float(g_text.getCharacterSize()) * screen_box.w / g_text.getGlobalBounds().size.x));
    g_text.setCharacterSize(size);

    g_text.setPosition(sf::Vector2f(screen_box.x, screen_box.y));
    window.draw(g_text);
}