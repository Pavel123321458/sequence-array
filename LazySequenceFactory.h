#pragma once
#include "LazySequence.h"
#include <functional>

// Факториал
LazySequence<int>* FactorialSequence() {
    int initial[] = {1};
    std::function<int(const MutableArraySequence<int>&)> rule = [](const MutableArraySequence<int>& history) -> int {
        int n = history.GetLength();
        return history.Get(n - 1) * n;
    };
    return new LazySequence<int>(rule, initial, 1);
}

// Числа Фибоначчи
LazySequence<int>* FibonacciSequence() {
    int initial[] = {0, 1};
    std::function<int(const MutableArraySequence<int>&)> rule = [](const MutableArraySequence<int>& history) -> int {
        int n = history.GetLength();
        return history.Get(n - 1) + history.Get(n - 2);
    };
    return new LazySequence<int>(rule, initial, 2);
}

// Степени двойки
LazySequence<int>* PowersOfTwo() {
    int initial[] = {1};
    std::function<int(const MutableArraySequence<int>&)> rule = [](const MutableArraySequence<int>& history) -> int {
        return history.Get(history.GetLength() - 1) * 2;
    };
    return new LazySequence<int>(rule, initial, 1);
}

// Натуральные числа
LazySequence<int>* NaturalNumbers() {
    int initial[] = {1};
    std::function<int(const MutableArraySequence<int>&)> rule = [](const MutableArraySequence<int>& history) -> int {
        return history.Get(history.GetLength() - 1) + 1;
    };
    return new LazySequence<int>(rule, initial, 1);
}