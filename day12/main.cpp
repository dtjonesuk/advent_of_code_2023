#include "../advent.h"

namespace day12 {
    /// Change this to the current day
    static const std::string day = "12";
    static const std::string inputFilename = "..\\day" + day + "\\input.txt";
    static const std::string testFilename = "..\\day" + day + "\\test.txt";

    struct ConditionRecord {
        std::string condition;
        std::vector<int> groups;

        bool is_valid(const std::string &sample) const {
            auto current = sample.cbegin();
            auto group = groups.cbegin();
            int count = 0;
            bool in_group = false;

            do {
                if (*current == '#') {
                    count++;
                    in_group = true;
                } else if (*current == '.') {
                    if (in_group) {
                        if (group == groups.cend())
                            // sample has too many groups
                            return false;

                        if (count != *group)
                            // wrong group size
                            return false;

                        // group ok, next group
                        group++;
                    }
                    count = 0;
                    in_group = false;
                }
                current++;
            } while (current != sample.cend());
            // test final group
            if (in_group) {
                if (group == groups.cend())
                    return false;
                if (count != *group)
                    return false;
            }
            return true;
        }
    };

    struct PuzzleInput {
        std::vector<ConditionRecord> records;

        explicit PuzzleInput(std::istream &istream) {
            std::string line;

            while (std::getline(istream, line)) {
                std::stringstream ss(line);
                ConditionRecord &record = records.emplace_back();
                ss >> record.condition;
                while (std::getline(ss, line, ','))
                    record.groups.emplace_back(stoi(line));
            }
        }

    };

    // assumes size of permutation = number of ? in string
    std::string replace_unknowns(const std::string &condition, const std::vector<bool> &permutation) {
        std::string sample = condition;
        auto current = permutation.begin();
        for (char &ch: sample) {
            if (ch == '?') {
                ch = *current ? '#' : '.';
                current++;
            }
        }
        return sample;
    }

    // count the number of ?
    // generate permutations of booleans
    // replace the ?s according to booleans
    // see if it is a valid record
    int64_t find_permutations(const ConditionRecord &record) {
        int missing = std::count(record.condition.begin(), record.condition.end(), '?');
        int fixed = std::count(record.condition.begin(), record.condition.end(), '#');
        int required = std::reduce(record.groups.begin(), record.groups.end());
        int64_t total = 0;

        std::vector<bool> permutation(missing, false);
        for (int i = (required - fixed) - 1; i >= 0; --i)
            permutation[i] = true;

        do {
            std::string sample = replace_unknowns(record.condition, permutation);
            if (record.is_valid(sample)) {
                ++total;
//                std::cout << sample << std::endl;
            }
//            std::copy(permutation.begin(), permutation.end(), std::ostream_iterator<bool>(std::cout, " "));
//            std::cout << std::endl;

        } while (std::prev_permutation(permutation.begin(), permutation.end()));

        return total;
    }

    ConditionRecord unfold_record(const ConditionRecord &record) {
        std::ostringstream unfolded_condition;
        unfolded_condition << record.condition << '?' << record.condition << '?' << record.condition << '?'
                           << record.condition << '?'
                           << record.condition;

        std::vector<int> unfolded_groups(record.groups);
        for (int i = 0; i < 4; i++) {
            std::copy(record.groups.begin(), record.groups.end(), std::back_inserter(unfolded_groups));
        }

        return ConditionRecord{unfolded_condition.str(), std::move(unfolded_groups)};
    }

    /// Unit Test
    void test() {
        std::ifstream istream(testFilename);
        PuzzleInput input(istream);

        std::vector samples = {"#.#.###",
                               ".#...#....###.",
                               ".#.###.#.######",
                               "####.#...#...",
                               "#....######..#####.",
                               ".###.##....#"};
        std::vector combinations = {1, 4, 1, 1, 4, 10};
        std::vector unfolded_combinations = {1, 16384, 1, 16, 2500, 506250};

        auto record = input.records.cbegin();
        auto combination = combinations.cbegin();
        auto unfolded_combination = unfolded_combinations.cbegin();
        for (auto sample = samples.cbegin(); sample != samples.cend(); ++sample, ++record, ++combination, ++unfolded_combination) {
            assert(record->is_valid(*sample));
            assert(find_permutations(*record) == *combination);
            assert(find_permutations(unfold_record(*record)) == *unfolded_combination);
        }

        assert(true);
    }

    /// Part One Solution
    int64_t partOne() {
        using namespace std::views;

        std::ifstream istream(inputFilename);
        PuzzleInput input(istream);
        return std::transform_reduce(input.records.begin(), input.records.end(), 0LL, std::plus{}, [](auto record) {
            return find_permutations(record);
        });
    }


    /// Part Two Solution
    int64_t partTwo() {
        using namespace std::views;

        std::ifstream istream(inputFilename);
        PuzzleInput input(istream);

        return 0;
    }

}

int main() {
    using namespace day12;
    test();
    advent::run<int64_t>(day, "One", partOne);
    advent::run<int64_t>(day, "Two", partTwo);
}