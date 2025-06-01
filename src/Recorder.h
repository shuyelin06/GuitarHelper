#pragma once

#include <vector>
#include <mutex>

#include <SFML/Audio.hpp>

// Recorder implements a ring buffer to store samples in.
class Recorder : public sf::SoundRecorder
{
private:
    // Sample data will be written to this input_data buffer,
    // to be copied over later.
    std::mutex mutex;
    std::vector<std::int16_t> input_data;

    std::vector<std::int16_t> data;
    int tail;

public:
    Recorder(float num_seconds);
    ~Recorder();

    void pullInputAudio();
    void aggregateData(std::vector<std::int16_t>& output, int aggregate_count);

    std::int16_t getSample(int index);
    int getSize();
    
    static int SamplingRate();
    
protected:
    bool onStart() override;
    bool onProcessSamples(const std::int16_t *samples, std::size_t sampleCount) override;
};