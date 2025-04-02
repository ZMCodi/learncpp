#include "UserInput.h"

bool UserInput::isValid(char command)
{
    bool valid{false};
    for (std::size_t i{}; i < validInputs.size(); ++i)
    {
        if (validInputs[i] == command) {valid = true; break;}
    }

    return valid;
}

void UserInput::getUserInput()
{
        while (true)
        {
            char command{};
            std::cin >> command;

            bool valid{isValid(command)};

            if (!valid)
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            } else
            {
                std::cout << "Valid command: " << command << '\n';
            }

            if (command == 'q')
            {
                std::cout << "\n\nBye\n\n";
                return;
            }
        }
}
