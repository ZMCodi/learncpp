#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>

void insertNames(auto* arr, std::size_t length) {
    for (std::size_t i{}; i < length; ++i) {
        std::cout << "Enter name #" << i + 1 << ": ";
        std::string name{};

        std::getline(std::cin >> std::ws, arr[i]);
    }
}

void printNames(auto* arr, std::size_t length) {
    for (std::size_t i{}; i < length; ++i) {
        std::cout << "Name #" << i + 1 << ": " << arr[i] << '\n';
    }
}


int main() {
    std::cout << "How many names would you like to enter? ";

    std::size_t length{};
    std::cin >> length;

    auto* names{new std::string[length]{}};

    insertNames(names, length);
    std::sort(names, names + length);

    std::cout << "\n\nHere's your sorted list:\n";
    printNames(names, length);

    delete[] names;
}
