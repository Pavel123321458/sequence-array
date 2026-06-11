#pragma once
#include "ArraySequence.h"

template <class T>
class ImmutableArraySequence : public ArraySequence<T> {
protected:
    Sequence<T>* CreateInstance(T* items, int count) const override {
        return new ImmutableArraySequence<T>(items, count);
    }

public:
    ImmutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}
    ImmutableArraySequence() : ArraySequence<T>() {}
    ImmutableArraySequence(const ImmutableArraySequence<T>& other) : ArraySequence<T>(other) {}
};