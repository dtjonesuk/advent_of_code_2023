//
// Created by David on 03/12/2023.
//

#include "Schematic.h"

namespace day03 {
    std::map<Location, std::vector<int>> Schematic::find_gears() const {
        std::regex re{"\\d+"};
        std::map<Location, std::vector<int>> gears;

        int y = 0;
        for (auto &line: lines) {
            for (auto i = std::sregex_iterator{line.begin(), line.end(), re};
                 i != std::sregex_iterator{};
                 ++i) {
                Range rng{{static_cast<int>(i->position()), y}, static_cast<int>(i->length())};
                auto [success, gear] = has_adjacent_gear(rng);
                if (success) {
                    int ratio = std::stoi(i->str(0));
                    gears[gear].emplace_back(ratio);
                }
            }
            ++y;
        };
        return gears;
    }

    std::vector<int> Schematic::find_part_numbers() const {
        std::vector<int> parts;
        std::regex re{"\\d+"};
        int y = 0;
        for (auto &line: lines) {
            for (auto i = std::sregex_iterator{line.begin(), line.end(), re};
                 i != std::sregex_iterator{};
                 ++i) {
                Range rng{{static_cast<int>(i->position()), y}, static_cast<int>(i->length())};
                if (has_adjacent_symbol(rng)) {
                    parts.emplace_back(std::stoi(i->str(0)));
                }
            }
            ++y;
        };
        return parts;
    }

    std::pair<bool, Location> Schematic::has_adjacent_gear(Range rng) const {
        std::regex re{"\\*"};
        auto neighbours = find_neighbours(rng);
        for (Range& r : neighbours) {
            std::smatch m;
            if (std::regex_search(lines[r.from.y].begin() + r.from.x,
                                  lines[r.from.y].begin() + r.from.x + r.length,
                                  m, re)) {
                // gear found
                Location gear{r.from.x + static_cast<int>(m.position()), r.from.y};
                return {true, gear};
            }
        }
        return {false, {}};
    }

    bool Schematic::has_adjacent_symbol(Range rng) const {
        std::regex re{"[^\\d\\.]"};
        auto neighbours = find_neighbours(rng);
        return std::any_of(neighbours.begin(), neighbours.end(), [&](Range r) {
            std::smatch m;
            return std::regex_search(lines[r.from.y].begin() + r.from.x,
                                     lines[r.from.y].begin() + r.from.x + r.length,
                                     m, re);
        });
    }

    std::vector<Range> Schematic::find_neighbours(const Range &rng) const {
        int max_x = static_cast<int>(lines[0].size());
        int max_y = static_cast<int>(lines.size());

        std::vector<Range> ranges;

        // line above
        if ((rng.from.y > 0)) {
            Location from{std::max(0, rng.from.x - 1), rng.from.y - 1};
            int length = (rng.from.x == 0 ? 0 : 1) + rng.length + ((rng.from.x + rng.length) == max_x ? 0 : 1);
            ranges.emplace_back(from, length);
        }
        // line below
        if (rng.from.y < (max_y - 1)) {
            Location from{std::max(0, rng.from.x - 1), rng.from.y + 1};
            int length = (rng.from.x == 0 ? 0 : 1) + rng.length + ((rng.from.x + rng.length) == max_x ? 0 : 1);
            ranges.emplace_back(from, length);
        }
        // cell before
        if (rng.from.x > 0)
            ranges.emplace_back(Location{rng.from.x - 1, rng.from.y}, 1);
        // cell after
        if ((rng.from.x + rng.length) < (max_x - 1))
            ranges.emplace_back(Location{rng.from.x + rng.length, rng.from.y}, 1);

        return ranges;
    }
} // day03