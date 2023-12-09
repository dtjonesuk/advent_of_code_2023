#include "HandPartTwo.h"

namespace day07 {
    std::map<char, int> HandPartTwo::get_card_values() const {
        return {
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
    }
    HandType HandPartTwo::get_type() const {
        std::vector<unsigned> buckets(13, 0);
        // first count cards
        for (char ch: hand) {
            int card = card_values.at(ch);
            buckets[card]++;
        }

        // remove the jokers
        unsigned jokers = buckets[0];
        buckets[0] = 0;

        // sort buckets by highest
        std::sort(buckets.begin(), buckets.end(), std::greater{});

        // add the jokers to the best pile
        buckets[0] += jokers;

        return from_buckets(buckets);
    }

    std::vector<unsigned> HandPartTwo::get_values() const {
        std::vector<unsigned> v(5);
        std::transform(hand.begin(), hand.end(), v.begin(), [&](char card) {
            return card_values.at(card);
        });
        return v;
    }
}