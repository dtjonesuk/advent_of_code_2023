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

        int steps_required(const std::string &starting_node, const std::string &ending_node) {
            // avoid copying by storing a pointer to the string
            const std::string *current_node = &starting_node;
            auto current_instruction = instructions.begin();
            int steps = 0;

            while (*current_node != ending_node) {
                // take first if left node, second otherwise
                if (*current_instruction == 'L')
                    current_node = &(nodes[*current_node].first);
                else
                    current_node = &(nodes[*current_node].second);

                // increment steps
                steps++;

                // next instruction
                current_instruction++;
                // wrap around at end of instructions
                if (current_instruction == instructions.end())
                    current_instruction = instructions.begin();
            }
            return steps;
        }

        int steps_required(const std::string &starting_node, char ending_node_char) {
            // avoid copying by storing a pointer to the string
            const std::string *current_node = &starting_node;
            auto current_instruction = instructions.begin();
            int steps = 0;

            while (current_node->back() != ending_node_char) {
                // take first if left node, second otherwise
                if (*current_instruction == 'L')
                    current_node = &(nodes[*current_node].first);
                else
                    current_node = &(nodes[*current_node].second);

                // increment steps
                steps++;

                // next instruction
                current_instruction++;
                // wrap around at end of instructions
                if (current_instruction == instructions.end())
                    current_instruction = instructions.begin();
            }
            return steps;
        }

    };
} // day08

#endif //ADVENT_OF_CODE_2023_NETWORK_H
