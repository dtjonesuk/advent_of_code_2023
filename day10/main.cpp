#include "../advent.h"
#include "Pipe.h"

namespace day10 {
    /// Change this to the current day
    static const std::string day = "10";
    static const std::string inputFilename = "..\\day" + day + "\\input.txt";
    static const std::string testFilename = "..\\day" + day + "\\test.txt";

    struct PuzzleInput {
        Schematic schematic;

        explicit PuzzleInput(std::istream &istream) : schematic(parse(istream)) {

        }

        static Schematic parse(std::istream &istream) {
            std::string line;
            std::vector<std::string> lines;
            while (std::getline(istream, line)) {
                // do something
                lines.emplace_back(std::move(line));
            }
            return Schematic(lines);
        }
    };


    /// Unit Test
    void test() {
        std::ifstream istream(testFilename);
        PuzzleInput input(istream);
        assert(true);
    }

    /// Part One Solution
    int64_t partOne() {
        using namespace std::views;

        std::ifstream istream(inputFilename);
        PuzzleInput input(istream);

        return input.schematic.length() / 2;
    }


    /// Part Two Solution
    int64_t partTwo() {
        using namespace std::views;

        std::ifstream istream(inputFilename);
        PuzzleInput input(istream);

        return 0;
    }

}

int main() {
    using namespace day10;
    test();
    advent::run<int64_t>(day, "One", partOne);
    advent::run<int64_t>(day, "Two", partTwo);
}