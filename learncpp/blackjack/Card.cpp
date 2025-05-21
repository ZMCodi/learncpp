#include "Card.h"
#include <iostream>

int Card::value() {
    if (rank == 0) {
        return 11;
    }

    return std::min(rank + 1, 10);
}

std::ostream& operator<<(std::ostream& out, const Card &card) {
    out << Card::ranks[card.rank] << Card::suits[card.suit];
    return out;
}
