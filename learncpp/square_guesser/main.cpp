#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
#include <cmath>
#include "../Random.h"

std::vector<int> generateSquares(int start, int num, int mult)
{
    std::vector<int> squares{};
    squares.reserve(static_cast<std::size_t>(num));

    for (int i{}; i < num; ++i)
    {
        squares.push_back((start + i) * (start + i) * mult);
    }

    return squares;
}

void guess(std::vector<int>& squares) 
{
    while (true)
    {
        int guess{};
        std::cin >> guess;

        auto found{std::find(squares.begin(), squares.end(), guess)};

        if (found != squares.end())
        {
            squares.erase(found);
            if (squares.size())
            {
                std::cout << "Nice! " << squares.size() << " number(s) left.\n";
            } else 
            {
                std::cout << "Nice! You found all numbers, good job!\n";
                return;
            }

        } else 
        {
            auto closest{
                std::min_element(squares.begin(), squares.end(),
                                [guess](int a, int b)
                                {
                                    return std::abs(guess - a) < std::abs(guess - b);
                                })
            };

            std::cout << guess << " is wrong. Try " << *closest <<  " next time.\n";
            return;
        }
    }
}

int main()
{
  int start{};
  std::cout << "Start where? ";
  std::cin >> start;

  int numOfSquares{};
  std::cout << "How many? ";
  std::cin >> numOfSquares;

  int multiplier{Random::get(2, 4)};

  std::vector squares{generateSquares(start, numOfSquares, multiplier)};
  std::cout << "I generated " << numOfSquares << " square numbers. Do you know what each number is after multiplying it by " << multiplier << "?\n";

  guess(squares);

  for (auto square : squares)
  {
    std::cout << square << ' ';
  }
}
