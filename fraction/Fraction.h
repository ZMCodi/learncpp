#pragma once

#include <iostream>
#include <numeric>

class Fraction
{
    int m_num{};
    int m_den{};

public:
    Fraction(int num, int den)
        : m_num{num}, m_den{den} {reduce();}

    void reduce();
    void print();

    friend Fraction operator*(int a, const Fraction& b);
    friend Fraction operator*(const Fraction& a, int b);
    friend Fraction operator*(const Fraction& a, const Fraction& b);
};
