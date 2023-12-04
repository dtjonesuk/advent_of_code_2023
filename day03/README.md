# Advent of Code 2023 :: Day 03

## Gear Ratios

Today we are tasked with fixing the engine for a gondola lift.

## Parsing the input

The input parser is a custom `Schematic` that handles the input and searching functions.

* `find_neighbours` generates search zones around a part number
* `has_adjacent_symbol` searches zones for an engine part symbol
* `has_adjacent_gear` searches zones for a gear symbol only
* `find_part_numbers` finds all the **part numbers** that have adjacent engine parts
* `find_gears` finds all the **gear ratio pairs** that are connected by a gear symbol

## Part One

Once the part numbers have been found, producing the sum is trivial.

```c++
auto part_numbers = input.schematic.find_part_numbers();
return std::reduce(part_numbers.begin(), part_numbers.end());
```

## Part Two

Again, once the gear ratio pairs have been found producing the relevant sum is made easy by the use of `std::range`
functions.

```c++
auto gears = input.schematic.find_gears()
                     | filter([](auto &item) { return item.second.size() == 2; })
                     | transform([](auto &item) { return item.second[0] * item.second[1]; });
return std::reduce(gears.begin(), gears.end());
```

## Conclusion

I hate string searching puzzles, but they are part of the game so here we are. In retrospect, it occurs to me that there
are two ways to approach this puzzle.

1. Find the numbers and search for 'parts' around them.
2. Find the parts and search for 'numbers' around them.

I'm not entirely sure which of these is the most efficient, but I opted for the first one.