#pragma once
#include "../Random.h"
#include "Card.h"
#include <algorithm>
#include <cassert>

class Deck {
private:
    std::array<Card, 52> m_cards{};
    std::size_t m_idx{};

public:

    Deck();

    Card dealCard();
    void shuffle();
};
