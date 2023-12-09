//
// Created by David on 07/12/2023.
//

#include "Hand.h"

namespace day07 {
    std::string to_string(HandType hand_type) {
        switch (hand_type) {
            case HighCard:
                return "High Card";
            case TwoPair:
                return "Two Pair";
            case OnePair:
                return "One Pair";
            case ThreeOfAKind:
                return "Three Of A Kind";
            case FullHouse:
                return "Full House";
            case FourOfAKind:
                return "Four Of A Kind";
            case FiveOfAKind:
                return "Five Of A Kind";
        }
        return "Unknown Hand Type";
    }
} // day07