//
// Created by David on 04/12/2023.
//

#include "CardCounter.h"

namespace day04 {
    CardCounter::CardCounter(const std::vector<ScratchCard> &cards) : cards(cards) {}

    int CardCounter::total() {
        int total = 0;
        return std::transform_reduce(cards.begin(), cards.end(), 0, std::plus{}, [&](auto& card) {
            return calculate_total_for_card(card);
        });
    }

    int CardCounter::calculate_total_for_card(const ScratchCard &card) {
        int total = 1;
        for (int i = 1; i <= card.winning_count(); ++i) {
            if ((card.id + i - 1) < cards.size()) {
                if (!card_totals.contains(card.id + i))
                    card_totals.emplace(card.id + i, calculate_total_for_card(cards[card.id + i - 1]));
                total += card_totals[card.id + i];
            }
        }
        return total;
    }
} // day04