#pragma once
#include "ListSequence.h"

template <class T>
class ImmutableListSequence : public ListSequence<T> {
protected:
    Sequence<T>* CreateInstance(T* items, int count) const override {
        return new ImmutableListSequence<T>(items, count);
    }

public:
    ImmutableListSequence(T* items, int count) : ListSequence<T>(items, count) {}
    ImmutableListSequence() : ListSequence<T>() {}
    ImmutableListSequence(const ImmutableListSequence<T>& other) : ListSequence<T>(other) {}
};