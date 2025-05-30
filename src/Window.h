#pragma once

#include "SFML/Graphics.hpp"

class Window {
public:
    virtual void pollInput(sf::Event& event);
    virtual void update();
    virtual void render();
};