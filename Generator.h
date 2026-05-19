#pragma once
#include <functional>
#include <stdexcept>

template <class T>
class Generator {
private:
    std::function<T(const std::vector<T>&)> rule;  // правило порождения
    std::vector<T> history;                         // уже порождённые элементы
    int generated;                                  // сколько элементов порождено
    int maxCount;                                   // максимальное количество (-1 — бесконечно)

public:
    Generator(std::function<T(const std::vector<T>&)> r, T* initial, int count, int max = -1)
        : rule(r), generated(count), maxCount(max) {
        for (int i = 0; i < count; ++i)
            history.push_back(initial[i]);
    }

    Generator() : rule(nullptr), generated(0), maxCount(0) {}

    bool HasNext() const {
        return maxCount == -1 || generated < maxCount;
    }

    T GetNext() {
        if (!HasNext())
            throw std::out_of_range("Generator: no more elements");
        if (generated >= (int)history.size()) {
            T next = rule(history);
            history.push_back(next);
        }
        return history[generated++];
    }

    T Get(int index) {
        if (maxCount != -1 && index >= maxCount)
            throw std::out_of_range("Generator: index out of range");
        while (index >= (int)history.size()) {
            if (!HasNext())
                throw std::out_of_range("Generator: index out of range");
            history.push_back(rule(history));
        }
        return history[index];
    }

    int GetGeneratedCount() const {
        return generated;
    }

    int GetMaterializedCount() const {
        return history.size();
    }
};