#include <iostream>
#include <iterator>
#include <utility>

int main() {
    int arr[] { 30, 60, 20, 50, 40, 10 };
    constexpr int length{static_cast<int>(std::size(arr))};

    for (int i{}; i < length - 1; ++i) {
        int smallestIdx{i};
        for (int currIdx{i}; currIdx < length; ++currIdx) {
            if (arr[smallestIdx] > arr[currIdx]) {
                smallestIdx = currIdx;
            }
        }
        std::swap(arr[i], arr[smallestIdx]);
    }

    for (int i{}; i < length; ++i) {
        std::cout << arr[i] << ' ';
    }


}
