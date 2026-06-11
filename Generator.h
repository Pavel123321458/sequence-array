#pragma once
#include <functional>
#include <stdexcept>
#include "MutableArraySequence.h"

template <class T>
class Generator {
private:
    std::function<T(const MutableArraySequence<T>&)> rule;
    MutableArraySequence<T> history;
    int generated;
    int maxCount;

public:
    Generator() : rule(nullptr), history(), generated(0), maxCount(0) {}

    Generator(std::function<T(const MutableArraySequence<T>&)> r, T* initial, int count, int max = -1)
        : rule(r), history(initial, count), generated(count), maxCount(max) {}

    bool HasNext() const {
        return maxCount == -1 || generated < maxCount;
    }

    T GetNext() {
        if (!HasNext())
            throw std::out_of_range("Generator: no more elements");
        if (generated >= history.GetLength()) {
            T next = rule(history);
            history.Append(next);
        }
        return history.Get(generated++);
    }

    T Get(int index) {
        if (maxCount != -1 && index >= maxCount)
            throw std::out_of_range("Generator: index out of range");
        while (index >= history.GetLength()) {
            if (!HasNext())
                throw std::out_of_range("Generator: index out of range");
            history.Append(rule(history));
        }
        return history.Get(index);
    }

    int GetGeneratedCount() const {
        return generated;
    }

    int GetMaterializedCount() const {
        return history.GetLength();
    }
};