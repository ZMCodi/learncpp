#include <iostream>
#include "Potion.h"

void shop() {
    std::cout << "Here is our selection for today:\n";

    for (auto potion : Potion::types) {
        std::cout << potion << ") " << Potion::names[potion] << " costs " << Potion::costs[potion] << '\n';
    }
}

