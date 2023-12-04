//
// Created by David on 03/12/2023.
//

#ifndef ADVENT_OF_CODE_2023_SCHEMATIC_H
#define ADVENT_OF_CODE_2023_SCHEMATIC_H

#include <string>
#include <vector>
#include <map>
#include <regex>

namespace day03 {
    struct Location {
        int x;
        int y;

        bool operator<(const Location &other) const {
            if (x == other.x)
                return (y < other.y);
            return (x < other.x);
        }
    };

    struct Range {
        Location from;
        int length;
    };

    class Schematic {
    public:
        std::vector<std::string> lines;

        [[nodiscard]] std::vector<Range> find_neighbours(const Range &rng) const;

        [[nodiscard]] bool has_adjacent_symbol(Range rng) const;

        [[nodiscard]] std::pair<bool, Location> has_adjacent_gear(Range rng) const;

        [[nodiscard]] std::vector<int> find_part_numbers() const;

        [[nodiscard]] std::map<Location, std::vector<int>> find_gears() const;

    };

} // day03

#endif //ADVENT_OF_CODE_2023_SCHEMATIC_H
