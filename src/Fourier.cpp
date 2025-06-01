#include "Fourier.h"

#include <complex>
#include <math.h>
constexpr float PI = 3.14159f;

Complex::Complex() = default;
Complex::Complex(float _r, float _im)
{
    r = _r;
    im = _im;
}

float Complex::magnitude() const {
    return sqrtf(r * r + im * im);
}

Complex Complex::Exp(float r)
{
    const float real = cosf(r);
    const float im = sinf(r);
    return Complex(real, im);
}

Complex Complex::operator+(const Complex &c) const
{
    return Complex(r + c.r, im + c.im);
}
Complex Complex::operator-(const Complex &c) const
{
    return Complex(r - c.r, im - c.im);
}
Complex Complex::operator*(const Complex &c) const
{
    const float real = r * c.r - im * c.im;
    const float imag = r * c.im + im * c.r;
    return Complex(real, im);
}

FourierSolver::FourierSolver() = default;

const std::vector<Complex>& FourierSolver::DFT(const std::vector<int16_t> &sampled_data)
{
    frequencies.clear();
    const int N = sampled_data.size();

    for (int n = 0; n < N; n++)
    {
        Complex frequency = Complex(0, 0);

        for (int k = 0; k < N; k++)
        {
            const Complex data = Complex(sampled_data[k], 0.f);
            const Complex exp = Complex::Exp(-2 * PI / N * n * k);

            frequency = frequency + data * exp;
        }

        frequencies.push_back(frequency);
    }

    return frequencies;
}

const std::vector<Complex>& FourierSolver::FFT(const std::vector<int16_t> &sampled_data) {
    frequencies.clear();

    // Copy over my sample data
    for (int i = 0; i < sampled_data.size(); i++) 
        frequencies.push_back(Complex(sampled_data[i], 0.f));
    // Find the next power of 2, and pad input data so it is a power of 2
    const int exp = ((int) log2f(sampled_data.size())) + 1;
    const int new_size = (int) pow(2, exp);
    while (frequencies.size() < new_size)
        frequencies.push_back(Complex(0.f, 0.f));
    
    // Perform my FFT. 
    FFTHelper(0, frequencies.size());
    
    // My final results have the frequencies in bit-reversal sorted 
    // order. Reverse this.
    BitReversalSort();


    return frequencies;
}

void FourierSolver::FFTHelper(int start, int length) 
{
    // http://wwwa.pikara.ne.jp/okojisan/otfft-en/cooley-tukey.html
    const int m = length / 2;
    const float theta = 2 * PI / length;

    if (length > 1) {
        for (int i = 0; i < m; i++) {
            const Complex exp = Complex::Exp(-i * theta);
            const Complex a = frequencies[start + i];
            const Complex b = frequencies[start + i + m];
            frequencies[start + i] = a + b;
            frequencies[start + i + m] = (a - b) * exp;
        }
        FFTHelper(start, m);
        FFTHelper(start + m, m);
    }
    
}

void FourierSolver::BitReversalSort() {
    const int N = frequencies.size();
    for (int i = 0, j = 1; j < N - 1; j++) {
        for (int k = N >> 1; k > (i ^= k); k >>= 1);
        if (i < j) std::swap(frequencies[i], frequencies[j]); // swap x[i] and x[j]
    }
}