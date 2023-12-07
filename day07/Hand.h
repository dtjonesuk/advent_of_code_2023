//
// Created by David on 07/12/2023.
//

#ifndef ADVENT_OF_CODE_2023_HAND_H
#define ADVENT_OF_CODE_2023_HAND_H

#include "../advent.h"
#include <stdexcept>

namespace day07 {

    class Hand {
    public:
        enum HandType {
            HighCard = 0,
            OnePair,
            TwoPair,
            ThreeOfAKind,
            FullHouse,
            FourOfAKind,
            FiveOfAKind
        };

        Hand(std::string str, int bid) : hand(std::move(str)), bid(bid) {
            if (hand.size() != 5)
                throw std::invalid_argument("Invalid hand string");
            type = get_type();
            values = get_values();
        }

        virtual ~Hand() = default;

        bool operator<(const Hand &other) {
            if (other.type == type) {
                return values < other.values;
            } else
                return type < other.type;
        }

        bool operator>(const Hand &other) {
            if (other.type == type) {
                return values > other.values;
            } else
                return type > other.type;
        }

        std::string hand;
        int bid;
        HandType type;
        std::vector<unsigned> values;


    protected:
        [[nodiscard]] HandType get_type() const {
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

        static HandType from_buckets(std::vector<unsigned> &buckets) {
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

        [[nodiscard]] std::vector<unsigned> get_values() const {
            std::vector<unsigned> v(5);
            std::transform(hand.begin(), hand.end(), v.begin(), [&](char card) {
                return card_values.at(card);
            });
            return v;
        }

        std::map<char, int> card_values{
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
    };

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

#endif //ADVENT_OF_CODE_2023_HAND_H
