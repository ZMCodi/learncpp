#include <array>
#include <iostream>
#include <string_view>

#include "Potion.h"
#include "Player.h"

bool buyPotion(Player& p, Potion::Type potion) {
    if (p.gold() < Potion::costs[potion]) {
        std::cout << "You cannot afford that.\n";
        return false;
    }

    p.buy(potion);
    std::cout << "You purchased a potion of " << Potion::names[potion] << ". You have " << p.gold() << " gold left.\n\n";
    return true;
}

int main() {
    Player p{welcome()};

    shop();

    while (true ) {
        std::cout << "Enter the number of potion you'd like to buy or 'q' to quit: ";
        char choice{};
        std::cin >> choice;

        if (choice == 'q') {
            p.printInventory();
            return 0;
        } else {
            if (buyPotion(p, static_cast<Potion::Type>(choice - '0'))) {
                shop();
            }
        }
    }
}
