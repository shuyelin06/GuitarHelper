#include "Recorder.h"

#include <iostream>

// Creates a recorder, which will store enough samples for N seconds.
// While recording, the recorder will remove the oldest data, and internally maintain
// a ring buffer.
Recorder::Recorder(float seconds)
{
    data.resize((int)(seconds * SamplingRate()));
    tail = 0;
}
Recorder::~Recorder() = default;

std::int16_t Recorder::getSample(int index)
{
    return data[(tail + index) % data.size()];
}
int Recorder::getSize() { return data.size(); }

// Copies the input_data samples to our data buffer
void Recorder::pullInputAudio()
{
    mutex.lock();

    const int new_tail = tail + input_data.size();
    if (new_tail <= data.size())
    {
        memcpy(&data[tail], &input_data[0], input_data.size() * sizeof(std::int16_t));
    }
    else
    {
        const int c1_size = data.size() - tail;
        const int c2_size = input_data.size() - c1_size;
        memcpy(&data[tail], &input_data[0], c1_size * sizeof(std::int16_t));
        memcpy(&data[0], &input_data[c1_size], c2_size * sizeof(std::int16_t));
    }

    // for (int i = 0; i < input_data.size(); i++)
    // {
    //     data[tail++] = input_data[i];
    //     tail = tail % data.size();
    // }

    tail = new_tail % data.size();
    input_data.clear();

    mutex.unlock();
}

// Averages neighboring samples and populates output with aggregate_count
// data values
void Recorder::aggregateData(std::vector<std::int16_t> &output, int samples_per_data)
{
    output.clear();
    int index = tail + 1;

    std::int16_t avg = 0;
    int count = 0;
    for (int i = 0; i < data.size(); i++)
    {
        avg += data[index++ % data.size()];
        count++;
        if (count == samples_per_data) {
            avg /= samples_per_data;
            output.push_back(avg);
            
            avg = 0;
            count = 0;
        }
    }
    
}

// Overwritten method that will set the processing timeframe
bool Recorder::onStart()
{
    input_data.clear();
    memset(&data[0], 0, data.size() * sizeof(data[0]));
    return true;
}

// Overwritten method that will save the samples to an input buffer. This buffer
// will be copied to our readable data buffer, so that we don't stall the
// input device.
bool Recorder::onProcessSamples(const std::int16_t *samples, std::size_t sampleCount)
{
    mutex.lock();

    const int end = input_data.size();
    input_data.resize(end + sampleCount);
    memcpy(&input_data[end], samples, sampleCount * sizeof(std::int16_t));

    mutex.unlock();

    return true;
}

int Recorder::SamplingRate() {
    return 44100;
}