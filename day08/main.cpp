#include "../advent.h"
#include "Network.h"

namespace day08 {
    /// Change this to the current day
    static const std::string day = "08";
    static const std::string inputFilename = "..\\day" + day + "\\input.txt";
    static const std::string testFilename = "..\\day" + day + "\\test.txt";

    struct PuzzleInput {

        Network network;

        explicit PuzzleInput(std::istream &istream) {
            std::string line;

            // read instructions;
            std::getline(istream, network.instructions);

            // read blank line;
            std::getline(istream, line);

            std::regex re("(\\w+) = \\((\\w+), (\\w+)\\)");
            while (std::getline(istream, line)) {
                // do something
                std::smatch m;
                if (std::regex_match(line, m, re)) {
                    network.nodes.insert({m.str(1), {m.str(2), m.str(3)}});
                }
            }
        }

    };


    /// Unit Test
    void test() {
        std::ifstream istream(testFilename);
        PuzzleInput input(istream);
        assert(input.network.instructions == "LLR");
        assert(input.network.nodes.size() == 3);
        assert(input.network.steps_required("AAA", "ZZZ") == 6);
    }

    /// Part One Solution
    int64_t partOne() {
        using namespace std::views;

        std::ifstream istream(inputFilename);
        PuzzleInput input(istream);

        return input.network.steps_required("AAA", "ZZZ");
    }

    /// Part Two Solution
    int64_t partTwo() {
        using namespace std::views;

        std::ifstream istream(inputFilename);
        PuzzleInput input(istream);

        // this is a cheat: we need to find the length of the repeat for each ghost
        // we assume the length of repeat is the distance to the first 'xxZ'
        // we assume we don't start in the middle of any sequence
        std::vector<int64_t> repeats;
        for (auto &node: input.network.nodes) {
            if (node.first.back() == 'A') {
                int repeat = input.network.steps_required(node.first, 'Z');
                repeats.push_back(repeat);
            }
        }

        // find the lowest common multiple of the set of repeating nodes using C++17 std::lcm
        // this will be the first time the sequences align and all the ghosts are at 'xxZ'
        return std::reduce(repeats.begin() + 1, repeats.end(), repeats[0],
                           [](auto lcm, auto n) { return std::lcm(lcm, n); });
    }

}

int main() {
    using namespace day08;
    test();
    advent::run<int64_t>(day, "One", partOne);
    advent::run<int64_t>(day, "Two", partTwo);
}