#include "Monster.h"
#include <iostream>

void Monster::print() const {
    std::cout << m_name << " the " << getTypeString(m_type);

    if (m_hitpoints) {
        std::cout << " has " << m_hitpoints << " hit points and says " << m_roar << ".\n";
    } else {
        std::cout << " is dead.\n";
    }
}
