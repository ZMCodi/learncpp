#include <iostream>
#include "Card.h"
#include "Deck.h"
#include "Blackjack.h"

int main()
{
    if (blackjack()) {
        std::cout << "\nYou lose!\n";
    } else {
        std::cout << "\nYou win!\n";
    }

    return 0;
}
