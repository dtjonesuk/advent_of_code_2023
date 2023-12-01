#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <ranges>
#include <chrono>

namespace day02 {
    /// Change this to the current day
    static const std::string day = "02";
    static const std::string inputFilename = "..\\day" + day + "\\input.txt";

    struct PuzzleInput {
        std::vector<std::string> lines;

        explicit PuzzleInput(const std::string &filename) {
            std::ifstream istream(filename);
            std::string line;

            while (std::getline(istream, line)) {
                // do something
                lines.push_back(line);
            }
        }

    };

    /// Unit Test
    void test() {
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


    /// Benchmarks a callable
    template<typename T>
    std::pair<double, T> eval(std::function<T()> func) {
        const auto t1 = std::chrono::high_resolution_clock::now();
        T result = func();
        const auto t2 = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> seconds = t2 - t1;

        return std::make_pair(seconds.count(), result);
    }

    void run() {
        test();

        {
            std::cout << std::fixed << std::setprecision(3);
            auto [seconds, result] = eval<int>(&partOne);

            std::cout << "Day " << day << ": Part One = " << result << "\t (completed in " << seconds << "s).\n";
        }
        {
            std::cout << std::fixed << std::setprecision(3);
            auto [seconds, result] = eval<int>(&partTwo);

            std::cout << "Day " << day << ": Part One = " << result << "\t (completed in " << seconds << "s).\n";
        }
    }
}

int main() {
    day02::run();
}