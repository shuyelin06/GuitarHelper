#pragma once

// Chromagram Class:
// Converts a frequency spectrum to the 12 distinct chroma
// (semitones) that make up music.
// These semitones are based off A4, with frequency 440Hz.
class Chromagram
{
private:
    int chroma[12];
    float accumulated[12];

public:
    Chromagram();
};