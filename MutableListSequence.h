#pragma once
#include "ListSequence.h"

template <class T>
class MutableListSequence : public ListSequence<T> {
protected:
    virtual ListSequence<T>* CreateInstance(T* items, int count) const override {
        return new MutableListSequence<T>(items, count);
    }

public:
    MutableListSequence(T* items, int count)
        : ListSequence<T>(items, count) {}

    MutableListSequence()
        : ListSequence<T>() {}

    MutableListSequence(const MutableListSequence<T>& other)
        : ListSequence<T>(other) {}

    virtual Sequence<T>* Append(const T& item) override {
        this->list->Append(item);
        return this;
    }

    virtual Sequence<T>* Prepend(const T& item) override {
        this->list->Prepend(item);
        return this;
    }

    virtual Sequence<T>* InsertAt(const T& item, int index) override {
        this->list->InsertAt(item, index);
        return this;
    }

    virtual Sequence<T>* Concat(Sequence<T>* other) override {
        if (other == nullptr)
            throw std::invalid_argument("Concat: nullptr argument");
        int otherSize = other->GetLength();
        for (int i = 0; i < otherSize; ++i)
            this->list->Append(other->Get(i));
        return this;
    }
};