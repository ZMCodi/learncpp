#include <iostream>
#include <iterator>
#include <numeric>

// array is the array to search over.
// target is the value we're trying to determine exists or not.
// min is the index of the lower bounds of the array we're searching.
// max is the index of the upper bounds of the array we're searching.
// binarySearch() should return the index of the target element if the target is found, -1 otherwise
int binarySearch(const int* array, int target, int min, int max)
{
    while (max >= min)
    {
        int midpoint{std::midpoint(max, min)};

        if (array[midpoint] == target) {return midpoint;}

        if (array[midpoint] > target)
        {
            max = midpoint - 1;
        } else 
        {
            min = midpoint + 1;
        }
    }

    return -1;
}

int binarySearchRecursive(const int* array, int target, int min, int max)
{
    if (min > max) {return -1;}
    int midpoint(std::midpoint(min, max));

    if (array[midpoint] == target) {return midpoint;}

    if (array[midpoint] > target) {return binarySearchRecursive(array, target, min, midpoint-1);}
    if (array[midpoint] < target) {return binarySearchRecursive(array, target, midpoint+1, max);}

    return -1;
}


int main()
{   //                     0  1  2   3   4   5   6   7   8   9  10  11  12  13  14
    constexpr int array[]{ 3, 6, 8, 12, 14, 17, 20, 21, 26, 32, 36, 37, 42, 44, 48 };

    // We're going to test a bunch of values to see if the algorithm returns the result we expect

    // Here are the test values
    constexpr int testValues[]{ 0, 3, 12, 13, 22, 26, 43, 44, 48, 49 };

    // And here are the results that we expect for those test values
    int expectedResult[]{ -1, 0, 3, -1, -1, 8, -1, 13, 14, -1 };

    // Make sure we have the same number of test values and expected results
    static_assert(std::size(testValues) == std::size(expectedResult));

    int numTestValues { std::size(testValues) };
    // Loop through all of the test values
    for (int count{ 0 }; count < numTestValues; ++count)
    {
        // See if our test value is in the array
        int index{ binarySearchRecursive(array, testValues[count], 0, static_cast<int>(std::size(array)) - 1) };
        // If it matches our expected value, then great!
        if (index == expectedResult[count])
             std::cout << "test value " << testValues[count] << " passed!\n";
        else // otherwise, our binarySearch() function must be broken
             std::cout << "test value " << testValues[count] << " failed.  There's something wrong with your code!\n";
    }

    return 0;
}
