//
// Created by David on 04/12/2023.
//

#include "CardCounter.h"

namespace day04 {
    CardCounter::CardCounter(const std::vector<ScratchCard> &cards) : cards(cards) {}

    int CardCounter::total() {
        return std::transform_reduce(cards.begin(), cards.end(), 0, std::plus{}, [&](auto& card) {
            return calculate_total_for_card(card);
        });
    }

    int CardCounter::calculate_total_for_card(const ScratchCard &card) {
        int total = 1;
        for (int i = 1; i <= card.winning_count(); ++i) {
            int next_id = card.id + i;
            if ((next_id - 1) < cards.size()) {
                if (!card_totals.contains(next_id))
                    card_totals.emplace(next_id, calculate_total_for_card(cards[next_id - 1]));
                total += card_totals[next_id];
            }
        }
        return total;
    }
} // day04