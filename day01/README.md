# Advent of Code 2023 :: Day 01

# Trebuchet?!

## Task

Today we are tasked with finding various calibration values for a trebuchet the elves are strapping me into!

## Parsing the input

The puzzle input consists of a set of calibration value strings, one per line. My boilerplate framework produces
a `vector<string>` of the input by default.

## Part One

We need to calculate the calibration values from the input strings. Each calibration value consists of the first and
last digits of the string put together as a two-digit number.

### Calibration value

We can extract the calibration value from the string as follows:

1. Filter only the digits in the string.
2. Take the `first` element of the digit list.
3. Take the `last` element of the digit list (the first element of the reversed list);
4. Return `first * 10 + last`

```c++
auto digits = filter(line, isdigit);
int first = digits.front() - '0';
int last = reverse(digits).front() - '0';
return first * 10 + last;
```

We can calculate the calibration value on the entire input and sum all these values by using `std::ranges`.

```c++
auto values = input.lines | transform(sumFirstLast);
int result = fold_left(values, 0, std::plus{});
```

## Part Two

The elves have messed up again and it turns out we have to interpret the following words as
digits: `one`, `two`, `three`, `four`, `five`, `six`, `seven`, `eight` and `nine`.

The approach I selected for this task was to:

1. Use a `regex` to find occurrences of the words we need to replace.
2. Use a `map<string, char>` to replace the first character of word with the respective digit.

In this way, `one` becomes `1ne`, `two` becomes `2wo`, `three` becomes `3hree`, etc. Then we can simply use the code
from part one to calculate the calibration value. As there are now digits where the word used to be, the correct
calibration value can be found. There is no point in contracting the string by removing the extra letters in the words,
as our calculating function strips all non-digits from the string anyway.

```c++
const std::regex re("(one|two|three|four|five|six|seven|eight|nine)");
for (auto i = std::sregex_iterator(output.begin(), output.end(), re);
    i != std::sregex_iterator();
    ++i) {
        const std::smatch &m = *i;
        output[m.position()] = replacements.at(m.str(1));
}
```

## Conclusion

I thank the elves for allowing us a gentle warm-up day this year.

One small gotcha, was that you can't use a simple naive search-and-replace function in part two. Globally
replacing `one` with `1` then `two` with `2`, etc. This fails because `twone` becomes `tw1` rather than `2ne`.

Having _discovered_ this 'feature', I adopted the regular expression approach.  `sregex_iterator` was unfamiliar to me,
but proved to be effective, although I wish there the syntax was a little more concise. 