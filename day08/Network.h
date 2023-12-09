//
// Created by David on 08/12/2023.
//

#ifndef ADVENT_OF_CODE_2023_NETWORK_H
#define ADVENT_OF_CODE_2023_NETWORK_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ranges>
#include <algorithm>

namespace day08 {

    struct Network {
        std::string instructions;
        std::map<std::string, std::pair<std::string, std::string>> nodes;

        /// Part One - returns steps required to reach ending_node
        int steps_required(const std::string &starting_node, const std::string &ending_node);

        /// Part Two - returns steps required to reach any node ending with ending_node_char
        int steps_required(const std::string &starting_node, char ending_node_char);

    };
} // day08

#endif //ADVENT_OF_CODE_2023_NETWORK_H
