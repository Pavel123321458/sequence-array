#pragma once
#include "Sequence.h"
#include "Generator.h"
#include "MutableArraySequence.h"
#include <vector>
#include <functional>

template <class T>
class LazySequence : public Sequence<T> {
private:
    mutable Generator<T>* generator;
    mutable MutableArraySequence<T>* cache;
    int knownSize;

public:
    LazySequence() : generator(new Generator<T>()), cache(new MutableArraySequence<T>()), knownSize(0) {}

    LazySequence(T* items, int count)
        : generator(nullptr), cache(new MutableArraySequence<T>(items, count)), knownSize(count) {}

    LazySequence(Sequence<T>* seq)
        : generator(nullptr), knownSize(seq->GetLength()) {
        T* items = new T[knownSize];
        for (int i = 0; i < knownSize; ++i)
            items[i] = seq->Get(i);
        cache = new MutableArraySequence<T>(items, knownSize);
        delete[] items;
    }

    LazySequence(std::function<T(const std::vector<T>&)> rule, T* initial, int initCount, int max = -1)
        : generator(new Generator<T>(rule, initial, initCount, max)),
          cache(new MutableArraySequence<T>()),
          knownSize(max) {
        for (int i = 0; i < initCount; ++i)
            cache->Append(initial[i]);
    }

    LazySequence(const LazySequence<T>& other)
        : generator(nullptr),
          cache(new MutableArraySequence<T>(*other.cache)),
          knownSize(other.knownSize) {}

    ~LazySequence() {
        delete generator;
        delete cache;
    }

    T GetFirst() const override {
        if (GetLength() == 0)
            throw std::out_of_range("IndexOutOfRange: sequence is empty");
        return Get(0);
    }

    T GetLast() const override {
        if (knownSize == -1)
            throw std::runtime_error("Cannot get last of infinite sequence");
        if (knownSize == 0)
            throw std::out_of_range("IndexOutOfRange: sequence is empty");
        return Get(knownSize - 1);
    }

    T Get(int index) const override {
        if (knownSize != -1 && index >= knownSize)
            throw std::out_of_range("IndexOutOfRange");
        if (generator && index >= cache->GetLength()) {
            while (generator->HasNext() && index >= cache->GetLength()) {
                cache->Append(generator->GetNext());
            }
        }
        if (index >= cache->GetLength())
            throw std::out_of_range("IndexOutOfRange");
        return cache->Get(index);
    }

    int GetLength() const override {
        return knownSize;
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if (knownSize != -1 && (startIndex < 0 || endIndex >= knownSize || startIndex > endIndex))
            throw std::out_of_range("IndexOutOfRange");
        int newSize = endIndex - startIndex + 1;
        T* items = new T[newSize];
        for (int i = 0; i < newSize; ++i)
            items[i] = Get(startIndex + i);
        Sequence<T>* result = new MutableArraySequence<T>(items, newSize);
        delete[] items;
        return result;
    }

    int GetMaterializedCount() const {
        return cache->GetLength();
    }

    Sequence<T>* Append(const T& item) override {
        int size = knownSize == -1 ? cache->GetLength() : knownSize;
        T* items = new T[size + 1];
        for (int i = 0; i < size; ++i)
            items[i] = Get(i);
        items[size] = item;
        Sequence<T>* result = new MutableArraySequence<T>(items, size + 1);
        delete[] items;
        return result;
    }

    Sequence<T>* Prepend(const T& item) override {
        int size = knownSize == -1 ? cache->GetLength() : knownSize;
        T* items = new T[size + 1];
        items[0] = item;
        for (int i = 0; i < size; ++i)
            items[i] = Get(i);
        Sequence<T>* result = new MutableArraySequence<T>(items, size + 1);
        delete[] items;
        return result;
    }

    Sequence<T>* InsertAt(const T& item, int index) override {
        int size = knownSize == -1 ? cache->GetLength() : knownSize;
        if (index < 0 || index > size)
            throw std::out_of_range("IndexOutOfRange");
        T* items = new T[size + 1];
        for (int i = 0; i < index; ++i)
            items[i] = Get(i);
        items[index] = item;
        for (int i = index; i < size; ++i)
            items[i + 1] = Get(i);
        Sequence<T>* result = new MutableArraySequence<T>(items, size + 1);
        delete[] items;
        return result;
    }

    Sequence<T>* Concat(Sequence<T>* list) override {
        int size1 = knownSize == -1 ? cache->GetLength() : knownSize;
        int size2 = list->GetLength();
        T* items = new T[size1 + size2];
        for (int i = 0; i < size1; ++i)
            items[i] = Get(i);
        for (int i = 0; i < size2; ++i)
            items[size1 + i] = list->Get(i);
        Sequence<T>* result = new MutableArraySequence<T>(items, size1 + size2);
        delete[] items;
        return result;
    }

protected:
    Sequence<T>* CreateInstance(T* items, int count) const override {
        return new MutableArraySequence<T>(items, count);
    }
};