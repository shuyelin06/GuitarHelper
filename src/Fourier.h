#pragma once

#include <vector>

class Complex {
public:
    float r, im;

    Complex();    
    Complex(float r, float im);
    
    float magnitude() const;

    static Complex Exp(float r);

    Complex operator+(const Complex& c) const;
    Complex operator-(const Complex& c) const;
    Complex operator*(const Complex& c) const;
};

// Fourier Class:
// My own implementation of the fourier transform.
class FourierSolver
{
private:
    std::vector<Complex> frequencies;

public:
    FourierSolver();

    const std::vector<Complex>& DFT(const std::vector<int16_t>& sampled_data);
    const std::vector<Complex>& FFT(const std::vector<int16_t>& sampled_data);

private:
    void FFTHelper(int start, int length);
    void BitReversalSort();
};