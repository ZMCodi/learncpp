#pragma once

#include <array>
#include <iostream>

namespace UserInput
{
    inline std::array<char, 5> validInputs{'w', 'a', 's', 'd', 'q'};

    bool isValid(char command);
    void getUserInput();
}
