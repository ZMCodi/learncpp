#pragma once

#include <iostream>
#include "Creature.h"

void handlePlayerWin(Player&p, Monster& m);
void handlePlayerLoss(Player&p);
int handleAttack(Player& p, Monster& m);
int attackMonster(Player& p, Monster& m);
int attackPlayer(Player& p, Monster& m);
bool fightMonster(Player& p, Monster& m);
