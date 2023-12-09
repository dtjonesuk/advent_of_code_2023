#include "../advent.h"
#include "Hand.h"
#include "HandPartTwo.h"

namespace day07 {
    /// Change this to the current day
    static const std::string day = "07";
    static const std::string inputFilename = "..\\day" + day + "\\input.txt";
    static const std::string testFilename = "..\\day" + day + "\\test.txt";

    struct PuzzleInput {
        std::vector<Hand> hands;
        std::vector<HandPartTwo> hands2;

        explicit PuzzleInput(const std::string &filename) {
            std::ifstream istream(filename);
            std::string line;

            while (std::getline(istream, line)) {
                std::istringstream iss(line);
                std::string hand;
                int bid;
                iss >> hand >> bid;
                hands.push_back({hand, bid});
                hands2.emplace_back(hand, bid);
            }
        }

    };

    template<class H>
    int total_winnings(std::vector<H> &hands) {
        using namespace std::views;

        std::sort(hands.begin(), hands.end());

        int rank = 1;
        auto result = hands | transform([&] (const H& hand) {
            return rank++ * hand.bid;
        });

        int answer = std::reduce(result.begin(), result.end());
        return answer;
    }

    /// Unit Test
    void test() {
        PuzzleInput input(testFilename);

        assert(total_winnings(input.hands) == 6440);
        assert(total_winnings(input.hands2) == 5905);
    }

    /// Part One Solution
    int64_t partOne() {
        using namespace std::views;

        PuzzleInput input(inputFilename);

        return total_winnings(input.hands);
    }


    /// Part Two Solution
    int64_t partTwo() {
        using namespace std::views;

        PuzzleInput input(inputFilename);

        return total_winnings(input.hands2);
    }

}

int main() {
    using namespace day07;
    test();
    advent::run<int64_t>(day, "One", partOne);
    advent::run<int64_t>(day, "Two", partTwo);
}