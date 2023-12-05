#include "../advent.h"

namespace day05 {
    /// Change this to the current day
    static const std::string day = "05";
    static const std::string inputFilename = "..\\day" + day + "\\input.txt";
    static const std::string testFilename = "..\\day" + day + "\\test.txt";

    struct PuzzleInput {
        std::vector<std::string> lines;

        explicit PuzzleInput(const std::string &filename) {
            std::ifstream istream(filename);
            std::string line;

            while (std::getline(istream, line)) {
                // do something
                lines.emplace_back(std::move(line));
            }
        }

    };

    /// Unit Test
    void test() {
        PuzzleInput input(testFilename);
        assert(true);
    }

    /// Part One Solution
    int partOne() {
        using namespace std::views;

        PuzzleInput input(inputFilename);

        return 0;
    }


    /// Part Two Solution
    int partTwo() {
        using namespace std::views;

        PuzzleInput input(inputFilename);

        return 0;
    }

}

int main() {
    using namespace day05;
    test();
    advent::run<int>(day, "One", partOne);
    advent::run<int>(day, "Two", partTwo);
}