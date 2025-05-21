#include <iostream>
#include <utility>
#include <iterator>

int main() {
    int arr[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
    constexpr int length{static_cast<int>(std::size(arr))};

    bool noSwap{true};
    for (int i{length - 1}; i >= 0; --i) {
        for (int j{}; j < i; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                noSwap = false;
            }
        }
        if (noSwap) {
            std::cout << "Early termination on iteration " << length - i << std::endl;
            break;
        }
        noSwap = true;
    }

    for (int i{}; i < length; ++i) {
        std::cout << arr[i] << ' ';
    }
}
