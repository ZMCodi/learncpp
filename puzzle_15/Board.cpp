#include "Board.h"

std::ostream& operator<<(std::ostream& out, Board& board)
{
    for(int i{}; i < g_consoleLines; ++i) {out << '\n';}

    for(auto& tile : board.m_tiles)
    {
        out << tile;
        if (tile.getNum() % 4 == 0)
        {
            out << '\n';
        }
    }

    return out;
}
