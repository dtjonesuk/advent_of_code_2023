//
// Created by David on 07/12/2023.
//

#ifndef ADVENT_OF_CODE_2023_HAND2_H
#define ADVENT_OF_CODE_2023_HAND2_H

#include "../advent.h"
#include "Hand.h"
#include <stdexcept>

namespace day07 {

    class HandPartTwo : public Hand<HandPartTwo> {
    public:
        HandPartTwo(std::string str, int bid) : Hand(str, bid) {}

        [[nodiscard]] HandType get_type() const;

        [[nodiscard]] std::vector<unsigned> get_values() const;

        [[nodiscard]] std::map<char, int> get_card_values() const;
    };



} // day07

#endif //ADVENT_OF_CODE_2023_HAND2_H
