#pragma once
#include "ArraySequence.h"

template <class T>
class MutableArraySequence : public ArraySequence<T> {
protected:
    Sequence<T>* CreateInstance(T* items, int count) const override {
        return new MutableArraySequence<T>(items, count);
    }

public:
    MutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}
    MutableArraySequence() : ArraySequence<T>() {}
    MutableArraySequence(const MutableArraySequence<T>& other) : ArraySequence<T>(other) {}

    Sequence<T>* Append(const T& item) override {
        this->array->Append(item);
        return this;
    }
    Sequence<T>* Prepend(const T& item) override {
        this->array->Prepend(item);
        return this;
    }
    Sequence<T>* InsertAt(const T& item, int index) override {
        this->array->InsertAt(item, index);
        return this;
    }
    Sequence<T>* Concat(Sequence<T>* other) override {
        if (!other) throw std::invalid_argument("Concat: nullptr");
        for (int i = 0; i < other->GetLength(); ++i)
            this->array->Append(other->Get(i));
        return this;
    }
};