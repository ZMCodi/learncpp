#include <iostream>
#include "Monster.h"
#include "MonsterGenerator.h"

int main() {
    std::cout << "Enter how many monsters to generate: ";
    int monsters{};
    std::cin >> monsters;

    for (int i{}; i < monsters; ++i) {
        MonsterGenerator::generate().print();
    }
}
