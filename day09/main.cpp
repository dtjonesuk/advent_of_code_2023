#include "../advent.h"

namespace day09 {
    /// Change this to the current day
    static const std::string day = "09";
    static const std::string inputFilename = "..\\day" + day + "\\input.txt";
    static const std::string testFilename = "..\\day" + day + "\\test.txt";

    using History = std::vector<int64_t>;

    struct PuzzleInput {
        std::vector<History> histories;

        explicit PuzzleInput(std::istream &istream) {
            std::string line;

            while (std::getline(istream, line)) {
                // do something
                History &history = histories.emplace_back();
                std::istringstream iss(line);
                int64_t n;
                while (iss >> n)
                    history.emplace_back(n);
            }
        }
    };



    int64_t find_next(const std::vector<History> &histories) {
        if (histories.size()<3)
            throw std::invalid_argument("History must have at least 3 generations");

        // get increment from last but one generation
        int64_t increment = histories[histories.size() - 2][0];

        for (auto h = histories.crbegin() + 2; h != histories.crend(); ++h) {
            increment += h->back();
        }

        return increment;
    }

    int64_t find_prev(const std::vector<History> &histories) {
        if (histories.size()<3)
            throw std::invalid_argument("History must have at least 3 generations");

        // get increment from last but one generation
        int64_t increment = histories[histories.size() - 2][0];

        for (auto h = histories.crbegin() + 2; h != histories.crend(); ++h) {
            increment = h->front() - increment;
        }

        return increment;
    }

    History find_differences(const History &history) {
        History differences;

        for (auto it = history.cbegin() + 1; it != history.cend(); ++it) {
            differences.emplace_back(*it - *(it - 1));
        }
        return differences;
    }

    std::vector<History> finite_differences(const History &history) {
        History current = history;
        std::vector<History> differences;
        differences.push_back(current);

        // loop until all current elements are zero
        while (!std::all_of(current.begin(), current.end(), [](auto n) { return n == 0;})) {
            current = find_differences(current);
            differences.push_back(current);
        }

        return differences;
    }

    void print_differences(const std::vector<History>& differences) {
        int line = 0;
        for (const History &history : differences) {
            std::cout << std::string(line*2, ' ');
            for (auto n : history) {
                std::cout << std::left << std::setw(4) << n;
            }
            std::cout << std::endl;
            ++line;
        }
    }

    /// Unit Test
    void test() {
        std::ifstream istream(testFilename);
        PuzzleInput input(istream);
        assert(input.histories.size() == 3);

        // Part One
        {
            std::vector answers = {18, 28, 68};
            auto answer = answers.cbegin();

            for (History &history: input.histories) {
                auto differences = finite_differences(history);
                assert(find_next(differences) == *answer);
                ++answer;
            }
        }
        // Part Two
        {
            std::vector answers = {-3, 0, 5};
            auto answer = answers.cbegin();

            for (History &history: input.histories) {
                auto differences = finite_differences(history);
                assert(find_prev(differences) == *answer);
                ++answer;
            }
        }
    }

    /// Part One Solution
    int64_t partOne() {
        using namespace std::views;

        std::ifstream istream(inputFilename);
        PuzzleInput input(istream);

        auto result = input.histories | transform(finite_differences) | transform(find_next);

        return std::reduce(result.begin(), result.end());
    }


    /// Part Two Solution
    int64_t partTwo() {
        using namespace std::views;

        std::ifstream istream(inputFilename);
        PuzzleInput input(istream);

        auto result = input.histories | transform(finite_differences) | transform(find_prev);

        return std::reduce(result.begin(), result.end());
    }

}

int main() {
    using namespace day09;
    test();
    advent::run<int64_t>(day, "One", partOne);
    advent::run<int64_t>(day, "Two", partTwo);
}