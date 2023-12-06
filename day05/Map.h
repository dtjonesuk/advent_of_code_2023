//
// Created by David on 05/12/2023.
//

#ifndef ADVENT_OF_CODE_2023_MAP_H
#define ADVENT_OF_CODE_2023_MAP_H

#include <string>
#include <stdexcept>
#include <set>
#include <map>
#include <utility>

namespace day05 {

    template<typename T>
    struct Range {
        Range(T source) : source(source), destination(0), length(0) {}

        Range(T source, T destination, T length) : source(source), destination(destination), length(length) {}

        constexpr bool contains(T other) const {
            return ((other >= source) && (other < source + length));
        }

        constexpr T map(T other) const {
            return destination - source + other;
        }

        constexpr bool operator<(const Range &other) const {
            if (other.length == 0)
                return (source + length) < other.source;
            return source < other.source;
        }

        T source;
        T destination;
        T length;
    };

    template<typename T>
    class Map {
    public:
        Map(std::string from, std::string to) : from(std::move(from)), to(std::move(to)) {}

        T convert(T value) const {
            auto [lower, upper] = ranges.equal_range({value});

            if (lower == ranges.end())
                lower = ranges.begin();
            if (lower->contains(value))
                return lower->map(value);

            if (upper == ranges.end())
                upper--;
            if (upper->contains(value))
                return upper->map(value);

            return value;

        }

        void convert_ranges(Map<T> map) {

        }

        const std::string from;
        const std::string to;
        std::set<Range<T>> ranges;
    };

} // day05

#endif //ADVENT_OF_CODE_2023_MAP_H
