//
// Created by David on 02/12/2023.
//

#include "Game.h"
#include <algorithm>

namespace day02 {

    /// checks whether a game is possible given the available contents
    /// a game is possible if:
    ///     for all of the rounds...
    ///     for all the cubes shown...
    ///     number of cubes available >= number of cubes shown
    bool Game::is_possible(Round &available) {
        return std::ranges::all_of(rounds, [&](Round &round) {
            return std::ranges::all_of(round, [&](auto pair){
                return (available[pair.first] >= pair.second);
            });
        });
    }

    /// calculates the minimum required set of cubes for a game to be possible
    Round Game::minimum_required() {
        Round min{{"red", 0}, {"green", 0}, {"blue", 0}};
        for (Round& round : rounds) {
            for (auto& [colour, n] : round) {
                if (n > min[colour])
                    min[colour] = n;
            }
        }
        return min;
    }
} // day02