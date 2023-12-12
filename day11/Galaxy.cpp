//
// Created by David on 12/12/2023.
//

#include "Galaxy.h"

namespace day11 {
    std::ostream &operator<<(std::ostream &os, const Galaxy &galaxy) {
        os << "(" << galaxy.x << ", " << galaxy.y << ")";
        return os;
    }
} // day11