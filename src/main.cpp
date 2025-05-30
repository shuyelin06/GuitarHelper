#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include "Recorder.h"
constexpr int WINDOW_WIDTH = 1920u;
constexpr int WINDOW_HEIGHT = 1080u;

int main()
{
    // Create my window
    auto window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Guitar Helper");
    window.setFramerateLimit(144);

    // Set up an audio recorder
    if (!sf::SoundBufferRecorder::isAvailable())
    {
        std::cout << "Sound Recorder Not Available!";
        return 1;
    }

    Recorder recorder = Recorder(1.f);
    recorder.start(44100);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            // else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            // {
            //     if (keyPressed->scancode == sf::Keyboard::Scancode::O)
            //         recorder.start();
            //     else if (keyPressed->scancode == sf::Keyboard::Scancode::P)
            //         recorder.stop();
            // }
        }

        window.clear();

        recorder.pullInputAudio();
        
        const int size = recorder.getSize();
        sf::CircleShape shape(1.f);
        shape.setFillColor(sf::Color::Blue);
        
        for (int i = 0; i < size; i++) 
        {
            const std::int16_t sample = recorder.getSample(i);

            const float x = float((i + 1) * WINDOW_WIDTH) / float(size + 2);
            const float y = WINDOW_HEIGHT / 2 + sample / 5.f;
            
            shape.setPosition(sf::Vector2f(x,y));
            window.draw(shape); 
        }

        window.display();
    }

    recorder.stop();
}