#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include "Recorder.h"
#include "Fourier.h"
#include "display/BoxPlot.h"
#include "display/Text.h"

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;

const std::string BASE_DIRECTORY = "../";

int main()
{
    // Create my window
    auto window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Guitar Helper");
    window.setFramerateLimit(144);

    // Load my font
    sf::Font font(BASE_DIRECTORY + "resources/arial.ttf");
    Text::setFont(font);

    // Set up an audio recorder
    if (!sf::SoundBufferRecorder::isAvailable())
    {
        std::cout << "Sound Recorder Not Available!";
        return 1;
    }

    BoxPlot box_plot = BoxPlot(Box(0.1f, 0.1f, 0.8f, 0.8f));

    Recorder recorder = Recorder(0.1f);
    std::vector<std::int16_t> output_data;
    recorder.start();

    Text test = Text(Box(0.1f, 0.1f, 0.8f, 0.8f));
    test.setText("Testing");
    box_plot.addChild(test);

    // int chroma[12];
    // chroma[0] = 440;
    // const float exp = pow(2, 1 / 12.f);
    // for (int i = 1; i < 12; i++)
    //     chroma[i] = exp * chroma[i - 1];
    // float accumulated[12] = {};

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        // Pull the available audio data we have
        recorder.pullInputAudio();
        recorder.aggregateData(output_data, 1);

        // Perform the FFT to obtain the frequencies
        FourierSolver solver;
        const std::vector<Complex> &frequencies = solver.FFT(output_data);

        // Bin the frequencies into chromatic notes
        constexpr int NUM_BINS = 12;
        float bins[NUM_BINS] = {};

        box_plot.clear();
        
        for (int i = 0; i < frequencies.size(); i++)
        {
            const float frequency = i * Recorder::SamplingRate() / frequencies.size();

            // Only include frequencies in the range of human hearing
            if (20 <= frequency && frequency < 20000)
            {
                // const float sample = frequencies[i].magnitude();
                // box_plot.addBar(sample);

                int bin_index = int(round(69 + NUM_BINS * log2f(frequency / 440.f))) % NUM_BINS;
                bins[bin_index] += frequencies[i].magnitude();
            }

        }

        for (int i = 0; i < 12; i++) {
            box_plot.addBar(bins[i]);
        }

        // for (int i = 0; i < 12; i++)
        // {
        //     accumulated[i] = 0.f;

        //     int freq = chroma[i];
        //     while (freq < frequencies.size() && freq < 4000) {
        //         accumulated[i] += frequencies[freq - 1].magnitude() / frequencies.size();
        //         accumulated[i] += frequencies[freq].magnitude() / frequencies.size();
        //         accumulated[i] += frequencies[freq + 1].magnitude() / frequencies.size();
        //         freq *= 2;
        //     }

        //     accumulated[i] = pow(accumulated[i], 2);
        // }
        
        box_plot.draw(window, Box(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

        window.display();
    }

    recorder.stop();
}