#include "Tile.h"

std::ostream& operator<<(std::ostream& out, Tile& tile)
{
    if(tile.m_value >= 10)
    {
        out << ' ' << tile.m_value << ' ';
    } else if (tile.m_value == 0)
    {
        out << "    ";
    } else
    {
        out << "  " << tile.m_value << ' ';
    }

    return out;
}
