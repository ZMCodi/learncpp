#include <iostream>
#include "Point3d.h"
#include "Vector3d.h"

int main() {
    std::cout << "Enter 3 coordinates: ";
    double x{}; double y{}; double z{};
    std::cin >> x >> y >> z;

    Point3d point(x, y, z);
    std::cout << "Your point is ";
    point.print();

    while (true) {
        std::cout << "\n\nMove your point? (y/n) ";
        char choice{};
        std::cin >> choice;

        if (choice == 'n') {return 0;}

        std::cout << "Enter the vector to move it by: ";
        std::cin >> x >> y >> z;

        Vector3d vec{x, y, z};

        std::cout << "Moving ";
        point.print(); 
        std::cout << " by ";
        vec.print();

        point.moveByVector(vec);
        std::cout << "\nYour point is now ";
        point.print();

    }
}
