#include <iostream>
#include <cassert>
#include <cmath>

int factorial(int n)
{
    if (n <= 1)
    {
        return 1;
    }

    return factorial(n - 1) * n;
}

int sumDigits(int num)
{
    if (num < 10) {return num;}

    return sumDigits(num / 10) + num % 10;
}

void printBinary(unsigned int n)
{
	if (n > 1)
	{
		printBinary(n / 2);
	}

	std::cout << n % 2;
}

int main()
{
    assert(factorial(4) == 24);
    assert(factorial(5) == 120);
    assert(factorial(6) == 720);

    assert(sumDigits(93427) == 25);

    printBinary(4);
    std::cout << '\n';
}
