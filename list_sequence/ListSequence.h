#pragma once
#include "Sequence.h"
#include "LinkedList.h"

template <class T>
class ListSequence : public Sequence<T> {
protected:
    LinkedList<T>* list;

public:
    ListSequence(T* items, int count) : list(new LinkedList<T>(items, count)) {}
    ListSequence() : list(new LinkedList<T>()) {}
    ListSequence(const ListSequence<T>& other) : list(new LinkedList<T>(*other.list)) {}
    virtual ~ListSequence() { delete list; }

    T GetFirst() const override { return list->GetFirst(); }
    T GetLast() const override { return list->GetLast(); }
    T Get(int index) const override { return list->Get(index); }
    int GetLength() const override { return list->GetLength(); }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        LinkedList<T>* sub = list->GetSubList(startIndex, endIndex);
        int subLen = sub->GetLength();
        T* items = new T[subLen];
        for (int i = 0; i < subLen; ++i) items[i] = sub->Get(i);
        Sequence<T>* result = this->CreateInstance(items, subLen);
        delete[] items;
        delete sub;
        return result;
    }

    Sequence<T>* Append(const T& item) override {
        int size = list->GetLength();
        T* items = new T[size + 1];
        for (int i = 0; i < size; ++i) items[i] = list->Get(i);
        items[size] = item;
        Sequence<T>* result = this->CreateInstance(items, size + 1);
        delete[] items;
        return result;
    }
    Sequence<T>* Prepend(const T& item) override {
        int size = list->GetLength();
        T* items = new T[size + 1];
        items[0] = item;
        for (int i = 0; i < size; ++i) items[i + 1] = list->Get(i);
        Sequence<T>* result = this->CreateInstance(items, size + 1);
        delete[] items;
        return result;
    }
    Sequence<T>* InsertAt(const T& item, int index) override {
        int size = list->GetLength();
        if (index < 0 || index > size) throw std::out_of_range("Index out of range");
        T* items = new T[size + 1];
        for (int i = 0; i < index; ++i) items[i] = list->Get(i);
        items[index] = item;
        for (int i = index; i < size; ++i) items[i + 1] = list->Get(i);
        Sequence<T>* result = this->CreateInstance(items, size + 1);
        delete[] items;
        return result;
    }
    Sequence<T>* Concat(Sequence<T>* other) override {
        if (!other) throw std::invalid_argument("Concat: nullptr");
        int size = list->GetLength();
        int otherSize = other->GetLength();
        T* items = new T[size + otherSize];
        for (int i = 0; i < size; ++i) items[i] = list->Get(i);
        for (int i = 0; i < otherSize; ++i) items[size + i] = other->Get(i);
        Sequence<T>* result = this->CreateInstance(items, size + otherSize);
        delete[] items;
        return result;
    }
};