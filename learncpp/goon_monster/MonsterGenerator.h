#pragma once
#include <string_view>
#include "Monster.h"
#include "../Random.h"

namespace MonsterGenerator{

    constexpr std::string_view getRoar(int i) {
        switch(i) {
            case 0: return "*rawr*";
            case 1: return "*uwu*";
            case 2: return "*nuzzles*";
            case 3: return "*baaaka*";
            case 4: return "*oi oi oi*";
            case 5: return "*nyaaa*";
        }
        return "???";
    }

    constexpr std::string_view getName(int i) {
        switch(i) {
            case 0: return "Bobby Jobby";
            case 1: return "Gooner";
            case 2: return "Joobler";
            case 3: return "Retard";
            case 4: return "Bombaclat";
            case 5: return "Buddy"; 
        }
        return "???";
    }

    Monster generate() {
        return { 
            static_cast<Monster::Type>(Random::get(0, Monster::Type::maxMonsterTypes - 1)), 
            getName(Random::get(0, 5)), 
            getRoar(Random::get(0, 5)), 
            Random::get(0, 100) };
    }
}
