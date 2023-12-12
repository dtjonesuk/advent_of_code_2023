//
// Created by David on 12/12/2023.
//

#ifndef ADVENT_OF_CODE_2023_GALAXY_H
#define ADVENT_OF_CODE_2023_GALAXY_H
#include <ostream>

namespace day11 {

    struct Galaxy {
        Galaxy(int x, int y) : x(x), y(y) {}

        int x;
        int y;

        bool operator<(const Galaxy& other) {
            if (x==other.x)
                return y < other.y;
            return x < other.x;
        }
    };

    std::ostream& operator<<(std::ostream& os, const Galaxy &galaxy);

} // day11

#endif //ADVENT_OF_CODE_2023_GALAXY_H
