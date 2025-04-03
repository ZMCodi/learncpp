#pragma once

#include "../Random.h"

class Creature
{
protected:
    char m_symbol{};
    int m_health{};
    int m_damage{};
    int m_gold{};
    std::string m_name{};

public:
    Creature(std::string_view name, char symbol, int health, int damage, int gold)
        : m_symbol{symbol}
        , m_health{health}
        , m_damage{damage}
        , m_gold{gold}
        , m_name{name} {}

    char getSymbol() const {return m_symbol;}
    int getHealth() const {return m_health;}
    int getDamage() const {return m_damage;}
    int getGold() const {return m_gold;}
    const std::string& getName() const {return m_name;}

    void addGold(int gold) {m_gold += gold;}
    void reduceHealth(int health) {m_health -= health;}
    bool isDead() {return m_health <= 0;}
};

class Player: public Creature
{
    int m_level{1};

public:
    Player(std::string_view name)
        : Creature{name, '@', 10, 1, 0} {}

    int getLevel() {return m_level;}
    void levelUp() {++m_level; ++m_damage;}
    void replenishHealth() {m_health += 5;}
    bool hasWon() {return m_level >= 20;}
};

class Monster: public Creature
{
public:
    enum Type
    {
        dragon,
        orc,
        slime,
        max_types,
    };

private:
    static inline Creature monsterData[] {
        {"dragon", 'D', 20, 4, 100},
        {"orc",    'o',  4, 2,  25},
        {"slime",  's',  1, 1,  10},
    };

    static_assert(std::size(monsterData) == max_types);

public:
    Monster(Type type)
        : Creature{monsterData[type]} {}

    static Monster getRandomMonster()
    {
        return Monster{static_cast<Type>(Random::get(0, max_types - 1))};
    }
};
