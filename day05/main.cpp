#include "../advent.h"
#include "Map.h"
#include <set>

namespace day05 {
    /// Change this to the current day
    static const std::string day = "05";
    static const std::string inputFilename = "..\\day" + day + "\\input.txt";
    static const std::string testFilename = "..\\day" + day + "\\test.txt";

    struct PuzzleInput {
        std::map<std::string, Map<long long>> maps;
        std::vector<long long> seeds;
        std::vector<std::pair<long long, long long>> seed_ranges;

        explicit PuzzleInput(const std::string &filename) {
            std::ifstream istream(filename);
            std::string line;

            if (!istream.is_open())
                return;

            /// read seeds
            std::getline(istream, line, ' ');

            if (line != "seeds:") {
                throw std::invalid_argument("Invalid input stream");
            }
            long long seed1, seed2;
            while (istream >> seed1 >> seed2) {
                seeds.emplace_back(seed1);
                seeds.emplace_back(seed2);
                seed_ranges.emplace_back(seed1, seed2);
            }
            // skip empty line
            istream.clear();

            /// read maps
            while (std::getline(istream, line)) {


                std::smatch m;
                std::regex map_re{"(\\w+)-to-(\\w+) map:"};
                std::regex range_re{"(\\d+)\\s+(\\d+)\\s+(\\d+)"};

                if (!std::regex_match(line, m, map_re))
                    throw std::invalid_argument("Invalid input stream");
                Map map = Map<long long>(m.str(1), m.str(2));

                while (std::getline(istream, line)) {
                    if (!std::regex_search(line, m, range_re))
                        break;
                    long long dst = stoll(m.str(1));
                    long long src = stoll(m.str(2));
                    long long length = stoll(m.str(3));
                    map.ranges.emplace(src, dst, length);
                }

                maps.emplace(map.from, map);
            }
        }
    };

    template<typename T>
    std::vector<T> find_locations(const std::vector<T> seeds, const std::map<std::string, Map<T>> maps) {
        std::vector<T> items(seeds.begin(), seeds.end());
        std::string current = "seed";

        while (maps.contains(current)) {
            const Map<T> &map = maps.at(current);
            for (T &item: items) {
                item = map.convert(item);
            }

            current = map.to;
        }
        return items;
    }

    template<typename T>
    T find_locations(std::vector<std::pair<T, T>> seed_ranges, const std::map<std::string, Map<T>> maps) {
        T lowest = INT64_MAX;
        Map<T> final_map("seed", "location");
        final_map.ranges = maps.at("seed").ranges;


        std::string current = "seed";
        std::vector<std::pair<T, T>> ranges = seed_ranges;
        while (maps.contains(current)) {
            const Map<T> &map = maps.at(current);
            std::vector<std::pair<T, T>> converted_ranges;
            for (std::pair<T,T> range : ranges) {
                std::vector<std::pair<T, T>> temp = map.convert_range(range);
                std::move(temp.begin(), temp.end(), std::back_inserter(converted_ranges));
            }

            current = map.to;
            ranges = converted_ranges
        }

//            for (T n = seed_range.first; n < (seed_range.first + seed_range.second); ++n) {
//                T item = final_map.convert(n);
//                lowest = std::min(lowest, item);
//            }




        return lowest;
    }

    /// Unit Test
    void test() {
        PuzzleInput input(testFilename);

        assert(input.seeds.size() == 4);
        assert(input.maps.size() == 7);

        {
            std::vector correct = {82, 43, 86, 35};
            std::vector locations = find_locations(input.seeds, input.maps);
            assert(std::equal(locations.begin(), locations.end(), correct.begin()));
        }
        {
            assert(find_locations(input.seed_ranges, input.maps) == 46);
        }
    }

    /// Part One Solution
    long long partOne() {
        using namespace std::views;

        PuzzleInput input(inputFilename);

        std::vector locations = find_locations(input.seeds, input.maps);

        return *std::min_element(locations.begin(), locations.end());
    }


    /// Part Two Solution
    long long partTwo() {
        using namespace std::views;

        PuzzleInput input(inputFilename);
        long long location = find_locations(input.seed_ranges, input.maps);

        return location;
    }

}

int main() {
    using namespace day05;
    test();
    advent::run<long long>(day, "One", partOne);
    advent::run<long long>(day, "Two", partTwo);
}