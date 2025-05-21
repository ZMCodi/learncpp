#include <iostream>
#include <string>
#include <string_view>
#include "Creature.h"
#include "Game.h"

int main()
{
	std::cout << "Enter your name: ";
	std::string playerName;
	std::cin >> playerName;

	Player p{ playerName };
	std::cout << "Welcome, " << p.getName() << ".\n";
    std::cout << "Your adventure begins now...\n\n";

    while (true)
    {
        Monster m{Monster::getRandomMonster()};

        if (!fightMonster(p, m)) {break;}

        if (p.hasWon())
        {
            std::cout << "You won the game with " << p.getGold() << " gold!\n";
            break;
        }
    }


	return 0;
}
