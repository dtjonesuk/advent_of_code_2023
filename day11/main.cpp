#include "../advent.h"
#include "Galaxy.h"
#include "Universe.h"

namespace day11 {
    /// Change this to the current day
    static const std::string day = "11";
    static const std::string inputFilename = "..\\day" + day + "\\input.txt";
    static const std::string testFilename = "..\\day" + day + "\\test.txt";

    struct PuzzleInput {
        std::vector<std::string> lines;
        Universe universe;

        explicit PuzzleInput(std::istream &istream) {
            std::string line;

            while (std::getline(istream, line)) {
                lines.emplace_back(std::move(line));
            }

            universe.parse(lines);
        }

        void print() {
            for (auto &line: lines) {
                std::cout << line << std::endl;
            }
        }

    };


    /// calculate the distance between all pairs of galaxies
    /// expand the universe according to the expand parameter
    /// default is to double the size of blank rows/cols
    int64_t universe_distance(Universe &universe, int expand = 2) {
        using namespace std::views;

        auto pairs = universe.find_galaxy_pairs();
        auto distances = pairs | transform([&](auto pair) {
            return universe.distance_between(pair, expand);
        });

        return std::reduce(distances.begin(), distances.end(), 0LL);
    }

    /// Unit Test
    void test() {
        std::ifstream istream(testFilename);
        PuzzleInput input(istream);

        Universe &universe = input.universe;

        auto pairs = universe.find_galaxy_pairs();
        assert(pairs.size() == 36);

        assert(universe.distance_between(universe.galaxies[0], universe.galaxies[6]) == 15);
        assert(universe.distance_between(universe.galaxies[2], universe.galaxies[5]) == 17);
        assert(universe.distance_between(universe.galaxies[7], universe.galaxies[8]) == 5);

        auto total = universe_distance(universe);
        assert(total == 374);

        assert (universe_distance(universe, 10) == 1030);
        assert (universe_distance(universe, 100) == 8410);
    }

    /// Part One Solution
    int64_t partOne() {
        using namespace std::views;

        std::ifstream istream(inputFilename);
        PuzzleInput input(istream);

        Universe &universe = input.universe;
        return universe_distance(universe);
    }


    /// Part Two Solution
    int64_t partTwo() {
        using namespace std::views;

        std::ifstream istream(inputFilename);
        PuzzleInput input(istream);

        Universe &universe = input.universe;
        return universe_distance(universe, 1'000'000);
    }

}

int main() {
    using namespace day11;
    test();
    advent::run<int64_t>(day, "One", partOne);
    advent::run<int64_t>(day, "Two", partTwo);
}