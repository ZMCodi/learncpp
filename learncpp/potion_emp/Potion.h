#pragma once
#include <array>
#include <string_view>

namespace Potion {
    enum Type {
        healing,
        mana,
        speed,
        invisibility,
        maxPotions,
    };

    constexpr std::array types{healing, mana, speed, invisibility};
    constexpr std::array costs{20, 30, 12, 50};
    constexpr std::array<std::string_view, maxPotions> names{"healing", "mana", "speed", "invisibility"};

    static_assert(types.size() == maxPotions);
    static_assert(costs.size() == maxPotions);
    static_assert(names.size() == maxPotions);
}

void shop();
