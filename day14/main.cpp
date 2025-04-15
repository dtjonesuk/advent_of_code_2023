#include "../advent.h"

namespace day14 {
    /// Change this to the current day
    static const std::string day = "14";
    static const std::string inputFilename = "..\\day" + day + "\\input.txt";
    static const std::string testFilename = "..\\day" + day + "\\test.txt";

    struct PuzzleInput {
        std::vector<std::string> lines;

        explicit PuzzleInput(std::istream &istream) {
            std::string line;

            while (std::getline(istream, line)) {
                // do something
                lines.emplace_back(std::move(line));
            }
        }

    };

    void tilt_north_south(std::vector<std::string> &lines, bool north = true) {
        for (int col = 0; col < lines[0].size(); ++col) {
            int can_move = 0;
            for (int line = north ? 0 : (lines.size() - 1);
                 line != (north ? lines.size() : -1); line += north ? 1 : -1) {
                switch (lines[line][col]) {
                    case '.':
                        can_move++;
                        break;
                    case '#':
                        can_move = 0;
                        break;
                    case 'O':
                        if (can_move) {
                            if (north)
                                std::swap(lines[line][col], lines[line - can_move][col]);
                            else
                                std::swap(lines[line][col], lines[line + can_move][col]);
                        }
                        break;
                }
            }
        }
    }

    void tilt_east_west(std::vector<std::string> &lines, bool west = true) {
        for (auto &line: lines) {
            int can_move = 0;
            for (int col = west ? 0 : (line.size() - 1);
                 col != (west ? line.size() : -1); col += west ? 1 : -1) {
                switch (line[col]) {
                    case '.':
                        can_move++;
                        break;
                    case '#':
                        can_move = 0;
                        break;
                    case 'O':
                        if (can_move) {
                            if (west)
                                std::swap(line[col], line[col - can_move]);
                            else
                                std::swap(line[col], line[col + can_move]);
                        }
                        break;
                }
            }
        }

    }

    void print(const std::vector<std::string> &lines) {
        for (auto &s: lines) {
            std::cout << s << std::endl;
        }
        std::cout << std::endl;
    }

    void cycle(std::vector<std::string> &lines) {
        tilt_north_south(lines);
        tilt_east_west(lines);
        tilt_north_south(lines, false);
        tilt_east_west(lines, false);
    }

    int64_t calculate_load(const std::vector<std::string> &lines) {
        int64_t load = 0;
        int single_load = lines.size();
        for (auto &s: lines) {
            load += single_load * std::count(s.begin(), s.end(), 'O');
            single_load--;
        }
        return load;
    }


    /// Unit Test
    void test() {
        std::ifstream istream(testFilename);
        PuzzleInput input(istream);
//        assert(calculate_load(input.lines) == 136);
        cycle(input.lines);
        print(input.lines);
        cycle(input.lines);
        print(input.lines);
        cycle(input.lines);
        print(input.lines);
    }

    /// Part One Solution
    int64_t partOne() {
        using namespace std::views;

        std::ifstream istream(inputFilename);
        PuzzleInput input(istream);

        tilt_north_south(input.lines);
        return calculate_load(input.lines);

    }


    /// Part Two Solution
    int64_t partTwo() {
        using namespace std::views;

        std::ifstream istream(inputFilename);
        PuzzleInput input(istream);
        std::vector<std::string> first_lines;

        int64_t last = 0;
        for (int64_t i = 0; i < 1'000'000'000; i++) {
            cycle(input.lines);
            int64_t current = calculate_load(input.lines);
            if (current == last){
                std::cout << "Iteration " << i << " matched." << std::endl;
            }
            last = current;
        }

        return calculate_load(input.lines);

    }
}

int main() {
    using namespace day14;
    test();
    advent::run<int64_t>(day, "One", partOne);
    advent::run<int64_t>(day, "Two", partTwo);
}
