//
// Created by David on 10/12/2023.
//

#ifndef ADVENT_OF_CODE_2023_PIPE_H
#define ADVENT_OF_CODE_2023_PIPE_H

#include <string>
#include <vector>
#include <set>
#include <map>
#include <stdexcept>

namespace day10 {

    struct Pipe {
        int x, y;

        bool operator<(const Pipe &other) const {
            if (x == other.x)
                return y < other.y;
            return x < other.x;
        }

        bool operator==(const Pipe &other) const {
            return (x == other.x) && (y == other.y);
        }
    };

    class Schematic {
    public:
        std::map<Pipe, char> pipes;
        std::multimap<Pipe, Pipe> connections;
        unsigned width, height;
        Pipe start;

        Schematic(const std::vector<std::string> &input) {
            if (input.empty())
                return;

            height = input.size();
            width = input[0].size();

            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    char c = input[y][x];
                    Pipe p{x, y};
                    pipes.emplace(p, c);

                    switch (c) {
                        case 'S':
                            start = p;
                            break;
                        case '|':
                            add_connection(p, x, y - 1);
                            add_connection(p, x, y + 1);
                            break;
                        case '-':
                            add_connection(p, x - 1, y);
                            add_connection(p, x + 1, y);
                            break;
                        case 'L':
                            add_connection(p, x, y - 1);
                            add_connection(p, x + 1, y);
                            break;
                        case 'J':
                            add_connection(p, x, y - 1);
                            add_connection(p, x - 1, y);
                            break;
                        case '7':
                            add_connection(p, x - 1, y);
                            add_connection(p, x, y + 1);
                            break;
                        case 'F':
                            add_connection(p, x + 1, y);
                            add_connection(p, x, y + 1);
                            break;
                        case '.':
                            break;
                        default:
                            throw std::invalid_argument("Unknown character in input stream");
                    }
                }
            }

            // add connections for start position
            for (auto [from, to]: connections) {
                if (to == start)
                    add_connection(start, from.x, from.y);
            }
        }

        int length() {
            // set of visited pipes
            std::set<Pipe> visited;

            // pick a (random) connection for start
            Pipe current = start;
            visited.emplace(start);

            // len includes start, so begins at 1
            int len = 1;

            do {
                // get connection that's not been visited
                auto it = connections.lower_bound(current);
                while ((it->first == current) && (visited.contains(it->second))) {
                    ++it;
                }
                if (it->first != current) {
                    // no more unvisted tiles in the loop
                    break;
                }

                current = it->second;
                visited.emplace(current);

                ++len;
            } while (true);

            return len;
        }

    private:
        void add_connection(Pipe &pipe, int x, int y) {
            if ((x >= 0) && (x < width) && (y >= 0) && (y < height)) {
                connections.insert({pipe, {x, y}});
            }
        }
    };

} // day10

#endif //ADVENT_OF_CODE_2023_PIPE_H
