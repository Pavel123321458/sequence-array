#pragma once
#include "Sequence.h"
#include "LinkedList.h"

template <class T>
class ListSequence : public Sequence<T> {
protected:
    LinkedList<T>* list;

    virtual ListSequence<T>* CreateInstance(T* items, int count) const = 0;

public:
    ListSequence(T* items, int count)
        : list(new LinkedList<T>(items, count)) {}

    ListSequence()
        : list(new LinkedList<T>()) {}

    ListSequence(const ListSequence<T>& other)
        : list(new LinkedList<T>(*other.list)) {}

    virtual ~ListSequence() {
        delete list;
    }

    virtual T GetFirst() const override {
        return list->GetFirst();
    }

    virtual T GetLast() const override {
        return list->GetLast();
    }

    virtual T Get(int index) const override {
        return list->Get(index);
    }

    virtual int GetLength() const override {
        return list->GetLength();
    }

    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        LinkedList<T>* subList = list->GetSubList(startIndex, endIndex);
        int subLen = subList->GetLength();
        T* items = new T[subLen];
        for (int i = 0; i < subLen; ++i)
            items[i] = subList->Get(i);
        Sequence<T>* result = CreateInstance(items, subLen);
        delete[] items;
        delete subList;
        return result;
    }

    virtual Sequence<T>* Append(const T& item) override {
        int size = list->GetLength();
        T* items = new T[size + 1];
        for (int i = 0; i < size; ++i)
            items[i] = list->Get(i);
        items[size] = item;
        Sequence<T>* result = CreateInstance(items, size + 1);
        delete[] items;
        return result;
    }

    virtual Sequence<T>* Prepend(const T& item) override {
        int size = list->GetLength();
        T* items = new T[size + 1];
        items[0] = item;
        for (int i = 0; i < size; ++i)
            items[i + 1] = list->Get(i);
        Sequence<T>* result = CreateInstance(items, size + 1);
        delete[] items;
        return result;
    }

    virtual Sequence<T>* InsertAt(const T& item, int index) override {
        int size = list->GetLength();
        if (index < 0 || index > size)
            throw std::out_of_range("Index out of range");
        T* items = new T[size + 1];
        for (int i = 0; i < index; ++i)
            items[i] = list->Get(i);
        items[index] = item;
        for (int i = index; i < size; ++i)
            items[i + 1] = list->Get(i);
        Sequence<T>* result = CreateInstance(items, size + 1);
        delete[] items;
        return result;
    }

    virtual Sequence<T>* Concat(Sequence<T>* other) override {
        if (other == nullptr)
            throw std::invalid_argument("Concat: nullptr argument");
        int size = list->GetLength();
        int otherSize = other->GetLength();
        T* items = new T[size + otherSize];
        for (int i = 0; i < size; ++i)
            items[i] = list->Get(i);
        for (int i = 0; i < otherSize; ++i)
            items[size + i] = other->Get(i);
        Sequence<T>* result = CreateInstance(items, size + otherSize);
        delete[] items;
        return result;
    }
};