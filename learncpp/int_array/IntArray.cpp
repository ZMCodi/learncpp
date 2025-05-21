#include "IntArray.h"

// constructor
IntArray::IntArray(int length)
    : m_length{static_cast<std::size_t>(length)}
{
    assert(length > 0 && "Array length must be positive");
    m_arr = new int[m_length]{};
}

// copy constructor with deepcopy
IntArray::IntArray(const IntArray& source)
    : m_length{source.m_length}
{

    if (source.m_arr)
    {
        m_arr = new int[m_length]{};

        for (std::size_t i{}; i < m_length; ++i)
        {
            m_arr[i] = source.m_arr[i];
        }
    } else
    {
        m_arr = nullptr;
    }
}

void swap(IntArray& first, IntArray& second)
{
    std::swap(first.m_length, second.m_length);
    std::swap(first.m_arr, second.m_arr);

}

IntArray& IntArray::operator=(IntArray source)
{
    swap(*this, source);
    return *this;
}

// subscript operator
int& IntArray::operator[](int idx)
{
    assert(idx >= 0 && idx < static_cast<int>(m_length) && "Array index out of bounds");
    return m_arr[idx];
}

// output overload
std::ostream& operator<<(std::ostream& out, IntArray& a)
{
    for (std::size_t i{}; i < a.m_length; ++i)
    {
        out << a.m_arr[i] << ' ';
    }

    return out;
}
