#include "../advent.h"

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

        const std::regex re("(one|two|three|four|five|six|seven|eight|nine)");
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

        std::string output = line;

        // uses regular expression to find occurrences of number words and replace with digit
        for (auto i = std::sregex_iterator(output.begin(), output.end(), re);
             i != std::sregex_iterator();
             ++i) {
            const std::smatch &m = *i;
            output[m.position()] = replacements.at(m.str(1));
        }
/*
        // incrementally scans through the string attempting to match any of the replacement words
        for (auto search = output.begin(); search != output.end(); ++search) {
            for (auto &[str, replace]: replacements) {
                const auto temp = std::string_view(search, output.end());
                if (temp.starts_with(str))
                    *search = replace;
            }
        }
*/
        return output;
    }

    /// Unit Test
    void test() {
        assert(sumFirstLast("1abc2") == 12);
        assert(sumFirstLast("pqr3stu8vwx") == 38);
        assert(sumFirstLast("a1b2c3d4e5f") == 15);
        assert(sumFirstLast("treb7uchet") == 77);

        assert(sumFirstLast(convertWordsToDigits("two1nine")) == 29);
        assert(sumFirstLast(convertWordsToDigits("eightwothree")) == 83);
        assert(sumFirstLast(convertWordsToDigits("abcone2threexyz")) == 13);
        assert(sumFirstLast(convertWordsToDigits("xtwone3four")) == 24);
        assert(sumFirstLast(convertWordsToDigits("4nineeightseven2")) == 42);
        assert(sumFirstLast(convertWordsToDigits("zoneight234")) == 14);
        assert(sumFirstLast(convertWordsToDigits("7pqrstsixteen")) == 76);
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

    void run() {
        test();

        {
            std::cout << std::fixed << std::setprecision(3);
            auto [seconds, result] = advent::eval<int>(&partOne);

            std::cout << "Day " << day << ": Part One = " << result << "\t (completed in " << seconds << "s).\n";
        }
        {
            std::cout << std::fixed << std::setprecision(3);
            auto [seconds, result] = advent::eval<int>(&partTwo);

            std::cout << "Day " << day << ": Part One = " << result << "\t (completed in " << seconds << "s).\n";
        }
    }
}

int main() {
    day01::run();
}