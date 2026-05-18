#pragma once
#include "ListSequence.h"

template <class T>
class MutableListSequence : public ListSequence<T> {
protected:
    Sequence<T>* CreateInstance(T* items, int count) const override {
        return new MutableListSequence<T>(items, count);
    }

public:
    MutableListSequence(T* items, int count) : ListSequence<T>(items, count) {}
    MutableListSequence() : ListSequence<T>() {}
    MutableListSequence(const MutableListSequence<T>& other) : ListSequence<T>(other) {}

    Sequence<T>* Append(const T& item) override {
        this->list->Append(item);
        return this;
    }
    Sequence<T>* Prepend(const T& item) override {
        this->list->Prepend(item);
        return this;
    }
    Sequence<T>* InsertAt(const T& item, int index) override {
        this->list->InsertAt(item, index);
        return this;
    }
    Sequence<T>* Concat(Sequence<T>* other) override {
        if (!other) throw std::invalid_argument("Concat: nullptr");
        for (int i = 0; i < other->GetLength(); ++i)
            this->list->Append(other->Get(i));
        return this;
    }
};