#pragma once

#include <iostream>
#include <numeric>

class Fraction
{
    int m_num{};
    int m_den{};

public:
    Fraction(int num = 0, int den = 1)
        : m_num{num}, m_den{den} {reduce();}

    void reduce();

    friend Fraction operator*(int a, const Fraction& b);
    friend Fraction operator*(const Fraction& a, int b);
    friend Fraction operator*(const Fraction& a, const Fraction& b);

    friend std::ostream& operator<<(std::ostream& out, const Fraction& f);
    friend std::istream& operator>>(std::istream& in, Fraction& f);
};
