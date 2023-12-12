//
// Created by David on 12/12/2023.
//

#ifndef ADVENT_OF_CODE_2023_UNIVERSE_H
#define ADVENT_OF_CODE_2023_UNIVERSE_H

#include <map>
#include <vector>
#include <algorithm>
#include <stdint.h>
#include "Galaxy.h"

namespace day11 {

    struct Universe {
       void parse(const std::vector<std::string> &lines) {
            height = static_cast<int>(lines.size());
            width = static_cast<int>(lines[0].size());

            empty_rows.resize(height, false);
            empty_cols.resize(width, false);

            // go through the rows, enlarging distance whenever we have a blank row
            for (int row = 0; row < height; ++row) {
                const std::string &line = lines[row];
                if (std::all_of(line.begin(), line.end(), [&](char c) { return c == '.'; })) {
                    empty_rows[row] = true;
                }
            }

            // go through the columns, enlarging column distance whenever we have a blank col
            for (size_t col = 0; col < width; ++col) {
                if (std::all_of(lines.begin(), lines.end(), [&](auto line) { return line[col] == '.'; })) {
                    empty_cols[col] = true;
                }
            }

            // scan the universe for galaxies
            for (int line = 0; line < lines.size(); ++line) {
                for (int col = 0; col < lines[line].size(); ++col) {
                    if (lines[line][col] == '#')
                        galaxies.emplace_back(col, line);
                }
            }
        }

        std::vector<std::pair<Galaxy, Galaxy>> find_galaxy_pairs() const {
            std::vector<std::pair<Galaxy, Galaxy>> pairs;

            for (int i = 0; i < galaxies.size() - 1; ++i) {
                for (int j = i + 1; j < galaxies.size(); ++j) {
                    pairs.emplace_back(galaxies[i], galaxies[j]);
                }
            }

            return pairs;
        }

        /// calculate the distance between a pair of galaxies
        /// expands the universe according to the expand parameter
        /// default is to double the size of blank rows/cols
        int64_t distance_between(const Galaxy &a, const Galaxy &b, int expand = 2) const {
            int64_t distance = 0;
            for (int x = std::min(a.x, b.x); x < std::max(a.x, b.x); x++) {
                distance += empty_cols.at(x) ? expand : 1;
            }
            for (int y = std::min(a.y, b.y); y < std::max(a.y, b.y); y++) {
                distance += empty_rows.at(y) ? expand : 1;
            }
            return distance;
        }

        int64_t distance_between(const std::pair<Galaxy, Galaxy> pair, int expand = 2) const {
           return distance_between(pair.first, pair.second, expand);
       }

        std::vector<Galaxy> galaxies;
        std::vector<bool> empty_rows;
        std::vector<bool> empty_cols;
        int height;
        int width;
    };

} // day11

#endif //ADVENT_OF_CODE_2023_UNIVERSE_H
