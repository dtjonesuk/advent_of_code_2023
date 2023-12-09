//
// Created by David on 09/12/2023.
//

#include "HandPartOne.h"

namespace day07 {
    HandType HandPartOne::get_type() const {
        std::vector<unsigned> buckets(13, 0);

        // first count cards
        for (char ch: hand) {
            int card = card_values.at(ch);
            buckets[card]++;
        }

        // sort buckets by highest
        std::sort(buckets.begin(), buckets.end(), std::greater{});

        return from_buckets(buckets);
    }

    std::vector<unsigned> HandPartOne::get_values() const {
        std::vector<unsigned> v(5);
        std::transform(hand.begin(), hand.end(), v.begin(), [&](char card) {
            return card_values.at(card);
        });
        return v;
    }

    std::map<char, int> HandPartOne::get_card_values() const {
        return {
                { 'A', 12 },
                { 'K', 11 },
                { 'Q', 10 },
                { 'J', 9 },
                { 'T', 8 },
                { '9', 7 },
                { '8', 6 },
                { '7', 5 },
                { '6', 4 },
                { '5', 3 },
                { '4', 2 },
                { '3', 1 },
                { '2', 0 },
        };
    }
} // day07