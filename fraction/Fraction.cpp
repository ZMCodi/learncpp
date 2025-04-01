#include "Fraction.h"

void Fraction::reduce()
{
    int gcd{std::gcd(m_num, m_den)};
    if (gcd)
    {
        m_num /= gcd;
        m_den /= gcd;
    }
}

void Fraction::print()
{
    std::cout << m_num << '/' << m_den << '\n';
}

Fraction operator*(int a, const Fraction& b)
{
    return Fraction{a * b.m_num, b.m_den};
}

Fraction operator*(const Fraction& a, int b)
{
    return (b * a);
}

Fraction operator*(const Fraction& a, const Fraction& b)
{
    return Fraction{a.m_num * b.m_num, a.m_den * b.m_den};
}
