#include "../advent.h"
#include <deque>
#include "ScratchCard.h"
#include "CardCounter.h"

namespace day04 {
    /// Change this to the current day
    static const std::string day = "04";
    static const std::string inputFilename = "..\\day" + day + "\\input.txt";
    static const std::string testFilename = "..\\day" + day + "\\test.txt";

    struct PuzzleInput {
        std::vector<ScratchCard> cards;

        explicit PuzzleInput(const std::string &filename) {
            std::ifstream istream(filename);
            std::string line;

            while (std::getline(istream, line)) {
                // do something
                cards.emplace_back(line);
            }
        }

    };

    int sum_card_points(const std::vector<ScratchCard> &cards) {
        using namespace std::views;
        auto result = cards | transform(&ScratchCard::points);
        return std::reduce(result.begin(), result.end());
    }

    /// Unit Test
    void test() {
        PuzzleInput input(testFilename);

        assert(input.cards.size() == 6);
        assert(sum_card_points(input.cards) == 13);

        CardCounter counter(input.cards);
        assert(counter.total() == 30);
    }

    /// Part One Solution
    int64_t partOne() {
        using namespace std::views;

        PuzzleInput input(inputFilename);

        return sum_card_points(input.cards);
    }


    /// Part Two Solution
    int64_t partTwo() {
        using namespace std::views;

        PuzzleInput input(inputFilename);
        CardCounter counter(input.cards);

        return counter.total();
    }
}

int main() {
    using namespace day04;
    test();
    advent::run<int64_t>(day, "One", partOne);
    advent::run<int64_t>(day, "Two", partTwo);
}