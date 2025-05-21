#include "Game.h"

void handlePlayerWin(Player&p, Monster& m)
{
    std::cout << "You killed the " << m.getName() << ".\n";
    p.levelUp();
    p.addGold(m.getGold());

    std::cout << "You are now level " << p.getLevel();
    std::cout << ".\nYou found " << m.getGold() << " gold.\n";

    if (p.getLevel() % 5 == 0 && p.getLevel() != 20)
    {
        p.replenishHealth();
        std::cout << "Your health is replenished to " << p.getHealth() << "!\n";
    }
}

void handlePlayerLoss(Player&p)
{
    std::cout << "You died at level " << p.getLevel() << " and with " << p.getGold() << " gold.\n";
    std::cout << "Too bad you can't take it with you!";
}

int handleAttack(Player& p, Monster& m)
{
    if (p.isDead()) { 
        handlePlayerLoss(p);
        return -1; 
    }
    if (m.isDead()) {
        handlePlayerWin(p, m);
        return 1;
    }
    return 0;
}

int attackMonster(Player& p, Monster& m)
{
    std::cout << "You hit the " << m.getName() << " for " << p.getDamage() << " damage.\n";
    m.reduceHealth(p.getDamage());

    return handleAttack(p, m);
}

int attackPlayer(Player& p, Monster& m)
{
    std::cout << "The " << m.getName() << " hit you for " << m.getDamage() << " damage.\n";
    p.reduceHealth(m.getDamage());

    return handleAttack(p, m);
}

// true if player survives, false if player dies
bool fightMonster(Player& p, Monster& m)
{
    std::cout << "You have encountered a " << m.getName() << " (" << m.getSymbol() << ")\n";

    while (true)
    {
        std::cout << "(R)un or (F)ight: ";
        char choice{};
        std::cin >> choice;

        if (choice == 'f' || choice == 'F')
        {

            int res{attackMonster(p, m)};

            if (res == -1) {return false;}
            if (res == 1) {return true;}

            res = attackPlayer(p, m);
            if (res == -1) {return false;}
            if (res == 1) {return true;}

        }

        if (choice == 'r' || choice == 'R')
        {
            int chance{Random::get(0, 1)};
            if (chance)
            {
                std::cout << "You successfully fled.\n";
                return true;
            } else 
            {
                std::cout << "You failed to flee.\n";

                int res{attackPlayer(p, m)};
                if (res == -1) {return false;}
                if (res == 1) {return true;}

                continue;
            }
        }
    }

}
