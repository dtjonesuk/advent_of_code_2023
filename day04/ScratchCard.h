//
// Created by David on 04/12/2023.
//

#ifndef ADVENT_OF_CODE_2023_SCRATCHCARD_H
#define ADVENT_OF_CODE_2023_SCRATCHCARD_H

#include <string>
#include <regex>
#include <set>

namespace day04 {

    struct ScratchCard {
        explicit ScratchCard(const std::string &str);

        /// Returns the # of points this card is worth
        /// : The first match makes the card worth one point and each match after the first doubles the point value of that card.
        [[nodiscard]] int points() const;

        /// Returns the # of winning numbers on this card
        [[nodiscard]] int winning_count() const;

        int id;
        std::set<int> card_numbers;
        std::set<int> winning_numbers;
    };

} // day04

#endif //ADVENT_OF_CODE_2023_SCRATCHCARD_H
