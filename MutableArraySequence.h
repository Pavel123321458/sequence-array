#pragma once
#include "ArraySequence.h"

template <class T>
class MutableArraySequence : public ArraySequence<T> {
protected:
    virtual ArraySequence<T>* CreateInstance(T* items, int count) const override {
        return new MutableArraySequence<T>(items, count);
    }

public:
    MutableArraySequence(T* items, int count)
        : ArraySequence<T>(items, count) {}

    MutableArraySequence()
        : ArraySequence<T>() {}

    MutableArraySequence(const MutableArraySequence<T>& other)
        : ArraySequence<T>(other) {}

    virtual Sequence<T>* Append(const T& item) override {
        this->array->Append(item);
        return this;
    }

    virtual Sequence<T>* Prepend(const T& item) override {
        this->array->Prepend(item);
        return this;
    }

    virtual Sequence<T>* InsertAt(const T& item, int index) override {
        this->array->InsertAt(item, index);
        return this;
    }

    virtual Sequence<T>* Concat(Sequence<T>* other) override {
        if (other == nullptr)
            throw std::invalid_argument("Concat: nullptr argument");
        int otherSize = other->GetLength();
        for (int i = 0; i < otherSize; ++i)
            this->array->Append(other->Get(i));
        return this;
    }
};