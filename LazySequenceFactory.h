#pragma once
#include "LazySequence.h"
#include <vector>
#include <functional>

// Факториал: 1, 1, 2, 6, 24, 120, ...
LazySequence<int>* FactorialSequence() {
    int initial[] = {1};
    std::function<int(const std::vector<int>&)> rule = [](const std::vector<int>& history) -> int {
        int n = history.size();
        return history.back() * n;
    };
    return new LazySequence<int>(rule, initial, 1);
}

// Числа Фибоначчи: 0, 1, 1, 2, 3, 5, 8, 13, ...
LazySequence<int>* FibonacciSequence() {
    int initial[] = {0, 1};
    std::function<int(const std::vector<int>&)> rule = [](const std::vector<int>& history) -> int {
        int n = history.size();
        return history[n - 1] + history[n - 2];
    };
    return new LazySequence<int>(rule, initial, 2);
}

// Степени двойки: 1, 2, 4, 8, 16, 32, ...
LazySequence<int>* PowersOfTwo() {
    int initial[] = {1};
    std::function<int(const std::vector<int>&)> rule = [](const std::vector<int>& history) -> int {
        return history.back() * 2;
    };
    return new LazySequence<int>(rule, initial, 1);
}

// Натуральные числа: 1, 2, 3, 4, 5, ...
LazySequence<int>* NaturalNumbers() {
    int initial[] = {1};
    std::function<int(const std::vector<int>&)> rule = [](const std::vector<int>& history) -> int {
        return history.back() + 1;
    };
    return new LazySequence<int>(rule, initial, 1);
}