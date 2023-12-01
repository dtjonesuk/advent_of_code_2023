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

namespace day01 {
    /// Change this to the current day
    static const std::string day = "01";
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

    /// sumFirstLast
    /// gets the first and last digits in a string and returns a two-digit number
    int sumFirstLast(const std::string &line) {
        using namespace std::views;

        auto digits = filter(line, isdigit);
        int first = digits.front() - '0';
        int last = reverse(digits).front() - '0';

        return (first * 10) + last;
    }

    /// convertWordsToDigits
    /// replaces number words with digits using a naive string search algorithm
    std::string convertWordsToDigits(const std::string &line) {
        std::string output = line;
        static const std::map<std::string, char> replacements =
                {{"one",   '1'},
                 {"two",   '2'},
                 {"three", '3'},
                 {"four",  '4'},
                 {"five",  '5'},
                 {"six",   '6'},
                 {"seven", '7'},
                 {"eight", '8'},
                 {"nine",  '9'}
                };

        // incrementally scans through the string attempting to match any of the replacement words
        for (auto search = output.begin(); search != output.end(); ++search) {
            for (auto &[str, replace]: replacements) {
                const auto temp = std::string_view(search, output.end());
                if (temp.starts_with(str))
                    *search = replace;
            }
        }

        return output;
    }

    /// Unit Test
    void test() {
        assert(true);
    }

    /// Part One Solution
    int partOne() {
        using namespace std::views;

        PuzzleInput input(inputFilename);

        // get first + last values of each "calibration value"
        auto values = input.lines | transform(sumFirstLast);

        // puzzle answer is sum of all calibration values
        // fold (reduce) using plus
        int result = std::ranges::fold_left(values, 0, std::plus{});

        return result;
    }


    /// Part Two Solution
    int partTwo() {
        using namespace std::views;

        PuzzleInput input(inputFilename);

        // convert words to their digit counterparts
        // get first + last values of each "calibration value"
        auto values = input.lines | transform(convertWordsToDigits) | transform(sumFirstLast);

        // puzzle answer is sum of all calibration values
        // fold (reduce) using plus
        int result = std::ranges::fold_left(values, 0, std::plus{});

        return result;
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
    day01::run();
}