#include "../advent.h"
#include "Schematic.h"

namespace day03 {
    /// Change this to the current day
    static const std::string day = "03";
    static const std::string inputFilename = "..\\day" + day + "\\input.txt";
    static const std::string testFilename = "..\\day" + day + "\\test.txt";

    struct PuzzleInput {
        Schematic schematic;

        explicit PuzzleInput(const std::string &filename) {
            std::ifstream istream(filename);
            std::string line;

            while (std::getline(istream, line)) {
                // do something
                schematic.lines.emplace_back(std::move(line));
            }
        }

    };


    /// Unit Test
    void test() {
        using namespace std::views;
        PuzzleInput input(testFilename);
        auto part_numbers = input.schematic.find_part_numbers();
        assert( std::reduce(part_numbers.begin(), part_numbers.end()) == 4361);

        auto gears = input.schematic.find_gears()
                | filter([](auto &item) { return item.second.size() == 2; })
                | transform([](auto &item) { return item.second[0] * item.second[1]; });

        assert(std::reduce(gears.begin(), gears.end()) == 467835);
    }

    /// Part One Solution
    int64_t partOne() {
        using namespace std::views;

        PuzzleInput input(inputFilename);
        auto part_numbers = input.schematic.find_part_numbers();
        return std::reduce(part_numbers.begin(), part_numbers.end());
    }


    /// Part Two Solution
    int64_t partTwo() {
        using namespace std::views;

        PuzzleInput input(inputFilename);
        auto gears = input.schematic.find_gears()
                     | filter([](auto &item) { return item.second.size() == 2; })               // only gears with 2 ratios
                     | transform([](auto &item) { return item.second[0] * item.second[1]; });   // multiply ratios
        return std::reduce(gears.begin(), gears.end());                                         // return sum
    }
}

int main() {
    using namespace day03;
    test();
    advent::run<int64_t>(day, "One", partOne);
    advent::run<int64_t>(day, "Two", partTwo);
}