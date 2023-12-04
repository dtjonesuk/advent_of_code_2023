#include "../advent.h"

namespace day04 {
    /// Change this to the current day
    static const std::string day = "04";
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

    void run() {
        test();

        {
            std::cout << std::fixed << std::setprecision(3);
            auto [seconds, result] = advent::eval<int>(&partOne);

            std::cout << "Day " << day << ": Part One = " << result << "\t\t (completed in " << seconds << "s).\n";
        }
        {
            std::cout << std::fixed << std::setprecision(3);
            auto [seconds, result] = advent::eval<int>(&partTwo);

            std::cout << "Day " << day << ": Part One = " << result << "\t\t (completed in " << seconds << "s).\n";
        }
    }
}

int main() {
    day04::run();
}