//
// Created by David on 05/12/2023.
//

#ifndef ADVENT_OF_CODE_2023_MAP_H
#define ADVENT_OF_CODE_2023_MAP_H

#include <string>
#include <stdexcept>
#include <set>
#include <map>
#include <vector>
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
                return (source + length - 1) < other.source;
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
            auto lower = ranges.lower_bound({value});

            // if not found
            if (lower == ranges.end())
                return value;

            // else if nearest range contains value
            if (lower->contains(value)) {
                value = lower->map(value);
                return value;
            }

            // else
            return value;
        }

        std::vector<std::pair<T, T>> convert_range(std::pair<T,T> range) const {
            std::vector<std::pair<T, T>> output;

            T top = range.first;
            while (true) {
                auto lower = ranges.lower_bound({top});
                if (lower == ranges.end()) {
                    // no range found
                    return output;
                }


                T bottom = std::max(range.first, lower->source);
                if (lower->contains(bottom)) {
                    if (lower->contains(range.second)) {
                        // complete range contained
                        top = range.second;
                    } else {
                        // disjoint range
                        top = lower->source + lower->length - 1;
                        //output.emplace_back(convert(bottom), convert(lower->source + lower->length - 1));
                    }
                    output.emplace_back(convert(bottom), convert(top));
                } else {
                    return output;
                }
            }
        }

        const std::string from;
        const std::string to;
        std::set<Range<T>> ranges;
    };

} // day05

#endif //ADVENT_OF_CODE_2023_MAP_H
