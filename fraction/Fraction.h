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

    friend bool operator==(const Fraction& a, const Fraction& b){return (a.m_num == b.m_num && a.m_den == b.m_den);}
    friend bool operator!=(const Fraction& a, const Fraction& b){return !operator==(a, b);}
    friend bool operator<(const Fraction& a, const Fraction& b){return (a.m_num * b.m_den < b.m_num * a.m_den);}
    friend bool operator>(const Fraction& a, const Fraction& b){return operator<(b, a);}
    friend bool operator<=(const Fraction& a, const Fraction& b){return !operator>(a, b);}
    friend bool operator>=(const Fraction& a, const Fraction& b){return !operator<(a, b);}

};
