#include "../advent.h"

namespace day13 {
    /// Change this to the current day
    static const std::string day = "13";
    static const std::string inputFilename = "..\\day" + day + "\\input.txt";
    static const std::string testFilename = "..\\day" + day + "\\test.txt";

    using Pattern = std::vector<std::string>;

    struct PuzzleInput {
        std::vector<Pattern> patterns;

        explicit PuzzleInput(std::istream &istream) {
            std::string line;

            do {
                Pattern &pattern = patterns.emplace_back();

                while (std::getline(istream, line)) {
                    // read pattern until empty line
                    if (line == "")
                        break;

                    pattern.emplace_back(std::move(line));
                }
            } while (istream.good());
        }

    };

    /// Returns true if there is a vertical line of reflection
    /// between col and col+1
    bool is_v_reflection(const Pattern &pattern, int col) {
        //  first and last cols cannot be mirror lines
        if ( (col == pattern.size() - 1))
            return false;

        size_t width = pattern[0].size();
        int l = col;
        int r = col + 1;

        do {
            if (std::any_of(pattern.begin(), pattern.end(), [&](auto p) {
                return p[l] != p[r];
            }))
                return false;

            --l;
            ++r;
        } while ((l >= 0) && (r < width));
        return true;
    }

    /// Returns true if there is a horizontal line of reflection
    /// between row and row+1
    bool is_h_reflection(const Pattern &pattern, int row) {
        //  last rows cannot be mirror lines
        if ((row == pattern.size() - 1))
            return false;

        size_t height = pattern.size();
        int t = row;
        int b = row + 1;

        do {
            if (pattern[t] != pattern[b])
                return false;

            --t;
            ++b;
        } while ((t >= 0) && (b < height));
        return true;
    }

    int find_vertical_reflection(const Pattern &pattern) {
        for (int col = 0; col < pattern[0].size() - 1; col++) {
            if (is_v_reflection(pattern, col))
                return col + 1;  // col numbered from 1
        }
        return 0;
    }

    int find_horizontal_reflection(const Pattern &pattern) {
        for (int row = 0; row < pattern.size() - 1; row++) {
            if (is_h_reflection(pattern, row))
                return row + 1;  // row numbered from 1
        }
        return 0;
    }

    /// Unit Test
    void test() {
        std::ifstream istream(testFilename);
        PuzzleInput input(istream);
        assert(input.patterns.size() == 2);
        assert(is_v_reflection(input.patterns[0], 4));
        assert(!is_v_reflection(input.patterns[0], 3));
        assert(is_h_reflection(input.patterns[1], 3));
        assert(!is_h_reflection(input.patterns[1], 4));

        assert(std::transform_reduce(input.patterns.begin(), input.patterns.end(), 0LL, std::plus{},
                                     find_vertical_reflection) == 5);
        assert(std::transform_reduce(input.patterns.begin(), input.patterns.end(), 0LL, std::plus{},
                                     find_horizontal_reflection) == 4);
    }

    /// Part One Solution
    int64_t partOne() {
        using namespace std::views;

        std::ifstream istream(inputFilename);
        PuzzleInput input(istream);

        int64_t vertical = std::transform_reduce(input.patterns.begin(), input.patterns.end(), 0LL, std::plus{},
                                                 find_vertical_reflection);

        int64_t horizontal = std::transform_reduce(input.patterns.begin(), input.patterns.end(), 0LL, std::plus{},
                                                   find_horizontal_reflection);


        return vertical + (horizontal * 100);
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
    using namespace day13;
//    test();
    advent::run<int64_t>(day, "One", partOne);
    advent::run<int64_t>(day, "Two", partTwo);
}