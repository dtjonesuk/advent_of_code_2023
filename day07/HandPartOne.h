//
// Created by David on 09/12/2023.
//

#ifndef ADVENT_OF_CODE_2023_HANDPARTONE_H
#define ADVENT_OF_CODE_2023_HANDPARTONE_H

#include "Hand.h"

namespace day07 {

    class HandPartOne : public Hand<HandPartOne> {
    public:
        HandPartOne(std::string str, int bid) : Hand(str,bid) {}

        // Calculates the type of hand we have
        [[nodiscard]] HandType get_type() const;

        // Calculates the values of the cards
        [[nodiscard]] std::vector<unsigned> get_values() const;

        [[nodiscard]] std::map<char, int> get_card_values() const;
    };

} // day07

#endif //ADVENT_OF_CODE_2023_HANDPARTONE_H
