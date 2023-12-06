#include "../advent.h"

namespace day06 {
    /// Change this to the current day
    static const std::string day = "06";
    static const std::string inputFilename = "..\\day" + day + "\\input.txt";
    static const std::string testFilename = "..\\day" + day + "\\test.txt";

    struct PuzzleInput {
        std::vector<int> times;
        std::vector<int> distances;
        size_t count;

        explicit PuzzleInput(const std::string &filename) {
            std::ifstream istream(filename);
            std::string line;

            while (std::getline(istream, line)) {
                std::istringstream iss(line);
                int num;
                std::string field;
                iss >> field;
                if (field == "Time:") {
                    while (iss >> num) {
                        times.emplace_back(num);
                    }
                } else if (field == "Distance:") {
                    while (iss >> num) {
                        distances.emplace_back(num);
                    }
                }
            }

            if (times.size() != distances.size())
                throw std::invalid_argument("Bad input stream!");

            count = times.size();
        }
    };

    uint64_t count_ways_to_win(uint64_t time, uint64_t distance) {
        uint64_t ways = 0;
        for (int speed = 0; speed <= time; ++speed) {
            uint64_t travelled = (time - speed) * speed;
            if (travelled > distance)
                ++ways;
                // optimization: once we are no longer winning we can stop the loop
            else if (ways > 0)
                break;
        }
        return ways;
    }

    uint64_t get_number(std::vector<int> &numbers) {
        auto func = [](uint64_t total, int n) {
            int digits = int(log10(n) + 1);
            int k = int(pow(10, digits));
            return (total * k) + n;
        };
        return std::reduce(numbers.begin(), numbers.end(), 0ULL, func);
    }

    /// Unit Test
    void test() {
        PuzzleInput input(testFilename);

        assert(input.times.size() == 3);
        assert(input.distances.size() == 3);

        std::vector<int> correct = {4, 8, 9};
        for (int n = 0; n < input.count; ++n) {
            assert(count_ways_to_win(input.times[n], input.distances[n]) == correct[n]);
        }

        assert(get_number(input.times) == 71530);
        assert(get_number(input.distances) == 940200);
    }

    /// Part One Solution
    uint64_t partOne() {
        using namespace std::views;

        PuzzleInput input(inputFilename);

        // count the ways to win for all the input variables...
        auto result = iota(size_t(0), input.count) |
                      transform([&](size_t n) {
                          return count_ways_to_win(input.times[n], input.distances[n]);
                      });

        // ...and return the product of them
        return std::reduce(result.begin(), result.end(), 1ULL, std::multiplies{});
    }


    /// Part Two Solution
    uint64_t partTwo() {
        using namespace std::views;

        PuzzleInput input(inputFilename);

        // get the concatenation of the input numbers...
        uint64_t time = get_number(input.times);
        uint64_t distance = get_number(input.distances);

        // ... and return the number of ways to win
        return count_ways_to_win(time, distance);
    }

}

int main() {
    using namespace day06;
    test();
    advent::run<uint64_t>(day, "One", partOne);
    advent::run<uint64_t>(day, "Two", partTwo);
}