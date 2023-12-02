# Advent of Code 2023 :: Day 02

## Cube Conundrum

Today we are tasked with paying various games with an elf who pulls different coloured cubes out of a bag at random.

## Parsing the input

Each game is listed with its id followed by a semicolon-separated list of rounds that were played. A round
consists of a comma-separated list of a number followed by the colour of the cube.

```
Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
```

To parse the input I decided to use the following strategy:

1. Use a `regex` to extract the game's id and the list of *rounds* (everything following the `:`).
2. Use a `stringstream` to iterate over each `;` separated *round*.
3. Use another `regex` to extract the number of respective red, green & blue cubes from the `,` separated list.

The subsequent data structure looks as follows:

* The input consists of a `vector<Game> games`.
* Each `Game` contains an `int id` and `vector<Round> rounds`;
* Each `Round` is a `map<string,int>` that maps the colour of a cube to number of cubes.

## Part One

The Elf would first like to know which games would have been possible if the bag contained
only `12 red cubes, 13 green cubes, and 14 blue` cubes? The puzzle answer is the sum of the IDs of those games.

### Is a game possible?

The `is_possible()` function takes checks whether a game could legally be played given the available set of cubes. A
game is possible if and only if:

* for all of the rounds...
* for all each colour cube that was shown...
* the number of cubes of that colour available >= number of cubes shown

### Summing it all up

As I am trying to learn to use C++20's `std::ranges` feature, I opted for the following strategy:

1. Filter the list of games according to which were possible.
2. Transform each `Game` to the `id` of the game.
3. Calculate the sum of all the `id`s in the list. This is the puzzle answer.

This translates into the following code:

```c++
auto valid_ids = games | filter([&](auto &game) { return game.is_possible(available); }) | transform(&Game::id);
return std::ranges::fold_left(valid_ids, 0, std::plus{});
```

## Part Two

The elf wants to know what is the fewest number of cubes of each color that could have been in the bag to make the game
possible?

### Cube Power?

The cube power involves finding the _minimum_ required set of cubes for a game to be possible. To do this, we can simply
iterate through the rounds to determine the _maximum_ shown number of red, green and blue cubes respectively.
The cube power is the product of the number of red, green and blue cubes in the minimum set.

### The answer

Now we know how to calculate the cube power, finding the answer is simply a matter of:

1. For each game: calculate the `cube_power` of that game
2. Sum the list of powers. This is the puzzle answer.

This translates into the following code:

```c++
auto powers = games | transform(cube_power);
return std::ranges::fold_left(powers, 0, std::plus{});
```

## Conclusion

All in all, another good day for the elves. I'm still not 100% confident that my parser is the best, but it was quick to
write and produces a neat data structure. There are many ways to parse text input!

Using `std::ranges` produces compact, readable and easily composable code. It is definitely proving to be worthwhile
learning. 