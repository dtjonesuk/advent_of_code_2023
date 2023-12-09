//
// Created by David on 07/12/2023.
//

#ifndef ADVENT_OF_CODE_2023_HAND2_H
#define ADVENT_OF_CODE_2023_HAND2_H

#include "../advent.h"
#include "Hand.h"
#include <stdexcept>

namespace day07 {

    class HandPartTwo : public Hand {
    public:
        HandPartTwo(std::string str, int bid);

        [[nodiscard]] HandType get_type() const;

        [[nodiscard]] std::vector<unsigned> get_values() const;

    };



} // day07

#endif //ADVENT_OF_CODE_2023_HAND2_H
