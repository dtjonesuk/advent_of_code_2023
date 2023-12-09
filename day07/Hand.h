//
// Created by David on 07/12/2023.
//

#ifndef ADVENT_OF_CODE_2023_HAND_H
#define ADVENT_OF_CODE_2023_HAND_H

#include "../advent.h"
#include <stdexcept>

namespace day07 {

    enum HandType {
        HighCard = 0,
        OnePair,
        TwoPair,
        ThreeOfAKind,
        FullHouse,
        FourOfAKind,
        FiveOfAKind
    };

    template <typename Base>
    class Hand {
    public:
        Hand(std::string str, int bid)  : hand(std::move(str)), bid(bid) {
            if (hand.size() != 5)
                throw std::invalid_argument("Invalid hand string");
            card_values = static_cast<Base &>(*this).get_card_values();
            type = static_cast<Base &>(*this).get_type();
            values = static_cast<Base &>(*this).get_values();
        }

        bool operator<(const Hand &other) {
            if (other.type == type) {
                return values < other.values;
            } else
                return type < other.type;
        }

        std::string hand;
        int bid;
        HandType type;
        std::vector<unsigned> values;


    protected:
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
        std::map<char, int> card_values;
    };

    std::string to_string(HandType hand_type);
} // day07

#endif //ADVENT_OF_CODE_2023_HAND_H
