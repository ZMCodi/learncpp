#include <iostream>
#include <stdexcept>

class Fraction
{
public:
    int numerator{};
    int denominator{1};

    Fraction(int a, int b)
    : numerator{a}, denominator{b}
    {
        if (b == 0)
        {
            throw std::runtime_error("Invalid denominator");
        }
    }
};


int main()
{
    int num{};
    int den{};

    std::cout << "Enter the numerator: ";
    std::cin >> num;
    std::cout << "Enter the denominator: ";
    std::cin >> den;

    try
    {
        Fraction f {num, den};
        std::cout << "Your fraction is " << f.numerator << '/' << f.denominator;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}
