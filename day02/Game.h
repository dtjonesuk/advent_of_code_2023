//
// Created by David on 02/12/2023.
//

#ifndef ADVENT_OF_CODE_2023_GAME_H
#define ADVENT_OF_CODE_2023_GAME_H

#include <map>
#include <vector>
#include <string>

namespace day02 {
    typedef std::map<std::string, int> Round;

    struct Game {
        bool is_possible(Round &available);
        Round minimum_required();

        int id;
        std::vector<Round> rounds;
    };
} // day02

#endif //ADVENT_OF_CODE_2023_GAME_H
