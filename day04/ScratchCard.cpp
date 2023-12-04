//
// Created by David on 04/12/2023.
//

#include "ScratchCard.h"

namespace day04 {
    ScratchCard::ScratchCard(const std::string &str) {
        std::regex re{"Card\\s+(\\d+):((?:\\s+\\d+)+)\\s\\|((?:\\s+\\d+)+)"};
        std::smatch m;
        if (std::regex_match(str, m, re)) {
            // card #
            id = stoi(m.str(1));

            // winning numbers
            std::regex number_re{"\\d+"};
            std::string numbers = m.str(2);
            for (auto n = std::sregex_iterator{numbers.begin(), numbers.end(), number_re};
                 n != std::sregex_iterator{};
                 ++n) {
                winning_numbers.emplace(stoi(n->str(0)));
            }

            // card numbers
            numbers = m.str(3);
            for (auto n = std::sregex_iterator{numbers.begin(), numbers.end(), number_re};
                 n != std::sregex_iterator{};
                 ++n) {
                card_numbers.emplace(stoi(n->str(0)));
            }
        } else
            throw std::invalid_argument("Bad scratch card input");
    }

    int ScratchCard::points() const {
        int points = 0;
        for (int card_number : card_numbers) {
            if (winning_numbers.contains(card_number)) {
                if (points == 0)
                    points = 1;
                else
                    points *= 2;
            }
        }
        return points;
    }

    int ScratchCard::winning_count() const {
        return static_cast<int>(std::count_if(card_numbers.begin(), card_numbers.end(), [&](int n) {
            return winning_numbers.contains(n);
        }));
    }
} // day04