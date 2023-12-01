#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

namespace day## {
/// Change this to the current day
    static const std::string day = "##";

    struct PuzzleInput {
        PuzzleInput(const std::string &filename) {
            std::ifstream istream(filename);
            std::string line;

            while (std::getline(istream, line)) {
                // do something
            }
        }

    };

    void test(const std::string &filename) {
        assert(true);
    }

    int partOne(const std::string &filename) {
        PuzzleInput input(filename);
        int result = 0;

        return result;
    }

    int partTwo(const std::string &filename) {
        PuzzleInput input(filename);
        int result = 0;

        return result;

    }

    void run() {
        const std::string inputFilename = "..\\day" + day + "\\input.txt";

        test(inputFilename);

        std::cout << "Day " << day << ": Part One = " << partOne(inputFilename) << std::endl;

        std::cout << "Day " << day << ": Part Two = " << partTwo(inputFilename) << std::endl;
    }
}

int main() {
    day##::run();
}