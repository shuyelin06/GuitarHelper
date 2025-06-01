#include "Chromagram.h"

#include <math.h>

Chromagram::Chromagram() {
    // Generate my chroma frequencies.
    // A4 will have frequency 440Hz, and every chroma 
    // beyond this can be found by multiplying by 2^{1/12}
    chroma[0] = 440;

    const float exp = pow(2, 1 / 12.f);
    for (int i = 1; i < 12; i++)
        chroma[i] = exp * chroma[i - 1];
}