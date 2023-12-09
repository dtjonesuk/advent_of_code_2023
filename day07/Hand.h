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

        Hand(std::string str, int bid);

        virtual ~Hand() = default;

        bool operator<(const Hand &other);

//        bool operator>(const Hand &other) {
//            if (other.type == type) {
//                return values > other.values;
//            } else
//                return type > other.type;
//        }

        std::string hand;
        int bid;
        HandType type;
        std::vector<unsigned> values;


    protected:
        // Calculates the type of hand we have
        [[nodiscard]] HandType get_type() const;

        // Calculates the values of the cards
        [[nodiscard]] std::vector<unsigned> get_values() const;

        static HandType from_buckets(std::vector<unsigned> &buckets);

        std::map<char, int> card_values;
    };

    std::string to_string(Hand::HandType hand_type);
} // day07

#endif //ADVENT_OF_CODE_2023_HAND_H
