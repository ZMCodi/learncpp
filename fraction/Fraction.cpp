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

std::ostream& operator<<(std::ostream& out, const Fraction& f)
{
    std::cout << f.m_num << '/' << f.m_den;
    return out;
}

std::istream& operator>>(std::istream& in, Fraction& f)
{
    int num{};
    char slash{};
    int den{};

    std::cin >> num >> slash >> den;

    if (den == 0) 
    {
        in.setstate(std::ios_base::failbit);
    }

    if (in)
    {
        f = Fraction{num, den};
    }

    return in;
}
