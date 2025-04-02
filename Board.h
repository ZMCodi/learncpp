#pragma once

#include "Tile.h"

// Increase amount of new lines if your board isn't
// at the very bottom of the console
constexpr int g_consoleLines{ 25 };

// Your code goes here

class Board
{
    std::array<Tile, 16> m_tiles{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};

public:
    friend std::ostream& operator<<(std::ostream& out, Board& board);
};
