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

        HandPartTwo(std::string str, int bid) : Hand(std::move(str), bid) {
            if (hand.size() != 5)
                throw std::invalid_argument("Invalid hand string");
            type = get_type();
            values = get_values();
        }

        [[nodiscard]] HandType get_type() const {
            std::vector<unsigned> buckets(13, 0);
            // first count cards
            for (char ch: hand) {
                int card = card_values.at(ch);
                buckets[card]++;
            }

            // remove the jokers
            int jokers = buckets[0];
            buckets[0] = 0;

            // sort buckets by highest
            std::sort(buckets.begin(), buckets.end(), std::greater{});

            // add the jokers to the best pile
            buckets[0] += jokers;

            return from_buckets(buckets);
        }

        [[nodiscard]] std::vector<unsigned> get_values() const {
            std::vector<unsigned> v(5);
            std::transform(hand.begin(), hand.end(), v.begin(), [&](char card) {
                return card_values.at(card);
            });
            return v;
        }


        std::map<char, unsigned> card_values{
                {'A', 12},
                {'K', 11},
                {'Q', 10},
                {'T', 9},
                {'9', 8},
                {'8', 7},
                {'7', 6},
                {'6', 5},
                {'5', 4},
                {'4', 3},
                {'3', 2},
                {'2', 1},
                {'J', 0}
        };
    };

} // day07

#endif //ADVENT_OF_CODE_2023_HAND2_H
