//
// Created by David on 01/12/2023.
//
#ifndef ADVENT_OF_CODE_2023_ADVENT_H
#define ADVENT_OF_CODE_2023_ADVENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <ranges>
#include <regex>
#include <chrono>
#include <cassert>

namespace advent {
/// Benchmarks a callable
    template<typename T>
    std::pair<double, T> eval(std::function<T()> func) {
        const auto t1 = std::chrono::high_resolution_clock::now();
        T result = func();
        const auto t2 = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> seconds = t2 - t1;

        return std::make_pair(seconds.count(), result);
    }
}
#endif //ADVENT_OF_CODE_2023_ADVENT_H
