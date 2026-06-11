#pragma once
#include "Sequence.h"
#include "DynamicArray.h"

template <class T>
class ArraySequence : public Sequence<T> {
protected:
    DynamicArray<T>* array;

public:
    ArraySequence(T* items, int count) : array(new DynamicArray<T>(items, count)) {}
    ArraySequence() : array(new DynamicArray<T>(0)) {}
    ArraySequence(const ArraySequence<T>& other) : array(new DynamicArray<T>(*other.array)) {}
    virtual ~ArraySequence() { delete array; }

    typename Sequence<T>::Iterator* begin() override {
        return new typename DynamicArray<T>::Iterator(array->begin()->getPtr());
    }
    typename Sequence<T>::Iterator* end() override {
        return new typename DynamicArray<T>::Iterator(array->end()->getPtr());
    }

    T GetFirst() const override {
        if (array->GetSize() == 0) throw std::out_of_range("Index out of range: sequence is empty");
        return array->Get(0);
    }

    T GetLast() const override {
        int size = array->GetSize();
        if (size == 0) throw std::out_of_range("Index out of range: sequence is empty");
        return array->Get(size - 1);
    }

    T Get(int index) const override { return array->Get(index); }
    int GetLength() const override { return array->GetSize(); }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        int size = array->GetSize();
        if (startIndex < 0 || endIndex >= size || startIndex > endIndex)
            throw std::out_of_range("Index out of range");
        int newSize = endIndex - startIndex + 1;
        T* items = new T[newSize];
        for (int i = 0; i < newSize; ++i) items[i] = array->Get(startIndex + i);
        Sequence<T>* result = this->CreateInstance(items, newSize);
        delete[] items;
        return result;
    }

    Sequence<T>* Append(const T& item) override {
        int size = array->GetSize();
        T* items = new T[size + 1];
        for (int i = 0; i < size; ++i) items[i] = array->Get(i);
        items[size] = item;
        Sequence<T>* result = this->CreateInstance(items, size + 1);
        delete[] items;
        return result;
    }

    Sequence<T>* Prepend(const T& item) override {
        int size = array->GetSize();
        T* items = new T[size + 1];
        items[0] = item;
        for (int i = 0; i < size; ++i) items[i + 1] = array->Get(i);
        Sequence<T>* result = this->CreateInstance(items, size + 1);
        delete[] items;
        return result;
    }

    Sequence<T>* InsertAt(const T& item, int index) override {
        int size = array->GetSize();
        if (index < 0 || index > size) throw std::out_of_range("Index out of range");
        T* items = new T[size + 1];
        for (int i = 0; i < index; ++i) items[i] = array->Get(i);
        items[index] = item;
        for (int i = index; i < size; ++i) items[i + 1] = array->Get(i);
        Sequence<T>* result = this->CreateInstance(items, size + 1);
        delete[] items;
        return result;
    }

    Sequence<T>* Concat(Sequence<T>* other) override {
        if (!other) throw std::invalid_argument("Concat: nullptr");
        int size = array->GetSize();
        int otherSize = other->GetLength();
        T* items = new T[size + otherSize];
        for (int i = 0; i < size; ++i) items[i] = array->Get(i);
        for (int i = 0; i < otherSize; ++i) items[size + i] = other->Get(i);
        Sequence<T>* result = this->CreateInstance(items, size + otherSize);
        delete[] items;
        return result;
    }
};