#pragma once

#include "Potion.h"
#include "../Random.h"

class Player {

    static constexpr int s_minStartingGold { 80 };
    static constexpr int s_maxStartingGold { 120 };

    int m_gold{};
    std::string m_name{};
    [[maybe_unused]] std::array<int, Potion::maxPotions> m_inventory{};

public:
    Player(std::string_view name)
        : m_gold{Random::get(s_minStartingGold, s_maxStartingGold)}
        , m_name{name} {}

    std::string_view name() const {return m_name;}
    int gold() const {return m_gold;}

    void buy(Potion::Type p);
    void printInventory();
};

Player welcome();
