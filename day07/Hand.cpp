//
// Created by David on 07/12/2023.
//

#include "Hand.h"

namespace day07 {
    Hand::Hand(std::string str, int bid) : hand(std::move(str)), bid(bid) {
        if (hand.size() != 5)
            throw std::invalid_argument("Invalid hand string");
        card_values = {
            {'A', 12},
            {'K', 11},
            {'Q', 10},
            {'J', 9},
            {'T', 8},
            {'9', 7},
            {'8', 6},
            {'7', 5},
            {'6', 4},
            {'5', 3},
            {'4', 2},
            {'3', 1},
            {'2', 0},
        };
        type = get_type();
        values = get_values();

    }

    bool Hand::operator<(const Hand &other) {
        if (other.type == type) {
            return values < other.values;
        } else
            return type < other.type;
    }

    Hand::HandType Hand::get_type() const {
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

    Hand::HandType Hand::from_buckets(std::vector<unsigned int> &buckets) {
        if (buckets[0] == 5)
            return FiveOfAKind;

        if (buckets[0] == 4)
            return FourOfAKind;

        if (buckets[0] == 3) {
            if (buckets[1] == 2)
                return FullHouse;
            else return ThreeOfAKind;
        }

        if (buckets[0] == 2) {
            if (buckets[1] == 2)
                return TwoPair;
            else
                return OnePair;
        }

        return HighCard;
    }

    std::vector<unsigned> Hand::get_values() const {
        std::vector<unsigned> v(5);
        std::transform(hand.begin(), hand.end(), v.begin(), [&](char card) {
            return card_values.at(card);
        });
        return v;
    }

    std::string to_string(Hand::HandType hand_type) {
        switch (hand_type) {
            case Hand::HighCard:
                return "High Card";
            case Hand::TwoPair:
                return "Two Pair";
            case Hand::OnePair:
                return "One Pair";
            case Hand::ThreeOfAKind:
                return "Three Of A Kind";
            case Hand::FullHouse:
                return "Full House";
            case Hand::FourOfAKind:
                return "Four Of A Kind";
            case Hand::FiveOfAKind:
                return "Five Of A Kind";
        }
        return "Unknown Hand Type";
    }
} // day07