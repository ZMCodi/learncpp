#pragma once

#include <iostream>
#include <cassert>

class IntArray
{
    std::size_t m_length{};
    int* m_arr{nullptr};

public:
    // constructor
    IntArray(int length);
    IntArray(const IntArray& source);

    // destructor
    ~IntArray(){delete[] m_arr;}

    friend void swap(IntArray& first, IntArray& second);
    IntArray& operator=(IntArray source);

    int& operator[](int idx);
    friend std::ostream& operator<<(std::ostream& out, IntArray& a);
};
