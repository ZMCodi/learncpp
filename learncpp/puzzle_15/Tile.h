#pragma once

#include <iostream>

class Tile
{
    int m_value{};

public:
    Tile(int value) :m_value{value} {}

    bool isEmpty() {return m_value == 0;}
    int getNum() {return m_value;}

    friend std::ostream& operator<<(std::ostream& out, Tile& tile);
};
