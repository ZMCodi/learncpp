#pragma once
#include "Deck.h"
#include <iostream>

struct Player {
    int score{};
};

namespace Settings {
    constexpr int bust{21};
    constexpr int dealerMax{17};
}

using Dealer = Player;

bool playersTurn(Deck& deck, Player& player);
bool dealersTurn(Deck& deck, Dealer& dealer);
bool blackjack();
