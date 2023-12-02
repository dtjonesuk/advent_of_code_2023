#include "../advent.h"
#include "Game.h"

namespace day02 {
    /// Change this to the current day
    static const std::string day = "02";
    static const std::string inputFilename = "..\\day" + day + "\\input.txt";
    static const std::string testFilename = "..\\day" + day + "\\test.txt";

    struct PuzzleInput {
        const std::regex game_re{"Game (\\d+):(.*)"};
        const std::regex round_re{"(\\d+) (red|green|blue)"};

        std::vector<Game> games;

        explicit PuzzleInput(const std::string &filename) {
            std::ifstream istream(filename);
            std::string line;

            while (std::getline(istream, line)) {
                std::smatch m;
                if (regex_match(line, m, game_re)) {
                    Game &game = games.emplace_back();
                    game.id = stoi(m.str(1));

                    std::stringstream ss = std::stringstream(m.str(2));
                    std::string round_string;
                    while (getline(ss, round_string, ';')) {
                        Round &round = game.rounds.emplace_back();
                        for (auto match = std::sregex_iterator(round_string.begin(), round_string.end(), round_re);
                             match != std::sregex_iterator{};
                             ++match) {
                            int n = stoi(match->str(1));
                            std::string color = match->str(2);

                            round.emplace(color, n);
                        }
                    }
                }
            }
        }
    };

    /// calculates the power of a set of cubes = n_of_red * n_of_blue & n_of_green
    int cube_power(Game &game) {
        Round round = game.minimum_required();
        return round["red"] * round["blue"] * round["green"];
    }

    /// calculates the sum of the ids of all the games that are possible
    int calc_possible_games(std::vector<Game> &games, Round &available) {
        using namespace std::views;

        auto valid_ids = games | filter([&](auto &game) { return game.is_possible(available); }) | transform(&Game::id);
        return std::ranges::fold_left(valid_ids, 0, std::plus{});
    }

    /// calculates the sum of the powers for the minimum required set of cubes for all games
    int calc_minimum_cube_power(std::vector<Game> &games) {
        using namespace std::views;

        auto powers = games | transform(cube_power);
        return std::ranges::fold_left(powers, 0, std::plus{});
    }

    /// Unit Test
    void test() {
        Round available{{"red",   12},
                        {"green", 13},
                        {"blue",  14}};
        PuzzleInput input(testFilename);

        assert(calc_possible_games(input.games, available) == 8);
        assert(input.games.size() == 5);
        assert(input.games[3].id == 4);
        assert(input.games[2].rounds.size() == 3);
        assert(input.games[4].rounds[1]["blue"] == 2);
        assert(calc_minimum_cube_power(input.games) == 2286);
    }

    /// Part One Solution
    int partOne() {

        PuzzleInput input(inputFilename);
        Round available{{"red",   12},
                        {"green", 13},
                        {"blue",  14}};

        return calc_possible_games(input.games, available);
    }


    /// Part Two Solution
    int partTwo() {
        using namespace std::views;

        PuzzleInput input(inputFilename);

        return calc_minimum_cube_power(input.games);
    }

    void run() {
        test();

        {
            std::cout << std::fixed << std::setprecision(3);
            auto [seconds, result] = advent::eval<int>(&partOne);

            std::cout << "Day " << day << ": Part One = " << result << "\t\t (completed in " << seconds << "s).\n";
        }
        {
            std::cout << std::fixed << std::setprecision(3);
            auto [seconds, result] = advent::eval<int>(&partTwo);

            std::cout << "Day " << day << ": Part One = " << result << "\t (completed in " << seconds << "s).\n";
        }
    }
}

int main() {
    day02::run();
}