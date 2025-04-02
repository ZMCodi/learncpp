#include <iostream>
#include <array>
#include "Board.h"
#include "UserInput.h"

int main()
{
    Board board{};
    std::cout << board;
    UserInput::getUserInput();

    return 0;
}
