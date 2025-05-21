#include <iostream>
#include "Player.h"

Player welcome() {
    std::cout << "Welcome to Roscoe's potion emporium!\n";
    std::cout << "Enter your name: ";

    std::string name{};
    std::getline(std::cin >> std::ws, name);

    Player p {name};

    std::cout << "Welcome " << p.name() << ", you have " << p.gold() << " gold.\n\n";

    return p;
}

void Player::buy(Potion::Type p) {
    m_inventory[p] += 1;
    m_gold -= Potion::costs[p];
}

void Player::printInventory() {
    std::cout << "\n\nYour inventory contains: \n";

    for (Potion::Type potion : Potion::types) {
        if (m_inventory[potion]) {
            std::cout << m_inventory[potion] << "x potion of " << Potion::names[potion] << '\n';
        }
    }

    std::cout << "You escaped with " << m_gold << " gold remaining.\n";
}
