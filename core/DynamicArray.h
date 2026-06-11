#pragma once
#include <stdexcept>
#include "Sequence.h"

template <class T>
class DynamicArray {
private:
    T* data;
    int size;
    int capacity;

    void ensureCapacity(int needed) {
        if (needed <= capacity) return;
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        while (newCapacity < needed)
            newCapacity *= 2;
        T* newData = new T[newCapacity]();
        for (int i = 0; i < size; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    class Iterator : public Sequence<T>::Iterator {
    private:
        T* ptr;
    public:
        Iterator(T* p) : ptr(p) {}
        T& operator*() override { return *ptr; }
        typename Sequence<T>::Iterator& operator++() override { ++ptr; return *this; }
        bool operator!=(const typename Sequence<T>::Iterator& other) const override {
            return ptr != static_cast<const Iterator&>(other).ptr;
        }
        T* getPtr() const { return ptr; }
    };

    Iterator* begin() { return new Iterator(data); }
    Iterator* end() { return new Iterator(data + size); }

    DynamicArray(T* items, int count) : size(count), capacity(count) {
        if (count < 0) throw std::invalid_argument("Negative size");
        data = new T[count];
        for (int i = 0; i < count; ++i) data[i] = items[i];
    }

    explicit DynamicArray(int size) : size(size), capacity(size) {
        if (size < 0) throw std::invalid_argument("Negative size");
        data = new T[size]();
    }

    DynamicArray(const DynamicArray<T>& other) : size(other.size), capacity(other.capacity) {
        data = new T[capacity];
        for (int i = 0; i < size; ++i) data[i] = other.data[i];
    }

    DynamicArray<T>& operator=(const DynamicArray<T>& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            for (int i = 0; i < size; ++i) data[i] = other.data[i];
        }
        return *this;
    }

    ~DynamicArray() { delete[] data; }

    T Get(int index) const {
        if (index < 0 || index >= size) throw std::out_of_range("IndexOutOfRange");
        return data[index];
    }

    int GetSize() const { return size; }

    void Set(int index, const T& value) {
        if (index < 0 || index >= size) throw std::out_of_range("IndexOutOfRange");
        data[index] = value;
    }

    void Append(const T& item) {
        ensureCapacity(size + 1);
        data[size] = item;
        ++size;
    }

    void Prepend(const T& item) {
        ensureCapacity(size + 1);
        for (int i = size; i > 0; --i) data[i] = data[i - 1];
        data[0] = item;
        ++size;
    }

    void InsertAt(const T& item, int index) {
        if (index < 0 || index > size) throw std::out_of_range("IndexOutOfRange");
        ensureCapacity(size + 1);
        for (int i = size; i > index; --i) data[i] = data[i - 1];
        data[index] = item;
        ++size;
    }

    void Resize(int newSize) {
        if (newSize < 0) throw std::invalid_argument("Negative new size");
        if (newSize > capacity) ensureCapacity(newSize);
        size = newSize;
    }
};