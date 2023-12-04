//
// Created by David on 04/12/2023.
//

#ifndef ADVENT_OF_CODE_2023_CARDCOUNTER_H
#define ADVENT_OF_CODE_2023_CARDCOUNTER_H
#include <vector>
#include <map>
#include <numeric>

#include "ScratchCard.h"

namespace day04 {

    class CardCounter {
    public:
        explicit CardCounter(const std::vector<ScratchCard> &cards);

        int total();

    private:
        /// counts the total # of cards you win from a particular card.
        /// stores the result in a map for future calcs.
        int calculate_total_for_card(const ScratchCard &card);

        const std::vector<ScratchCard> &cards;      // the original ordered list of cards
        std::map<int, int> card_totals;             // cache of total cards a card results in you winning
    };

} // day04

#endif //ADVENT_OF_CODE_2023_CARDCOUNTER_H
